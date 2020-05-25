#include <stdio.h>
#include <stdlib.h>		//atoi()함수 존재
#include <string.h>		//strcmp()함수 존재

int main(int argc, char* argv[]){

	int result=0;

	if(strcmp(argv[1], "sum")==0){ //strcmp()를 했을 때 0이 나온다는 것은 일치한다는 것. 사전적으로 단어상 순서를 비교하는 거였나?
		result = atoi(argv[2]) + atoi(argv[3]);
	}
	if(!strcmp(argv[1], "sub")){
		result = atoi(argv[2]) - atoi(argv[3]);
	}
	if(!strcmp(argv[1], "mul")){
		result = atoi(argv[2]) * atoi(argv[3]);  //cmd에서 입력할 때 변환 안될 이상한 값들 넣으면 오류나겠지?
	}
	if(!strcmp(argv[1], "div")){
		result = atoi(argv[2]) / atoi(argv[3]);
	}
	
	printf("result : %d\n", result); //argv[1]에 들어갈 값을 이상하게 적으면 result=0이 뜰 것

	char a='1';
	argv[1]=&a;		//매개변수로서의 argv는 공간크기가 정해지지 않았는데, 만들어지지 않은 공간에 값 넣으려하면 오류가 나려나. 0번째 방만 만들어져 있어도 이 코드는 오류?
	printf("%d\n", atoi(&a));    //atoi(&('1'))나 atoi(&'1') 이런건 안되네. 문법적으로.. 문자열을 넣으면 그건 시작주소를 나타내는거라 가능한데..
	//오호라. argv도 atoi도 문자열만을 취급하기는 하는데 이런게 되는걸까? 주소값을 취급하는 것 뿐인가.
	//숫자문자열을 변환하고자 할 때 배열의 시작주소라는 배열명말고는 달리 표현할 방법이 없으니 atoi함수는 인자로 시작주소값을 입력하도록 설계된 듯
	//그러고보니 atoi()의 매개변수형태가 const char* 형태였지..argv 또한..
	//결국 내가 말하고자 하는건.. 단일문자도 변환가능하냐는 것 -> 가능하다. 주소값을 넣어줘야 하긴 함


	return 0;
}