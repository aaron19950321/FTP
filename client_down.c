/*************************************************************************
    > File Name: client.c
    > Author: ZhangShifang
    > Mail: zsf@qq.com 
    > Created Time: 2017年03月29日 星期三 13时58分50秒
 ************************************************************************/

#include"hdsokt.h"
#include"func.h"

int main()
{
	struct sockaddr_in s_addr;
	int sfd,fd,size;
	char sendbuf[50] = "";
	char recvbuf[50] = "";
    int choice;
	int res;
	int s_len = sizeof(s_addr);

	bzero(&s_addr,s_len);
	//socket
	sfd = socket(AF_INET,SOCK_STREAM,0);
    if (sfd< 0)
    {
        perror("socket");
        exit(-1);
    }
	//set server's IP & port
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(9999);
	inet_pton(AF_INET,"127.0.0.1",&s_addr.sin_addr);


	res = connect(sfd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr));
    if (res < 0)
    {
        perror("connect");
        exit(-1);
    }
    //send choice
    choice = DOWNLOAD;
    res = send(sfd,&choice,sizeof(choice),0);
    if (res < 0)
    {
        perror("send");
        exit(-1);
    }
    //recv file name
    res = read(sfd,recvbuf,sizeof(recvbuf));
	if(res < 0)
	{
		perror("read");
		exit(-1);
	}
	fd = open(recvbuf,O_RDWR | O_CREAT,0666);
	if (fd < 0)
	{
		perror("open");
		exit(-1);
	}
    //recv size
	read(sfd,&size,sizeof(size));
    memset(recvbuf,0,sizeof(recvbuf));
	while(size != 0)
	{
        while(*recvbuf == '\0')
            read(sfd,recvbuf,sizeof(recvbuf));
        write(fd,recvbuf,sizeof(recvbuf));
        size = size - 5;
        send(sfd,&size,sizeof(int),0);
        memset(recvbuf,0,sizeof(recvbuf));
	}
	printf("%s\r\n",recvbuf);

	close(sfd);
	return 0;
}
