//////////////////////////////////////////////////////////////////////
// erro_log.h
//
// Criador:	Thiago Pereira de Oliveira (theE008)
// Início: 	01/2026
// Versão: 	0.1.0
// Status: 	Em desenvolvimento
//
// Descrição:
//   
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers

#ifndef ERRO_LOG_H
#define ERRO_LOG_H

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

// Escreve texto no arquivo log 
void erro_log_write_chars 
(
    const char* log_arq, 
    const char* msg 
);

// Escreve o erro no final do log
void erro_log 
(
    const char* log_arq,
    const char* arq,
    const char* func, 
    const char* msg,
    int ln 
);
     
//////////////////////////////////////////////////////////////////////
// Definições 

// Define o caminho padrão, o usuário pode redefinir
#ifndef ERRO_LOG_ARQUIVO_PADRAO
    #define ERRO_LOG_ARQUIVO_PADRAO "../erro_log.txt"
#endif

// Deixa a chamada da função mais fácil 
#define Erro_log(msg) \
    erro_log (ERRO_LOG_ARQUIVO_PADRAO, __FILE__, __func__, msg, __LINE__)

//////////////////////////////////////////////////////////////////////

#endif
