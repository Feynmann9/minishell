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
