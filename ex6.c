#include <stdio.h>
#include <malloc.h>  //동적할당과 해제를 위한 함수가 정의되어있는 헤더파일

typedef struct{
	int data1;
	int data2;
}Data1;

void func1(void* ptr){  //포인터변수 자체의 주소를 준다면 이걸 뭘로 받아야하나? Data1* 도 안되고 int* 나 int 도 안되고.. 포인터변수 자체는 대체 무슨 자료형인거야?
	//헐.. void* 로 해야한다고??? 포인터변수 그 자체는 어떠한 자료형도 아니라는건가?? 
	//Data1을 결국 가리킬테니 Data1* ptr 을 해도 안됐고 포인터변수는 주소라는 정수를 가지고 있는거니 int형일까봐 int* ptr했는데도 안됐고
	//주소값은 정수일테니 int p 했는데도 안됐는데..
	
	// ptr->p->data1=100; 이건 또 안되네
	Data1* ptr2 = (Data1*)ptr;
	ptr2->data1=100;
	//이게 뭔소리지 대체
}
void func2(Data1* ptr){
	ptr->data2=200;    //왜 컴파일하고 실행해도 아무 결과가 안나오고 디버그하면 여기서 오류가 나오는걸까
}

void main(){
	Data1* p = (Data1*)malloc(sizeof(Data1));
	func1(&p);
	//func1 함수를 만들어서 func1안에서 data1에 100을 넣으세요.
	func2(p);
	//func2 함수를 만들어서 func2안에서 data2에 200을 넣으세요.

	//data1과 data2를 출력하세요.
	//동적해제 코드를 추가하세요.

	printf("%d %d", p->data1, p->data2);
	printf("%d %d", (*p).data1, (*p).data2);
	free(p);
}


//강의 코드
void _func1(Data1** p1){  //이러한 것을 이중포인터(다중포인터)라고 한다. 이런게 왜 필요한지는 잘 모르겠다.
	//아무튼 설명하자면, main에서 넘어오는 것은 포인터변수 p의 주소이다. 포인터변수 p의 자료형은 그 어떠한 것도 아닌, Data1* 자료형이다. 즉 Data1 포인터자료형이다.
	//int형 변수를 포인트 하기 위해서 int* 로 포인터변수를 만들듯이 Data1* 자료형 포인터변수를 가리키기 위해 Data** 로 *을 하나 더 써준거라 보면 된다.
	//마치 int형 변수를 가리키기 위해 int*을 한 뒤에, int* 이라는 자료형변수를 가리키기 위해 int** 로 포인터변수를 하나 더 만들 듯

	(*p1)->data1 = 100;
	(*(*p1)).data1=100;  //내가 다른방식으로 표현해본 코드. 애로우연산자는 *. 을 쉽게 하기위해 생긴 연산자
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