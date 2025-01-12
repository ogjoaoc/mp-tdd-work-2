#include <iostream>

#include <string>

#include <sstream>

#include <fstream>

#include <vector>

#include <cstdlib>

#include <cstring>

#include <cctype>

#include <utility>

/**
 * @file conta_palavras.cpp
 * @brief Implementação de uma função para contar palavras em um texto.
 * @author João Carlos
 */
#include "conta_palavras.hpp"


/**
 * @brief Lê o conteúdo de um arquivo e retorna uma string.
 * @param nome_arquivo O nome do arquivo de input.
 * @return O conteúdo do arquivo como uma string.
 */
std::string lerArquivo(const std::string nome_arquivo) {
  std::ifstream arquivo("input/" + nome_arquivo);
  if (!arquivo.is_open()) {  
    std::cerr << "Erro ao abrir o arquivo: " << nome_arquivo << '\n';
    return "-1";
  }
  std::stringstream buffer;  
  buffer << arquivo.rdbuf();  
  return buffer.str();  
}

/**
 * @brief Compara duas palavras com base na normalização.
 * @param palavra_a Primeira palavra para comparação.
 * @param palavra_b Segunda palavra para comparação.
 * @return true se a primeira palavra for menor que a segunda após normalização, false caso contrário.
 */
bool compararPares(const std::pair<std::string, int>& palavra_a, const std::pair<std::string, int>& palavra_b) {
    return normalizarPalavra(palavra_a.first, true) < normalizarPalavra(palavra_b.first, true);
}

/**
 * @brief Processo de merge para ordenar palavras contadas.
 * @param esquerda Índice da parte esquerda do vetor a ser ordenado.
 * @param direita Índice da parte direita do vetor a ser ordenado.
 * @param palavrasContadas Vetor de pares (palavra, contagem) a ser ordenado.
 */
void merge(int esquerda, int direita, std::vector<std::pair<std::string, int>>& palavrasContadas) {
  int meio = esquerda + (direita - esquerda) / 2;
  int ponteiro_esquerda = esquerda, ponteiro_direita = meio + 1;
  std::vector<std::pair<std::string, int>> auxiliar;
  while (ponteiro_esquerda <= meio && ponteiro_direita <= direita) {
    if (compararPares(palavrasContadas[ponteiro_direita], palavrasContadas[ponteiro_esquerda])) {
      auxiliar.push_back(palavrasContadas[ponteiro_direita++]);
    } else {
      auxiliar.push_back(palavrasContadas[ponteiro_esquerda++]);
    }
  }
  while (ponteiro_esquerda <= meio) {
    auxiliar.push_back(palavrasContadas[ponteiro_esquerda++]);
  }
  while (ponteiro_direita <= direita) {
    auxiliar.push_back(palavrasContadas[ponteiro_direita++]);
  }
  for (int i = 0; i < (int)auxiliar.size(); i++) {
    palavrasContadas[esquerda + i] = auxiliar[i];
  }
}

/**
 * @brief Ordena o vetor de palavras contadas utilizando o algoritmo MergeSort.
 * @param esquerda Índice inicial do vetor a ser ordenado.
 * @param direita Índice final do vetor a ser ordenado.
 * @param palavrasContadas Vetor de pares (palavra, contagem) a ser ordenado.
 */
void mergeSort(int esquerda, int direita, std::vector<std::pair<std::string, int>>& palavrasContadas) {
  if (esquerda < direita) {
    int meio = esquerda + (direita - esquerda) / 2;
    mergeSort(esquerda, meio, palavrasContadas);
    mergeSort(meio + 1, direita, palavrasContadas);
    merge(esquerda, direita, palavrasContadas);
  }
}

/**
 * @brief  Faz ordenação das palavras contadas utilizando mergeSort.
 * @param palavrasContadas Vetor de pares (palavra, contagem) a ser ordenado.
 */
void ordenaContagem(std::vector<std::pair<std::string, int>>& palavrasContadas) {
  mergeSort(0, (int)palavrasContadas.size() - 1, palavrasContadas);
} 

/**
 * @brief Cria e inicializa um novo HashMap.
 * @return Um ponteiro para o novo HashMap alocado.
 */
