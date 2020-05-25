#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

void main(int argc, char* argv[]){
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET SRVs;
	SRVs = socket(AF_INET, SOCK_STREAM,0);
	if(SRVs==INVALID_SOCKET){
		printf("���� ���� ����");
		return;
	}

	SOCKADDR_IN SRVi;
	memset(&SRVi, 0, sizeof(SRVi));
	SRVi.sin_family = AF_INET;
	SRVi.sin_port = htons(12345);
	SRVi.sin_addr.S_un.S_addr = inet_addr("192.168.139.134");

	int error=0;
	error = bind(SRVs, (sockaddr*)(&SRVi), sizeof(SRVi)); //���ϰ� �����ּұ���ü�� �����Ͽ� �ü���κ��� ����ޱ�
	if(error == SOCKET_ERROR){
		printf("���ϰ� �����ּ���������ü�� �����ϴ� �������� ������ �߻��Ͽ����ϴ�.-bind()����");
		return;
	}

	error = listen(SRVs, SOMAXCONN);
	if(error == SOCKET_ERROR){
		printf("������ ���¸� listen���·� �����ϴ� �������� ������ �߻��Ͽ����ϴ�.-listen()����");
		return;
	}

	SOCKET CiTs;
	SOCKADDR_IN CiTa;
	memset(&CiTa, 0, sizeof(CiTa));
	int CiTaLen = sizeof(CiTa);

	CiTs = accept(SRVs, (sockaddr*)(&CiTa), &CiTaLen);
	if(CiTs == INVALID_SOCKET){
		printf("Ŭ���̾�Ʈ�� ���ӿ�û�� accept()�ϴ� �������� ������ �߻��Ͽ����ϴ�.");
		return;
	}

	//������ Ŭ���̾�Ʈ�� ���� ����ϱ�
	printf("������ Ŭ���̾�Ʈ�� IP�ּҴ� %s �̰� ��Ʈ��ȣ�� %d�Դϴ�\n", inet_ntoa(CiTa.sin_addr), ntohs(CiTa.sin_port));


	char msg[100];
	int len;
	len = recv(CiTs, msg, sizeof(msg), 0);   //len���� �޽��� ���� �� ũ�� �� ���� ��

	//������ Ŭ���̾�Ʈ�� �޽����� ��۽��ϱ�(ECHO ���� ����)
	len = send(CiTs, msg, strlen(msg), 0);  //len���� ������ ������ �� ũ�Ⱑ �� ���̸�, ���� ������ msg�� ����ִ� ����ŭ�� ������ �Ǵ� strlen()�� ���.

	closesocket(SRVs);
	WSACleanup();

}