/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:48:47 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/09 15:10:35 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_doc	*init_doc(t_doc *doc)
{
	doc->name = NULL;
	doc->count = 0;
	doc->limiters = NULL;
	doc->zero = 0;
	return (doc);
}
