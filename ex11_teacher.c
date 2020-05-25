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
	printf("이름 : ");
	gets(p->name);
	printf("주소 : ");
	gets(p->addr);
	printf("나이 : ");
	scanf("%d", &(p->age));
	return p;
	//gets()함수는 키보드로부터 값을 입력받아서 문자열배열에 저장하는 함수이다. 구글 - gets()함수 검색. http://egloos.zum.com/lechocolat/v/441439 참고
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