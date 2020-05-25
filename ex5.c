#include <stdio.h>
#include <string.h>

struct B{
	union{
		struct {int a[5];}A;
		struct {char a[10], b[10];}B;
		struct {short a[5], b[5];}C;
		char addr[20];
	}UN;		//Union 공용체를 바로 정의하고 바로 UN이라는 이름으로 쓰겠다
#define _addr UN.addr  //이건 뭐지 -> 오른쪽의 값을 왼쪽의 이름으로 정의해서 쓰겠다.
	//이것을 최상단에 적어둘 수도 있지만 어떤 정의인지 바로 알 수 있게 하기위해 여기에 쓴 듯
};
struct A{
	int port;
	struct B b;
};

void main(){
	struct A a;
	a.port=12345;
	strcpy(a.b.UN.addr, "192.168.0.26");  // a.b._addr 로도 접근 가능
	printf("%d %s\n", a.port, a.b.UN.addr);
}