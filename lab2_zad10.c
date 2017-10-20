/*
Zadanie 10
a) Sprawdź jak działa polecenie who.
b) Zapoznaj się ze wstępną wersją polecenia who (pliklab2.tar.gz). Zwróć uwagę na funkcje otwierania pliku,
czytania i zamykania pliku (open, read, close). Zmodyfikuj tę wersję tak, aby wyświetlany wynik przypominał
wynik polecenia who.
Wskazówka: Zmodyfikuj funkcję showinfo() tak, aby wyświetlała informacje tylko o sesjach użytkownika. Napisz
funkcję showtime(), która zamienia czas podany w sekundach na czas w postaci napisu.
c) Uwzględnij możliwość wydawania polecenia w postaci : who am i
*/

//==================UWAGA - BŁĘDY==========================

#include	<stdio.h>
#include	<stdlib.h>
#include	<utmp.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<pwd.h>
#include	<time.h>
#include	<string.h>
#include	<unistd.h>
#define	SHOWHOST	/* include remote machine on output */

int main(int argc, char *argv[])
{
	struct utmp	current_record;	/* read info into here       */
	int		utmpfd;		/* read from this descriptor */
	int		reclen = sizeof(current_record);
	char opcjeA[]="am";
	char opcjeB[]="i";
  //nie sprawdza czy sa argumenty - podejrzane
	char *opcjeC= argv[1];
	char *opcjeD= argv[2];
	char alternatywnie[7]="whoami";
	
	if(argv[1]==NULL){
	if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 ){
		perror( UTMP_FILE );	/* UTMP_FILE is in utmp.h    */
		exit(1);
	}


	while ( read(utmpfd, &current_record, reclen) == reclen )
		show_info(&current_record);
	close(utmpfd);
	return 0;
	}
	if (strcmp(opcjeC,opcjeA) !=0){
	printf("Zly argument: %s", argv[1]);
	printf(" %s\n",argv[2]);
	return 0;
	}
	if(argc<3){
	printf("Za malo argumentow\n");
	return 0;
	}
	if(strcmp(opcjeD,opcjeB) !=0){
	printf("Zly argument: %s", argv[1]);
	printf(" %s\n",argv[2]);
	return 0;
	}
	system(alternatywnie);
	/*char *login;
	if((login = getlogin()) == NULL) {
	printf("Not in /var/run/utmp ?\n");
	perror("getlogin");
	exit(1);
	}
	printf("Login name = %s\n",login);*/
	exit(0);
/* a teraz sie wytlumacze czemu uzylem system(alternatywnie) otorz to co jest zakomentowane jest przykladem z wykladu(Uzytkownik i zasoby strona: 2) ktory niestety nie dziala u mnie na oceaniu tez nie bo sprawdzalem, a wg wykladu efektem powinien byc login osoby ktora 	wykonuje dany proces czyli polecenia who am i, niestety na wyjsciu jest NULL*/

}
/*
 *  show info()
 *	displays contents of the utmp struct in human readable form
 *	*note* these sizes should not be hardwired
 */
show_info( struct utmp *utbufp )
{
	struct passwd *opis;
	if((opis=getpwnam(utbufp->ut_user))==NULL){
		//printf("dupa nie dziala");
		return 0;
	}
	time_t czas= utbufp->ut_time;
	printf("%-8.8s", utbufp->ut_user);	/* the logname	*/
	printf(" ");				/* a space	*/
	printf("%-8.8s", utbufp->ut_line);	/* the tty	*/
	printf(" ");
	showtime(&czas);				/* a space	*/		
	printf(" ");				/* a space	*/
#ifdef	SHOWHOST
	printf("(%s)", utbufp->ut_host);	/* the host	*/
#endif
	printf("\n");				/* newline	*/

}

showtime(time_t *time){
	struct tm *ptm;
	ptm=localtime(time);
	printf(" %d-%d-%d %d:%d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,(ptm->tm_hour)%24, ptm->tm_min);
  //wypluwa zle minuty - do sprawdzenia

}
