#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>

char uname_container[100];
char ugrp_container[100];

void show_stat_info(char *fname, struct stat *buf);
void mode_to_letters(int mode, char *str);
char* GetUser(uid_t uid);
char* GetGroup(gid_t gid);
char* mode_to_type( char* fname);


int main(int argc, char *argv[])
{
    struct stat info;   
    if (argc>1) {
      if( stat(argv[1], &info) != -1 ){
            show_stat_info( argv[1], &info );
            return 0;
      }
    }
    else
      printf("Uzycie: %s nazwa_pliku\n",argv[0]);  
    return 1;
}
void show_stat_info(char *fname, struct stat *buf)
{
    char tryby[15];
    printf("File name: %s\n",fname);
    printf("File type:%s\n",mode_to_type(fname));
    mode_to_letters(buf->st_mode,tryby);
    printf("\tMode: %s\n", tryby) ;         /* type + mode */
    printf("\tlinks: %ld\n", buf->st_nlink);        /* # links     */
    printf("\tuser (UID):%s (%d)\n",GetUser(buf->st_uid), buf->st_uid);          /* user id     */
    printf("\tgroup (GID):%s (%d)\n",GetGroup(buf->st_gid),buf->st_gid);          /* group id    */
    printf("\tsize: %ld\n", buf->st_size);         /* file size   */
    //printf("modtime: %ld\n", buf->st_mtime);        /* modified    */
    printf("Accessed: %s", ctime(&(buf->st_atime)));        
    printf("Modified: %s", ctime(&(buf->st_mtime))); 
    printf("Changed: %s", ctime(&(buf->st_ctime))); 
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

char* GetUser(uid_t uid)
{
	struct passwd *pwd;
	setpwent();
	pwd=getpwuid(uid);
	strcpy(uname_container,pwd->pw_name);
	endpwent();
	return uname_container;
}

char* GetGroup(gid_t gid)
{
	struct group *pwd;
	setgrent();
	pwd=getgrgid(gid);
	strcpy(ugrp_container,pwd->gr_name);
	endgrent();
	return ugrp_container;
}

char * mode_to_type( char* fname)
{
	struct stat buf;
	char *ptr;
	lstat(fname, &buf);
	if (S_ISREG(buf.st_mode)) ptr = "zwykly";	     
	else if (S_ISDIR(buf.st_mode)) ptr = "katalog";
	else if (S_ISCHR(buf.st_mode)) ptr = "specjalny znakowy";
	else if (S_ISBLK(buf.st_mode)) ptr = "specjalny blokowy";	
	else if (S_ISFIFO(buf.st_mode)) ptr = "fifo";	
	#ifdef S_ISLNK
	else if (S_ISLNK(buf.st_mode)) ptr = "dowiazanie";
	#endif	
	#ifdef S_ISSOCK
	else if (S_ISSOCK(buf.st_mode)) ptr = "gniazdo";
	#endif
	else ptr = "** nieznany typ pliku **";
	return ptr;
} 
