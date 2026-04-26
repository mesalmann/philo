#include "philo.h"

int main(int ac, char **av)
{
	t_table	table;

	if(!(ac == 5 || ac == 6))
		error_exit("Wrong input!\n");
	if (!is_arg_valid(av))
        error_exit("Invalid argument\n");
	parse_arg(&table, av);
	data_init(&table);
	dinner_start(&table);
	clean(&table); 	
}
