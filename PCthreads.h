#include<stdlib.h>
#include"buffer.h"
#include<windows.h>
#include<time.h>
#define MAX_ITEM 100
#define MAX_TIME 500
#define P_num 10
#define C_num 5
HANDLE Empty = CreateSemaphore(NULL,buffersize, buffersize, NULL);
HANDLE Full = CreateSemaphore(NULL,0,buffersize,NULL);
HANDLE Mutex = CreateMutex(NULL,false,NULL);
int P_id = 0;
int C_id = 0;

DWORD WINAPI ThreadP(LPVOID)
{
	int id = P_id++;
	do {
		srand(GetCurrentThreadId());
		int time = rand() % MAX_TIME;
		Sleep(time);
		WaitForSingleObject(Empty, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << "producer" << id<<":";
		int item = rand() % MAX_ITEM;
		buf.item_insert(item);
		ReleaseMutex(Mutex);
		ReleaseSemaphore(Full, 1, NULL);
	} while (1);
	return 0;
}

DWORD WINAPI ThreadC(LPVOID)
{
	int id = C_id++;
	do {
		srand(GetCurrentThreadId());
		int time = rand() % MAX_TIME;
		Sleep(time);
		WaitForSingleObject(Full, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << "consumer" << id<<":";
		buf.item_remove();
		ReleaseMutex(Mutex);
		ReleaseSemaphore(Empty, 1, NULL);
	} while (1);
	return 0;
}