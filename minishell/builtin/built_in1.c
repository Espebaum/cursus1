/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*          				                                 +:+ +:+
			+:+ */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:22:56 by youngski          #+#    #+#             */
/*   Updated: 2023/02/11 19:35:59 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_check(char *str)
{
	if (!ft_strncmp("echo", str, 4) && str[4] == 0)
		return (1);
	if (!ft_strncmp("cd", str, 2) && str[2] == 2)
		return (1);
	if (!ft_strncmp("pwd", str, 4) && str[4] == 0)
		return (1);
	if (!ft_strncmp("export", str, 7) && str[7] == 0)
		return (1);
	if (!ft_strncmp("unset", str, 6) && str[6] == 0)
		return (1);
	if (!ft_strncmp("env", str, 4) && str[4] == 0)
		return (1);
	if (!ft_strncmp("exit", str, 5) && str[5] == 0)
		return (1);
	return (0);
}

char	**cutting_t(char **t, int *flag)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	(t)++;
	while (t[i])
	{
		temp = &t[i];
		j = 0;
		if (t[i][j] == '-')
		{
			j++;
			while (t[i][j] != 0)
			{
				if (t[i][j] != 'n' && t[i][j] != 0)
					return (temp);
				j++;
			}
			if (t[i][j - 1] == '-')
				return (temp);
			if (t[i][j] == 0)
				*flag = 1;
		}
		else
			return (temp);
		i++;
	}
	if (i == 0)
		return (temp);
	return (&t[i]);
}

int	built_echo(char **t)
{
	int	flag;

	flag = 0;
	if (!ft_strncmp(t[0], "echo", 5) && t[1] == NULL)
	{
		printf("\n");
		return (1);
	}
	t = cutting_t(t, &flag);
	while (t && t[0])
	{
		if (t && t[0] != NULL)
		{
			printf("%s", t[0]);
			if (*(t + 1) != 0)
				printf(" ");
		}
		else
			printf("\n");
		t++;
	}
	if (flag == 0)
		printf("\n");
	g_exit_code = 0;
	return (1);
}

char	*get_home(char **envp)
{
	while (*envp && ft_strncmp(*envp, "HOME", 4))
		envp++;
	if (!*envp)
		return (0);
	return (*envp + 5);
}

int	built_cd(char **t, char **envp)
{
	char	**temp;
	char	*home;

	temp = deep_copy_env(envp);
	home = get_home(temp);
	if (t[1] == 0)
	{
		if (!home)
		{
			printf("cd: HOME not set\n");
			g_exit_code = 1;
			return (1);
		}
		else
			chdir(home);
	}
	else
	{
		if (chdir(t[1]) != 0)
		{
			g_exit_code = 1;
			printf("cd: %s: No such file or directory\n", t[1]);
			return (1);
		}
	}
	g_exit_code = 0;
	free(temp);
	return (1);
}

int	built_pwd(char **builtin)
{
	char	t[2048];

	(void)builtin;
	getcwd(t, 2048);
	printf("%s\n", t);
	//free(t);
	g_exit_code = 0;
	return (1);
}

void	init_make_env(int *i, char **key, char **value, char *t)
{
	int	len;

	len = ft_strlen(t);
	*i = 0;
	*key = (char *)malloc(sizeof(char) * (len + 1));
	if (ft_strchr(t, '='))
	{
		*value = (char *)malloc(sizeof(char) * (len + 1));
		*value[0] = 0;
	}
	else
		*value = 0;
	*key[0] = 0;
}

void	make_env(char *t, t_list **head)
{
	int		flag;
	char	*key;
	char	*value;
	int		i;

	flag = 0;
	init_make_env(&i, &key, &value, t);
	while (t && *t)
	{
		if (*t == '=' && flag == 0)
		{
			t++;
			i = 0;
			flag = 1;
			continue ;
		}
		else if (*t != '=' && flag == 0)
			key[i++] = *t;
		else if (flag == 1)
			value[i++] = *t;
		t++;
	}
	new_value(head, key, value);
}

int	export_parsing(t_list **head, char **t)
{
	int		ret;

	ret = 0;
	t++;
	while (*t)
	{
		if (env_error_check(*t))
		{
			printf("export: `%s': not a valid identifier\n", *t);
			t++;
			ret = 1;
			continue ;
		}
		while (*t && **t)
		{
			if (*t[0] == '=')
			{
				t++;
				ret = 1;
				continue ;
			}
			make_env(*t, head); //make key, value and upload it
			t++;
		}
	}
	return (ret);
}

int	built_export(char **builtin, t_list *head)
{
	char	**t;

	(void)builtin;
	if (!t)
		return (0);
	if (!builtin[1])
	{
		print_export(head);
		g_exit_code = 0;
		return (1);
	}
	else
	{
		if (!export_parsing(&head, builtin))
			g_exit_code = 0;
		else
			g_exit_code = 1;
	}
	return (1);
}

void	del_one(char *t, t_list *head_first)
{
	t_list	*head;
	t_list	*prev;

	head = head_first;
	prev = 0;
	while (head)
	{
		if (!ft_strncmp(head->key, t, ft_strlen(t) + 1))
		{
			if (prev)
				prev->next = head->next;
			else
				head_first = head_first->next;
			free(head->key);
			if (head->value)
				free(head->value);
			free(head);
			break;
		}
		prev = head;
		head = head->next;
	}
}

int	built_unset(char **builtin, t_list *head)
{
	int	i;

	i = 1;
	if (!builtin[1])
	{
		g_exit_code = 0;
		return (1);
	}
	while ((builtin)[i])
	{
		if (builtin[i])
			del_one(builtin[i], head);
		i++;
	}
	g_exit_code = 0;
	return (1);
}

int	built_env(char **builtin, t_list *head)
{
	if (builtin[1])
		return (0);
	print_env(head);
	g_exit_code = 0;
	return (1);
}

int	exit_num_arg_req(char *str)
{
	printf("exit: ");
	printf("%s: ", str);
	printf("numeric argument required\n");
	exit(255);
	return (0);
}

int	is_exit_code_num(char *str)
{
	if (*str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int	non_exit_many_arg()
{
	printf("exit: too many arguments\n");
	g_exit_code = 1;
	return (g_exit_code);
}

int	call_exit(char **builtin, t_list *head)
{
	int	is_first_arg_num;
	int	exit_code;

	printf("exit\n");
	if (builtin[1] == NULL)
		exit(0);
	is_first_arg_num = is_exit_code_num(builtin[1]);
	if (is_first_arg_num == 0)
		exit_num_arg_req(builtin[1]);
	if (builtin[2] != NULL)
		non_exit_many_arg();
	exit_code = ft_atoi(builtin[1]);
	exit(exit_code);
	return (0);
}
// exit -> 정상 종료 -> exit(0)
// exit (long min ~ long max) -> 종료 -> exit(long min ~ long max)
// exit (long min보다 작거나 long max보다 큼) -> exit: a: numeric argument required, exit(255)
// exit 1 1 -> 종료 안함 -> exit: too many arguments
// exit 1 a -> 이하 동문
// exit	a -> 종료함(?) -> exit: a: numeric argument required, exit(255)
// exit a 1 -> 종료함(?) -> exit: a: numeric argument required, exit(255)


int	check_builtin(char **builtin, t_list *head, char **envp)
{
	int	result;

	result = -1;
	if (!ft_strncmp(builtin[0], "echo", 5) || (ft_strnstr(builtin[0], "echo",
				ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_echo(builtin);
	else if (!ft_strncmp(builtin[0], "cd", 3) || (ft_strnstr(builtin[0], "cd",
					ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_cd(builtin, envp);
	else if (!ft_strncmp(builtin[0], "pwd", 4) || (ft_strnstr(builtin[0], "pwd",
					ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_pwd(builtin);
	else if (!ft_strncmp(builtin[0], "export", 7) || (ft_strnstr(builtin[0],
					"export", ft_strlen(builtin[0])) && access(builtin[0],
					X_OK) != -1))
		result = built_export(builtin, head);
	else if (!ft_strncmp(builtin[0], "unset", 6) || (ft_strnstr(builtin[0],
					"unset", ft_strlen(builtin[0])) && access(builtin[0],
					X_OK) != -1))
		result = built_unset(builtin, head);
	else if (!ft_strncmp(builtin[0], "env", 4) || (ft_strnstr(builtin[0], "env",
					ft_strlen(builtin[0])) && access(builtin[0], X_OK) != -1))
		result = built_env(builtin, head);
	else if (!ft_strncmp(builtin[0], "exit", 5) || (ft_strnstr(builtin[0],
					"exit", ft_strlen(builtin[0])) && access(builtin[0],
					X_OK) != -1))
		result = call_exit(builtin, head);
	return (result);
}
