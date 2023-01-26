#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void	handler(int signum)
{
	if (signum != SIGINT)
		return;
	printf("ctrl + c\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(void)
{
	int		ret;
	char	*line;

	ret = 0;
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("input> ");
		if (line)
		{
			//파싱
			//명령어 및 문자열 실행
			add_history(line);
			free(line);
			line = NULL;
		}
		else
		{
			printf("exit\n");
			exit(0);
		}
	}
	return (0);
}
