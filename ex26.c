#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

void sender(){  //��ε�ĳ��Ʈ�� �޽����� �Ѹ� ���
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SDs;
	SDs = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN Addr;
	memset(&Addr, 0, sizeof(Addr));
	Addr.sin_addr.s_addr=inet_addr("192.168.52.255");
	Addr.sin_port = htons(12345);
	Addr.sin_family = AF_INET;

	BOOL opt = TRUE;  //BOOL���� int�� ����ü
	setsockopt(SDs, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt));

	char sendbuf[1024];
	memset(sendbuf, 0, sizeof(sendbuf));

	printf("�޽��� �Է� : ");
	scanf("%s", sendbuf);

	int output=0;
	output = sendto(SDs, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&Addr, sizeof(Addr));
	printf("�۽ŵ� ������ ũ�� : %d\n", output);


	//���࿡ ���������� �ѷȴٸ�, - ���� ���� �������� ��� ȸ�� ��� �κ�

	int time = 10000; //10��
	setsockopt(SDs, SOL_SOCKET,SO_RCVTIMEO, (char*)&time, sizeof(time));

	int one=0,two=0,three=0,four=0, select;
	int navi;
	while(1){
		navi = recvfrom(SDs, (char*)&select, sizeof(select), 0, 0, 0); //���� ���´��� ������ ���� �ʿ�� ���� ��.
		if(navi==-1) break;
		switch(select){
		case 1: one++; break;
		case 2: two++; break;
		case 3: three++; break;
		case 4: four++; break;
		default:
		}//������ ���ƿ� ������ recvfrom�� �Լ��� �۵��ϰ� �� ��������� ���� ���̴�. �׸��� ������ ���ƿ��� �ϴ� recvfrom()�Լ��� �ٽ� �۵����״�
	}	//10�ʾ� ���� ��ٸ� ���̴�. �ٵ� ������ �� ���� ���̻� ���� �ȿ��� ���� ���� �����״� navi=-1�� �ɰŰ� �� �� �ݺ����� �����Ѵ�.
	//�ƹ��͵� �޾ƿ��� ���ϰ� Ÿ�Ӿƿ��Ȱ�� -1�� ��ȯ�ȴ�.

	printf("��� %d, %d, %d, %d\n", one, two, three, four);



	//���ú���� ũ�⸦ Ȯ���غ���
	int rcvBufSize=0;
	int rcvBufSizeLen=sizeof(rcvBufSize);

	getsockopt(SDs, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBufSize, &rcvBufSizeLen);
	printf("���ú� ������ ũ�� : %d\n", rcvBufSize);

	//���ú������ ũ�⸦ �����غ���
	rcvBufSize *=2;
	setsockopt(SDs, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBufSize, rcvBufSizeLen);

	//Ÿ�Ӿƿ� ����
	opt = 3000;
	setsockopt(SDs, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, sizeof(opt));
	setsockopt(SDs, SOL_SOCKET, SO_SNDTIMEO, (char*)&opt, sizeof(opt));


	//����
	sprintf(sendbuf, "[����] �ڽ��� ��ȣ�ϴ� ���θ� �����ÿ�.\n1.���α׷���\n2.��Ʈ��ũ������\n3.�ý��۰�����\n4.���Ȱ�����\n");
	sendto(SDs, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&Addr, sizeof(Addr));

	int result = 0;
	int errch = 0;

	int timeopt=10000;
	setsockopt(SDs, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeopt, sizeof(timeopt));

	int data[5] = {0, 0, 0, 0, 0};

	while(1){
		errch = recvfrom(SDs, (char*)&result, sizeof(result), 0, NULL, 0);
		if(errch == SOCKET_ERROR) break;  //recvfrom�� Ÿ�Ӿƿ��� ���� ���ᰡ �ȴٸ� SOCKET_ERROR�� ��ȯ�ȴ�. (-1��)
		printf("%d\n", result);
		data[result]++;
	}

	printf("#################�������� ��� ##################\n");
	for(int i=1; i<5; i++){
		printf("%d�� : %d�� \n", i, data[i]);
	}
	//�ٵ� ���ù��ʿ��� �亯�� ���¾ ����� ������ ���� �ִ�. (UDP����� Ư¡)

	closesocket(SDs);
	WSACleanup();

}

void receiver(){  //������ ���� ��Ʈ��ũ�� �����ϴ� �� ���ù�
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

	//���������� �Դٸ�
	int choice;
	printf("�亯 �Է� : ");
	scanf("%d", &choice);
	sendto(RCVs, (char*)&choice, sizeof(choice), 0, (SOCKADDR*)&SDAddr, sizeof(SDAddr));

	
	closesocket(RCVs);
	WSACleanup;
}


