#include "minishell.h"

int ft_env(char **envp, char **args_in)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    if (args_in)
    {
        while (args_in[j])
        {
            printf("%s\n", args_in[j]);
            j++;
        }
    }  
    return (0);
}