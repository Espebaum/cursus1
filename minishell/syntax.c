/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:55:59 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/31 12:48:40 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_func(int *cnt)
{
	int		i;

	printf("in check func: ");
	for(int i=0;i<6;++i)printf("%d ", cnt[i]);
	printf("\n");
	if (cnt[0] == 0 || cnt[0] > 1)
		return (0);
	i = 0;
	// cnt[i] == 1인 경우, redirection만 존재하고 arg가 없을때라 안된다
	while (++i < 5)
		if(cnt[i] == 1)
			return (0);
	if (cnt[5] > 0)
		return (0);
	return (1);
}
/*
	cnt[0]: 명령어의 개수 카운트
	cnt[1] ~ cnt[4]: <, >, <<, >> 개수 카운트 ㄴㄴㄴ그게아니라 1일때는 redirection만 존재 0이면 아예 안존재  아잠만
	cnt[5] 에러임? ㅇㅇ
*/
// 0 -> cmd , 1 -> < , 2 -> > , 3 -> << , 4 -> >>, 5->error
int is_valid_token(t_token *t)
{
	int		is_vaild;
	int		cnt[6];
	int		is_first;
	int		i;

	is_vaild = 1;
	is_first = 1;
	t = t->next;
	while (t)
	{
		printf("%s\n", t->str);
		if (is_first)
		{
			i = -1;
			while (++i < 6)
				cnt[i] = 0;
			is_first = 0;
		}
		if (t->type == T_WORD)
		{
			printf("in word\n");
			cnt[0]++;
			while (t && t->type == T_WORD)
				t = t->next;
		}
		else if (t->type == T_REDIRECT)
		{
			printf("in red\n");
			if (t->str[0] == '<' && t->str[1] == '\0')
			{
				if (cnt[1] > 0)
					cnt[1] = -1;
				else if (cnt[1] == 0)
				{
					cnt[1] = 1;
					t = t->next;
					if (t && t->type == T_WORD)
					{
						cnt[1]++;
						t = t->next;
					}
				}
			}
			else if (t->str[0] == '>' && t->str[1] == '\0')
			{
				if (cnt[2] > 0)
					cnt[2] = -1;
				else if (cnt[2] == 0)
				{
					cnt[2] = 1;
					t = t->next;
					if (t && t->type == T_WORD)
					{
						cnt[2]++;
						t = t->next;
					}
				}
			}
			else if (t->str[0] == '<' && t->str[1] == '<')
			{
				if (cnt[3] > 0)
                {
                    cnt[3] = -1;
                    t = t->next;
                }
				else if (cnt[3] == 0)
				{
					cnt[3] = 1;
					t = t->next;
					if (t && t->type == T_WORD)
					{
						cnt[3]++;
						t = t->next;
					}
				}
			}
			else if (t->str[0] == '>' && t->str[1] == '>')
			{
				if (cnt[4] > 0)
					cnt[4] = -1;
				else if (cnt[4] == 0)
				{
					cnt[4] = 1;
					t = t->next;
					if (t && t->type == T_WORD)
					{
						cnt[4]++;
						t = t->next;
					}
				}
			}
		}
		else if (t->type == T_ERROR)
		{
			cnt[5]++;
			t = t->next;
		}
		else if (t->type == T_PIPE)
		{
			is_vaild &= check_func(cnt);
			is_first = 1;
			t = t->next;
		}
	}
	is_vaild &= check_func(cnt);
	return (is_vaild);
}