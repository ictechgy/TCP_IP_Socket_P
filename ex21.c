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

	char str[20]="Hello!!";
	//���ǿ����� gets()�� ���ڸ� �Է¹���. gets�Լ��� Ű����κ��� ���� �Է¹����� ���Ͱ��� �������� ���� �����Ѵ�. �ٸ� �Է������� ��� overflow���� �� ����
	sendto(CiTs, str, strlen(str), 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

	char recv[20] = ""; //���������� �ڵ� 0 �ʱ�ȭ. ={0}; ���� �ʱ�ȭ�ص� ��
	int svrlen = sizeof(svrAddr);
	recvfrom(CiTs, recv, sizeof(recv), 0, (SOCKADDR*)&svrAddr, &svrlen);  //������ �������� ������ �� ���̴� �۽����� ������ �����ּ� ����ü�� �ٽ� ����
	//���ǿ����� recvfrom(CiTs, recv, sizeof(recv), 0, 0, 0); ���� �ΰ�ó����. ���� �ʿ䰡 ���ٴ� ��
	printf("���� ���� �޽��� : %s, ���ƿ� �޽��� : %s", str, recv);

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

	char msg[20] = "";
	recvfrom(SVRs, msg, sizeof(msg), 0, (SOCKADDR*)&CiTa, &CiTSize);  //Ŭ���̾�Ʈ�� ���� �޽����� Ŭ���̾�Ʈ�� ������ ����
	sendto(SVRs, msg, strlen(msg), 0, (SOCKADDR*)&CiTa, sizeof(CiTa)); //���� Ŭ���̾�Ʈ ������ ���� �ٽ� ����
	
	closesocket(SVRs);
	WSACleanup();

}