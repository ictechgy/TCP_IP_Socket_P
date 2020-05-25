#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>
#include <WS2tcpip.h>

typedef struct msg{
	int a_num;
	char q_str[512];
}_msg;

void sender(){  
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SDs;
	SDs = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN Addr;
	memset(&Addr, 0, sizeof(Addr));
	Addr.sin_addr.s_addr=inet_addr("233.3.3.3");  //��Ƽĳ��Ʈ ���� �뿪�� ����
	Addr.sin_port = htons(12345);
	Addr.sin_family = AF_INET;

	int ttl = 32;		//ttl�� ����
	setsockopt(SDs, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl));

	_msg msg;
	memset(&msg, 0, sizeof(msg));
	sprintf(msg.q_str, "[����] �ڽ��� ��ȣ�ϴ� ���θ� �����ÿ�.\n1.���α׷���\n2.��Ʈ��ũ������\n3.�ý��۰�����\n4.���Ȱ�����\n");
	printf("%s", msg.q_str);

	sendto(SDs, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&Addr, sizeof(Addr));

	int rcvtime = 10000;
	setsockopt(SDs, SOL_SOCKET, SO_RCVTIMEO, (char*)&rcvtime, sizeof(rcvtime));

	int total[5] = {0};
	int verify;

	while(1){
		verify = recvfrom(SDs, (char*)&msg, sizeof(msg), 0, 0, 0);
		if (verify == -1){
			break;
		}
		if (msg.a_num >= 1 && msg.a_num<=4){
			total[msg.a_num]++;
		}
	}
	printf("\n### �������� ��� ###\n");
	for(int i=1; i<5; i++){
		printf("%d�� : %d��\n", i, total[i]);
	}

	closesocket(SDs);
	WSACleanup();

}

void receiver(){  
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

	struct ip_mreq multi;
	multi.imr_interface.s_addr = inet_addr("192.168.52.72");
	multi.imr_multiaddr.s_addr = inet_addr("233.3.3.3");

	setsockopt(RCVs, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multi, sizeof(multi));

	SOCKADDR_IN SDAddr;
	memset(&SDAddr, 0, sizeof(SDAddr));
	int SDsize = sizeof(SDAddr);

	_msg msg = {0};

	recvfrom(RCVs, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&SDAddr, &SDsize);
	printf("%s\n", msg.q_str);
	printf("�亯 �Է� : ");
	scanf("%d", &msg.a_num);

	sendto(RCVs, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&SDAddr, sizeof(SDAddr));

	setsockopt(RCVs, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&multi, sizeof(multi));
	
	closesocket(RCVs);
	WSACleanup;
}


