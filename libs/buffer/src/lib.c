//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stddef.h> // size_t
#include <stdint.h> // uint8_t
#include <stdbool.h> // boola
#include <stdlib.h> // malloc

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "buffer.h"

#include "erro_handler.h"

//////////////////////////////////////////////////////////////////////
// Definições



//////////////////////////////////////////////////////////////////////
// Valores

// Apenas guarda os valores alocados 
// Valores locais não importam tanto
#if BUFFER_MODE == 1
    size_t alocacoes = 0;
    size_t limpezas  = 0;

    size_t al_bytes  = 0;
    size_t lp_bytes  = 0;
#endif 

//////////////////////////////////////////////////////////////////////
// Funções

// Aloca um buffer dinâmicamente [estilo malocar]
Buffer Buffer_dinamico (const size_t tam, bool zerado)
{
    ERRO_SE ("Tamanho inválido", tam == 0);

    uint8_t* mem = (zerado)?(uint8_t*) calloc (1, tam):malloc (tam);
    ERRO_SE_NULO (mem);

    #if BUFFER_MODE == 1
        alocacoes ++;
        al_bytes += tam;
    #endif 

    return (Buffer){
        .dados = mem,
        .tamanho = tam,
        .alocado = true
    };
}

// Realoca a memória do buffer 
Buffer Buffer_realocar (Buffer* bfr, const size_t tam)
{
    ERRO_SE_NULO (bfr);
    ERRO_SE_NULO (bfr->dados);
    ERRO_SE ("Tamanho inválido", tam == 0);

    void* ptr = realloc (bfr->dados, tam);
    ERRO_SE_NULO (ptr);

    bfr->dados = ptr;

    #if BUFFER_MODE == 1 // Talvez somar um malloc e a memória em vez?
        al_bytes -= bfr->tamanho;
        al_bytes += tam;
    #endif

    // Limpa a memória extra, se existir
    for (size_t x = bfr->tamanho; x < tam; x++)
        bfr->dados [x] = 0;

    bfr->tamanho = tam;

    return *bfr;
}

// Semelhante ao limpar, só que para Buffers 
void Buffer_limparInterno (Buffer* b) 
{
    ERRO_SE_NULO (b);
    ERRO_SE ("Limpeza de Buffer local", !b->alocado);

    free (b->dados);

    #if BUFFER_MODE == 1
        limpezas += 1;
        lp_bytes += b->tamanho;
    #endif 

    b->dados = NULL;
    b->alocado = false;
    b->tamanho = 0;
}

// O sistema de imprimir os valores no final não iria funcionar bem 
// Ele precisa de concatenação, que precisa de buffers 
// Para evitar dependências circulares, resolvi só deixar o acesso 
// aqui.
// Retorna true se o modo do Buffer for o de verificação.
bool Buffer_status (size_t* at, size_t* lt, size_t* ab, size_t* lb)
{
    ERRO_SE_NULO (at);
    ERRO_SE_NULO (lt);
    ERRO_SE_NULO (ab);
    ERRO_SE_NULO (lb);

    *at = 0; *lt = 0; *ab = 0; *lb = 0;

    #if BUFFER_MODE == 1
        *at = alocacoes;
        *ab = al_bytes;

        *lt = limpezas;
        *lb = lp_bytes;
    #endif 

    return BUFFER_MODE == 1;
}

//////////////////////////////////////////////////////////////////////
