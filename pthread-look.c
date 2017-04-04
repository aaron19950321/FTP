/*************************************************************************
	> File Name: pthread-look.c
	> Author: aaron
	> Mail: 60360329@163.com
	> Created Time: Tue 04 Apr 2017 03:48:01 PM CST
 ************************************************************************/

#include"hdsokt.h"
#include"func.h"
#include<dirent.h>
void *thread_funcForLook(void *arg)
{
    DIR * dir = opendir("./file/");
    struct dirent * ptr ;
    while((ptr = readdir(dir)) != NULL)
    {
        strcat((char *)arg,ptr->d_name);
        strcat((char *)arg,"-");
    }
    closedir(dir);
}

