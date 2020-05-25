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
	//이미 b라는 구조체는 선언된 상태이고 그 안의 문자열배열공간도 선언이 된 상태라 한번에 값을 할당하는 것은 strcpy()함수를 써야한다.
	//해당 함수는 <string.h> 헤더파일에 선언되어있다.

}