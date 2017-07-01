/**
 * @file 7.07.04.c
 * @brief 线程互斥锁
 * @author LiWenGang
 * @date 2016-10-11
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define THREAD_NUM 3
#define REPEAT_TIMES 5
#define DELAY 4

pthread_mutex_t mutex;

void *thrd_func(void *arg);

int main(){
    pthread_t thread[THREAD_NUM];
    void *tret;

       // 创建快速互斥锁（默认），锁的编号返回给mutex
    pthread_mutex_init(&mutex,NULL);

    // 创建THREAD_NUM个线程，每个线程号返回给&thread[i]，每个线程的入口函数均为thrd_func，参数为
    for(int i=0;i<THREAD_NUM;i++){
        if (pthread_create(&thread[i],NULL,thrd_func,(void*)(long)i)!=0) {
            printf("Create thread %d error!\n",i);
            exit(1);
        } else
            printf("Create thread %d success!\n",i);
    }

    // 对每个线程进行join，返回值给tret
    for(int i=0;i<THREAD_NUM;i++){
        if (pthread_join(thread[i],&tret)!=0){
            printf("Join thread %d error!\n",i);
            exit(1);
        }else
            printf("Join thread %d success!\n",i);
    }
    // 消除互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *thrd_func(void *arg){
    long int thrd_num=(long)arg; // 传入的参数，互斥锁的编号
    int delay_time,count;

    srand((int)time(0));

    // 对互斥锁上锁
    if(pthread_mutex_lock(&mutex)!=0) {
        printf("Thread %ld lock failed!\n",thrd_num);
        pthread_exit(NULL);
    }

    printf("Thread %ld is starting.\n",thrd_num);
    for(count=0;count<REPEAT_TIMES;count++) {
        delay_time=(int)(DELAY*(rand()/(double)RAND_MAX))+1;
        sleep(delay_time);
        printf("\tThread %ld:job %d delay =%d.\n",thrd_num,count,delay_time);
    }

    printf("Thread %ld is exiting.\n",thrd_num);
    // 解锁
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

/* 互斥锁
 * 　　用简单的加锁方法控制对共享资源的原子操作
 * 　　只有两种状态: 上锁、解锁
 * 可把互斥锁看作某种意义上的全局变量
 * 　　在同一时刻只能有一个线程掌握某个互斥锁，拥有上锁状态的线程能够对共享资源进行操作
 * 　　若其他线程希望上锁一个已经被上锁的互斥锁,则该线程就会挂起，直到上锁的线程释放掉互斥锁为止
 * 互斥锁保证让每个线程对共享资源按顺序进行原子操作
 *
 *
 *   互斥锁分类
 *   　　区别在于其他未占有互斥锁的线程在希望得到互斥锁时是否需要阻塞等待
 *   　　快速互斥锁
 *			•调用线程会阻塞直至拥有互斥锁的线程解锁为止
 *			•默认为快速互斥锁
 *   　　检错互斥锁
			•为快速互斥锁的非阻塞版本，它会立即返回并返回一个错误信息
 *
 *    互斥锁主要包括下面的基本函数：
 *    　　互斥锁初始化：pthread_mutex_init()
 *    　　互斥锁上锁：pthread_mutex_lock()
 *    　　互斥锁判断上锁：pthread_mutex_trylock()
 *    　　互斥锁解锁：pthread_mutex_unlock()
 *    　　消除互斥锁：pthread_mutex_destroy()
 */
