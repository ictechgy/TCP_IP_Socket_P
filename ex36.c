#include <stdio.h>
#include <Windows.h>
#include <process.h>

int sum;   //�޸��� data������ ��������� ��������

unsigned __stdcall func1(void* arg){
	int i;
	for(i = 0; i<100; i++){
		sum+=i;
		printf("sum : %d\n", sum);
	}
	return 0;
}
void main(){
	for(int i=0; i<100; i++){
		_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	}
}  //������ ����� ������ �ȴ�.