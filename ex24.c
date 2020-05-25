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

	FILE* fp = fopen("C:\\picture.jpg", "rb");
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);

	sendto(CiTs, (char*)&fsize, sizeof(fsize), 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

	char* filebuf = (char*)malloc(fsize);
	memset(filebuf, 0, fsize);

	fseek(fp, 0, SEEK_SET);
	fread(filebuf, 1, fsize, fp);

	//udp ����� �۽ŵ������� ũ�⿡ ������ �ִ�. ���� filebuf�� ������ �ִ� ���� �ɰ��� ������ �Ѵ�.

	char buf[1024];  //�ѹ��� ���� ������ ��
	memset(buf, 0, sizeof(buf));

	//�� filebuf�� �ִ� ���� �ɰ��� buf�� �������� ���� ���̴�.
	int startIndex = 0;
	int sendingsize=1024;
	int remainedSize=fsize;

	while(1){
		memcpy(buf, &filebuf[startIndex], sendingsize);  //2��° ������ �ּҰ��� ���󰡸� �����ϴ� ������ 3��° ���� ũ�⸸ŭ ù��° ���� ������ ī��
		//ó������ filebuf�������� [0] ~ [1023]��ŭ ��, 1024����Ʈ��ŭ buf������ ����ȴ�.

		sendingsize = sendto(CiTs, buf, sendingsize, 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

		printf("�۽� ������ ũ�� : %d\n", sendingsize);

		if(sendingsize==0)  //�������� ���ٸ� ���̻� ������ ���ٴ� ���̹Ƿ� ����
			break;

		remainedSize -= sendingsize;

		startIndex+= sendingsize;

		if (remainedSize < sendingsize)
			sendingsize = remainedSize;
	}



	free(filebuf);
	fclose(fp);
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


	int fsize=0;
	recvfrom(SVRs, (char*)&fsize, sizeof(fsize), 0, (SOCKADDR*)&CiTa, &CiTSize);

	char buf[1024];
	memset(buf, 0, sizeof(buf));
	//���������� ���ó� �ѹ��� ���� �� �����Ƿ� buf��ŭ ���ʴ�� �ް� �̸� Ư�������� �����Ͽ� ������ѳ��ƾ� �Ѵ�.

	char* recvbuf = (char*)malloc(fsize);
	memset(recvbuf, 0, fsize);

	int recvlen=0;
	int startIndex=0;

	while(1){
		recvlen = recvfrom(SVRs, buf, sizeof(buf), 0, (SOCKADDR*)&CiTa, &CiTSize);
		printf("���� ������ ũ�� : %d\n", recvlen);
		
		if(recvlen == 0)  //���̻� ������ ���ٸ� ����
			break;

		memcpy(&recvbuf[startIndex], buf, recvlen);
		startIndex+=recvlen;
	}

	FILE* fp = fopen("C:\\picture.jpg", "wb");
	fwrite(recvbuf, 1, fsize, fp);

	free(recvbuf);
	fclose(fp);	
	closesocket(SVRs);
	WSACleanup();

}