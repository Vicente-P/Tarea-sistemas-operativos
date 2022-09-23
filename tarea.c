#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <regex.h>

int main(int argc, char *argv[])
{
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        char *regexstring = "[a-zA-Z]*\\.txt";
        regex_t regexcompile;
        regcomp(&regexcompile, regexstring, REG_EXTENDED);

        if (d)
        {
                while ((dir = readdir(d)) != NULL)
                {
                        int value = regexec(&regexcompile, dir->d_name, 0, NULL, 0);
                        if (value == 0)
                        {
                                char cadena[50]; /* Depósito de los caracteres */
                                int leidos;
                                int fichero = open(dir->d_name, O_RDONLY);
                                if (fichero == -1)
                                {
                                        perror("Error al abrir fichero:");
                                        exit(1);
                                }
                                lseek(fichero, 0, SEEK_SET);
                                char delimitador[] = "\n";
                                int cont = 1;
                                /* Lee diez bytes */
                                leidos = read(fichero, cadena, 50);
                                close(fichero);
                                char *token = strtok(cadena, delimitador);
                                if (token != NULL)
                                {
                                        while (token != NULL)
                                        {
                                                token = strtok(NULL, delimitador);
                                                if (cont == 2)
                                                {
                                                        mkdir(token, S_IRWXU);
                                                        char slash[3] = "./";
                                                        strcat(slash, token);
                                                        strcat(slash, "/");
                                                        strcat(slash, dir->d_name);
                                                        rename(dir->d_name, slash);
                                                }
                                                cont++;
                                        }
                                }
                        }
                }
                closedir(d);
        }

        int n, opcion;

        do
        {
                printf("\n   1. Ver cartas por pinta");
                printf("\n   2. Ver cartas por criatura");
                printf("\n   3. Editar Pinta");
                printf("\n   4. Editar criatura");
                printf("\n   5. Salir.");
                printf("\n\n   Introduzca opcion (1-5): ");

                scanf("%d", &opcion);

                /* Inicio del anidamiento */

                switch (opcion)
                {
                case 1:
                       ;
                        break;

                case 2:

                        break;

                case 3:
                        break;
                case 4:
                        break;
                }

                /* Fin del anidamiento */

        } while (opcion != 5);

        return 0;
}