#include "Matice.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum chyby chyba = BEZ_CHYBY;

bool zkontroluj_matice(matice mat1, matice mat2, enum operace mat_oper) {
    switch (mat_oper) {
        case PLUS:
        case MINUS:
            if (mat1.m != mat2.m || mat1.n != mat2.n) {
                printf("[\033[31m\033[1mERROR\033[0m] Matice maji odlisne velikosti. Mat1: %d x %d; Mat2: %d x %d", mat1.m, mat1.n, mat2.m, mat2.n);
                chyba = CHYBA_TYPU;
                return false;
            }

            chyba = BEZ_CHYBY;
            return true;
        case KRAT:
            if (mat1.n != mat2.m) {
                printf("[\033[31m\033[1mERROR\033[0m] Pocet sloupcu prvni matice se musi rovnat poctu radku druhe. Mat1 ma %d sloupcu, Mat2 ma %d radku", mat1.n, mat2.m);
                chyba = CHYBA_TYPU;
                return false;
            }

            chyba = BEZ_CHYBY;
            return true;
        default:
            // pouze v pripade, ze se prida dalsi operace do `enum operace`, pro kterou se neprida kontrola
            printf("[\033[33m\033[1mWARN\033[0m] Neznama operace.");
            chyba = CHYBA_TYPU;
            return false;
    }
}

bool zkontroluj_parametry(matice mat, int i, int j) {
    if (mat.m < i || mat.n < j) {
        printf("[\033[31m\033[1mERROR\033[0m] Chyba - matice nema rozmery %d x %d. Rozmery matice: %d x %d", i, j, mat.m, mat.n);
        chyba = CHYBA_TYPU;
        return false;
    }

    chyba = BEZ_CHYBY;
    return true;
}

// ############################################
// ###          INICIALIZACE MATIC           ##
// ############################################

matice inicializace(int m, int n) {
    matice init_mat;
    enum chyby aktualni_chyba = BEZ_CHYBY;

    init_mat.m = m;
    init_mat.n = n;
    init_mat.data = malloc(m * sizeof(float*));

    if (init_mat.data == NULL) {
        aktualni_chyba = CHYBA_ALOKACE;
    }

    for (int i = 0; i < m; i++) {
        init_mat.data[i] = malloc(n * sizeof(float));
        if (init_mat.data[i] == NULL) {
            aktualni_chyba = CHYBA_ALOKACE;
        }
    }

    // v pripade, ze pri minulem pruchodu funkci `inicializace()` nastala chyba alokace, ale aktualni ne, chceme nastavit
    // globalni promennou `chyba` na novou hodnotu - jinym jednodussim zpusobem nelze zjistit
    chyba = aktualni_chyba;
    return init_mat;
}

matice nulova(int m, int n) {
    matice mat = inicializace(m, n);
    
    for (int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            nastav_prvek(mat, i, j, 0.0);
        }
    }

    return mat;
}

matice jednotkova(int m, int n) {
    matice mat = nulova(m, n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                nastav_prvek(mat, i, j, 1.0);
            }
        }
    }

    return mat;
}

// ############################################
// ###        ZAKLADNI OPERACE MATIC         ##
// ############################################

void odstran(matice mat) {
    for (int i = 0; i < mat.m; i++) {
        free(mat.data[i]);
    }

    free(mat.data);
}

void vypis(matice mat) {
    printf("\n");
    
    for (int i = 0; i < mat.m; i++) {
        printf("\033[33m|\033[0m ");
        for(int j = 0; j < mat.n; j++) {
            printf("%f ", prvek(mat, i, j));
        }
        printf("\033[33m|\033[0m\n");
    }
    
    printf("\n");
}

// ############################################
// ###        POCETNI OPERACE MATIC          ##
// ############################################

matice plus(matice mat1, matice mat2) {
    if (zkontroluj_matice(mat1, mat2, PLUS)) {
        matice mat3 = inicializace(mat1.m, mat1.n);

        for (int i = 0; i < mat1.m; i++) {
            for (int j = 0; j < mat1.n; j++) {
                nastav_prvek(mat3, i, j, mat1.data[i][j] + mat2.data[i][j]);
            }
        }

        return mat3;
    }

    return nulova(1, 1);
}

