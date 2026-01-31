# GerBiC - Gerenciador de Bibliotecas em C 

Este é um projeto pessoal para me ajudar a integrar diferentes bibliotecas mais facilmente em C.

**Motivação**: Eu criei várias tentativas de bibliotecas em C, mas eventualmente, por conta de dependências cíclicas, o projeto ficava complexo de mais para entender, e eu acabava tendo que recomeçar com uma versão mais polida. Eventualmente decidi separar as funcionalidades em diretórios (Módulos, você os encontra dentro de [libs](libs/)) controlados por arquivos [CMake](CMakeLists.txt).

**Estrutura:** O projeto é organizado da seguinte forma:

```
$ tree 
.
├── build
├── CMakeLists.txt
├── GerBiC
│   ├── CMake_dir.txt
│   ├── CMake_lib.txt
│   ├── Gerenciador
│   ├── Gerenciador.c
│   └── README.md
├── libs
│   ├── Biblioteca_qualquer
│   │   ├── CMakeLists.txt
│   │   ├── include
│   │   │   └── Biblioteca_qualquer.h
│   │   └── src
│   │       └── lib.c
│   Outras bibliotecas ...
├── README.md
└── src
    └── main.c

33 directories, 35 files
```

**Build**: Local padrão onde o CMake gera a configuração do Make e o executável.

**Libs:** Onde o projeto/módulo guardam seus módulos. Um módulo pode ter módulos internos também, recursivamente.

**Src:** Onde o arquivo C do projeto/módulo respectivo fica.

**Include:** Este diretório existe apenas em módulos, nele fica o header do módulo.

**GerBiC:** Diretório do configurador da biblioteca. Não necessário para a execução, mas auxilia na criação de módulos e sua chamada em 'neovim'. Leia mais sobre em [GerBiC](GerBiC/README.md).

**Especificações do Sistema:** Eu criei esse projeto majoritáriamente para uso próprio, então, no momento, talvez não seja otimizado para outras máquinas. O GerBiC por exemplo infere que o usuário tenha e use NeoVim, e a não ser que recompilado, isso não pode ser reconfigurado. Abaixo eu inseri um exemplo do ambiente de desenvolvimento (dados sensíveis omitidos).

```
$ nvim -v
NVIM v0.11.5
Build type: RelWithDebInfo
LuaJIT 2.1.1767980792
Run "nvim -V1 -v" for more info
$ cmake -version
cmake version 4.2.2-dirty

CMake suite maintained and supported by Kitware (kitware.com/cmake).
$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-pc-linux-gnu/15.2.1/lto-wrapper
Target: x86_64-pc-linux-gnu
Configured with: /build/gcc/src/gcc/configure --enable-languages=ada,c,c++,d,fortran,go,lto,m2,objc,obj-c++,rust,cobol --enable-bootstrap --prefix=/usr --libdir=/usr/lib --libexecdir=/usr/lib --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=https://gitlab.archlinux.org/archlinux/packaging/packages/gcc/-/issues --with-build-config=bootstrap-lto --with-linker-hash-style=gnu --with-system-zlib --enable-__cxa_atexit --enable-cet=auto --enable-checking=release --enable-clocale=gnu --enable-default-pie --enable-default-ssp --enable-gnu-indirect-function --enable-gnu-unique-object --enable-libstdcxx-backtrace --enable-link-serialization=1 --enable-linker-build-id --enable-lto --enable-multilib --enable-plugin --enable-shared --enable-threads=posix --disable-libssp --disable-libstdcxx-pch --disable-werror
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 15.2.1 20260103 (GCC) 
$ fastfetch
                  -`                     ##########
                 .o+`                    ---------------
                `ooo/                    OS: Arch Linux x86_64
               `+oooo:                   Host: ###############
              `+oooooo:                  Kernel: Linux 6.18.6-arch1-1
              -+oooooo+:                 Uptime: ###############
            `/:-:++oooo+:                Packages: ###########################
           `/++++/+++++++:               Shell: bash 5.3.9
          `/++++++++++++++:              Display #############################################
         `/+++ooooooooooooo/`            DE: KDE Plasma 6.5.5
        ./ooosssso++osssssso+`           WM: KWin (X11)
       .oossssso-````/ossssss+`          WM Theme: ######
      -osssssso.      :ssssssso.         Theme: #####################################################
     :osssssss/        osssso+++.        Icons: ########################################
    /ossssssss/        +ssssooo/-        Font: ##################################################
  `/ossssso+/:-        -:/+osssso+-      Cursor: #############
 `+sso+:-`                 `.-/+oso:     Terminal: konsole 25.12.1
`++:.                           `-/+/    CPU: 11th Gen Intel(R) Core(TM) i5-1135G7 (8) @ 4.20 GHz
.`                                 `/    GPU: Intel Iris Xe Graphics @ 1.30 GHz [Integrated]
                                         Memory: #########################
                                         Swap: ########################
                                         Disk (/): ##################################
                                         Disk (/home): ###################################
                                         Local IP (wlan0): #################
                                         Battery (SR Real Battery): ############################################
                                         Locale: en_GB.UTF-8

                                                                 
                                                                 
$ 

```





