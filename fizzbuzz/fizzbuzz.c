/*
	Code eval challenge: Fizz Buzz generator

	Author: Ravi Niure
	Linkedin/twitter: niurerav
	Department of Electrical and Computer Engineering
	University of Toronto
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERROR_WHILE_OPENING_FILE 1
#define MAX_BUFFER_LEN 256

/*
	Fizz Buzz generator
	@param: x_num divides a number
			if divisible by x_num, F is displayed
	@param: y_num divides a number
			if divisible by y_num, B is displayed
	@param: num is the upper limit of the numbers to be divided either by x_num or y_num

	note: if a number is divisible by both x_num and y_num, FB is displayed
*/
void fb_generator(int x_num, int y_num, int num);

/*
	Main function
*/
int main(int argc, char* argv[])
{

	FILE* pfile;
	pfile = fopen(argv[1], "r");

	char string_line [MAX_BUFFER_LEN];
	memset(string_line, 0, MAX_BUFFER_LEN);

	int x, y, n;

	if(pfile == NULL)
	{
		printf("error: %d\n", ERROR_WHILE_OPENING_FILE);
	}
	else
	{
		while(fgets(string_line, MAX_BUFFER_LEN, pfile) != NULL)
		{
			x = (int)atoi(strtok(string_line, " "));
			y = (int)atoi(strtok(NULL, " "));
			n = (int)atoi(strtok(NULL, " "));

			fb_generator(x, y, n);
			memset(string_line, 0, MAX_BUFFER_LEN);

		}

	}
	fclose(pfile);
}

void fb_generator(int x_num, int y_num, int num)
{
	int i;
	int xflag = 0, yflag = 0;
	for(i = 1; i <= num; i++)
	{
		if(i == 1)
		{
			if(i%x_num == 0 && i%y_num == 0)
				printf("FB");
			else if(i%x_num == 0)
				printf("F");
			else if(i%y_num == 0)
				printf("B");
			else
				printf("%d", i);

		}
		else if(i%x_num == 0 && i%y_num == 0)
			printf(" FB");
		else if(i%x_num == 0)
			printf(" F");
		else if(i%y_num == 0)
			printf(" B");
		else
			printf(" %d", i);
	}
	printf("\n");

}
