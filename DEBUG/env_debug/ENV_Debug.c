
#include "env.h"
#include "debug.h"
#include "hexprint.h"

int main(int argc, char *argv[])
{
	log_verbose();
	
	get_env();
	check(argv);
	hexprint(argv[1]);

	return 0;
}



