#include <stdio.h>

void main(){
	FILE* fp = fopen("C:\\Users\\USER-PC\\Desktop\\TCP_IP 소켓 프로그래밍\\Test.txt","w");
	fprintf(fp, "%s", "이름 : 홍길동\n나이 : 16\n주소 : 산골짜기\n");
	fclose(fp);
}