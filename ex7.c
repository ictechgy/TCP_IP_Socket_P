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
//���Ͱ��� ����ü�� �����ϸ� ���� ���� �������θ� ���ڴٴ°ǰ�?

void main(){
	Data1* p = (Data1*)malloc(sizeof(Data1));
	printf("�̸��� �Է��ϼ��� : ");
	//scanf�� �Ἥ name�� �̸��� �Է¹�������.
	scanf("%s", p->p.name);
	scanf("%s", (*p).p.name);

	printf("������ �Է��ϼ��� : ");
	//scanf�� �Ἥ score�� �̸��� �Է¹�������.
	scanf("%d", &(p->p.score));
	scanf("%d", &((*p).p.score));

	//�Է¹��� ���� ����ϼ���.
	//�����Ҵ� ����

	printf("�̸� : %s, ���� : %d\n", p->p.name, p->p.score);
	free(p);
}