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

// typedef struct s_environment
// {
// 	char	*key;
// 	char	*value;
// 	struct s_environment	*next;
// } t_environment;

typedef struct s_tree
{
	int	type;
} t_tree;


void	execute();
int		specify_types(t_tree *node);
void	check_cmd(char **args, char	**env);

#endif