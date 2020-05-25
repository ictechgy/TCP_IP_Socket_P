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

	char msg[256] = "�ð��� �ٷ���!!";
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
	printf("Ŭ���̾�Ʈ�� ���� �޽��� : %s\n", msg);

	time_t tm;  //1970�� 1�� 1�Ϻ��� ������ �ð� �ʰ��� ������ �� �ִ� 64��Ʈ int �ڷ��� ����ü. time()�Լ��� ���� ��ȯ�Ǵ� ���� �����ϸ� �ȴ�.
	time(&tm); //1970�� 1�� 1�Ϻ��� ������ �ð� �ʰ��� ��ȯ�ϴ� �Լ�. ���ڷ� time_t ����ü ������ �ּҰ��� �־��ָ� �� ������ ���� ���嵵 �����ش�.
	struct tm* lt = localtime(&tm);
	//tm����ü�� �������� time������ �����Ͽ� ������ �� �ִ� ����ü�̴�. 
	//localtime()�Լ��� ���ڷ� ���� time_t�� �ּҸ� ã�ư��� ������ �ʰ��� �̿��Ͽ� tm����ü ������ ���� �� �� ����ü�� �ʱ�ȭ��Ų��.
	//���Ŀ� �� tm����ü�� ����Ű�� �ּҰ��� �����Ѵ�.

	char time[512];
	memset(time, 0, sizeof(time));
	
	sprintf(time, "������ %d�� %d�� %d�� ���� �ð��� %d�� %d�� �Դϴ�.\n", lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min);
	//sprintf()�Լ��� ����ȭ�� ���ڿ��� ������ ���ڿ������� �����ϴ� �Լ��̴�. ũ�⸦ �����ϴ� ���ڰ� �����Ƿ� �����÷ο� ������ �߻��� �� �ִ�.
	//tm����ü������ �⵵���� 1900�⵵ ���ĺ��� ���� ������ ����Ǿ������Ƿ� ���� 1900�� �����־�� �Ѵ�.
	//��ǻ�Ϳ��� ���� 0~11�� ���Ƿ� 1�� �����༭ �־�� �Ѵ�.(�ڹٿ� ����)

	sendto(SVRs, time, strlen(time), 0, (SOCKADDR*)&CiTa, sizeof(CiTa));
	
	
	closesocket(SVRs);
	WSACleanup();

}