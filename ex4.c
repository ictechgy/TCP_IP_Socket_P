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
	strcpy(S.i.name.name, "홍길동");
	strcpy(S.i.addr.addr, "경기도");

	printf("%s %d살 %s 국어점수:%d점 영어점수:%d점 수학점수:%d점", S.i.name.name, S.i.age, S.i.addr.addr, S.s.kor, S.s.eng, S.s.math);
}