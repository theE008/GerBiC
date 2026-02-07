//////////////////////////////////////////////////////////////////////
// destrutor_handler
//
// Criador: Thiago Pereira de Oliveira
// Início:  04/02/2026
// Versão:  0.1.0
// Status:  Em desenvolvimento
//
// Descrição: Executa funções no final do programa na ordem escolhida.
// Algo precisa ser registrado, se não, as barras não aparecem.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers Padrão

#ifndef DESTRUTOR_HANDLER_H
#define DESTRUTOR_HANDLER_H

//////////////////////////////////////////////////////////////////////
// Headers Próprios



//////////////////////////////////////////////////////////////////////
// Definições

// O modo padrão tem as barras
#ifndef DESTRUTOR_HANDLER_MODE 
    #define DESTRUTOR_HANDLER_MODE 1
#endif 

//////////////////////////////////////////////////////////////////////
// Valores

// Função destrutora
// bool: serve para saber se está no terminal ou não 
// se não estiver, a função se comporta diferente
typedef void (*funcao_destrutora_gerbic)(void);

// Guarda a hierarquia das funcoes 
typedef struct destrutor_gerbic
{
    double prioridade;
    funcao_destrutora_gerbic fn;
} 
destrutor_gerbic;

//////////////////////////////////////////////////////////////////////
// Funções

// Registra um finalizador de programa 
void registrar_destrutor_gerbic (funcao_destrutora_gerbic fn, double prioridade);

// Acorda o handler se necessário
void DESTRUTOR_HANDLER_ACORDAR ();

/////////////////////////////////////////////////////////////////////

#endif
