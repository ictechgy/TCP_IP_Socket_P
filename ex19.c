#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

void main(int argc, char* argv[]){  //���α׷� ����� exe������ ��ġ �� ������ IP�ּ�, ã�� ������ ��Ʈ��ȣ, ã�⸦ ���� �� ��Ʈ��ȣ �� argv�� ���� ��
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	SOCKET CiTs;
	CiTs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN svrAddr;
	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_addr.s_addr=inet_addr(argv[1]);
	svrAddr.sin_family = AF_INET;

	int start = atoi(argv[2]);
	int end = atoi(argv[3]);

	int chk=0;
	int port;
	for(port=start; port<=end; port++){
		svrAddr.sin_port = htons(port);
		chk = connect(CiTs, (SOCKADDR*)(&svrAddr), sizeof(svrAddr));
		if(chk!=SOCKET_ERROR) break;
	}

	if(chk!=SOCKET_ERROR) {
		printf("������ ��Ʈ�ּҴ� %d�Դϴ�.\n", ntohs(svrAddr.sin_port)); //�׳� port ������ ����ص� ��
	}
	else{
		printf("������ �����ֽ��ϴ�.\n");
	}

	closesocket(CiTs);
	WSACleanup;
}