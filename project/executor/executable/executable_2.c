#include "../../includes/minishell.h"//"minishell.h"

/************************************
 * 	1.1.1. check_command_sourse		*
 * **********************************
*/
/* Description:
 * 		1) The function looks for the '/' character. 
 * 		2) The function checks if only the '.' 
 * 			Character has been entered.
 * 			If yes, completion code is set to 1.
 * Return value:
 * 		If the string com_name contain '/' character or
 * 		contain only '.', return 1.
 * 		else it return 0.
*/

int	check_command_sourse(t_all *all, char *com_name)
{
	int	i;

	i = 0;
	if (com_name[0] == '.' && com_name[1] == '\0')
	{
		write(STDERR_FILENO, "minishell: This command is missing from the subject.\n", 54);
		write(STDERR_FILENO, "In the shell, . is a builtin command ", 38);
		write(STDERR_FILENO, "in its own right, an alias for 'source',", 41);
		write(STDERR_FILENO, "which is used to read in a shell script ", 41);
		write(STDERR_FILENO, "and execute its commands in the current ", 41);
		write(STDERR_FILENO, "shell rather than spawning a subshell, t", 41);
		write(STDERR_FILENO, "ypically used for scripts that set envir", 41);
		write(STDERR_FILENO, "onment variables that you want to use later.\n", 46);
		return (all->completion_code = 1);
	}
	if (com_name[0] == '.' && com_name[1] == '.' && com_name[2] == '\0')
		return (all->completion_code = 127);
	if (!ft_strchr(com_name, '/'))
		return (1);
	return (0);
}

/************************************
 * 	1.1.2. executable_error_print	*
 * **********************************
*/
/* Description:
 * 		Set value error_code to *code_to_on.
 * 		Print error message error_message for 
 * 		input string com_name (command, directory,
 * 		executable, etc.).
 * Return value:
 * 		Integer 1.
*/

int	executable_error_print(int	*code_to_on, char *com_name, char *error_message, int error_code)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, com_name, ft_strlen(com_name));
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	*code_to_on = error_code;
	return (1);
}

/************************************
 * 	1.1.2. split_name_directory		*
 * **********************************
*/
/* Description:
 * 		The function divides the PPPP into two parts. 
 * 		The first part is written to the 'directory' 
 * 		line and contains the path to the executable 
 * 		file. The second line is written to the 
 * 		'com_name' line and contains the name of the 
 * 		executable file.
 * Return value:
 * 		Integer 1. If com_name contains at least one 
 * 			character '/'.
 * 		Integer 0. If com_name not contains at least 
 * 			character '/'.
*/

int	split_name_directory(t_all *all, char **directory, char **com_name)
{
	int		i;
	int		cmp;
	char	c;

	i = ft_strlen(*com_name);
	while (i && (*com_name)[i] != '/')
		--i;
	cmp = 0;
	if ((*com_name)[i] == '/')
	{
		c = (*com_name)[i + 1];
		(*com_name)[i + 1] = '\0';
		*directory = ft_strdup((*com_name));
		(*com_name)[i + 1] = c;
		*com_name = ft_strdup(&((*com_name)[i + 1]));
		cmp = 1;
		if (*directory == NULL || *com_name == NULL)
			completion_code_malloc_error(&(all->completion_code), NULL, "executable (split_name_directory): ");
	}
	return (cmp);
}

/************************************
 * 			1.1.3. find_file		*
 * **********************************
*/
/* Description:
 * 		The function searches for the specified 
 * 		file "com_name" inside the directory, 
 * 		the path to which is specified before 
 * 		the file name.
 * 		If the file was found, the function tries 
 * 		to run it.
 * Return value:
 * 		Integer 0. If the file was found and the 
 * 		function launched it.
 * 		Else return not zero (1 or compiletion code).
*/

int	find_file(t_all *all, char *com_name)
{
	char			*directory;
	int				cmp;
	char			*tmp_com_name;

	cmp = 0;
	tmp_com_name = com_name;
	if (split_name_directory(all, &directory, &com_name))
	{
		if (!all->completion_code)
			return (find_file_in_dir(all, directory, com_name, tmp_com_name));
		else
			return (all->completion_code);
	}
	return (cmp);
}

/************************************
 * 				fork_execve			*
 * **********************************
*/
/* Description:
 * 		A function runs an executable using functions fork() and execve().
 * Return value:
 * 		Integer 0. If the file was found and the 
 * 		function launched it.
 * 		Else return not zero (1 or compiletion code).
*/

int		fork_execve(t_all *all, char *com_name)
{
	int		ret;
	pid_t	pid;
	int		rv;

	ret = 2;
	pid = fork();
	if (pid == 0)
	{
		ret = execve(com_name, all->args, all->env);
		if (ret == -1)
		{
			exit(rv = 2);
		}
	}
	else if (pid < 0)
	{
		write(STDERR_FILENO, "minishell: fork error. try again\n", 34);
		all->completion_code = 1;
		return (1);
	}
	wait(NULL);
	return (!ret);
}
