#include <stdio.h>
#include <string.h>

struct score{
	int kor;
	int eng;
	int math;
};
struct _name{
	char name[20];
};
struct _addr{
	char addr[50];
};
struct infor{
	struct _name name;
	struct _addr addr;
	int age;
};
struct Student{
	struct score s;
	struct infor i;
};

void main(){
	struct Student S;
	S.s.kor=100;
	S.s.eng=80;
	S.s.math=60;
	S.i.age=20;
	strcpy(S.i.name.name, "ȫ�浿");
	strcpy(S.i.addr.addr, "��⵵");

	printf("%s %d�� %s ��������:%d�� ��������:%d�� ��������:%d��", S.i.name.name, S.i.age, S.i.addr.addr, S.s.kor, S.s.eng, S.s.math);
}