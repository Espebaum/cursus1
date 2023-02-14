/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_syntax2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:36:48 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/14 21:38:47 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_s_flag(int *in_squote, int *in_dquote, int *s_flag)
{
	if (*in_dquote != 1 && *in_squote == 0)
		*in_squote = 1;
	else
		*in_squote = 0;
	if (*in_dquote != 1)
		(*s_flag)++;
	return (0);
}

int	count_d_flag(int *in_squote, int *in_dquote, int *d_flag)
{
	if (*in_squote != 1 && *in_dquote == 0)
		*in_dquote = 1;
	else
		*in_dquote = 0;
	if (*in_squote != 1)
		(*d_flag)++;
	return (0);
}
