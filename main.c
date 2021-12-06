#include "Matice.h"
#include <stdio.h>

int main() {
    matice mat1 = jednotkova(3, 4);
    nastav_prvek(mat1 , 0, 1, 2);nastav_prvek(mat1 , 0, 2, 3);nastav_prvek(mat1 , 0, 3, 4);nastav_prvek(mat1 , 1, 0, 5);nastav_prvek(mat1 , 2, 3, 1);
    
    printf("%f\n", mat1.data[1][3]);
    vypis(mat1);

    printf("Vynasobime 3x\n");
    vypis(nasobeni(mat1, 3.0));

    printf("\nTranspozice\n");
    matice t = transpozice(mat1);
    vypis(t);
}

