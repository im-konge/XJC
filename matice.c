#include "matice.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

enum chyby chyba = BEZ_CHYBY;
#define BUFFER_SIZE 128

// ##########################################
// ###          KONTROLNI FUNKCE           ##
// ##########################################

bool zkontroluj_matice(matice mat1, matice mat2, enum operace mat_oper) {
    switch (mat_oper) {
        case PLUS:
        case MINUS:
            if (velikost(mat1, 1) != velikost(mat2, 1) || velikost(mat1, 2) != velikost(mat2, 2)) {
                chyba = CHYBA_TYPU;
                return false;
            }

            chyba = BEZ_CHYBY;
            return true;
        case KRAT:
            if (velikost(mat1, 2) != velikost(mat2, 1)) {
                chyba = CHYBA_TYPU;
                return false;
            }

            chyba = BEZ_CHYBY;
            return true;
        default:
            // pouze v pripade, ze se prida dalsi operace do `enum operace`, pro kterou se neprida kontrola
            chyba = CHYBA_TYPU;
            return false;
    }
}

bool zkontroluj_parametry(matice mat, int i, int j) {
    if (velikost(mat, 1) < i || velikost(mat, 2) < j) {
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
    chyba = BEZ_CHYBY;

    init_mat.m = m;
    init_mat.n = n;
    init_mat.data = malloc(m * sizeof(float*));

    if (init_mat.data == NULL) {
        chyba = CHYBA_ALOKACE;
        return prazdna();
    }

    for (int i = 0; i < m; i++) {
        init_mat.data[i] = malloc(n * sizeof(float));
        if (init_mat.data[i] == NULL) {
            chyba = CHYBA_ALOKACE;
            odstran(init_mat);
            return prazdna();
        }
    }

    return init_mat;
}

matice nulova(int m, int n) {
    matice mat = inicializace(m, n);
    
    if (chyba == CHYBA_ALOKACE) {
        return prazdna();
    }

    for (int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            nastav_prvek(mat, i, j, 0.0);
        }
    }

    return mat;
}

matice jednotkova(int m, int n) {
    matice mat = nulova(m, n);
    
    if (chyba == CHYBA_ALOKACE) {
        return prazdna();
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                nastav_prvek(mat, i, j, 1.0);
            }
        }
    }

    return mat;
}

matice prazdna() {
    matice prazdna_mat;

    prazdna_mat.m = 0;
    prazdna_mat.n = 0;
    prazdna_mat.data = NULL;

    return prazdna_mat;
}

// ############################################
// ###        ZAKLADNI OPERACE MATIC         ##
// ############################################

void odstran(matice mat) {
    for (int i = 0; i < velikost(mat, 1); i++) {
        free(mat.data[i]);
    }

    free(mat.data);
}

void vypis(matice mat) {
    printf("\n");
    
    for (int i = 0; i < velikost(mat, 1); i++) {
        for(int j = 0; j < velikost(mat, 2); j++) {
            printf("%f ", prvek(mat, i, j));
        }
        printf("\n");
    }
    
    printf("\n");
}

// ############################################
// ###        POCETNI OPERACE MATIC          ##
// ############################################

matice plus(matice mat1, matice mat2) {
    if (zkontroluj_matice(mat1, mat2, PLUS)) {
        matice mat3 = inicializace(velikost(mat1, 1), velikost(mat1, 2));

        if (chyba == CHYBA_ALOKACE) {
            return prazdna();
        }

        for (int i = 0; i < velikost(mat1, 1); i++) {
            for (int j = 0; j < velikost(mat1, 2); j++) {
                nastav_prvek(mat3, i, j, prvek(mat1, i, j) + prvek(mat2, i, j));
            }
        }

        return mat3;
    }

    return prazdna();
}

matice minus(matice mat1, matice mat2) {
    if (zkontroluj_matice(mat1, mat2, MINUS)) {
        matice mat3 = inicializace(velikost(mat1, 1), velikost(mat1, 2));

        if (chyba == CHYBA_ALOKACE) {
            return prazdna();
        }

        for (int i = 0; i < velikost(mat1, 1); i++) {
            for (int j = 0; j < velikost(mat1, 2); j++) {
                nastav_prvek(mat3, i, j, prvek(mat1, i, j) - prvek(mat2, i, j)); 
            }
        }

        return mat3;
    }

    return nulova(1, 1);
}

matice nasobeni(matice mat, float skalar) {
    matice mat2 = inicializace(velikost(mat, 1), velikost(mat, 2));

    if (chyba == CHYBA_ALOKACE) {
        return prazdna();
    }

    for (int i = 0; i < velikost(mat, 1); i++) {
        for (int j = 0; j < velikost(mat, 2); j++) {
            nastav_prvek(mat2, i, j, prvek(mat, i, j) * skalar); 
        }
    }

    return mat2;
}

