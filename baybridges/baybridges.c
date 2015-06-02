/*
	Code eval challenge: Bay Bridges

	Author: Ravi Niure
	Linkedin/Github: niurerav
	Twitter: NiureRavi
	Department of Electrical and Computer Engineering
	University of Toronto
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERROR_WHILE_OPENING_FILE 1
#define MAX_BUFFER_LEN 256

//Function Definitions

/*
	Parsing Module
	@para: input_string consists of a single line entry extracted from the file
			input_string is in form: "1: ([37.788353, -122.387695], [37.829853, -122.294312])"
			from which X1, Y1, X2, and Y2 are to be extracted.
	@lat_long_array: double array which should be modified by the parsing module to 
			include latitude and longitude information of the two points in the format 
			[X1, Y1, X2, Y2]
	@return: integer that represents the ID of each entry. '1' from above example.
			will return -1 if parsing was unsuccessful.
*/
int parsing_module(char* input_string, double* lat_long_array);

/*
	Equation Generator
	@para: 

*/
void equation_generator()

/*
	Main Function
*/
int main(int argc, char* argv[])
{
	FILE* pfile;
	pfile = fopen(argv[1], "r");

	char string_line [MAX_BUFFER_LEN];
	memset(string_line, 0, MAX_BUFFER_LEN);

	int num_entries = 0;
	if(pfile == NULL)
	{
		printf("error: %d\n", ERROR_WHILE_OPENING_FILE);
	}
	else
	{
		while(fgets(string_line, MAX_BUFFER_LEN, pfile) != NULL)
		{
			double lat_long_array [4] = {0, 0, 0, 0}; 
			parsing_module(string_line, lat_long_array);
			num_entries++;
			memset(string_line, 0, MAX_BUFFER_LEN);
		}

	}
	fclose(pfile);
}

/*
	Parsing module
*/
int parsing_module(char* input_string, double* lat_long_array)
{
	double x1, x2, y1, y2;
	int line_id;

	line_id = (int)atoi(strtok(input_string, ": ([,])"));

	//printf("line Id %d ",line_id);

	x1 = (double)atof(strtok(NULL, ": ([,])"));
	y1 = (double)atof(strtok(NULL, ": ([,])"));
	x2 = (double)atof(strtok(NULL, ": ([,])"));
	y2 = (double)atof(strtok(NULL, ": ([,])"));

	lat_long_array[0] = x1;
	lat_long_array[1] = y1;
	lat_long_array[2] = x2;
	lat_long_array[3] = y2;
	
	//printf("%f %f %f %f\n", x1, y1, x2, y2);

	return line_id;
}