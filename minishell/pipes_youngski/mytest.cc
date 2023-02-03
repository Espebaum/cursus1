#include <stdio.h>
#include <stdlib.h>

void	copy_orders(char ***t);
void	add_order(char ***t, char *str, int flag);
int main()
{

	char **t;

	t = (char **)malloc(sizeof(char *));
	t[0] = 0;
	copy_orders(&t);
	add_order(&t, "mytemp", 0);
	printf("%s\n",t[0]);
	copy_orders(&t);
	add_order(&t, "gawrge", 1);
	printf("%s\n",t[1]);
	copy_orders(&t);
	add_order(&t, "third", 1);
	printf("%s\n",t[2]);


}
