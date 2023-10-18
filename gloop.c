#include "main.h"

/**
 * hsh - main the shell loop
 * @info: par & return info the struct
 * @av: the arg vec from main
 * Return: on success 0, on error 1, or error
*/
int hsh(info_t *info, char **av)
{
	ssize_t x = 0;
	int buiiltiin_ret = 0;

	while (x != -1 && buiiltiin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(info);
		if (x != -1)
		{
			set_info(info, av);
			buiiltiin_ret = find_builtin(info);
			if (buiiltiin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (buiiltiin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (buiiltiin_ret);
}
