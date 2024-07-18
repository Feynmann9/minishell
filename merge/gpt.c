
#include "minishell.h"

int ft_execution(t_infos *infos)
{
	int fd[2];
	int pid1;
	int pid2;
	char *path_env;
	char *full_path = NULL;
	char **strs;
	char *path_env2;
	char *full_path2 = NULL;
	char **strs2;

	if (infos->envp == NULL || infos == NULL)
		return (1);
	if (pipe(fd) == -1)
		return (1);

	pid1 = fork();
	if (pid1 < 0)
		return (1);

	strs = NULL;
	if (pid1 == 0)
	{
		if (infos->tok->infile)
		{
			while (infos->tok->infile->NEXT)
				infos->tok->infile = infos->tok->infile->NEXT;
			int infile_fd = open(infos->tok->infile->file, O_RDONLY);
			if (infile_fd < 0)
				exit(EXIT_FAILURE);
			if (dup2(infile_fd, STDIN_FILENO) < 0)
				exit(EXIT_FAILURE);
			close(infile_fd);
		}

		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		path_env = get_env_value(infos->tmp_env, "PATH");
		if (!path_env)
			ft_quit(infos, "Error: no env path\n", 2);
		full_path = find_command(infos->tok->cmd[0], path_env);
		if (!full_path)
			ft_quit(infos, "Error: no full path\n", 2);
		strs = ft_str(strs, infos->tok->cmd);
		execve(full_path, strs, infos->envp);
		exit(EXIT_FAILURE);
	}

	pid2 = fork();
	if (pid2 < 0)
		return (1);

	strs2 = NULL;
	if (pid2 == 0)
	{
		if (infos->tok->NEXT)
			infos->tok = infos->tok->NEXT;
		if (infos->tok->outfile)
		{
			while (infos->tok->outfile->NEXT)
				infos->tok->outfile = infos->tok->outfile->NEXT;
			int outfile_fd;
			if (infos->tok->outfile->type == TOKEN_REDIRECT_OUT)
				outfile_fd = open(infos->tok->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (infos->tok->outfile->type == TOKEN_REDIRECT_APPEND)
				outfile_fd = open(infos->tok->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (outfile_fd < 0)
				exit(EXIT_FAILURE);
			if (dup2(outfile_fd, STDOUT_FILENO) < 0)
				exit(EXIT_FAILURE);
			close(outfile_fd);
		}

		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		path_env2 = get_env_value(infos->tmp_env, "PATH");
		if (!path_env2)
			ft_quit(infos, "Error: no env path 2\n", 2);
		full_path2 = find_command(infos->tok->cmd[0], path_env2);
		if (!full_path2)
			ft_quit(infos, "Error: no full path 2\n", 2);
		strs2 = ft_str(strs2, infos->tok->cmd);
		execve(full_path2, strs2, infos->envp);
		exit(EXIT_FAILURE);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}
