/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:06:50 by gyopark           #+#    #+#             */
/*   Updated: 2022/11/12 20:22:58 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char s, char c)
{
	if (s == c || s == 0)
		return (1);
	return (0);
}

int	count_size(char const *str, char c)
{
	int	strs_size;

	strs_size = 0;
	while (*str)
	{
		if (!is_sep(*str, c) && is_sep(*(str + 1), c))
			strs_size++;
		str++;
	}
	return (strs_size);
}

void	ft_strncpy(char *dest, char const *src, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

void	place_word(char **spl, char const *str, char c)
{
	int		strs_idx;
	int		i;

	if (!spl || !str)
		return ;
	strs_idx = 0;
	while (*str)
	{
		if (is_sep(*str, c))
			str++;
		else
		{
			i = 0;
			while (!is_sep(str[i], c))
				i++;
			spl[strs_idx] = (char *) malloc(sizeof(char) * (i + 1));
			if (spl[strs_idx] == NULL)
				return ;
			ft_strncpy(spl[strs_idx], str, i);
			strs_idx += 1;
			str += i;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**spl;
	int		strs_size;

	if (!s)
		return (NULL);
	strs_size = count_size(s, c);
	spl = (char **) malloc(sizeof(char *) * (strs_size + 1));
	if (spl == NULL)
		return (NULL);
	spl[strs_size] = NULL;
	place_word(spl, s, c);
	return (spl);
}
