#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <getopt.h>

#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void show_stat_info(char *fname, struct stat *buf);
char *mode_to_perm(int mode);
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);
void do_ls(char []);
void longlist ( char dirname[] );
void showtime(time_t timeval);

char str[12];

int main(int argc, char *argv[])
{
	int opcja;

	opcja = getopt(argc, argv, "l");
	if (opcja == -1)
	{
		 do_ls( "." );
		return(1);
	}

	switch (opcja)
	{
		case 'l':
			longlist(".");
			break;
		default:
			do_ls( "." );
			return(1);
	}
  return 0;
}

void do_ls( char dirname[] )
{
  DIR *dir_ptr;    /* katalog */
  struct dirent *direntp;    /* wpis w katalogu */

  if ( ( dir_ptr = opendir( dirname ) ) == NULL )
    fprintf(stderr,"ls1: cannot open %s\n", dirname);
  else
  {
    while ( ( direntp = readdir( dir_ptr ) ) != NULL )
      printf("%s\n", direntp->d_name );
    closedir(dir_ptr);
  }
}

void longlist ( char dirname[] )
{
	printf ("Long list of directory %s\n",dirname);  
  	struct stat info;
 	DIR *dir_ptr;
  	struct dirent *direntp;

  	if ( ( dir_ptr = opendir( dirname ) ) == NULL )
    	fprintf(stderr,"ls1: cannot open %s\n", dirname);
  	else
  	{
    		while ( ( direntp = readdir( dir_ptr ) ) != NULL )
		{    
      			if( stat(direntp->d_name, &info) != -1 ){
      				show_stat_info( direntp->d_name, &info); 
      		}
     	}
        closedir(dir_ptr);
  }

};

void show_stat_info(char* fname, struct stat *buf)
{ 
	printf("%s ",mode_to_perm(buf->st_mode)); 
	printf("%s %s ", uid_to_name(buf->st_uid), gid_to_name(buf->st_gid)); 
	printf("%ld ", buf->st_size);
	showtime(buf->st_mtime);
	printf ("%s \n",fname);
}

void showtime(time_t timeval) 
{
	struct tm *cp; 
	cp = localtime(&timeval);
	char time_string[40];
	strftime(time_string,sizeof(time_string),"%Y-%m-%d %H:%M ",cp);		
	printf("%s ", time_string); 

}

char *mode_to_perm(int mode)
{
	strcpy( str, "----------" );

	if ( S_ISDIR(mode) ) str[0] = 'd';
	if ( S_ISCHR(mode) ) str[0] = 'c';
	if ( S_ISBLK(mode) ) str[0] = 'b';

	if ( mode & S_IRUSR ) str[1] = 'r';
	if ( mode & S_IWUSR ) str[2] = 'w';
	if ( mode & S_IXUSR ) str[3] = 'x';

	if ( mode & S_IRGRP ) str[4] = 'r';
	if ( mode & S_IWGRP ) str[5] = 'w';
	if ( mode & S_IXGRP ) str[6] = 'x';

	if ( mode & S_IROTH ) str[7] = 'r';
	if ( mode & S_IWOTH ) str[8] = 'w';
	if ( mode & S_IXOTH ) str[9] = 'x';

	if ( mode & S_ISUID ) str[2] = 's';
	if ( mode & S_ISGID ) str[5] = 'S';
	if ( mode & S_ISVTX ) str[8] = 'T';
	return str;
} 

char* uid_to_name(uid_t uid)
{	
	struct passwd *pwd;
	setpwent();
	pwd=getpwuid(uid);	
	endpwent();
	return pwd->pw_name;
}

char* gid_to_name(gid_t gid)
{
	struct group *pwd;
	setgrent();
	pwd=getgrgid(gid);	;
	endgrent();
	return pwd->gr_name;
} 
