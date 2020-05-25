#include <stdio.h>
#include <string.h>

struct B{
	union{
		struct {int a[5];}A;
		struct {char a[10], b[10];}B;
		struct {short a[5], b[5];}C;
		char addr[20];
	}UN;		//Union ����ü�� �ٷ� �����ϰ� �ٷ� UN�̶�� �̸����� ���ڴ�
#define _addr UN.addr  //�̰� ���� -> �������� ���� ������ �̸����� �����ؼ� ���ڴ�.
	//�̰��� �ֻ�ܿ� ����� ���� ������ � �������� �ٷ� �� �� �ְ� �ϱ����� ���⿡ �� ��
};
struct A{
	int port;
	struct B b;
};

void main(){
	struct A a;
	a.port=12345;
	strcpy(a.b.UN.addr, "192.168.0.26");  // a.b._addr �ε� ���� ����
	printf("%d %s\n", a.port, a.b.UN.addr);
}