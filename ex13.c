#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

void main(int argc, char* argv[]){
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET CiTs;
	CiTs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN srvAddr;
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = inet_addr(argv[1]);
	srvAddr.sin_port = htons(atoi(argv[2]));		//cmd�� ���� ���α׷� ����� �߰������� �־��� ���ڸ� ���� ����

	connect(CiTs, (sockaddr*)(&srvAddr), sizeof(srvAddr));

	char msg[100];
	printf("�޽��� �Է� : ");
	scanf("%s", msg);

	int len;
	len = send(CiTs, msg, strlen(msg), 0);

	char recvMsg[100];
	len = recv(CiTs, recvMsg, sizeof(recvMsg), 0);  //���࿡ ������ ���ڼ����̰ų� � �޽����� ������ ��� �ޱ�
	printf("%s", recvMsg);

	closesocket(CiTs);
	WSACleanup();
	
}