#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include <time.h>

void sender(){  //��Ƽĳ��Ʈ�� �ð����� �Ѹ� ���
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SDs;
	SDs = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN Addr;
	memset(&Addr, 0, sizeof(Addr));
	Addr.sin_addr.s_addr=inet_addr("233.3.3.3");  //������ ��Ƽĳ��Ʈ �ּ�
	Addr.sin_port = htons(12345);
	Addr.sin_family = AF_INET;

	int ttl = 64;  //�� ��Ƽĳ��Ʈ�� TTL�� �����ұ�
	setsockopt(SDs, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl));
	
	char buf[1024] = {0};
	time_t tm;
	struct tm* lt;
	int sendsize = 0;
	int i = 0;

	while(i<10){
		time(&tm);
		lt = localtime(&tm);
		sprintf(buf, "%d�� %d�� %d�� %d�� %d�� %d��\n", lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);

		sendto(SDs, buf, strlen(buf), 0, (SOCKADDR*)&Addr, sizeof(Addr));
		printf("%d�� ����!\n", i+1);
		i++;
		Sleep(1000);
	}

	closesocket(SDs);
	WSACleanup();

}

void receiver(){  //��Ƽĳ��Ʈ �׷쿡 ���Ե� ���ù�
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

	int timeout = 5000;
	setsockopt(RCVs, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

	char buf[1024] = {0};
	int result;
	while(1){
		result = recvfrom(RCVs, buf, sizeof(buf), 0, 0, 0);
		if(result == -1){
			break;
		}
		printf("���� ������ : %s\n", buf);
	}

	setsockopt(RCVs, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&multi, sizeof(multi));
	
	closesocket(RCVs);
	WSACleanup;
}