matice transpozice(matice mat1) {
    matice t_mat = nulova(velikost(mat1, 2), velikost(mat1, 1));

    if (chyba == CHYBA_ALOKACE) {
        return prazdna();
    }

    for (int i = 0; i < velikost(mat1, 1); i++) {
        for (int j = 0; j < velikost(mat1, 2); j++) {
            nastav_prvek(t_mat, j, i, prvek(mat1, i, j)); 
        }
    }

    return t_mat;
}

matice krat(matice mat1, matice mat2) {
    if (zkontroluj_matice(mat1, mat2, KRAT)) {
        matice mat3 = nulova(velikost(mat1, 1), velikost(mat2, 2));

        if (chyba == CHYBA_ALOKACE) {
            return prazdna();
        }

        for (int i = 0; i < velikost(mat1, 1); i++) {
            for (int j = 0; j < velikost(mat1, 2); j++) {
                float vysledek = 0.0;

                for (int k = 0; k < velikost(mat2, 1); k++) {
                    vysledek += prvek(mat1, i, k) * prvek(mat2, k, j);
                }

                nastav_prvek(mat3, i, j, vysledek);
            }
        }

        return mat3;
    }

    return prazdna();
}

// ############################################
// ###         OPERACE SE SOUBORY            ##
// ############################################

matice nacti_ze_souboru(const char *soubor) {
    FILE *file;
    chyba = BEZ_CHYBY;

    if ((file = fopen(soubor, "r")) == NULL) {
        chyba = CHYBA_OTEVRENI;
        return prazdna();
    }

    int pocitadlo_hodnot = 0, pocitadlo_m = 0, pocitadlo_n = 0, maximalni_pocet_hodnot = BUFFER_SIZE, n = 0, index = 0;
    char cislo[BUFFER_SIZE] = {0}, znak;
    float* hodnoty = malloc(maximalni_pocet_hodnot * sizeof(float));
    bool prvni_pruchod = true;

    if (hodnoty == NULL) {
        chyba = CHYBA_ALOKACE;
        return prazdna();
    }

    while ((znak = fgetc(file)) != EOF) {
        if (isdigit(znak) || znak == '.') {
            cislo[index++] = znak;
        } else if (znak == ' ' || znak == '\n') {
            if (isdigit(cislo[0])) {
                hodnoty[pocitadlo_hodnot++] = strtof(cislo, NULL);
                index = 0;
                n++;
                memset(cislo, 0, BUFFER_SIZE);
                if (pocitadlo_hodnot == maximalni_pocet_hodnot - 1) {
                    maximalni_pocet_hodnot += BUFFER_SIZE;
                    hodnoty = realloc(hodnoty, maximalni_pocet_hodnot * sizeof(float));

                    if (hodnoty == NULL) {
                        chyba = CHYBA_ALOKACE;
                        return prazdna();
                    }
                }
            }
            if (znak == '\n') {
                pocitadlo_m++;
                if (prvni_pruchod) {
                    pocitadlo_n = n;
                    prvni_pruchod = false;
                } else if (!prvni_pruchod && pocitadlo_n != n) {
                    return prazdna();
                }
                n = 0;
            }
        }
    }

    matice mat = inicializace(pocitadlo_m, pocitadlo_n);

    if (chyba == CHYBA_ALOKACE) {
        free(hodnoty);
        return prazdna();
    }

    int aktualni_m = 0, aktualni_n = 0;

    for (int i = 0; i < pocitadlo_hodnot; i++) {
        if (aktualni_n == pocitadlo_n) {
            aktualni_n = 0;
            aktualni_m++;
        }

        nastav_prvek(mat, aktualni_m, aktualni_n++, hodnoty[i]);
    }

    if (fclose(file) == EOF) {
        chyba = CHYBA_ZAVRENI;
    }

    free(hodnoty);

    return mat;
}

void uloz_do_souboru(matice mat, const char *soubor) {
    FILE *file;
    enum chyby aktualni_chyba = BEZ_CHYBY;

    if ((file = fopen(soubor, "a+")) == NULL) {
        aktualni_chyba = CHYBA_OTEVRENI;
    }
    
    for (int i = 0; i < velikost(mat, 1); i++) {
        for(int j = 0; j < velikost(mat, 2); j++) {
            fprintf(file, "%f ", prvek(mat, i, j));
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\n");

    if (fclose(file) == EOF) {
        aktualni_chyba = CHYBA_ZAVRENI;
    }

    chyba = aktualni_chyba;
}

// ##############################################################
// ###         FUNKCE PRO NEPRIMY PRISTUP K MATICIM            ##
// ##############################################################

int velikost(matice mat, int dimenze) {
    switch(dimenze) {
        case 1:
            return mat.m;
        case 2:
            return mat.n;
        default:
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
