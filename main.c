#include "philo.h"

int	main(int ac, char **av)
{
	t_program	program;

	if (ac != 5 && ac != 6)
		error_exit("Wrong input!");
	if (!is_arg_valid(av))
		error_exit("Invalid argument");
	parse_arg(&program, av);
	data_init(&program);
	start_dinner(&program);
	clean(&program);
	return (0);
}