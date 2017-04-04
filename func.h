/*************************************************************************
	> File Name: func.h
	> Author: aaron
	> Mail: 60360329@163.com
	> Created Time: Thu 30 Mar 2017 04:29:01 PM CST
 ************************************************************************/

#ifndef _FUNC_H_
#define _FUNC_H_

#include "hdsokt.h"
int Initsocket(struct sockaddr_in * svr_addr,int port, char *ip);


/*
 * pthread func
 */
void *thread_funcForDownload(void *arg);
void *thread_funcForLook(void * arg);
/*
 *For transfer parameter into (void *)arg
 */
void splite(char * const src,char * const outone,char * const outtwo);
void merge(char * const src,char * const inone,char * const intwo);
#endif
