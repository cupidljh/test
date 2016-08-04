#include <stdlib.h>
#include <stdio.h>


int DEBUG_ERR;
int DEBUG_WARN;
int DEBUG_INFO;
int DEBUG_VERBOSE;

void get_env() {
	
	char *a,*b,*c,*d;
	

	a = getenv("DEBUG_ERR");
	b = getenv("DEBUG_WARN");
	c = getenv("DEBUG_INFO");
	d = getenv("DEBUG_VERBOSE");

	DEBUG_ERR = atoi(a);
	DEBUG_WARN = atoi(b);
	DEBUG_INFO = atoi(c);
	DEBUG_VERBOSE = atoi(d);

	
}

