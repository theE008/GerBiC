//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stddef.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "substituirTexto.h"

#include "erro_handler.h"
#include "acharTexto.h"
#include "tamanhoTexto.h"
#include "buffer.h"

//////////////////////////////////////////////////////////////////////
// Definições



//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Substiur um por um 
char* substituirPrimeiro (Buffer* fonte, const char* regex, const char* alt)
{
    ERRO_SE_NULO (fonte);
    ERRO_SE_NULO (regex);
    ERRO_SE_NULO (alt);

    size_t tamF = tamanhoTexto (fonte->dados);
    size_t tamA = tamanhoTexto (alt);
    size_t tamR = tamanhoTexto (regex);
    size_t onde = acharTexto (fonte->dados, regex, 0);

    if (onde < tamF) // Se não achou, acaba aqui 
    {
        long total = (long)tamA - (long)tamR;

        ERRO_SE ("Tamanho insuficiente", total + tamF > fonte->tamanho);

        if (total > 0)
            for (size_t x = tamF; x >= onde; x--)
                BUFFER_ACESSAR (*fonte, char, x + total) = BUFFER_ACESSAR (*fonte, char, x);

        else if (total < 0)
            for (size_t x = onde + tamR; x <= tamF; x++)
                BUFFER_ACESSAR (*fonte, char, x + total) = BUFFER_ACESSAR (*fonte, char, x);

        // Escrever no espaço feito
        for (size_t i = 0; i < tamA; i++)
            fonte->dados[onde + i] = alt[i];
    }
        
    return fonte->dados;
}

// Substitui todas as instâncias de uma substring por outra 
// Tem que ser em Buffer pra garantir que não irá estourar o tamanho
// Lembre-se: isso aqui é TERRÍVEL E CRIMINOSO
// Atualize isso de forma mais inteligente depois!
// Só que agora? Não sei exatamente como fazer isso, ficaria muito 
// complexo da forma original que imaginei
char* substituirTexto (Buffer* fonte, const char* regex, const char* alt) 
{
    ERRO_SE_NULO (fonte);
    ERRO_SE_NULO (regex);
    ERRO_SE_NULO (alt);

    size_t tamA = tamanhoTexto (alt);
    size_t ptr = 0;
    
    // Enquanto achar o regex, substitui um por um
    size_t onde = 0;
    while ((onde = acharTexto (fonte->dados, regex, ptr)) < tamanhoTexto (fonte->dados)) 
    {
        substituirPrimeiro (fonte, regex, alt); 
        
        ptr = onde + tamA;
    }

    return fonte->dados;
}

//////////////////////////////////////////////////////////////////////
