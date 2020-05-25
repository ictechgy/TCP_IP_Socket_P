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
	strcpy(ptr->name,"홍길동");
	strcpy(ptr->addr,"경기도");
	ptr->age=20;
	return ptr;
}

void main(){
	ST* p;
	p=func();
	FILE* fp = fopen("c:\\test.txt", "wt");
	fprintf(fp, "이름 : %s\n지역 : %s\n나이 : %d\n", p->name, p->addr, p->age);

	fclose(fp);
	free(p);

}
