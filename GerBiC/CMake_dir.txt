# Informação Importante:
# 
# Gerei esse CMakeLists com o ChatGPT.
# Aprender CMake não é o meu objetivo com essa biblioteca,
# mesmo que ter um bom CMake seja essencial para ter uma 
# boa biblioteca, e esse é o objetivo - criar uma biblioteca
# própria bem usável para qualquer coisa em C. 

cmake_minimum_required(VERSION 3.18)

######################################################################
# PROJECT SETUP
#
# Aqui definimos o projeto de forma dinâmica:
# - O nome do projeto será o nome da pasta atual
# - Espaços no nome são convertidos para _
# - A linguagem usada é C
#
# Isso permite reutilizar este CMakeLists.txt em vários projetos
# sem precisar editar o nome manualmente.
######################################################################

# Pega o nome da pasta atual (ex: my_project)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Substitui espaços por "_" para evitar problemas com targets
string(REPLACE " " "_" ProjectId ${ProjectId})

# Define o projeto
project(${ProjectId} LANGUAGES C)

######################################################################
# OUTPUT DIRECTORIES
#
# Centraliza todos os artefatos de build:
# - bibliotecas estáticas (.a)
# - bibliotecas dinâmicas (.so)
# - executáveis
#
# Tudo fica organizado dentro da pasta build/
######################################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

######################################################################
# AUTOMATION START
#
# Esta seção automatiza completamente:
# - Descoberta de bibliotecas em /libs
# - Includes compartilhados
# - Defines automáticos
# - Geração de um header global (modules.h)
#
# A ideia é: adicionar uma pasta em libs/ e pronto.
######################################################################

######################################################################
# 1. DISCOVER LIBRARY DIRECTORIES
#
# Lista tudo que existe dentro de /libs
# O resultado é uma lista de nomes relativos (não caminhos absolutos)
#
# Exemplo:
# libs/
#   log/
#   math/
#   net/
#
# Resultado: log;math;net
######################################################################

file(GLOB LIB_DIRS
     RELATIVE "${PROJECT_SOURCE_DIR}/libs"
     "${PROJECT_SOURCE_DIR}/libs/*")

######################################################################
# LISTAS AUXILIARES
#
# ALL_LIBS:
#   - nomes dos targets (assumindo que cada lib cria um target
#     com o mesmo nome da pasta)
#
# ALL_INCLUDES:
#   - todos os diretórios include/ encontrados
#
# MODULE_DEFINES:
#   - defines do tipo TEM_LOG, TEM_MATH, etc
######################################################################

set(ALL_LIBS "")
set(ALL_INCLUDES "")
set(MODULE_DEFINES "")

######################################################################
# 2. PROCESS EACH LIBRARY DIRECTORY
#
# Loop por cada item encontrado em libs/
# Verificamos se é realmente um diretório
# e coletamos informações úteis.
######################################################################

foreach(dir ${LIB_DIRS})
    if (IS_DIRECTORY "${PROJECT_SOURCE_DIR}/libs/${dir}")

        ##############################################################
        # Nome da lib
        #
        # Assumimos:
        # - a pasta se chama "log"
        # - o CMake dentro dela cria um target chamado "log"
        #
        # Esse nome será usado depois em target_link_libraries
        ##############################################################

        list(APPEND ALL_LIBS ${dir})

        ##############################################################
        # Includes
        #
        # Convenção:
        # - se existir libs/<lib>/include
        #   ele será exposto para todas as libs
        #
        # Isso permite includes cruzados sem dor de cabeça:
        #   #include <log/log.h>
        ##############################################################

        if(EXISTS "${PROJECT_SOURCE_DIR}/libs/${dir}/include")
            list(APPEND ALL_INCLUDES
                 "${PROJECT_SOURCE_DIR}/libs/${dir}/include")
        endif()

        ##############################################################
        # Defines automáticos
        #
        # Para cada módulo criamos um define global:
        #   TEM_<NOME_DA_LIB>
        #
        # Ex:
        #   libs/log  ->  #define TEM_LOG
        #
        # Útil para compilação condicional no C:
        #   #ifdef TEM_LOG
        ##############################################################

        string(TOUPPER ${dir} DIR_UPPER)
        list(APPEND MODULE_DEFINES "TEM_${DIR_UPPER}")

    endif()
endforeach()

######################################################################
# 3. GENERATE modules.h
#
# Este header é gerado automaticamente durante a configuração
# do CMake (não durante o build).
#
# Ele permite que QUALQUER código C saiba:
# - quais módulos existem no projeto
#
# Resultado típico:
#
#   #ifndef MODULES_H
#   #define MODULES_H
#   #define TEM_LOG
#   #define TEM_NET
#   #endif
######################################################################

set(MODULE_HEADER_CONTENT
"#ifndef MODULES_H\n#define MODULES_H\n\n")

foreach(def ${MODULE_DEFINES})
    string(APPEND MODULE_HEADER_CONTENT "#define ${def}\n")
endforeach()

string(APPEND MODULE_HEADER_CONTENT "\n#endif // MODULES_H")

# Escreve o arquivo no diretório de build
file(WRITE
     "${CMAKE_BINARY_DIR}/generated/modules.h"
     "${MODULE_HEADER_CONTENT}")

######################################################################
# 4. ADD SUBDIRECTORIES
#
# Aqui cada biblioteca é realmente adicionada ao build.
#
# IMPORTANTE:
# - Cada pasta em libs/<nome> DEVE ter seu próprio CMakeLists.txt
# - Esse CMake deve criar um target com o MESMO nome da pasta
######################################################################

foreach(lib ${ALL_LIBS})
    add_subdirectory("libs/${lib}")
endforeach()

######################################################################
# 5. RETRO-FITTING INCLUDES
#
# Agora que os targets já existem, forçamos:
# - todas as libs enxergarem
#   - includes de todas as outras libs
#   - o header gerado modules.h
#
# PRIVATE:
# - isso não vaza para quem linkar essas libs
######################################################################

foreach(lib ${ALL_LIBS})
    target_include_directories(${lib} PRIVATE
        ${ALL_INCLUDES}
        "${CMAKE_BINARY_DIR}/generated"
    )
endforeach()

######################################################################
# AUTOMATION END
######################################################################

######################################################################
# MAIN EXECUTABLE
#
# Define o executável principal do projeto
######################################################################

add_executable(${PROJECT_NAME} src/main.c)

######################################################################
# MAIN INCLUDES
#
# O executável também precisa enxergar modules.h
######################################################################

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_BINARY_DIR}/generated")

######################################################################
# LINK EVERYTHING
#
# Linka todas as bibliotecas automaticamente no executável
######################################################################

target_link_libraries(${PROJECT_NAME} PRIVATE ${ALL_LIBS})

