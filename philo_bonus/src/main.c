

#include "../include/philosopher_bonus.h"

void	error_message(int error)
{
	if (error == 1)
		printf("Argument error!\n");
	if (error == 2)
		printf("Memory error!\n");
	if (error == 3)
		printf("Time error!\n");
	if (error == 4)
		printf("Mutex error!\n");
	if (error == 5)
		printf("Pthread error!\n");
	if (error == 0)
		printf("Error!\n");
	exit (1);
}

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (ft_prog(argc, argv))
		return (1);
	init_all(&arg, argv);
	launcher(&arg);
}
