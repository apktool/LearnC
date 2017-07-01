/**
 * @file 7.07.05.c
 * @brief 信号量
 * @author LiWenGang
 * @date 2016-10-11
 */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define THREAD_NUM 3
#define REPEAT_TIMES 5
#define DELAY 4

sem_t sem[THREAD_NUM];

void *thrd_func(void *arg);

int main(){
    pthread_t thread[THREAD_NUM];
    int no;
    void *tret;
    
    srand((int)time(0)); 

    // 初始化THREAD_NUM-1个信号量，均初始化为0
    for(no=0;no<THREAD_NUM-1;no++){
        sem_init(&sem[no],0,0);
    }

    // sem[2]信号量初始化为1，即sem数组中最后一个信号量
    sem_init(&sem[2],0,1);
    
    // 创建THREAD_NUM个线程，入口函数均为thrd_func，参数为(void*)no
    for(no=0;no<THREAD_NUM;no++){
        if (pthread_create(&thread[no],NULL,thrd_func,(void*)(long)no)!=0) {
            printf("Create thread %d error!\n",no);
            exit(1);
        } else
            printf("Create thread %d success!\n",no);
    }
    
    // 逐个join掉THREAD_NUM个线程
    for(no=0;no<THREAD_NUM;no++){
        if (pthread_join(thread[no],&tret)!=0){
            printf("Join thread %d error!\n",no);
            exit(1);
        }else
            printf("Join thread %d success!\n",no);
    }
    
    // 逐个取消信号量
    for(no=0;no<THREAD_NUM;no++){
        sem_destroy(&sem[no]);
    }

    return 0;
}

void *thrd_func(void *arg){
    int thrd_num=(long)arg; // 参数no
    int delay_time,count;

    // 带有阻塞的p操作
    sem_wait(&sem[thrd_num]);

    
    printf("Thread %d is starting.\n",thrd_num);
    for(count=0;count<REPEAT_TIMES;count++) {
        delay_time=(int)(DELAY*(rand()/(double)RAND_MAX))+1;
        sleep(delay_time);
        printf("\tThread %d:job %d delay =%d.\n",thrd_num,count,delay_time);
    }

    printf("Thread %d is exiting.\n",thrd_num);
    
    // 对前一个信号量进行V操作
    // 由于只有最后一个信号量初始化为1，其余均为0
    // 故线程执行的顺序将为逆序
    sem_post(&sem[(thrd_num+THREAD_NUM-1)%THREAD_NUM]);

    pthread_exit(NULL); // 线程主动结束
}

/*
 * 信号量
 *		操作系统中所用到的PV原子操作，广泛用于进程或线程间的同步与互斥
 *			•本质上是一个非负的整数计数器，被用来控制对公共资源的访问
 *		PV原子操作：对整数计数器信号量sem的操作
 *			•一次P操作使sem减一，而一次V操作使sem加一
 *			•进程（或线程）根据信号量的值来判断是否对公共资源具有访问权限
 *		–当信号量sem的值大于等于零时，该进程（或线程）具有公共资源的访问权限
 *		–当信号量sem的值小于零时，该进程（或线程）就将阻塞直到信号量sem的值大于等于0为止
 *  
 *  PV操作主要用于线程间的同步和互斥
 *  　　互斥，几个线程只设置一个信号量sem
 *  　　同步，会设置多个信号量，安排不同初值来实现它们之间的顺序执行
 *
 *  信号量函数
 *		sem_init() 创建一个信号量，并初始化它
 *		sem_wait()和sem_trywait(): P操作，在信号量大于零时将信号量的值减一
 *			 •区别: 若信号量小于零时，sem_wait()将会阻塞线程,sem_trywait()则会立即返回
 *		sem_post(): V操作，将信号量的值加一同时发出信号来唤醒等待的线程
 *		sem_getvalue(): 得到信号量的值
 *		sem_destroy(): 删除信号量
 */
