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

void main(){  //���ν����� ����
	printf("main()�Լ� ����\n");

	printf("Thread�� ���� \n");
	unsigned long hThread1 = _beginthreadex(NULL, 0, func1, NULL, 0, NULL);  //func1�� ���� ������ ����� ������ �ٷ� ���۵�
	unsigned long hThread2 = _beginthreadex(NULL, 0, func2, NULL, 0, NULL);  //func2 ������ ���� �� �ٷ� ����

	while(1){
		printf("main()\n");
		Sleep(10000);  //�����Լ�(������) ��� ����ϰ� �ؼ� �� �Լ����� ��������� �۵��� ����� �ð��� �ֱ�
	}
	

	//���ν����尡 ����Ǿ������ �׳� �� �����
	//�� �����Լ��� ����Ǿ�����鼭 ���� ���뵵 �� ���ᰡ �� �� - �����Լ��� �⺻������ �����尡 �����Ѵٴ� ���� �� �� �ִ�.
	
	//��Ƽ�������� ���� �����尡 �ѹ��� ���� ���۵Ǵ� ��ó�� �������� ��� CPU�� ���� ���� �ӵ��� ���� �����带 �ϳ��� ���۽�Ű�� ���̴�.
}