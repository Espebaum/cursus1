#include <stdio.h>
#include <string.h>

int	builtin_check(char *str)
{
	return (strncmp("cd", str, strlen("cd") + 1) == 0 || \
	strncmp("echo", str, strlen("echo") + 1) == 0 || \
	strncmp("pwd", str, strlen("pwd") + 1) == 0 || \
	strncmp("export", str, strlen("export") + 1) == 0 || \
	strncmp("unset", str, strlen("unset") + 1) == 0 || \
	strncmp("env", str, strlen("env") + 1) == 0 || \
	strncmp("exit", str, strlen("exit") + 1));
}

int main(void)
{
	char	*str = "echo";
	char	*str2 = "clear";

	int	a = builtin_check(str);
	int b = builtin_check(str2);

	printf("a : %d, b : %d\n", a, b);
	return 0;
}
