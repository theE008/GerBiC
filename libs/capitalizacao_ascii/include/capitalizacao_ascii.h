//////////////////////////////////////////////////////////////////////
// capitalizacao_ascii.h
//
// Criador:	Thiago Pereira de Oliveira (theE008)
// Início: 	01/2026
// Versão: 	0.1.0
// Status: 	Em desenvolvimento
//
// Descrição: Serve para EXPLICITAMENTE trabalhar capitalização de 
// ASCII.
//   
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers

#ifndef CAPITALIZACAO_ASCII_H
#define CAPITALIZACAO_ASCII_H

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// # include "modules.h"

// Headers próprios 
/* 
#ifdef TEM_(biblioteca) // Incluir biblioteca apenas se ela existir
#include (biblioteca)
#endif
*/

// Qualquer outro Header importante
#include <stdbool.h> 

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Verifica se é maiúscula
bool eh_maiuscula (char carac);

// Verifica se é minúscula
bool eh_minuscula (char carac);

// Passa para maiúscula se necessário 
char para_maiuscula (char c);

// Passa para minúscula se necessário
char para_minuscula (char c);

// Passa todo o texto para maiúsculas 
void para_maiusculas (char* str);

// Passa todo o texto para minúsculas
void para_minusculas (char* str);

//////////////////////////////////////////////////////////////////////
// Definições

//////////////////////////////////////////////////////////////////////

#endif
