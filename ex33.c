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
	HANDLE hThread[2];

	hThread[0] = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	//스레드의 개수, 스레드배열명, 옵션, 시간값

}