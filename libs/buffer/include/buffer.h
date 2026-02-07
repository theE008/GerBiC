//////////////////////////////////////////////////////////////////////
// buffer
//
// Criador: Thiago Pereira de Oliveira
// Início:  03/02/2026
// Versão:  0.1.0
// Status:  Em desenvolvimento
//
// Descrição: Trata o uso da memória no geral usando Buffers.
// Funciona tanto para memória alocada quanto para memória local.
// Segurança é a motivação desse módulo.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers Padrão

#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h> // size_t
#include <stdint.h> // uint8_t
#include <stdbool.h> // bool
                    
//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "erro_handler.h"

//////////////////////////////////////////////////////////////////////
// Definições

// Se o modo de buffer não tiver sido definido 
#ifndef BUFFER_MODE
    #define BUFFER_MODE 1 // Ativa o modo de verificação 
#endif 

// Cria um buffer ali mesmo 
#define BUFFERS_LOCAIS(nome,qnts,tam) \
    uint8_t buffer_de_dados_##nome [qnts][tam] = {0}; /* inicia zerado */ \
    Buffer nome [qnts]; \
    for (size_t b_x_##nome = 0; b_x_##nome < (qnts); b_x_##nome++) \
        nome [b_x_##nome] = (Buffer) \
        { \
            .dados = buffer_de_dados_##nome [b_x_##nome], \
            .tamanho = (tam), \
            .alocado = false, \
        }

// Pega uma posição. Pode ser lida ou escrita
#define BUFFER_ACESSAR(bfr,tipo,offset) \
    ({ \
        Buffer *__b = &(bfr); \
        size_t __os = offset; \
        ERRO_SE_NULO (__b->dados); \
        ERRO_SE ("Acesso fora do Buffer", (__os) + sizeof(tipo) > __b->tamanho); \
        (tipo*)((uint8_t*)__b->dados + (__os)); \
    })[0]

// Wrapper do limpar
#define BUFFER_LIMPAR(bfr) \
        Buffer_limparInterno (&bfr) 

// Cria um buffer de uso único. NÃO GUARDE! EXTREMAMENTE VOLÁTIL [morre no fim da própria linha]
#define BFR_TMP(tam) \
    ((Buffer){ .dados = (uint8_t[tam]){0}, .tamanho = tam })

//////////////////////////////////////////////////////////////////////
// Valores

// Definição do tipo buffer 
typedef struct Buffer 
{
    uint8_t* dados;
    size_t tamanho;
    bool alocado;
}
Buffer;

//////////////////////////////////////////////////////////////////////
// Funções

// Aloca um buffer dinâmicamente [estilo malocar]
// zerado só define se calloc será usado
Buffer Buffer_dinamico (const size_t tam, bool zerado);

// Semelhante ao limpar [free], só que para Buffers (não usar)
void Buffer_limparInterno (Buffer* b);

// O sistema de imprimir os valores no final não iria funcionar bem 
// Ele precisa de concatenação, que precisa de buffers 
// Para evitar dependências circulares, resolvi só deixar o acesso 
// aqui.
// Retorna true se o modo do Buffer for o de verificação.
bool Buffer_status (size_t* at, size_t* lt, size_t* ab, size_t* lb);

// Realoca a memória do buffer 
Buffer Buffer_realocar (Buffer* bfr, const size_t tam);

//////////////////////////////////////////////////////////////////////

#endif
