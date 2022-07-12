#include "minishell.h"

void ft_unset(char **cmd_test, char **args_in)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!cmd_test[1])
        return;
    while (args_in[j])
        j++;
    while (args_in[i])
    {
        if (ft_strncmp(args_in[i], cmd_test[1], ft_strlen(cmd_test[1])) != 0)
            i++;
        else
        {
            args_in[i] = ft_strdup("zzzzzz");
            ft_sort_alpha(args_in);
            args_in[j - 1] = NULL;
            return ;
        }
    }
    return ;
}