# GerBiC - Gerenciador

Este diretório se destina aos arquivos do Gerenciador de módulos do GerBiC.

**Motivação:** O meu sistema de biblioteca geral usa um modelo específico de como os diretórios e arquivos dos módulos devem estar para realmente funcionar. Copiar e colar na mão era uma simples inconveniência, mas eu decidi fazer um Gerenciador de Módulos como meu primeiro projeto da biblioteca, para ela se acelerar em desenvolvimento.

**Uso:** ```./GerBiC/Gerenciador <nome do projeto/módulo>```

**Estrutura:** Os arquivos de texto são os modelos para CMake que o projeto usa. O executável é um pré-compilado do Gerenciador, e o arquivo C é o arquivo bruto do Gerenciador. Para usar, coloque ele dentro de "./src/" com o nome "main.c", e estará pronto para uso.

**Execução:** O que ele faz é simples. Ele verifica pela existência de "libs/". Não existe? Então ele monta toda a estrutura do projeto, com o build/, o libs/, e o src/. E aí o argumento que você passou, ele usa como o nome do projeto em src/main.c. Mas se o projeto já exista, ele vai em libs/ e procura por um módulo com aquele nome. Não existe? Então ele cria o diretório, copia o CMake dentro dele, e cria os diretórios e arquivos padrão do módulo e os abrem no neovim. Já existe? Então eles são abertos no neovim.
