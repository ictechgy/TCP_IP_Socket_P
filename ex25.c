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
	printf("��� �Է� : ");
	scanf("%s", path);
	sendto(CiTs, path, strlen(path), 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

	int datasize=0;
	recvfrom(CiTs, (char*)&datasize, sizeof(datasize), 0, 0, 0); //�������� ũ�� ������ �������� ������ �״� �ּұ���ü �ȳ���
	printf("������ ũ�� : %d\n", datasize);

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
		printf("���ŵ����� ũ�� : %d\n", recvSize);
		memcpy(&recvBuf[startIndex], buf, recvSize);
		startIndex+=recvSize;
	}

	FILE* fp = fopen("C:\\picture.jpg", "wb");
	fwrite(recvBuf, datasize, 1, fp); //datasize��ŭ �ѹ��� �ݺ��Ͽ� �ְڴ�.(�ѹ��� �����͸� ���Ͽ� ���)
	
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
	printf("��� : %s\n", path);

	FILE* fp = fopen(path, "rb");
	fseek(fp, 0, SEEK_END);
	int datasize = ftell(fp);
	printf("%d\n", datasize);

	sendto(SVRs, (char*)&datasize, sizeof(datasize), 0, (SOCKADDR*)&CiTa, sizeof(CiTa));


	char* fileBuf = (char*)malloc(datasize);
	memset(fileBuf, 0, datasize);

	fseek(fp, 0, SEEK_SET);
	fread(fileBuf, datasize, 1, fp); //fp�� ����Ű�� ������ ������ datasize��ŭ 1���� �ݺ��Ͽ� fileBuf�� ��ڴ�. (�ѹ��� �����͸� ��ڴ�)

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

		printf("������ �۽� : %d\n", output);
	}


	free(fileBuf);
	fclose(fp);
	closesocket(SVRs);
	WSACleanup();

}