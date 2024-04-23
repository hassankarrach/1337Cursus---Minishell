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
	struct s_environment	*next;
} t_environment;

void	execute();
int		specify_types(t_tree *node);
void	check_cmd(char **args, char	**env);
void	expand(char **str);
void	check_to_expand(char **str);
void	expansion(char ***args);

int		builtins(char **args);
int		echo_builtin(char **args);

#endif