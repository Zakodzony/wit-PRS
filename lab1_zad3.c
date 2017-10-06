//main.c

#include <stdio.h>
#include <stdlib.h>
#define ARGMAX

int main(int argc, char* argv[])
{
    char tmp;
    #ifdef ARGMAX2
    if(argc != 3)
    #endif // ARGMAX2
    #ifdef ARGMAX
    if(argc < 3)
    #endif // ARGMAX
    {
        printf("Blad wywolania. Prawidlowe wywolanie: %s parametr1 parametr2...\n", argv[0]);
        return -1;
    }
    else
    {
        printf("Uruchomiony program: %s\n", argv[0]);
        for(int i = 1; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }

    }

    return 0;
}
