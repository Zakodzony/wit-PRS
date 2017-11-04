#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>

void show_stat_info(char *fname, struct stat *buf);
void mode_to_letters(int mode, char *str);
char tryby[15]; 

int main(int argc, char *argv[])
{
    struct stat info;
    if(argc == 3)
    {
        int opcja;
        opcja = getopt(argc, argv, ":r:w:x:");

        if (opcja == -1)
        {
            perror("getopt");
            exit(1);
        }
        
        if(stat(argv[2], &info) != 0)
        {
            perror("stat");
            exit(1);
        }
            
        show_stat_info( argv[1], &info );
        switch (opcja)
        {
            case 'r':
                printf("Opcja czytania:\n");
                printf("Wlasciciel:\t"); (tryby[1]=='r') ? printf("tak\n") : printf("nie\n");
                printf("Grupa:\t\t"); (tryby[4]=='r') ? printf("tak\n") : printf("nie\n");
                printf("Pozostali:\t"); (tryby[7]=='r') ? printf("tak\n") : printf("nie\n");
                break;
            case 'w':
                printf("Opcja zapisu:\n");
                printf("Wlasciciel:\t"); (tryby[2]=='w') ? printf("tak\n") : printf("nie\n");
                printf("Grupa:\t\t"); (tryby[5]=='w') ? printf("tak\n") : printf("nie\n");
                printf("Pozostali:\t"); (tryby[8]=='w') ? printf("tak\n") : printf("nie\n");
                break;
            case 'x':
                printf("Opcja wykonania:\n");
                printf("Wlasciciel:\t"); (tryby[3]=='x') ? printf("tak\n") : printf("nie\n");
                printf("Grupa:\t\t"); (tryby[6]=='x') ? printf("tak\n") : printf("nie\n");
                printf("Pozostali:\t"); (tryby[9]=='x') ? printf("tak\n") : printf("nie\n");
                break;
            default:
                return(1);
        }
        return 0;
    }
    else
    {
        printf("Niewlasciwa liczba argumentow. Poprawne wywolanie: %s -[r/w/x] [nazwa_pliku]\n", argv[0]);
        exit(1);
    }
}

void show_stat_info(char *fname, struct stat *buf)
{
    mode_to_letters(buf->st_mode,tryby);
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


