/*************************************************************************
	> File Name: pthread-upload.c
	> Author: aaron
	> Mail: 60360329@163.com
	> Created Time: Wed 05 Apr 2017 10:33:03 AM CST
 ************************************************************************/

#include"hdsokt.h"

void *thread_funcForUpload(void *arg)
{
    int sfd = *((int *)arg);
    char sendbuf[BUFSIZE] = "";
    char name[BUFSIZE] = "";
    char sendbufOfchar[5] = "";   //5 char one cir
    int ret;
    //recv Name
    recv(*((int *)arg),name,sizeof(name),0);
    sprintf(name,"./file/%s",name);      //if open failed  then how to process
    int fd = open(name,O_RDWT | O_RDWT, 0666);
    if (fd < 0)
    {
        perror("open");
        exit(-1);
    }
    else
        printf("open file success");
    //send ->ready
    //recv size
    //while(size)
    //recv into recvbuf
    //write into ./file/name

}

