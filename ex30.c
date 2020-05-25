#include <stdio.h>
#include <Windows.h>
#include <process.h>

unsigned __stdcall func1(void* arg){
	int i;
	for(i = 0; i<100; i++)
		printf("i : %d\n", i);
	return 0;
}
unsigned __stdcall func2(LPVOID arg){
	int j;
	for(j=0; j<100; j++)
		printf("j : %d\n", j);
	return 0;
}

void main(){  //메인스레드 시작
	printf("main()함수 시작\n");

	printf("Thread들 시작 \n");
	unsigned long hThread1 = _beginthreadex(NULL, 0, func1, NULL, 0, NULL);  //func1에 대한 스레드 생기고 내용이 바로 시작됨
	unsigned long hThread2 = _beginthreadex(NULL, 0, func2, NULL, 0, NULL);  //func2 스레드 생성 및 바로 실행

	while(1){
		printf("main()\n");
		Sleep(10000);  //메인함수(스레드) 잠시 대기하게 해서 이 함수안의 스레드들이 작동할 충분한 시간을 주기
	}
	

	//메인스레드가 종료되어버리면 그냥 다 종료됨
	//즉 메인함수가 종료되어버리면서 안의 내용도 다 종료가 된 것 - 메인함수는 기본적으로 스레드가 존재한다는 것을 알 수 있다.
	
	//멀티스레드라는 것은 스레드가 한번에 같이 동작되는 것처럼 보이지만 사실 CPU가 아주 빠른 속도로 여러 스레드를 하나씩 동작시키는 것이다.
}