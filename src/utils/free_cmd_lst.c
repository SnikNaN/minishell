/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:53:24 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/13 13:41:04 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void *cmd)
{
	free(((t_command *) cmd)->cmd_line);
	ft_lstclear(&((t_command *) cmd)->element, free_word);
	free(cmd);
}

void	free_word(void *word)
{
	if (word)
	{
		free(((t_word *) word)->val);
		free(word);
	}
}

void	free_cmds(t_list **cmds)
{
	if (cmds)
		ft_lstclear(cmds, free_cmd);
}
