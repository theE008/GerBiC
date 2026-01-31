//////////////////////////////////////////////////////////////////////
// memoria_verificador.h
//
// Criador:	Thiago Pereira de Oliveira (theE008)
// Início: 	01/2026
// Versão: 	0.1.0
// Status: 	Em desenvolvimento
//
// Descrição: Garante que a memória foi corretamente alocada.
// Também conta a quantia de elementos alocados (se permitido).
// Pela natureza simples da função, só funciona com a erro_handler.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers

#ifndef MEMORIA_VERIFICADOR_H
#define MEMORIA_VERIFICADOR_H

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// # include "modules.h"

// Headers próprios 
/* 
#ifdef TEM_(biblioteca) // Incluir biblioteca apenas se ela existir
#include (biblioteca)
#endif
*/

// Qualquer outro Header importante
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções 

// Garante que a memória tenha sido alocada antes de retornar
void* malocar (size_t tam);

// Limpa a memória (Use o limpar(ptr) por preferência)
void memoria_verificador_limpar (void* ptr);

//////////////////////////////////////////////////////////////////////
// Definições

// Garantir que automaticamente, tenha verificação de memória. 
#ifndef MEMORIA_VERIFICADOR_MODE 
    #define MEMORIA_VERIFICADOR_MODE 1 
#endif

// Redefine o limpar para não precisar de ponteiro 
#define limpar(ptr) \
    do \
    { \
        memoria_verificador_limpar(ptr); \
        (ptr) = NULL; \
    } while (0)

//////////////////////////////////////////////////////////////////////

#endif
