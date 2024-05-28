#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc,char *argv[]){
    if(argv[1]==NULL){
        printf("\033[1;31mUso correto: cat <arquivo>\033[0m\n");
        return 0;
    }
    char filepath[256];
    getcwd(filepath,sizeof(filepath));
    strcat(filepath, "/");
    strcat(filepath, argv[1]);
 
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("\033[1;31mcat : Não é possível localizar o caminho '%s' porque ele não existe.\033[0m", filepath);
    }

    else{
        char ch;
        while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    }

    printf("\n");

    return 0;

}
