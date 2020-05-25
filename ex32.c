#include <stdio.h>
#include <windows.h>

DWORD WINAPI func1(LPVOID arg){
	int i;
	for(i=0; i<100; i++){
		printf("i : %d\n", i);
	}
	return 0;
}
DWORD WINAPI func2(void* arg){
	int j;
	for(j=0; j<100; j++){
		printf("j : %d\n", j);
	}
	return 0;
}

void main(){
	HANDLE hThread1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	WaitForSingleObject(hThread1, INFINITE);  //INFINITE : 쓰레드가 끝날때까지
	WaitForSingleObject(hThread2, INFINITE);


	//func1과 func2의 쓰레드는 생성되자마자 서로 같이 실행이 막 된다.
	//이 Wait함수들은 메인함수스레드의 작동을 잠시 일시정지시킬뿐, 다른 스레드들은 계속 움직인다.
}