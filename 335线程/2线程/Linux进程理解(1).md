# Linux进程理解

[TOC]



> #### 对于进程回收机制的理解：

### 孤儿进程

一个父进程退出，而它的一个或多个子进程还在运行，那么那些子进程将成为孤儿进程。孤儿进程将被init进程(进程号为1)所收养，并由init进程对它们完成状态收集工作

> ##### 为了释放子进程占用的系统资源：
>
> - 进程结束之后，能够释放用户区空间
> - 释放不了的PCB，必须由父进程释放（于是孤儿进程就被系统收为义子，然后等待系统停止指令的到来进而释放内存）

### 僵尸进程：

> 一个比较特殊的状态，当进程退出父进程（没有使用wait()系统调用）没有读取到子进程退出的返回代码时就会产生僵尸进程。僵尸进程会在以终止状态保持在进程表中，并且会一直等待父进程读取退出状态代码。

是一个已经死掉的进程

意思就是一对父子进程在运行时，期间父进程执行完后，按理来说系统都有该回收进程资源，然而，父进程中没有设置wait（）函数来等待来回收子进程，这回导致该进程变为僵尸进程

![image-20231124162202784](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241622835.png)

![image-20231124162610483](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241626525.png)

![image-20231124162132615](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241621722.png)

> #### 设置了wait（）函数等待子进程结束并回收，就没有僵尸进程的情况

![image-20231124162426951](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241624991.png)

![image-20231124162430866](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241624901.png)

![image-20231124162433833](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241624865.png)

## 话说回来

在信号处理函数中

```c
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void myfun(int signum)
{
        int i = 0;
        while(i < 5)
        {
                printf("receive signum is %d,i=%d\n",signum,i);
                sleep(1);
                i++;
        }
}

void myfun1(int signum)
{
        printf("client signal %d sucess\n",signum);
        wait(NULL);
}

int main(void)
{
        pid_t pid;
        pid = fork();
        if(pid > 0)
        {
                int i = 0;
                signal(10,myfun);
                signal(17,myfun1);
                while(1)
                {
                        printf("process i = %d\n",i);
                        sleep(1);
                        i++;
                }
        }
        if(pid == 0)
        {
                sleep(10);
                kill(getppid(),10);
                sleep(10);
                exit(0);  //kill(getppid(),17);仍是僵尸进程
        }

        return 0;
}
     
```

也是遵循同样的道理。在父子进程通信之间，子进程在两个特殊的时间点给父进程发送信号，父进程做出回应，若是，在父进程执行期间没有回收子进程则会导致该进程在某一段时间该进程变成僵尸进程，并且被牢牢打印在终端界面，除非函数被系统终止回收。

![image-20231124163937605](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241639651.png)

![image-20231124163941315](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241639362.png)

没有回收函数时

![image-20231124164130845](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311241641877.png)

除非系统回收子进程资源，才会收回僵尸进程的日志

# 问:为什么线程比进程要节省资源?

> ### 来自进程概念的答案：

![image-20231124203257640](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311242032717.png)

对于父子进程来讲，fork之后了地址空间数据完全相同，用户数据一样，进程ID不一致。并且各个进程的地址空间中的数据时完全独立的。对于同一个变量，读时共享，写的时候分别在物理地址上拷贝一份变量进行单独读写。而且父子进程还不能用全局变量互相通信，因为他们时互相独立的进程。这是他们的天然属性。

![image-20231124203600369](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311242036427.png)

> ### 来自线程概念的答案：（其实进程控制块时PCB，线程控制块应该是TCB才对）

![image-20231124203746817](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311242037857.png)

> 在Linux下：线程就是进程-轻量级进程
>
> 对于内核来说，线程就是进程
>
> 多进程和多线程的区别：
>
> - 多进程：始终共享的资源：代码、文件描述符、内存映射区--mmap
> - 多线程：始终共享的资源：堆、全局变量，节省资源
>     - **由进程概念里得知进程的全局变量并不互相共享，都是互相独立设置的，所以他用到的堆区比较大，所以才导致资源开销比较大。**