HashMap* build() {
  HashMap* hashMap = (HashMap*) malloc(sizeof(HashMap));
  hashMap->capacidade = 1009;  // máximo de palavras
  hashMap->tamanho = 0;   // quantas palavras diferentes até agora
  hashMap->lista = (Par**) calloc(hashMap->capacidade, sizeof(Par*));
  return hashMap;
}

/**
 * @brief Codifica uma chave (palavra) utilizando um algoritmo de hash.
 * @param hashMap Ponteiro para o HashMap onde a chave será armazenada.
 * @param chave A chave (palavra) a ser codificada.
 * @return O código gerado para a chave.
 */
unsigned encode(HashMap* hashMap, const char* chave) {
  unsigned code = 0;
  while (*chave != '\0') {
    code = *chave + 31 * code;
    chave++;
  }
  return code % hashMap->capacidade;
}

/**
 * @brief Busca o valor associado a uma chave no HashMap.
 * @param hashMap Ponteiro para o HashMap.
 * @param chave A chave a ser buscada.
 * @return O valor associado à chave ou -1 se não encontrado.
 */
int get(HashMap* hashMap, const char* chave) {
  // dado determinado índice, calculado na função hash,
  // encontra nó(Par) inicial referente aquele índice, e faz a busca pela chave.
  unsigned index = encode(hashMap, chave);
  Par* atual = hashMap->lista[index];
  while (atual) {
    if (strcmp(atual->chave, chave) == 0) {
      return atual->valor;
    }
    atual = atual->prox;
  }
  return -1;
}

/**
 * @brief Adiciona ou atualiza um par chave-valor no HashMap.
 * @param hashMap Ponteiro para o HashMap.
 * @param chave A chave a ser adicionada ou atualizada.
 * @param num O valor a ser associado à chave.
 */
void add(HashMap* hashMap, const char* chave, int num) {
  unsigned index = encode(hashMap, chave);
  Par* atual = hashMap->lista[index];
  while (atual) {
    if (strcmp(atual->chave, chave) == 0) {
      atual->valor = num;
      return;
    }
    atual = atual->prox;
  }
  Par* novaChaveAuxiliar = (Par*)malloc(sizeof(Par));
  novaChaveAuxiliar->chave = strdup(chave);
  novaChaveAuxiliar->valor = num;
  novaChaveAuxiliar->prox = hashMap->lista[index];
  hashMap->lista[index] = novaChaveAuxiliar;
  hashMap->tamanho++;
}

/**
 * @brief Desaloca memória utilizada por um HashMap.
 * @param contador Ponteiro para o HashMap contendo as contagens das palavras.
 */
void desalocarHashMap(HashMap* hashMap) {
  for (int i = 0; i < hashMap->capacidade; i++) {
    Par* atual = hashMap->lista[i];
    while (atual) {
      Par* auxiliar = atual;
      atual = atual->prox;
      free(auxiliar->chave);
      free(auxiliar);
    }
  }
  free(hashMap->lista);
  free(hashMap);
}

/**
 * @brief Processa as contagens das palavras no HashMap e as retorna como um vetor de pares (palavra, contagem).
 * @param contador Ponteiro para o HashMap contendo as contagens das palavras.
 * @param lista_de_palavras Lista de palavras para comparar com o HashMap.
 * @return Um vetor de pares (palavra, contagem) das palavras encontradas.
 */
std::vector<std::pair<std::string, int>> processaContagem(HashMap* contador, std::vector<std::string> lista_de_palavras) {
  std::vector<std::pair<std::string, int>> palavrasContadas;
  for (int i = 0; i < (int)contador->capacidade; i++) {
    Par* atual = contador->lista[i];
    while (atual) {
      int contagem = atual->valor;
      char* chave = atual->chave;
      for (auto &palavra : lista_de_palavras) {
        if (palavra == chave) {
          palavrasContadas.push_back({palavra, contagem});    
          break;
        }
      }
      atual = atual->prox;
    }
  }
  return palavrasContadas;
}

/**
 * @brief Separa um texto em palavras, removendo pontuações.
 * @param texto O texto de entrada a ser separado em palavras.
 * @return Um vetor de palavras extraídas do texto.
 */
