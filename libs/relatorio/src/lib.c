//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stdint.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "relatorio.h"

#include "buffer.h"
#include "erro_handler.h"
#include "buffer_concatenar.h"
#include "size_t_paraTexto.h"
#include "destrutor_handler.h"

//////////////////////////////////////////////////////////////////////
// Definições

#define parse size_t_paraTexto

//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Um wrapper simples da função de relatório (interno)
void relatorio_wrapper () 
{
    BUFFERS_LOCAIS (b, 1, 512);

    erro_handler_write_chars (relatorio_da_memoria (&b[0], (erro_handler_modo () == 1)));
}

// Gera o relatório
char* relatorio_da_memoria (Buffer* out, bool cores)
{
    ERRO_SE_NULO (out);

    size_t at = 0, lt = 0, ab = 0, lb = 0;

    bool modo = Buffer_status (&at, &lt, &ab, &lb);

    if (modo == 1)
    {
        BUFFERS_LOCAIS (b, 6, 256);

        BUFFER_UNIR  
        (
            *out,
            (cores)?(((at - lt)> 5)?("\033[31m"):(((at - lt) != 0)?("\033[33m"):("\033[32m"))):"",
            "\n\tEstado da Memória",
            "\n\tAlocações feitas: ", parse (&b[0], at     ), " (", parse (&b[3], ab     ), " bytes)",
            "\n\tLimpezas  feitas: ", parse (&b[1],      lt), " (", parse (&b[4],      lb), " bytes)",
            "\n\tLixo: "            , parse (&b[2], at - lt), " (", parse (&b[5], ab - lb), " bytes)",
            "\n\n\n", (cores)?"\033[0m":""
        );
    }
    else ERRO_SE ("Relatório sendo impresso no modo de Buffer errado", 1);

    return out->dados;
}

// Inicializador
static void __attribute__((constructor)) relatorio_construtor (void)
{
    registrar_destrutor_gerbic (relatorio_wrapper, 500);
}

// Acorda o módulo 
void RELATORIO_ACORDAR () {DESTRUTOR_HANDLER_ACORDAR ();}

//////////////////////////////////////////////////////////////////////
