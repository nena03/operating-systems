
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
int m;
#define K 100
#define V 100
int m1[V][K];
int m2[V][K];

typedef struct {
    int p;
    int z;
    int id;
} thread;

void *funkcija(void *argument) 
{
    thread *nova = (thread *)argument;//pretvaram argument u tip podataka thread kastovanje
    int i, j;
    for (i = nova->p; i < nova->z; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            m2[j][m - 1 - i] = m1[i][j];
        }
    }
    pthread_exit(NULL);// zavrsava rad trenutnog threda
}

void unesi(const char *fajl) 
{
    FILE *fajl1 = fopen(fajl, "r");
    if (fajl1 == NULL) {
        exit(EXIT_FAILURE);
    }
    
    m = 0;
    char red[V * 10];
    if (fgets(red, sizeof(red), fajl1)) //cita prvu liniju fajla to jest prvi red i smesta u "red"
    {
        char *pokazivac = red;
        while (sscanf(pokazivac, "%d", &m1[0][m]) == 1) //ako pronadje da je taj karakter celobrojna vrednost, redom popunjava prvi red
        {
            pokazivac += strcspn(pokazivac, " ") + 1;// pokazivac pomeramo na sld karakter, cim naidje na razmak
            m++;// uvecavamo br kolona i tako nadjemo na kraju ukupan broj m
        }
    }
    
    for (int i = 1; i < m; i++) // sad samo popunimo ostatak matrice citajuci ostale karaktere sad kad znamo velicinu kvadratne matrice
    {
        for (int j = 0; j < m; j++) 
        {
            fscanf(fajl1, "%d", &m1[i][j]);
        }
    }
    
    fclose(fajl1);
}

void print(const char *fajl) //funkcija za upisivanje matrice u fajl
{
    FILE *fajl1 = fopen(fajl, "w");
    if (fajl1 == NULL) 
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            fprintf(fajl1, "%d ", m2[i][j]);
        }
        fprintf(fajl1, "\n");
    }
    fclose(fajl1);
}

int main() {
    unesi("input.txt");
    pthread_t threads[m];
    thread podaci[m];
    for (int i = 0; i < m; i++) 
    {
        podaci[i].z = (i + 1);
        podaci[i].id = i;
        podaci[i].p = i;
        pthread_create(&threads[i], NULL, funkcija, &podaci[i]);
    }
    for (int i = 0; i < m; i++) 
    {
        pthread_join(threads[i], NULL);// cekamo niti, jedna po jedna da obave svoj posao
    }

    print("output.txt");// stampamo rezultat u fajl output.txt

    return 0;
}
