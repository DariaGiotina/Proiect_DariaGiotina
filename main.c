#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HOMARI 100 // Definim o constanta pentru numarul maxim de homari
#define MAX_CAPACITATE 2000 // Definim o constanta pentru capacitatea maxima a plasei

// Functie pentru a returna maximul dintre doua numere
int maxim(int numar1, int numar2) {
    return (numar1 > numar2) ? numar1 : numar2; // Returneaza numar1 daca este mai mare, altfel returneaza numar2
}

// Functie pentru a afisa homarii selectati
void afisare_homari(int dp[MAX_HOMARI+1][MAX_CAPACITATE+1], int dimensiuni[MAX_HOMARI+1], int valori[MAX_HOMARI+1], int numar_homari, int capacitate_plasa) {
    printf("Homarii inclusi in plasa sunt:\n"); // Mesaj informativ
    int i = numar_homari, j = capacitate_plasa;
    while (i > 0 && j > 0) { // Parcurge matricea dp pentru a determina homarii selectati
        if (dp[i][j] != dp[i - 1][j]) { // Daca valoarea curenta difera de cea anterioara
            printf("Homar %d: Dimensiune = %d, Valoare = %d\n", i, dimensiuni[i], valori[i]); // Afiseaza detalii despre homar
            j -= dimensiuni[i]; // Reduce capacitatea plasei cu dimensiunea homarului selectat
        }
        i--; // Trecem la homarul anterior
    }
}

int main() {
    int numar_homari, capacitate_plasa; // Variabile pentru numarul de homari si capacitatea plasei

    // Initializare generator de numere aleatorii
    srand(time(NULL));

    // Generare numar de homari si capacitate plasa
    numar_homari = MAX_HOMARI; // De exemplu, folosim maximul definit
    capacitate_plasa = rand() % 1000 + 1000; // Capacitate plasa intre 1000 si 2000

    int dimensiuni[MAX_HOMARI+1], valori[MAX_HOMARI+1]; // Vectori pentru dimensiunile si valorile homarilor
    int dp[MAX_HOMARI+1][MAX_CAPACITATE+1]; // Matrice pentru programarea dinamica

    // Generare dimensiuni ale homarilor intre 1 si 100
    for (int i = 1; i <= numar_homari; i++) { // Parcurge homarii
        dimensiuni[i] = rand() % 100 + 1; // Dimensiuni aleatorii intre 1 si 100
    }

    // Generare valori ale homarilor intre 1 si 500
    for (int i = 1; i <= numar_homari; i++) { // Parcurge homarii
        valori[i] = rand() % 500 + 1; // Valori aleatorii intre 1 si 500
    }

    // Initializare si calcul matrice dp pentru programarea dinamica
    for (int i = 0; i <= numar_homari; i++) { // Parcurge numarul de homari
        for (int j = 0; j <= capacitate_plasa; j++) { // Parcurge capacitatea plasei
            if (i == 0 || j == 0) { // Daca nu sunt homari sau capacitatea plasei este zero
                dp[i][j] = 0; // Initializeaza dp cu 0
            } else if (dimensiuni[i] <= j) { // Daca dimensiunea homarului este mai mica sau egala cu capacitatea plasei
                dp[i][j] = maxim(valori[i] + dp[i - 1][j - dimensiuni[i]], dp[i - 1][j]); // Calculam valoarea maxima posibila
            } else { // Altfel
                dp[i][j] = dp[i - 1][j]; // Copiaza valoarea de pe linia anterioara
            }
        }
    }

    printf("Valoarea maxima este: %d\n", dp[numar_homari][capacitate_plasa]); // Afiseaza valoarea maxima a homarilor care incap in plasa
    afisare_homari(dp, dimensiuni, valori, numar_homari, capacitate_plasa); // Apeleaza functia pentru afisarea homarilor inclusi in plasa

    return 0; // Programul s-a incheiat cu succes
}
