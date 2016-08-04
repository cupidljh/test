#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

struct input_data
{
	char oper[2];
	char func[10];
	char lib[30];
};

int main(int argc, char **argv)
{
	char oper[2];
	char left[11];
	char right[11];
	char buf[50];
	char null[1];
	int data_num;

	struct input_data plug_num[10];

	void *handle;

	int (*result)(int, int);
	int i;
	char *error;

	FILE *fp;

	fp = fopen("plugin.cfg", "r");
	data_num = 0;
	while(fgets(buf, 50, fp) != NULL)
	{
		buf[strlen(buf) -1] = '\0';
		scanf(buf, "%[^,]%[,]%[^,]%[,]^[%,]", plug_num[data_num].oper,null,plug_num[data_num].fun,plug_num[data_num].lib);

		data_num++;
	}

	fclose(fp);

	printf("> ");
	memset(left, 0x00, 11);
	memset(right, 0x00, 11);
	fscanf(stdin, "%[0-9]%[^0-9]%[0-9]", left,oper,right);


