#include "minishell.h"

void ft_export_basic(char **envp, char **envp_sorted, char **args)
{
    int i;

    i = 0;
    while (envp[i])
    {
        envp_sorted[i] = ft_strdup(envp[i]);
        i++;
    }
    ft_sort_alpha(envp_sorted);
    ft_printf_all(envp_sorted);
    if (args)
    {
        ft_sort_alpha(args);
        ft_printf_all(args);
    }
}

void ft_export_new_args(char **cmd_test, char **new_args)
{
    int i;

    i = 0;
    while (i < ft_nbr_args(cmd_test))
    {
        new_args[i] = ft_strdup(cmd_test[i + 1]);
        i++;
    }
}

void ft_sort_new_args(char **new_args, char **args)
{
    int i;

    i = 0;
    ft_sort_alpha(new_args);
    while (new_args[i])
    {
        args[i] = ft_strdup(new_args[i]);
        i++;
    }
}

void ft_total_args(char **tmp, char **args, char ** cmd_test)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (tmp[i])
    {
        args[i] = ft_strdup(tmp[i]);
        i++;
    }
    while (j < ft_nbr_args(cmd_test))
    {
        args[i + j] = ft_strdup(cmd_test[j + 1]);
        j++;
    }
}

char **ft_sort_args(char **args, char **cmd_test)
{
    int i;
    int j;
    char **tmp;

    i = 0;
    j = 0;
    tmp = ft_malloc_env(args);
    while (args[i])
    {
        tmp[i] = ft_strdup(args[i]);
        i++;
    }
    ft_free_tab_simple(args);
    args = malloc((i + ft_nbr_args(cmd_test) + 1) * sizeof(char *));
    args[i + ft_nbr_args(cmd_test) + 1] = NULL;
    ft_total_args(tmp, args, cmd_test);
    return(args);
}

char    **ft_export(char **cmd_test, char **envp, char **args)
{
    char **envp_sorted;
    char **new_args;

    envp_sorted = ft_malloc_env(envp);
    if (!envp_sorted)
        return NULL;
    if (ft_nbr_args(cmd_test) == 0)
    {
        ft_export_basic(envp, envp_sorted, args);
    }
    if (ft_nbr_args(cmd_test) > 0)
    {
        new_args = ft_malloc_var(cmd_test);
        if (!new_args)
            return NULL;
        ft_export_new_args(cmd_test, new_args);
        if (!args)
        {
            args = ft_malloc_env(new_args);
            ft_sort_new_args(new_args, args);
        }
        else if (args[0])
            args = ft_sort_args(args, cmd_test);
    }
    return (args);
}