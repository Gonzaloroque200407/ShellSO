# ShellSO
Trabalho final de projetos de sistemas operacionais

## Sumário

- [Instalação](#instalação)
- [Recepção dos Comandos](#recepção-dos-comandos)
- [Comandos](#comandos)
- [Comando em Paralelo](#comandos-em-paralelo)
## Instalação

Para instalar o projeto, siga os passos abaixo:

- Abra o seu termninal
- Navega para o diretório compartilhado com a VM
```
cd navegue/até/o/caminho/desejado
```
- Baixe o repositório
```
Baixe o repositório com download zip e extraia na pasta compartilhada da sua VM
```
- Abra a sua VM
- Navegue até o diretório do projeto
```
cd nome_da_pasta_compartilhada/ShellSO-main/shell
```

- Executar o shell

Para executar os comandos via arquivo .batch
```
./projeto batch
```
Para executar os comandos via terminal texto
```
./projeto texto 
```
## Recepção dos Comandos 

Ao executar o shell poderá selecionar duas maneiras:
  - Interativamente, via terminal de texto
    - Utilizar as opções de comandos existentes
  - Vindos de um arquivo .batch
    - editar o arquivo 'projeto.batch' com os comandos desejados e também com a localização do arquivo projeto.c nos conformes da VM.
## Comandos

Opções de comandos:

- path: Define caminho(s) para busca de executáveis
  - Exemplo:
    ```
    path <caminho>
    ```
    Apenas path imprime o path atual
    ```
    path
    ```
- cd: Muda o diretório de trabalho
  - Exemplo:
    ```
     cd <nome_do_arquivo>
    ```
    
    ```
    cd .. (retorna uma pasta)
    ```
    ```
    cd . (mantém o diretório atual)
    ```
- ls: Lista o conteúdo do diretório atual
  - Parâmetros disponíveis:
    - -l
    - -a
    - -la
    - -al
  - Exemplo:
    ```
    ls
    ```
    ```
    ls -a
    ```
- cat: Lê o conteúdo do arquivo no argumento e o escreve na saída padrão
  - Exemplo:
    ```
    cat <nome_do_arquivo>
    ```
- clear: Limpa o terminal (Necessita adicionar o caminho "/usr/bin" ao path)
  - Exemplo:
    ```
    clear
    ```
- exit: Finaliza o shell
  - Exemplo:
    ```
    exit
    ```
- Redirecionamento de saída: 
  - Exemplo:
    ```
    cat <arquivo.txt> > <arquivo_saída>
    ```
 
## Comandos em Paralelo

Para executar comandos em pararelo é necessário utilizar o "&":
  - Exemplo:
  ```
  cmd1 & cmd2 arg1 arg2 & cmd arg
  ```
