#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <process.h>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>  //udp����� ���ؼ� �� ����� ��

HANDLE hThread[2];
SOCKET UDPs;
SOCKADDR_IN Addr;
unsigned __stdcall func1(void* arg);
unsigned __stdcall func2(void* arg);

void main(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	UDPs = socket(AF_INET, SOCK_DGRAM, 0);
	if(UDPs == INVALID_SOCKET){
		printf("SOCKET ERROR!\n");
		return;
	}

	Addr.sin_addr.s_addr = inet_addr("192.168.148.129");
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(22222);

	int error=0;
	error = bind(UDPs, (SOCKADDR*)&Addr, sizeof(Addr));
	if(error == SOCKET_ERROR){
		printf("BIND ERROR!\n");
		return;
	}

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, NULL);

	WaitForMultipleObjects(2, hThread, FALSE, INFINITE);  //���ǿ����� TRUE�� �Ǿ��־����� �޽��������� ������ �����ϸ� �� ����ǰ� FALSE�� ����

	closesocket(UDPs);
	WSACleanup();

}

unsigned __stdcall func1(void* arg){
	int ttl=128;
	setsockopt(UDPs, IPPROTO_IP, IP_DEFAULT_MULTICAST_TTL, (char*)&ttl, sizeof(ttl));

	SOCKADDR_IN DstAddr;  //Destination Adddress
	DstAddr.sin_addr.s_addr = inet_addr("233.3.3.3");  //������ ��Ƽĳ��Ʈ �ּ�
	DstAddr.sin_family = AF_INET;
	DstAddr.sin_port = htons(22222);

	char sendBuf[512] = {0};
	int error=0;
	while(1){
		printf("[�Է�] > ");
		gets(sendBuf);   //���Ͱ��� �����ڷ� ��� �����͸� �Է¹޴´�. �����̽����� �Է� �����ϸ� �ٸ� �����÷ο� �߻��� �� ����

		error = sendto(UDPs, sendBuf, strlen(sendBuf), 0, (SOCKADDR*)&DstAddr, sizeof(DstAddr));
		if(error == SOCKET_ERROR){
			printf("SENTTO ERROR!!\n");
			return -1;
		}
		if(strcmp(sendBuf, "exit") == 0){
			sprintf(sendBuf, "%s���� ä�ù��� �������ϴ�.", inet_ntoa(Addr.sin_addr));
			sendto(UDPs, sendBuf, strlen(sendBuf), 0, (SOCKADDR*)&Addr, sizeof(Addr));
			// closesocket(UDPs); ���ǿ����� �־����� ������ ���ο��� ���� ������
			printf("���α׷� ����\n");
			break;
		}
	}
	return 0;
}

unsigned __stdcall func2(void* arg){
	struct ip_mreq multi;  //��Ƽĳ��Ʈ ������ ���� ����ü
	multi.imr_interface.s_addr = inet_addr("192.168.148.129");
	multi.imr_multiaddr.s_addr = inet_addr("233.3.3.3");

	setsockopt(UDPs, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multi, sizeof(multi));

	SOCKADDR_IN recvAddr;  //�޽��� ���� ����� ������ ��� ����
	int recvSize = sizeof(recvAddr);

	char recvBuf[512] = {0};
	int error=0;
	while(1){
		error = recvfrom(UDPs, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&recvAddr, &recvSize);
		if(error==SOCKET_ERROR){
			printf("RECVFROM ERROR!\n");
			return -1;
		}
		printf("[UDP %s:%d]\n", inet_ntoa(recvAddr.sin_addr), ntohs(recvAddr.sin_port));  //�޽����� ���� ������ IP�� �޽����� ���۵� ��Ʈ�� ��µȴ�.
		printf("[���] > %s\n", recvBuf);
	}

	//�� �����忡���� sending�ϴ� ������ ���Ḧ ��� �˾�ä�� ����� Ż�� �����Ű��?
	//��������� �� Ż�� �׳� ���ο��� �ϴ°� �����Ű�����
	setsockopt(UDPs, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&multi, sizeof(multi));

}

//�ٵ� �ڱ� �ڽŵ� ��Ƽĳ��Ʈ �뿪�� ���ԵǾ��־ �� �뿪�� �Ѹ� �޽����� �ڱ� �ڽŵ� �ް� �ȴ�.
//sendto�� recvfrom �� ���� ��������� �����ư��� ������ ������ �Ǵµ� �׷��� recvfrom�� ��� ���� �ȵǰ����� �� �޽��� ���� ������ ���� �ְڳ