#include <stdio.h>
#include <process.h>
#include <Windows.h>

int A[100];
CRITICAL_SECTION cs;

unsigned __stdcall func1(void* arg){
	EnterCriticalSection(&cs);

	printf("func1\n");
	for(int i=0; i<100; i++){
		A[i] = 3;
		printf(" %d", A[i]);
		Sleep(10);
	}
	
	LeaveCriticalSection(&cs);
	return 0;
}

unsigned __stdcall func2(void* arg){
	EnterCriticalSection(&cs);

	printf("\nfunc2\n");
	for(int j=99; j>=0; j--){
		A[j] = 4;
		printf(" %d", A[j]);
		Sleep(10);
	}

	LeaveCriticalSection(&cs);
	return 0;
}

void main(){
	InitializeCriticalSection(&cs);

	printf("main() start\n");
	HANDLE hThread1, hThread2;

	hThread1 = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, NULL); 
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, NULL);

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	DeleteCriticalSection(&cs);
	printf("\n");

}