std::vector<std::string> separaPalavras(std::string texto) {
  std::istringstream iss(texto);
  std::string palavra;
  std::vector <std::string> lista_de_palavras;
  while (iss >> palavra) {
    palavra = removePontuacao(palavra);
    lista_de_palavras.push_back(palavra);
  }
  return lista_de_palavras;
}

/**
 * @brief Normaliza uma palavra, convertendo caracteres acentuados para suas versões sem acento e para minúsculas se indicado.
 * @param palavra A palavra a ser normalizada.
 * @param converter_para_lowercase Indica se a palavra deve ser convertida para minúsculas.
 * @return A palavra normalizada.
 */
std::string normalizarPalavra(std::string palavra, bool converter_para_lowercase) {
  std::vector<std::pair<std::string, std::string>> mapa_de_substituicoes = {
    {"á", "a"}, {"à", "a"}, {"â", "a"}, {"ã", "a"}, {"ä", "a"},
    {"é", "e"}, {"è", "e"}, {"ê", "e"}, {"ë", "e"},
    {"í", "i"}, {"ì", "i"}, {"î", "i"}, {"ï", "i"},
    {"ó", "o"}, {"ò", "o"}, {"ô", "o"}, {"õ", "o"}, {"ö", "o"},
    {"ú", "u"}, {"ù", "u"}, {"û", "u"}, {"ü", "u"}, {"ç", "c"},
    {"Á", "A"}, {"À", "A"}, {"Â", "A"}, {"Ã", "A"}, {"Ä", "A"},
    {"É", "E"}, {"È", "E"}, {"Ê", "E"}, {"Ë", "E"},
    {"Í", "I"}, {"Ì", "I"}, {"Î", "I"}, {"Ï", "I"},
    {"Ó", "O"}, {"Ò", "O"}, {"Ô", "O"}, {"Õ", "O"}, {"Ö", "O"},
    {"Ú", "U"}, {"Ù", "U"}, {"Û", "U"}, {"Ü", "U"}, {"Ç", "C"}
  };
  std::string resultado = palavra;
  for (auto & [letra_acentuada, letra_sem_acento]: mapa_de_substituicoes) {
    unsigned long long posicao_acento = 0;
    while ((posicao_acento = resultado.find(letra_acentuada, posicao_acento)) != std::string::npos) {
      resultado.replace(posicao_acento, letra_acentuada.length(), letra_sem_acento);
      posicao_acento += letra_sem_acento.length();
    }
  }
  if (converter_para_lowercase) {
    for (char& letra : resultado) {
      letra = tolower(letra);
    }
  }
  return resultado;
}

/**
 * @brief Remove pontuações de uma palavra.
 * @param palavra A palavra da qual as pontuações serão removidas.
 * @return A palavra sem pontuações.
 */
std::string removePontuacao(std::string palavra) {
  std::string resultado;
  for (char& letra : palavra) {
    if (!std::ispunct(letra)) {
      resultado.push_back(letra);
    }
  }
  return resultado;
}

/**
 * @brief Verifica se o texto fornecido está vazio.
 * @param texto O texto a ser verificado.
 * @return true se o texto estiver vazio, false caso contrário.
 */
bool checaTextoVazio(std::string texto) {
  if (texto == "") return true;
  return false;
}

/**
 * @brief Função principal para contar as palavras em um texto.
 * @param texto O texto a ser analisado.
 * @return Um vetor de pares (palavra, contagem) representando a contagem de palavras no texto.
 */
std::vector<std::pair<std::string, int>> ContaPalavras(std::string texto) {
  if (checaTextoVazio(texto)) {
    return std::vector<std::pair<std::string, int>> ();
  }
  HashMap* Contador = build();
  std::vector<std::string> lista_de_palavras = separaPalavras(texto);
  for (auto palavra_atual : lista_de_palavras) {
    int contagem = get(Contador, palavra_atual.c_str());
    if (contagem == -1) {
        add(Contador, palavra_atual.c_str(), 1);
    } else {
        add(Contador, palavra_atual.c_str(), contagem + 1);
    }
  }
  std::vector<std::pair<std::string, int>> palavrasContadas = processaContagem(Contador, lista_de_palavras);
  ordenaContagem(palavrasContadas);
  return palavrasContadas;
}
