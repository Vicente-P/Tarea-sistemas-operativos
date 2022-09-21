#include <fcntl.h>      /* Modos de apertura */
#include <stdlib.h>     /* Funciones de ficheros */
#include <stdio.h>

int main ( int argc, char* argv[] )
{
    int n, opcion;

    do
    {
        printf( "\n   1. Ver cartas por pinta");
        printf( "\n   2. Ver cartas por criatura");
        printf( "\n   3. Editar Pinta");
        printf( "\n   4. Editar criatura");
        printf( "\n   5. Salir." );
        printf( "\n\n   Introduzca opcion (1-5): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1:
                char cadena[11];	/* Depósito de los caracteres */
                int leidos;

                /* Apertura del fichero */

                int fichero = open ("/mnt/c/Users/vicho/Desktop/Tarea-sistemas-operativos/Rombo", O_CREAT|O_RONL,0644);

                /* Comprobación */   
                if (fichero==-1)
                {
                        perror("Error al abrir fichero:");
                        exit(1);
                }

                /* Coloca el puntero en la posición 400 */
                lseek(fichero,0,SEEK_SET);

                /* Lee diez bytes */
                leidos = fread(fichero, cadena, 11);
                pclose(fichero);
                cadena[11]=0;

                /* Mensaje para ver qué se leyó */
                printf ( "Se leyeron %d bytes. La cadena leida es %s\n",leidos,cadena );
                break;

            case 2:
                    
                    break;

            case 3: 
                    break;
            case 4:
                    break;
         }

         /* Fin del anidamiento */

    } while ( opcion != 5 );

    return 0;
}