#include "../../includes/minishell.h"//"minishell.h"

/************************************
 * 				 path_env			*
 * **********************************
*/
/* Description:
 * 		The function splits the PATH-variable string 
 * 		in env-array into a two-dimensional array of 
 * 		strings when each character ':' is encountered.
 * Return value:
 * 		Two-dimensional array of path-strings.
*/

char	**path_env(t_all *all)
{
	int		i;
	char	*path_env_value;
	char	**path_env;

	i = get_my_env_index(all->env, "PATH", 4);
	if (all->env[i] == NULL)
		return (NULL);
	path_env_value = ft_strchr(all->env[i], '=');
	path_env = ft_split(++path_env_value, ':');
	if (path_env == NULL)
	{
		all->completion_code = 1;
		write(STDOUT_FILENO, "minishell: ", 12);
		write(STDOUT_FILENO, all->args[0], ft_strlen(all->args[0]));
		write(STDOUT_FILENO, ": malloc error. Try again.\n", 28);
	}
	return (path_env);
}

/************************************
 * 		join_directory_and_command	*
 * **********************************
*/
/* Description:
 * 		The function join two strings (directory and 
 * 		command_name) to one new string.
 * Return value:
 * 		New strings.
*/
char	*join_directory_and_command(char *directory, char *command_name)
{
	char	*tmp;

	tmp = command_name;
	command_name = ft_strjoin("/", command_name);
	if (command_name)
	{
		free(tmp);
		tmp = command_name;
		command_name = ft_strjoin(directory, command_name);
		if (command_name)
			free(tmp);
	}
	return (command_name);
}