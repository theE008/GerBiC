//////////////////////////////////////////////////////////////////////
// concatenar_em_buffer.h
//
// Criador:	Thiago Pereira de Oliveira (theE008)
// Início: 	01/2026
// Versão: 	0.2.0
// Status: 	Em desenvolvimento
//
// Descrição: Junta duas strings em um buffer simples. 
// Para evitar complexidade.
//   
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers

#ifndef CONCATENAR_EM_BUFFER_H
#define CONCATENAR_EM_BUFFER_H

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// # include "modules.h"

// Headers próprios 
/* 
#ifdef TEM_(biblioteca) // Incluir biblioteca apenas se ela existir
#include (biblioteca)
#endif
*/

// Qualquer outro Header importante
#include <stddef.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Função principal da biblioteca 
size_t concatenar_em_buffer (char* destino, size_t max, const char* a, const char* b);

// Função recursiva
size_t concatenar_em_buffer_recursivamente (char* destino, size_t max, ...);

//////////////////////////////////////////////////////////////////////
// Definições

// Deixa concatenar no geral bem mais fácil
#define concatenar_rec(destino,max,...) \
    concatenar_em_buffer_recursivamente (destino, max, __VA_ARGS__, NULL)

//////////////////////////////////////////////////////////////////////

#endif
