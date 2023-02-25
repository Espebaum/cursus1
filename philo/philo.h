/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:13:16 by gyopark           #+#    #+#             */
/*   Updated: 2023/02/25 19:23:37 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_arg
{
	int					philo_num;		//철학자의 수, 포크의 수
	int					time_to_die;	//수명
	int					time_to_eat;	//밥먹는 시간
	int					time_to_sleep;	//잠자는 시간
	int					eat_times;		//먹어야할 횟수
	long long			start_time;		//먹기 시작한 시간
	int					finish;			//플래그
	int					finished_eat;	//플래그
	//int					*fork_status;	//포크의 상태
	pthread_mutex_t		*forks;			//포크, 공유자원이다, 포크를 뮤텍스로 보호해줘야 한다
	pthread_mutex_t		print;			//마찬가지로 출력이 섞이면 안되므로 뮤텍스로 보호해준다
}	t_arg;

typedef struct s_philo
{
	t_arg		*arg;		//각 철학자는 공유자원을 지닌다.
	int			id;			//철학자의 인덱스이다
	int			left;		//왼쪽에 포크
	int			right;		//오른쪽에 포크
	long long	last_eat_time;	//가장 최근에 식사한 시간
	int			eat_count;	//먹은 횟수
	pthread_t	thread;
}	t_philo;

int		print_err(char *message, int errno);
int		ft_atoi(const char *str);
void	*ft_thread(void *argv);
long	ft_get_time(void);
size_t	ft_strlen(char *str);
void	ft_philo_check_finish(t_arg *arg, t_philo *philo);
int		ft_philo_printf(t_arg *arg, int id, char *message);
void	ft_free_thread(t_arg *arg, t_philo *philo);


#endif
