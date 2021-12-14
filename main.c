#include "matice.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    matice mat1 = jednotkova(3, 4);
    matice mat2 = jednotkova(4, 3);

    nastav_prvek(mat1 , 0, 0, 3);
    nastav_prvek(mat1 , 0, 1, 4);
    nastav_prvek(mat1 , 0, 2, 5);
    nastav_prvek(mat1 , 0, 3, 6);
    
    nastav_prvek(mat1 , 1, 0, 4);
    nastav_prvek(mat1 , 1, 1, 5);
    nastav_prvek(mat1 , 1, 2, 6);
    nastav_prvek(mat1 , 1, 3, 7);

    nastav_prvek(mat1 , 2, 0, 3);
    nastav_prvek(mat1 , 2, 1, 5);
    nastav_prvek(mat1 , 2, 2, 7);
    nastav_prvek(mat1 , 2, 3, 8);

    nastav_prvek(mat2 , 0, 0, 2);
    nastav_prvek(mat2 , 0, 1, 3);
    nastav_prvek(mat2 , 0, 2, 2);
    
    nastav_prvek(mat2 , 1, 0, 4);
    nastav_prvek(mat2 , 1, 1, 5);
    nastav_prvek(mat2 , 1, 2, 2);

    nastav_prvek(mat2 , 2, 0, 6);
    nastav_prvek(mat2 , 2, 1, 7);
    nastav_prvek(mat2 , 2, 2, 1);

    nastav_prvek(mat2 , 3, 0, 7);
    nastav_prvek(mat2 , 3, 1, 8);
    nastav_prvek(mat2 , 3, 2, 2);

    printf("%f\n", mat1.data[1][3]);
    vypis(mat1);

    printf("Vynasobime 3x\n");
    vypis(nasobeni(mat1, 3.0));

    printf("\nTranspozice\n");
    matice t = transpozice(mat1);
    vypis(t);

    matice kratpls = krat(mat1, mat2);
    printf("\nmat1:\n");
    vypis(mat1);
    printf("\nmat2:\n");
    vypis(mat2);
    printf("\nNasobeni mat1 a mat2:\n");
    vypis(kratpls);

    zkontroluj_parametry(mat1, 24, 23);
    printf("\n%d", chyba);

    const char *soubor = "/Users/lkral/CLionProjects/xjc/some131233.txt";

    matice matx = nacti_ze_souboru(soubor);

    printf("\n%d", chyba);
    vypis(matx);
    odstran(matx);
}

