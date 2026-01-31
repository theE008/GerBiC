//////////////////////////////////////////////////////////////////////
// erro_terminal.h
//
// Criador:	Thiago Pereira de Oliveira (theE008)
// Início: 	01/2026
// Versão: 	0.1.0
// Status: 	Em desenvolvimento
//
// Descrição: Dá uma mensagem de erro padrão no terminal
//   
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers

#ifndef ERRO_TERMINAL_H
#define ERRO_TERMINAL_H

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// # include "modules.h"

// Headers próprios 
/* 
#ifdef TEM_(biblioteca) // Incluir biblioteca apenas se ela existir
#include (biblioteca)
#endif
*/

// Qualquer outro Header importante

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Esqueleto da função em si
void erro_terminal 
(
    const char *arq,
    const char *func,
    const char *msg,
    int ln
);

//////////////////////////////////////////////////////////////////////
// Definições 

// Para permitir uma chamada mais fácil
#define Erro_terminal(msg) \
    erro_terminal (__FILE__, __func__, (msg), __LINE__)

//////////////////////////////////////////////////////////////////////

#endif
