/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:19:56 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/01 15:19:58 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell	g_lobal_minishell;

int	check_single_cmd(int flag)
{
	int		type;
	t_cmd	*tmp;

	type = (g_lobal_minishell.root)->type;
	if (g_lobal_minishell.root != NULL && type == TOKEN_WORD)
	{
		tmp = (t_cmd *)(g_lobal_minishell.root);
		expansion(&(tmp->args), tmp->args_number);
		flag = check_builtins((tmp->args)[0]);
		if ((flag >= 0 && flag <= 6))
		{
			builtins(tmp->args, flag);
			return (1);
		}
	}
	return (0);
}

void	ctrl_d(char *input)
{
	if (input == NULL)
	{
		printf("exit\n");
		exit(g_lobal_minishell.status);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell-1.0: invalid arguments", 2, '\n');
		exit(1);
	}
	g_lobal_minishell.env = env;
	g_lobal_minishell.status = 0;
	setup_environment(1);
	while (1)
	{
		input = readline(PROMPT);
		ctrl_d(input);
		if (check_just_spaces(1, &input, "\0") || input[0] == '\0')
			continue ;
		if (input[0] != '\0')
			add_history(input);
		init_minishell(input);
		if (check_single_cmd(0) == 1)
			continue ;
		execute();
	}
}
