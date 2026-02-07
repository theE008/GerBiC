//////////////////////////////////////////////////////////////////////
// Headers Padrão

#include <stddef.h>
#include <limits.h> //int_min

//////////////////////////////////////////////////////////////////////
// Headers Próprios

#include "int_para_chars.h"

#include "erro_handler.h"
#include "concatenar_em_buffer.h"
#include "copiar_em_buffer.h"
#include "inverter_chars.h"

//////////////////////////////////////////////////////////////////////
// Definições



//////////////////////////////////////////////////////////////////////
// Valores



//////////////////////////////////////////////////////////////////////
// Funções

// Passa um valor inteiro para um valor chars 
char* int_para_chars (char* buffer, size_t max, int val)
{
    erro_se_nulo (buffer);
    erro_se ("Buffer muito pequeno", max < 2); // O menor valor tem um dígito e um \0
    erro_se ("int_para_chars não suporta INT_MIN", val == INT_MIN);

    buffer [0] = '\0'; // Zera o buffer 
    bool negativo = false;

    if (val == 0) copiar_em_buffer (buffer, 2, "0");
    else if (val < 0) 
    {
        negativo = true; // O sinal tem que ser o último adicionado

        val = -val; // Trabalha com positivos
                    // Pode quebrar com o INT_MIN, mas fazer o que.
                    // Não se pode ganhar todas
    }

    while (val)
    {
        char D[2] = "0";
        D[0] += (val % 10);
        concatenar_em_buffer(buffer, max, buffer, D);

        val /= 10;
    }

    // Adiciona o sinal se necessário
    if (negativo) concatenar_em_buffer (buffer, max, buffer, "-");

    // E inverte tudo 
    inverter_chars (buffer);

    return buffer;
}

//////////////////////////////////////////////////////////////////////

