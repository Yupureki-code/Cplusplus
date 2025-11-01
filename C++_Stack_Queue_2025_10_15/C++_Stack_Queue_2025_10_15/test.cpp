#define _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"
#include "Queue.h"
#include "priority_queue.h"
#include <algorithm>
#include <stdlib.h>
int main()
{
	int arr[] = { 5,2,7,9,6,0,3,4,8,1 };
	priority_queue<int,vector<int>,less<int>> pq(arr,arr+10);
	pq.pop();
	pq.Print();
	return 0;
}