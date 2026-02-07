//////////////////////////////////////////////////////////////////////
// Headers 

// Header Próprio
#include "erro_terminal.h"

// Outros Headers 
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Função que lança um erro padrão no terminal 
void erro_terminal 
(
    const char *arq,
    const char *func,
    const char *msg,
    int ln
)
{
    printf 
    ( 
        "\n\n\t\033[1;31mErro no GerBiC"
        "\n\tArquivo: %s"
        "\n\tFunção: %s"
        "\n\tLinha: %d"
        "\n\n\tErro: %s\033[0m\n\n",
        arq, func, ln, msg 
    );

    #ifdef ERRO_TERMNAL_PRE_KILL
        ERRO_TERMINAL_PRE_KILL ();
    #endif 
    
    // Para código de erro
    exit (ln > 0 ? ln : EXIT_FAILURE);
}

//////////////////////////////////////////////////////////////////////
