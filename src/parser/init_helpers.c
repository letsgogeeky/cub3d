#include "../../include/cube.h"

void	ft_prerr(char *str, char *argv)
{
	int			i;
	static int	err;

	i = 0;
	if (str == NULL)
		return ;
	if (err == 0)
	{
		write(2, "Error\n", 6);
		err++;
	}
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	if (argv != NULL)
	{
		i = 0;
		while (argv[i] != '\0')
			write(2, &str[i++], 1);
	}
	write(2, "\n", 1);
}

int	set_max_len(char *str, int max)
{
	int	i;

	i = ft_strlen(str);
	if (i > 0 && str[i - 1] == '\n')
		i = i - 1;
	if (max < i)
		return (i);
	return (max);
}

int	find_start_map(char *str)
{
	int	len;
	int	flag;

	len = ft_strlen(str);
	flag = 0;
	while (len > 0)
	{
		if (str[len] == ' ' || str[len] == '\n' || str[len] == '\0')
			len--;
		else if (str[len] == '1' || str[len] == '0' || str[len] == 'N' || \
		str[len] == 'O' || str[len] == 'S' || str[len] == 'W')
		{
			len--;
			flag = 1;
		}
		else
			return (1);
	}
	if (flag == 0)
		return (1);
	return (0);
}
