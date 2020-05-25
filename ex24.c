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

	//udp 통신은 송신데이터의 크기에 제한이 있다. 따라서 filebuf의 공간에 있는 값을 쪼개서 보내야 한다.

	char buf[1024];  //한번에 보낼 데이터 양
	memset(buf, 0, sizeof(buf));

	//즉 filebuf에 있는 것을 쪼개서 buf에 담은다음 보낼 것이다.
	int startIndex = 0;
	int sendingsize=1024;
	int remainedSize=fsize;

	while(1){
		memcpy(buf, &filebuf[startIndex], sendingsize);  //2번째 인자의 주소값을 따라가면 존재하는 값부터 3번째 인자 크기만큼 첫번째 인자 공간에 카피
		//처음에는 filebuf공간에서 [0] ~ [1023]만큼 즉, 1024바이트만큼 buf공간에 복사된다.

		sendingsize = sendto(CiTs, buf, sendingsize, 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

		printf("송신 데이터 크기 : %d\n", sendingsize);

		if(sendingsize==0)  //보내진게 없다면 더이상 보낼게 없다는 것이므로 종료
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
	//서버에서도 역시나 한번에 받을 수 없으므로 buf만큼 차례대로 받고 이를 특정공간에 누적하여 저장시켜놓아야 한다.

	char* recvbuf = (char*)malloc(fsize);
	memset(recvbuf, 0, fsize);

	int recvlen=0;
	int startIndex=0;

	while(1){
		recvlen = recvfrom(SVRs, buf, sizeof(buf), 0, (SOCKADDR*)&CiTa, &CiTSize);
		printf("수신 데이터 크기 : %d\n", recvlen);
		
		if(recvlen == 0)  //더이상 받은게 없다면 종료
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