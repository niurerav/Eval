/*
	Code eval challenge: Bay Bridges

	Author: Ravi Niure
	Linkedin/Github: niurerav
	Twitter: NiureRavi
	Website: www.raviniure.com
	Department of Electrical and Computer Engineering
	University of Toronto
*/


/*
	Problem Statement
	-----------------
	CHALLENGE DESCRIPTION:

	A new technological breakthrough has enabled us to build bridges that can withstand
	 a 9.5 magnitude earthquake for a fraction of the cost. Instead of retrofitting existing 
	 bridges which would take decades and cost at least 3x the price we're drafting up a proposal 
	 rebuild all of the bay area's bridges more efficiently between strategic coordinates outlined below.

	You want to build the bridges as efficiently as possible and connect as 
	many pairs of points as possible with bridges such that no two bridges cross. 
	When connecting points, you can only connect point 1 with another point 1, point 2 with another point 2.

	At example given on the map we should connect all the points except points with number 4.

	INPUT SAMPLE:

	Your program should accept as its first argument a path to a filename. Input example is the following

	1: ([37.788353, -122.387695], [37.829853, -122.294312])
	2: ([37.429615, -122.087631], [37.487391, -122.018967])
	3: ([37.474858, -122.131577], [37.529332, -122.056046])
	4: ([37.532599,-122.218094], [37.615863,-122.097244])
	5: ([37.516262,-122.198181], [37.653383,-122.151489])
	6: ([37.504824,-122.181702], [37.633266,-122.121964])
	Each input line represents a pair of coordinates for each possible bridge.

	OUTPUT SAMPLE:

	You should output bridges in ascending order.
	1
	2
	3
	5
	6
	(Check lines on the map)

	Link: https://www.codeeval.com/public_sc/109/

*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define ERROR_WHILE_OPENING_FILE 1
#define MAX_BUFFER_LEN 256

#define NUM_ENTRIES 1000 //FIX: gotta change this later on

typedef int bool;
#define true 1
#define false 0

int counter = 0;

/*
	Bridge Structure
	----------------

	1. Bridge Line Properties (double array): corresponds to the properties of line that the bridge makes. stored as [Line Id, slope, y-intercept]
	2. Bridges Crossed (integer array): keeps the ID of all bridges that it crosses
	3. Number of Bridges Crossed (integer): number of bridges it crosses *** we can get derive this property from property 2. as well. 
*/
struct bridge
{
	/* data */
	double bridge_line_properties[3];
	int bridges_crossed[NUM_ENTRIES]; //Worst case: one bridge crosses all other bridges
	int number_bridge_crossed;
};

//Array of struct bridge
struct bridge bridges[NUM_ENTRIES+1];

//Function Definitions************************************************************************************************************************

//HELPER FUNCTIONS

/*
	Slope Calculator
*/
double get_slope(double* points);

/*
	Y-intercept Calculator
*/
double get_y_intercept(double* points, double slope);

/*
	Printer
*/
void print();

/*
	Max Finder
*/
int max_position(int* array);


//MODULES
/*
	Parsing Module
	@param: input_string, consists of a single line entry extracted from the file
			input_string is in form: "1: ([37.788353, -122.387695], [37.829853, -122.294312])"
			from which X1, Y1, X2, and Y2 are to be extracted.
	@param: lat_long_array, double array which should be modified by the parsing module to 
			include latitude and longitude information of the two points in the format 
			[X1, Y1, X2, Y2]
	@return: integer that represents the ID of each entry. '1' from above example.
			will return -1 if parsing was unsuccessful.
*/
int parsing_module(char* input_string, double* lat_long_array);

/*
	Equation Generator
	This function computes the equation of a line represented by the two pair of points. And the properties of
	the line (slope 'm' and 'c' intercept) and its id is stored in the line_properties array
	 as [line_id, slope, y-intercept]
	Remember: equation of line is Y = mX + C

	@param: lat_long_array consists of latitude and longitude information of the two points in the format
			[X1, Y1, X2, Y2]

	@param: line_properties, is an empty array which needs to be updated with slope, line Id and y-intercept
			in the form [line_id, slope, y-intercept]

	@param: line_id, corresponding integer value that represents the entree number in the input file

	Note: When the line is vertical, slope is stored as 'NULL' and Y-intercept represents the constant x-intercept;
*/
void equation_generator(double* lat_long_array, double* line_properties, int line_id);

/*
	Intersection Test Module
	This module checks whether a new line that will be created from new set of points will intersect with the reference line.
	
	@param: reference_line - > [line id, slope, ]
	@param: new_points - > [X1, Y1, X2, Y2]
	@param: new_line_id, ID of the new set of points

	@returns: true if line intersects with any line on the list
				false if the new line doesn't intersect or in other words new bridge is passed to be built. 
*/
bool intersection_test_module(double* reference_line, double* new_points, int new_line_id);

/*
	List Updater
	Updates the passed list with new line that passed the intersection test module

	@param: line_id of the new line
	@param: new_points for a new line that passed the test
*/
void list_update(int line_id, double* new_points);

//Function Implementations******************************************************************************************************************

