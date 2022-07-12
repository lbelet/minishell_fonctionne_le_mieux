#include "minishell.h"

int ft_echo(char **cmd_test, char **args_in)
{
    int i;
    int j;
    int k;
    char *cmp;
    char **dollar;

    j = 0;
    k = 0;    
    if (ft_strncmp(cmd_test[1], "-n", 2) == 0 && !cmd_test[1][2])
    {
        i = 2;
        while (cmd_test[i] && cmd_test[i + 1])
        {
            printf("%s ", cmd_test[i]);
            i++;
        }
        printf("%s", cmd_test[i]);
    }
    else
    {
        i = 1;
        if (cmd_test[i][j] == '$')
        {
            j++;
            while (cmd_test[i][j])
            {
               j++;
            }
            if (j == 1)
                return (EXIT_FAILURE);
            cmp = ft_substr(cmd_test[i], 1, j - 1);
            while (&(args_in[k]))
            {
                if (ft_strncmp(cmp, args_in[k], ft_strlen(cmp)) == 0)
                {
                    dollar =  ft_split(args_in[k], '=');
                    printf("%s\n", dollar[1]);
                    free(dollar);
                    free(cmp);
                    return (EXIT_SUCCESS);
                }
                k++;
                free(cmp);
            }
            return (EXIT_FAILURE);
        }
        while (cmd_test[i] && cmd_test[i + 1])
        {
            printf("%s ", cmd_test[i]);
            i++;
        }
        printf("%s\n", cmd_test[i]);
    }
    return (EXIT_SUCCESS);
}

int ft_echo_fd(int fd_out, char **cmd_test)
{
    int i;

    if (ft_strncmp(cmd_test[1], "-n", 2) == 0 && !cmd_test[1][2])
    {
        i = 2;
        while (cmd_test[i] && cmd_test[i + 1])
        {
            printf("%s ", cmd_test[i]);
            i++;
        }
        printf("%s", cmd_test[i]);
    }
    else
    {
        i = 1;
        while (cmd_test[i] && cmd_test[i + 1])
        {
            write(fd_out, cmd_test[i], ft_strlen(cmd_test[i]));
            write(fd_out, " ", 1);
            i++;
        }
        write(fd_out, cmd_test[i], ft_strlen(cmd_test[i]));
        write(fd_out, "\n", 1);
    }
    return (0);
}