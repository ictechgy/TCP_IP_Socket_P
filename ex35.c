#include <stdio.h>
#include <Windows.h>

int sum=0;

DWORD WINAPI MyThread(LPVOID arg){
	int num = (int)arg;
	for(int i=0; i<=num; i++){
		sum+=i;
	}
}

void main(){
	int num = 100;
	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL); //인자 넘기기 및 스레드 생성만 하고 일시중지

	printf("스레드 실행 전 계산 결과 : %d\n", sum);
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
	printf("스레드 실행 후 계산 결과 : %d\n", sum);

	CloseHandle(hThread);   //스레드자원을 컴퓨터에게 반환? - 구글에서 closehandle 검색
	//핸들값을 반환한다는 의미일뿐 스레드가 종료되지는 않는다. (제어권만 잃을뿐)
	//스레드의 종료는 Usage Count라는 값에 의해 운영체제가 결정하는데 스레드생성시 +1, 핸들값 생성시 +1이 된다.
	//closehandle은 핸들값을 반환한다는 의미로서 Usage Count가 -1이 되며, 나머지 -1은 스레드함수 종료시 된다.(함수 return(종료)시 -1)

}