//////////////////////////////////////////////////////////////////////
// arquivo_handler.h
//
// Criador:	Thiago Pereira de Oliveira (theE008)
// Início: 	01/2026
// Versão: 	0.1.0
// Status: 	Em desenvolvimento
//
// Descrição: Uma simples biblioteca geral para cuidar de arquivos.
//   
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers

#ifndef ARQUIVO_HANDLER_H
#define ARQUIVO_HANDLER_H

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// # include "modules.h"

// Headers próprios 
#include "erro_handler.h"

/* 
#ifdef TEM_(biblioteca) // Incluir biblioteca apenas se ela existir
#include (biblioteca)
#endif
*/

// Qualquer outro Header importante
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Copia um arquivo para outro lugar 
void copiar_arquivo (const char* path_origem, const char* path_destino);

// Cria um diretório 
bool criar_diretorio (const char* path);

//////////////////////////////////////////////////////////////////////
// Definições

// Transforma a abertura e fechamento de arquivos em blocos
// Para garantir que o usuário não vai simplesmente esquecer
// Estilo Python.
#define usar_arquivo(path,nome,modo) \
       for \
       ( \
            FILE* nome = fopen (path, modo); \
            nome != NULL; \
            fclose (nome), nome = NULL \
        ) // Não é lindo?

//////////////////////////////////////////////////////////////////////

#endif