/*
	Main Function
*/
int main(int argc, char* argv[])
{
	FILE* pfile;
	pfile = fopen(argv[1], "r");

	char string_line [MAX_BUFFER_LEN];
	memset(string_line, 0, MAX_BUFFER_LEN);

	if(pfile == NULL)
	{
		printf("error: %d\n", ERROR_WHILE_OPENING_FILE);
	}
	else
	{
		while(fgets(string_line, MAX_BUFFER_LEN, pfile) != NULL)
		{
			int line_id = 0;
			double lat_long_array [4] = {0, 0, 0, 0};
			double line_properties [3] = {0, 0, 0};
			line_id = parsing_module(string_line, lat_long_array);


			if(counter == 0)
			{
				equation_generator(lat_long_array, line_properties, line_id);
				list_update(line_id, lat_long_array);
				counter++;
			}
			else
			{
				int i;
				list_update(line_id, lat_long_array);
				for(i = 1; i <= counter; i++)
				{
					if (intersection_test_module(bridges[i].bridge_line_properties, lat_long_array, line_id) == true)
					{
						
						bridges[counter+1].bridges_crossed[bridges[counter+1].number_bridge_crossed] = bridges[i].bridge_line_properties[0];
						bridges[counter+1].number_bridge_crossed++;

						bridges[i].bridges_crossed[bridges[i].number_bridge_crossed] = line_id;
						bridges[i].number_bridge_crossed++;
					}

				}
				counter++;

			}
			memset(string_line, 0, MAX_BUFFER_LEN);
		}
		//print();

	}
	fclose(pfile);


	int temp_array[counter+1];
	int i;
	temp_array[0] = -1;

	for(i = 1; i <= counter; i++)
		temp_array[i] = bridges[i].number_bridge_crossed;

	int max_pos;
	int max_cross;
	while((max_cross = bridges[max_pos = max_position(temp_array)].number_bridge_crossed) != 0)
	{
		//printf("max_pos %d\n", max_pos);
		temp_array[max_pos] = -1;
		for(i = 0; i < max_cross; i++)
		{
			temp_array[bridges[max_pos].bridges_crossed[i]]--;
		}
	}

	for(i = 0; i <= counter; i++)
	{
		if(temp_array[i] >= 0)
			printf("%d\n", i);
	}



}

//HELPER FUNCTIONS===============================================================================================================

/*
	Slope Calculator
*/
double get_slope(double* points)
{
	double x_var = points[2] - points[0];
	double y_var = points[3] - points[1];

	double slope;
	if (x_var == 0)
		slope = INFINITY;
	else
		slope = y_var/x_var;
	return slope;
}

/*
	Y-intercept Calculator
*/
double get_y_intercept(double* points, double slope)
{
	if (slope != INFINITY)
		return (points[1] - slope*points[0]);
	else
		return points[0]; //read the description above
}

/*
	Printer
*/
void print()
{
	int i;
	int j;
	for(i = 1; i <= counter; i++)
	{
		printf("%d ", (int)bridges[i].bridge_line_properties[0]);
		for(j = 0; j < bridges[i].number_bridge_crossed; j++)
		{
			printf("%d, ", bridges[i].bridges_crossed[j]);
		}
		printf("\n");
	}
}


/*
	Max Finder
*/
int max_position(int* array)
{
	int max_pos = 1;
	int i;
	for (i = 2; i <= counter; ++i)
	{
		if(array[i] > array[max_pos])
			max_pos = i;
	}
	return max_pos;
}



//MODULES=========================================================================================================================
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

/*
	Equation Generator
*/
void equation_generator(double* lat_long_array, double* line_properties, int line_id)
{
	double slope;
	double y_intercept;

	slope = get_slope(lat_long_array);
	y_intercept = get_y_intercept(lat_long_array, slope);

	line_properties[0] = line_id;
	line_properties[1] = slope;
	line_properties[2] = y_intercept;
}

/*
	Intersection Test Module
*/
bool intersection_test_module(double* reference_line, double* new_points, int new_line_id)
{
	double x_lower_limit;
	double x_upper_limit;
	double new_line_slope = get_slope(new_points);
	double new_y_intercept;

	if(new_line_slope != INFINITY)
		new_y_intercept = get_y_intercept(new_points, new_line_slope);

	if(new_points[0] > new_points[2])
	{
		x_lower_limit = new_points[2];
		x_upper_limit = new_points[0];
	}
	else if (new_points[0] < new_points[2])
	{
		x_lower_limit = new_points[0];
		x_upper_limit = new_points[2];
	}
	else //vertical line
	{
		x_upper_limit = x_lower_limit = new_points[0];
	}

	if (reference_line[1] == new_line_slope)
	{
		//lines are parallel
		if(new_y_intercept != reference_line[2])
		{
			return false;
		}
		else return true;
	}
	else
	{
		double x_point;
		//lines are not parallel
		if (reference_line[1] == INFINITY) //reference line is vertical
		{
			x_point = reference_line[2];
			if(x_point < x_lower_limit || x_point > x_upper_limit)
			{
				return false;

			}
			else return true;
		}
		else if (new_line_slope == INFINITY) //new line is vertical
		{
			x_point = new_y_intercept;
			if (x_point < x_lower_limit || x_point > x_upper_limit)
			{
				return false;
			}
			else return true;

		}
		else //none of them are vertical
		{
			x_point = (new_y_intercept - reference_line[2])/(reference_line[1] - new_line_slope);
			if (x_point < x_lower_limit || x_point > x_upper_limit)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

}

/*
	List update module
*/
void list_update(int line_id, double* new_points)
{
	double slope = get_slope(new_points);

	//bridge line properties update
	bridges[counter+1].bridge_line_properties[0] = line_id;
	bridges[counter+1].bridge_line_properties[1] = slope;
	bridges[counter+1].bridge_line_properties[2] = get_y_intercept(new_points, slope);

	//number of bridges crossed update
	bridges[counter+1].number_bridge_crossed = 0;
}

