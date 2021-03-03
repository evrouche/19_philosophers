#include "include/philo_three.h"

int init_semaphore(t_data *three)
{
	sem_unlink("fork");
    sem_unlink("global");
    sem_unlink("dead");
    three->dead = sem_open("dead", O_CREAT, 0660, 1);
    if (three->dead == SEM_FAILED)
	    return (-1);
    three->global = sem_open("global", O_CREAT, 0660, 1);
    if (three->global == SEM_FAILED)
		return (-1);
    three->fork = sem_open("fork", O_CREAT, 0660, three->number_of_philo);
    if (three->dead == SEM_FAILED)
		return (-1);
    return (1); 
}

int     creat_frok(t_data *three)
{
    int     i;

    i = 0;
    if (init_semaphore(three) < 0)
        return (-1);
    while (i < three->number_of_philo)
    {
        three->pid[i] = fork();
        three->name[i] = i + 1;
        if (three->pid[i] == 0)
        {
            pthread_create(&three->check_dead, NULL, &check_time, NULL);
            routine(three, i);
            
            // kill(three->pid[i], )
        }
        i++;
    }
    return (0);
}

int     main(int argc, char **argv)
{
    t_data      three;

	init_struct(&three);
	if (fill_struct(&three, argc, argv))
		return (-1);
    *static_struct() = &three;
    if (creat_frok(&three) < 0)
        return (-1);
    return (0);
}