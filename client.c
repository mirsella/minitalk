#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"

int	main(int argc, char **argv)
{
	int		i;
	int		bit;
	int		pid;
	char	c;

	if (argc != 3)
	{
		ft_printf("usage: ./client [pid] [string]\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		c = argv[2][i];
		bit = 128;
		ft_printf("c: %c, decimal: %d\n", c, c);
		while (bit > 0)
		{
			if (c & bit)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			bit >>= 1;
			usleep(100);
		}
		i++;
	}
	return (0);
}
