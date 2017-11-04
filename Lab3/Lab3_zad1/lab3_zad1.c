#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

void mode_to_letters(int mode, char str[]);

int main(int argc, char *argv[])
{
	if(argc == 2)
        {
            const char* const nazwa_pliku=argv[1];
            struct stat buf;
            char tryby[15];
            if(stat(nazwa_pliku,&buf) == 0)
            {
            mode_to_letters(buf.st_mode,tryby);
            printf("Plik: %s\t%s\n",argv[1],tryby);
            return 0;
            }
            else
            {
                perror("stat");
                exit(1);
            }
        }
        else
        {
            printf("Blad: Nie podano nazwy nazwa_pliku\nPoprawne wywolanie: %s [nazwa_pliku]",argv[0]);
            exit(1);
        }	
}


void mode_to_letters(int mode, char str[])
{
	strcpy(str,"----------");

	if(S_ISDIR(mode) ) str[0] = 'd';
	if(S_ISCHR(mode) ) str[0] = 'c';
	if(S_ISBLK(mode) ) str[0] = 'b';

	if(mode & S_IRUSR ) str[1] = 'r';
	if(mode & S_IWUSR ) str[2] = 'w';
	if(mode & S_IXUSR ) str[3] = 'x';

	if(mode & S_IRGRP ) str[4] = 'r';
	if(mode & S_IWGRP ) str[5] = 'w';
	if(mode & S_IXGRP ) str[6] = 'x';

	if(mode & S_IROTH ) str[7] = 'r';
	if(mode & S_IWOTH ) str[8] = 'w';
	if(mode & S_IXOTH ) str[9] = 'x';
} 
