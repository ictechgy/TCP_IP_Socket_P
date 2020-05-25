#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

void main(int argc, char* argv[]){  //프로그램 실행시 exe파일의 위치 및 서버의 IP주소, 찾기 시작할 포트번호, 찾기를 끝낼 끝 포트번호 가 argv로 들어올 것
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
		printf("서버의 포트주소는 %d입니다.\n", ntohs(svrAddr.sin_port)); //그냥 port 변수로 출력해도 됨
	}
	else{
		printf("서버가 닫혀있습니다.\n");
	}

	closesocket(CiTs);
	WSACleanup;
}