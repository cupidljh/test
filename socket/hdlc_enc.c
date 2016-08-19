#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "crc_table.h"
#include "hdlc.h"

#define FLAG 0x7E

void hdlc_enc_init(hdlc_enc *hdlc_encode) //hdlc ����ü�� �ʱ�ȭ ���ش�.
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


void hdlc_encode(char *buf, size_t buflen,  hdlc_enc *hdlc_encode) // ���Ͽ��� 16byte�� �����͸� �����´�.
{

    int i;

    for(i=0;i<(int)buflen;i++)
    {
       hdlc_encode->info[i] = buf[i];
    }
	
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
    {   
        printf("%02X ", hdlc_encode->info[i]);
    }

    printf("%02X %02X %02X\n\n",hdlc_encode->crcH,hdlc_encode->crcL, hdlc_encode->finish_flag);
}
