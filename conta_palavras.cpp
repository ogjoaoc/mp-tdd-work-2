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

bool checaTextoVazio(std::string texto) {
    if(texto == "") return true;
    return false;
}

std::vector<std::pair<std::string,int>> ContaPalavras(std::string texto) {
    if(checaTextoVazio(texto)) {
        return std::vector<std::pair<std::string,int>> ();
    } 
    return {{"-1", 0}};
}