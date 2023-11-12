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
        // Hicimos un regex para que al ordenar los archivos en carpetas solo intentara abrir los archivos que terminaran en un .txt
        char *regexstring = "[a-zA-Z]*\\.txt";
        regex_t regexcompile;
        regcomp(&regexcompile, regexstring, REG_EXTENDED);
        char delimitador[] = "\n";

        if (d)
        {
                // mediante el struct dirent recorrimos todos los archivos dentro de la carpeta de nuestra tarea
                while ((dir = readdir(d)) != NULL)
                {
                        // Validamos que hace match con nuestro regex
                        int value = regexec(&regexcompile, dir->d_name, 0, NULL, 0);
                        if (value == 0)
                        {
                                // abrimos el archivo, lo leimos guardamos su contenido en un char
                                // separamos la cadena apartir de los saltos de linea
                                // cuando el contador llega a 2, es cuando obtenemos la pinta de la carta
                                int cont = 1;
                                char cadena[26];
                                int leidos;
                                int fichero = open(dir->d_name, O_RDONLY);
                                lseek(fichero, 0, SEEK_SET);
                                leidos = read(fichero, cadena, 26);
                                cadena[leidos] = 0;
                                close(fichero);

                                // separar
                                char *token = strtok(cadena, delimitador);
                                if (token != NULL)
                                {
                                        while (token != NULL)
                                        {
                                                token = strtok(NULL, delimitador);
                                                if (cont == 2)
                                                {
                                                        // creamos la carpeta con el nombre de la pinta
                                                        // si esta creada el mkdir no hace nada
                                                        // rename para mover el archivo a su carpeta
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

        // menu
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
                        // pedimos la pinta por consola
                        printf("Ingrese la pinta: ");
                        char pinta1[10];
                        scanf("%s", pinta1);

                        // usamos strcat para concadenar asi obtener la direccion de la carpeta
                        char slash[10] = "./";
                        strcat(slash, pinta1);
                        strcat(slash, "/");

                        // abrimos la direccion
                        d = opendir(slash);
                        if (d)
                        {
                                // recorremos sus archivos
                                while ((dir = readdir(d)) != NULL)
                                {
                                        // usamos el regex para que no intente leer algo que no sea un archivo txt
                                        int value = regexec(&regexcompile, dir->d_name, 0, NULL, 0);
                                        if (value == 0)
                                        {
                                                // concadenamos para poder abrir el archivo
                                                char cadena[25]; /* Depósito de los caracteres */
                                                int leidos;
                                                char slash[10] = "./";
                                                strcat(slash, pinta1);
                                                strcat(slash, "/");
                                                strcat(slash, dir->d_name); // direccion del archivo concadenada

                                                // abrimos el archivo, lo leimos guardamos su contenido en un char
                                                int fichero = open(slash, O_RDONLY);
                                                lseek(fichero, 0L, SEEK_SET);
                                                leidos = read(fichero, cadena, 24);
                                                cadena[leidos] = 0;
                                                close(fichero);

                                                // sacamos el primer token de la cadena separando mediante el salto de linea y obtenemos el nombre
                                                char *token = strtok(cadena, delimitador);
                                                printf("\n%s\n", token);
                                        }
                                }
                                closedir(d);
                        }
                        break;

                case 2:
                        // pedimos la criatura por consola
                        printf("Ingrese la criatura: ");
                        char criatura1[20];
                        scanf("%s", criatura1);

                        // Para esta funcion abrimos las cuatro direcciones posibles o carpetas que deberian crearse
                        d = opendir("./Rombo/");

                        if (d)
                        {
                                while ((dir = readdir(d)) != NULL)
                                {
                                        // usamos el regex para que no intente leer algo que no sea un archivo txt
                                        int value = regexec(&regexcompile, dir->d_name, 0, NULL, 0);
                                        if (value == 0)
                                        {
                                                char cadena[25]; /* Depósito de los caracteres */
                                                int leidos;
                                                int cont = 0;
                                                char slash[50] = "./";
                                                strcat(slash, "Rombo");
                                                strcat(slash, "/");
                                                strcat(slash, dir->d_name); // direccion del archivo concadenada

                                                int fichero = open(slash, O_RDONLY);
                                                lseek(fichero, 0L, SEEK_SET);
                                                leidos = read(fichero, cadena, 24);
                                                cadena[leidos] = 0;
                                                close(fichero);

                                                // separamos la cadena apartir de los saltos de linea
                                                // cuando el contador llega a 2, es cuando obtenemos la pinta de la carta
                                                char *token = strtok(cadena, delimitador);
                                                char *nombre = token;
                                                //separamos todas las lineas dentro del txt
                                                while (token != NULL)
                                                {
                                                        token = strtok(NULL, delimitador);

                                                        if (token != NULL)
                                                        {

                                                                if (cont == 2)
                                                                {
                                                                        // verificamos si el token es igual a la criatura pedida
                                                                        if (strcasecmp(token, criatura1) == 0)
                                                                        {
                                                                                printf("\n%s\n", nombre);
                                                                        }
                                                                }
                                                                cont++;
                                                        }
                                                }
                                        }
                                }
                                closedir(d);
                        }
                        d = opendir("./Pica/");
                        if (d)
                        {
                                while ((dir = readdir(d)) != NULL)
                                {
                                        // usamos el regex para que no intente leer algo que no sea un archivo txt
                                        int value = regexec(&regexcompile, dir->d_name, 0, NULL, 0);
                                        if (value == 0)
                                        {
                                                char cadena[25]; /* Depósito de los caracteres */
                                                int leidos;
                                                int cont = 0;
                                                char slash[50] = "./";
                                                strcat(slash, "Pica");
                                                strcat(slash, "/");
                                                strcat(slash, dir->d_name); // direccion del archivo concadenada

                                                int fichero = open(slash, O_RDONLY);
                                                lseek(fichero, 0L, SEEK_SET);
                                                leidos = read(fichero, cadena, 24);
                                                cadena[leidos] = 0;
                                                close(fichero);

                                                // separamos la cadena apartir de los saltos de linea
                                                // cuando el contador llega a 2, es cuando obtenemos la pinta de la carta
                                                char *token = strtok(cadena, delimitador);
                                                char *nombre = token;
                                                //separamos todas las lineas dentro del txt
                                                while (token != NULL)
                                                {
                                                        token = strtok(NULL, delimitador);

                                                        if (token != NULL)
                                                        {

                                                                if (cont == 2)
                                                                {
                                                                        // verificamos si el token es igual a la criatura pedida
                                                                        if (strcasecmp(token, criatura1) == 0)
                                                                        {
                                                                                printf("\n%s\n", nombre);
                                                                        }
                                                                }
                                                                cont++;
                                                        }
                                                }
                                        }
                                }
                                closedir(d);
                        }
                        d = opendir("./Corazon/");
                        if (d)
                        {
                                while ((dir = readdir(d)) != NULL)
                                {
                                        // usamos el regex para que no intente leer algo que no sea un archivo txt
                                        int value = regexec(&regexcompile, dir->d_name, 0, NULL, 0);
                                        if (value == 0)
                                        {
                                                char cadena[25]; /* Depósito de los caracteres */
                                                int leidos;
                                                int cont = 0;
                                                char slash[50] = "./";
                                                strcat(slash, "Corazon");
                                                strcat(slash, "/");
                                                strcat(slash, dir->d_name); // direccion del archivo concadenada

                                                int fichero = open(slash, O_RDONLY);
                                                lseek(fichero, 0L, SEEK_SET);
                                                leidos = read(fichero, cadena, 24);
                                                cadena[leidos] = 0;
                                                close(fichero);

                                                // separamos la cadena apartir de los saltos de linea
                                                // cuando el contador llega a 2, es cuando obtenemos la pinta de la carta
                                                char *token = strtok(cadena, delimitador);
                                                char *nombre = token;
                                                //separamos todas las lineas dentro del txt
                                                while (token != NULL)
                                                {
                                                        token = strtok(NULL, delimitador);

                                                        if (token != NULL)
                                                        {

                                                                if (cont == 2)
                                                                {
                                                                        // verificamos si el token es igual a la criatura pedida
                                                                        if (strcasecmp(token, criatura1) == 0)
                                                                        {
                                                                                printf("\n%s\n", nombre);
                                                                        }
                                                                }
                                                                cont++;
                                                        }
                                                }
                                        }
                                }
                                closedir(d);
                        }
                        d = opendir("./Trebol/");
                        if (d)
                        {
                                while ((dir = readdir(d)) != NULL)
                                {
                                        // usamos el regex para que no intente leer algo que no sea un archivo txt
                                        int value = regexec(&regexcompile, dir->d_name, 0, NULL, 0);
                                        if (value == 0)
                                        {
                                                char cadena[25]; /* Depósito de los caracteres */
                                                int leidos;
                                                int cont = 0;
                                                char slash[50] = "./";
                                                strcat(slash, "Trebol");
                                                strcat(slash, "/");
                                                strcat(slash, dir->d_name); // direccion del archivo concadenada

                                                int fichero = open(slash, O_RDONLY);
                                                lseek(fichero, 0L, SEEK_SET);
                                                leidos = read(fichero, cadena, 24);
                                                cadena[leidos] = 0;
                                                close(fichero);

                                                // separamos la cadena apartir de los saltos de linea
                                                // cuando el contador llega a 2, es cuando obtenemos la pinta de la carta
                                                char *token = strtok(cadena, delimitador);
                                                char *nombre = token;
                                                //separamos todas las lineas dentro del txt
                                                while (token != NULL)
                                                {
                                                        token = strtok(NULL, delimitador);

                                                        if (token != NULL)
                                                        {

                                                                if (cont == 2)
                                                                {
                                                                        // verificamos si el token es igual a la criatura pedida
                                                                        if (strcasecmp(token, criatura1) == 0)
                                                                        {
                                                                                printf("\n%s\n", nombre);
                                                                        }
                                                                }
                                                                cont++;
                                                        }
                                                }
                                        }
                                }
                                closedir(d);
                        }
                        break;

                case 3:
                        //pedimos el nombre de la carta por consola
                        printf("Ingrese el nombre de la carta: ");
                        char carta1[20];
                        char pinta[10];
                        scanf("%s", carta1);
                        //pedimos la nueva pinta igualmente
                        printf("Ingrese la pinta Nueva: ");
                        scanf("%s", pinta);

                        //creamos todas las posibles direcciones donde puede estar la carta
                        char trebol1[30] = "./Trebol/";
                        char corazon1[30] = "./Corazon/";
                        char pica1[30] = "./Pica/";
                        char rombo1[30] = "./Rombo/";

                        //se les concadena el nombre de la carta
                        strcat(trebol1, carta1);
                        strcat(corazon1, carta1);
                        strcat(pica1, carta1);
                        strcat(rombo1, carta1);

                        //creamos la ruta nueva donde ira la carta
                        char ruta_nueva[30] = "./";
                        strcat(ruta_nueva, pinta);
                        strcat(ruta_nueva, "/");
                        strcat(ruta_nueva, carta1);

                        d = opendir(".");
                        if (d)
                        {

                                while ((dir = readdir(d)) != NULL)
                                {
                                        
                                        //intentamos abrir todas las posibles direcciones
                                        char cadena[26];
                                        int fichero1 = open(corazon1, O_RDONLY);

                                        int fichero2 = open(pica1, O_RDONLY);

                                        int fichero3 = open(rombo1, O_RDONLY);

                                        int fichero4 = open(trebol1, O_RDONLY);

                                        //Creamos un nuevo archivo en la direccion nueva
                                        int fd = open(ruta_nueva, O_WRONLY | O_CREAT, 0777); 
                                        lseek(fichero1, 0L, SEEK_SET);
                                        lseek(fichero2, 0L, SEEK_SET);
                                        lseek(fichero3, 0L, SEEK_SET);
                                        lseek(fichero4, 0L, SEEK_SET);

                                        int cont = 0;
                                        //intentamos leer todas las posibles direcciones
                                        ssize_t r1 = read(fichero1, cadena, 25);

                                        cadena[r1] = 0; // zero-terminate manually.

                                        ssize_t r2 = read(fichero2, cadena, 25);

                                        cadena[r2] = 0; // zero-terminate manually.

                                        ssize_t r3 = read(fichero3, cadena, 25);

                                        cadena[r3] = 0; // zero-terminate manually.

                                        ssize_t r4 = read(fichero4, cadena, 25);

                                        cadena[r4] = 0; // zero-terminate manually.

                                        //si el fichero es mayor a 0 significa que ahi se encontraba la carta
                                        //por lo tanto con unlink la borramos para escribir todo en un nuevo archivo
                                        //solo entrara a un fichero, pq la cartas no se repiten.
                                        if (fichero1 > 0)
                                        {
                                                unlink(corazon1);
                                        }
                                        if (fichero2 > 0)
                                        {
                                                unlink(pica1);
                                        }
                                        if (fichero3 > 0)
                                        {
                                                unlink(rombo1);
                                        }
                                        if (fichero4 > 0)
                                        {
                                                unlink(trebol1);
                                        }
                                        
                                        //vamos separando la cadena leida en una de las direcciones
                                        //la vamos escribiendo linea por linea en el archivo nuevo
                                        char *token = strtok(cadena, delimitador); //primera linea del txt

                                        write(fd, token, strlen(token));
                                        write(fd, "\n", strlen("\n"));

                                        while (token != NULL)
                                        {
                                                token = strtok(NULL, delimitador);
                                                if (token != NULL)
                                                {

                                                        if (cont == 1) //segunda linea del txt
                                                        {
                                                                strcat(pinta, "\n");
                                                                //escribe la nueva pinta, remplaza la que estaba escrita antes
                                                                write(fd, pinta, strlen(pinta));
                                                        }
                                                        else if (cont > 2)
                                                        {       
                                                                //si lee mas de lo que deberia no escribe nada
                                                                write(fd, "", strlen(""));
                                                        }

                                                        else
                                                        {       
                                                                //lo demas lo escribe como estaba
                                                                write(fd, token, strlen(token));
                                                                if (cont != 2)
                                                                {
                                                                        write(fd, "\n", strlen("\n"));
                                                                }
                                                        }
                                                        cont++;
                                                }
                                        }
                                        
                                        //cerramos todos los ficheros
                                        close(fd);
                                        close(fichero1);
                                        close(fichero2);
                                        close(fichero3);
                                        close(fichero4);
                                        break;
                                }
                                closedir(d);
                        }

                        break;
                case 4:
                        //pedimos el nombre de la carta por consola 
                        printf("Ingrese el nombre de la carta: ");
                        char carta[20];
                        scanf("%s", carta);
                        //pedimos la nueva criatura igualmente
                        printf("Ingrese la criatura nueve: ");
                        char criatura[20];
                        scanf("%s", criatura);
                        
                        //creamos todas las posibles direcciones donde puede estar la carta
                        char trebol[30] = "./Trebol/";
                        char corazon[30] = "./Corazon/";
                        char pica[30] = "./Pica/";
                        char rombo[30] = "./Rombo/";

                         //se les concadena el nombre de la cartas
                        strcat(trebol, carta);
                        strcat(corazon, carta);
                        strcat(pica, carta);
                        strcat(rombo, carta);

                        d = opendir(".");
                        if (d)
                        {

                                while ((dir = readdir(d)) != NULL)
                                {       
                                        //intentamos abrir todas las posibles direcciones
                                        int fd;
                                        char cadena[26];
                                        int fichero1 = open(corazon, O_RDONLY);

                                        int fichero2 = open(pica, O_RDONLY);

                                        int fichero3 = open(rombo, O_RDONLY);

                                        int fichero4 = open(trebol, O_RDONLY);

                                        lseek(fichero1, 0L, SEEK_SET);
                                        lseek(fichero2, 0L, SEEK_SET);
                                        lseek(fichero3, 0L, SEEK_SET);
                                        lseek(fichero4, 0L, SEEK_SET);

                                        int cont = 0;

                                        //intentamos leer todos los archivos
                                        ssize_t r1 = read(fichero1, cadena, 25);

                                        cadena[r1] = 0;

                                        ssize_t r2 = read(fichero2, cadena, 25);

                                        cadena[r2] = 0; 

                                        ssize_t r3 = read(fichero3, cadena, 25);

                                        cadena[r3] = 0; 

                                        ssize_t r4 = read(fichero4, cadena, 25);

                                        cadena[r4] = 0; 

                                        //si el fichero es mayor a 0 significa que ahi se encontraba la carta
                                        //por lo tanto con unlink la borramos para escribir todo en un nuevo archivo
                                        //solo entrara a un fichero, pq la cartas no se repiten.

                                        if (fichero1 > 0)
                                        {
                                                unlink(corazon);
                                                //Creamos un nuevo archivo 
                                                fd = open(corazon, O_WRONLY | O_CREAT, 0777);
                                        }
                                        if (fichero2 > 0)
                                        {
                                                unlink(pica);
                                                //Creamos un nuevo archivo 
                                                fd = open(pica, O_WRONLY | O_CREAT, 0777);
                                        }
                                        if (fichero3 > 0)
                                        {
                                                unlink(rombo);
                                                //Creamos un nuevo archivo
                                                fd = open(rombo, O_WRONLY | O_CREAT, 0777);
                                        }
                                        if (fichero4 > 0)
                                        {
                                                unlink(trebol);
                                                //Creamos un nuevo archivo 
                                                fd = open(trebol, O_WRONLY | O_CREAT, 0777);
                                        }

                                        char *token = strtok(cadena, delimitador);

                                        write(fd, token, strlen(token));
                                        write(fd, "\n", strlen("\n"));

                                        while (token != NULL)
                                        {
                                                token = strtok(NULL, delimitador);

                                                if (token != NULL)
                                                {

                                                        if (cont == 2)
                                                        {       
                                                                //escribe la nueva criatura, remplaza la que estaba escrita antes
                                                                write(fd, criatura, strlen(criatura));
                                                        }
                                                        else if (cont > 2)
                                                        {       
                                                                //si lee mas de lo que deberia no escribe nada
                                                                write(fd, "", strlen(""));
                                                        }
                                                        else
                                                        {       
                                                                //los demas token de la cadena, se escribe tal como estaban en el archivo antiguo
                                                                write(fd, token, strlen(token));
                                                                if (cont != 2)
                                                                {
                                                                        write(fd, "\n", strlen("\n"));
                                                                }
                                                        }
                                                        cont++;
                                                }
                                        }
                                        
                                         //cerramos todos los ficheros
                                        close(fd);
                                        close(fichero1);
                                        close(fichero2);
                                        close(fichero3);
                                        close(fichero4);
                                }
                                closedir(d);
                        }
                        break;
                }

        } while (opcion != 5);

        return 0;
}