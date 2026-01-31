//////////////////////////////////////////////////////////////////////
// Headers

// Header Próprio
#include "memoria_verificador.h"

// Outros Headers 
#include "erro_handler.h"

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// #include "modules.h"

// Outros Headers
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

// Essas variáveis não tá definida no header. 
// O usuário não tem acesso 
static int alocacoes = 0;
static int limpezas  = 0;

//////////////////////////////////////////////////////////////////////
// Funções

// Imprime o estado da memória se o usuário permitir
#if MEMORIA_VERIFICADOR_MODE == 1
    static void __attribute__((destructor)) memoria_verificador_destructor (void)
    {
        int lixo = alocacoes - limpezas;

        printf
        (
             "\n\t%sEstado da Memória"
             "\n\tAlocações feitas: %d"
             "\n\tLimpezas  feitas: %d"
             "\n\tLixo: %d\n\n\n\033[0m",
             (lixo > 5)? "\033[31m": (lixo != 0)? "\033[33m": "\033[32m", 
             alocacoes, limpezas, lixo
        );
    }
#endif 

// Garante que a memória tenha sido alocada antes de retornar
void* malocar (size_t tam)
{
    void* ptr = malloc (tam);

    erro_se ("Memória não alocada", ptr == NULL);
    
    #if MEMORIA_VERIFICADOR_MODE == 1
        alocacoes ++;
    #endif 

    return ptr;
}

// Função de limpeza 
void memoria_verificador_limpar(void *ptr)
{
    if (ptr)
    {
        free(ptr);

        #if MEMORIA_VERIFICADOR_MODE == 1
            limpezas++;
        #endif
    }
}


//////////////////////////////////////////////////////////////////////
