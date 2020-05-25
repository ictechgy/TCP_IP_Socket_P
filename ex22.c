#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

struct test{
	int num1, num2;
	char op;
};

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

	int su1, su2;
	char oper;
	printf("첫번째 숫자 입력 : ");
	scanf("%d", &su1);
	printf("연산자 입력 : ");
	scanf("%c", &oper);
	printf("두번째 숫자 입력 : ");
	scanf("%d", &su2);

	sendto(CiTs, (char*)&su1, sizeof(su1), 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));
	sendto(CiTs, &oper, 1, 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));
	sendto(CiTs, (char*)&su2, sizeof(su2), 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

	//강의에서는 구조체를 하나 만들고 그 안에 int형 변수공간 2개와 char형 변수공간 하나를 만든 뒤, 이 구조체를 전송하는 방식으로 구현함
	struct test ca;
	scanf("%d%c%d", &ca.num1, &ca.op, &ca.num2);

	double result;
	recvfrom(CiTs, (char*)&result, sizeof(result), 0, 0, 0);

	printf("%d %c %d = %f", su1, oper, su2, result);

	closesocket(CiTs);
	WSACleanup;
}

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

	int su1, su2;
	char oper;
	recvfrom(SVRs, (char*)&su1, sizeof(su1), 0, (SOCKADDR*)&CiTa, &CiTSize);
	recvfrom(SVRs, &oper, 1, 0, 0, 0);
	recvfrom(SVRs, (char*)&su2, sizeof(su2), 0, 0, 0);

	double result;
	switch(oper){
	case '+':
		result = su1 + su2;
		break;
	case '-':
		result = su1 - su2;
		break;
	case '*':
		result = su1 * su2;
		break;
	case '/':
		if (su2==0) result=0; break;
		result = (double)su1 / su2;
		break;
	case '%':
		result = su1%su2;
		break;
	default:
		result=0;
	}

	sendto(SVRs, (char*)&result, sizeof(result), 0, (SOCKADDR*)&CiTa, sizeof(CiTa));

	//강의에서는 구조체로 클라이언트가 보낸 값을 그대로 받고, if문으로 연산자 비교 후 int형 변수 result에 결과값을 담아서 보냄
	
	closesocket(SVRs);
	WSACleanup();

}