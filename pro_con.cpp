/*
 * pro_con.cpp
 *
 *  Created on: 2019年4月25日
 *      Author: liu
 */
#include<iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
using namespace std;
#define runtime 10000
#define MAX_ITEM 100
#define MAX_TIME 500
#define P_num 10
#define C_num 5
#define buffersize 20
sem_t Empty,Full,Mutex;
int P_id = 0;
int C_id = 0;
pthread_t P_array[P_num];
pthread_t C_array[C_num];
class buffer
{
	int buff[buffersize];
	int in_ptr;
	int out_ptr;
public:
	buffer() { for (int i = 0; i < buffersize; i++) buff[i] = 0; in_ptr = 0; out_ptr = 0; }
	void item_insert(int item) {
		buff[in_ptr] = item;
		in_ptr = (in_ptr + 1) % buffersize;
		cout << "put " << item << " into buffer" << endl;
	}
	void item_remove() {
		cout << "remove " <<buff[out_ptr]<< " from buffer" << endl;
		out_ptr = (out_ptr + 1) % buffersize;
	}

};

buffer buf;
void* ThreadP(void*)
{
	int id = P_id++;
	do {
		srand(int(pthread_self()));
		int item = rand() % MAX_ITEM;
		int time = rand() % MAX_TIME;
		sleep(time/1000);
		sem_wait(&Empty);
		sem_wait(&Mutex);
		cout << "producer" << id<<":";	
		buf.item_insert(item);
		sem_post(&Mutex);
		sem_post(&Full);
	} while (1);
	return 0;
}

void* ThreadC(void*)
{
	int id = C_id++;
	do {
		srand(int(pthread_self()));
		int time = rand() % MAX_TIME;
		sleep(time/1000);
		sem_wait(&Full);
		sem_wait(&Mutex);
		cout << "consumer" << id<<":";
		buf.item_remove();
		sem_post(&Mutex);
		sem_post(&Empty);
	} while (1);
	return 0;
}


int main()
{
	sem_init(&Full,0,0);
	sem_init(&Mutex,0,1);
	sem_init(&Empty,0,buffersize);
	for (int i = 0; i < P_num; i++)
	{
		pthread_create(&P_array[i],NULL,ThreadP,NULL);
	}
	for (int i = 0; i < C_num; i++)
	{
		pthread_create(&C_array[i],NULL,ThreadC,NULL);
	}
	sleep(runtime/1000);
	return 0;
}




