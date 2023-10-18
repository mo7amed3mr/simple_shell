#include "shell.h"

/**
 * _myexit - exit shell
 * @info: Structure arguments. Used to maintain prototype
 * Return: with a given exit 0 status return exit
*/
int _myexit(info_t *info)
{
	int extchck;

	if (info->argv[1]) /* If there is a exit the arguement */
	{
		extchck = _erratoi(info->argv[1]);
		if (extchck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - this change in the current dirr
 * @info: the struct containing arguments
 * Return: Always 0
*/
int _mycd(info_t *info)
{
	char *s, *dirr, buffer[1024];
	int cdir_rt;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirr = _getenv(info, "HOME=");
		if (!dirr)
			cdir_rt = /* TODO: what should this be? */
				chdir((dirr = _getenv(info, "PWD=")) ? dirr : "/");
		else
			cdir_rt = chdir(dirr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cdir_rt = /* TODO: what should this be? */
			chdir((dirr = _getenv(info, "OLDPWD=")) ? dirr : "/");
	}
	else
		cdir_rt = chdir(info->argv[1]);
	if (cdir_rt == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - the change the current directory
 * @info: Structure containing arguments
 * Return: Always 0
*/
int _myhelp(info_t *info)
{
	char **ag_arr;

	ag_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ag_arr); /* the temp att_unused work around */
	return (0);
}

