#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "crc_table.h"
#include "hdlc.h"

#define FLAG 0x7E

void hdlc_enc_init(hdlc_enc *hdlc_encode) //hdlc 구조체를 초기화 해준다.
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


void hdlc_encode(char *buf, size_t buflen,  hdlc_enc *hdlc_encode) // 파일에서 16byte씩 데이터를 가져온다.
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
        if ((hdlc_encode->info[i] == FLAG) |( hdlc_encode->info[i] == 0x7d)) { // data 중간 7E가 있으면 안됨으로 처리
            hdlc_encode->info[i] ^= ESCAPE_BYTE; // 7E와 0x20을 XOR해줌 그 후 XOR 값 앞에 7D 넣어주면 끝
            
            memmove(hdlc_encode->info + i + 1, hdlc_encode->info + i, (int)buflen - i + 1); //배열 중간에 7d 삽입 할 공간 만듦
            hdlc_encode->info[i] = 0x7d; // 7D 삽입
            (int)buflen++;
        }
    }
	
    hdlc_encode->fcs = compute_fcs(hdlc_encode->info, (int)buflen); // fcs 계산
	
    hdlc_encode->crcH = hdlc_encode->fcs >> 8; //계산된 CRC값을 CRCH와 CRCL로 나누어준다.
	
    hdlc_encode->crcL = hdlc_encode->fcs;
	
    hdlc_encode->size = (int)buflen;
	
    hdlc_encode->finish_flag = FLAG;

    printf("After Encoding Data : %02X ", hdlc_encode->start_flag);   //Encoding 한 HDLC 출력하기.
	
    for (i = 0; i < (int)buflen; i++)
    {   
        printf("%02X ", hdlc_encode->info[i]);
    }

    printf("%02X %02X %02X\n\n",hdlc_encode->crcH,hdlc_encode->crcL, hdlc_encode->finish_flag);
}
