#include "minishell.h"

int ft_check_builtins(char **cmd)
{
    if (ft_strncmp(cmd[0], "echo", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "exit", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "env", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "cd", 2) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "export", 6) == 0)
        return (1);
    else if (ft_strncmp(cmd[0], "unset", 5) == 0)
        return (1);
    return (0);
}

void    ft_execute_inbuilt(char **cmd_test, char **envp)
{
    static char **args_in = NULL;

    if ((ft_strncmp(cmd_test[0], "echo", 4)) == 0)
        ft_echo(&(cmd_test[0]), args_in);
    if (ft_strncmp(cmd_test[0], "export", 6) == 0)
         args_in = ft_export(cmd_test, envp, args_in);
    if (strncmp(cmd_test[0], "env", 3) == 0)
        ft_env(envp, &(args_in[0]));
    if (ft_strncmp(cmd_test[0], "cd", 2) == 0)
        ft_cd(cmd_test, envp);
    if (ft_strncmp(cmd_test[0], "unset", 5) == 0)
        ft_unset(cmd_test, &(args_in[0]));
    if (ft_strncmp(cmd_test[0], "pwd", 3) == 0)
        ft_pwd();
    if ((ft_strncmp(cmd_test[0], "exit", 4)) == 0)
        ft_exit(&(cmd_test[0]));
}

int ft_execute_inbuilt_fd(int fd_out, char **cmd_test)
{
    if ((ft_strncmp(cmd_test[0], "echo", 4)) == 0)
    {
        ft_echo_fd(fd_out, cmd_test);
        return (1);
    }
    /*
    if (ft_strcmp(cmd[0], "export") == 0)
        return (export(cmd));
    if (strncmp(cmd[0], "env", 3) == 0)
    {
        env(&(cmd[0]));
        return (0);
    }
    if (ft_strcmp(cmd[0], "cd") == 0)
        return (cd(cmd));
    if (ft_strcmp(cmd[0], "unset") == 0)
        return (unset(cmd));
    if (ft_strcmp(cmd[0], "pwd") == 0)
        return (pwd());
    if (ft_strcmp(cmd[0], "exit") == 0)
        return (exit_inbuilt(cmd));
     */
   return (0);
}