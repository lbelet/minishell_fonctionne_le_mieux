#include "minishell.h"

void ft_malloc(int **fd_pipe, int *pid, int nbr_cmd)
{
    int i;

    i = 0;
    fd_pipe = malloc((nbr_cmd - 1) * sizeof(int*));
    while (i < nbr_cmd -1)
	{
		fd_pipe[i] = malloc(2 * sizeof(int));
		i++;
	}
    pid = malloc(nbr_cmd * sizeof(int));
}

void ft_free_tab_int(int **fd, int *pid, int nbr_cmd)
{
    int j;

    j = 0;
    free(pid);
	while (j < nbr_cmd - 1)
	{
		free(fd[j]);
		j++;
	}
	free(fd);
}

int ft_pipes(int **fd, int nbr_cmd)
{
    int j;

    j = 0;
	while (j < nbr_cmd - 1)
	{
		if (pipe(fd[j]) == -1)
      		return (1);
		j++;
	}
    return (0);
}

// ======== ft_1er =========================================================

void  ft_process_first_bis(int fd_in, int fd_out, char **cmd, char **envp)
{
    char *path_cmd;

    path_cmd = ft_path(cmd[0]);
//	if (ft_cmd_error(path_cmd, cmd, pid) == 0)
//		return;
    dup2(fd_out, STDOUT_FILENO);
    close(fd_in);
    close(fd_out);
    execve(path_cmd, cmd, envp);
}

void  ft_process_first_bis_in(int fd_in, int fd_out, char **cmd, char **envp)
{
    char *path_cmd;

    path_cmd = ft_path(cmd[0]);
//	if (ft_cmd_error(path_cmd, cmd, pid) == 0)
//		return;
    dup2(fd_out, STDOUT_FILENO);
    dup2(fd_in, STDIN_FILENO);
    close(fd_in);
    close(fd_out);
    execve(path_cmd, cmd, envp);
}

void ft_first_process(char **split_pipe, int *fd_redir, int **fd_pipe, char **envp)
{
    char **commande;
    char **split_space;
    int k;
    int i;

    i = 0;
    k = 0;
    if (i < 1)
    {
        split_space = ft_split_modif(split_pipe[i], ' ', ft_code_caractere(split_pipe[i]), 0);
        commande = ft_malloc_env(split_space);
        ft_check_redir(fd_redir, split_space, commande);
        if (fd_redir[0] > 0 && fd_redir[1] > 0)
        {
            close (fd_pipe[k][0]);
            close (fd_pipe[k][1]);
            ft_process_first_bis_in(fd_redir[0], fd_redir[1], commande, envp);
            fd_redir[0] = 0;
        }
		else if (fd_redir[0] > 0 && fd_redir[1] == 0)
        {
            close(fd_pipe[k][0]);
		    ft_process_first_bis_in(fd_redir[0], fd_pipe[k][1], commande, envp);
            fd_redir[0] = 0;
        }
	    else if (fd_redir[0] == 0 && fd_redir[1] > 0)
        {
            close(fd_pipe[k][1]);
		    ft_process_first_bis(fd_pipe[k][0], fd_redir[1], commande, envp);
        }
		else if (fd_redir[0] == 0 && fd_redir[1] == 0)
		    ft_process_first_bis(fd_pipe[k][0], fd_pipe[k][1], commande, envp);
    }
}

// ======== ft_middle ==========================================================

void  ft_process_middle_bis(int fd_in, int fd_out, char **cmd, char **envp)
{
    char *path_cmd;

    path_cmd = ft_path(cmd[0]);
    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_in);
    close(fd_out);
    execve(path_cmd, cmd, envp);
}

void ft_middle_process(int k, int i, char **split_pipe, int *fd_redir, int **fd_pipe, char **envp)
{
    char **split_space;
    char **commande;

    if (fd_redir[1] > 0)
    {
        fd_redir[0] = fd_redir[1];
        fd_redir[1] = 0;
    }
    split_space = ft_split_modif(split_pipe[i], ' ', ft_code_caractere(split_pipe[i]), 0);
    commande = ft_malloc_env(split_space);
    ft_check_redir(fd_redir, split_space, commande);
    if (fd_redir[0] > 0 && fd_redir[1] > 0)
    {
        close (fd_pipe[k][0]);
        close (fd_pipe[k + 1][1]);
        ft_process_middle_bis(fd_redir[0], fd_redir[1], commande, envp);
        fd_redir[0] = 0;
    }
    else if (fd_redir[0] > 0 && fd_redir[1] == 0)
    {
        close(fd_pipe[k][0]);
        ft_process_middle_bis(fd_redir[0], fd_pipe[k + 1][1], commande, envp);
        fd_redir[0] = 0;
    }
    else if (fd_redir[0] == 0 && fd_redir[1] > 0)
    {
        close(fd_pipe[k + 1][1]);
	    ft_process_middle_bis(fd_pipe[k][0], fd_redir[1], commande, envp);
    }
	else if (fd_redir[0] == 0 && fd_redir[1] == 0)
	    ft_process_middle_bis(fd_pipe[k][0], fd_pipe[k + 1][1], commande, envp);
}

// ========= ft_last ===================================================================

void  ft_process_last(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp)
{
  dup2(fd_in, STDIN_FILENO);
  close(fd_in);
  close(fd_out);
  execve(path_cmd, cmd, envp);
}

