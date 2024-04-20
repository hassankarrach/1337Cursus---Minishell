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

void	expand(char **str)
{
	t_environment *tmp;

	if (*str == NULL)
		return ;
	(*str) = ft_strdup(((*str) +  1));
	tmp = global_minishell.environment;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, *str) == 0)
		{
			(*str) = ft_strdup(tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
	(*str) = ft_strdup(NULL);
}
size_t	ft_sublen(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (c == ' ')
	{	
		while (s[i] != '\0' && ft_is_space(s[i]) != 1 && s[i] != '\'')
			i++;
	}
	else
	{
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (i);
}

void	check_to_expand(char **str)
{
	int		i;
	int		j;
	char	*tmp;
	char 	**tmp1;
	char	*tmp2;

	tmp1 = (char **)malloc(sizeof(char *) * 4);
	i = 0;
	while(i < 4)
		tmp1[i++] = NULL;
	tmp = *str;
	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '$')
		{
			tmp1[0] = ft_substr(tmp, 0, ft_sublen(tmp, '$'));
			j = ft_sublen((tmp + i), ' ');
			tmp1[1] = ft_substr(tmp, i, j);
			tmp1[2] = ft_substr(tmp, (i + j), ft_strlen(tmp + j));
		}
		i++;
	}
	if (tmp1[1] != NULL)
	{
		if (ft_strcmp(tmp1[1], "$?") == 0)
			tmp1[1] = ft_itoa(global_minishell.status);
		else
			expand(&(tmp1[1]));
		i = 0;
		tmp2 = ft_strjoin(tmp1[0], tmp1[1]);
		*str = ft_strjoin(tmp2, tmp1[2]);
	}
}
int	exist_in_list(int i)
{
	int j;

	j = 0;
	while (j < global_minishell.a_counter)
	{
		if (i == global_minishell.quote[j])
			return (1);
		j++;
	}
	return (0);
}

void	expansion(char ***args)
{
	char **tmp;
	int 	i;

	tmp = *args;
	i = 0;
	while (tmp != NULL && tmp[i] != NULL)
	{
		if(exist_in_list(i) == 0)
				check_to_expand(&(tmp[i]));
		i++;
	}
}

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
	global_minishell.status = 127;
	ft_putstr_fd("minishell-1.0: Command not found", 2);
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
