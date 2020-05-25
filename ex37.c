#include <stdio.h>
#include <Windows.h>
#include <process.h>

int sum; 
CRITICAL_SECTION cs;  //임계영역에 대한 구조체 전역변수

unsigned __stdcall func1(void* arg){
	int i;
	EnterCriticalSection(&cs);
	for(i = 0; i<100; i++){
		sum+=i;
		printf("sum : %d\n", sum);
	}
	LeaveCriticalSection(&cs);
	return 0;
}
void main(){
	InitializeCriticalSection(&cs);
	for(int i=0; i<100; i++){
		_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	}
	LeaveCriticalSection(&cs);
}
//마치.. main에서 cs라는 수영장을 만들고, 각각의 함수라는 사람이 들어갈 때 Enter와 Leave라는 것을 만들어서 한명씩만 들락날락 할 수 있게 만든것 같음
//결과를 보면 스레드 하나가 먼저 작동을 다 한뒤 그 다음스레드차례가 되는 방식으로 작동하는 것을 볼 수 있다.
//임계영역내에서는 스레드 하나가 공유자원에 다 접근했으면 공유자원에서 나올때까지 다른 스레드들은 접근불가

