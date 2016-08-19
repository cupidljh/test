#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "crc_table.h"
#include "hdlc.h"

#define FLAG 0x7E

void hdlc_dec_init(hdlc_dec *hdlc_decode) //hdlc 구조체를 초기화 해준다.
{
    int i;
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

void hdlc_decode(hdlc_enc *hdlc_encode, hdlc_dec *hdlc_decode)
{
    int i;
	
    if (hdlc_encode->start_flag == FLAG)
    { // 시작 플래그에 0x7E가 들어갔을 때만 decoding한다.
		hdlc_decode->size = hdlc_encode->size; // input data size를 가져온다

		hdlc_decode->start_flag = hdlc_encode->start_flag;
		hdlc_decode->finish_flag = hdlc_encode->finish_flag;

		for (i = 0; i < hdlc_decode->size; i++)  // encode에 data를 decode 에 저장
			hdlc_decode->info[i] = hdlc_encode->info[i];

		hdlc_decode->fcs = compute_fcs(hdlc_decode->info, hdlc_decode->size); // fcs 계산

		for (i = 0; i < hdlc_decode->size; i++)
		{
			if (hdlc_decode->info[i] == 0x7D) // decode data 에 7D가 있다면 그 뒤에 인자값을 0x20 과 XOR 해줘서 원래 값으로 되돌린 후
			{                                // 7D를 없애고 배열을 한 칸씩 땡긴다
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
	}else{
        printf("flag is not 7E\n");
    }
}
