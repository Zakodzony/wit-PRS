/*main.c Zadanie 3,4: Napisz program, który wyświetla pełną informację o systemie, w którym został uruchomiony program, podaje nazwę
użytkownika, który uruchomił program, jego UID oraz imię i nazwisko.
Wskazówka: Odszukaj opis funkcji getlogin(), getuid(), getpwent(), getpwuid(), getpwnam(),
uname(), gethostname().
b) Dołącz obsługę błędów funkcji systemowych. Zwróć uwagę na zerowanie zmiennej errno. Dlaczego jest ono
wymagane?Zmodyfikuj program z zadania 3 tak, aby w zależności od zadanych opcji wyświetlał informację o systemie (opcja –s)
lub o podanym użytkowniku (opcja –u nazwa). Wskazówka: użyj funkcji getopt().*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <errno.h>

errno = 0;
struct utsname utsname;
struct passwd *opis;

void SystemInfo(void);
void UserInfo(char *login);

int main(int argc, char *argv[])
{
	if(argc < 2)
    	{
        fprintf(stderr, "Niepoprawne wywolanie. Za malo parametrow! Wywolanie: ./prog4 -s lub ./prog4 -u [username]\n");
        exit(-1);
    	}
    	if(argc > 3)
    	{
        fprintf(stderr, "Niepoprawne wywolanie. Za duzo parametrow! Wywolanie: ./prog4 -s lub ./prog4 -u [username]\n");
        exit(-1);
    	}
	int opt;
	char optstring[] = ":su:";

	while ((opt = getopt(argc,argv,optstring)) !=-1)
  	switch (opt)
	{
  		case 's' :
			SystemInfo();
    		break;
  		case 'u' :
			UserInfo(optarg);
			break;
		case ':' :
			fprintf(stderr,"Brak opcji -%c\n",optopt);
			exit(-1);
			break;
  		case '?' :
  		default :
			fprintf(stderr, "Nieznana opcja\n");
			exit(-1);
			break;
		}
	return EXIT_SUCCESS;
}

void SystemInfo(void)
{
	if (uname (&utsname) == -1)
	{
		perror("uname");
		exit(-1);
	}
	printf ("System:\n");
	printf (" \tsysname: %s\n", utsname.sysname);
	printf (" \tnodename: %s\n", utsname.nodename);
	printf (" \trelease: %s\n", utsname.release);
	printf (" \tversion: %s\n", utsname.version);
	printf (" \tmachine: %s\n\n", utsname.machine);
}

void UserInfo(char *login)
{
	if((opis=getpwnam(login))==NULL)
  	{
		fprintf(stderr,"Uzytkownik: %s nie istnieje.\n",login);
    		exit(-1);
  	}
	printf("Uzytkownik:\n");
	printf("\tuser name: %s\n",opis->pw_name);
	printf("\tUID: %d\n",opis->pw_uid);
	printf("\tGID: %d\n",opis->pw_gid);
	printf("\tgecos: %s\n",opis->pw_gecos);
	printf("\thome dir: %s\n",opis->pw_dir);
	printf("\tshell: %s\n",opis->pw_shell);
}
