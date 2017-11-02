#include "../include/func.h"

int main(int argc, char *argv[])
{
	if(argc < 2)
    	{
        fprintf(stderr, "Niepoprawne wywolanie. Za malo parametrow! Wywolanie: %s  -s lub %s -u [username]\n", argv[0]);
        exit(-1);
    	}
    	if(argc > 3)
    	{
        fprintf(stderr, "Niepoprawne wywolanie. Za duzo parametrow! Wywolanie: %s -s lub %s -u [username]\n", argv[0]);
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
