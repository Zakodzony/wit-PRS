#include "../include/func.h"
void SystemInfo(void)
{
    struct utsname utsname;
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
    struct passwd *opis;
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
