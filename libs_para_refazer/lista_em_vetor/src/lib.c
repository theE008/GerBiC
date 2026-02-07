//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stdint.h>
#include <stddef.h>

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "lista_em_vetor.h"

#include "erro_handler.h"

//////////////////////////////////////////////////////////////////////
// Definições



//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Apenas cria um struct com os elementos passados
lista_vet lista_em_vetor_criar (uint8_t* buffer, size_t tam_max, size_t tam_elem)
{
    erro_se_nulo(buffer);
    erro_se("Tamanho de elemento inválido", tam_elem == 0);

    lista_vet tmp;
    tmp.buffer = buffer;
    tmp.tam_max = tam_max;
    tmp.tam_elem = tam_elem;
    tmp.x = 0;

    return tmp;
}

// Copia um elemento byte a byte
static void copiar_elem (uint8_t* dst, const uint8_t* src, size_t tam)
{
    for (size_t b = 0; b < tam; b++)
    dst[b] = src[b];
}

// Desloca elementos para a direita (usado em insert)
static void deslocar_direita 
(
    uint8_t* buffer,
    size_t inicio,
    size_t fim,
    size_t tam
)
{
    for (size_t i = fim; i > inicio; i--)
    {
        size_t dst = i * tam;
        size_t src = (i - 1) * tam;
        copiar_elem(buffer + dst, buffer + src, tam);
    }
}

// Desloca elementos para a esquerda (usado em remove)
static void deslocar_esquerda 
(
    uint8_t* buffer,
    size_t inicio,
    size_t fim,
    size_t tam
)
{
    for (size_t i = inicio; i < fim; i++)
    {
        size_t dst = i * tam;
        size_t src = (i + 1) * tam;
        copiar_elem(buffer + dst, buffer + src, tam);
    }
}

// Adiciona um elemento em uma posição
void lista_em_vetor_insert (lista_vet* l, const void* elem, size_t pos)
{
    erro_se_nulo(l);

    erro_se("Lista cheia", l->x >= l->tam_max);
    erro_se("Posição inválida", pos > l->x);

    deslocar_direita(l->buffer, pos, l->x, l->tam_elem);

    copiar_elem
    (
        l->buffer + (pos * l->tam_elem),
        (const uint8_t*) elem,
        l->tam_elem
    );

    l->x++;
}

// Pega um elemento
void lista_em_vetor_get (lista_vet* l, size_t pos, void* out)
{
    erro_se_nulo(l);
    erro_se_nulo(out);

    erro_se("Lista vazia", l->x == 0);
    erro_se("Posição inválida", pos >= l->x);

    copiar_elem
    (
        (uint8_t*) out,
        l->buffer + (pos * l->tam_elem),
        l->tam_elem
    );
}

// Modifica um elemento
void lista_em_vetor_set (lista_vet* l, size_t pos, const void* elem)
{
    erro_se_nulo(l);
    erro_se_nulo(elem);

    erro_se("Lista vazia", l->x == 0);
    erro_se("Posição inválida", pos >= l->x);

    copiar_elem
    (
        l->buffer + (pos * l->tam_elem),
        (const uint8_t*) elem,
        l->tam_elem
    );
}

// Remove um elemento
void lista_em_vetor_remove (lista_vet* l, size_t pos, void* out)
{
    erro_se_nulo(l);
    erro_se_nulo(out);

    erro_se("Lista vazia", l->x == 0);
    erro_se("Posição inválida", pos >= l->x);

    // Copia o elemento removido
    lista_em_vetor_get(l, pos, out);

    // Desloca os elementos à esquerda
    deslocar_esquerda(l->buffer, pos, l->x - 1, l->tam_elem);

    l->x--;
}

// Coloca um elemento no fim 
void lista_em_vetor_push (lista_vet* l, const void* elem)
{
    erro_se_nulo (l);
    erro_se_nulo (elem);

    lista_em_vetor_insert (l, elem, l->x);
}

// Remove um elemento no fim 
void lista_em_vetor_pop (lista_vet* l, void* out)
{
    erro_se_nulo (l);
    erro_se_nulo (out);

    erro_se("Lista vazia", l->x == 0);

    lista_em_vetor_remove (l, l->x - 1, out);
}
   
// Remove um elemento no início
void lista_em_vetor_pop_start (lista_vet* l, void* out)
{
    erro_se_nulo (l);
    erro_se_nulo (out);

    erro_se("Lista vazia", l->x == 0);
    
    lista_em_vetor_remove (l, 0, out);
}

// Retorna o elemento do topo sem o remover 
void lista_em_vetor_peek (lista_vet* l, void* out)
{
    erro_se_nulo (l);
    erro_se_nulo (out);

    erro_se("Lista vazia", l->x == 0);

    lista_em_vetor_get (l, l->x - 1, out);
}

// Retorna o elemento do início sem o remover 
void lista_em_vetor_peek_start (lista_vet* l, void* out)
{
    erro_se_nulo (l);
    erro_se_nulo (out);

    erro_se("Lista vazia", l->x == 0);

    lista_em_vetor_get (l, 0, out);
}

// Retorna a quantia sendo usada
int lista_em_vetor_uso (lista_vet* l)
{
    erro_se_nulo (l);

    return l->x;
}

// Retorna se está vazia 
bool lista_em_vetor_estah_vazia (lista_vet* l)
{
    erro_se_nulo (l);

    return l->x == 0;
}

// Retorna uma lista como um wrapper
pilha_vet pilha_em_vetor_criar
(
    uint8_t* buffer,
    size_t tam_max,
    size_t tam_elem
)
{
    return lista_em_vetor_criar(buffer, tam_max, tam_elem);
}

// Coloca um elemento no fim 
void pilha_em_vetor_push (pilha_vet* l, const void* elem)
{
    lista_em_vetor_push (l, elem);
}

// Remove um elemento no fim 
void pilha_em_vetor_pop (pilha_vet* l, void* out)
{
    lista_em_vetor_pop (l, out);
}

// Retorna o elemento do topo sem o remover 
void pilha_em_vetor_peek (pilha_vet* l, void* out)
{
    lista_em_vetor_peek (l, out);
}

// Retorna a quantia sendo usada
int pilha_em_vetor_uso (pilha_vet* l)
{
    return lista_em_vetor_uso (l);
}

// Retorna se está vazia 
bool pilha_em_vetor_estah_vazia (pilha_vet* l)
{
    return lista_em_vetor_estah_vazia (l);
}

// Retorna uma lista como um wrapper
fila_vet fila_em_vetor_criar
(
    uint8_t* buffer,
    size_t tam_max,
    size_t tam_elem
)
{
    return lista_em_vetor_criar(buffer, tam_max, tam_elem);
}

// Coloca um elemento no fim 
void fila_em_vetor_push (fila_vet* l, const void* elem)
{
    lista_em_vetor_push (l, elem);
}

// Remove um elemento no início 
void fila_em_vetor_pop (fila_vet* l, void* out)
{
    lista_em_vetor_pop_start (l, out);
}

// Retorna o elemento do início sem o remover 
void fila_em_vetor_peek (fila_vet* l, void* out)
{
    lista_em_vetor_peek_start (l, out);
}

// Retorna a quantia sendo usada
int fila_em_vetor_uso (fila_vet* l)
{
    return lista_em_vetor_uso (l);
}

// Retorna se está vazia 
bool fila_em_vetor_estah_vazia (fila_vet* l)
{
    return lista_em_vetor_estah_vazia (l);
}

//////////////////////////////////////////////////////////////////////
