#include <stdio.h>

void main(){
	FILE* fp = fopen("C:\\Users\\USER-PC\\Desktop\\TCP_IP ���� ���α׷���\\Test.txt","w");
	fprintf(fp, "%s", "�̸� : ȫ�浿\n���� : 16\n�ּ� : ���¥��\n");
	fclose(fp);
}