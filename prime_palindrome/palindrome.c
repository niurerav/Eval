/*
	Code eval challenge: Prime Palindrome

	Author: Ravi Niure
	Linkedin/twitter: niurerav
	Department of Electrical and Computer Engineering
	University of Toronto
*/

/*
	Problem Statement:

	Write a program which determines the largest prime palindrome less than 1000.

	Input: No input

	Output: Print to stdout the largest prime palindrome less than 1000.

	Link: https://www.codeeval.com/open_challenges/3/

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


bool is_prime (int num);
bool is_pdrm (int num);

//Function Definitions

/*
	Is Palindrome
	@param: num, number which is to be determined if it is a palindrome number or not.
			For example: 16461 is a palindrome number.
	@return: 'true' if the number is palindrome or else returns 'false'
*/
bool is_pdrm (int num);

/*
	Is Prime
	@param: num, number which is to be determined if it is a prime number or not.
	@return: 'true' if the number is prime or else returns 'false'
*/
bool is_prime(int num);

//Function Implementations

//Start_Main
int main()
{
	
	int num = 10000;
	for(num; num > 0; num--)
	{
		if(is_prime(num))
		{
			if(is_pdrm(num))
			{
				printf("%d\n", num);			
			}
		}
	}
	
	return 0;
}
//End_Main

//Start_is_pdrm
bool is_pdrm (int num)
{
	bool result = true;
	
	char temp[1024];
	sprintf(temp, "%d", num);
	int i = strlen(temp) - 1;
	int j = 0;
	
	if(i == 1)
	{
		if(temp[i] == temp[j])
		{
			result = true;
			return result;
		}
		else return false;
	}
	else
	{
		while(i!= j)
		{
			if(temp[i] != temp[j])
			{
				result = false;
				return result;
			}
			i--;
			j++;
		}
		return result;
	}
	return result;
}
//End_is_pdrm

//Start_is_prime
bool is_prime(int num)
{
	bool result = false;
	int i = 0;
	for(i = 2; i < num; i++)
	{
		if(num%i == 0)
		{
			result = false;
			break;
		}
			
	}
	if(i == num) result = true;
	else result = false;
	return result;
}
//End_is_prime


