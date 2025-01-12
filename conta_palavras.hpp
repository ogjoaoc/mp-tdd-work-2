#include <string>
#include <vector>

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

HashMap* build();
unsigned encode(HashMap* hashMap, const char* chave);
int get(HashMap* hashMap, const char* chave);
void add(HashMap* hashMap, const char* chave, int num);
std::vector<std::pair<std::string,int>> processaContagem(HashMap* contador, std::vector<std::string> lista_de_palavras);
std::vector<std::pair<std::string, int>> ContaPalavras(std::string texto);
bool checaTextoVazio(std::string texto);
std::vector<std::string> separaPalavras(std::string texto);
std::string removePontuacao(std::string palavra);

