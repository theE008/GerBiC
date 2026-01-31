//////////////////////////////////////////////////////////////////////
// Headers

// Header Próprio
#include "tamanho_chars.h"

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// #include "modules.h"

// Headers de Outros módulos
#include "erro_handler.h"

// Outros Headers
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Retorna o index em que o '\0' foi encontrado.
int tamanho_chars (const char* str)
{
    erro_se ("Argumento NULL", str == NULL);

    char c = str [0];
    int x = 0;

    while (c != '\0') c = str [++ x];

    return x;
}

//////////////////////////////////////////////////////////////////////
