#include <stdio.h>
#include <malloc.h>  //�����Ҵ�� ������ ���� �Լ��� ���ǵǾ��ִ� �������

typedef struct{
	int data1;
	int data2;
}Data1;

void func1(void* ptr){  //�����ͺ��� ��ü�� �ּҸ� �شٸ� �̰� ���� �޾ƾ��ϳ�? Data1* �� �ȵǰ� int* �� int �� �ȵǰ�.. �����ͺ��� ��ü�� ��ü ���� �ڷ����ΰž�?
	//��.. void* �� �ؾ��Ѵٰ�??? �����ͺ��� �� ��ü�� ��� �ڷ����� �ƴ϶�°ǰ�?? 
	//Data1�� �ᱹ ����ų�״� Data1* ptr �� �ص� �ȵư� �����ͺ����� �ּҶ�� ������ ������ �ִ°Ŵ� int���ϱ�� int* ptr�ߴµ��� �ȵư�
	//�ּҰ��� �������״� int p �ߴµ��� �ȵƴµ�..
	
	// ptr->p->data1=100; �̰� �� �ȵǳ�
	Data1* ptr2 = (Data1*)ptr;
	ptr2->data1=100;
	//�̰� ���Ҹ��� ��ü
}
void func2(Data1* ptr){
	ptr->data2=200;    //�� �������ϰ� �����ص� �ƹ� ����� �ȳ����� ������ϸ� ���⼭ ������ �����°ɱ�
}

void main(){
	Data1* p = (Data1*)malloc(sizeof(Data1));
	func1(&p);
	//func1 �Լ��� ���� func1�ȿ��� data1�� 100�� ��������.
	func2(p);
	//func2 �Լ��� ���� func2�ȿ��� data2�� 200�� ��������.

	//data1�� data2�� ����ϼ���.
	//�������� �ڵ带 �߰��ϼ���.

	printf("%d %d", p->data1, p->data2);
	printf("%d %d", (*p).data1, (*p).data2);
	free(p);
}


//���� �ڵ�
void _func1(Data1** p1){  //�̷��� ���� ����������(����������)��� �Ѵ�. �̷��� �� �ʿ������� �� �𸣰ڴ�.
	//�ƹ�ư �������ڸ�, main���� �Ѿ���� ���� �����ͺ��� p�� �ּ��̴�. �����ͺ��� p�� �ڷ����� �� ��� �͵� �ƴ�, Data1* �ڷ����̴�. �� Data1 �������ڷ����̴�.
	//int�� ������ ����Ʈ �ϱ� ���ؼ� int* �� �����ͺ����� ������� Data1* �ڷ��� �����ͺ����� ����Ű�� ���� Data** �� *�� �ϳ� �� ���ذŶ� ���� �ȴ�.
	//��ġ int�� ������ ����Ű�� ���� int*�� �� �ڿ�, int* �̶�� �ڷ��������� ����Ű�� ���� int** �� �����ͺ����� �ϳ� �� ���� ��

	(*p1)->data1 = 100;
	(*(*p1)).data1=100;  //���� �ٸ�������� ǥ���غ� �ڵ�. �ַο쿬���ڴ� *. �� ���� �ϱ����� ���� ������
}
void _func2(Data1* p2){
	(*p2).data2 = 200;
	p2->data2=200;
}
int _main(){
	Data1* p = (Data1*)malloc(sizeof(Data1));
	_func1(&p);
	_func2(p);
	printf("data1 : %d, data2 : %d\n", p->data1, p->data2);
	free(p);
	return 0;
}