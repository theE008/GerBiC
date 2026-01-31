//////////////////////////////////////////////////////////////////////
// Headers

// Header Próprio
#include "concatenar_em_buffer.h"

// Isso é usado para que a biblioteca enxergue as outras (se necessário)
// #include "modules.h"

// Headers de Outros módulos
#include "tamanho_chars.h"
#include "erro_handler.h"

// Outros Headers
#include <stddef.h>

//////////////////////////////////////////////////////////////////////
// Variáveis

//////////////////////////////////////////////////////////////////////
// Funções

// Função principal da biblioteca 
size_t concatenar_em_buffer (char* destino, size_t max, const char* a, const char* b)
{
    erro_se_nulo (a);
    erro_se_nulo (b);

    size_t tam_a = tamanho_chars (a);
    size_t tam_b = tamanho_chars (b);
    
    erro_se ("Destino menor que fontes", tam_a + tam_b >= max);

    for (size_t x = 0; x < tam_a; x++) destino [x] = a [x];
    for (size_t y = 0; y < tam_b; y++) destino [y + tam_a] = b [y];

    destino [tam_a + tam_b] = '\0';

    return tam_a + tam_b;
}
    
//////////////////////////////////////////////////////////////////////
