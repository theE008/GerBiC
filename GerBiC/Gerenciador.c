//////////////////////////////////////////////////////////////////////
// Gerenciador de Bibliotecas em C 
//
// Projeto iniciado em Janeiro de 2026 
// Por Thiago Pereira de Oliveira 
//
// COMANDOS:
//
// ./Gerenciador <biblioteca>
// Se a biblioteca não existe, cria e abre seus arquivos.
// Se ela já existe, só abre ela.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers do C 

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Headers da Biblioteca 

#include "concatenar_em_buffer.h"
#include "capitalizacao_ascii.h"
#include "copiar_em_buffer.h"
#include "arquivo_handler.h"
#include "erro_handler.h"

//////////////////////////////////////////////////////////////////////
// Definições 

#define LIBS "libs"         // Arquivo ./lib 
#define BUILD "build"       // Arquivo ./build 
#define SRC "src"           // Arquivo ./src

#define CRIADOR "Thiago Pereira de Oliveira"
#define BARRA \
"///////////////////////////////////" \
"///////////////////////////////////\n"

//////////////////////////////////////////////////////////////////////
// Main 

int main (int argc, char* argv [])
{
    // Garante dois argumentos 
    if (argc != 2)
    {
        printf ("\nUso: %s <nome do projeto>\n", argv[0]);
        
        erro_se ("Quantia de inputs não condizente", 1);
    }

    // Pega a data certa
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    int dia = t->tm_mday;
    int mes = t->tm_mon + 1;
    int ano = t->tm_year + 1900;
    printf ("Data: %02d/%02d/%04d\n", dia, mes, ano);

    // Pega o ponteiro do nome
    const char* nome = argv [1];
    printf ("Diretório: %s\n", nome);

    // Faz uma cópia maiúscula
    char nome_maiusculo [256];
    copiar_em_buffer (nome_maiusculo, 256, nome);
    para_maiusculas (nome_maiusculo);
    printf ("CapsLock: %s\n", nome_maiusculo);

    // Verifica se o diretório 'libs' existe 
    const char libs_path [5] = LIBS; // Irei usar pra debug
    bool nao_primeira_run = criar_diretorio (libs_path);
    printf ("Primeira Run? %s\n", (!nao_primeira_run)?"Sim":"Não"); 

    // Se os arquivos do projeto ainda não existem
    if (!nao_primeira_run)
    {
        // Copia o arquivo cmake no diretório do projeto 
        const char cmake_dir [64] = "GerBiC/CMake_dir.txt";
        copiar_arquivo (cmake_dir, "CMakeLists.txt");
        printf ("Criando o CMake do diretório...\n");

        // Cria o build
        const char build_path [6] = BUILD;
        criar_diretorio (build_path);
        printf ("Criando o build...\n");

        // Cria o src 
        const char source_path [4] = SRC;
        bool existe = criar_diretorio (source_path);
        printf ("Criando o source...\n");

        // Cria o path do main 
        char main_c [256];
        concatenar_em_buffer (main_c, 256, source_path, "/main.c");
        printf ("Path do main: %s\n", main_c);

        // Escreve no main 
        if (!existe) usar_arquivo (main_c, m, "wt")
        {
            fprintf (m, BARRA "// %s\n//\n", nome);
            fprintf (m, "// Criador: " CRIADOR "\n");
            fprintf (m, "// Início:  %02d/%02d/%04d\n", dia, mes, ano);
            fprintf (m, "// Versão:  0.1.0\n");
            fprintf (m, "// Status:  Em desenvolvimento\n//\n");
            fprintf (m, "// Descrição: \n//\n");
            fprintf (m, BARRA "\n");
            fprintf (m, BARRA "// Headers Padrão\n\n\n\n");
            fprintf (m, BARRA "// Headers Próprios\n\n\n\n");
            fprintf (m, BARRA "// Definições\n\n\n\n");
            fprintf (m, BARRA "// Valores\n\n\n\n");
            fprintf (m, BARRA "// Funções\n\n\n\n");
            fprintf (m, BARRA "// Main\n\n\n\n" BARRA);
            fprintf 
            (
                m, 
                "// Comandos \n\n/** COMANDOS DO CMAKE \n\n// Geral \nclear &&"
                " cmake <suas flags> .. && make && ./bin/<nome do diretório atu"
                "al>\n\n// Release \nclear && cmake -DCMAKE_BUILD_TYPE=Release"
                "<suas flags> .. \\n&& make -j$(nproc)\n\n*/"
            );

        }

        // Abre no neovim 
        system ("nvim -O src/main.c");

        // Finaliza, já que o resto é desnecessário 
        return 0;
    }

    // Escolhe um path com 'nome' em libs_path 
    char biblioteca_path [256];
    concatenar_em_buffer (biblioteca_path, 256, libs_path, "/");
    concatenar_em_buffer (biblioteca_path, 256, biblioteca_path, nome);
    printf ("Path da Biblioteca: %s\n", biblioteca_path);

    // Cria o diretório da bibliote"ca e vê se já existe 
    bool ja_existe = criar_diretorio (biblioteca_path);
    printf ("Biblioteca já existe? %s\n", (ja_existe)?"Sim":"Não");

    // Fazer o path para copiar o CMake na biblioteca. 
    const char cmake_lib [64] = "GerBiC/CMake_lib.txt";
    char cmake_lib_path [256];
    concatenar_em_buffer (cmake_lib_path, 256, biblioteca_path, "/CMakeLists.txt");
    printf ("Path do CMake da biblioteca: %s\n", cmake_lib_path);
    
    // Criar o path diretório include/
    char biblioteca_include_path [256];
    concatenar_em_buffer (biblioteca_include_path, 256, biblioteca_path, "/include");
    printf ("Path do include: %s\n", biblioteca_include_path);

    // Cria o path para o header
    char biblioteca_header [256];
    concatenar_em_buffer (biblioteca_header, 256, biblioteca_include_path, "/");
    concatenar_em_buffer (biblioteca_header, 256, biblioteca_header, nome);
    concatenar_em_buffer (biblioteca_header, 256, biblioteca_header, ".h");
    printf ("Path do header: %s\n", biblioteca_header);

    // Cria o path do src/ 
    char biblioteca_src_path [256];
    concatenar_em_buffer (biblioteca_src_path, 256, biblioteca_path, "/src");
    printf ("Path do source: %s\n", biblioteca_src_path);

    // Path do C 
    char biblioteca_c [256];
    concatenar_em_buffer (biblioteca_c, 256, biblioteca_src_path, "/lib.c");
    printf ("Path do C: %s\n", biblioteca_c);

    // Se ainda não existe, o projeto é feito.
    if (!ja_existe)
    {
        printf ("Criando biblioteca...\n");

        // Copiando em si 
        copiar_arquivo (cmake_lib, cmake_lib_path);
        printf ("CMake copiado!\n");

        // Cria o diretório do include/
        criar_diretorio (biblioteca_include_path);
        printf ("Criando include...\n");

        // Cria o diretório do src/ 
        criar_diretorio (biblioteca_src_path);
        printf ("Criando source...\n");

        // Escreve o header 
        usar_arquivo (biblioteca_header, h, "wt")
        {
            fprintf (h, BARRA "// %s\n//\n", nome);
            fprintf (h, "// Criador: " CRIADOR "\n");
            fprintf (h, "// Início:  %02d/%02d/%04d\n", dia, mes, ano);
            fprintf (h, "// Versão:  0.1.0\n");
            fprintf (h, "// Status:  Em desenvolvimento\n//\n");
            fprintf (h, "// Descrição: \n//\n");
            fprintf (h, BARRA "\n");
            fprintf (h, BARRA "// Headers Padrão\n\n");
            fprintf (h, "#ifndef %s_H\n#define %s_H\n\n",
                    nome_maiusculo, nome_maiusculo);
            fprintf (h, BARRA "// Headers Próprios\n\n\n\n");
            fprintf (h, BARRA "// Definições\n\n\n\n");
            fprintf (h, BARRA "// Valores\n\n\n\n");
            fprintf (h, BARRA "// Funções\n\n\n\n");
            fprintf (h, BARRA "\n#endif");
        }
        printf ("Escrevendo no header...\n");

        // Escrever no C 
        usar_arquivo (biblioteca_c, c, "wt")
        {
            fprintf (c, BARRA "// Headers Padrão\n\n\n\n");
            fprintf (c, BARRA "// Headers Próprios\n\n\n\n");
            fprintf (c, BARRA "// Definições\n\n\n\n");
            fprintf (c, BARRA "// Valores\n\n\n\n");
            fprintf (c, BARRA "// Funções\n\n\n\n");
            fprintf (c, BARRA);
           
        }
        printf ("Escrevendo no C...\n");
    }

    // Finalmente, abrir o projeto
    char nvim [256];
    concatenar_em_buffer (nvim, 256, "nvim -O ", biblioteca_header);
    concatenar_em_buffer (nvim, 256, nvim, " ");
    concatenar_em_buffer (nvim, 256, nvim, biblioteca_c);
    concatenar_em_buffer (nvim, 256, nvim, " ");
    concatenar_em_buffer (nvim, 256, nvim, cmake_lib_path);
    printf ("Comando de execução: %s\n", nvim);

    // Abrindo o NeoVim
    system (nvim);

    return 0;
}

//////////////////////////////////////////////////////////////////////
// Comandos 

/** COMANDOS DO CMAKE 

// Geral 
clear && cmake <suas flags> .. && make && ./bin/<nome do diretório atual>

// Release 
clear && cmake -DCMAKE_BUILD_TYPE=Release <suas flags> .. \
&& make -j$(nproc)

*/

/** COMANDOS DE COMPILAÇÃO ÚTEIS E RÁPIDOS

// Normal 
clear && cmake -DERRO_HANDLER_MODE=1 .. && make && ./bin/GerBiC

// Log 
clear && cmake -DERRO_HANDLER_MODE=2 .. && make && ./bin/GerBiC

// Livre 
clear && cmake -DERRO_HANDLER_MODE=3 .. && make && ./bin/GerBiC

// Release (Livre)
clear && cmake -DCMAKE_BUILD_TYPE=Release -DERRO_HANDLER_MODE=3 .. \
&& make -j$(nproc)

*/
////////////////////////////////////////////////////////////////////// 
