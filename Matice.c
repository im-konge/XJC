#include "Matice.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// ############################################
// ###          INICIALIZACE MATIC           ##
// ############################################

matice inicializace(int m, int n) {
    matice init_mat;
    init_mat.m = m;
    init_mat.n = n;
    init_mat.data = malloc(m * sizeof(float*));
    
    for (int i = 0; i < m; i++) {
        init_mat.data[i] = malloc(n * sizeof(float));
    }

    return init_mat;
}

matice nulova(int m, int n) {
    matice mat = inicializace(m, n);
    
    for (int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            mat.data[i][j] = 0.0;
        }
    }

    return mat;
}

matice jednotkova(int m, int n) {
    matice mat = nulova(m, n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                mat.data[i][j] = 1.0;
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
    for (int i = 0; i < mat.m; i++) {
        printf("| ");
        for(int j = 0; j < mat.n; j++) {
            printf("%f ", prvek(mat, i, j));
        }
        printf("|\n");
    }
}

bool zkontroluj_matice(matice mat1, matice mat2) {

}

// ############################################
// ###        POCETNI OPERACE MATIC          ##
// ############################################

matice plus(matice mat1, matice mat2) {
    if (zkontroluj_matice(mat1, mat2)) {
        matice mat3 = inicializace(mat1.m, mat1.n);

        for (int i = 0; i < mat1.m; i++) {
            for (int j = 0; j < mat1.n; j++) {
                mat3.data[i][j] = mat1.data[i][j] + mat2.data[i][j]; 
            }
        }

        return mat3;
    }

    return nulova(mat1.m, mat1.n);
}

matice minus(matice mat1, matice mat2) {
    if (zkontroluj_matice(mat1, mat2)) {
        matice mat3 = inicializace(mat1.m, mat1.n);

        for (int i = 0; i < mat1.m; i++) {
            for (int j = 0; j < mat1.n; j++) {
                nastav_prvek(mat3, i, j, mat1.data[i][j] - mat2.data[i][j]); 
            }
        }

        return mat3;
    }

    return nulova(mat1.m, mat1.n);
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
            t_mat.data[j][i] = prvek(mat1, i, j); 
        }
    }

    return t_mat;
}

matice krat(matice mat1, matice mat2) {
    matice mat3 = nulova(mat1.m, mat2.n);
    
}

matice nacti_ze_souboru(const char *soubor) {
    FILE *file;

    if ((file = fopen(soubor, "r")) == NULL) {

    }

    if (fclose(file) == EOF) {

    }
}

void uloz_do_souboru(matice mat, const char *soubor) {
    FILE *file;

    if ((file = fopen(soubor, "r")) == NULL) {

    }

    if (fclose(file) == EOF) {

    }
}

int velikost(matice mat, int dimenze) {
    switch(dimenze) {
        case 1:
            return mat.m;
        case 2:
            return mat.n;
        default:
        // zde bude chyba
            return 0;
    }
}

float prvek(matice mat, int i, int j) {
    return mat.data[i][j];
}

void nastav_prvek(matice mat, int i, int j, float hodnota) {
    mat.data[i][j] = hodnota;
}