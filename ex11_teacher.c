#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct st{
	char name[20];
	char addr[50];
	int age;
}ST;

ST* func(){
	ST* p = (ST*)malloc(sizeof(ST));
	printf("�̸� : ");
	gets(p->name);
	printf("�ּ� : ");
	gets(p->addr);
	printf("���� : ");
	scanf("%d", &(p->age));
	return p;
	//gets()�Լ��� Ű����κ��� ���� �Է¹޾Ƽ� ���ڿ��迭�� �����ϴ� �Լ��̴�. ���� - gets()�Լ� �˻�. http://egloos.zum.com/lechocolat/v/441439 ����
}

void main(int argc, char* argv[]){
	ST* p;
	p = func();
	FILE* fp = fopen("c:\\test.txt", "w");

	fwrite(p->name, 1, strlen(p->name), fp);
	fprintf(fp, "\n");
	fwrite(p->addr, 1, strlen(p->addr), fp);
	fprintf(fp, "\n%d\n", p->age);

	fclose(fp);
	free(p);

}