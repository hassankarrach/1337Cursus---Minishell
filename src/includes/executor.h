/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:26:12 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/08 21:26:15 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_environment
{
	char	*key;
	char	*value;
	int		flag;
	struct s_environment	*next;
} t_environment;

char			*ft_strdup_key(const char *s, char c);
t_environment	*new_env(char *key, char *value, int flag);

void	execute();
int		specify_types(t_tree *node);
void	check_cmd(char **args, char	**env);
void	expand(char **str);
void	check_to_expand(char **str);
void	expansion(char ***args, int i);

int		args_number(char **args);
void	printf_varibles(int flag);
void	edit_environment(char *str, char *new);

void	builtins(char **args, int flag);
int		check_builtins(char *cmd);
void	echo_builtin(char **args);
void	cd_builtin(char **args);
void	pwd_builtin(char **args);
void	export_builtin(char **args);
void	unset_builtin(char **args);
void	env_builtin(char **args);
void	exit_builtin(char **args);
void	re_create_env();

#endif