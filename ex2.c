#include <stdio.h>

struct A{
	int a;
	int b;
};
struct B{
	int b;
	struct A a;
};
struct C{
	struct B b;
	struct A a;
	int c;
};

void main(){
	struct C c;
	//�����͸� ����ü ������ �ְ� ��� �Ͻÿ�
	c.c = 10;
	c.a.a=40;
	c.a.b=30;
	c.b.b=20;
	c.b.a.a=40;
	c.b.a.b=30;

	printf("%d %d %d %d %d %d \n",c.c, c.a.a, c.a.b, c.b.b, c.b.a.a, c.b.a.b);
}