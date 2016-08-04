#include <stdio.h>
#include <stdlib.h>

int main(void) {

	  FILE *in;
	  FILE *fp;
	    int ch;
		char c;


		  // test.bin 이라는 이진파일을 읽기 전용으로 열기
		  if ( (in = fopen("test.bin", "rb")) == NULL ) {
			      fputs("파일 열기 에러!", stderr);
				      exit(1);
				    }

	      while ( (ch = fgetc(in)) != EOF ) {
				    printf("%02X ", ch);
					  }

			fclose(in);

			printf("\n");
			

			if ( (fp = fopen("test.bin", "r")) == NULL ) {
	               fputs("파일 열기 에러!", stderr);
	                    exit(1);
	                      }

			while ( (c = fgetc(in)) != EOF) {
					printf( "%c" , c);
			}

			fclose(fp);

			return 0;
}
