cmake_minimum_required(VERSION 3.18)

######################################################################
# IDENTIFICAÇÃO DA BIBLIOTECA
#
# O nome da biblioteca é o nome da pasta atual
######################################################################

get_filename_component(LIB_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
string(REPLACE " " "_" LIB_NAME "${LIB_NAME}")

######################################################################
# ARQUIVOS-FONTE
#
# Coleta automática de todos os .c em src/
######################################################################

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
    src/*.c
)

######################################################################
# CRIAÇÃO DO TARGET
#
# Biblioteca estática (.a)
######################################################################

add_library(${LIB_NAME} STATIC)
target_sources(${LIB_NAME} PRIVATE ${LIB_SOURCES})

######################################################################
# INCLUDES DA BIBLIOTECA
#
# PUBLIC:
# - Headers que fazem parte da API
#
# PRIVATE:
# - Headers internos (se existirem)
######################################################################

target_include_directories(${LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

######################################################################
# DEPENDÊNCIAS DE OUTRAS BIBLIOTECAS DO PROJETO
#
# Use PRIVATE para evitar vazamento de dependências
######################################################################

# target_link_libraries(${LIB_NAME}
#     PRIVATE
#         outra_lib
# )

######################################################################
# PARÂMETROS DE COMPILAÇÃO (ARGUMENTOS DA LIB)
#
# Permite configurar comportamento via linha de comando:
#
#   cmake -Dlog_MODE=2 ..
######################################################################

string(TOUPPER "${LIB_NAME}" LIB_NAME_UPPER)

set(${LIB_NAME_UPPER}_MODE "" CACHE STRING
    "Modo de operação da biblioteca ${LIB_NAME}")

if(NOT "${${LIB_NAME_UPPER}_MODE}" STREQUAL "")
    target_compile_definitions(${LIB_NAME}
        PRIVATE ${LIB_NAME_UPPER}_MODE=${${LIB_NAME_UPPER}_MODE}
    )
endif()


######################################################################
# HEADERS GERADOS PELO PROJETO
#
# Necessário para:
#   #include "modules.h"
######################################################################

target_include_directories(${LIB_NAME}
    PRIVATE
        "${CMAKE_BINARY_DIR}/generated"
)

######################################################################
# SUB-BIBLIOTECAS PRIVADAS DA BIBLIOTECA
#
# Permite que esta biblioteca tenha suas próprias dependências internas,
# isoladas do projeto principal.
#
# Estrutura esperada:
#
#   libs/<esta_lib>/libs/<sub_lib>/
#
# Cada sub-lib:
# - tem a mesma estrutura de uma biblioteca normal
# - pode ter suas próprias sub-libs (recursivo)
#
# IMPORTANTE:
# - Essas bibliotecas NÃO ficam visíveis para o projeto principal
# - Elas são linkadas como PRIVATE
######################################################################

set(LOCAL_LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

if(EXISTS "${LOCAL_LIBS_DIR}")

    # Descobre todas as sub-bibliotecas locais
    file(GLOB LOCAL_LIB_DIRS
         RELATIVE "${LOCAL_LIBS_DIR}"
         "${LOCAL_LIBS_DIR}/*")

    set(LOCAL_LIB_TARGETS "")

    foreach(local_lib ${LOCAL_LIB_DIRS})
        if(IS_DIRECTORY "${LOCAL_LIBS_DIR}/${local_lib}")

            # Adiciona a sub-lib ao build
            add_subdirectory("libs/${local_lib}")

            # Guarda o nome do target (nome da pasta)
            list(APPEND LOCAL_LIB_TARGETS ${local_lib})

        endif()
    endforeach()

    # Linka TODAS as sub-libs como dependências privadas
    if(LOCAL_LIB_TARGETS)
        target_link_libraries(${LIB_NAME}
            PRIVATE
                ${LOCAL_LIB_TARGETS}
        )
    endif()

endif()

######################################################################
# FIM DA CONFIGURAÇÃO DA BIBLIOTECA
######################################################################

