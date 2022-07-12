#include "minishell.h"

void  ft_process_onlyone(char *path_cmd, char **cmd, char **envp)
{
  execve(path_cmd, cmd, envp);
}

void  ft_process_onlyone_output(int fd_out, char *path_cmd, char **cmd, char **envp)
{
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execve(path_cmd, cmd, envp);
}

void	ft_check_quote_simple(char *tab)
{
	int code_quote;
	int j;
	int k;
	char temp[50] = {0};

	j = 0;
	code_quote = 0;
	k = 0;
	while (tab[j])
	{
        if ((tab[j] == 34 || tab[j] == 39) && code_quote == 0)
       	    code_quote = ft_subopen_code_caractere(tab, j);
       	else if ((tab[j] == 34 && code_quote == 1) || (tab[j] == 39 && code_quote == 3))
           	code_quote = 0;
		else if ((code_quote == 0) || (code_quote == 1 && tab[j] != 34) ||
           	    (code_quote == 3 && tab[j] != 39))
			temp[k++] = tab[j];
		j++;
	}
	temp[k] = '\0';
	free(tab);
    tab = ft_strdup(temp);
}

char	*ft_strjoin_modif(char const *s1, char const s2)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dst = malloc(ft_strlen(s1) + 2);
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	if (!s1)
	{
		dst[0] = s2;
		dst[1] = '\0';
	}
	else
	{
		dst[i + 1] = s2;
		dst[i + 2] = '\0';
	}
	return (dst);
}

char *ft_set_cmd(char **cmd, int *j, int i, int *code_caractere)
{
	int start;
	int len;
	char *tmp;
	char *commande;

	start = *j;
	len = 0;
	while (((cmd[i][*j] != '<' && cmd[i][*j] != '>') || code_caractere[*j] != 6) && cmd[i][*j])
	{	
		len++;
		*j = *j + 1;
	}
	tmp = ft_substr(cmd[i], start, len);
	commande = ft_strdup(tmp);
	free(tmp);
	return (commande);
}

char *ft_set_file(char **cmd, int *j, int i)
{
	int start;
	int len;
	char *tmp;
	char *infile;

	if (cmd[i][*j + 1] != '<' && cmd[i][*j + 1])
	{
		*j = *j + 1;
		start = *j;
		len = 0;
		while (cmd[i][*j] != '<' && cmd[i][*j] != '>' && cmd[i][*j])
		{	
			len++;
			*j = *j + 1;
		}
		tmp = ft_substr(cmd[i], start, len);
		infile = ft_strdup(tmp);
		free(tmp);
		return (infile);
	}
	return (NULL);
}

void ft_error_fd(int fd, char *infile)
{
	if (fd < 0)
		printf("Probleme d'access au fichier: %s\n", infile);
}

void ft_infile_nosplit(char **cmd, int *fd, int *j, int i)
{
	char *infile;

	if (fd[0] != 0)
		close(fd[0]);
	infile = ft_set_file(cmd, j, i);
	ft_check_quote_simple(infile);
	fd[0] = open(infile, O_RDONLY);
	ft_error_fd(fd[0], infile);
	*j += (ft_strlen(infile) + 1);
	free (infile);
}

void ft_infile_split(char **cmd, int *fd, int *i)
{
	char *infile;

	if (fd[0] != 0)
		close(fd[0]);
	*i = *i + 1;
	infile = ft_strdup(cmd[*i]);
	ft_check_quote_simple(infile);
	fd[0] = open(infile, O_RDONLY);
	ft_error_fd(fd[0], infile);
	free (infile);
}

void ft_outfile_split(char **cmd, int *fd, int *i)
{
	char *outfile;

	if (fd[1] != 0)
		close(fd[1]);
	*i = *i + 1;
	outfile = ft_strdup(cmd[*i]);
	ft_check_quote_simple(outfile);
	fd[1] = open(outfile, O_WRONLY | O_CREAT, 0777);
	ft_error_fd(fd[1], outfile);
	free (outfile);
}

void ft_outfile_nosplit(char **cmd, int *fd, int i, int *j)
{
	char *outfile;

	if (fd[1] != 0)
		close(fd[1]);
	outfile = ft_set_file(cmd, j, i);
	ft_check_quote_simple(outfile);
	fd[1] = open(outfile, O_WRONLY | O_CREAT, 0777);
	ft_error_fd(fd[1], outfile);
	*j += (ft_strlen(outfile) + 1);
	free (outfile);
}

