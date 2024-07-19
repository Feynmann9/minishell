#include "../../minishell.h"

int     ft_jedoistoutfaire(char *str)
{
    int i = 0;
    while(str[i])
    {
        if (!is_digit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

//chat gpt
int get_last_exit_status(const char *history_file) {
    FILE *file = fopen(history_file, "r");
    if (!file) {
        perror("fopen");
        return 1; // Valeur par défaut si le fichier ne peut pas être lu
    }

    int last_exit_status = 0;
    char line[256];

    // Lire le fichier ligne par ligne pour trouver le dernier statut de sortie
    while (fgets(line, sizeof(line), file)) {
        char *status_str = strrchr(line, ' '); // Supposons que le statut de sortie est le dernier élément de la ligne
        if (status_str) {
            last_exit_status = atoi(status_str + 1); // Convertir en entier
        }
    }

    fclose(file);
    return last_exit_status;
}
//

void    ft_jedois_exit(t_infos *infos)
{
    int exot;

    if (infos->tok->cmd[1] != NULL && infos->tok->cmd[2] != NULL)
    {
        ft_printf("Minishell exit: trop d'arguments\n");
        return ;
    }
    if (infos->tok->cmd[1] != NULL && ft_jedoistoutfaire(infos->tok->cmd[1]))
    {
        //printf("cmd 1 = %s\n", infos->tok->cmd[1]);
        exot = ft_atoi(infos->tok->cmd[1]);
        exot = exot % 255;
        //printf("exot = %d\n", exot);
    }
    else if (infos->tok->cmd[1] != NULL)
    {
        ft_printf("Minishell exit; argument numerique necessaire\n");
        exot = 2;
    }
    else
        exot = get_last_exit_status(infos->history_file);
    exit(exot);    
} 