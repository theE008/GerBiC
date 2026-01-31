//////////////////////////////////////////////////////////////////////
// Headers

// Header Próprio
#include "copiar_em_buffer.h"

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// #include "modules.h"

// Headers de Outros módulos
#include "tamanho_chars.h"
#include "erro_handler.h"

// Outros Headers
#include <stddef.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Copia uma char[] em outra. 
void copiar_em_buffer (char* destino, size_t max, const char* origem)
{
    erro_se_nulo (destino);
    erro_se_nulo (origem);

    size_t tam = tamanho_chars (origem);

    erro_se ("Origem maior que destino", tam >= max);

    for (int x = 0; x < tam; x++)
        destino [x] = origem [x]; 

    destino [tam] = '\0';
}

//////////////////////////////////////////////////////////////////////
