//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stddef.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "acharTexto.h"

#include "erro_handler.h"
#include "tamanhoTexto.h"

//////////////////////////////////////////////////////////////////////
// Definições



//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Retorna a posição da primeira instância daquele texto 
size_t acharTexto (const char* fonte, const char* regex, const size_t inicio)
{
    ERRO_SE_NULO (fonte);
    ERRO_SE_NULO (regex);

    size_t tamF = tamanhoTexto (fonte);
    size_t tamR = tamanhoTexto (regex);

    size_t x = inicio;
    size_t isMatch = 0;

    if (inicio >= tamF || tamR == 0) 
        x = tamF + 1;

    for (; isMatch != tamR && x <= tamF - tamR; x++) 
    {
        isMatch = 0;

        // Tenta casar a regex a partir da posição x
        while (isMatch < tamR && fonte[x + isMatch] == regex[isMatch]) 
            isMatch++;
    }

    return (isMatch == tamR) ? (x - 1) : tamF;
}

// Retorna a posição da última instância daquele texto 
size_t acharUltimoTexto (const char* fonte, const char* regex, size_t fim)
{
    ERRO_SE_NULO (fonte);
    ERRO_SE_NULO (regex);

    size_t tamF = tamanhoTexto (fonte);
    size_t tamR = tamanhoTexto (regex);
    
    // x começa no ponto de busca ou no limite máximo seguro
    size_t x = (fim >= (tamF - tamR)) ? (tamF - tamR) : fim;
    size_t isMatch = 0;
    
    bool processando = (tamF >= tamR && tamR > 0);
    size_t resultado = tamF;

    while (processando)
    {
        isMatch = 0;

        while (isMatch < tamR && fonte [x + isMatch] == regex [isMatch])
            isMatch++;

        if (isMatch == tamR)
        {
            resultado = x;
            processando = 0; // Para o loop
        }
        else if (x == 0) processando = 0; // Chegou no início e não achou
        else x--; // Continua voltando
    }

    return resultado;
}
// Conta quantas vezes o texto aparece na string
size_t ocorrenciasEmTexto (const char* fonte, const char* regex) 
{
    ERRO_SE_NULO (fonte);
    ERRO_SE_NULO (regex);

    size_t contagem = 0;
    size_t tamF = tamanhoTexto(fonte);
    size_t tamR = tamanhoTexto(regex);
    size_t ptr = 0;

    if (tamR != 0)
    while (ptr <= tamF - tamR) 
    {
        size_t proximo = acharTexto (fonte, regex, ptr);
        
        if (proximo < tamF) 
        {
            contagem++;
            ptr = proximo + tamR; // Pula a palavra inteira para não contar sobreposto
        } 
        else ptr = tamF; // Encerra o loop
    }

    return contagem;
}
                
//////////////////////////////////////////////////////////////////////