matice minus(matice mat1, matice mat2) {
    if (zkontroluj_matice(mat1, mat2, MINUS)) {
        matice mat3 = inicializace(mat1.m, mat1.n);

        for (int i = 0; i < mat1.m; i++) {
            for (int j = 0; j < mat1.n; j++) {
                nastav_prvek(mat3, i, j, mat1.data[i][j] - mat2.data[i][j]); 
            }
        }

        return mat3;
    }

    return nulova(1, 1);
}

matice nasobeni(matice mat, float skalar) {
    matice mat2 = inicializace(mat.m, mat.n);

    for (int i = 0; i < mat.m; i++) {
        for (int j = 0; j < mat.n; j++) {
            nastav_prvek(mat2, i, j, prvek(mat, i, j) * skalar); 
        }
    }

    return mat2;
}

matice transpozice(matice mat1) {
    matice t_mat = nulova(mat1.n, mat1.m);

    for (int i = 0; i < mat1.m; i++) {
        for (int j = 0; j < mat1.n; j++) {
            nastav_prvek(t_mat, j, i, prvek(mat1, i, j)); 
        }
    }

    return t_mat;
}

matice krat(matice mat1, matice mat2) {
    if (zkontroluj_matice(mat1, mat2, KRAT)) {
        matice mat3 = nulova(mat1.m, mat2.n);
        for (int i = 0; i < mat1.m; i++) {
            for (int j = 0; j < mat1.n; j++) {
                float vysledek = 0.0;

                for (int k = 0; k < mat2.m; k++) {
                    vysledek += prvek(mat1, i, k) * prvek(mat2, k, j);
                }

                nastav_prvek(mat3, i, j, vysledek);
            }
        }

        return mat3;
    }

    return nulova(1,1);
}

matice nacti_ze_souboru(const char *soubor) {
    FILE *file;

    if ((file = fopen(soubor, "r")) == NULL) {
        printf("[\033[31m\033[1mERROR\033[0m] Chyba pri otevirani souboru.");
        chyba = CHYBA_OTEVRENI;
        return nulova(1, 1);
    }

    matice mat;

    if (fclose(file) == EOF) {
        printf("[\033[31m\033[1mERROR\033[0m] Chyba pri zavirani souboru.");
        chyba = CHYBA_ZAVRENI;
    }

    return mat;
}

void uloz_do_souboru(matice mat, const char *soubor) {
    FILE *file;
    enum chyby aktualni_chyba = BEZ_CHYBY;

    if ((file = fopen(soubor, "a+")) == NULL) {
        printf("[\033[31m\033[1mERROR\033[0m] Chyba pri otevirani souboru.");
        aktualni_chyba = CHYBA_OTEVRENI;
    }
    
    for (int i = 0; i < mat.m; i++) {
        fprintf(file, "| ");
        for(int j = 0; j < mat.n; j++) {
            fprintf(file, "%f ", prvek(mat, i, j));
        }
        fprintf(file, "|\n");
    }

    fprintf(file, "\n");

    if (fclose(file) == EOF) {
        printf("[\033[31m\033[1mERROR\033[0m] Chyba pri zavirani souboru.");
        aktualni_chyba = CHYBA_ZAVRENI;
    }

    chyba = aktualni_chyba;
}

int velikost(matice mat, int dimenze) {
    switch(dimenze) {
        case 1:
            return mat.m;
        case 2:
            return mat.n;
        default:
            printf("[\033[31m\033[1mERROR\033[0m] Chyba - dimenze %d neni definovana.", dimenze);
            chyba = CHYBA_JINA;
            return 0;
    }
}

float prvek(matice mat, int i, int j) {
    return zkontroluj_parametry(mat, i, j) ? mat.data[i][j] : 0.0;
}

void nastav_prvek(matice mat, int i, int j, float hodnota) {
    if (zkontroluj_parametry(mat, i, j)) {
        mat.data[i][j] = hodnota;
    }
}