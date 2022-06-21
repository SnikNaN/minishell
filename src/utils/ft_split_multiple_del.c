/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multiple_del.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:56:38 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/07 21:56:46 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_char_in_str(char *str, char ch)
{
	while (*str)
	{
		if (ch == *str)
			return (1);
		str++;
	}
	return (0);
}

static size_t	ft_datasnaps(const char *str, char *dels)
{
	size_t	c;

	c = 0;
	while (*str)
	{
		if (is_char_in_str(dels, *str))
			while (is_char_in_str(dels, *str) && *str)
				str++;
		else
		{
			c++;
			while (!is_char_in_str(dels, *str) && *str)
				str++;
		}
	}
	return (c);
}

static int	ft_parse(char **str, const char *src, char *dels, size_t d_snaps)
{
	size_t	size;
	size_t	str_n;

	str_n = 0;
	while (str_n < d_snaps)
	{
		size = 0;
		while (is_char_in_str(dels, *src) && *src)
			src++;
		while (!is_char_in_str(dels, *src) && *src)
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

char	**ft_split_multiple_del(char const *s, char *del)
{
	char	**ret;
	size_t	data_snaps;

	if (!s)
		return (NULL);
	data_snaps = ft_datasnaps(s, del);
	ret = (char **)malloc(sizeof(char *) * (data_snaps + 1));
	fatal_err_if(!ret, NULL);
	ft_parse(ret, s, del, data_snaps);
	ret[data_snaps] = NULL;
	return (ret);
}
