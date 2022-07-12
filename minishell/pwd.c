#include "minishell.h"

int    ft_pwd(void)
{
    char    *cwd;

    cwd = NULL;
    cwd = getcwd(cwd, 0);
    if (cwd == NULL)
    {
        perror("Error");
        return (EXIT_FAILURE);
    }
    else
        printf("%s\n", cwd);
    return (EXIT_SUCCESS);
}