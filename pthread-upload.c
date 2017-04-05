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
    char recvbuf[BUFSIZE] = "";
    char sendbuf[BUFSIZE] = "";
    char name[BUFSIZE] = "";
    char recvbufOfchar[5] = "";   //5 char one cir
    int ret;
    int size = 0;
    //recv Name
    recv(*((int *)arg),name,sizeof(name),0);
    sprintf(name,"./file/%s",name);      //if open failed  then how to process
    int fd = open(name,O_RDWR | O_CREAT, 0666);
    if (fd < 0)
    {
        perror("open");
        exit(-1);
    }
    else
        printf("open file success");
    //send ->ready
    strcpy(sendbuf,"ready");
    send(sfd,sendbuf,sizeof(sendbuf),0);
    //recv size
    recv(sfd,&size,sizeof(int),0);
    size = ntohs(size);

    while (size)                                                 //at the client: send size for server 
    {
        ret = recv(sfd,recvbufOfchar,sizeof(recvbufOfchar),0);
        printf("recv %d charachters\r\n",ret);
        write(fd,recvbufOfchar,sizeof(recvbufOfchar));
        size = size - sizeof(recvbufOfchar);
        size = htons(size);
        send(sfd,&size,sizeof(int),0);
        memset(recvbufOfchar,0,sizeof(recvbufOfchar));
    }
    printf("down!\r\n");
    close(sfd);

}

