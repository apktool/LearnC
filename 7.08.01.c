/**
 * @file 7.08.01.c
 * @brief pthread_mutexattr_init(),pthread_mutexattr_settype(),pthread_mutex_init(),pthread_mutexattr_destroy()
 * @author LiWenGang
 * @date 2016-07-08
 */
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);

static void* pthreadFunc(void*);
static int cnt=0;

static pthread_mutex_t mtx;
static pthread_mutexattr_t mtxAttr;

void MutexLockInit();
void MutexLockDestory();

int main(int argc, char* argv[]){
	pthread_t thd1,thd2;
	int loops=100000;
	int flag;

	MutexLockInit();

	flag=pthread_create(&thd1,NULL,pthreadFunc,&loops);
	if(flag!=0){
		perror("error pthread_create");
	}

	flag=pthread_create(&thd2,NULL,pthreadFunc,&loops);
	if(flag!=0){
		perror("error pthread_create");
	}

	flag=pthread_join(thd1,NULL);
	if(flag!=0){
		perror("error pthread_join");
	}

	flag=pthread_join(thd2,NULL);
	if(flag!=0){
		perror("error pthread_join");
	}

	MutexLockDestory();

	printf("cnt=%d\n",cnt);
	return 0;
}

static void* pthreadFunc(void *s){
	int loops=*((int*)s);
	int flag;

	flag=pthread_mutex_lock(&mtx);
	if(flag!=0){
		perror("error pthread_mutex_lock");
	}
	for(int i=0;i<loops;i++){
		cnt++;
	}
	flag=pthread_mutex_unlock(&mtx);
	if(flag!=0){
		perror("error pthread_mutex_unlock");
	}
	return NULL;
}

void MutexLockInit(){
	int flag;

	flag=pthread_mutexattr_init(&mtxAttr);
	if(flag!=0){
		perror("error pthread_mutexattr_init");
	}
	flag=pthread_mutexattr_settype(&mtxAttr,PTHREAD_MUTEX_ERRORCHECK_NP);
	if(flag!=0){
		perror("error pthread_mutexattr_settype");
	}
	flag=pthread_mutex_init(&mtx,&mtxAttr);
	if(flag!=0){
		perror("error pthread_mutex_init");
	}
}

void MutexLockDestory(){
	int flag;

	flag=pthread_mutexattr_destroy(&mtxAttr);
	if(flag!=0){
		perror("error pthread_mutexattr_destory");
	}
}

/*
 * 动态分配互斥量
 * 1.使用时需要注意互斥量mtx必须要设置为全局变量，这主要是因为如果设置为局部变量的话，因为作用域的原因，会导致锁失效
 * 2.关于设置互斥锁属性的问题，比如这里使用的是“PTHREAD_MUTEX_ERRORCHECK_NP”属性，提供了检错功能
 * 3.关于设置所属性的位置也一定要注意，不然会导致互斥锁失效
 * 4.关于加锁的位置一定需要搞清楚，不然会导致互斥锁失效
 *
 * 互斥锁属性：
 * * PTHREAD_MUTEX_TIMED_NP，这是缺省值，也就是普通锁。当一个线程加锁以后，其余请求锁的线程将形成一个等待队列，并在解锁后按优先级获得锁。这种锁策略保证了资源分配的公平性。
 * * PTHREAD_MUTEX_RECURSIVE_NP，嵌套锁，允许同一个线程对同一个锁成功获得多次，并通过多次unlock解锁。如果是不同线程请求，则在加锁线程解锁时重新竞争。
 * * PTHREAD_MUTEX_ERRORCHECK_NP，检错锁，如果同一个线程请求同一个锁，则返回EDEADLK，否则与PTHREAD_MUTEX_TIMED_NP类型动作相同。这样就保证当不允许多次加锁时不会出现最简单情况下的死锁。
 * * PTHREAD_MUTEX_ADAPTIVE_NP，适应锁，动作最简单的锁类型，仅等待解锁后重新竞争。
 */ 
