//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stddef.h> // size_t
#include <stdarg.h> // va_args

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "buffer_concatenar.h"

#include "buffer.h"
#include "erro_handler.h"
#include "argumentos.h"
#include "tamanhoTexto.h"

//////////////////////////////////////////////////////////////////////
// Definições



//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Concatena o valor usando o buffer 
// Retorna o char* resultante
char* Buffer_concatenar (Buffer* destino, const char* orig_a, const char* orig_b)
{
    ERRO_SE_NULO (destino);

    size_t t_a = tamanhoTexto (orig_a);
    size_t t_b = tamanhoTexto (orig_b);
    size_t t   = t_a + t_b;

    ERRO_SE ("Tamanho insuficiente", t + 1 > destino->tamanho);

    if ((uint8_t*)orig_a != destino->dados)
        for (size_t x = 0; x < t_a; x++)
            BUFFER_ACESSAR (*destino, char, x) = orig_a [x];

    for (size_t y = 0; y < t_b; y++)
        BUFFER_ACESSAR (*destino, char, y + t_a) = orig_b [y];

    BUFFER_ACESSAR (*destino, uint8_t, t) = '\0';

    return destino->dados;
}

// Concatena vários 
char* Buffer_unirInterno (Buffer* destino, ...)
{
    ERRO_SE_NULO (destino);

    ARGUMENTOS (destino)
    {
        char* s = RECEBER_ARG (char*);
        ERRO_SE_NULO (s);

        size_t t_a = tamanhoTexto (s);
        ERRO_SE ("Tamanho insuficiente", t_a + 1 > destino->tamanho);

        if ((uint8_t*)s != destino->dados)
            for (size_t x = 0; x < t_a; x++)
                BUFFER_ACESSAR (*destino, char, x) = s [x]; // aqui

        while ((s = RECEBER_ARG (char*)) != NULL)
        {
            size_t tam = tamanhoTexto (s);

            ERRO_SE ("Tamanho insuficiente", t_a + tam + 1 > destino->tamanho);

            for (size_t x = 0; x < tam; x++)
                BUFFER_ACESSAR (*destino, char, x + t_a) = s [x];

            t_a += tam;
        }

        BUFFER_ACESSAR(*destino, char, t_a) = '\0';
    }

    return destino->dados;
}

//////////////////////////////////////////////////////////////////////
