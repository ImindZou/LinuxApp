#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}Node;

//create head node
Node* head = NULL;

//create mutex
pthread_mutex_t mutex;

//create cond
pthread_cond_t cond;

void* produce(void* arg)
{
	while(1)
	{
		//create node
		Node* pnew = (Node*)malloc(sizeof(Node));
		//init node
		pnew->data = rand()%1000;//0-999

		//lock
		pthread_mutex_lock(&mutex);

		pnew->next = head;
		head = pnew;
		printf("prodece:%ld,%d\n",pthread_self(),pnew->data);

		//unlock
		pthread_mutex_unlock(&mutex);

		//alarm signal
		pthread_cond_signal(&cond);

		sleep(rand()%3);
	}
	printf("error\n");
	return NULL;	
}

void* customer(void* arg)
{
	while(1)
	{
		//lock
		pthread_mutex_lock(&mutex);

		if(head == NULL)
		{
			//continue;
			pthread_cond_wait(&cond,&mutex);
		}
		//delete head node
		Node* pdel = head;
		head = head->next;
		printf("customer:%ld,%d\n",pthread_self(),pdel->data);
		free(pdel);

		//unlock
		pthread_mutex_unlock(&mutex);

	}
	return NULL;	
}

int main(void)
{
	pthread_t p1,p2;

	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);

	pthread_create(&p1,NULL,produce,NULL);
	pthread_create(&p2,NULL,customer,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}
