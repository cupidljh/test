#ifdef __HEXPRINT_H__
#define __HEXPRINT_H__

#include "env.h"
#include "debug.h"

#endif

int hexprint(char* filename)
{

	log_verbose();

	size_t buf16Len;   // ���پ� ����� ����
	char buf16[16];    // ����

	if ((in = fopen(filename, "rb")) == NULL) {
		DEBUG_LEVEL(DEBUG_ERR);
		exit(1);
	}
	//16 ����Ʈ�� ������ �б�
	while ((buf16Len = fread(buf16, sizeof(char), sizeof(buf16), in)) != '\0')
	{
		printf("%zu:     ", offset); // ���� ���

		for (i = 0; i < (int)buf16Len; i++)
		{
			if (i == 8) printf("| ");
			if ((unsigned)buf16[i] == 0x0A) DEBUG_LEVEL(DEBUG_VERBOSE);

			printf("%02X ", (unsigned)buf16[i]);//�ٻ� �� ���
		}

		// �� ���� 16����Ʈ�� ���� ������ ���, ���� �κп� - ����
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
			if (buf16[i] >= 0x20 && buf16[i] <= 0x7E) // Ư������ �ƴϸ� ���
				printf("%c", buf16[i]);
			else printf("."); //Ư������, �׷��ȹ��� ���� ��ħǥ�� ���
		}

		offset += 16; // ������ ����
		printf("\n");
	}

	if (offset == 0) DEBUG_LEVEL(DEBUG_VERBOSE); // 0����Ʈ�� ���
	fclose(in);

	return 0;


}
