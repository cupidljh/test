#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "crc_table.h"
#include "hdlc.h"
#include "debug.h"


#define FLAG 0x7E

void hdlc_init(hdlc_enc *hdlc_encode, hdlc_dec *hdlc_decode) //hdlc ����ü�� �ʱ�ȭ ���ش�.
{
	//hdlc_encode init
	int len = 10;
	int i;
	for (i = 0; i < len; i++)
	{
		hdlc_encode->start_flag = 0x00;
		hdlc_encode->finish_flag = 0x00;

		for (i = 0; i < sizeof(hdlc_encode->info); i++)
			hdlc_encode->info[i] = 0;

		hdlc_encode->fcs = 0x0000;
	}
	//hdlc_decode init

	hdlc_decode->start_flag = 0x00;

	for (i = 0; i < strlen(hdlc_decode->info); i++)
		hdlc_decode->info[i] = 0;

	hdlc_decode->fcs = 0x0000;

	hdlc_decode->finish_flag = 0x00;
}

u16 compute_fcs(unsigned char *data, int length)
{
	u16 fcs;

	fcs = 0xffff;
	for (int i = 0; i< length; i++)
	{
		fcs = (fcs >> 8) ^ fcstab[(fcs ^ ((u16)*data)) & 0xff];
		data++;
	}
	return (fcs);
}


void hdlc_encode(char *filename, hdlc_enc *hdlc_encode) // ���Ͽ��� 16byte�� �����͸� �����´�.
{
	int i;
	size_t buflen;
	char buf[16];
	FILE *in;

	if ((in = fopen(filename, "rb")) == NULL) {
		fputs("file error\n", stderr);
		exit(1);
	}

	while ((buflen = fread(hdlc_encode->info, sizeof(char), sizeof(buf), in)) != '\0')//������ ���� �� ���� �б�
	{
		hdlc_encode->start_flag = FLAG;

		printf("\nBefore Encoding Data : ");

		for (i = 0; i < (int)buflen; i++)
			printf("%02X ", hdlc_encode->info[i]);

		printf("\n\n");
		

		for (i = 0; i < (int)buflen; i++)
		{
			if ((hdlc_encode->info[i] == FLAG) |( hdlc_encode->info[i] == 0x7d)) { // data �߰� 7E�� ������ �ȵ����� ó��
				hdlc_encode->info[i] ^= ESCAPE_BYTE; // 7E�� 0x20�� XOR���� �� �� XOR �� �տ� 7D �־��ָ� ��

				memmove(hdlc_encode->info + i + 1, hdlc_encode->info + i, (int)buflen - i + 1); //�迭 �߰��� 7d ���� �� ���� ����
				hdlc_encode->info[i] = 0x7d; // 7D ����
				(int)buflen++;
			}
		}

		hdlc_encode->fcs = compute_fcs(hdlc_encode->info, (int)buflen); // fcs ���

		hdlc_encode->crcH = hdlc_encode->fcs >> 8; //���� CRC���� CRCH�� CRCL�� �������ش�.
		hdlc_encode->crcL = hdlc_encode->fcs;


		hdlc_encode->size = (int)buflen;

		hdlc_encode->finish_flag = FLAG;

		printf("After Encoding Data : %02X ", hdlc_encode->start_flag);   //Encoding �� HDLC ����ϱ�.
		for (i = 0; i < (int)buflen; i++)
			printf("%02X ", hdlc_encode->info[i]);
		printf("%02X %02X %02X\n\n",hdlc_encode->crcH,hdlc_encode->crcL, hdlc_encode->finish_flag);

		hdlc_encode++; // ����ü �迭 ����
	}
}


void hdlc_decode(hdlc_enc *hdlc_encode, hdlc_dec *hdlc_decode)
{
	int len = 10;
	while (len>0)
	{
		if (hdlc_encode->start_flag == FLAG) { // ���� �÷��׿� 0x7E�� ���� ���� decoding�Ѵ�.
			int i;

			hdlc_decode->size = hdlc_encode->size; // input data size�� �����´�

			hdlc_decode->start_flag = hdlc_encode->start_flag;
			hdlc_decode->finish_flag = hdlc_encode->finish_flag;

			for (i = 0; i < hdlc_decode->size; i++)  // encode�� data�� decode �� ����
				hdlc_decode->info[i] = hdlc_encode->info[i];

			hdlc_decode->fcs = compute_fcs(hdlc_decode->info, hdlc_decode->size); // fcs ���

			for (i = 0; i < hdlc_decode->size; i++)
			{
				if (hdlc_decode->info[i] == 0x7D) // decode data �� 7D�� �ִٸ� �� �ڿ� ���ڰ��� 0x20 �� XOR ���༭ ���� ������ �ǵ��� ��
				{                                // 7D�� ���ְ� �迭�� �� ĭ�� �����
					hdlc_decode->info[i + 1] ^= ESCAPE_BYTE;
					memmove(hdlc_decode->info + i, hdlc_decode->info + i + 1, hdlc_decode->size - i);
					hdlc_decode->size--;
				}
			}

			printf("Decoding Data = ");

			for (i = 0; i < hdlc_decode->size; i++)
				printf("%02X ", hdlc_decode->info[i]);

			printf("\n\n");

			if (hdlc_decode->fcs != hdlc_encode->fcs)
				printf("receive error\n\n");
			else
				printf("receive success\n\n");

			
		}
		hdlc_encode++;
		len--;
	}
}
