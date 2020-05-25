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

	char route[100];
	memset(route, 0, sizeof(route));
	printf("파일의 경로와 파일명을 입력하세요 : ");
	scanf("%s", route);
	send(CiTs, route, strlen(route), 0);

	int fsize;
	recv(CiTs, (char*)(&fsize), sizeof(fsize), 0);
	char* fptr = (char*)malloc(fsize);
	recv(CiTs, fptr, fsize, 0);

	FILE* fp = fopen("c:\\picture.jpg", "wb");
	fwrite(fptr, 1, fsize, fp);


	fclose(fp);
	free(fptr);
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

	char route[100];
	memset(route, 0, sizeof(route));
	recv(CiTs, route, sizeof(route), 0);
	FILE* fp = fopen(route, "rb");

	int fsize=0;
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);

	send(CiTs, (char*)&fsize, sizeof(fsize), 0);
	char* fptr = (char*)malloc(fsize);

	fseek(fp, 0, SEEK_SET);
	fread(fptr, 1, fsize, fp);
	send(CiTs, fptr, fsize, 0);
	
	fclose(fp);
	free(fptr);
	closesocket(CiTs); 
	closesocket(SVRs);
	WSACleanup();

}