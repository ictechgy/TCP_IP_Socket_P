#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

void sender(){  //브로드캐스트로 메시지를 뿌릴 사람
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SDs;
	SDs = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN Addr;
	memset(&Addr, 0, sizeof(Addr));
	Addr.sin_addr.s_addr=inet_addr("192.168.52.255");
	Addr.sin_port = htons(12345);
	Addr.sin_family = AF_INET;

	BOOL opt = TRUE;  //BOOL형은 int형 구조체
	setsockopt(SDs, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt));

	char sendbuf[1024];
	memset(sendbuf, 0, sizeof(sendbuf));

	printf("메시지 입력 : ");
	scanf("%s", sendbuf);

	int output=0;
	output = sendto(SDs, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&Addr, sizeof(Addr));
	printf("송신된 데이터 크기 : %d\n", output);


	//만약에 설문내용을 뿌렸다면, - 내가 만든 설문조사 결과 회수 출력 부분

	int time = 10000; //10초
	setsockopt(SDs, SOL_SOCKET,SO_RCVTIMEO, (char*)&time, sizeof(time));

	int one=0,two=0,three=0,four=0, select;
	int navi;
	while(1){
		navi = recvfrom(SDs, (char*)&select, sizeof(select), 0, 0, 0); //누가 보냈는지 일일히 받을 필요는 없을 듯.
		if(navi==-1) break;
		switch(select){
		case 1: one++; break;
		case 2: two++; break;
		case 3: three++; break;
		case 4: four++; break;
		default:
		}//선택이 돌아올 때마다 recvfrom의 함수는 작동하고 그 결과값들은 쌓일 것이다. 그리고 선택이 돌아오면 일단 recvfrom()함수는 다시 작동할테니
	}	//10초씩 새로 기다릴 것이다. 근데 선택이 다 오고 더이상 값이 안오면 받은 값은 없을테니 navi=-1이 될거고 그 때 반복문을 종료한다.
	//아무것도 받아오지 못하고 타임아웃된경우 -1이 반환된다.

	printf("결과 %d, %d, %d, %d\n", one, two, three, four);



	//리시브버퍼 크기를 확인해보자
	int rcvBufSize=0;
	int rcvBufSizeLen=sizeof(rcvBufSize);

	getsockopt(SDs, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBufSize, &rcvBufSizeLen);
	printf("리시브 버퍼의 크기 : %d\n", rcvBufSize);

	//리시브버퍼의 크기를 변경해보자
	rcvBufSize *=2;
	setsockopt(SDs, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBufSize, rcvBufSizeLen);

	//타임아웃 설정
	opt = 3000;
	setsockopt(SDs, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, sizeof(opt));
	setsockopt(SDs, SOL_SOCKET, SO_SNDTIMEO, (char*)&opt, sizeof(opt));


	//강의
	sprintf(sendbuf, "[질문] 자신이 선호하는 진로를 고르시오.\n1.프로그래머\n2.네트워크관리자\n3.시스템관리자\n4.보안관리자\n");
	sendto(SDs, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&Addr, sizeof(Addr));

	int result = 0;
	int errch = 0;

	int timeopt=10000;
	setsockopt(SDs, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeopt, sizeof(timeopt));

	int data[5] = {0, 0, 0, 0, 0};

	while(1){
		errch = recvfrom(SDs, (char*)&result, sizeof(result), 0, NULL, 0);
		if(errch == SOCKET_ERROR) break;  //recvfrom이 타임아웃에 의해 종료가 된다면 SOCKET_ERROR가 반환된다. (-1값)
		printf("%d\n", result);
		data[result]++;
	}

	printf("#################설문조사 결과 ##################\n");
	for(int i=1; i<5; i++){
		printf("%d번 : %d명 \n", i, data[i]);
	}
	//근데 리시버쪽에서 답변을 보냈어도 제대로 못받을 수도 있다. (UDP통신의 특징)

	closesocket(SDs);
	WSACleanup();

}

void receiver(){  //샌더와 같은 네트워크상에 존재하는 한 리시버
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	SOCKET RCVs;
	RCVs = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN myAddr;
	memset(&myAddr, 0, sizeof(myAddr));
	myAddr.sin_addr.s_addr=inet_addr("192.168.52.72");
	myAddr.sin_port = htons(12345);
	myAddr.sin_family = AF_INET;

	bind(RCVs, (SOCKADDR*)&myAddr, sizeof(myAddr));

	SOCKADDR_IN SDAddr;
	memset(&SDAddr, 0, sizeof(SDAddr));
	int SDsize = sizeof(SDAddr);

	char recvbuf[1024];
	memset(recvbuf, 0, sizeof(recvbuf));

	recvfrom(RCVs, recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&SDAddr, &SDsize);
	printf("%s\n", recvbuf);

	//설문같은게 왔다면
	int choice;
	printf("답변 입력 : ");
	scanf("%d", &choice);
	sendto(RCVs, (char*)&choice, sizeof(choice), 0, (SOCKADDR*)&SDAddr, sizeof(SDAddr));

	
	closesocket(RCVs);
	WSACleanup;
}



