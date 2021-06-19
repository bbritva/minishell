#include "../includes/minishell.h"

/************************************
 * 			all_args_free			*
 * **********************************
*/
/* Description:
 * Free all->args memory.
*/

void	all_args_free(t_all *all)
{
	int	i;
write(1, "Befor all_args_free\n", 21);
	i = 0;
	while (all->args[i])
	{
printf("all->args[%d] = |%s|\n", i, all->args[i]);
		free(all->args[i]);
		all->args[i] = NULL;
		++i;
	}
write(1, "After executor\n", 16);
}

/************************************
 * 		1.4.1. command_not_found	*
 * **********************************
*/
/* Description:
 * Prints the result or error to standard 
 * output as needed. Bash standart erorr $? sets 127.
 * 
 * Contains functions:
 * libft. ft_strlen;
*/

void command_not_found(t_all *all)
{
	all->completion_code = 0;
	if (executable(all) == 0)
		return ;
	write(1, "minishell: ", 12);
	write(1, all->args[0], ft_strlen(all->args[0]));
	write(STDOUT_FILENO, COM_NOT_FOUND, ft_strlen(COM_NOT_FOUND));
	all->completion_code = 127;
}

/************************************
 * 		1.4. executor				*
 * **********************************
*/
/* Description:
 * Checks the command flag (enum) and sends the 
 * command for execution.
 * Prints the result or error to standard output as
 * needed.
 * 
 * Contains functions:
 * 1.4.1. command_not_found;
 * 		Prints the result or error to standard 
 * 		output as needed. Bash standart erorr $? 127.
 * 1.4.2. exec_echo;
 * 		execution command 'echo'
 * exec_cd;
 * exec_pwd;
 * exec_env;
 * exec_export;
 * exec_unset;
 * 1.5.   exit_clean;
*/

int executor(t_all *all)
{
	if (all->flag_command == not_found)
		command_not_found(all);
	else if (all->flag_command == exit_shell)
		exec_exit(all);
	else if (all->flag_command == echo)
		exec_echo(all);
	else if (all->flag_command == cd)
		exec_cd(all);
	else if (all->flag_command == pwd)
		exec_pwd(all);
	else if (all->flag_command == env)
		exec_env(all);
	else if (all->flag_command == export)
		exec_export(all);
	else if (all->flag_command == unset)
		exec_unset(all);
	else
		write(1, "other command\n", 15);
	all_args_free(all);
	return (1);
}

//echo m$PWD$USER$