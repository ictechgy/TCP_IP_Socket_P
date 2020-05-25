#include <stdio.h>
#include <malloc.h>

void main(){
	FILE* src = fopen("c:\\test\\src.txt", "rb");
	FILE* dst = fopen("c:\\test\\dst.txt", "wb");
	char* pStr;

	if(src == NULL||dst == NULL){
		printf("파일 NO OPEN!!\n");
		return;
	}
	fseek(src, 0, SEEK_END);
	int size = ftell(src);

	//char str[size];  size에는 상수값이 있어야 한다고 뜸.
	pStr = (char*)malloc(size);

	fseek(src, 0, SEEK_SET);
	fread(pStr, 1, size, src);
	fwrite(pStr, 1, size, dst);

	free(pStr);
	fclose(src);
	fclose(dst);
}
