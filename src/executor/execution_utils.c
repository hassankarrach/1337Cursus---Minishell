/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:12:24 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/07 06:13:31 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_cmds(char **args, char *cmd)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd != NULL && cmd[0] == '/')
	{
		paths = (char **)malloc(sizeof(char *) * (2));
		if (!paths)
			return (NULL);
		return (paths[0] = ft_strdup(cmd), paths[1] = 0, paths);
	}
	while (args[i] != NULL)
		i++;
	paths = (char **)malloc(sizeof(char *) * (i + 1));
	if (!paths)
		return (NULL);
	i = 0;
	while (args[i] != NULL)
	{
		tmp = ft_strjoin(args[i], "/");
		paths[i++] = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	return (paths[i] = 0, paths);
}

char	*check_access(char **paths)
{
	int		i;
	char	*cmd;

	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], X_OK) != -1)
		{
			cmd = ft_strdup(paths[i]);
			return (cmd);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**args;
	char	**paths;
	char	*check;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	args = ft_split((env[i] + 5), ':');
	paths = set_cmds(args, cmd);
	check = check_access(paths);
	ft_free(args);
	ft_free(paths);
	return (check);
}

void check_cmd(char **args, char **env)
{
	char *cmd;
	
	cmd = *args;
	if (cmd[0] == '.' && cmd[1] == '/')
		return ;
	if(cmd[1] == '/')
		return ;
	*args = find_path(cmd, env);
}
