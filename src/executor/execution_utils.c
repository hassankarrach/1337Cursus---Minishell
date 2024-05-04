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

void	re_create_env()
{
	int				i;
	int				j;
	char			*tmp1;
	char			**env;
	t_environment	*tmp;

	tmp = g_lobal_minishell.environment ;
	i = 0; 
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	tmp = g_lobal_minishell.environment;
	while (tmp != NULL)
	{
		tmp1 = ft_strjoin(tmp->key, "=");
		env[j] = ft_strjoin(tmp1, tmp->value);
		tmp = tmp->next;
		j++;
	}
	env[j] = NULL;
	g_lobal_minishell.env = env;
}

void	expand(char **str)
{
	t_environment *tmp;

	if (*str == NULL)
		return ;
	(*str) = ft_strdup(((*str) +  1));
	tmp = g_lobal_minishell.environment;
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
		{
			i++;
			if (s[i] == '$')
				break;
		}
	}
	else
	{
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (i);
}

void	add_the_word(t_list **head, int flag, char *str, int start, int end)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;
	char	**tmp1;
	t_list	*node;

	i = 0;
	tmp = NULL;
	if (str[start] == '\"' || str[start] == '\'')
		start++;
	if (flag == 1 && start >= end)
	{
		node = ft_lstnew("");
		ft_lstadd_back(head, node);
		return ;
	}
	if (start <= end)
	{
		tmp = ft_substr(str, start, end - start);
	}
	if (flag == 0 || flag == 1)
	{
		tmp1 = (char **)malloc(sizeof(char *) * 4);
		i = 0;
		while(i < 4)
			tmp1[i++] = NULL;
		i = 0;
		while(tmp && tmp[i] != '\0')
		{
			if (tmp[i] == '$')
			{
				// tmp1[0] = ft_substr(tmp, 0, ft_sublen(tmp, '$'));
				j = ft_sublen((tmp + i), ' ');
				tmp1[1] = ft_substr(tmp, i, j);
				tmp1[2] = ft_substr(tmp, (i + j), ft_strlen(tmp + j));
			}
			i++;
		}
		if (tmp1[1] != NULL)
		{
			if (ft_strncmp(tmp1[1], "$?", 2) == 0)
				tmp1[1] = ft_strjoin(ft_itoa(g_lobal_minishell.status), (tmp1[1]) + 2);
			else if (ft_strcmp(tmp1[1], "$") != 0)
				expand(&(tmp1[1]));
			i = 0;
			tmp2 = ft_strjoin(tmp1[0], tmp1[1]);
			tmp = ft_strjoin(tmp2, tmp1[2]);
		}
	}
	if (flag == 0 && ft_strcmp(tmp, "") == 0)
		tmp = NULL;
	node = ft_lstnew(tmp);
	ft_lstadd_back(head, node);
}

void	check_to_expand(char **str)
{
	int		i;
	int		j;
	t_list	*head;
	int		start;
	int		end;
	int		flag;
	char	*tmp;
	char 	*tmp1;
	char	*tmp2;

	i = 0;
	flag = 0;
	start = 0;
	tmp = *str;
	head = NULL;
	end = ft_strlen(*str);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			if (tmp[i] == '\'' && flag == 0)
			{
				end = i;
				add_the_word(&head, flag, *str, start, end);
				flag = 2;
			}
			else if (tmp[i] == '\'' && flag == 2)
			{
				end = i;
				add_the_word(&head, flag, *str, start, end);
				flag = 0;
			}
			else if (tmp[i] == '\"' && flag == 0)
			{
				end = i;
				add_the_word(&head, flag, *str, start, end);
				flag = 1;
			}
			else if (tmp[i] == '\"' && flag == 1)
			{
				end = i;
				add_the_word(&head, flag, *str, start, end);
				flag = 0;
			}
			start = end;
		}
		else if (tmp[i] == '$' && flag != 2)
			add_the_word(&head, flag, *str, start, i);
		i++;
	}
	if (start != i)
		add_the_word(&head, flag, *str, start, i);
	tmp1 = NULL;
	while (head != NULL)
	{
		// printf("-->%s\n", (char *)(head->content));
		*str = ft_strjoin(tmp1, (char *)(head->content));
		tmp1 = *str;
		head = head->next;
	}
}
void	edit_args(char ***args, int nb)
{
	int		i;
	int		j;
	char	**tmp;
	char	**new_args;

	i = 0;
	j = 0;
	new_args = (char **)malloc(sizeof(char *) * (nb + 1));
	tmp = *args;
	while(i < nb)
	{
		if (tmp[i] != NULL)
		{
			new_args[j] = ft_strdup(tmp[i]);
			// free(tmp[i]);
			j++;
		}
		i++;
	}
	while(j < nb + 1)
		new_args[j++] = NULL;
	*args = new_args;
	// printf("%d new_args = (%s)\n", j, new_args[0]);
	// printf("%d new_args = (%s)\n", j, new_args[1]);
	// printf("new_args = %s\n", (*args)[0]);

}

void	expansion(char ***args, int nb)
{
	char **tmp;
	int 	i;

	tmp = *args;
	i = 0;
	while (tmp != NULL && tmp[i] != NULL)
	{
		check_to_expand(&(tmp[i]));
		i++;
	}
	// printf("(%s)\n", (*args)[0]);
	edit_args(args, nb);
	// printf("(%s)\n", (*args)[0]);
	// int k = 0;
	// while (k < 4)
	// 	printf("here meme = (%s)\n", tmp[k++]);
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

char	*check_access(char **paths, char *cmd1)
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
	check = check_access(paths, cmd);
	ft_free(args);
	ft_free(paths);
	return (check);
}

void check_cmd(char **args, char **env)
{
	char *cmd;
	struct  stat *buf;

	cmd = *args;
	if (ft_strcmp(cmd, "") == 0)
	{
		ft_putstr_fd("minishell-1.0: Command not found: ", 2, 4);
		ft_putstr_fd("''", 2, '\n');
		g_lobal_minishell.status = 127;
		exit(g_lobal_minishell.status);
	}
	else if ((cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '/'))
	{

		if (access(cmd, X_OK) == -1)
		{
			if (access(cmd, F_OK) == 0)
			{
				ft_putstr_fd("minishell-1.0: Permission denied: ", 2, 4);
				g_lobal_minishell.status = 126;
			}
			else
			{
				ft_putstr_fd("minishell-1.0: Command not found: ", 2, 4);
				g_lobal_minishell.status = 127;
			}
			ft_putstr_fd(cmd, 2, '\n');
			exit(g_lobal_minishell.status);
		}
		else if (stat(cmd, buf) != 0)
		{
			ft_putstr_fd("minishell-1.0: is directory: ", 2, 4);
			ft_putstr_fd(cmd, 2, '\n');
			g_lobal_minishell.status = 126;
			exit(g_lobal_minishell.status);

		}
	}
	else
	{
		*args = find_path(cmd, env);
		if (*args == NULL)
		{
			ft_putstr_fd("minishell-1.0: Command not found: ", 2, 4);
			ft_putstr_fd(cmd, 2, '\n');
			g_lobal_minishell.status = 127;
			exit(g_lobal_minishell.status);
		}
	}
}
