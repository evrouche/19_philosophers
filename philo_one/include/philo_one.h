#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct      s_philo_one
{
    int             number_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_time;
    pthread_t       *philo;
    pthread_mutex_t *mutex;
    pthread_mutex_t global;
    int             *name;
	long    		*last_eat;
	int 			statut;
    long int        time_start;
}                   t_data;

int     main();
void    init_struct(t_data *one);

/*
** ft_fill_the_struct.c
*/

int     check_digit(int argc, char **argv);
int     fill_struct(t_data *one, int argc, char **argv);
void    init_struct(t_data *one);

/*
** tools.c
*/

void    lock_mutex(t_data *one);
void    unlock_mutex(t_data *one);
void    destroy_mutex(t_data *one);
long    get_time(void);
t_data   **static_struct(void);
int	    ft_isdigit(int c);
int     ft_atoi(const char *str);
void    ft_print_str(t_data *one, long int time, int philo, char *message);
void    ft_print_dead(t_data *one, long int time, int philo);
void    ft_print_fork(t_data *one, long int time, int philo);

void    ft_sleep(int time);


/*
** ft_action.c
*/
void    *routine(void *arg);
void 	*check_time(void *arg);
void 	eating(t_data *one, int i);
void 	sleeping(t_data *one, int i);
void 	thinking(t_data *one, int i);

/*
** ft_libft.c
*/

char	        *ft_strjoin(char const *s1, char const *s2);
char	        *ft_strjoin_free_all(char *s1, char *s2);
char	        *ft_strjoin_free(char *s1, char *s2);
char	        *ft_strdup(const char *s1);
int             ft_atoi(const char *str);
char			*ft_itoa(int n);
int		        ft_isdigit(int c);
size_t		    ft_strlen(const char *s);








#endif
