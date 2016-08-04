#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef DEBUG
#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>

#define printf MyOutputDebugString   //printf�� Debug �ÿ� �ٲ��ش�.

void MyOutputDebugString(char *format, ...) // print�� �Ķ���� �޾ƿ���
{
	char outString[256] = { 0, };

	va_list args;
	va_start(args, format);

	vsprintf(outString, format, args);  //�Ķ���͵��� ���ۿ� �ֱ�

	va_end(args);

	OutputDebugString(outString);  // Debug â�� ���
}
#endif

#endif
