#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc,char *argv[]) 
{  
    if (argc != 2) 
	{
		printf("Skladnia polecenia:\n %s [czas w sekundach]\n",argv[0]);
        printf("Nastapi zamkniecie programu.\n");
		exit(-1);
	}
	int optA = 0;
	if((optA = atoi(argv[1])) == 0)
    {
        printf("Niepoprawny parametr: %s\n",argv[1]);
        printf("Nastapi zamkniecie programu.\n");
        exit(-1);
    }
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    sleep(optA);
    gettimeofday(&tv2, NULL);

    printf ("Czas wykonania funkcji: %f sekund\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}
