#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct drawing		drawing;

struct drawing
{
	int		width;
	int		height;
	char	*matrice;
};

typedef struct rectangle	rectangle;

struct rectangle
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
};

int	ft_strlen(char *str)
{
	int		cnt;

	cnt = 0;
	while (*str++)
		cnt++;
	return (cnt);
}

int	get_info(FILE *file, drawing *drawing)
{
	char	*tmp; // draw zone 문자열 tmp
	int		i;		//반복문 돌릴 i
	char	background; //draw zone 문자 background

	if (fscanf(file, "%d %d %c\n", &drawing->width, &drawing->height, &background) == 3)
	{
		if ((drawing->width < 1) || (drawing->width > 300) || (drawing->height < 1) || (drawing->height > 300))
			return (1);
		tmp = (char *) malloc(sizeof(char) * drawing->width * drawing->height);
		drawing->matrice = tmp;
		if (!drawing->matrice)
			return (1);
		i = 0;
		while (i < drawing->width * drawing->height)
			drawing->matrice[i++] = background;
		return (0);
	}
	return (1);
}

int	is_in_rectangle(float x, float y, rectangle *rectangle)
{
	if ((x < rectangle->x) || (rectangle->x + rectangle->width < x) || (y < rectangle->y) || (rectangle->y + rectangle->height < y))
		return (0);
	if ((x - rectangle->x < 1.00000000) || (rectangle->x + rectangle->width) - x < 1.00000000
			|| (y - rectangle->y) < 1.00000000 || (rectangle->y + rectangle->height) - y < 1.00000000)
		return (2);
	return (1);
}

void	execute_one(rectangle *rect, drawing *drawing, int x, int y)
{
	int	is_in;

	is_in = is_in_rectangle((float)x, (float)y, rect);
	if ((is_in == 2) || (is_in == 1 && (rect->type == 'R'))) //2 테두리, 1 꽉찬 직사각형 
		drawing->matrice[x + y * drawing->width] = rect->color;
	return ;
}

int	apply_op(rectangle *rect, drawing *drawing)
{
	int	i;
	int	j;

	if ((rect->width <= 0.00000000) || (rect->height <= 0.00000000)
			|| (rect->type != 'R' && rect->type != 'r'))
		return (1); // 기본적인 너비와 높이 조건
	i = 0;
	while (i < drawing->width)
	{
		j = 0;
		while (j < drawing->height)
			execute_one(rect, drawing, i, j++);
		i++;
	}
	return (0);
}

void	print_info(drawing *zone)
{
	int	i;
	
	i = 0;
	while (i < zone->height)
		printf("%.*s\n", zone->width, zone->matrice + i++ * zone->width);
}

int	execute(FILE *file)
{
	int			scan_ret;
	drawing		drawing;
	rectangle	rect;

	if (!get_info(file, &drawing)) //drawing을 바꿔야하니까 주소로 보내줌
	{
		scan_ret = fscanf(file, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.width, &rect.height, &rect.color);
		while (scan_ret == 6)
		{
			if (apply_op(&rect, &drawing)) // 기본적인 조건 확인 및 i와 j를 돌면서 직접 draw zone을 조정
				return (1);
			scan_ret = fscanf(file, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.width, &rect.height, &rect.color);
		}
		if (scan_ret == -1)
		{
			print_info(&drawing);
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	FILE	*file;

	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (file && !execute(file))
			return (0);
		i = ft_strlen("Error: Operation file corrupted\n");
		write(1, "Error: Operation file corrupted\n", i);
	}
	else 
	{
		i = ft_strlen("Error: argument\n");
		write(1, "Error: argument\n", i);
	}
	return (1);
}
