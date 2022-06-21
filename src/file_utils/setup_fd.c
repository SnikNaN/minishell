/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:03:39 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/14 19:47:10 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redirect_append(t_list *command)
{
	int		f;
	t_word	*word;

	word = get_word_by_type(command, FILE_OUT_APPEND);
	if (word)
	{
		f = open(word->val, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (f == -1)
		{
			f = open("/dev/null", O_WRONLY);
			perror(word->val);
			dup2(f, 1);
			dup2(f, 0);
			return (1);
		}
		dup2(f, 1);
	}
	return (0);
}

int	setup_redirect(t_list *command)
{
	int		f;
	t_word	*word;

	word = get_word_by_type(command, OUT_FILE);
	if (word)
	{
		f = open(word->val, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (f == -1)
		{
			f = open("/dev/null", O_WRONLY);
			perror(word->val);
			dup2(f, 1);
			dup2(f, 0);
			return (1);
		}
		dup2(f, 1);
	}
	return (0);
}

int	setup_redirect_in(t_list *command)
{
	int		f;
	t_word	*word;

	word = get_word_by_type(command, IN_FILE);
	if (word)
	{
		f = open(word->val, O_RDONLY);
		if (f == -1)
		{
			f = open("/dev/null", O_WRONLY);
			perror(word->val);
			dup2(f, 1);
			dup2(f, 0);
			return (1);
		}
		dup2(f, 0);
	}
	return (0);
}

int	setup_here_doc(t_list *command, int std_io[2])
{
	int		f;
	int		save_fd;
	t_word	*word;

	word = get_word_by_type(command, HERE_DOC_OP);
	if (word)
	{
		dup2(std_io[0], 0);
		save_fd = dup(1);
		dup2(std_io[1], 1);
		f = here_doc_fd(get_word_by_type(command, LIM)->val);
		dup2(f, 0);
		dup2(save_fd, 1);
		close(save_fd);
		return (1);
	}
	return (0);
}

int	setup_fd(t_list *command, int std_io[2])
{
	setup_redirect(command);
	setup_redirect_append(command);
	setup_redirect_in(command);
	setup_here_doc(command, std_io);
	return (0);
}
