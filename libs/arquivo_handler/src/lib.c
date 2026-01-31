//////////////////////////////////////////////////////////////////////
// Headers

// Header Próprio
#include "arquivo_handler.h"

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// #include "modules.h"

// Headers de Outros módulos
#include "erro_handler.h"

// Outros Headers
#include <sys/stat.h> // Para criação de diretórios
#include <stdio.h>
#include <errno.h> // Para saber porque criar o diretório falhou

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Copia um arquivo para outro lugar 
void copiar_arquivo (const char* path_origem, const char* path_destino)
{
    usar_arquivo (path_origem, origem, "rb")
    {
        usar_arquivo (path_destino, destino, "wb")
        {
            char buffer [4096] = "\0";   
            size_t quantos = 0;

            for (;(quantos = fread (buffer, 1, sizeof buffer, origem)) > 0;)
                erro_se 
                (
                    "Erro na escrita", 
                    fwrite (buffer, 1, quantos, destino) != quantos
                );
        }

        erro_se ("Erro na leitura", ferror (origem));
    }
}

// Cria um diretório (retorna true se já existia) 
bool criar_diretorio (const char* path) 
{
    int ret = mkdir(path, 0755);

    erro_se(
        "Erro na criação do diretório",
        ret && errno != EEXIST
    );

    return ret && errno == EEXIST;
}

//////////////////////////////////////////////////////////////////////
