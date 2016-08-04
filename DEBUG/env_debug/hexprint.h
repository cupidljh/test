#ifdef __HEXPRINT_H__
#define __HEXPRINT_H__

#include "env.h"
#include "debug.h"

#endif

int hexprint(char* filename)
{

	log_verbose();

	size_t buf16Len;   // 한줄씩 저장될 버퍼
	char buf16[16];    // 길이

	if ((in = fopen(filename, "rb")) == NULL) {
		DEBUG_LEVEL(DEBUG_ERR);
		exit(1);
	}
	//16 바이트씩 끝가지 읽기
	while ((buf16Len = fread(buf16, sizeof(char), sizeof(buf16), in)) != '\0')
	{
		printf("%zu:     ", offset); // 번지 출력

		for (i = 0; i < (int)buf16Len; i++)
		{
			if (i == 8) printf("| ");
			if ((unsigned)buf16[i] == 0x0A) DEBUG_LEVEL(DEBUG_VERBOSE);

			printf("%02X ", (unsigned)buf16[i]);//핵사 값 출력
		}

		// 한 줄이 16바이트가 되지 않을때 헥사, 문자 부분에 - 삽입
		if ((int)buf16Len < 8)
		{
			for (int i = 0; i < (8 - (int)buf16Len); i++)
				printf("   ");

			printf("| ");

			for (int i = 0; i < 8; i++)
				printf("   ");
		}
		else if ((int)buf16Len < 16) {
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
