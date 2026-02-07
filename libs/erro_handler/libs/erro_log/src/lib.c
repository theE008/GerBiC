//////////////////////////////////////////////////////////////////////
// Headers

// Header Próprio
#include "erro_log.h"

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
# include "modules.h"

#ifdef TEM_ERRO_TERMINAL
    #include "erro_terminal.h"
#endif

// Outros Headers
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Escreve texto no arquivo log 
void erro_log_write_chars 
(
    const char* log_arq, 
    const char* msg 
)
{
    FILE* a_log = fopen (log_arq, "at");

    if (!a_log)
    {
        #ifdef TEM_ERRO_TERMINAL
            Erro_terminal 
            (
                "Arquivo de Log para erros não encontrado, erro fatal"
            );
        #else 
            printf 
            (
                "\n\n\tArquivo de Log para erros não encontrado, erro fatal\n\n"
            );
            exit (-1);
        #endif
    } 

    fprintf (a_log, msg);

    fflush (a_log);
    fclose (a_log);
}


// Escreve o erro no final do log
void erro_log 
(
    const char* log_arq,
    const char* arq,
    const char* func, 
    const char* msg,
    int ln 
) 
{
    FILE* a_log = fopen (log_arq, "at");

    if (!a_log)
    {
        #ifdef TEM_ERRO_TERMINAL
            Erro_terminal 
            (
                "Arquivo de Log para erros não encontrado, erro fatal"
            );
        #else 
            printf 
            (
                "\n\n\tArquivo de Log para erros não encontrado, erro fatal\n\n"
            );
            exit (-1);
        #endif
    }

    static int erros = 0;

    erros++;

    fprintf 
    (
        a_log,
        "\n\n\t[%d] Erro no GerBiC"
        "\n\tArquivo: %s"
        "\n\tFunção: %s"
        "\n\tLinha: %d"
        "\n\n\tErro: %s\n\n",
        erros,
        arq,
        func,
        ln,
        msg 
    );

    #ifdef ERRO_LOG_PRE_KILL
        ERRO_LOG_PRE_KILL ();
    #endif 

    fflush (a_log);
    fclose (a_log);
}

//////////////////////////////////////////////////////////////////////
