/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:59:38 by aelbasri          #+#    #+#             */
/*   Updated: 2024/03/09 15:59:42 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	exec_cmd(t_tree *node);
int	exec_pip(t_tree *node);
int	exec_block(t_tree *node);

void	exec_redir(t_tree *node)
{
	if (node->type == RED_IN)
	{
		close(0);
		open(data->file_name, O_RDONLY);
	}
	else
	{
		close(1);
		open(data->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
}

int	exec_and_or(t_tree *node)
{
	int	status;

	if (node->type == O_AND)
	{
		status = specify_types(node->left);
		if (status == 0)
			status = specify_types(node->right);
	}
	else if (node->type == O_OR)
	{
		status = specify_types(node->left);
		if (status != 0)
			status = specify_types(node->right);
	}
	return (status);
}


int	specify_types(t_tree *node)
{
	if (node->type == WORD)
		return (exec_cmd(node));
	else if (node->type == PIP)
		return (exec_pip(node));
	else if (node->type == RED_IN || node->type == RED_OUT)
		exec_redir(node);
	else if (node->type ==  O_AND || node->type == O_OR)
		return (exec_and_or(node));
	else if (node->type == BLOCK)
		return (exec_block(node));
	return (0);
}

void	execute(t_data *data)
{
	if (!(data.root))
		return ;
	data.status = specify_types(data.root);
}
