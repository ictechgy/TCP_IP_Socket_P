#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct st{
	char name[20];
	char addr[50];
	int age;
}ST;

ST* func(){
	ST* ptr = (ST*)malloc(sizeof(ST));
	strcpy(ptr->name,"ȫ�浿");
	strcpy(ptr->addr,"��⵵");
	ptr->age=20;
	return ptr;
}

void main(){
	ST* p;
	p=func();
	FILE* fp = fopen("c:\\test.txt", "wt");
	fprintf(fp, "�̸� : %s\n���� : %s\n���� : %d\n", p->name, p->addr, p->age);

	fclose(fp);
	free(p);

}