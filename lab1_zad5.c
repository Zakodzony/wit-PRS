/* main.c Zadanie 5 Napisz funkcję, w której wyświetlana jest data za pomocą funkcji ctime().
Napisz funkcję, w której wyświetlana jest data w postaci: dzień.miesiąc.rok godzina korzystając z
funkcji gmtime()oraz localtime(). Czy obydwa czasy są równe?
*/

#include <time.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	errno = 0;
	time_t czas;
	struct tm* ptm;

	if(time(&czas) == -1)
	{
		perror("czas");
		exit(-1);
	}

	printf("ctime:\t\t%s",ctime(&czas));	
	
	ptm = localtime(&czas);	
	printf("localtime:\t%i.%i.%i %i:%i:%i\n",ptm->tm_mday,ptm->tm_mon,
	1900+ptm->tm_year,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
	
	ptm = gmtime(&czas);
	printf("gmtime:\t\t%i.%i.%i %i:%i:%i\n",ptm->tm_mday,ptm->tm_mon,
	1900+ptm->tm_year,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
	return 0;
}
