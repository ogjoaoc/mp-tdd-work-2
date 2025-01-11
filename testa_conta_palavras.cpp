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