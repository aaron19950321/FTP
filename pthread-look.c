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
    int sfd = *((int *)arg);
    char sendbuf[BUFSIZE] = "";
    DIR * dir = opendir("./file/");
    struct dirent * ptr ;
    while((ptr = readdir(dir)) != NULL)
    {
        strcat(sendbuf,ptr->d_name);
        strcat(sendbuf,"-");
    }
    send(sfd,sendbuf,sizeof(sendbuf),0);
    closedir(dir);
}

