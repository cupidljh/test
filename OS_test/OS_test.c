#include<stdio.h>

#ifdef __linux__

int main()
{
	printf("I'm Linux\n");

	return 0;
}

#elif __WIN32

int main()
{
	printf("I'm Window\n");

	return 0;
}


#endif
