//////////////////////////////////////////////////////////////////////
// lista_em_vetor
//
// Criador: Thiago Pereira de Oliveira
// Início:  01/02/2026
// Versão:  0.1.0
// Status:  Em desenvolvimento
//
// Descrição: Cria uma lista/pilha/fila em vetor.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Headers Padrão

#ifndef LISTA_EM_VETOR_H
#define LISTA_EM_VETOR_H

#include <stdint.h>
#include <stddef.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios



//////////////////////////////////////////////////////////////////////
// Definições

// Define a lista sem forçar o usuário a definir um buffer
// USE COM CAUTELA! 
#define nova_lista_em_vetor(nome,tam,tipo) \
    uint8_t buffer_##nome##_##__COUNTER__ [tam * sizeof (tipo)]; \
    lista_vet nome = lista_em_vetor_criar \
    ( \
        buffer_##nome##_##__COUNTER__, \
        tam, \
        sizeof (tipo) \
    )

// Para pilha
#define nova_pilha_em_vetor(nome,tam,tipo) \
    uint8_t buffer_##nome##_##__COUNTER__ [tam * sizeof (tipo)]; \
    pilha_vet nome = pilha_em_vetor_criar \
    ( \
        buffer_##nome##_##__COUNTER__, \
        tam, \
        sizeof (tipo) \
    )

// Para fila 
#define nova_fila_em_vetor(nome,tam,tipo) \
    uint8_t buffer_##nome##_##__COUNTER__ [tam * sizeof (tipo)]; \
    pilha_vet nome = fila_em_vetor_criar \
    ( \
        buffer_##nome##_##__COUNTER__, \
        tam, \
        sizeof (tipo) \
    )

//////////////////////////////////////////////////////////////////////
// Valores

// Definição do tipo lista_vet
typedef struct lista_vet 
{
    uint8_t* buffer; // Onde os elementos são guardados
    size_t tam_max;  // Quantia máxima de elementos em buffer
    size_t tam_elem; // Tamanho de um elemento individual
    size_t x;        // Elemento atual na lista
}
lista_vet;

// Definindo a pilha como uma lista 
typedef lista_vet pilha_vet;

// Definindo a fila como uma lista também
typedef lista_vet fila_vet;

//////////////////////////////////////////////////////////////////////
// Funções

/// LISTA 

// Apenas cria um struct com os elementos passados
lista_vet lista_em_vetor_criar (uint8_t* buffer, size_t tam_max, size_t tam_elem);

// Adiciona um elemento em uma posição
void lista_em_vetor_insert (lista_vet* l, const void* elem, size_t pos);

// Pega um elemento
void lista_em_vetor_get (lista_vet* l, size_t pos, void* out);

// Modifica um elemento
void lista_em_vetor_set (lista_vet* l, size_t pos, const void* elem);

// Remove um elemento
void lista_em_vetor_remove (lista_vet* l, size_t pos, void* out);

// Coloca um elemento no fim 
void lista_em_vetor_push (lista_vet* l, const void* elem);

// Remove um elemento no fim 
void lista_em_vetor_pop (lista_vet* l, void* out);

// Remove um elemento no início
void lista_em_vetor_pop_start (lista_vet* l, void* out);

// Retorna o elemento do topo sem o remover 
void lista_em_vetor_peek (lista_vet* l, void* out);

// Retorna o elemento do início sem o remover 
void lista_em_vetor_peek_start (lista_vet* l, void* out);

// Retorna a quantia sendo usada
int lista_em_vetor_uso (lista_vet* l);

// Retorna se está vazia 
bool lista_em_vetor_estah_vazia (lista_vet* l);


/// PILHA  

// Retorna uma lista como um wrapper
pilha_vet pilha_em_vetor_criar
(
    uint8_t* buffer,
    size_t tam_max,
    size_t tam_elem
);

// Coloca um elemento no fim 
void pilha_em_vetor_push (pilha_vet* l, const void* elem);

// Remove um elemento no fim 
void pilha_em_vetor_pop (pilha_vet* l, void* out);

// Retorna o elemento do topo sem o remover 
void pilha_em_vetor_peek (pilha_vet* l, void* out);

// Retorna a quantia sendo usada
int pilha_em_vetor_uso (pilha_vet* l);

// Retorna se está vazia 
bool pilha_em_vetor_estah_vazia (pilha_vet* l);

/// FILA

// Retorna uma lista como um wrapper
fila_vet fila_em_vetor_criar
(
    uint8_t* buffer,
    size_t tam_max,
    size_t tam_elem
);

// Coloca um elemento no fim 
void fila_em_vetor_push (fila_vet* l, const void* elem);

// Remove um elemento no início 
void fila_em_vetor_pop (fila_vet* l, void* out);

// Retorna o elemento do início sem o remover 
void fila_em_vetor_peek (fila_vet* l, void* out);

// Retorna a quantia sendo usada
int fila_em_vetor_uso (fila_vet* l);

// Retorna se está vazia 
bool fila_em_vetor_estah_vazia (fila_vet* l);

//////////////////////////////////////////////////////////////////////

#endif
