//////////////////////////////////////////////////////////////////////
// Headers

// Header Próprio
#include "erro_handler.h"

// Headers da própria biblioteca 
#include "erro_log.h"
#include "erro_terminal.h" // Necessita de ambos para funcionar 
                           
// Outros Headers
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Variáveis


//////////////////////////////////////////////////////////////////////
// Funções

// Lança textos no local junto com os erros para decorar/informar 
// melhor.
void erro_handler_write_chars
(
    const char* txt 
)
{
    #if ERRO_HANDLER_MODE == 1 
        printf ("%s", txt);
    #endif 

    #if ERRO_HANDLER_MODE == 2
        erro_log_write_chars (ERRO_LOG_ARQUIVO_PADRAO, txt);
    #endif 
}

// Lança o erro desejado 
void erro_handler
(
    const char* arq,
    const char* func,
    const char* msg,
    int ln,
    int tst
)
{
    #if ERRO_HANDLER_MODE == 1 
        if (tst) erro_terminal (arq, func, msg, ln);
    #endif

    #if ERRO_HANDLER_MODE == 2
        if (tst) erro_log 
        (
            ERRO_LOG_ARQUIVO_PADRAO,
            arq, func, msg, ln 
        );
    #endif 

    // Se não for nem um nem outro, simplesmente não faz nada 
}

// Retorna o modo do handler 
int erro_handler_modo () {return ERRO_HANDLER_MODE;}

//////////////////////////////////////////////////////////////////////

