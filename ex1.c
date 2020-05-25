#include <stdio.h>


//소문자를 입력받아 대문자로 출력하는 함수를 만드시오
void change(){
	char c;
	printf("소문자를 입력하십시오 : ");
	scanf("%c", &c);
	printf("입력하신 소문자 %c를 대문자로 바꾸면 %c입니다\n", c, c-32);
}

//사칙연산 계산기 함수를 만드시오(단 나누기는 실수값으로 출력)
void calc(){
	int a, b;
	printf("첫번째 숫자를 입력하십시오 : ");
	scanf("%d", &a);
	printf("두번째 숫자를 입력하십시오 : ");
	scanf("%d", &b);

	printf("%d + %d = %d\n", a, b, a+b);
	printf("%d - %d = %d\n", a, b, a-b);
	printf("%d * %d = %d\n", a, b, a*b);
	printf("%d / %d = %f\n", a, b, (double)a/b);	//정수를 %f로 출력하려 한다거나 실수를 %d로 출력하려고 하면 이상하게 출력된다. - 파이썬은 알아서 해주는데
}


//강의 코드

int add_func(int su1, int su2){
	return su1 + su2;
}

int sub_func(int su1, int su2){
	return su1-su2;
}

int mul_func(int su1, int su2){
	return su1*su2;
}

double div_func(int su1, int su2){
	return (double)su1/su2;
}

void main(){
	int su1, su2;
	printf("첫번째 수 입력 : ");
	scanf("%d", &su1);
	printf("두번째 수 입력 : ");
	scanf("%d", &su2);

	printf("%d + %d = %d \n", su1, su2, add_func(su1, su2));
	printf("%d - %d = %d \n", su1, su2, sub_func(su1, su2));
	printf("%d * %d = %d \n", su1, su2, mul_func(su1, su2));
	printf("%d / %d = %f \n", su1, su2, div_func(su1, su2));
}