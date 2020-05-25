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


	FILE* fp = fopen("c:\\data.txt", "rb");
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	

	send(CiTs, (char*)&fsize, sizeof(fsize), 0);	//int형 변수의 주소를 char* 형으로 강제 형변환한다는건 무슨의미일까. int형변수를 char형 포인터변수가 바라보고 있으면
	//이 char형 포인터변수로는 1바이트밖에 값을 못읽을텐데??
	//그냥 매개변수형을 맞추기 위해 임시로 맞추기만 해주는 거고 결국 fsize변수 시작주소에서 sizeof(fsize) 크기만큼 읽어서 값을 보내는 거니 상관없음?
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

	char* recvbuf = (char*)malloc(fsize+1); //맨 마지막부분에 널값을 넣기 위해 공간 하나 더 생성
	memset(recvbuf, 0, fsize+1); 

	recv(CiTs, recvbuf, fsize, 0);
	printf("수신한 데이터 : %s\n", recvbuf);  //널 공간이 있어야 여기서 데이터를 제대로 출력할 수 있다. 없으면 뒤의 쓰레기값까지 출력

	FILE* fp = fopen("c:\\data.txt", "ab");  //append binary
	fwrite(recvbuf, 1, fsize, fp);


	fclose(fp);
	free(recvbuf);
	closesocket(CiTs); //서버에서는 클라이언트 소켓도 닫아줘야 하는건가?
	closesocket(SVRs);
	WSACleanup();

}