/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:17:30 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/17 20:57:15 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_meta_chr(char c)
{
	if (c == '!' || c == '#' || c == '%' || c == '&' || c == '*' || c == '+' \
			|| c == ',' || c == '-' || c == '.' || c == ':' || c == '$' \
				|| c == '=' || c == '?' || c == '@' || c == '[' || c == ']' \
					|| c == '^' || c == '{' || c == '}' || c == '~' \
						|| c == '<' || c == '>' || c == '|' || c == ';' \
							|| c == '\"' || c == '\'')
		return (1);
	return (0);
}
// ", ' -> 처리된 syntax 오류라서 빠짐
// (, ) -> syntax 오류, 앞에서 처리 안했는데 해야할것같음
// ; -> 마찬가지로 앞에서 처리 안한 syntax 오류
// <, >, | -> 처리된 syntax 오류
// '$' 이거 체크해봐야함 ***
