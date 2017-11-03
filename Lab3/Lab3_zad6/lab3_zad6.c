#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define BUF 255

int split (char *str, char c, char ***arr);

int main (int ac, char *av[])
{
    
    char pth[BUF];
    if (ac != 2)
    {
        printf("Poprawne wywolanie programu: ./%s nazwa_programu\n", av[0]);
        exit(1);
    }
    if(strcpy(pth, getenv("PATH")) != NULL)
    {
        printf("[DEBUG]: Zmienna PATH odnaleziona. Zawartosc:\n%s\n",pth);
        int i;
        int c = 0;
        char **arr = NULL;

        c = split(pth, ':', &arr);

        printf("[DEBUG]: Odnaleziono %d sciezek w zmiennej PATH.\n", c);

        for (i = 0; i < c; i++)
        {
            char temp[100] = "";
            strcat(temp,arr[i]);
            strcat(temp,"/");
            strcat(temp,av[1]);
            if((access(temp,F_OK))==0)
            {
                printf("%s\n",temp);
                return 0;
            }
            
        }
        printf("Nie odnaleziono polecenia lub nie masz uprawnien do jego wykonania...\n");

        return 0;
    }
    else
    {
        printf("Nie odnaleziono zmiennej PATH!");
        exit(1);
    }
    return 0;
} 

int split (char *str, char c, char ***arr)
{
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}
    
