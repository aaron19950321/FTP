/*************************************************************************
    > File Name: pthread-download.c
    > Author: aaron
    > Mail: 60360329@163.com
    > Created Time: Mon 03 Apr 2017 04:08:00 PM CST
 ************************************************************************/
#include"hdsokt.h"
#include"func.h"
void *thread_funcForDownload(void *arg)
{
    char sendbyyuf[BUFSIZE] = "";
    char sendbufOfchar[5] = "";   //5 char one cir
    char name[BUFSIZE] = "";
    char c_fd[4];  //int c_fd
    int ret;
    //process buf
    splite((char *)arg,c_fd,name);
    //open File
    sprintf(name,"./file/%s",name);      //if open failed  then how to process
    int fd = open(name,O_RDONLY, 0666);
    if (fd < 0)
    {
        perror("open");
        exit(-1);
    }
    else
    {
        printf("open file success");
    }
    //get size
    int size = lseek(fd, 0, SEEK_END);
    if (size < 0)
    {
        perror("lseek");
        exit(-1);
    }
    lseek(fd,0,SEEK_SET);
    if(NULL == strcpy(sendbuf,name))
    {
        perror("strcpy");
        exit(-1);
    }
    //send file name
    ret = send((int)c_fd,sendbuf,sizeof(sendbuf),0);
    if (ret < 0)
    {
        perror("send");
        exit(-1);
    }
    else
        printf("File name was sent!\r\n");
    //send size
    ret = send((int)c_fd,&size,sizeof(int),0);
    if (ret < 0)
    {
        perror("send");
        exit(-1);
    }
    while (size)                                                 //at the client: send size for server 
    {
        ret = read(fd,sendbufOfchar,sizeof(sendbufOfchar));
        printf("take %d charachters\r\n",ret);
        send((int)c_fd,sendbufOfchar,sizeof(sendbufOfchar),0);
        read((int)c_fd, &size,sizeof(int));                     //read size
        printf("size is %d\r\n",size);
        memset(sendbufOfchar,0,sizeof(sendbufOfchar));
    }
    printf("down!\r\n");
    close((int)c_fd);
}
