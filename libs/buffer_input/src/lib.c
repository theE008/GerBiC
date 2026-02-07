//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "buffer_input.h"

#include "buffer.h"
#include "erro_handler.h"
#include "tamanhoTexto.h"

//////////////////////////////////////////////////////////////////////
// Definições



//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Recebe o input de um arquivo ou do terminal 
char* Buffer_input (Buffer* bfr, FILE* fonte, uint8_t tratamento)
{
    ERRO_SE_NULO (bfr);
    bfr->dados [0] = '\0'; // Só pra garantir
    bool conseguiu = fgets (bfr->dados, bfr->tamanho, fonte);
    size_t tam = tamanhoTexto (bfr->dados);
    if (tam > 0 && BUFFER_ACESSAR(*bfr, char, tam - 1) == '\n')
            BUFFER_ACESSAR(*bfr, char, tam - 1) = '\0';

    // Política sobre erro de leitura 
    if (!conseguiu)
    {
        // Segurança total: Erro quando há erro
        ERRO_SE ("Erro na leitura", tratamento == 0);

        // Tampa os dados caso o erro ocorrer mas a segurança 
        // Não precisar ser tão alta
        BUFFER_ACESSAR(*bfr, char, 0) = '\0';
    }
    
    // Se o buffer encheu (provavelmente leftovers)
    if (tam == bfr->tamanho - 1)
    {
        // Segurança alta: Não permite leftovers
        ERRO_SE ("Buffer estourado", tratamento == 1);

        // Segurança média: apaga leftovers
        if (tratamento <= 2)
        {
            int c = 0;
            while ((c = fgetc(fonte)) != '\n' && c != EOF);
        }

        // Segurança baixa (tratamento = 3): Não tratado
    }

    return bfr->dados;
}

//////////////////////////////////////////////////////////////////////