void ft_files(char **cmd, int *fd, int *j, int *i)
{
	if (cmd[*i][*j] == '<')
	{
		if (cmd[*i][*j + 1] != '<' && cmd[*i][*j + 1])
			ft_infile_nosplit(cmd, fd, j, *i);
		else if (cmd[*i][*j + 1] != '<' && !cmd[*i][*j + 1] && cmd[*i + 1])
			ft_infile_split(cmd, fd, i);
	}
	if (cmd[*i][*j] == '>')
	{
		if (cmd[*i][*j + 1] != '>' && cmd[*i][*j + 1])
			ft_outfile_nosplit(cmd, fd, *i, j);
		else if (cmd[*i][*j + 1] != '>' && !cmd[*i][*j + 1] && cmd[*i + 1])
			ft_outfile_split(cmd, fd, i);
	}
}

void ft_check_redir(int *fd, char **cmd, char **commande)
{
	int *caractere;
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	while (cmd[i])
	{	
		caractere = ft_code_caractere(cmd[i]);
		j = 0;
		while (cmd[i][j])
		{
			if (((cmd[i][j] != '<' && cmd[i][j] != '>') || caractere[j] != 6) && cmd[i][j])
			{
				commande[k] = ft_set_cmd(cmd, &j, i, caractere);
				ft_check_quote(commande, k);
				k++;
			}
			if ((cmd[i][j] == '<' || cmd[i][j] == '>') && caractere[j] == 6)
			{
				ft_files(cmd, fd, &j, &i);
				break;
			}
			j++;	
		}
		free(caractere);
		i++;
	}
}


void	ft_free_tab_simple(char **tab)
{
	int	i;
	int n;

	n =0;
	i = 0;
	while (tab[n])
		n++;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_error(char *path_cmd, char **cmd_infile)
{
	if (path_cmd[0] == 'E')
	{
		printf("Command %s not found\n", cmd_infile[0]);
		ft_free_tab_simple(cmd_infile);
		return (0);
	}
	else
		return (1);
}

int ft_process_one_classic(char **cmd, char **envp)
{
	int pid;
	char *path_cmd;

	path_cmd = ft_path(cmd[0]);
	if (ft_error(path_cmd, cmd) == 0)
		return (0);
   	pid = fork();
    if (pid < 0)
       	return (0);
   	if (pid == 0)
        ft_process_onlyone(path_cmd, cmd, envp);
   	waitpid(pid, NULL, 0);
	free(path_cmd);
	return (0);
}

void ft_exec_in_out(int *fd, char **commande, char **envp)
{
	char *path;
	int pid;

	path = ft_path(commande[0]);
	if (ft_error(path, commande) == 0)
		return;
	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path, commande, envp);
	}
	ft_free_tab_simple(commande);
	free(path);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return;
}

void ft_exec_in(int fd_in, char **commande, char **envp)
{
	char *path;
	int pid;

	path = ft_path(commande[0]);
	if (ft_error(path, commande) == 0)
		return;
	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		execve(path, commande, envp);
	}
	ft_free_tab_simple(commande);
	free(path);
	close(fd_in);
	waitpid(pid, NULL, 0);
	return;
}

void ft_exec_out(int fd_out, char **commande, char **envp)
{
	char *path;
	int pid;

	path = ft_path(commande[0]);
	if (ft_error(path, commande) == 0)
		return;
	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		execve(path, commande, envp);
	}
	ft_free_tab_simple(commande);
	free(path);
	close(fd_out);
	waitpid(pid, NULL, 0);
	return;
}


void ft_one(char **split_pipe, char **envp)
{
	char **cmd;
	int *fd;
	char **commande;

	fd = malloc(2 * sizeof(int));
	fd[0] = 0;
	fd[1] = 0;
    cmd = ft_split_modif(split_pipe[0], ' ', ft_code_caractere(split_pipe[0]));
	ft_execute_inbuilt(cmd, envp);
	if (ft_check_builtins(cmd) == 0)
	{
		commande = ft_malloc_env(cmd);
		ft_check_redir(fd, cmd, commande);
		if (fd[0] > 0 && fd[1] > 0)
			ft_exec_in_out(fd, commande, envp);
		else if (fd[0] > 0 && fd[1] == 0)
			ft_exec_in(fd[0], commande, envp);
		else if (fd[0] == 0 && fd[1] > 0)
			ft_exec_out(fd[1], commande, envp);
		else if (fd[0] == 0 && fd[1] == 0)
			ft_process_one_classic(commande, envp);
		ft_free_tab_simple(cmd);
		free(fd);
	}
}