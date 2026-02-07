//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stddef.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "size_t_paraTexto.h"

#include "erro_handler.h"
#include "buffer_concatenar.h"
#include "inverterTexto.h"
#include "buffer.h"

//////////////////////////////////////////////////////////////////////
// Definições



//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Função que transforma size_t em texto 
char* size_t_paraTexto (Buffer* bfr, size_t val)
{
    ERRO_SE_NULO (bfr);
    
    if (val == 0) BUFFER_UNIR (*bfr, "0");
    else 
    {
        bfr->dados [0] = '\0';

        while (val)
        {
            char digito [2] = "0";
            digito [0] += (val % 10);
            Buffer_concatenar (bfr, bfr->dados, digito);
            val /= 10;
        }

        inverterTexto (bfr->dados);
    }
    
    return bfr->dados;
}

//////////////////////////////////////////////////////////////////////
