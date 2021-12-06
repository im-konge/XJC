#pragma once

#include <stdbool.h>

typedef struct matice {
    int m;
    int n;
    float **data;
} matice;

matice inicializace(int m, int n);
matice nulova(int m, int n);
matice jednotkova(int m, int n);

void odstran(matice mat);
void vypis(matice mat);
matice plus(matice mat1, matice mat2);
matice minus(matice mat1, matice mat2);
matice nasobeni(matice mat, float skalar);
matice transpozice(matice mat1);
matice krat(matice mat1, matice mat2);
matice nacti_ze_souboru(const char *soubor);
void uloz_do_souboru(matice mat, const char *soubor);
int velikost(matice mat, int dimenze);
float prvek(matice mat, int i, int j);
void nastav_prvek(matice mat, int i, int j, float hodnota);

bool zkontroluj_matice(matice mat1, matice mat2);
matice proved_operaci(matice mat1, matice mat2, char operator);