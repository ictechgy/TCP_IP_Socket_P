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

	char path[256];
	memset(path, 0, sizeof(path));
	printf("경로 입력 : ");
	scanf("%s", path);
	sendto(CiTs, path, strlen(path), 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

	int datasize=0;
	recvfrom(CiTs, (char*)&datasize, sizeof(datasize), 0, 0, 0); //데이터의 크기 어차피 서버에서 보냈을 테니 주소구조체 안넣음
	printf("데이터 크기 : %d\n", datasize);

	char* recvBuf = (char*)malloc(datasize);
	memset(recvBuf, 0, datasize);

	char buf[1024];
	memset(buf, 0, sizeof(buf));
	
	int startIndex=0;
	int recvSize=0;

	while(1){
		recvSize = recvfrom(CiTs, buf, sizeof(buf), 0, 0, 0);
		if(recvSize==0)
			break;
		printf("수신데이터 크기 : %d\n", recvSize);
		memcpy(&recvBuf[startIndex], buf, recvSize);
		startIndex+=recvSize;
	}

	FILE* fp = fopen("C:\\picture.jpg", "wb");
	fwrite(recvBuf, datasize, 1, fp); //datasize만큼 한번만 반복하여 넣겠다.(한번에 데이터를 파일에 출력)
	
	fclose(fp);
	free(recvBuf);
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


	char path[256];
	memset(path, 0, sizeof(path));
	recvfrom(SVRs, path, sizeof(path), 0, (SOCKADDR*)&CiTa, &CiTSize);
	printf("경로 : %s\n", path);

	FILE* fp = fopen(path, "rb");
	fseek(fp, 0, SEEK_END);
	int datasize = ftell(fp);
	printf("%d\n", datasize);

	sendto(SVRs, (char*)&datasize, sizeof(datasize), 0, (SOCKADDR*)&CiTa, sizeof(CiTa));


	char* fileBuf = (char*)malloc(datasize);
	memset(fileBuf, 0, datasize);

	fseek(fp, 0, SEEK_SET);
	fread(fileBuf, datasize, 1, fp); //fp가 가리키는 파일의 내용을 datasize만큼 1번만 반복하여 fileBuf에 담겠다. (한번에 데이터를 담겠다)

	char buf[1024];
	memset(buf, 0, sizeof(buf));

	int sendingSize = sizeof(buf);  //1024
	int startIndex = 0;
	
	int output = 0;

	while(1){
		memcpy(buf, &fileBuf[startIndex], sendingSize);
		output = sendto(SVRs, buf, sendingSize, 0, (SOCKADDR*)&CiTa, sizeof(CiTa));
		if(output==0)
			break;
		
		datasize -= output;

		if(datasize<output)
			sendingSize = datasize;

		startIndex+=output;

		printf("데이터 송신 : %d\n", output);
	}


	free(fileBuf);
	fclose(fp);
	closesocket(SVRs);
	WSACleanup();

}