void  ft_process_last_out(int fd_in, int fd_out, char *path_cmd, char **cmd, char **envp)
{
  dup2(fd_in, STDIN_FILENO);
  dup2(fd_out, STDOUT_FILENO);
  close(fd_in);
  close(fd_out);
  execve(path_cmd, cmd, envp);
}

void ft_last_process(int k, char **split_pipe, int *fd_redir, int **fd_pipe, char **envp)
{
    char **commande;
    char **split_space;
    char *path_cmd;
    int i;

    if (fd_redir[1] > 0)
    {
        fd_redir[0] = fd_redir[1];
        fd_redir[1] = 0;
    }
    i = ft_nbr_args(split_pipe);
    split_space = ft_split_modif(split_pipe[i], ' ', ft_code_caractere_bis(split_pipe[i]), 0);
    commande = ft_malloc_env(split_space);
    ft_check_redir(fd_redir, split_space, commande);
    path_cmd = ft_path(commande[0]);
//    if (ft_cmd_error(path_cmd, split_space, pid) == 0)
//		return (0);
    if (fd_redir[0] == 0 && fd_redir[1] == 0)
	    ft_process_last(fd_pipe[k][0], fd_pipe[k][1], path_cmd, commande, envp);
    else if (fd_redir[0] > 0 && fd_redir[1] == 0)
    {
        close(fd_pipe[k][0]);
        ft_process_last(fd_redir[0], fd_pipe[k][1], path_cmd, commande, envp);
    }
    else if (fd_redir[0] == 0 && fd_redir[1] > 0)
    {
        close(fd_pipe[k][1]);
	    ft_process_last_out(fd_pipe[k][0], fd_redir[1], path_cmd, commande, envp);
    }
    else if (fd_redir[0] > 0 && fd_redir[1] > 1)
    {
        close(fd_pipe[k][0]);
        close(fd_pipe[k][1]);
        ft_process_last_out(fd_redir[0], fd_redir[1], path_cmd, commande, envp);
    }
}

// ====== ft_close =============================================================

void ft_close_fl(int k, int nbr_cmd, int **fd_pipe)
{
    int j;

    j = 0;
	while (j < nbr_cmd - 1)
	{
	    if ( j != k)
		{
			close(fd_pipe[j][0]);
			close(fd_pipe[j][1]);
		}	
		j++;
	}
}

void ft_close_all(int nbr_cmd, int **fd_pipe)
{
    int j;

    j = 0;
	while (j < nbr_cmd - 1)
	{
    	close(fd_pipe[j][0]);
		close(fd_pipe[j][1]);
		j++;
	}
}

void ft_close_middle(int k, int nbr_cmd, int **fd_pipe)
{
    int j;

	j = 0;
	while (j < nbr_cmd - 1)
	{	
		if (j != k)
			close(fd_pipe[j][0]);
		if ( j != (k + 1))
			close(fd_pipe[j][1]);
		j++;
	}
}

// ====== ft_wait ========================================================

void ft_waitpid_all(int nbr_cmd, int *pid)
{
    int j;

    j = 0;
	while (j < nbr_cmd)
	{
		waitpid(pid[j], NULL, 0);
		j++;
	}
}

// ===== ft_principal =====================================================

int ft_pipex_multi(char **split_pipe, int nbr_cmd, char **envp)
{
    int *pid;
    int **fd_pipe;
    int *fd_redir;
    int i;
    int k;

    k = 0;
    i = 0;
// ++++++++++ malloc +++++++=
    fd_pipe = malloc((nbr_cmd - 1) * sizeof(int*));
    while (i < nbr_cmd -1)
		fd_pipe[i++] = malloc(2 * sizeof(int));
    pid = malloc(nbr_cmd * sizeof(int));
    fd_redir = malloc(2 * sizeof(int));
    fd_redir[0] = 0;
    fd_redir[1] = 0;
// ++++++++ pipes ++++++++
    ft_pipes(fd_pipe, nbr_cmd);
// ++++++++ 1er +++++++++
    i = 0;
    pid[i] = fork();
    if (pid[i] < 0) 
		return (0);
	if (pid[i] == 0)
    {
        ft_close_fl(k, nbr_cmd, fd_pipe);
        ft_first_process(split_pipe, fd_redir, fd_pipe, envp);
    }
    i++;
// +++++++ middle ++++++++
    while (i < nbr_cmd - 1)
    {
        pid[i] = fork();
        if (pid[i] < 0)
			return (0);
		if (pid[i] == 0)
        {
            ft_close_middle(k, nbr_cmd, fd_pipe);
            ft_middle_process(k, i, split_pipe, fd_redir, fd_pipe, envp);
        }  
        i++;
        k++;
    }
// +++++++++ last +++++++++
    if (i < nbr_cmd)
    {
		pid[i] = fork();
		if (pid[i] < 0)
			return (0);
		if (pid[i] == 0)
		{	        
            ft_close_fl(k, nbr_cmd, fd_pipe);
            ft_last_process(k, split_pipe, fd_redir, fd_pipe, envp);
		}
    }
// ++++++ close +++++++++
    ft_close_all(nbr_cmd, fd_pipe);
// +++++++ waitpid ++++++
    ft_waitpid_all(nbr_cmd, pid);
// +++++++ free ++++++++++
    ft_free_tab_int(fd_pipe, pid, nbr_cmd);
    free(fd_redir);
    return (0);
}