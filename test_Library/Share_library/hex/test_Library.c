#include<stdio.h>
#include<stdlib.h>

extern void hexprint(char* filename);

int main(int argc, char* argv[])
{
	if(argc == 1){
		fputs("error\n",stderr);
		exit(1);
	}

	hexprint(argv[1]);

	return 0;
}

		
