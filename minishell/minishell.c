#include "minishell.h"

void ft_exec_cmd(char *str, char **envp)
{
	int *code_caractere;
	char **split_pipe;
	int nbr_cmd;

	nbr_cmd = 0;
	code_caractere = ft_code_caractere(str);
    split_pipe = ft_split_modif(str, '|', ft_code_caractere(str), 0);
    while (split_pipe[nbr_cmd])
    	nbr_cmd++;
    if (nbr_cmd == 1)
        ft_one(split_pipe, envp);         
    if (nbr_cmd >= 2)
        ft_pipex_multi(split_pipe, nbr_cmd, envp);
	ft_free_tab_simple(split_pipe);
}

void ft_cpy_tab(char **original, char **copy)
{
    int i;

    i = 0;
    while (original[i])
    {
        copy[i] = ft_strdup(original[i]);
        i++;        
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *str;
    char **envp_copy;

    envp_copy = ft_malloc_env(envp);
    ft_cpy_tab(envp, envp_copy);
    while (42)
    {
        define_input_signals();
        str = readline("prompt> ");
        if (str == NULL)//CTRL+D
            break;
        add_history(str);
		ft_exec_cmd(str, envp_copy);
		free(str);      
    }
    ft_free_tab_simple(envp_copy);
    return (0);
}