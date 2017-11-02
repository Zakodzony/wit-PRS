 
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

void showtime(time_t *time);
void show_info(struct utmp *utbufp);

int main(int argc, char *argv[])
{
	if(argv[1]==NULL)
    {
        struct utmp	current_record;	/* read info into here       */
        int utmpfd;		/* read from this descriptor */
        int reclen = sizeof(current_record);
        
        if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 )
        {
            perror( UTMP_FILE );	/* UTMP_FILE is in utmp.h    */
            exit(1);
        }
        
        while ( read(utmpfd, &current_record, reclen) == reclen )
        {
            show_info(&current_record);
        }
        close(utmpfd);
        return 0;
	}
	//kod do obslugi polecenia who am i
	if(argc == 3)
    {
        char optOne[]="am";
        char optTwo[]="i";
        if (strcmp(argv[1],optOne) !=0)
        {
            printf("Zly argument pierwszy: %s", argv[1]);
            printf("Program przyjmuje jako pierwszy argument \"am\"");
            exit(1);
        }
        
        if(strcmp(argv[2],optTwo) !=0)
        {
            printf("Zly argument drugi: %s", argv[2]);
            printf("Program przyjmuje jako drugi argument \"i\"");
            exit(1);
        }
        char *login;
        if((login = getlogin()) == NULL) 
        {
            printf("Not in /var/run/utmp ?\n");
            perror("getlogin");
            exit(1);
        }
        printf("%s\n",login);
    }
    else
    {
        printf("Niepoprawna liczba argumentow: %d\nWprowadz poprawna liczbe argumentow: 2.\n", argc-1);
        exit(1);
    }
    return 0;
}
/*
 *  show info()
 *	displays contents of the utmp struct in human readable form
 *	*note* these sizes should not be hardwired
 */
void show_info(struct utmp *utbufp)
{
	struct passwd *pwd;
	if((pwd=getpwnam(utbufp->ut_user))==NULL)
    {
        //printf("%s\n",utbufp->ut_user);
		//printf("Blad wywolania getpwnam! Program zakonczy dzialanie...\n");
		return;
	}
	time_t time= utbufp->ut_time;
    //zwiekszylem troche rozmiar napisu
	printf("%-12.12s", utbufp->ut_user);	/* the logname	*/
	printf(" ");				/* a space	*/
	printf("%-8.8s", utbufp->ut_line);	/* the tty	*/
	printf(" ");
	showtime(&time);	
	printf(" ");				/* a space	*/
#ifdef	SHOWHOST
	printf("(%s)", utbufp->ut_host);	/* the host	*/
#endif
	printf("\n");				/* newline	*/

}
//dodatkowa funkcja
void showtime(time_t *time){
	struct tm *ptm;
	ptm=localtime(time);
	printf(" %d-%d-%d %d:%d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,(ptm->tm_hour)%24, ptm->tm_min);

}
