#include <stdio.h>
#include <Windows.h> //������� ��Ƽ������ �������� ���� ���� ��ó�� - LPVOID, WINAPI, DWORD, HANDLE ��
#include <process.h> //C �� C++ ��Ƽ������ �������� ���� ���� ��ó�� - __stdcall, _beginthreadex ��
#include <conio.h>   //getch()�Լ��� �������� ��ó��

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
//Ű���� ����Ű�鿡 ���� �ƽ�Ű�ڵ� ����������

int x, y;
void gotoxy(int x, int y){
	COORD pos={x,y};   //short������ x�� y��� ��ǥ�� ������ �� �ִ� ����ü COORD
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  //Ŀ���� ��ġ�� COORD�� �ι�° ����(pos)�� ������ �ִ� �� ��ġ�� �������ִ� �Լ�
} 

unsigned __stdcall func_1(void* arg){  //�Ű������κ� ���� �ʾƵ� ������ ������ �ʴ´�.
	int i;
	for(i=0; i<1000; i++){
		gotoxy(x,y);
		printf("��");
		y++;
		Sleep(400);
		system("cls");
		gotoxy(x,y);
		printf("��");
	}	//���ϴ� y���� ���� Ŀ���� ������ �޾� ���̶�� ���ڰ� �Ʒ��� �������� ��� (������ ���� �����, Ŀ�� ��ġ ���� �� �� �����)
	return 0;
}
unsigned __stdcall func_2(LPVOID arg){
	int j;
	char ch;
	for(j=0; j<1000; j++){
		switch(getch()){   //���͸� �Է����� �ʾƵ� �ԷµǴ� ���� �ٷ� �о����. conio.h ������� �ʿ�
		case LEFT:gotoxy(x--,y); printf("��"); break;
		case RIGHT:gotoxy(x++,y);printf("��");break;
		case UP:gotoxy(x,y--);printf("��");break;
		case DOWN:gotoxy(x,y++);printf("��");break;

		}
		system("cls");
		gotoxy(x, y);
		printf("��");
	}
	return 0;
}

void main(){
	unsigned long hthread_1 = _beginthreadex(NULL, 0, func_1, NULL, 0, 0);
	unsigned long hthread_2 = _beginthreadex(0, 0, func_2, 0, 0, 0);
	Sleep(1000000);
}