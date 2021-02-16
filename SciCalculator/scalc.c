#include <stdio.h>
#include <stdlib.h>
/*
 Program to implement a scientific calculator
*/

int main(int argc, char *argv[]) // command line arguments
{
	char operand;
	operand = *argv[2];
	int j = 0;
        int k = 0;
	if (argc != 4)
	{
		printf("Error: invalid number of arguments!\n");
		printf("scalc <operand1> <operator> <operand2>\n");
		return 1;
	}
	else if (operand != '+') 
	{
		printf("Error: operator can only be + !\n");
		return 1;
	}
	else
	{
		for(int i=1; i<argc; i++)
    		{
			switch(i) 
			{
				case 1: 
					// calculating length, and ensuring there are no decimal points
					do 
					{
					       	if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
						{
                                                        printf("Error!! operand can only be positive integers\n");
							return 1;
                                                }
                                                j++;
					} while (argv[i][j] != '\0'); 
					break;
				case 3:
					do 
					{
						if (!(argv[i][k] >= 48 && argv[i][k] <= 57)) 
						{
							printf("Error!! operand can only be positive integers\n");
							return 1;
						}
						k++;
					} while (argv[i][k] != '\0');
					break;
			}
   		}			
		
	}

	// doing addition
	int answerSize = j>k ? j : k; // getting the size of the array that will store the answer
	char answer[answerSize]; // declaring a array that will store the final answer
	int answerIndex = answerSize - 1; // the last value of the character array representing the number to add

	int carry = 0;
	int sum = 0;
	int remainder = 0;
	// to do addition from right to left one must start at the last index of the array but the last index is           // one less than the size therefore j and k are one less
	j--;
	k--;
	while (j > -1 || k > -1) // after the zeroth index has been counted there are no more values to parse
	{
		int firstDigit;
		if (j > -1) { // this condition helps to avoid memory leakage 
			firstDigit = argv[1][j] - 48; // changes ASCII value to its integer equivalent
		} else {
			firstDigit = 0; // sets everything else to zero
		}
		int secondDigit;
		if (k > -1) { 
			secondDigit = argv[3][k] - 48;
		} else {
			secondDigit = 0;
		}

		sum = firstDigit + secondDigit + carry; // calculates sum and adds carry value
		carry = sum / 10;
		remainder = sum % 10;
		answer[answerIndex--] = remainder; // appends the sum from right to left just like in addition
		j--;
		k--;	
	}

	if (carry == 1) // the case that there is one more carry value after all addition has been done
	{
		printf("%d", 1); // just append the last carry value at the left
	}

	for (int i = 0; i < answerSize; i++)
	{
		printf("%d", answer[i]); // print the values stored in the array
	}
	printf("\n");
}


