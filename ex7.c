#include <stdio.h>
#include <malloc.h>

typedef struct{
	char name[20];
	int score;
}Element;

typedef struct{
	int data1;
	int data2;
	Element p;
}Data1;
//위와같이 구조체를 정의하면 본명 없이 별명으로만 쓰겠다는건가?

void main(){
	Data1* p = (Data1*)malloc(sizeof(Data1));
	printf("이름을 입력하세요 : ");
	//scanf를 써서 name에 이름을 입력받으세요.
	scanf("%s", p->p.name);
	scanf("%s", (*p).p.name);

	printf("점수를 입력하세요 : ");
	//scanf를 써서 score에 이름을 입력받으세요.
	scanf("%d", &(p->p.score));
	scanf("%d", &((*p).p.score));

	//입력받은 값을 출력하세요.
	//동적할당 해제

	printf("이름 : %s, 점수 : %d\n", p->p.name, p->p.score);
	free(p);
}