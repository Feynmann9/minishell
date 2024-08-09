/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpp <jpp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/09 18:22:52 by jpp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    for_all_builtin(t_infos *infos)
{
    if (infos->tok->cmd[0] && infos->tok->cmd[1] == NULL)
    {
        if (ft_strcmp(infos->tok->cmd[0], "pwd") == 0)
            ft_pwd(infos);
        else if (ft_strcmp(infos->tok->cmd[0], "cd") == 0)
            ft_cd(infos, NULL);
        else if (ft_strcmp(infos->tok->cmd[0], "env") == 0)
            ft_env(infos);
        else if (ft_strcmp(infos->tok->cmd[0], "exit") == 0)
            ft_jedois_exit(infos);
        else if (ft_strcmp(infos->tok->cmd[0], "export") == 0)
        {
            ft_order_env(infos);
            ft_print_order(infos);
        }
    }
    else if(infos->tok->cmd[0])
    {
        if (ft_strcmp(infos->tok->cmd[0], "echo") == 0)
            ft_echo(infos->tok->cmd);
        else if (ft_strcmp(infos->tok->cmd[0], "export") == 0)
            ft_export(infos, infos->tok->cmd[1]);
        else if (ft_strcmp(infos->tok->cmd[0], "unset") == 0)
            ft_unset(infos, infos->tok->cmd[1]);
        else if (ft_strcmp(infos->tok->cmd[0], "cd") == 0)
            ft_cd(infos, infos->tok->cmd[1]);
    }
}

int is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0 ||
            ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "unset") == 0);
}

// Fonction pour exécuter une commande avec redirections et pipes
void handle_redirections(t_infos *infos)
{
    int **pipes;
    int i;
    int pid;
    char *path_env;
    char *full_path = NULL;
    t_tok *current_tok;

    if (infos->envp == NULL || infos == NULL)
        return;

    // allocation pour le nombre de pipes quil y a
    // le pipe connecte les deux parties seulement si besoin (cat < Makefile > out | echo mathieu)
    // mais echo n a pas d entree de cat, car ca le fou dans out
    // Pipe (|) : Relie deux programmes pour que la sortie du premier devienne l'entrée du second
    // Redirection (>, <) : Change où les données vont (vers ou depuis un fichier)
    pipes = malloc(sizeof(int *) * infos->count_pipes);
    i = 0;
    while (i < infos->count_pipes)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1)
            return ;
        i++;
    }
    //pipes[i][0] : Descripteur de lecture.
    //pipes[i][1] : Descripteur d'écriture.
    current_tok = infos->tok;
    i = 0;
    while (i <= infos->count_pipes)
    {
        // creation processus pour chaque commande dans la chaine de pipes
        pid = fork();
        if (pid < 0)
            return;
        if (pid == 0)
        {
            // Gestion des redirections d'entrée
            if (current_tok->infile)
            {
                //Configurer le programme pour lire depuis un fichier au lieu du clavier.
                t_files *infile = current_tok->infile;
                while (infile->NEXT) // Trouver le dernier fichier dans la liste
                    infile = infile->NEXT;
                //Utiliser la fonction open() pour ouvrir le fichier en mode lecture
                int fd_in = open(infile->file, O_RDONLY);
                if (fd_in < 0)
                    exit(EXIT_FAILURE);
                //Utiliser dup2() pour rediriger l’entrée standard (stdin) vers le fichier ouvert.
                if (dup2(fd_in, STDIN_FILENO) < 0)
                    exit(EXIT_FAILURE);
                close(fd_in);
            }

            // Gestion des redirections de sortie
            if (current_tok->outfile)
            {
                t_files *outfile = current_tok->outfile;
                while (outfile->NEXT)
                    outfile = outfile->NEXT;
                int fd_out;
                if (outfile->type == TOKEN_REDIRECT_OUT)
                    fd_out = open(outfile->file, O_CREAT | O_WRONLY | O_TRUNC, 0666); // Créer ou écraser le fichier
                else if (outfile->type == TOKEN_REDIRECT_APPEND)
                    fd_out = open(outfile->file, O_CREAT | O_WRONLY | O_APPEND, 0666); // Ajouter au fichier existant
                if (fd_out < 0)
                    exit(EXIT_FAILURE);
                if (dup2(fd_out, STDOUT_FILENO) < 0) // Rediriger stdout vers le fichier
                    exit(EXIT_FAILURE);
                close(fd_out);
            }
            // Gestion des pipes
            if (i > 0)
            {
                //Si nous ne sommes pas à la première commande
                close(pipes[i - 1][1]); // Fermer l'extrémité d'écriture du pipe précédent
                //Nous redirigeons l'entrée standard (stdin) vers l'extrémité de lecture du tuyau précédent.
                if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
                    exit(EXIT_FAILURE);
                close(pipes[i - 1][0]);
            }
            //la sortie du premier devient l entree du prochain
            if (i < infos->count_pipes && current_tok->outfile == 0)
            {
                close(pipes[i][0]); // Fermer l'extrémité de lecture du pipe actuel
                //Cela signifie que tout ce que la commande(1er) écrit sera envoyé au tuyau.
                //en gros on dit que la sortie de la commande sera envoye au pipe
                if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
                    exit(EXIT_FAILURE);
                close(pipes[i][1]);
            }
            // Fermeture des descripteurs de fichiers inutilisés dans les processus enfants
            // cette une sorte de securite
            int j = 0;
            while (j < infos->count_pipes)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }

            //if (is_builtin(current_tok->cmd[0]))
            //{
            //    for_all_builtin(infos);
            //    exit(EXIT_SUCCESS);  // Terminer l'enfant après l'exécution du builtin
            //}
            // Exécution de la commande
            path_env = get_env_value(infos->tmp_env, "PATH");
            if (!path_env)
                exit(EXIT_FAILURE);
            full_path = find_command(infos, current_tok->cmd[0], path_env);
            //printf("exec = %s\n", full_path);
            if (!full_path)
            {
                for_all_builtin(infos);
                exit(EXIT_FAILURE);
            }
            execve(full_path, current_tok->cmd, infos->envp);
            exit(EXIT_FAILURE);
            //exit(EXIT_SUCCESS);
        }
        current_tok = current_tok->NEXT;
        i++;
    }

    // Fermeture des descripteurs de fichiers inutilisés dans le processus parent
    i = 0;
    while (i < infos->count_pipes)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }

    // Attente de tous les processus enfants se terminent
    i = 0;
    while (i <= infos->count_pipes)
    {
        wait(NULL);
        i++;
    }
    // Libération de la mémoire allouée pour les pipes
    i = 0;
    while (i < infos->count_pipes)
        free(pipes[i++]);
    free(pipes);
}
