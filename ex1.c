#include <stdio.h>


//�ҹ��ڸ� �Է¹޾� �빮�ڷ� ����ϴ� �Լ��� ����ÿ�
void change(){
	char c;
	printf("�ҹ��ڸ� �Է��Ͻʽÿ� : ");
	scanf("%c", &c);
	printf("�Է��Ͻ� �ҹ��� %c�� �빮�ڷ� �ٲٸ� %c�Դϴ�\n", c, c-32);
}

//��Ģ���� ���� �Լ��� ����ÿ�(�� ������� �Ǽ������� ���)
void calc(){
	int a, b;
	printf("ù��° ���ڸ� �Է��Ͻʽÿ� : ");
	scanf("%d", &a);
	printf("�ι�° ���ڸ� �Է��Ͻʽÿ� : ");
	scanf("%d", &b);

	printf("%d + %d = %d\n", a, b, a+b);
	printf("%d - %d = %d\n", a, b, a-b);
	printf("%d * %d = %d\n", a, b, a*b);
	printf("%d / %d = %f\n", a, b, (double)a/b);	//������ %f�� ����Ϸ� �Ѵٰų� �Ǽ��� %d�� ����Ϸ��� �ϸ� �̻��ϰ� ��µȴ�. - ���̽��� �˾Ƽ� ���ִµ�
}


//���� �ڵ�

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
	printf("ù��° �� �Է� : ");
	scanf("%d", &su1);
	printf("�ι�° �� �Է� : ");
	scanf("%d", &su2);

	printf("%d + %d = %d \n", su1, su2, add_func(su1, su2));
	printf("%d - %d = %d \n", su1, su2, sub_func(su1, su2));
	printf("%d * %d = %d \n", su1, su2, mul_func(su1, su2));
	printf("%d / %d = %f \n", su1, su2, div_func(su1, su2));
}