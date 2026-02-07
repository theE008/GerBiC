//////////////////////////////////////////////////////////////////////
// Gerenciador
//
// Criador: Thiago Pereira de Oliveira
// Início:  03/02/2026
// Versão:  0.3.0
// Status:  Em desenvolvimento
//
// Descrição: Um gerenciador geral de bibliotecas, reconstruido.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "destrutor_handler.h"
#include "buffer.h"
#include "buffer_concatenar.h"
#include "relatorio.h"
#include "arquivo_handler.h"
#include "capitalizacao_ascii.h"
#include "compararTexto.h"
#include "erro_handler.h"
#include "size_t_paraTexto.h"
#include "tamanhoTexto.h"
#include "substituirTexto.h"
#include "acharTexto.h"
#include "buffer_input.h"

//////////////////////////////////////////////////////////////////////
// Definições

// Escrita 
#define HELPHLPER(cmparer) /* Ajuda a diminuir o texto no ajuda */ \
    if (!compararTexto (com_oque, cmparer) || help) {usado = true; printf (cmparer##H);}

#define RUNHELPER(cmd) /* Ajuda a descobrir a flag*/ \
    if ((!compararTexto (argv [1], cmd)) && ++usado)

#define STEP(dsc,repl) /* Escreve uma descrição do que está fazendo*/ \
    printf ("\n[%2d] \033[1m%s\033[0m %s\n", __COUNTER__, dsc, repl)

// Comandos possíveis 
#define BIB     "-bib"      // Cria ou abre uma biblioteca
#define BGN     "-start"    // Inicia o projeto
#define GIT     "-git"      // Commita (mensagem padrão se nenhuma)
#define CMP     "-comp"     // Compila o main usando o cmake 
#define CMD     "-cmdline"  // Abre o Gerenciador como commandline
#define SLF     "-self"     // Abre o próprio projeto 
#define SLC     "-selfc"    // Compila o próprio projeto 
#define GET     "-get"      // Baixa uma biblioteca do github
#define ABT     "-about"    // Imprime informação geral sobre mim 
#define HLP     "-help"     // Imprime ajuda sobre tudo ou comando individual
#define VER     "-version"  // Imprime a versão 
#define USO     ""          // Vazio, para padronizar
#define SYS     "-sys"      // Roda um comando no terminal

// Informações do Gerenciador 
#define VERSION "0.3.0" 
#define CREATOR "Thiago Pereira de Oliveira (theE008)"
#define DESCRPT "\n\tGerenciador de Bibliotecas em C (GerBiC): " \
                "\n\tUm projeto individual para o uso de C"
#define GITMAIL "144809113+theE008@users.noreply.github.com" 
#define ISSUERS "https://github.com/theE008/GerBiC/issues"

// Ordenador de informações
#define VERP    DESCRPT "\n\tVersão " VERSION "\n"
#define ABTP    "\n\tCopyright (C) " CREATOR \
                "\n\tReporte problemas em: " GITMAIL \
                "\n\tOu em: "ISSUERS "\n"

// Ajuda 
#define USOH    "\n\tUso: %s -<flag> <argumento>" \
                "\n\tPara mais ajuda, use: %s " HLP "\n", \
                programa, programa
#define VERH    "\n\t" VER ": Diz a versão do %s\n", programa
#define ABTH    "\n\t" ABT ": Diz informação sobre o projeto e seu criador\n"
#define BIBH    "\n\t" BIB ": Cria ou abre um módulo" \
                "\n\tUso: " BIB " <nome do módulo> ou <mód. pai.>.<módulo filho>" \
                "\n\tNota: Apenas o nome de UM módulo depois de " BIB "\n"
#define BGNH    "\n\t" BGN ": Inicia um projeto no local"\
                "\n\t(Argumentos serão escritos no header como nome - decorativo)\n"
#define GITH    "\n\t" GIT ": Faz um commit" \
                "\n\t(Argumentos serão usados de mensagem)\n"
#define SLFH    "\n\t" SLF ": Abre o projeto em C do %s\n", programa
#define SLCH    "\n\t" SLC ": Temporariamente substitui o projeto main.c para "\
                "compilar o %s\n", programa
#define GETH    "\n\t" GET ": Baixa o módulo escolhido do github do %s" \
                "\n\tUso: " GET " <nome do módulo> " \
                "ou <mód. pai>.<módulo filho> \n", programa 
#define CMPH    "\n\t" CMP ": Compila seu projeto usando o CMake" \
                "\n\t(Argumentos serão usados de flags)\n"
#define CMDH    "\n\t" CMD ": Inicia o %s como uma command line" \
                "\n\t(as flags são os comandos, use ctrl+C para sair)\n", \
                programa
#define SYSH    "\n\t" SYS ": Executa um comando fora do " CMD "\n"

// Erros 
#define HPNF    "\n\tO comando que você quer aprender não foi encontrado!" USOH
#define RNNF    "\n\tO comando que você quer rodar não foi encontrado!" USOH

// Textos de uso do programa 
#define T_LNCHR "nvim -O" // O editor de código usado
#define T_LNCH2 "nvim -p" // Para duas janelas diferentes
#define T_LIBFL "libs/" // Pasta de módulos
#define T_BUILD "build/" // Pasta da build 
#define T_INCLD "include/" // Pasta do header dos módulos
#define T_SOURC "src/" // Pasta do source
#define T_MAINS T_SOURC "main.c" // Main                       
#define T_TMPRE ".tmp_repo" // Pasta temporária do git
#define T_SYSTM "GerBiC/" // Pasta do sistema 
#define T_SELFN "Gerenciador.c" // Nome desse arquivo aqui
#define T_MNCMK T_SYSTM "CMake_dir.txt" // CMake do sistema 
#define T_MDCMK T_SYSTM "CMake_lib.txt" // CMake dos módulos
#define T_GCLN1 "git clone --filter=blob:none --sparse " \
                "https://github.com/theE008/GerBiC.git " T_TMPRE\
                " && cd " T_TMPRE " && " \
                "git sparse-checkout set " 
#define T_GCLN2 " && cp -r " T_LIBFL "* ../" T_LIBFL " && " \
                "cd .. && rm -rf " T_TMPRE 
#define T_STRCM /*Não usa &&, se der erro, não executa*/\
                "cp " T_MNCMK " ./CMakeLists.txt"
#define T_STRC2 "cp " T_MDCMK " "
#define BARRA \
"//////////////////////////////////////////////////////////////////////"
#define T_HEADR BARRA \
                  "\n// %s" \
                  "\n//" \
                  "\n// Criador: " CREATOR \
                  "\n// Início:  %02d/%02d/%04d" \
                  "\n// Versão:  0.1.0" \
                  "\n// Status:  Em desenvolvimento" \
                  "\n//" \
                  "\n// Descrição: " \
                  "\n//\n" \
                BARRA "\n\n"
#define T_CRPO \
                BARRA "\n// Headers Padrão \n\n%s\n\n" \
                BARRA "\n// Headers Próprios \n\n%s\n\n" \
                BARRA "\n// Definições \n\n\n\n" \
                BARRA "\n// Valores \n\n\n\n" \
                BARRA "\n// Funções \n%s\n" \
                BARRA "%s"

// Escreve isso no final do main para mostrar o usuário quais
// Comandos ele pode usar do Gerenciador 
#define COMANDOS ""

//////////////////////////////////////////////////////////////////////
// Valores


//////////////////////////////////////////////////////////////////////
// Funções

// Função central de ajuda 
void f_ajuda (const char* programa, const char* com_oque)
{
    ERRO_SE_NULO (com_oque);
    ERRO_SE_NULO (programa);
    bool help = false;
    bool usado = false;
    
    // Caso o usuário escreva '-help', imprime todas as entradas
    if (!compararTexto (com_oque, HLP)) 
    { 
        help = true;
        printf (VERP ABTP);
    }

    // "switch case"
    HELPHLPER (USO); // Como usar o código
    HELPHLPER (VER); // Descrição, Versão
    HELPHLPER (ABT); // Sobre, email, link do git
    HELPHLPER (BGN); // Iniciar projeto 
    HELPHLPER (BIB); // Iniciar módulo
    HELPHLPER (GIT);
    HELPHLPER (SLF);
    HELPHLPER (SLC);
    HELPHLPER (GET);
    HELPHLPER (CMP);
    HELPHLPER (CMD);
    HELPHLPER (SYS);

    // Finalização (Erro e \n)
    if (!usado) printf (HPNF);
    printf ("\n");
}

//////////////////////////////////////////////////////////////////////
// Main

int main (int argc, char * argv [])
{
    // Definição de programa
    char* programa = argv [0];

    // Se o usuário só der um argumento, exibe ajuda 
    if (argc == 1) f_ajuda (programa, "");
    // Se ele der dois ou mais argumentos 
    else 
    {
        // Caso o usuário passar uma flag errada 
        int usado = false; 

        // E o segundo argumento for ajuda 
        RUNHELPER (HLP)
            f_ajuda (programa, (argc > 2)?argv[2]:HLP); // Passa o argumento extra se tiver

        // About 
        RUNHELPER (ABT) printf (ABTP);

        // Version 
        RUNHELPER (VER) printf (VERP);

        //////////////////////////////////////////////////////////////
        // Comandos em si 
        
        // Pega a data certa
        time_t agora = time(NULL);
        struct tm *t = localtime(&agora);
        int dia = t->tm_mday;
        int mes = t->tm_mon + 1;
        int ano = t->tm_year + 1900;

        // Inicia o projeto 
        RUNHELPER (BGN)
        {
            // Inicia CMake
            STEP ("Iniciando CMake Principal:", T_STRCM);
            system (T_STRCM);

            // Iniciando os diretórios 
            criar_diretorio (T_LIBFL);
            criar_diretorio (T_BUILD);
            bool ja_existe = criar_diretorio (T_SOURC);
            STEP ("Criando aquivos...", "");
            STEP (T_SOURC " já existe?", (ja_existe)?"Sim":"Não");

            // Escreve o main se o source foi criado
            if (!ja_existe) USAR_ARQUIVO (T_MAINS, fmain, "wf")
            {
                BUFFERS_LOCAIS (b, 1, 256);

                for (int x = 2; x < argc; x++)
                    BUFFER_UNIR (b [0], b[0].dados, argv [x], " ");

                STEP ("Escrevendo no " T_MAINS "...","");
                fprintf 
                (
                    fmain, 
                    T_HEADR T_CRPO,
                    b [0].dados,
                    dia, mes, ano,
                    "", "", "\n\n", // #ifndef | #include | \n\n
                    COMANDOS
                );
            }
           
            // Abre no editor
            STEP ("Abrindo no editor de texto...", "");
            system (T_LNCHR " " T_MAINS);
        }

        // Inicia um módulo 
        RUNHELPER (BIB)
        {
            // Ensina como usa o BIB caso passe mais que ./ger -bib nome 
            if (argc > 3) f_ajuda (programa, BIB);
            else 
            {
                // Passa os pontos para bib 
                BUFFERS_LOCAIS (b, 5, 1024);
                BUFFER_UNIR (b [0], T_LIBFL, argv [2]);
                substituirTexto (&b [0], ".", "/libs/");
                STEP ("Caminho do módulo:", b [0].dados);

                // Cria o libs se necessário
                Buffer_concatenar (&b [1], b [0].dados, "");
                size_t pos = acharUltimoTexto (b [1].dados, "/libs/", b [1].tamanho);
                BUFFER_ACESSAR (b [1], char, pos + tamanhoTexto ("/libs/")) = '\0';
                STEP ("Caminho do módulo pai:", b [1].dados);
                bool existe2 = criar_diretorio (b[1].dados);

                // Verifica se o módulo existe 
                // PELA NATUREZA DO ERRO HANDLER, PODE DAR ERRO 
                // SILENCIOSO SE NÃO INCLUIR O MODO 1 E DAR UM PATH INVÁLIDO
                bool existe = criar_diretorio (b [0].dados);
                STEP ("Existe?", (!existe || !existe2)?"Não":"Sim");

                if (!existe2 || !existe) // Cria/copia os três arquivos
                {
                    // Inicia CMake
                    BUFFER_UNIR (b [2], T_STRC2, b [0].dados, "/CMakeLists.txt");
                    STEP ("Iniciando CMake Modular:", b [2].dados);
                    system (b [2].dados);

                    // Cria os diretórios 
                    BUFFER_UNIR (b [3], b [0].dados, "/", T_SOURC);
                    criar_diretorio (b [3].dados);
                    STEP ("Path do diretório de source:", b [3].dados);
                    BUFFER_UNIR (b [4], b [0].dados, "/", T_INCLD);
                    criar_diretorio (b [4].dados);
                    STEP ("Path do diretório de header:", b[4].dados);

                    const char* modulo = (acharUltimoTexto (b [0].dados, "/", -1) + b [0].dados) + 1;
                    char* MODULO = CAT_TMP (modulo);
                    para_maiusculas (MODULO);

                    // Cria o lib.c
                    USAR_ARQUIVO (Buffer_concatenar (&BFR_TMP (256), b [3].dados, "lib.c"), libc, "wt")
                    {
                        fprintf 
                        (
                            libc, 
                            T_CRPO,
                            "", CAT_TMP ("#include \"", modulo, ".h\""), "\n\n", // #ifndef | #include | \n\n
                            ""
                        );
                    }

                    // Cria o header 
                    USAR_ARQUIVO 
                    (
                        BUFFER_UNIR (BFR_TMP (256), b[4].dados, 
                        (modulo), ".h"),
                        hder,
                        "wt"
                    )
                    {
                        fprintf 
                        (
                            hder, 
                            T_HEADR T_CRPO,
                            modulo,
                            dia, mes, ano,
                            CAT_TMP ("#ifndef ", MODULO, "_H\n#define ", MODULO, "_H"),
                            "", "", // #ifndef | #include | \n\n
                            "\n\n#endif"
                        );
                    }
                }

                BUFFERS_LOCAIS (b_2, 1, 1024);

                BUFFER_UNIR 
                (
                    b_2 [0],
                    b [0].dados, "/", T_INCLD, "* ",
                    b [0].dados, "/", "CMakeLists.txt ",
                    "-c \"tabfirst | vsplit ",
                    b [0].dados, "/", T_SOURC, "lib.c", // Para todos (um) arquivos
                    "\""
                );

                STEP ("Abrindo no editor de texto:", b_2 [0].dados);
                system (CAT_TMP (T_LNCH2 " ", b_2 [0].dados));
            }
        }

        // Commita o projeto 
        RUNHELPER (GIT) 
        {
            BUFFERS_LOCAIS (b, 1, 1024);

            // Pega argumentos de um a um
            if (argc == 2) BUFFER_UNIR (b [0], "Commit padrão da GerBiC");
            else
            for (int x = 2; x < argc; x++) BUFFER_UNIR (b [0], b [0].dados, " ", argv [x]);

            system 
            (
                CAT_TMP 
                (
                    "git add . && " 
                    "git commit -m \"",
                    b [0].dados, 
                    "\" &&"
                    "git push origin main"
                )
            );
        }

        // Abre esse arquivo no editor 
        RUNHELPER (SLF)
        {
            system (CAT_TMP (T_LNCHR, " ", T_SYSTM, T_SELFN)); // Clean
        }

        // Compila a si mesmo 
        RUNHELPER (SLC)
        {
            // Primeiro, salva o main original
            copiar_arquivo (T_MAINS, T_SOURC "backup.c");

            // Então, copia o compilador no src 
            copiar_arquivo (CAT_TMP (T_SYSTM, T_SELFN), T_SOURC "main.c"); 

            // Então, compila 
            system ("cd " T_BUILD " && cmake .. && make");

            // E aí move tudo de volta
            // [mantém backup [escolha de design seguro? preguiça? quem sabe!]]
            copiar_arquivo (T_SOURC "backup.c", T_MAINS);

            // Talvez depois, passar o compilado pro diretório certo
            system (
                "PROJ_NOME=$(basename $(pwd)) && " // Aqui ele pega "GerBiC" (raiz do projeto)
                "cp \"build/bin/$PROJ_NOME\" \"GerBiC/GerenciadorBuild\""
            );
        }

        // Compila e roda
        RUNHELPER (CMP)
        {
            BUFFERS_LOCAIS (b, 1, 1024);

            // Pega argumentos de um a um
            for (int x = 2; x < argc; x++) BUFFER_UNIR (b [0], b [0].dados, " ", argv [x]);

            system (CAT_TMP ("cd " T_BUILD " && cmake ", b [0].dados, " .. && make && ./bin/*"));
        }

        // Cmdline 
        RUNHELPER (CMD)
        {
            // Roda os argumentos um a um antes
            for (int x = 2; x < argc; x++) system (CAT_TMP (programa, " ", argv [x]));

            for (;;) // Loop eterno
            {
                printf ("GerBiC> "); 
                system (CAT_TMP (programa, " -", SCN_TMP (0)));
            }
        }

        // Anti-cmdline
        RUNHELPER (SYS)
        {
            // Pega argumentos de um a um
            BUFFERS_LOCAIS (b, 1, 1024);
            for (int x = 2; x < argc; x++) BUFFER_UNIR (b [0], b [0].dados, " ", argv [x]);

            system (b [0].dados);
        }

        // Baixar módulo do git
        RUNHELPER (GET)
        {
            BUFFERS_LOCAIS (b, 3, 1024);

            // Transforma os argumentos em módulos 
            for (int x = 2; x < argc; x++)
            {
                // Transformar '.' -> '/libs/' 
                Buffer_concatenar (&b [2], argv [x], "");
                substituirTexto (&b[2], ".", "/libs/");
                
                // Concatena todas as bibliotecas 
                BUFFER_UNIR (b [1], b [1].dados, T_LIBFL, b [2].dados, " ");
            }

            // Comando de acesso
            BUFFER_UNIR 
            (
                b [0],
                T_GCLN1,
                b [1].dados, // Módulos
                T_GCLN2
            );

            // Mostra e usa o comando
            STEP ("Instalando os módulos:", b[0].dados);
            system (b[0].dados);
        }

        // Fim dos comandos em si 
        //////////////////////////////////////////////////////////////

        // Exibe erro se não existir comando
        if (!usado) printf (RNNF);
        printf ("\n");
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////
// Comandos 

/** COMANDOS DO CMAKE 

// Geral 
clear && cmake <suas flags> .. && make && ./bin/<nome do diretório atual>

// Release 
clear && cmake -DCMAKE_BUILD_TYPE=Release<suas flags> .. \n&& make -j$(nproc)

*/
