#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#define N 10 
#define M 20

int a[N], b[N]; 
int r[N];
pthread_t threads[M];

typedef struct {
    int p;//pocetak vektora
    int z;//kraj vektora
} nit;
void* suma(void* argument) 
{
    nit* podatak = (nit*) argument;//kastovanje u strukturu nit
    for (int i = podatak->p; i < podatak->z; i++) 
    {
        r[i] = a[i] + b[i];
    }
    return NULL;
}
void randomvektori() // kreiranje vektora
{
    srand(time(NULL));// random broj
    for (int i = 0; i < N; i++) 
    {
        a[i] = rand() % 3;
        b[i] = rand() % 6;
    }
}
void print(int* v) // za stampanje vektora
{
    for (int i = 0; i < N; i++) 
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main() {
    randomvektori();
    nit podaci[M];
    int broj = M / N;

    clock_t pocetnovreme = clock();
    for (int i = 0; i < M; i++) {
        podaci[i].p = i * broj;
        podaci[i].z = (i + 1) * broj;
        pthread_create(&threads[i], NULL, suma, &podaci[i]);
    }
    for (int i = 0; i < M; i++) {
        pthread_join(threads[i], NULL);
    }
    print(a);// stampa vektore a i b
    print(b);
    clock_t zavrsenovreme = clock();
    double vreme = (double)(zavrsenovreme - pocetnovreme) / CLOCKS_PER_SEC;
    printf("novodobijeni vektor:\n");
    print(r);
    printf("konacno vreme kompajliranja: %f s\n", vreme);
    clock_t onestart = clock();
    for (int i = 0; i < N; i++) //kad sabiramo vektore uz pomoc jedne niti 
    {
        r[i] = a[i] + b[i];
    }
    clock_t oneend = clock();
    double one = (double)(oneend - onestart) / CLOCKS_PER_SEC;// vreme za jednonitne
    printf("konacan vektor(jednonitni):\n");
    print(r);
    printf("vreme kompajliranja jednonitno: %f, s\n", one); return 0;
}
