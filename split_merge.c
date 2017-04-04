/*************************************************************************
	> File Name: split_merge.c
	> Author: aaron
	> Mail: 60360329@163.com
	> Created Time: Mon 03 Apr 2017 04:25:29 PM CST
 ************************************************************************/

#include"hdsokt.h"
/*
 *src  ,it will splite src'string 
 *      and return outone,outtwo . 
 *       splite into two piece of string.
 */
void splite(char * const src,char * const outone,char * const outtwo)
{
    char *p = src;
    char *q1 = outone;
    char *q2 = outtwo;
    while( *p != '#' )
    {
        *q1++ = *p++;
    }
    p++;
    while( *p != '\0' )
    {
        *q2++ = *p++;
    }
}


void merge(char * const src,char * const inone,char * const intwo)
{
    strcpy(src,inone);
    strcat(src,"#");
    strcat(src,intwo);
}
