#include "main.h"

/**
 * main - entry point
 * @ac: argv the count
 * @av: argv the vector
 * Return: on success 0, on error 1
*/
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fdd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdd)
			: "r" (fdd));

	if (ac == 2)
	{
		fdd = open(av[1], O_RDONLY);
		if (fdd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