[什么是进程和线程？ 为什么要引入线程？ 进程和线程的区别？-腾讯云开发者社区-腾讯云 (tencent.com)](https://cloud.tencent.com/developer/article/2303101)

结合上面文章自己做了一下测试

得出的结论：通过 ps -Lf pid （查看线程的指令）

没打开火狐浏览器前的进程数据

![image-20231124204945142](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311242049183.png)

打开火狐浏览器后的进程数据

![image-20231124204824221](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311242048390.png)

![image-20231124204838431](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311242048469.png)

查看一个进程里边的多个线程

![image-20231124204911809](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311242049849.png)

# 线程同步思想

在没有锁的情况下两个线程会互相抢占CPU的使用权，这可能会出现变量初始化完成后没有写入内存的情况，于是有了一个东西叫做锁，应用在线程同步的情境，以确保内存的准确写入。

```c
/*两个线程分别对一个数加一万次
*因为线程的资源是共享的，所以可以对同一个全局变量进行操作
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10000
int number;

void *funA(void* arg)
{
	for(int i=0;i<MAX;i++)
	{
		int ret = number;
		ret++;
		number = ret;
		printf("funA id is %ld,number is %d\n",pthread_self(),number);
		usleep(10);
	}
}

void *funB(void* arg)
{
	for(int i=0;i<MAX;i++)
	{
		int ret = number;
		ret++;
		number = ret;
		printf("funB id is %ld,number is %d\n",pthread_self(),number);
		usleep(10);
	}
}

int main(void)
{
	pthread_t pth1,pth2;
	pthread_create(&pth1,NULL,funA,NULL);
	pthread_create(&pth2,NULL,funB,NULL);

	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);	

	return 0;
}

```

![image-20231125154711222](C:/Users/zdh/AppData/Roaming/Typora/typora-user-images/image-20231125154711222.png)

> 结果数据是比较混乱的，因为两个线程都在抢占CPU的使用权
>
> 原因：
>
> - 操作了共享资源，number
> - CPU的调度问题
>
> 解决方法线程同步（创建一把锁）
>
> - 什么是同步？协同步调，按照先后顺序操作执行

## 互斥锁原理

> ##### 当在多线程里使用锁的时候，多线程访问共享内存是串行的。
>
> 缺点：效率低

![image-20231125155724347](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311251557401.png)

> ##### 通过给多线程资源加锁，实现线程从并行到串行的操作。确保了数据的准确性。

![image-20231125162426704](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311251624750.png)

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10000
int number;
//create nytes
pthread_mutex_t mutex;

void *funA(void* arg)
{
	for(int i=0;i<MAX;i++)
	{
		//lock
		pthread_mutex_lock(&mutex);//阻塞在此
		int ret = number;
		ret++;
		number = ret;
		printf("funA id is %ld,number is %d\n",pthread_self(),number);
		//unlock
		pthread_mutex_unlock(&mutex);//变量通过系统函数写入到内存后才解锁,放出CPU使用权
		usleep(10);
	}
}

void *funB(void* arg)
{
	for(int i=0;i<MAX;i++)
	{
		//lock
		pthread_mutex_lock(&mutex);//阻塞在此

		int ret = number;
		ret++;
		number = ret;
		printf("funB id is %ld,number is %d\n",pthread_self(),number);
		//unlock
		pthread_mutex_unlock(&mutex);//变量通过系统函数写入到内存后才解锁,放出CPU使用权
		usleep(10);
	}
}

int main(void)
{
	//init mutex
	pthread_mutex_init(&mutex,NULL);
	pthread_t pth1,pth2;
	pthread_create(&pth1,NULL,funA,NULL);
	pthread_create(&pth2,NULL,funB,NULL);

	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);	

	pthread_mutex_destroy(&mutex);
	return 0;
}

