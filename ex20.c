#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

void client(){
	WSADATA wsa;  //WSAData 구조체
	WSAStartup(MAKEWORD(2,2),&wsa);
	//MAKEWORD는 define된 값으로서 F12를 눌러서 확인 가능하다.
	//함수가 어떤 주소값을 원한다는 것은 보통 그 변수공간에 어떤 값을 직접적으로 채워주겠다는 의미이다. 이것은 scanf("%d", &num); 에서도 알 수 있다.
	//WSAStartup을 통해 wsa 구조체 변수 안에 여러 값이 채워진다.

	SOCKET CiTs;  //unsigned int형 자료형이다. 유닉스에서 시작되었으며 유닉스와 리눅스에서는 int로 쓴다.
	CiTs = socket(AF_INET, SOCK_DGRAM, 0);
	//소켓생성이 되면 핸들링값이 반환된다. 소켓도 여러가지가 있는데 특정 소켓의 번호를 소켓변수에 대입시키겠다는 의미가 된다.
	//핸들링이란, 어떤 것을 조작한다는 의미이다. 동적할당에서 Heap을 가리키는 포인터변수로 우리는 메모리공간 핸들링을 했으며 FILE* fp로도 파일에 대해 핸들링 했었다.
	//마찬가지로 이 SOCKET 변수를 통해 특정 소켓을 우리는 조작하고 이용할 수 있다.

	SOCKADDR_IN svrAddr; //서버에 접속하기 위해 서버의 정보를 담을 SOCKADDR 구조체
	memset(&svrAddr, 0, sizeof(svrAddr));  //메모리세팅. 시작주소부터 3번째 인자 바이트수만큼 2번째 인자값으로 초기화
	
	svrAddr.sin_addr.s_addr=inet_addr("192.168.52.2"); //inet_addr => 문자열 ip주소를 정수(32비트)로 바꾼 뒤 네트워크 숫자 형식으로 변환
	svrAddr.sin_port = htons(12345); //인텔기반 컴퓨터에서는 숫자를 little endian방식으로 처리한다. 네트워크는 big endian방식이다.
	//리눅스시간에 DNS서버에서 질문이 들어온 IP에 대해 거꾸로 인식하던게 이런 이유때문인가?  ~.~.~.~.ARPA 뭐 이런식이었잖아
	//sin_port는 2바이트공간이므로 htoni가 아닌 htons를 쓰자
	svrAddr.sin_family = AF_INET;

	FILE* fp = fopen("c:\\test.txt", "rb");  //+로 개방하는 것은 입출력버퍼가 동시에 생기는 것인데 오류가 생기는 경우가 존재한다?
	//r모드는 rt와 같다고 보면 된다. text모드로서 값을 1바이트씩 읽어오겠다는 의미가 된다.
	//r모드와 b모드는 큰 차이는 없지만 개행인자를 처리하는 방식에 있어서 차이가 존재한다. 또한 대용량파일을 옮길 때 t모드를 쓰는 경우 부정확하다.

	fseek(fp, 0, SEEK_END);  //offset은 음수 또는 양수가 들어갈 수 있으며 음수가 들어가면 기준에서부터 왼쪽으로 커서를 이동시킨다. -> 맨 끝에 도달했는데 양수값 offset쓰면 이동 안되겠지?
	int fsize = ftell(fp);  //파일의 처음부터 커서가 존재하는 위치까지의 바이트수를 계산하여 반환한다.
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