#include <math.h>
#include <stdio.h>

int main()
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