```

### 互斥锁的使用步骤

- 创建互斥锁： pthread_mutex_t mutex;

- 初始化：pthread_mutex_init(&mutex,NULL); -- mutex = 1

- 找到线程共同操作的共享数据

    - 加锁：操作共享资源之前加锁，pthread_mutex_lock(&mutex); //阻塞 --mutex = 0

    - pthread_mutex_trylock(&mutex); // 如果锁上锁直接返回，不阻塞
        - XXXXXX共享数据操作 //临界区 ，越小越好

    - 解锁：pthread_mutex_unlock(&mutex); // -- mutex = 1
        - 阻塞在锁上的线程会被唤醒

- 销毁：pthread_mutex_destory(&mutex)；

具体实现流程演练

```
开锁
for（）
{
	lock();
	10;共享数据 
	unlock();
	20;不是共享数据
	lock();
	30;共享数据
	unlock();
}
关锁

```

# 原子操作（为什么要用锁的原因）

> CPU处理一个指令，进程/线程在处理完这个指令之前是不会失去CPU的执行权的，就像原子被认为是不可分割的颗粒一样，汇编语言也是一样，有的汇编指令集一条包含一个指令也有的两个或三个。

```c
//示例代码1：
void* procucer(void * arg)
{
while(1)
{
//创建一个链表的节点
Node * newNode = (Node*)malloc(sizeof(Node));
//init
newNode‐>data = rang()%100;
newNode ‐>next = head;
head = newNode;
printf("+++product:%d\n",newNode‐>data);
sleep(rang()%3);
}
reutn NULL;
}
```

```c
//示例代码2：
void* procucer(void * arg)
{
while(1)
{
//创建一个链表的节点
Node * newNode = (Node*)malloc(sizeof(Node));
//init
newNode‐>data = rang()%100;
pthread_mutex_lock(&mutex);		//利用锁来模拟原子操作，前面的没有锁可能随时会失去CPU的执行权，从而被打断，导致数据混乱
newNode ‐>next = head;
head = newNode;
printf("+++product:%d\n",newNode‐>data);
pthread_mutex_unlock(&mutex);
sleep(rang()%3);
}
reutn NULL;
}
```

# 死锁

造成死锁的原因：

- 自己锁自己

```c
for(int i = 0;i<MAX;i++)
{
pthread_mutex_lock(&mutex);
pthread_mutex_lock(&mutex);
int crt = number;
crt++;
number = crt;
printf("thread A id = %ld,number = %d\n",pthread_self(),number);
pthread_mutex_unlock(&mutex);
usleep(10);
}
```

操作完后，一定要解锁。

- ![image-20231125170137657](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311251701717.png)

线程1 对共享资源A加锁成功-A锁
线程2 对共享资源B加锁成功-B锁

线程1访问共享资源B，对B锁加锁-线程1阻塞在B锁上
线程2访问共享资源A，对A锁加锁-线程2阻塞在A锁上

如何解决：
-让线程按照一定的顺序去访问共享资源
-在访问其他锁的时候，需要先将自己的锁解开
--try_lock（）不会阻塞，可以进行一些解锁操作，比较灵活

# 读写锁

1. 读写锁一共是几把锁？
    - 一把锁
    - pthread_rwlock_t lock;
2. 读写锁的类型：
    - 读锁-对内存做读操作
    - 写锁-对内存做写操作
3. 读写锁的状态
4. 读写锁的特性：
    - 线程A加读锁成功，又来了三个线程，做读操作，可以加锁成功
        - 读共享-并行处理，因为读操作不会堆内存造成破坏，写会破坏原有的内存所以是串行
    - 线程A加写锁成功，又来了三个线程，做读操作，三个线程阻塞
        - 写独占。写优先级最比较高
    - 线程A加读锁成功，又来了线程加写锁阻塞，又来了C线程加读锁阻塞
        - 读写不可以同时进行
        - 写的优先级高
5. 读写锁场景练习
    - 线程A加写锁成功，线程B请求读锁
        - 线程B阻塞
    - 线程A持有读锁，线程B请求写锁
        - 线程B阻塞
    - 线程A拥有读写，线程B请求读锁
        - 线程B阻塞
    - 线程A持有读锁，然后线程B请求写锁，然后线程C请求读锁
        - 线程B阻塞，线程C阻塞
        - 线程C加锁，线程C阻塞
        - 线程C加锁
    - 线程A持有写锁，然后线程B请求读锁，然后线程C请求写锁
        - 线程B阻塞，线程C阻塞
        - 线程C加锁，线程B阻塞
        - 线程B加锁
6. 读写锁的适用场景
    - 互斥锁-读写串行
    - 读写锁：
        - 读：并行
        - 写：串行
7. 主要操作函数
    - 初始化读写锁
        - pthread_rwlock_init(pthread_rwlock_t* restrict rwlock,
            const pthread_rwlockattr_t* restrict attr );
    - 销毁读写锁
        - pthread_rwlock_destroy(pthread_rwlock_t* rwlock):
    - 加读锁
        - pthread_rwlock_rdlock(pthread_rwlock_t* rdlock);
            阻塞：之前对这把锁加的是写锁的操作
    - 尝试加读锁
        - pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock);
            加锁成功：返回0
            失败：返回错误号
    - 加写锁
        - pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);
            阻塞：上一次加写锁还没解锁
            阻塞：上一次加读锁还没解锁
    - 尝试加写锁
        - pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock);
    - 解锁
        - pthread_rwlock_unlock(pthread_rwlock_t* rwlock)
8. 练习
    - 三个线程不定时写同一个全局变量，五个线程不定期读同一个全局资源
        - 先不加锁（数据混乱）
            - ![image-20231125180547753](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311251805794.png)
        - 加锁（数据有序完整）
            - ![image-20231125180221350](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311251802405.png)

# 条件变量

- 阻塞线程
- 不是什么时候都能够阻塞线程

```c
链表头节点
Node*head = NULL;
while(head == NULL)
{
//我们想让代码在这个位置阻塞
//等待链表中有了节点之后再继续向下运行
//使用到了后面要讲的条件变量‐阻塞线程
}
//链表不为空的处理代码
xxxx
```

1. 条件变量是锁吗？
    - 不是锁，但是条件变量能够阻塞线程
    - 使用条件变量+互斥量
        - 互斥量：保护一块共享数据
        - 条件变量：引起阻塞
2. 条件变量额两个动作
    - 条件不满足，阻塞线程
    - 当条件满足，通知阻塞的线程开始工作
3. 条件变量的类型
    - pthread_cond_t cond; condition条件
4. 主要函数
    - 初始化一个条件变量
        - pthread_cond_init(pthread_cond_t * restrict cond,
            const pthread_condattr_t * restrict attr
            );
    - 销毁一个条件变量
        - pthread_cond_destroy(pthread_cond_t * cond);
    - 阻塞等待一个条件变量
        - pthread_cond_wait(
            pthread_cond_t *restrict cond,
            pthread_mutex_t * restrict mutex
            )；
        - 阻塞线程
        - 将已经上锁的mutex解锁
        - 该函数解除阻塞，对互斥锁加锁
    - 限时等待一个条件变量
        - pthread_cond_timedwait(
            pthread_cond_t * restrict cond,
            pthread_mutex_t * restrict mutex,
            const struct timespec * restrict abstime
            )；
    - 唤醒至少一个阻塞在条件变量上的线程
        - pthread_cond_signal(pthread_cond_t* cond);
    - 唤醒全部阻塞在条件变量上的线程
        - pthread_cond_broadcast(pthread_cond_t * cond)；
    - 练习
        - 使用条件变量实现生产者，消费者模型

## 条件变量+互斥锁

> #### 生产者消费者模型：

![image-20231125181911503](https://zdh934.oss-cn-shenzhen.aliyuncs.com/PigGo/202311251819568.png)

> ### 依靠信号函数来起到条件分支的作用

