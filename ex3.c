#include <stdio.h>
#include <string.h>

struct A{
	int a;
	char a_str[20];
};
struct B{
	int b;
	char b_str[20];
	struct A a;
};

void main(){
	struct B b;
	b.b=20;
	strcpy(b.b_str, "world");
	b.a.a=10;
	strcpy(b.a.a_str, "hello");

	printf("%s %s %d %d\n", b.a.a_str, b.b_str, b.a.a, b.b);
	//�̹� b��� ����ü�� ����� �����̰� �� ���� ���ڿ��迭������ ������ �� ���¶� �ѹ��� ���� �Ҵ��ϴ� ���� strcpy()�Լ��� ����Ѵ�.
	//�ش� �Լ��� <string.h> ������Ͽ� ����Ǿ��ִ�.

}