/*************************************************************************
	> File Name: Initsocket.c
	> Author: aaron
	> Mail: 60360329@163.com
	> Created Time: Thu 30 Mar 2017 03:56:51 PM CST
 ************************************************************************/

#include<stdio.h>
#include"hdsokt.h"
/*new fd and bind to return fd*/
int Initsocket(struct sockaddr_in * svr_addr,int port, char *ip)
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if (sfd < 0)
    {
        perror("socket");
        exit(-1);
    }
    int s_len = sizeof(*svr_addr);
    bzero(svr_addr, s_len);

    svr_addr->sin_family = AF_INET;
    svr_addr->sin_port = htons(port);
    inet_pton(AF_INET, ip,&(svr_addr->sin_addr));

    return sfd;
}
 
