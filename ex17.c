#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void server(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SVRs;
	SVRs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN SVRa;
	memset(&SVRa, 0, sizeof(SVRa));
	SVRa.sin_addr.s_addr=inet_addr("192.168.52.2");
	SVRa.sin_port = htons(12345);
	SVRa.sin_family = AF_INET;

	bind(SVRs, (SOCKADDR*)(&SVRa), sizeof(SVRa));
	listen(SVRs, SOMAXCONN);

	SOCKET CiTs;
	SOCKADDR_IN CiTa;
	memset(&CiTa, 0, sizeof(CiTa));
	int CiTSize = sizeof(CiTa);

	CiTs = accept(SVRs, (SOCKADDR*)(&CiTa), &CiTSize);

	srand(time(NULL));
	int random = rand()%99+1;

	int user_in;

	while(1){
		recv(CiTs, (char*)&user_in, sizeof(user_in),0);
		if(random==user_in){
			char msg[20] = "correct answer";
			send(CiTs, msg, strlen(msg), 0);
			break;
		}
		else if(random>user_in){
			char msg[20] = "UP";
			send(CiTs, msg, strlen(msg), 0); 
		}
		else if(random<user_in){
			char msg[20] = "DOWN";
			send(CiTs, msg, strlen(msg), 0); 
		}
	}

	closesocket(CiTs); 
	closesocket(SVRs);
	WSACleanup();

}

void client(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	SOCKET CiTs;
	CiTs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN svrAddr;
	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_addr.s_addr=inet_addr("192.168.52.2");
	svrAddr.sin_port = htons(12345);
	svrAddr.sin_family = AF_INET;

	connect(CiTs, (SOCKADDR*)(&svrAddr), sizeof(svrAddr));

	while(1){
		int input;
		printf("숫자 입력 : ");
		scanf("%d", &input);

		send(CiTs, (char*)(&input), sizeof(input), 0);

		char msg[20];
		recv(CiTs, msg, sizeof(msg), 0);
		printf("%s", msg);
		if(!strcmp(msg, "correct answer")){
			break;
		}
	}

	closesocket(CiTs);
	WSACleanup;
}


//강의에서 설명하는 updown게임 설명
int rand_(){
	srand(time(NULL));
	return rand()%99+1;
}
void check(int ran){
	int user=0, cnt=0;
	while(1){
		printf("input : ");
		scanf("%d", &user);
		system("pause");
		system("cls");  //clearscreen
		printf("com : %d\n", ran);
		if(user<ran){
			cnt++;
			printf("==== UP ====\n");
		}
		else if(user>ran){
			cnt++;
			printf("==== DOWN ====\n");
		}
		else{
			cnt++;
			printf("정답! %d번 시도하셨습니다.\n", cnt);
			break;
		}
	}
}
int main(){
	printf("updown game start~!\n");
	int ran=rand_();
	check(ran);
	printf("\n== !!Congratulations!! ==\n");
	return 0;
}


//강의에서 설명하는 업다운게임 코드
typedef struct u{
	int num;
	char str[1024];
}ST;
void client_(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s == INVALID_SOCKET){
		printf("socket error!");
		return;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("192.168.1.144");

	int error = connect(s, (sockaddr*)&addr, sizeof(addr));
	if(error == SOCKET_ERROR){
		printf("connect error!");
		return;
	}
	char buf[500];  //이건 왜 넣은거지
	int user;
	ST st;
	while(1){
		memset(&st, 0, sizeof(st));
		printf("보낼 데이터 입력 : ");
		scanf("%d", &user);
		int len = send(s, (char*)&user, sizeof(user), 0);
		recv(s, (char*)&st, sizeof(st), 0);
		printf("%s\n", st.str);
		if(st.num == 1) break;
	}
	closesocket(s);
	WSACleanup();
}



#include <string.h>
int up(int user);
int rand_();
void check();
int ran = 0, cnt = 0;

void server_(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SVRs;
	SVRs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN SVRa;
	memset(&SVRa, 0, sizeof(SVRa));
	SVRa.sin_addr.s_addr=inet_addr("192.168.52.2");
	SVRa.sin_port = htons(12345);
	SVRa.sin_family = AF_INET;

	bind(SVRs, (SOCKADDR*)(&SVRa), sizeof(SVRa));
	listen(SVRs, SOMAXCONN);

	SOCKET CiTs;
	SOCKADDR_IN CiTa;
	memset(&CiTa, 0, sizeof(CiTa));
	int CiTSize = sizeof(CiTa);

	CiTs = accept(SVRs, (SOCKADDR*)(&CiTa), &CiTSize);

	char buf[1024];  //이건 또 왜만든겨

	//전역변수로 ran과 cnt존재
	int len;
	int user;
	int result;
	ST st;
	while(1){
		len = recv(CiTs, (char*)&user, sizeof(user), 0);
		if(len==SOCKET_ERROR){
			printf("recv_error!");
			return;
		}
		result = up(user);
		if(result==1){
			printf("==== DOWN ====\n");
			sprintf(st.str, "==== DOWN ====\n");   //sprintf는 strcpy와 같다고 보면 된다. 다만 서식화된 방식으로 문자열 저장이 가능
			st.num = 0;
			send(CiTs, (char*)&st, sizeof(st), 0);
		}
		else if(result == -1){
			printf("==== UP ====\n");
			sprintf(st.str, "==== UP ====\n");
			st.num=0;
			send(CiTs, (char*)&st, sizeof(st), 0);
		}
		else{
			printf("%d번만의 정답\n", cnt);
			sprintf(st.str, "%d번만의 정답입니다!\n\n ==!!Congratulations!!== \n", cnt);
			st.num=1;
			send(CiTs, (char*)&st, sizeof(st), 0);
			break;
		}
	closesocket(CiTs); 
	closesocket(SVRs);
	WSACleanup();
}

int rand_(){
	srand(time(NULL));
	return rand()%99 + 1;
}
int check(int user){

	printf("input : %d\n", user);
	printf("com : %d\n", ran);
	if(user>ran){
		cnt++;
		return 1;
	}
	else if(user<ran){
		cnt++;
		return -1;
	}
	else{
		cnt++;
		return 0;
	}
	system("pause");
	system("cls");
}


int up(int user){
	int result;
	printf("updown game start~!\n");
	if(!ran)
		ran=rand_();
	result = check(user);
	return result;
}