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
	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL); //���� �ѱ�� �� ������ ������ �ϰ� �Ͻ�����

	printf("������ ���� �� ��� ��� : %d\n", sum);
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
	printf("������ ���� �� ��� ��� : %d\n", sum);

	CloseHandle(hThread);   //�������ڿ��� ��ǻ�Ϳ��� ��ȯ? - ���ۿ��� closehandle �˻�
	//�ڵ鰪�� ��ȯ�Ѵٴ� �ǹ��ϻ� �����尡 ��������� �ʴ´�. (����Ǹ� ������)
	//�������� ����� Usage Count��� ���� ���� �ü���� �����ϴµ� ����������� +1, �ڵ鰪 ������ +1�� �ȴ�.
	//closehandle�� �ڵ鰪�� ��ȯ�Ѵٴ� �ǹ̷μ� Usage Count�� -1�� �Ǹ�, ������ -1�� �������Լ� ����� �ȴ�.(�Լ� return(����)�� -1)

}