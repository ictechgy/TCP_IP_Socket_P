#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

void main(int argc, char* argv[]){
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SRVs;
	SRVs = socket(AF_INET, SOCK_STREAM,0);
	if(SRVs==INVALID_SOCKET){
		printf("소켓 생성 오류");
		return;
	}

	SOCKADDR_IN SRVi;
	memset(&SRVi, 0, sizeof(SRVi));
	SRVi.sin_family = AF_INET;
	SRVi.sin_port = htons(12345);
	SRVi.sin_addr.S_un.S_addr = inet_addr("192.168.139.134");

	int error=0;
	error = bind(SRVs, (sockaddr*)(&SRVi), sizeof(SRVi)); //소켓과 소켓주소구조체를 결합하여 운영체제로부터 허락받기
	if(error == SOCKET_ERROR){
		printf("소켓과 소켓주소정보구조체를 결합하는 과정에서 오류가 발생하였습니다.-bind()오류");
		return;
	}

	error = listen(SRVs, SOMAXCONN);
	if(error == SOCKET_ERROR){
		printf("소켓의 상태를 listen상태로 변경하는 과정에서 오류가 발생하였습니다.-listen()오류");
		return;
	}

	SOCKET CiTs;
	SOCKADDR_IN CiTa;
	memset(&CiTa, 0, sizeof(CiTa));
	int CiTaLen = sizeof(CiTa);

	CiTs = accept(SRVs, (sockaddr*)(&CiTa), &CiTaLen);
	if(CiTs == INVALID_SOCKET){
		printf("클라이언트의 접속요청을 accept()하는 과정에서 오류가 발생하였습니다.");
		return;
	}

	//접속한 클라이언트의 정보 출력하기
	printf("접속한 클라이언트의 IP주소는 %s 이고 포트번호는 %d입니다\n", inet_ntoa(CiTa.sin_addr), ntohs(CiTa.sin_port));


	char msg[100];
	int len;
	len = recv(CiTs, msg, sizeof(msg), 0);   //len에는 메시지 받은 총 크기 들어가 있을 것

	//접속한 클라이언트의 메시지를 재송신하기(ECHO 서버 구현)
	len = send(CiTs, msg, strlen(msg), 0);  //len에는 보내기 성공한 총 크기가 들어갈 것이며, 보낼 때에는 msg에 담겨있는 값만큼만 보내도 되니 strlen()을 썼다.

	closesocket(SRVs);
	WSACleanup();

}