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

	char str[20]="Hello!!";
	//강의에서는 gets()로 문자를 입력받음. gets함수는 키보드로부터 값을 입력받으며 엔터값을 기준으로 값을 구분한다. 다만 입력제한이 없어서 overflow생길 수 있음
	sendto(CiTs, str, strlen(str), 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

	char recv[20] = ""; //나머지영역 자동 0 초기화. ={0}; 으로 초기화해도 됨
	int svrlen = sizeof(svrAddr);
	recvfrom(CiTs, recv, sizeof(recv), 0, (SOCKADDR*)&svrAddr, &svrlen);  //어차피 서버에서 정보가 올 것이니 송신자의 정보를 서버주소 구조체에 다시 담음
	//강의에서는 recvfrom(CiTs, recv, sizeof(recv), 0, 0, 0); 으로 널값처리함. 받을 필요가 없다는 뜻
	printf("내가 보낸 메시지 : %s, 돌아온 메시지 : %s", str, recv);

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

	char msg[20] = "";
	recvfrom(SVRs, msg, sizeof(msg), 0, (SOCKADDR*)&CiTa, &CiTSize);  //클라이언트가 보낸 메시지와 클라이언트의 정보를 담음
	sendto(SVRs, msg, strlen(msg), 0, (SOCKADDR*)&CiTa, sizeof(CiTa)); //받은 클라이언트 정보를 토대로 다시 보냄
	
	closesocket(SVRs);
	WSACleanup();

}