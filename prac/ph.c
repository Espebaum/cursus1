/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:56:04 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/23 22:57:16 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	printf("%ld\n", tp.tv_sec * 1000 + tp.tv_usec / 1000);
	usleep(1000);
	gettimeofday(&tp, NULL);
	printf("%ld\n", tp.tv_sec * 1000 + tp.tv_usec / 1000);
}
