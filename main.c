/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:29:39 by aelbasri          #+#    #+#             */
/*   Updated: 2024/03/08 12:29:42 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		line = readline("\033[1;32m-> myMiniSh1.0$ \033[0m");
		if (line != NULL && line != '\0')
			add_history(line);
		//parse(line, env);
	}
}
