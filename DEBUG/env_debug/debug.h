#ifdef __DEBUG_H__
#define __DEBUG_H__

#include<stdio.h>
#include<stdarg.h>
#include<errno.h>
#include <string.h>
#include <stdlib.h>
#include "env.h"

#else 
	#include<stdio.h>
	#include<stdarg.h>
	#include<errno.h>
	#include<string.h>
	#include<stdlib.h>

#endif


#ifdef NODEBUG

#else

#define log_err(...) fprintf(stderr, "\n[DEBUG_ERROR] FILE : %s \n",  __FILE__, ##__VA_ARGS__)
#define log_warn(...) fprintf(stderr, "\n[DEBUG_WARNINGS] BYTE_ADDRESS : %d\n", i+1, ##__VA_ARGS__)
#define log_info(...) fprintf(stderr, "\n[DEBUG_INFO] OFFSET : %zx\n",  offset, ##__VA_ARGS__)
#define log_verbose(...) fprintf(stderr, "\n[DEBUG_VERB] FUNCTHION : %s\n",  __FUNCTION__,##__VA_ARGS__)


int i; // hex_byte
size_t offset = 0; // ¹øÁö
FILE *in;
#endif

void DEBUG_LEVEL(int level)
{
	

	switch (level) {

	case 1 :printf("\nDEBUG LEVEL : %d \n", level);  log_err(); break;
	case 2 :printf("\nDEBUG LEVEL : %d \n", level); log_warn(); log_err(); fclose(in);  exit(1); break;
	case 3 :printf("\nDEBUG LEVEL : %d \n", level); log_info(); log_warn(); log_err(); fclose(in); exit(1); break;
	case 4 : printf("\nDEBUG LEVEL : %d \n", level); log_verbose(); log_info(); log_warn(); log_err(); fclose(in); exit(1); break;
	//case 1: printf("case 1\n");
	//case 2: printf("case 2\n");
	//case 3: printf("case 3\n"); break;
	//case 4: printf("case 4\n");
	}

}

void check(char *argv[])
{
	
	log_verbose();

	if (!(argv[1])) {
		DEBUG_LEVEL(DEBUG_ERR);
		exit(1);
	}
	else {
		printf("file check!\n");
	}

}

