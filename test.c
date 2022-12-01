#include "libft/libft.h"

int	main(int argc, char **argv)
{
	unsigned char	c;
	int				i;
	int				bit;
	int				j;
	unsigned char	str[8];


	i = 0;
	while (argv[1] && argv[1][i])
	{
		c = argv[1][i];
		bit = 128;
		j = 0;
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
		ft_printf("c: %c, decimal: %d\n", c, c);
		// binary to unsigned char
		c = 0;
		j = 0;
		while (str[j])
		{
			c <<= 1;
			if (str[j] == '1')
				c |= 1;
			j++;
		}
		ft_printf("c: %c, decimal: %d\n", c, c);
		i++;
	}

}

