
#include <iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include"PCthreads.h"
using namespace std;
#define runtime 10000
HANDLE P_array[P_num];
HANDLE C_array[C_num];
int main()
{
	for (int i = 0; i < P_num; i++)
	{
		P_array[i] = CreateThread(NULL, 0, ThreadP, NULL, 0, NULL);
	}
	for (int i = 0; i < C_num; i++)
	{
		C_array[i] = CreateThread(NULL, 0, ThreadC, NULL, 0, NULL);
	}
	Sleep(runtime);
	return 0;

}

