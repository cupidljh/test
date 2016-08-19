#ifndef _HDLC_H
#define _HDLC_H

#define ESCAPE_BYTE 0x20   // 7E���� ������ �� �������� HEX��


typedef struct _Hdlc_encode {  // ����ü
	unsigned int start_flag;
	unsigned char info[256];
	unsigned short fcs;
	unsigned int finish_flag;
	int size;
	unsigned char crcH, crcL;
}hdlc_enc;



typedef struct _Hdlc_decode {
	unsigned int start_flag;
	unsigned char info[256];
	unsigned short fcs;
	unsigned int finish_flag;
	int size;
	unsigned char crcH, crcL;
}hdlc_dec;

extern void hdlc_enc_init(hdlc_enc *hdlc_encode); //hdlc ����ü�� �ʱ�ȭ ���ش�.
extern void hdlc_dec_init(hdlc_dec *hdlc_decode);
extern void hdlc_encode(char *buf, size_t buflen,  hdlc_enc *hdlc_encode); // ���Ͽ��� 16byte�� �����͸� �����´�.
extern void hdlc_decode(hdlc_enc *hdlc_encode, hdlc_dec *hdlc_decode);// decode
extern unsigned short compute_fcs(unsigned char *data, int length); //  CRC�� ���

#endif
