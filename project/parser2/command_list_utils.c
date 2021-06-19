#include "minishell.h"

static int free_command(t_command *command)
{
	free_char_array(command->args);
	command->args = NULL;
	free(command);
	command = NULL;
	return (0);
}

int free_commands(t_command **commands)
{
	t_command *tmp;
	t_command *tmp2;
	
	tmp = *commands;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free_command(tmp2);
	}
	free(commands);
	commands = NULL;	
	return (0);
}