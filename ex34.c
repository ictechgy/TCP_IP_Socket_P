#include <stdio.h>
#include <Windows.h>

DWORD WINAPI func1(LPVOID arg){
	int i;
	for(i=0; i<20; i++){
		printf("i : %d\n", i);
	}
	return 0;
}
DWORD WINAPI func2(LPVOID arg){
	int j;
	for(j=0; j<100; j++){
		printf("j : %d\n", j);
	}
	return 0;
}

void main(){
	HANDLE hThread1, hThread2;

	hThread1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	printf("func1 일시중지\n");
	SuspendThread(hThread1);
	WaitForSingleObject(hThread2, INFINITE);

	printf("func1 재시작\n");
	ResumeThread(hThread1);
	WaitForSingleObject(hThread1, INFINITE);


}
