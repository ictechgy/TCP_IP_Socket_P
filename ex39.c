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



void client(int argc, char** argv){   //���α׷��� �����ϸ鼭 �˻��� ������ ��Ʈ�� ���� ����ȣ ��Ʈ �ΰ��� �Է� -> ������ ���ڰ� argv[1]�� argv[2]�� ��
	memset(&SVRAddr, 0, sizeof(SVRAddr));
	SVRAddr.sin_family = AF_INET;
	SVRAddr.sin_addr.s_addr = inet_addr("192.168.148.130");

	int portsu = atoi(argv[2])-atoi(argv[1])+1;   //�˻��� �ؾ��� ��ü ��Ʈ�� ���ϱ�
	int port1[2], port2[2];
	int len = portsu/2;

	port1[0] = atoi(argv[1]);
	port1[1] = atoi(argv[1])+len-1;
	port2[0] = port1[1]+1;
	port2[1] = atoi(argv[2]);

	HANDLE handles[2];
	handles[0] = CreateThread(NULL, 0, portscan1, (LPVOID)port1, 0, NULL);
	handles[1] = CreateThread(NULL, 0, portscan2, (LPVOID)port2, 0, NULL);

	printf("��ĵ��.....\n");

	WaitForMultipleObjects(2, handles, TRUE, INFINITE);
	
	WSACleanup();

}

//UDP�� 1�� �� ����� �����Ѱ� �˰ڴ�. �׳� �޽����� �Ѹ��⸸ �ϸ� �Ǵϱ�.
//�ٵ� TCP�� 1��1������μ� ���� ������ Ȯ���� �ڿ� ����� �ϴµ�, �׷��� ������ Ŭ���̾�Ʈ�� �� �� ������ �����ִ°ǰ�.
//�� �� �ٸ� ��������� �Ұ�������? �ƴϸ� ����Ǿ��ִ� �������δ� �ٸ� ����� �Ұ����ϴٴ� ���ΰ�
//���ͳ� ������ TCP����̱�� �ѵ� HTTP �������ݷμ� ���� �ָ� �ٷ� ���Ͽ��� ���� ����ΰ�? �ٸ� Ŭ�� ���� ���� �����ϰ�? ������ ���� �ϳ�?
//�ƴϸ� TCP�� ���� �ϳ��� Ŭ����� 1:1 ��Ī�� �����ϴٴ°ǰ�. UDP�� ���� �ϳ��� �޽��� �� �Ѹ��Ⱑ �����ѵ�..





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