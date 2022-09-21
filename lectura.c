#include <fcntl.h>      /* Modos de apertura */
#include <stdlib.h>     /* Funciones de ficheros */
#include <stdio.h>

int main ( int argc, char* argv[] )
{
   char cadena[11];	/* Depósito de los caracteres */
   int leidos;

   /* Apertura del fichero */

   int fichero = open ("/mnt/c/Users/vicho/Desktop/Tarea-sistemas-operativos/Rombo/Cuatro.txt/", O_RDONLY);

   /* Comprobación */   
   if (fichero==-1)
   {
        perror("Error al abrir fichero:");
        exit(1);
   }

   /* Coloca el puntero en la posición 400 */
   lseek(fichero,0,SEEK_SET);

   /* Lee diez bytes */
   leidos = read(fichero, cadena, 11);
   close(fichero);
   cadena[11]=0;

   /* Mensaje para ver qué se leyó */
   printf ( "Se leyeron %d bytes. La cadena leida es %s\n",leidos,cadena );

   return 0;