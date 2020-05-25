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

	WaitForSingleObject(hThread1, INFINITE);  //INFINITE : �����尡 ����������
	WaitForSingleObject(hThread2, INFINITE);


	//func1�� func2�� ������� �������ڸ��� ���� ���� ������ �� �ȴ�.
	//�� Wait�Լ����� �����Լ��������� �۵��� ��� �Ͻ�������ų��, �ٸ� ��������� ��� �����δ�.
}