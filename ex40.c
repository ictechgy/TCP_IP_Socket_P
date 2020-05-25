#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <process.h>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>  //udp통신을 위해서 꼭 해줘야 함

HANDLE hThread[2];
SOCKET UDPs;
SOCKADDR_IN Addr;
unsigned __stdcall func1(void* arg);
unsigned __stdcall func2(void* arg);

void main(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	UDPs = socket(AF_INET, SOCK_DGRAM, 0);
	if(UDPs == INVALID_SOCKET){
		printf("SOCKET ERROR!\n");
		return;
	}

	Addr.sin_addr.s_addr = inet_addr("192.168.148.129");
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(22222);

	int error=0;
	error = bind(UDPs, (SOCKADDR*)&Addr, sizeof(Addr));
	if(error == SOCKET_ERROR){
		printf("BIND ERROR!\n");
		return;
	}

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, NULL);

	WaitForMultipleObjects(2, hThread, FALSE, INFINITE);  //강의에서는 TRUE로 되어있었지만 메시지보내는 스레드 종료하면 다 종료되게 FALSE로 만듬

	closesocket(UDPs);
	WSACleanup();

}

unsigned __stdcall func1(void* arg){
	int ttl=128;
	setsockopt(UDPs, IPPROTO_IP, IP_DEFAULT_MULTICAST_TTL, (char*)&ttl, sizeof(ttl));

	SOCKADDR_IN DstAddr;  //Destination Adddress
	DstAddr.sin_addr.s_addr = inet_addr("233.3.3.3");  //목적지 멀티캐스트 주소
	DstAddr.sin_family = AF_INET;
	DstAddr.sin_port = htons(22222);

	char sendBuf[512] = {0};
	int error=0;
	while(1){
		printf("[입력] > ");
		gets(sendBuf);   //엔터값을 구분자로 삼고 데이터를 입력받는다. 스페이스값도 입력 가능하며 다만 오버플로우 발생할 수 있음

		error = sendto(UDPs, sendBuf, strlen(sendBuf), 0, (SOCKADDR*)&DstAddr, sizeof(DstAddr));
		if(error == SOCKET_ERROR){
			printf("SENTTO ERROR!!\n");
			return -1;
		}
		if(strcmp(sendBuf, "exit") == 0){
			sprintf(sendBuf, "%s님이 채팅방을 나갔습니다.", inet_ntoa(Addr.sin_addr));
			sendto(UDPs, sendBuf, strlen(sendBuf), 0, (SOCKADDR*)&Addr, sizeof(Addr));
			// closesocket(UDPs); 강의에서는 있었지만 어차피 메인에서 닫을 소켓임
			printf("프로그램 종료\n");
			break;
		}
	}
	return 0;
}

unsigned __stdcall func2(void* arg){
	struct ip_mreq multi;  //멀티캐스트 가입을 위한 구조체
	multi.imr_interface.s_addr = inet_addr("192.168.148.129");
	multi.imr_multiaddr.s_addr = inet_addr("233.3.3.3");

	setsockopt(UDPs, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multi, sizeof(multi));

	SOCKADDR_IN recvAddr;  //메시지 보낸 사람의 정보를 담기 위함
	int recvSize = sizeof(recvAddr);

	char recvBuf[512] = {0};
	int error=0;
	while(1){
		error = recvfrom(UDPs, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&recvAddr, &recvSize);
		if(error==SOCKET_ERROR){
			printf("RECVFROM ERROR!\n");
			return -1;
		}
		printf("[UDP %s:%d]\n", inet_ntoa(recvAddr.sin_addr), ntohs(recvAddr.sin_port));  //메시지를 보낸 상대방의 IP와 메시지가 전송된 포트가 출력된다.
		printf("[출력] > %s\n", recvBuf);
	}

	//이 스레드에서는 sending하는 스레드 종료를 어떻게 알아채고 멤버쉽 탈퇴를 진행시키지?
	//멤버쉽가입 및 탈퇴를 그냥 메인에서 하는게 나을거같은데
	setsockopt(UDPs, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&multi, sizeof(multi));

}

//근데 자기 자신도 멀티캐스트 대역에 포함되어있어서 이 대역에 뿌린 메시지를 자기 자신도 받게 된다.
//sendto와 recvfrom 에 대한 스레드들이 번갈아가며 빠르게 실행이 되는데 그러면 recvfrom이 잠시 실행 안되고있을 때 메시지 오면 못받을 수도 있겠네