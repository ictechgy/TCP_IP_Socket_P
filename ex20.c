#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

void client(){
	WSADATA wsa;  //WSAData ����ü
	WSAStartup(MAKEWORD(2,2),&wsa);
	//MAKEWORD�� define�� �����μ� F12�� ������ Ȯ�� �����ϴ�.
	//�Լ��� � �ּҰ��� ���Ѵٴ� ���� ���� �� ���������� � ���� ���������� ä���ְڴٴ� �ǹ��̴�. �̰��� scanf("%d", &num); ������ �� �� �ִ�.
	//WSAStartup�� ���� wsa ����ü ���� �ȿ� ���� ���� ä������.

	SOCKET CiTs;  //unsigned int�� �ڷ����̴�. ���н����� ���۵Ǿ����� ���н��� ������������ int�� ����.
	CiTs = socket(AF_INET, SOCK_DGRAM, 0);
	//���ϻ����� �Ǹ� �ڵ鸵���� ��ȯ�ȴ�. ���ϵ� ���������� �ִµ� Ư�� ������ ��ȣ�� ���Ϻ����� ���Խ�Ű�ڴٴ� �ǹ̰� �ȴ�.
	//�ڵ鸵�̶�, � ���� �����Ѵٴ� �ǹ��̴�. �����Ҵ翡�� Heap�� ����Ű�� �����ͺ����� �츮�� �޸𸮰��� �ڵ鸵�� ������ FILE* fp�ε� ���Ͽ� ���� �ڵ鸵 �߾���.
	//���������� �� SOCKET ������ ���� Ư�� ������ �츮�� �����ϰ� �̿��� �� �ִ�.

	SOCKADDR_IN svrAddr; //������ �����ϱ� ���� ������ ������ ���� SOCKADDR ����ü
	memset(&svrAddr, 0, sizeof(svrAddr));  //�޸𸮼���. �����ּҺ��� 3��° ���� ����Ʈ����ŭ 2��° ���ڰ����� �ʱ�ȭ
	
	svrAddr.sin_addr.s_addr=inet_addr("192.168.52.2"); //inet_addr => ���ڿ� ip�ּҸ� ����(32��Ʈ)�� �ٲ� �� ��Ʈ��ũ ���� �������� ��ȯ
	svrAddr.sin_port = htons(12345); //���ڱ�� ��ǻ�Ϳ����� ���ڸ� little endian������� ó���Ѵ�. ��Ʈ��ũ�� big endian����̴�.
	//�������ð��� DNS�������� ������ ���� IP�� ���� �Ųٷ� �ν��ϴ��� �̷� ���������ΰ�?  ~.~.~.~.ARPA �� �̷����̾��ݾ�
	//sin_port�� 2����Ʈ�����̹Ƿ� htoni�� �ƴ� htons�� ����
	svrAddr.sin_family = AF_INET;

	FILE* fp = fopen("c:\\test.txt", "rb");  //+�� �����ϴ� ���� ����¹��۰� ���ÿ� ����� ���ε� ������ ����� ��찡 �����Ѵ�?
	//r���� rt�� ���ٰ� ���� �ȴ�. text���μ� ���� 1����Ʈ�� �о���ڴٴ� �ǹ̰� �ȴ�.
	//r���� b���� ū ���̴� ������ �������ڸ� ó���ϴ� ��Ŀ� �־ ���̰� �����Ѵ�. ���� ��뷮������ �ű� �� t��带 ���� ��� ����Ȯ�ϴ�.

	fseek(fp, 0, SEEK_END);  //offset�� ���� �Ǵ� ����� �� �� ������ ������ ���� ���ؿ������� �������� Ŀ���� �̵���Ų��. -> �� ���� �����ߴµ� ����� offset���� �̵� �ȵǰ���?
	int fsize = ftell(fp);  //������ ó������ Ŀ���� �����ϴ� ��ġ������ ����Ʈ���� ����Ͽ� ��ȯ�Ѵ�.
	sendto(CiTs, (char*)&fsize, sizeof(fsize), 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));

	char* fptr = (char*)malloc(fsize);
	fread(fptr, 1, fsize, fp);
	sendto(CiTs, fptr, fsize, 0, (SOCKADDR*)&svrAddr, sizeof(svrAddr));
	
	free(fptr);
	fclose(fp);
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

	int fsize;
	recvfrom(SVRs, (char*)&fsize, sizeof(fsize), 0, (SOCKADDR*)&CiTa, &CiTSize);
	char* fptr = (char*)malloc(fsize);
	recvfrom(SVRs, fptr, fsize, 0, (SOCKADDR*)&CiTa, &CiTSize);
	FILE* fp = fopen("c:\\test.txt", "wb");
	fwrite(fptr, 1, fsize, fp);

	fclose(fp);
	free(fptr);
	closesocket(SVRs);
	WSACleanup();

}