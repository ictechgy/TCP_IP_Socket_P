#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

void client(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	SOCKET CiTs;
	CiTs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN svrAddr;
	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_addr.s_addr=inet_addr("192.168.52.2");
	svrAddr.sin_port = htons(12345);
	svrAddr.sin_family = AF_INET;

	connect(CiTs, (SOCKADDR*)(&svrAddr), sizeof(svrAddr));


	FILE* fp = fopen("c:\\picture.jpg", "rb");
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	

	send(CiTs, (char*)&fsize, sizeof(fsize), 0);
	char* sendbuf = (char*)malloc(fsize);
	memset(sendbuf, 0, fsize);
	fread(sendbuf, 1, fsize, fp);
	fclose(fp);
	
	int size;
	size = send(CiTs, sendbuf, fsize, 0);
	printf("송신 데이터 크기 : %d\n", size);

	
	free(sendbuf);
	closesocket(CiTs);
	WSACleanup;
}

void server(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SVRs;
	SVRs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN SVRa;
	memset(&SVRa, 0, sizeof(SVRa));
	SVRa.sin_addr.s_addr=inet_addr("192.168.52.2");
	SVRa.sin_port = htons(12345);
	SVRa.sin_family = AF_INET;

	bind(SVRs, (SOCKADDR*)(&SVRa), sizeof(SVRa));
	listen(SVRs, SOMAXCONN);

	SOCKET CiTs;
	SOCKADDR_IN CiTa;
	memset(&CiTa, 0, sizeof(CiTa));
	int CiTSize = sizeof(CiTa);

	CiTs = accept(SVRs, (SOCKADDR*)(&CiTa), &CiTSize);

	int fsize=0;
	recv(CiTs, (char*)&fsize, sizeof(fsize), 0);

	char* recvbuf = (char*)malloc(fsize);
	memset(recvbuf, 0, fsize); 
	
	int recvsize=0;
	recvsize = recv(CiTs, recvbuf, fsize, 0);
	printf("수신한 데이터의 크기 : %d\n", recvsize);

	FILE* fp = fopen("c:\\picture.jpg", "wb");  
	fwrite(recvbuf, 1, fsize, fp);


	fclose(fp);
	free(recvbuf);
	closesocket(CiTs); 
	closesocket(SVRs);
	WSACleanup();

}