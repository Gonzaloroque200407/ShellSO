#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int size_buffer = 0;

void path(char **caminhos, int count, char ***buffer_ptr) {
    char **buffer = *buffer_ptr;

    if (caminhos[1] == NULL) {
        for (int i = 0; i < size_buffer; i++) {
            printf("%s\n", buffer[i]);
        }
        printf("\n");
        return;
    }

    buffer = realloc(buffer, sizeof(char *) * (size_buffer + count - 1));
    if (buffer == NULL) {
        perror("Falha na realocação de memória");
        exit(1);
    }

    for (int x = 1, i = size_buffer; x < count; x++, i++) {
        buffer[i] = malloc(strlen(caminhos[x]) + 1);
        if (buffer[i] == NULL) {
            perror("Falha na alocação de memória");
            exit(1);
        }
        strcpy(buffer[i], caminhos[x]);
    }
    size_buffer += count - 1;
    *buffer_ptr = buffer;
}

char *getPath(char *arquivo, char **buffer) {
    char *busca = (char *)malloc(100 * sizeof(char));
    for (int i = 0; i < size_buffer; i++) {
        strcpy(busca, buffer[i]);
        strcat(busca, "/");
        strcat(busca, arquivo);
        if (access(busca, F_OK) == 0) {
            return busca;
        }
    }
    free(busca); 
    return "0";
}

void funcaocd(char comando[]) {
    char novoDir[200];

    if (strcmp(comando, ".") == 0) {
        return;
    } else if (strcmp(comando, "..") == 0) {
        chdir("..");
        return;
    } else {
        if (strchr(comando, '/') != NULL) {
            strcpy(novoDir, comando);
        } else {
            getcwd(novoDir, sizeof(novoDir));
            strcat(novoDir, "/");
            strcat(novoDir, comando);
        }
        if (chdir(novoDir) != 0) {
            printf("\033[1;31mcd : Não é possível localizar o caminho '%s' porque ele não existe.\033[0m\n", novoDir);
        }
    }
}

void executar_unico(char **parameters, int count2, char ***buffer_ptr) {
    char **buffer = *buffer_ptr;
    pid_t pid;
    int pos = -1;
    int flag=0;
    char *arquivo = NULL;

    for (int j = 0; j < count2; j++) {
        if (strcmp(parameters[j], ">") == 0) {
            pos = j;
            arquivo = parameters[j + 1];
            parameters[j] = NULL;
            flag=1;
            break;
        }
    }

    if (strcmp(parameters[0], "cd") == 0) {
        if(parameters[1]!=NULL){
        funcaocd(parameters[1]);
        }
        else{
            printf("\033[1;31mcd : Insira um caminho válido\033[0m\n");
        }
    } else if (strcmp(parameters[0], "path") == 0) {
        path(parameters, count2, buffer_ptr);
    } else if (strcmp(parameters[0], "exit") == 0) {
        exit(0);
    } else {
        if(flag==1 && arquivo==NULL){
             printf("\033[1;31mErro: informe o arquivo no qual deseja redirecionar\033[0m\n");
        }
        else{
        char *caminho = getPath(parameters[0], buffer);
        if (strcmp(caminho, "0") != 0) {
            pid = fork();
            if (pid < 0) {
                printf("Erro no fork");
            } else if (pid == 0) {
                if (pos != -1 && arquivo != NULL) {
                    freopen(arquivo, "w", stdout);
                }
                execv(caminho, parameters);
                exit(1);
            } else {
                wait(NULL);
            }
            free(caminho);
        } else {
            printf("\033[1;31m'%s' não é reconhecido como um comando interno\n ou externo, um programa operável ou um arquivo em lotes.\033[0m\n", parameters[0]);
        }
        }
        
    }
}

void executar(char *comando, char ***buffer_ptr) {
    char *token;
    char **parametros = NULL;
    int count = 0;

    token = strtok(comando, " ");
    while (token) {
        parametros = realloc(parametros, sizeof(char *) * (count + 1));
        parametros[count] = strdup(token);
        
        count++;
        token = strtok(NULL, " ");
    }

    char **parameters = NULL;
    int count2 = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(parametros[i], "&") == 0) {
            parameters = realloc(parameters, sizeof(char *) * (count2 + 1));
            parameters[count2] = NULL;
            executar_unico(parameters, count2, buffer_ptr);
            for (int j = 0; j < count2; j++) {
                free(parameters[j]);
            }
            free(parameters);
            parameters = NULL;
            count2 = 0;
        } else {
            parameters = realloc(parameters, sizeof(char *) * (count2 + 1));
            parameters[count2] = strdup(parametros[i]);
            count2++;
        }
    }

    if (count2 > 0) {
        parameters = realloc(parameters, sizeof(char *) * (count2 + 1));
        parameters[count2] = NULL;
        executar_unico(parameters, count2, buffer_ptr);
        for (int j = 0; j < count2; j++) {
            free(parameters[j]);
        }
        free(parameters);
    }

    for (int j = 0; j < count; j++) {
        free(parametros[j]);
    }
    free(parametros);
}

int main(int argc, char *argv[]) {
    char dir[256];
    char comando[100];
    char **buffer = NULL;

    if (argc < 2) {
        printf("\033[1;31mArgumento não reconhecido, utilize ./projeto batch ou ./projeto texto\033[0m\n");
        return 1;
    }

    if (strcmp("batch", argv[1]) == 0) {
        FILE *batch_file;
        char *batch_line = NULL;
        size_t tam = 0;
        ssize_t read;

        batch_file = fopen("projeto.batch", "r");
        if (batch_file == NULL) {
            perror("Erro ao abrir o arquivo projeto.batch");
            exit(EXIT_FAILURE);
        }

        while ((read = getline(&batch_line, &tam, batch_file)) != -1) {
            if (batch_line[read - 1] == '\n') {
                batch_line[read - 1] = '\0';
            }
            executar(batch_line, &buffer);
        }

        free(batch_line);
        fclose(batch_file);
    } else if (strcmp("texto", argv[1]) == 0) {
        while (1) {
            getcwd(dir, sizeof(dir));
            printf("%s> ", dir);
            fgets(comando, sizeof(comando), stdin);
            comando[strcspn(comando, "\n")] = '\0';
            executar(comando, &buffer);
        }
    }

    for (int i = 0; i < size_buffer; i++) {
        free(buffer[i]);
    }
    free(buffer);
    return 0;
}
