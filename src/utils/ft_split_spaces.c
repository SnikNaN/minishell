/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:29:16 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 22:30:14 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n'
		|| ch == '\r' || ch == '\t' || ch == '\v')
		return (1);
	else
		return (0);
}

static size_t	ft_datasnaps(const char *str)
{
	size_t	c;

	c = 0;
	while (*str)
	{
		while (*str && is_space(*str))
			str++;
		if (*str)
		{
			c++;
			while (*str && !is_space(*str))
				str++;
		}
	}
	return (c);
}

static int	ft_parse(char **str, const char *src, size_t d_snaps)
{
	size_t	size;
	size_t	str_n;

	str_n = 0;
	while (str_n < d_snaps)
	{
		size = 0;
		while (is_space(*src) && *src)
			src++;
		while (! is_space(*src) && *src)
		{
			src++;
			size++;
		}
		str[str_n] = (char *)malloc(sizeof(char) * (size + 1));
		fatal_err_if(!str[str_n], NULL);
		src -= size;
		ft_strlcpy(str[str_n], src, size + 1);
		src += size;
		str_n++;
	}
	return (1);
}

char	**ft_split_spaces(char const *s)
{
	char	**ret;
	size_t	data_snaps;

	if (!s)
		return (NULL);
	data_snaps = ft_datasnaps(s);
	ret = (char **)malloc(sizeof(char *) * (data_snaps + 1));
	fatal_err_if(!ret, NULL);
	ft_parse(ret, s, data_snaps);
	ret[data_snaps] = NULL;
	return (ret);
}
