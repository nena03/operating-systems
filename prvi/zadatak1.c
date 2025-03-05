#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
void funkcija(const char* input_file, const char* temp_file, int* sum, int m[3][3]) 
{
    FILE *infile = fopen(input_file, "r");
    FILE *tempfile = fopen(temp_file, "w");
    *sum = 0; //dereferenciranje

    if (infile == NULL) 
    {
        exit(1);
    }
    if (tempfile == NULL) 
    {
        exit(1);
    }
    for (int i = 0; i < 3; i++) 
    {
    
        for (int j = 0; j < 3; j++) 
        {
            fscanf(infile, "%d", &m[i][j]);
            if (m[i][j] >= 0) 
            {
                *sum += m[i][j];
            }
        }
    }

    fprintf(tempfile, "konacan zbir: %d\n", *sum);// derenferenciranje vraca vrednost pokazicaca sum 
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            fprintf(tempfile, "%d ", m[i][j]);
        }
        fprintf(tempfile, "\n");
    }

    fclose(infile);
    fclose(tempfile);
}

int main(int argument, char *ar[]) {
    if (argument < 2) // moram na ulazu da prosledim naziv zadatka i broj n pa zato trazi bar dva argumenta
    {
        return 1;
    }
    pid_t pids[n];
    clock_t start[n], end[n];
    int n = atoi(ar[1]);// konvertuje mi iz ASSCI u intiger drugi argument kako bih ga koristila kao broj
    char temp_files[n][20];// svako dete mora da ima svoj privremen fajl u kome se pise rezultat
    for (int i = 1; i <= n; i++) 
    {
        pid_t pid = fork();
        start[i-1] = clock();

        if (pid == 0) {
            char input_file[20];
            sprintf(input_file, "input%d.txt", i);
            sprintf(temp_files[i-1], "temp%d.txt", i);

            int sum;
            int m[3][3];
            funkcija(input_file, temp_files[i-1], &sum, m);

            exit(0);
        } else if (pid > 0) 
        {
            pids[i-1] = pid;// cuvam pidove da bih ih kasnije sacekala, da ne postanu sirocici
        } else 
        {
            return 1;
        }
    }

    for (int i = 0; i < n; i++) 
    {
        waitpid(pids[i], NULL, 0);//cekam dete
        end[i] = clock();
    }

    FILE *outfile = fopen("output.txt", "w");
    if (outfile == NULL) 
    {
        return 1;
    }

    for (int i = 0; i < n; i++) 
    {
        sprintf(temp_files[i], "temp%d.txt", i+1);
        int sum;
        int m[3][3];
	FILE *tempfile = fopen(temp_files[i], "r");
        if (tempfile == NULL) 
        {
            return 1;
        }

        
        fscanf(tempfile, "konacan zbir: %d", &sum);

        fprintf(outfile, "kompajliralo se za %f s\n", (double)(end[i] - start[i]) / CLOCKS_PER_SEC);
        fprintf(outfile, "nasa matrica izgleda %d:\n", i+1);
        for (int j = 0; j < 3; j++) 
        {
            for (int k = 0; k < 3; k++) 
            {
                fscanf(tempfile, "%d", &m[j][k]);
                fprintf(outfile, "%d ", m[j][k]);
            }
            fprintf(outfile, "\n");
        }
        fprintf(outfile, "konacan zbir: %d\n\n", sum);

        fclose(tempfile);
    }
    fclose(outfile);
    return 0;
}

