#include <stdio.h>
#include <Windows.h>
#include <process.h>

int sum; 
CRITICAL_SECTION cs;  //�Ӱ迵���� ���� ����ü ��������

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
//��ġ.. main���� cs��� �������� �����, ������ �Լ���� ����� �� �� Enter�� Leave��� ���� ���� �Ѹ����� ������� �� �� �ְ� ����� ����
//����� ���� ������ �ϳ��� ���� �۵��� �� �ѵ� �� �������������ʰ� �Ǵ� ������� �۵��ϴ� ���� �� �� �ִ�.
//�Ӱ迵���������� ������ �ϳ��� �����ڿ��� �� ���������� �����ڿ����� ���ö����� �ٸ� ��������� ���ٺҰ�
