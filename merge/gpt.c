/*Pour ajouter la gestion des `infile`, `outfile` et `append` dans votre minishell, il faudra modifier plusieurs parties de votre code. Vous allez notamment devoir ouvrir les fichiers et rediriger les entrées/sorties standard avant d'exécuter les commandes.

Voici les étapes pour intégrer cette fonctionnalité dans votre minishell :

### 1. Ajouter les structures nécessaires

Dans votre fichier `minishell.h`, ajoutez les champs nécessaires dans la structure utilisée pour les commandes afin de stocker les informations sur les fichiers d'entrée et de sortie :*/

#include "minishell.h"

typedef enum s_type
{
	TOKEN_COMMAND,
	TOKEN_PIPE,				//	|
	TOKEN_REDIRECT_IN,		//	<
	TOKEN_HEREDOC,			//	<<
	TOKEN_HEREDOC_WORD,		//	heredoc file
	TOKEN_HEREDOC_DELIMITER,//	heredoc delimiter
	TOKEN_REDIRECT_OUT,		//	>
	TOKEN_REDIRECT_APPEND,	//	>>
	TOKEN_QUOTE,			//	''
	TOKEN_D_QUOTE,			//	""
	TOKEN_ENV,				//	$
}					t_type;

typedef struct s_files
{
	int				type;		//	le type du fichier. pour in = < ou <<. pour out = > ou >>
	char			*file;		//	le fichier
	struct s_files	*NEXT;		//	si NEXT != NULL alors il y'a un autre infiles
}			t_files;

typedef struct s_tok
{
	char			**cmd;		//	La liste de comande parser; ls -l == cmd[0] = ls; cmd[1] = -l;
	t_files			*infile;	//	les infiles avec leurs type < <<
	t_files			*outfile;	//	les outfiles avec leurs type > >>
	struct s_tok	*NEXT;		//	si NEXT != NULL alors il y'a un pipe
}			t_tok;

/*### 2. Modifier l'analyse des arguments

Lors de l'analyse des arguments de la ligne de commande, remplissez les champs `infile`, `outfile` et `append` de votre structure `t_command`.

### 3. Gestion des redirections dans `exec.c`

Dans `exec.c`, avant d'exécuter la commande, gérez les redirections. Voici un exemple de comment vous pourriez faire cela :*/

void	handle_redirections(t_tok *tok)
{
	int fd;

	if (tok->infile)
	{
		while (tok->infile->NEXT)
			tok->infile = tok->infile->NEXT;
		fd = open(tok->infile->file, O_RDONLY);
		if (fd < 0)
			exit(EXIT_FAILURE);
		if (dup2(fd, STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(fd);
	}
	else if (tok->outfile)
	{
		while (tok->outfile->NEXT)
			tok->outfile = tok->outfile->NEXT;
		if (tok->outfile->type == TOKEN_REDIRECT_OUT)
			fd = open(tok->outfile->file, O_WRONLY | O_CREAT, 0644);
		if (tok->outfile->type == TOKEN_REDIRECT_APPEND)
			fd = open(tok->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			exit(EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		close(fd);
	}
}

/*### 4. Appeler `handle_redirections` avant l'exécution

Avant d'exécuter la commande, appelez `handle_redirections` avec la structure de commande appropriée.*/

void execute_command(t_command *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_redirections(cmd);
		if (execvp(cmd->cmd, cmd->args) < 0)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

/*### 5. Modification de l'analyse syntaxique

Assurez-vous que votre analyseur syntaxique identifie correctement les redirections (`<`, `>`, `>>`) et remplit les champs `infile`, `outfile`, et `append` de votre structure de commande.

### Exemple d'analyse simple*/

void parse_command(char *input, t_command *cmd)
{
	// Remplir cmd->cmd, cmd->args, cmd->infile, cmd->outfile, cmd->append en analysant l'input
}

/*### Conclusion

Ces modifications devraient permettre à votre minishell de gérer les fichiers d'entrée, de sortie et d'append. Vous pouvez tester ces fonctionnalités en créant des commandes avec différentes combinaisons de redirections.

Si vous avez des questions spécifiques ou besoin d'aide supplémentaire avec des parties spécifiques du code, n'hésitez pas à demander!*/

void handle_redirections(t_infos *infos)
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
		return;
	if (pipe(fd) == -1)
		return;

	pid1 = fork();
	if (pid1 < 0)
		return;

	strs = NULL;
	if (pid1 == 0)
	{
		if (infos->tok->infile)
		{
			while(infos->tok->infile->NEXT)
				infos->tok->infile = infos->tok->infile->NEXT;
			fd[0] = open(infos->tok->infile->file, O_RDONLY);
			if (fd[0] < 0)
				exit(EXIT_FAILURE);
			if (dup2(fd[0], STDIN_FILENO) < 0)
				exit(EXIT_FAILURE);
			close(fd[0]);
		}
		else
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}

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
		return;

	strs2 = NULL;
	if (pid2 == 0)
	{
		if (infos->tok->NEXT)
			infos->tok = infos->tok->NEXT;
		if (infos->tok->outfile)
		{
			while(infos->tok->outfile->NEXT)
				infos->tok->outfile = infos->tok->outfile->NEXT;
			if (infos->tok->outfile->type == TOKEN_REDIRECT_OUT)
				fd[1] = open(infos->tok->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (infos->tok->outfile->type == TOKEN_REDIRECT_APPEND)
				fd[1] = open(infos->tok->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd[1] < 0)
				exit(EXIT_FAILURE);
			if (dup2(fd[1], STDOUT_FILENO) < 0)
				exit(EXIT_FAILURE);
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}

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
}
