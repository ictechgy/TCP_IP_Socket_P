#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <process.h>
#include <Windows.h>
#include <WinSock2.h>

SOCKET CLIs1, CLIs2;
SOCKADDR_IN SVRAddr;

DWORD WINAPI portscan1(LPVOID arg){
	FILE* fp1;
	char buf[20] = {0};
	int port = ((int*)arg)[0];

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa)!=0){
		printf("WSAStartup error\n");
		return -1;
	}

	for(;port<=((int*)arg)[1]; port++){
		CLIs1 = socket(AF_INET, SOCK_STREAM, 0);
		if(CLIs1==INVALID_SOCKET){
			printf("socket error\n"); 
			return -1;
		}

		SVRAddr.sin_port = htons(port);

		int error = connect(CLIs1, (SOCKADDR*)&SVRAddr, sizeof(SVRAddr));
		if(error==SOCKET_ERROR){
			sprintf(buf, "%d port close!!\n", port);
		}
		else{
			sprintf(buf, "%d port open!!\n", port);
		}

		fp1 = fopen("C:\\port1.txt", "a");
		fwrite(buf, sizeof(buf), 1, fp1);
		fclose(fp1);

	}
	return 0;
}

DWORD WINAPI portscan2(LPVOID arg){
	FILE* fp2;
	char buf[20] = {0};
	int port = ((int*)arg)[0];

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa)!=0){
		printf("WSAStartup error\n");
		return -1;
	}

	for(;port<=((int*)arg)[1];port++){
		CLIs2 - socket(AF_INET, SOCK_STREAM, 0);
		if(CLIs2 == INVALID_SOCKET){
			printf("socket error\n");
			return -1;
		}

		SVRAddr.sin_port = htons(port);

		int error = connect(CLIs2, (SOCKADDR*)&SVRAddr, sizeof(SVRAddr));
		if(error==SOCKET_ERROR){
			sprintf(buf, "%d port close", port);
		}
		else{
			sprintf(buf, "%d port open", port);
		}

		fp2 = fopen("C:\\port2.txt", "a");
		fwrite(buf, sizeof(buf), 1, fp2);
		fclose(fp2);
	}
	return 0;
}



void client(int argc, char** argv){   //프로그램을 실행하면서 검색을 시작할 포트와 끝낼 끝번호 포트 두개를 입력 -> 각각의 숫자가 argv[1]과 argv[2]에 들어감
	memset(&SVRAddr, 0, sizeof(SVRAddr));
	SVRAddr.sin_family = AF_INET;
	SVRAddr.sin_addr.s_addr = inet_addr("192.168.148.130");

	int portsu = atoi(argv[2])-atoi(argv[1])+1;   //검색을 해야할 전체 포트수 구하기
	int port1[2], port2[2];
	int len = portsu/2;

	port1[0] = atoi(argv[1]);
	port1[1] = atoi(argv[1])+len-1;
	port2[0] = port1[1]+1;
	port2[1] = atoi(argv[2]);

	HANDLE handles[2];
	handles[0] = CreateThread(NULL, 0, portscan1, (LPVOID)port1, 0, NULL);
	handles[1] = CreateThread(NULL, 0, portscan2, (LPVOID)port2, 0, NULL);

	printf("스캔중.....\n");

	WaitForMultipleObjects(2, handles, TRUE, INFINITE);
	
	WSACleanup();

}

//UDP는 1대 다 통신이 가능한건 알겠다. 그냥 메시지를 뿌리기만 하면 되니까.
//근데 TCP는 1대1통신으로서 서로 연결을 확인한 뒤에 통신을 하는데, 그러면 서버도 클라이언트도 그 때 동안은 묶여있는건가.
//둘 다 다른 소켓통신은 불가능해짐? 아니면 연결되어있는 소켓으로는 다른 통신이 불가능하다는 말인가
//인터넷 서버는 TCP통신이기는 한데 HTTP 프로토콜로서 정보 주면 바로 소켓연결 끊는 방식인가? 다른 클라 소켓 연결 가능하게? 서버는 소켓 하나?
//아니면 TCP는 소켓 하나당 클라소켓 1:1 매칭이 가능하다는건가. UDP면 소켓 하나로 메시지 다 뿌리기가 가능한데..





void server(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SVRs = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN SVRAddr;
	SVRAddr.sin_family = AF_INET;
	SVRAddr.sin_port = htons(12345);
	SVRAddr.sin_addr.s_addr = inet_addr("192.168.148.130");

	bind(SVRs, (SOCKADDR*)&SVRAddr, sizeof(SVRAddr));

	listen(SVRs, SOMAXCONN);

	
	SOCKET CLIs;
	SOCKADDR_IN CLIAddr;
	memset(&CLIAddr, 0, sizeof(CLIAddr));
	int CLISize = sizeof(CLIAddr);

	CLIs = accept(SVRs, (SOCKADDR*)&CLIAddr, &CLISize);


	closesocket(SVRs);
	closesocket(CLIs);
}