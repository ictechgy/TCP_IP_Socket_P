#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

void client(){
	//파일을 하나 만들었다고 가정한다.
	FILE* fp = fopen("c:\\Test.txt", "r");
	char msg[100];
	fread(msg, 1, 100, fp);  //파일의 내용을 읽는 방법은 여러가지
	fclose(fp);

	WSAData wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET CiTs;
	CiTs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN srvAddr;
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = inet_addr("192.168.139.134");
	srvAddr.sin_port = htons(12345);

	connect(CiTs, (sockaddr*)(&srvAddr), sizeof(srvAddr));

	send(CiTs, msg, strlen(msg), 0);

	closesocket(CiTs);
	WSACleanup();
	
}

void server(){
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SRVs;
	SRVs = socket(AF_INET, SOCK_STREAM,0);

	SOCKADDR_IN SRVi;
	memset(&SRVi, 0, sizeof(SRVi));
	SRVi.sin_family = AF_INET;
	SRVi.sin_port = htons(12345);
	SRVi.sin_addr.S_un.S_addr = inet_addr("192.168.139.134");

	bind(SRVs, (sockaddr*)(&SRVi), sizeof(SRVi));

	listen(SRVs, SOMAXCONN);

	SOCKET CiTs;
	SOCKADDR_IN CiTa;
	memset(&CiTa, 0, sizeof(CiTa));
	int CiTaLen = sizeof(CiTa);
	CiTs = accept(SRVs, (sockaddr*)(&CiTa), &CiTaLen);

	char msg[100];
	recv(CiTs, msg, sizeof(msg), 0);

	FILE* fp = fopen("c:\\Test.txt", "w");
	fwrite(msg, 1, sizeof(msg), fp);
	fclose(fp);


	closesocket(SRVs);
	WSACleanup();
}

void main(){

}