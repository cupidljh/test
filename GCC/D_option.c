#include <stdio.h>
int main(void)
{
#ifdef TEST
	printf("Hello\n");
#else
	printf("NONONO\n");
#endif

	return 0;
}
