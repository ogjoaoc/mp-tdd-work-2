#include <iostream>

#include <string>

#include <sstream>

#include <vector>

#include <cstdlib>

#include <cstring>

#include <cctype>

#include <utility>

/**
 * @file conta_palavras.cpp
 * @brief Implementação de uma função para contar palavras em um texto.
 */
#include "conta_palavras.hpp"

/** 
 * @brief Contador de palavras
 * @author João Carlos 
 * @param  texto string do texto de entrada
 * 
 */


HashMap* build() {
  HashMap* hashMap = (HashMap*) malloc(sizeof(HashMap));
  hashMap->capacidade = 1009;  // máximo de palavras
  hashMap->tamanho = 0;   // quantas palavras diferentes até agora
  hashMap->lista = (Par**) calloc(hashMap->capacidade, sizeof(Par*));
  return hashMap;
}

unsigned encode(HashMap* hashMap, const char* chave) {
  unsigned code = 0;
  while (*chave != '\0') {
    code = *chave + 31 * code;
    chave++;
  }
  return code % hashMap->capacidade;
}

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

std::vector<std::string> separaPalavras(std::string texto) {
  std::istringstream iss(texto);
  std::string palavra;
  std::vector <std::string> lista_de_palavras;
  while (iss >> palavra) {
    lista_de_palavras.push_back(palavra);
  }
  return lista_de_palavras;
}

std::string normalizarPalavra(const std::string& palavra) {
  std::vector<std::pair<std::string, std::string>> mapa_de_substituicoes = {
    {"á", "a"}, {"à", "a"}, {"â", "a"}, {"ã", "a"}, {"ä", "a"},
    {"é", "e"}, {"è", "e"}, {"ê", "e"}, {"ë", "e"},
    {"í", "i"}, {"ì", "i"}, {"î", "i"}, {"ï", "i"},
    {"ó", "o"}, {"ò", "o"}, {"ô", "o"}, {"õ", "o"}, {"ö", "o"},
    {"ú", "u"}, {"ù", "u"}, {"û", "u"}, {"ü", "u"},
    {"ç", "c"}, {"Á", "A"}, {"À", "A"}, {"Â", "A"}, {"Ã", "A"}, {"Ä", "A"},
    {"É", "E"}, {"È", "E"}, {"Ê", "E"}, {"Ë", "E"},
    {"Í", "I"}, {"Ì", "I"}, {"Î", "I"}, {"Ï", "I"},
    {"Ó", "O"}, {"Ò", "O"}, {"Ô", "O"}, {"Õ", "O"}, {"Ö", "O"},
    {"Ú", "U"}, {"Ù", "U"}, {"Û", "U"}, {"Ü", "U"},
    {"Ç", "C"}
  };
  std::string resultado = palavra;
  for (auto & [letra_acentuada, letra_sem_acento]: mapa_de_substituicoes) {
    unsigned long long pos = 0;
    while ((pos = resultado.find(letra_acentuada, pos)) != std::string::npos) {
      resultado.replace(pos, letra_acentuada.length(), letra_sem_acento);
      pos += letra_sem_acento.length();
    }
  }
  return resultado;
}

std::string removePontuacao(std::string palavra) {
  std::string resultado;
  for (char& letra : palavra) {
    if (!std::ispunct(letra)) {
      resultado.push_back(letra);
    }
  }
  return resultado;
}

bool checaTextoVazio(std::string texto) {
  if (texto == "") return true;
  return false;
}

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
  return processaContagem(Contador, lista_de_palavras);
}