#include "libft/libft.h"

int	main(int argc, char **argv)
{
	unsigned char	c;
	int				i;
	int				bit;
	int				j;
	unsigned char	str[8];


	i = 0;
	ft_printf("str: %s\n", argv[1]);
	while (argv[1] && argv[1][i])
	{
		c = argv[1][i];
		bit = 128;
		j = 0;
		ft_printf("c: %c, decimal: %d\n", c, c);
		while (bit > 0)
		{
			if (c & bit)
				str[j] = '1';
			else
				str[j] = '0';
			bit >>= 1;
			j++;
		}
		str[j] = '\0';
		ft_printf("%s\n", str);
		i++;
	}

}

