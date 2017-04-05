/*************************************************************************
	> File Name: udp.h
	> Author: aaron
	> Mail: 60360329@163.com
	> Created Time: Thu 30 Mar 2017 10:36:54 AM CST
 ************************************************************************/

#ifndef _UDP_H_
#define _UDP_H_
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<malloc.h>
#include<pthread.h>
#include<fcntl.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<mysql/mysql.h>

#define LOOK 0
#define DOWNLOAD 1
#define UPLOAD 2
#define BUFSIZE 50
#define PIDNUM 20
/*
#define SIGINFAIL 0     //zhuce
#define SIGINSUCC 1
#define LOGINFAIL 2     //denglu
#define LOGINSUCC 3
*/
#define REGISTER 3
#define LOGIN 4
#endif
