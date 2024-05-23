#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>



void imprimeStatus(char *filename){
    struct stat fileStat;
    struct passwd *pwd;
    struct group *grp;
    char timebuf[80];

    // Obter informações do arquivo
    if (stat(filename, &fileStat) < 0) {
        perror("stat");
        return;
    }

    // Imprimir tipo e permissões
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");

    // Imprimir número de links
    printf(" %ld", (long)fileStat.st_nlink);

    // Imprimir nome do usuário e grupo
    pwd = getpwuid(fileStat.st_uid);
    grp = getgrgid(fileStat.st_gid);
    printf(" %s %s", pwd->pw_name, grp->gr_name);

    // Imprimir tamanho do arquivo
    printf(" %8ld", (long)fileStat.st_size);

    // Formatar e imprimir horário da última modificação
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileStat.st_mtime));
    printf(" %s", timebuf);

    // Imprimir nome do arquivo
    printf("\033[1;32m %s\033[0m\n",filename);
}

int main(int argc,char *argv[]){
    DIR *diretorio;
    struct dirent *entrada;
    int flag=0;

    char dir[256];
    getcwd(dir,sizeof(dir));

    diretorio = opendir(dir);


    while ((entrada = readdir(diretorio)) != NULL)
  {
    if(argv[1] == NULL){
      if (entrada->d_type == DT_REG)
      {
        printf("\033[1;32m%s\033[0m ",entrada->d_name);
      }
      else if (entrada->d_type == DT_DIR && strcmp(entrada->d_name, "..")!=0 && strcmp(entrada->d_name, ".")!=0)
      {
        printf("\033[1;32m%s\033[0m ",entrada->d_name);
      }
      flag=2;
    }
    else{
      if(strcmp(argv[1],"-l")==0){
        if(strcmp(entrada->d_name, "..")!=0 && strcmp(entrada->d_name, ".")!=0){
          imprimeStatus(entrada->d_name);
        }
        flag=1;
      }
      else if(strcmp(argv[1],"-a")==0){
        printf("\033[1;32m%s\033[0m ",entrada->d_name);
        flag=1;
      }
      else if((argv[1][1]=='a' || argv[1][1]=='l')&&(argv[1][1]!=argv[1][2]) && (argv[1][2]=='a' || argv[1][2]=='l')){
        imprimeStatus(entrada->d_name);
        flag=1;
      }
    }
    
  }
  

  if(flag==0){
    printf("\033[1;31m'ls %s' não é reconhecido como um comando interno\n ou externo, um programa operável ou um arquivo em lotes.\033[0m\n", argv[1]);
  }
  if(flag==2 || flag==1){
    printf("\n");
  }

  if (closedir(diretorio) == -1)
  {
    printf("Erro ao fechar diretorio\n");
    return 1;
  }


}
