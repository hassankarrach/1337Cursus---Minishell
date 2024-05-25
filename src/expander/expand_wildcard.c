/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:37:25 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/25 11:18:06 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_them(char *list, char *new)
{
	list = ft_strjoin(list, " ");
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(list));
	list = ft_strjoin(list, new);
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(list));
	return (list);
}

static int	is_match(const char *f, const char *p)
{
	while (*f && *p)
	{
		if (*p == '*')
		{
			while (*(p + 1) == '*')
				p++;
			if (*(p + 1) == '\0')
				return (1);
			while (*f && *f != *(p + 1))
				f++;
			if (*f == '\0')
				return (0);
			p++;
		}
		else if (*f != *p)
			return (0);
		else
		{
			f++;
			p++;
		}
	}
	return (*f == '\0' && *p == '\0');
}

char	**get_all_files_in_curr_dir(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*list;

	list = " ";
	dir = opendir(".");
	if (!dir)
		printf("err\n");
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1) == 0)
		{
			entry = readdir(dir);
			continue ;
		}
		list = join_them(list, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (ft_split(list, ' '));
}

int	is_containing_asterisk(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

void	handle_expand_asterisk_wildcard(t_token **list, char *pattern)
{
	char	**files_list;
	int		i;

	i = 0;
	files_list = get_all_files_in_curr_dir();
	add_double_ptr_garbages(files_list);
	while (files_list[i])
	{
		if (is_match(files_list[i], pattern))
			token_list_add_back(list,
				new_token(ft_strdup(files_list[i]), TOKEN_WORD));
		i++;
	}
	free(pattern);
}
