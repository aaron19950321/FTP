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
    char nameOfDir[BUFSIZE] ="";
    char name[BUFSIZE];
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

    sfd = Initsocket(&svr_addr,9999,"127.0.0.1");

    //listen
    res = listen(sfd,5);
    if (res == -1)
    {
        perror("listen");
        exit(-1);
    }

    //init select
    count = 0;
    memset(c_fd,-1,sizeof(c_fd));

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
                /*
                 *sql
                 *send -> client to begin
                 *while(~DLsuccess)
                 *recv <- choice (zhuce,denglu)
                 *if zhuce then recv <-name pwd ,and insert to sql ,if success set fail=0,send ->zhuce'success.client (1)
                 *if denglu then recv <-name pwd ,and select   ,if insert DLsuccess ...
                 *
                 *if success ,then recv choice
                 */
                res = recv(c_fd[i],&recvbuf,sizeof(int),0);     //recv choice    
                /*
                 *
                 *recvbuf 
                 *inside the buf there have LOOK .   DOWNLOAD   .  UPLOAD
                 *          define that
                 *                           0        1            2
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
