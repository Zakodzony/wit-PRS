#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <errno.h>

void SystemInfo(void);
void UserInfo(char *login); 
#endif
