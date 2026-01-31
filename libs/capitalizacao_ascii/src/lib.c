//////////////////////////////////////////////////////////////////////
// Headers

// Header Próprio
#include "capitalizacao_ascii.h"

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// #include "modules.h"

// Headers de Outros módulos
#include "tamanho_chars.h"
#include "erro_handler.h"

// Outros Headers
#include <stdbool.h> 

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Verifica se é maiúscula
bool eh_maiuscula (char carac)
{
    bool resp = false;

    if ('A' <= carac && carac <= 'Z') resp = true;

    return resp;
}

// Verifica se é minúscula
bool eh_minuscula (char carac)
{
    bool resp = false;

    if ('a' <= carac && carac <= 'z') resp = true;

    return resp;
} 

// Passa para maiúscula se necessário 
char para_maiuscula (char c)
{
    if (eh_minuscula (c)) c -= 32;

    return c;
}

// Passa para minúscula se necessário
char para_minuscula (char c)
{
    if (eh_maiuscula (c)) c += 32;

    return c;
}

// Passa todo o texto para maiúsculas 
void para_maiusculas (char* str) 
{
    erro_se_nulo (str);

    int tam = tamanho_chars (str);

    for (int x = 0; x < tam; x++)
        str [x] = para_maiuscula (str [x]);
}

// Passa todo o texto para minúsculas
void para_minusculas (char* str) 
{
    erro_se_nulo (str);

    int tam = tamanho_chars (str);

    for (int x = 0; x < tam; x++)
        str [x] = para_minuscula (str [x]);
}

//////////////////////////////////////////////////////////////////////
