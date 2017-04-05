/*************************************************************************
	> File Name: server.c
	> Author: aaron
	> Mail: 60360329@163.com
	> Created Time: Thu 30 Mar 2017 01:20:19 PM CST
 ************************************************************************/

#include"hdsokt.h"
#include"func.h"
int main()
{
    /*define the stack var*/
    int sfd;                                                     //for listen
    pthread_t pid[PIDNUM];                                       //pthread's num
    int recvbuf;                                                 //recv choice
    char sendbuf[BUFSIZE] = "";
    char name_pwd[BUFSIZE] = "";
    char name[BUFSIZE] = "";
    char pwd[BUFSIZE] = "";
    //new
    MYSQL conn;
    MYSQL_RES *res_ptr;
    char setBuf[100] = "";
    char sbuf[BUFSIZE] = "";
	//new
    int i;
    int count;                                                   //for count
    int res;                                                     //for return

    fd_set rdset;                                                //select <- fd
    int maxfd;
    //int *c_fd = (int *)malloc(99 * sizeof(int));                 //fd for communication
    int c_fd[99];

    struct sockaddr_in svr_addr,ac_addr;                         //ac_addr is after accept
    int s_len = sizeof(svr_addr); 
    int c_len = sizeof(ac_addr);

    sfd = Initsocket(&svr_addr,4321,"127.0.0.1");

    //listen
    res = listen(sfd,5);
    if (res == -1)
    {
        perror("listen");
        exit(-1);
    }

    //init select
    count = 0;
    maxfd = 0;
    FD_ZERO(&rdset);
    for (i = 0;i < 99; i++)
    {
        c_fd[i] = -1;
    }

    while(1)
    {
        FD_ZERO(&rdset);
        maxfd = 0;
        //listen -> select
        FD_SET(sfd,&rdset);
        maxfd = maxfd >= sfd ? maxfd : sfd;
        //communication -> select
        for(i = 0; i<count ; i++)
        {
            if(c_fd[i] != -1)
            {
                FD_SET(c_fd[i],&rdset);
                maxfd = maxfd >= c_fd[i] ? maxfd : c_fd[i];
            }
        }

        //select -> sntl sir
        res = select(maxfd+1 , &rdset , NULL,NULL,NULL);
        if (res < 0)
        {
            perror("select");
            exit(-1);
        }

        //process every status
        //1 connect news
        if(FD_ISSET(sfd, &rdset))
        {
            c_fd[count] = accept(sfd, (struct sockaddr *)&ac_addr, &c_len);
            if (c_fd[count] > 0)
            {
                count++;
            }
        }
        //2 client send data to server
        for (i = 0;i<count ;i++)
        {
            if(c_fd[i] != -1 && FD_ISSET(c_fd[i], &rdset))
            {
                //login-register
                while(1)
                {
                    res = recv(c_fd[i],&recvbuf,sizeof(recvbuf),0);
                    if(recvbuf == REGISTER)
                    {
                        recv(c_fd[i],&name_pwd,sizeof(name_pwd),0);
                        splite(name_pwd,name,pwd);
                        sprintf(setBuf,"insert into User values('%s','%s')",name,pwd);
                        res = mysql_query(&conn, setBuf);
                        if(res)
                        {
                            strcpy(sbuf,"fail to register");
                            send(c_fd[i],sbuf,sizeof(sbuf),0);
                        }
                        else
                        {
                            strcpy(sbuf,"register success!");
                            send(c_fd[i],sbuf,sizeof(sbuf),0);
                        }
                    }
                    else if(recvbuf == LOGIN)
                    {
                        recv(c_fd[i],&name_pwd,sizeof(name_pwd),0);
                        splite(name_pwd,name,pwd);
                        sprintf(setBuf,"select * from Student where name='%s' and pwd='%s'",name,pwd);
                        res = mysql_query(&conn, setBuf);
                        if(res)
                        {
                            printf("do failed\n");
                            mysql_close(&conn);
                        }
                        else
                        {
                            //检索完整的结果集
                            res_ptr = mysql_store_result(&conn);
                            if(res_ptr)
                            {
                                //返回结果集中的行数
                                res = (unsigned long)mysql_num_rows(res_ptr);
                                if(res == 0)
                                {
                                    strcpy(sbuf,"name or pwd error,login failed!");
                                    send(c_fd[i],sbuf,sizeof(sbuf),0);
                                }
                                else
                                    break;
                            }
                        }
                    }
                }
                res = recv(c_fd[i],&recvbuf,sizeof(int),0);     //recv choice    
                recvbuf = ntohs(recvbuf);
                /*
                 *
                 *recvbuf 
                 *inside the buf there have LOOK .   DOWNLOAD   .  UPLOAD
                 *          define that     0          1           2
                 *
                 */
                if (res == 0)
                {
                    printf("client quit\r\n");
                    close(c_fd[i]);
                    c_fd[i] = -1;
                }

                if (res == -1)
                {
                    perror("recv");
                    close(c_fd[i]);
                    c_fd[i] = -1;
                }

                if(res > 0)
                {
                    switch(recvbuf)
                    {
                        case LOOK :                
                                    if (pthread_create(&pid[i],NULL,thread_funcForLook,(void *)&c_fd[i]) != 0)
                                    {
                                        perror("pthread_Look");
                                        exit(-1);
                                    }
                                    break;
                        case DOWNLOAD :
                                    if (pthread_create(&pid[i],NULL,thread_funcForDownload,(void *)&c_fd[i]) != 0)
                                    {
                                        perror("pthread_create");
                                        exit(-1);
                                    }
                                    break;
                        case UPLOAD :
                                    if (pthread_create(&pid[i],NULL,thread_funcForUpload,(void *)&c_fd[i]) != 0)
                                    {
                                        perror("pthread_create");
                                        exit(-1);
                                    }
                                    break;
                        default : 
                            perror("switch");
                    }
                }
            }
        }
    }

}
