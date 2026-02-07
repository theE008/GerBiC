//////////////////////////////////////////////////////////////////////
// Headers Padrão



//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "destrutor_handler.h"

#include "erro_handler.h"

//////////////////////////////////////////////////////////////////////
// Definições

#define MAX_DESTRUTORES 64
static destrutor_gerbic lista [MAX_DESTRUTORES];
static size_t usados = 0;

//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Apenas termina o programa com a barra 
// É melhor deixar isso aqui mesmo, e não em erro_handler 
// Para evitar dependência circular
void erro_handler_destructor ()
{
    erro_handler_write_chars 
    (
        "\n// PROGRAMA FINALIZADO\n"
        "//////////////////////////////////////////////////////////////////////\n\n"
    );
}

// Apenas coloca uma barra na tela ou no log indicando que o programa iniciou 
#if DESTRUTOR_HANDLER_MODE == 1
    static void __attribute__((constructor)) erro_handler_constructor (void)
    {
        erro_handler_write_chars
        (
            "\n//////////////////////////////////////////////////////////////////////\n"
            "// PROGRAMA INICIADO\n\n"
        );
        
        registrar_destrutor_gerbic (erro_handler_destructor, 1000);
    }
#endif

// Função da biblioteca 
static void ordenar_destrutores(void)
{
    for (size_t i = 0; i + 1 < usados; i++)
    {
        for (size_t j = i + 1; j < usados; j++)
        {
            if (lista[j].prioridade < lista[i].prioridade)
            {
                destrutor_gerbic tmp = lista[i];
                lista[i] = lista[j];
                lista[j] = tmp;
            }
        }
    }
}

// Destrutor real do programa
static void __attribute__((destructor)) GERBIC_DESTRUCTOR (void)
{
    ordenar_destrutores ();

    for (size_t i = 0; i < usados; i++)
        lista[i].fn();
}

// Registra um finalizador de programa 
void registrar_destrutor_gerbic (funcao_destrutora_gerbic fn, double prioridade)
{
    ERRO_SE_NULO (fn);
    ERRO_SE ("Máximo de funções destrutoras já registrados", usados >= MAX_DESTRUTORES);

    lista[usados++] = (destrutor_gerbic){
        .prioridade = prioridade,
        .fn = fn
    };
}

// Acorda o handler se necessário
void DESTRUTOR_HANDLER_ACORDAR (){}

//////////////////////////////////////////////////////////////////////
