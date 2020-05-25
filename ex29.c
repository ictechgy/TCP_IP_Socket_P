#include <stdio.h>
#include <Windows.h> //윈도우용 멀티스레드 예약어들을 쓰기 위한 전처리 - LPVOID, WINAPI, DWORD, HANDLE 등
#include <process.h> //C 및 C++ 멀티스레드 예약어들을 쓰기 위한 전처리 - __stdcall, _beginthreadex 등
#include <conio.h>   //getch()함수를 쓰기위한 전처리

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
//키보드 방향키들에 대한 아스키코드 숫자정수값

int x, y;
void gotoxy(int x, int y){
	COORD pos={x,y};   //short형으로 x와 y라는 좌표를 저장할 수 있는 구조체 COORD
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  //커서의 위치를 COORD형 두번째 인자(pos)가 가지고 있는 값 위치로 변경해주는 함수
} 

unsigned __stdcall func_1(void* arg){  //매개변수부분 적지 않아도 문제는 생기지 않는다.
	int i;
	for(i=0; i<1000; i++){
		gotoxy(x,y);
		printf("ㅁ");
		y++;
		Sleep(400);
		system("cls");
		gotoxy(x,y);
		printf("ㅁ");
	}	//변하는 y값에 따라 커서가 영향을 받아 ㅁ이라는 글자가 아래로 떨어지는 모습 (이전의 글자 지우고, 커서 위치 변경 후 ㅁ 재출력)
	return 0;
}
unsigned __stdcall func_2(LPVOID arg){
	int j;
	char ch;
	for(j=0; j<1000; j++){
		switch(getch()){   //엔터를 입력하지 않아도 입력되는 값을 바로 읽어들임. conio.h 헤더파일 필요
		case LEFT:gotoxy(x--,y); printf("ㅁ"); break;
		case RIGHT:gotoxy(x++,y);printf("ㅁ");break;
		case UP:gotoxy(x,y--);printf("ㅁ");break;
		case DOWN:gotoxy(x,y++);printf("ㅁ");break;

		}
		system("cls");
		gotoxy(x, y);
		printf("ㅁ");
	}
	return 0;
}

void main(){
	unsigned long hthread_1 = _beginthreadex(NULL, 0, func_1, NULL, 0, 0);
	unsigned long hthread_2 = _beginthreadex(0, 0, func_2, 0, 0, 0);
	Sleep(1000000);
}