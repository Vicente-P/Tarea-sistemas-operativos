#include <string.h>     /* Función strlen() */    /* Modos de apertura y función open()*/
#include <stdlib.h>     /* Funciones write() y close() */
#include <dirent.h> 
#include <stdio.h> 
#include <sys/stat.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <regex.h>

int main(void) {
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  char * regexstring ="[a-zA-Z]*\\.txt";
  regex_t regexcompile;
  regcomp(&regexcompile,regexstring,REG_EXTENDED);
  
  
  
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      int value = regexec(&regexcompile, dir->d_name, 0, NULL, 0);
      if(value == 0){
         char cadena[10];	/* Depósito de los caracteres */
         int leidos;
         int fichero = open (dir->d_name, O_RDONLY);

         if (fichero==-1)
         {
            perror("Error al abrir fichero:");
            exit(1);
         }
         lseek(fichero,6,SEEK_SET);

         /* Lee diez bytes */
         leidos = read(fichero, cadena, 9);
         close(fichero);
         printf("%s\n",cadena);
         mkdir(cadena,S_IRWXU);
         cadena[9]=0;
   
      }
    }
    closedir(d);
  }
  return(0);
}

