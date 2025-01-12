#include <string>
#include <vector>
#include <utility>

struct Par {
  char* chave;
  int valor;
  Par* prox;
};
struct HashMap {
  Par** lista;
  unsigned int capacidade;
  unsigned int tamanho; 
};

bool compararPares(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);
void merge(int esquerda, int direita, std::vector<std::pair<std::string, int>>& palavrasContadas);
void mergeSort(int esquerda, int direita, std::vector<std::pair<std::string, int>>& palavrasContadas);
void ordenaContagem(std::vector<std::pair<std::string, int>>& palavrasContadas);
HashMap* build();
unsigned encode(HashMap* hashMap, const char* chave);
int get(HashMap* hashMap, const char* chave);
void add(HashMap* hashMap, const char* chave, int num);
std::vector<std::pair<std::string,int>> processaContagem(HashMap* contador, std::vector<std::string> lista_de_palavras);
std::vector<std::string> separaPalavras(std::string texto);
std::string normalizarPalavra(std::string palavra, bool converter_para_lowercase = false);
std::string removePontuacao(std::string palavra);
bool checaTextoVazio(std::string texto);
std::vector<std::pair<std::string, int>> ContaPalavras(std::string texto);