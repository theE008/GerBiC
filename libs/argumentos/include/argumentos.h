//////////////////////////////////////////////////////////////////////
// argumentos
//
// Criador: Thiago Pereira de Oliveira
// Início:  04/02/2026
// Versão:  0.1.0
// Status:  Em desenvolvimento
//
// Descrição: 
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers Padrão

#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios



//////////////////////////////////////////////////////////////////////
// Definições

// Cria um escopo seguro e fácil de usar para lidar com va_args
// Chama va_end naturalmente
#define ARGUMENTOS(ultimo_fixo) \
    for (struct { va_list principal; va_list copia; bool ativa; } __va = { .ativa = true }; \
         __va.ativa; \
         (va_end(__va.principal), va_end(__va.copia), __va.ativa = false)) \
        for (va_start(__va.principal, ultimo_fixo), va_copy(__va.copia, __va.principal); \
             __va.ativa; \
             __va.ativa = false)

// Extrai o proximo valor da lista de argumentos
#define RECEBER_ARG(tipo) \
    ({ \
        _Static_assert(sizeof(tipo) >= sizeof(int) || (uintptr_t)#tipo == 0, \
            "SEGURANCA: Tipos menores que 'int' (char, short) sao promovidos. Use 'int' no RECEBER_ARG."); \
        va_arg(__va.principal, tipo); \
    })

// Pega o priximo valor da lista de argumentos clonada 
// Pode ser útil para saber o tamanho exato antes de mallocs
#define RECEBER_ARG_COPIA(tipo) \
    ({ \
        _Static_assert(sizeof(tipo) >= sizeof(int) || (uintptr_t)#tipo == 0, \
            "SEGURANCA: Tipos menores que 'int' sao promovidos. Use 'int' no RECEBER_ARG."); \
        va_arg(__va.copia, tipo); \
    })

//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções



//////////////////////////////////////////////////////////////////////

#endif
