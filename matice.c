#include "matice.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

enum chyby chyba = BEZ_CHYBY;

// ##########################################
// ###          KONTROLNI FUNKCE           ##
// ##########################################

bool zkontroluj_matice(matice mat1, matice mat2, enum operace mat_oper) {
    switch (mat_oper) {
        case PLUS:
        case MINUS:
            if (velikost(mat1, 1) != velikost(mat2, 1) || velikost(mat1, 2) != velikost(mat2, 2)) {
                printf("\n[\033[31m\033[1mERROR\033[0m] Matice maji odlisne velikosti. Mat1: %d x %d; Mat2: %d x %d.", mat1.m, mat1.n, mat2.m, mat2.n);
                chyba = CHYBA_TYPU;
                return false;
            }

            chyba = BEZ_CHYBY;
            return true;
        case KRAT:
            if (velikost(mat1, 2) != velikost(mat2, 1)) {
                printf("\n[\033[31m\033[1mERROR\033[0m] Pocet sloupcu prvni matice se musi rovnat poctu radku druhe. Mat1 ma %d sloupcu, Mat2 ma %d radku.", mat1.n, mat2.m);
                chyba = CHYBA_TYPU;
                return false;
            }

            chyba = BEZ_CHYBY;
            return true;
        default:
            // pouze v pripade, ze se prida dalsi operace do `enum operace`, pro kterou se neprida kontrola
            printf("\n[\033[33m\033[1mWARN\033[0m] Neznama operace.");
            chyba = CHYBA_TYPU;
            return false;
    }
}

bool zkontroluj_parametry(matice mat, int i, int j) {
    if (velikost(mat, 1) < i || velikost(mat, 2) < j) {
        printf("\n[\033[31m\033[1mERROR\033[0m] Chyba - matice nema rozmery %d x %d. Rozmery matice: %d x %d.", i, j, mat.m, mat.n);
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

    for (int i = 0; i < velikost(mat, 1); i++) {
        for (int j = 0; j < velikost(mat, 2); j++) {
            nastav_prvek(mat2, i, j, prvek(mat, i, j) * skalar); 
        }
    }

    return mat2;
}

matice transpozice(matice mat1) {
    matice t_mat = nulova(velikost(mat1, 2), velikost(mat1, 1));

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

    if ((file = fopen(soubor, "r")) == NULL) {
        printf("\n[\033[31m\033[1mERROR\033[0m] Chyba pri otevirani souboru.");
        chyba = CHYBA_OTEVRENI;
        return prazdna();
    }

    int pocitadlo_hodnot = 0, pocitadlo_m = 0, pocitadlo_n = 0, maximalni_pocet_hodnot = 128, n = 0, index = 0;
    char cislo[128] = {0}, znak;
    float* hodnoty = malloc(maximalni_pocet_hodnot * sizeof(float));
    bool prvni_pruchod = true;

    if (hodnoty == NULL) {
        printf("\n[\033[31m\033[1mERROR\033[0m] Chyba pri alokaci promenne pro hodnoty nacitane ze souboru.");
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
                memset(cislo, 0, 128);
                if (pocitadlo_hodnot == maximalni_pocet_hodnot - 1) {
                    maximalni_pocet_hodnot += maximalni_pocet_hodnot;
                    hodnoty = realloc(hodnoty, maximalni_pocet_hodnot * sizeof(float));

                    if (hodnoty == NULL) {
                        printf("\n[\033[31m\033[1mERROR\033[0m] Chyba pri alokaci promenne pro hodnoty nacitane ze souboru.");
                        chyba = CHYBA_ALOKACE;
                    }
                }
            }
            if (znak == '\n') {
                pocitadlo_m++;
                if (prvni_pruchod) {
                    pocitadlo_n = n;
                    prvni_pruchod = false;
                } else if (!prvni_pruchod && pocitadlo_n != n) {
                    printf("\n[\033[31m\033[1mERROR\033[0m] Chyba - aktualni pocet zaznamu (%d) na radek matice neodpovida predchozimu (%d).", n, pocitadlo_n);
                    return nulova(1,1);
                }
                n = 0;
            }
        }
    }

    matice mat = inicializace(pocitadlo_m, pocitadlo_n);
    int aktualni_m = 0, aktualni_n = 0;

    for (int i = 0; i < pocitadlo_hodnot; i++) {
        if (aktualni_n == pocitadlo_n) {
            aktualni_n = 0;
            aktualni_m++;
        }

        nastav_prvek(mat, aktualni_m, aktualni_n++, hodnoty[i]);
    }

    if (fclose(file) == EOF) {
        printf("\n[\033[31m\033[1mERROR\033[0m] Chyba pri zavirani souboru.");
        chyba = CHYBA_ZAVRENI;
    }

    free(hodnoty);

    return mat;
}

void uloz_do_souboru(matice mat, const char *soubor) {
    FILE *file;
    enum chyby aktualni_chyba = BEZ_CHYBY;

    if ((file = fopen(soubor, "a+")) == NULL) {
        printf("\n[\033[31m\033[1mERROR\033[0m] Chyba pri otevirani souboru.");
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
        printf("\n[\033[31m\033[1mERROR\033[0m] Chyba pri zavirani souboru.");
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
            printf("\n[\033[31m\033[1mERROR\033[0m] Chyba - dimenze %d neni definovana.", dimenze);
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