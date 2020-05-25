#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

void client(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	SOCKET CiTs;
	CiTs = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN svrAddr;
	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_addr.s_addr=inet_addr("192.168.52.2");
	svrAddr.sin_port = htons(12345);
	svrAddr.sin_family = AF_INET;

	char msg[256] = "시간을 줄래요!!";
	sendto(CiTs, msg, strlen(msg), 0, (sockaddr*)&svrAddr, sizeof(svrAddr));

	char time[512];
	memset(time, 0, sizeof(time));

	recvfrom(CiTs, time, sizeof(time), 0, 0, 0);
	
	printf("%s\n", time);
	

	closesocket(CiTs);
	WSACleanup;
}


#include <time.h>
void server(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SVRs;
	SVRs = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN SVRa;
	memset(&SVRa, 0, sizeof(SVRa));
	SVRa.sin_addr.s_addr=inet_addr("192.168.52.2");
	SVRa.sin_port = htons(12345);
	SVRa.sin_family = AF_INET;

	bind(SVRs, (SOCKADDR*)(&SVRa), sizeof(SVRa));

	SOCKADDR_IN CiTa;
	memset(&CiTa, 0, sizeof(CiTa));
	int CiTSize = sizeof(CiTa);

	char msg[256];
	memset(msg, 0, sizeof(msg));

	recvfrom(SVRs, msg, sizeof(msg), 0, (SOCKADDR*)&CiTa, &CiTSize);
	printf("클라이언트가 보낸 메시지 : %s\n", msg);

	time_t tm;  //1970년 1월 1일부터 지나온 시간 초값을 저장할 수 있는 64비트 int 자료형 구조체. time()함수를 통해 반환되는 값을 저장하면 된다.
	time(&tm); //1970년 1월 1일부터 지나온 시간 초값을 반환하는 함수. 인자로 time_t 구조체 변수의 주소값을 넣어주면 그 변수에 값을 저장도 시켜준다.
	struct tm* lt = localtime(&tm);
	//tm구조체는 여러가지 time값들을 분할하여 저장할 수 있는 구조체이다. 
	//localtime()함수는 인자로 들어온 time_t의 주소를 찾아가서 나오는 초값을 이용하여 tm구조체 공간을 만든 뒤 그 구조체를 초기화시킨다.
	//이후에 이 tm구조체를 가리키는 주소값을 리턴한다.

	char time[512];
	memset(time, 0, sizeof(time));
	
	sprintf(time, "오늘은 %d년 %d월 %d일 현재 시각은 %d시 %d분 입니다.\n", lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min);
	//sprintf()함수는 형식화된 문자열을 지정된 문자열공간에 저장하는 함수이다. 크기를 지정하는 인자가 없으므로 오버플로우 문제가 발생할 수 있다.
	//tm구조체에서의 년도값은 1900년도 이후부터 지난 값만이 저장되어있으므로 따로 1900을 더해주어야 한다.
	//컴퓨터에서 월은 0~11로 세므로 1을 더해줘서 넣어야 한다.(자바와 동일)

	sendto(SVRs, time, strlen(time), 0, (SOCKADDR*)&CiTa, sizeof(CiTa));
	
	
	closesocket(SVRs);
	WSACleanup();

}