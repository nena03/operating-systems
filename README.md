Z.1. Треба направити програм који користи фајлове да прослеђује информације између
процеса детета и родитеља. Програм се покреће са zad1 n и користи редом фајлове input<i>.txt за
i=1,..,n. Родитељски процес креира n деце, а свако дете рачуна збир свих ненегативних чланова
матрице димензија 3x3 из одговарајућег улазног фајла, и резултат уписује у привремени излазни
фајл.
Родитељ чита привремене излазне фајлове, када сва деца заврше са рачунањем. Када прочита све
привремене фајлове, родитељ креира излазни фајл output.txt који треба да садржи податке
сортиране по времену извршавања, у следећем формату:
Време извршавања процеса i, улазна матрица процеса i, збир ненегативних чланова матрице i
Време извршавања процеса j, улазна матрица процеса j, збир ненегативних чланова матрице j


Z.2. Напишите програм који треба да синхронизује m POSIX нити (pthread) које ротирају
квадратну матрицу димензија m x m у смеру казаљке на сату. Програм треба да учита матрицу из
датотеке input.txt и да је ротира за 90 степени у смеру казаљке на сату. Нити треба равномерно да
обрађују делове матрице, а коначни резултат треба уписати у фајл output.txt.
Улаз: 1 2 3 


      4 5 6

      
      7 8 9

      
Излаз: 7 4 1


       8 5 2

       
       9 6 3

       


Z.3. Синхронизовати m pthread нити тако да оне сабирају два n-димензионална вектора.
Свака нит је одговорна за m/n чланова резултујућег вектора. Штампати резултујући вектор као и
време извршавања. Упоредити времена извршавање са једном нити и са више нити. Сматрати да
је број n дељив бројем m.


Z.4. Користећи ExecutorService у Javi имплементирати програм у ком 5 нити узимају
задатке из реда, у ком има места за 10 задатака. У главном програму, на сваких 0.5 секунди
креирати насимучну матрицу са бројевима између 0 и 100, димензија 10x10 и ставити је у ред
задатака. Нити, након што преузму задатак, штампају на екрану своје име, матрицу и збир чланова
на главној дијагонали. Прекинути генерисање матрица након што нити детектују да нека од
генерисаних матица има збир елемената на главној дијагонали који прелази 300
