//////////////////////////////////////////////////////////////////////
// erro_handler.h
//
// Criador:	Thiago Pereira de Oliveira (theE008)
// Início: 	01/2026
// Versão: 	0.2.0
// Status: 	Em desenvolvimento
//
// Descrição: Cria um sistema de erros unificado, onde o usuário pode
// alterar com um #define todo o esquema de erros da biblioteca.
//
// Vão existir três modos de segurança:
//
// 1. Seguro: Este modo é mais voltado para desenvolvimento.
// No modo seguro, todo e qualquer erro é enviado para o terminal e 
// interrompe o fluxo do programa, não deixando chegar a um estado 
// mais severo. 
//
// 2. Catalogado: Este modo é mais voltado para uso de programas
// que ainda não são totalmente confiáveis.
// Este modo ainda faz todas as verificações de erro, mas apenas as 
// anota em um arquivo de log, garantindo que o programa continue 
// rodando, mesmo que com risco de segmentation fault.
// Ideal para ter um app que tenta continuar executando a qualquer 
// custo, e ainda ter uma lista de coisas a se voltar a atenção 
// posteriormente. 
//
// 3. Livre: Este modo é mais voltado para uso rápido.
// Todas as verificações de segurança são removidas completamente.
// O programa ficará mais rápido, porém em caso de segmentation fault,
// nada será registrado.
//
// Modificado para não tratar mais início e fim do programa [destrutor_handler]
// E para as macros terem seus nomes em caixa alta.
//   
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers

#ifndef ERRO_HANDLER_H
#define ERRO_HANDLER_H

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// # include "modules.h"

// Headers próprios 
/* 
#ifdef TEM_(biblioteca) // Incluir biblioteca apenas se ela existir
#include (biblioteca)
#endif
*/

// Qualquer outro Header importante
#include <stddef.h> // Para NULL

//////////////////////////////////////////////////////////////////////
// Variáveis


//////////////////////////////////////////////////////////////////////
// Funções

// Lança textos no local junto com os erros para decorar/informar 
// melhor.
void erro_handler_write_chars
(
    const char* txt 
);

// Lança o erro desejado 
void erro_handler
(
    const char* arq,
    const char* func,
    const char* msg,
    int ln,
    int tst
);

//////////////////////////////////////////////////////////////////////
// Definições

// O modo padrão é o mais seguro
#ifndef ERRO_HANDLER_MODE
    #define ERRO_HANDLER_MODE 1
#endif

// Definição padrão (mensagem de erro se teste for true)
#if ERRO_HANDLER_MODE != 3
    #define ERRO_SE(msg,tst) \
        erro_handler (__FILE__, __func__, msg, __LINE__, tst) 
#else
    #define ERRO_SE(msg,tst) ((void) 0)
#endif

// Uso mais específico, para padronização
#define ERRO_SE_NULO(ptr) \
    erro_handler (__FILE__, __func__, "Erro: Ponteiro nulo. '" #ptr "'", __LINE__, ptr == NULL) 

// Retorna o modo do handler 
int erro_handler_modo ();

//////////////////////////////////////////////////////////////////////

#endif

