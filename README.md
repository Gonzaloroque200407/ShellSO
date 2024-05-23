# ShellSO
Trabalho final de projetos de sistemas operacionais

## Sumário

- [Instalação](#instalação)
- [Comandos](#comandos)
- [Comando em Paralelo](#comandos-em-paralelo)
## Instalação

Para instalar o projeto, siga os passos abaixo:

- Clone o repositório
```
git clone https://github.com/seuusuario/seu-repositorio.git
```

- Navegue até o diretório do projeto
```
cd seu-repositorio
```

- Compilar o arquivo
```
gcc -c arquivo.c
```
```
gcc -o arquivo arquivo.o
```
- Executar o shell
```
./arquivo
```

## Comandos

Opções de comandos:

- path: Define caminho(s) para busca de executáveis
  - Exemplo:
    ```
    path <caminho>
    ```
- cd: Muda o diretório de trabalho
  - Exemplo:
    ```
     cd <nome_do_arquivo>
    ```
    
    ```
    cd ..
    ```
- ls: Lista o conteúdo do diretório atual
  - Parâmetros disponíveis:
    - -l
    - -a
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
