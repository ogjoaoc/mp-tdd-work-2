#include <iostream>

#include <string>

#include <sstream>

#include <vector>

#include <cstdlib>

#include <cstring>

#include <cctype>

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
  hashMap->capacidade = 1009; // máximo de palavras
  hashMap->tamanho = 0; // quantas palavras diferentes até agora
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
  return -1; 
}

void add(HashMap* hashMap, const char* chave, int num) {
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

bool checaTextoVazio(std::string texto) {
  if (texto == "") return true;
  return false;
}

std::vector<std::pair<std::string,int>> ContaPalavras(std::string texto) {
  if (checaTextoVazio(texto)) {
    return std::vector<std::pair<std::string,int>> ();
  }
  return {{"-1", 0}};
}