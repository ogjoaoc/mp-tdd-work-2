/**
 * \file testa_conta_palavras.cpp
 */

#include "conta_palavras.hpp"

#define CATCH_CONFIG_NO_POSIX_SIGNALS
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <vector>
#include <iostream>

TEST_CASE("Teste 1: Texto vazio.") {
  std::string texto = "";
  auto resultado = ContaPalavras(texto);
  REQUIRE(resultado.empty());
}

TEST_CASE("Teste 2: Separação de palavras do texto.") {
  std::string texto = "devem estar separadas";
  std::vector<std::string> esperado = {
    {"devem"},
    {"estar"},
    {"separadas"}
  };
  auto resultado = separaPalavras(texto);
  REQUIRE(resultado == esperado);
}

TEST_CASE("Teste 3: Teste especial para inserção de palavra no HashMap.") {
  std::string palavra = "opa";
  HashMap* contador_auxiliar = build();
  add(contador_auxiliar, palavra.c_str(), 1);
  REQUIRE(contador_auxiliar->tamanho == 1);
  REQUIRE(get(contador_auxiliar, palavra.c_str()) == 1);
}

TEST_CASE("Teste 4: Texto com uma única palavra.") {
  std::string texto = "palavra";
  auto resultado = ContaPalavras(texto);
}