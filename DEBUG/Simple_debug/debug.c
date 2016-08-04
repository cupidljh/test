#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#ifdef NODEBUG

#else

#define log_err(level, ...) fprintf(stderr, "\n[DEBUG_ERROR] FILE %s \n", __FILE__, ##__VA_ARGS__)
#define log_warn(level, ...) fprintf(stderr, "\n[DEBUG_WARNINGS] BYTE_ADDRESS : %d", i+1, ##__VA_ARGS__)
#define log_info(level, ...) fprintf(stderr, "\n[DEBUG_INFO] OFFSET : %zx", offset, ##__VA_ARGS__)
#define log_verbose(level, ...) fprintf(stderr, "\n[DEBUG_VERBOSE] FUNCTHION : %s", __FUNCTION__, ##__VA_ARGS__)

int i;
size_t offset = 0;
FILE *in;
#endif


int hexprint(const char* filename);

enum{
	DEBUG_ERR,
	DEBUG_WARN,
	DEBUG_INFO,
	DEBUG_VERBOSE,
};

void DEBUG_LEVEL( int level)
{
	switch(level) {
		case DEBUG_ERR : printf("\nDEBUG LEVEL : %d\n", level); log_err(level); break;
		case DEBUG_WARN : printf("\nDEBUG LEVEL :%d\n", level); log_warn(level); log_err(level); fclose(in); exit(1); break;
		case DEBUG_INFO : printf("\nDEBUG LEVEL : %d\n", level); log_info(level);log_warn(level); log_err(level); fclose(in); exit(1); break;
		case DEBUG_VERBOSE : printf("\nDEBUG LEVEL : %d\n", level); log_verbose(level); log_info(level);log_warn(level); log_err(level); fclose(in); exit(1); break;
	}
}

void check(char *argv[])
{
	if(!(argv[1])){
		DEBUG_LEVEL(DEBUG_ERR);
		exit(1);
	}

}



int main(int argc, char *argv[])
{
	check(argv);

	hexprint(argv[1]);
	
	return 0;
}


int hexprint(const char* filename)
{
	
	size_t buf16Len;   // 한줄씩 저장될 버퍼
	char buf16[16];    // 길이

		if ((in = fopen(filename, "rb")) == NULL) {
			DEBUG_LEVEL(DEBUG_ERR);
				exit(1);
		} 
		//16 바이트씩 끝가지 읽기
		while ((buf16Len = fread(buf16, sizeof(char), sizeof(buf16), in)) != '\0')
		{
											
			printf("%08X:     ", (unsigned int)offset); // 번지 출력

			for (int i = 0; i < (int)buf16Len; i++)
			{
				if (i == 8) printf("| ");
				if ((unsigned)buf16[i] == 0x0A) DEBUG_LEVEL(DEBUG_VERBOSE);

			printf("%02X ", (unsigned)buf16[i]);//핵사 값 출력
			}
		// 한 줄이 16바이트가 되지 않을때 헥사, 문자 부분에 . 삽입
		if((int)buf16Len < 8)
		{ 
		for (int i = 0; i < (8 - (int)buf16Len); i++)
				printf("   ");
				
		printf("| ");
		
		for (int i = 0; i < 8; i++)
			printf("   ");
		} else if ((int)buf16Len < 16) {
				for (int i = 0; i < (16 - (int)buf16Len); i++)
					printf("   ");
		}
					
		for (int i = 0; i < (int)buf16Len; i++)
		{
			if (buf16[i] >= 0x20 && buf16[i] <= 0x7E) // 특수문자 아니면 출력
					printf("%c", buf16[i]);
			else printf("."); //특수문자, 그래픽문자 등은 마침표로 출력
		}
	
		offset += 16; // 번지값 증가
		printf("\n");
		}

	if (offset == 0) DEBUG_LEVEL(DEBUG_VERBOSE); // 0바이트일 경우
		
	fclose(in);

	return 0;
}
