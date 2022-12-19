/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:06:50 by gyopark           #+#    #+#             */
/*   Updated: 2022/12/17 14:46:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sep(char s, char c)
{
	if (s == c || s == 0)
		return (1);
	return (0);
}

int	count_size(char const *s, char c)
{
	int	s_size;

	s_size = 0;
	while (*s)
	{
		if (!is_sep(*s, c) && is_sep(*(s + 1), c))
			s_size++;
		s++;
	}
	return (s_size);
}

void	ft_freeall(char **spl)
{
	size_t	j;

	j = 0;
	while (spl[j])
	{
		free(spl[j]);
		j++;
	}
	free(spl);
	return ;
}

void	place_word(char **spl, char const *s, char c, int *flag)
{
	int		s_idx;
	int		i;

	s_idx = 0;
	while (*s)
	{
		if (is_sep(*s, c))
			s++;
		else
		{
			i = 0;
			while (*(s + i) && !is_sep(*(s + i), c))
				i++;
			spl[s_idx] = ft_substr(s, 0, i);
			if (spl[s_idx] == NULL)
			{
				*flag = 1;
				ft_freeall(spl);
				return ;
			}
			s_idx += 1;
			s += i;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**spl;
	int		s_size;
	int		flag;
	int		i;

	i = ft_strlen(s);
	if (s[i] == ' ' && s[i + 1] == '\0')
		error_exit();
	flag = 0;
	if (!s)
		return (NULL);
	s_size = count_size(s, c);
	spl = (char **) malloc(sizeof(char *) * (s_size + 1));
	if (spl == NULL)
		return (NULL);
	place_word(spl, s, c, &flag);
	if (flag == 1)
		return (NULL);
	spl[s_size] = NULL;
	return (spl);
}
