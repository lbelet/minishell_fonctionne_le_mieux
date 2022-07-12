#include "minishell.h"

void ft_replace_pwd(char **copy_env, char *cwd, char *cwdbis)
{
    int i;

    i = 0;
    i = 0;
    while (copy_env[i])
    {
        if (ft_strncmp(copy_env[i], "PWD", 3) == 0)
        {
            free(copy_env[i]);
            copy_env[i] = ft_strdup("PWD=");
            copy_env[i] = ft_strjoin(copy_env[i], cwdbis);
        }
        if (ft_strncmp(copy_env[i], "OLDPWD", 6) == 0)
        {
            free(copy_env[i]);
            copy_env[i] = ft_strdup("OLDPWD=");
            copy_env[i] = ft_strjoin(copy_env[i], cwd);
        }
        i++;
    }
}

char **ft_env_copy(char **envp)
{
    int i;
    char **copy_env;

    i = 0;
    while (envp[i])
        i++;
    copy_env = malloc((i + 1) * sizeof(char *));
    i = 0;
    while(envp[i])
    {
        copy_env[i] = ft_strdup(envp[i]);
        i++;
    }
    copy_env[i] = NULL;
    return (copy_env);
}


int ft_cd(char **cmd_test, char **envp)
{
    int i;
    char **copy_env;
    char *cwd;
    char *cwdbis;

    i = 0;
    cwd = NULL;
    cwdbis = NULL;
    copy_env = ft_env_copy(envp);
    cwd = getcwd(cwd, 0);
    if (cmd_test[1])
        chdir(cmd_test[1]);
    else if (!cmd_test[1])
        chdir("/Users/lbelet");
    cwdbis = getcwd(cwdbis, 0);
    ft_replace_pwd(copy_env, cwd, cwdbis);
    i = 0;
    while (copy_env[i])
    {
        envp[i] = ft_strdup(copy_env[i]);
        i++;
    }
    return (0);
}