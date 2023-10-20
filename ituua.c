#include "shell.h"

/**
 * num_len - Counts the digit length of a number.
 * @num: the number to be count.
 * Return: length.
*/
int num_len(int num)
{
	unsigned int num1;
	int length = 1;

	if (num < 0)
	{
		length++;

		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}

	while (num > 9)
	{
		length++;
		num1 /= 10;
	}

	return (length);
}

/**
 * _itoa - Converts an int to a string.
 * @num: the number to be count.
 * Return: beffer.
*/
char *_itoa(int num)
{
	int length = num_len(num);
	unsigned int num1;
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));

	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;

	do {
		buffer[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return (buffer);
}
