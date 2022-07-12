#include "minishell.h"

int ft_nbr_args(char **cmd_test)
{
    int i;
    int nbr_args;

    i = 1;
    nbr_args = 0;
    while (cmd_test[i])
    {
        i++;
        nbr_args++;
    }
    return (nbr_args);
}

char    **ft_malloc_env(char **original)
{
    int i;
    char **sorted;

    i = 0;
    while (original[i])
        i++;
    sorted = malloc((i + 1) *sizeof(char *));
    sorted[i] = NULL;
    return (sorted);
}

char    **ft_malloc_var(char **original)
{
    int i;
    char **sorted;

    i = 1;
    while (original[i])
        i++;
    sorted = malloc(i *sizeof(char *));
    sorted[i - 1] = NULL;
    return (sorted);
}

void    ft_sort_alpha(char **sorted)
{
    int k;
    int j;
    char *tmp;

    k = 0;
    j = 0;
    while (sorted[k])
    {
        j = 0;
        while (sorted[j])
        {
            if (ft_strcmp(sorted[k], sorted[j]) < 0)
            {
                tmp = ft_strdup(sorted[k]);
                free(sorted[k]);
                sorted[k] = ft_strdup(sorted[j]);
                free(sorted[j]);
                sorted[j] = ft_strdup(tmp);
                free(tmp);
            }
            j++;
        }
        k++;
    }
}

void    ft_printf_all(char **sorted)
{
    int i;

    i = 0;
    while (sorted[i])
    {
        printf("declare -x %s\n", sorted[i]);
        i++;
    }  
}