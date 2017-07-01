/**
 * @file 7.12.03.c
 * @brief sigaction()
 * @author LiWenGang
 * @date 2016-07-12
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

static void sig_usr(int signum){
    if(signum == SIGUSR1){
        printf("SIGUSR1 received\n");
    }else if(signum == SIGUSR2){
        printf("SIGUSR2 received\n");
    }else{
        printf("signal %d received\n", signum);
    }
}

int main(int argc, char* argv[]){
    char buf[512];
    int  n;
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sig_usr;   //信号处理函数

    sigaction(SIGUSR1, &sa_usr, NULL);
    sigaction(SIGUSR2, &sa_usr, NULL);

    printf("My PID is %d\n", getpid());

    while(1){
        if((n = read(STDIN_FILENO, buf, 511)) == -1){
            if(errno == EINTR){
                printf("read is interrupted by signal\n");
            }
        }else{
            buf[n] = '\0';
            printf("%d bytes read: %s\n", n, buf);
        }
    }

    return 0;
}
/*
 * gcc 7.12.03.c -o a.out -Wall -std=c11 -D_POSIX_C_SOURCE
 */
