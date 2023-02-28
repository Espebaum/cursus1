#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct drawing		drawing;

struct drawing
{
	int		width;		//draw zone의 x축 길이, 0 < width <= 300
	int		height;		//draw zone의 y축 길이, 0 < height <= 300
	char	*matrice;	//draw zone을 채울 문자의 포인터
};

typedef struct rectangle	rectangle;

struct rectangle
{
	char	type;		//찬 직사각형인지 빈 직사각형인지
	float	x;			//직사각형 좌상단 시작점의 x 좌표 
	float	y;			//직사각형 좌상단 시작점의 y 좌표
	float	width;		//직사각형 너비
	float	height;		//직사각형 높이
	char	color;		//직사각형을 채울 문자
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
	char	*tmp;
	int		i;
	char	background;

	if (fscanf(file, "%d %d %c\n", &drawing->width, &drawing->height, &background) == 3) //파일을 읽어서 drawing 구조체를 채움
	{
		if ((drawing->width < 1) || (300 < drawing->width)
				|| (drawing->height < 1) || (300 < drawing->height))
			return (1); //width와 height가 적정 범위가 아닐 시 리턴
		tmp = (char *)malloc(drawing->width * drawing->height); //draw zone 문자열
		drawing->matrice = tmp;
		if (!drawing->matrice)
			return (1);
		i = 0;
		while (i < drawing->width * drawing->height)
			drawing->matrice[i++] = background; //문자를 받아서 draw zone 문자열을 채운 후
		return (0); //리턴
	}
	return (1);
}

int	is_in_rectangle(float x, float y, rectangle *rectangle)
{
	if ((x < rectangle->x) || (rectangle->x + rectangle->width < x)
			|| (y < rectangle->y) || (rectangle->y + rectangle->height < y))
		return (0); //해당사항 없음
	if (((x - rectangle->x < 1.00000000) || (rectangle->x + rectangle->width) - x < 1.00000000)
			|| (y - rectangle->y < 1.00000000 || (rectangle->y + rectangle->height) - y < 1.00000000))
		return (2); //찬 직사각형
	return (1); //빈 직사각형
}

void	execute_one(rectangle *rect, drawing *drawing, int x, int y)
{
	int	is_in;

	is_in = is_in_rectangle((float)x, (float)y, rect); //:59, 좌표가 직사각형 안에 있는지 판단 
	if ((is_in == 2) || (is_in == 1 && (rect->type == 'R')))
		drawing->matrice[x + y * drawing->width] = rect->color; //draw zone을 변경
	return ;
}

int	apply_op(rectangle *rect, drawing *drawing)
{
	int	j;
	int	i;

	if ((rect->width <= 0.00000000) || (rect->height <= 0.00000000)
			|| (rect->type != 'R' && rect->type != 'r'))
		return (1); //너비가 0이하거나, 높이가 0이하거나 혹은 지정된 타입이 아닌 경우
	i = 0;
	while (i < drawing->width)
	{
		j = 0;
		while (j < drawing->height)
			execute_one(rect, drawing, i, j++); //:70, draw zone을 한칸씩 순회하면서 바꿈 
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
	rectangle	rect;
	drawing		drawing;

	if (!get_info(file, &drawing)) //:36, draw zone check
	{
		scan_ret = fscanf(file, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y,
							&rect.width, &rect.height, &rect.color); //파일을 읽어서 rect 구조체를 채움
		while (scan_ret == 6) // 명령줄일 경우
		{
			if (apply_op(&rect, &drawing)) //:80, draw zone의 내용물을 서식에 맞게 변환
				return (1);
			scan_ret = fscanf(file, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y,
							&rect.width, &rect.height, &rect.color);
		}
		if (scan_ret == -1) // 명령줄이 끝난 경우
		{
			print_info(&drawing); //:99, draw zone을 출력
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
