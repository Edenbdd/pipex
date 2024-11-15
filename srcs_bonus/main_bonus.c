/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:46:07 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 09:10:12 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Only the main here

#include "../includes/libft.h"
#include "../includes_bonus/pipex_bonus.h"

t_err	*init(void)
{
	t_err	*err;

	err = ft_calloc(sizeof(t_err), 1);
	if (!err)
		exit(1);
	err->position = 0;
	err->fd = ft_calloc(sizeof(int), 2);
	if (!err->fd)
		exit(1);
	err->fd[0] = 0;
	err->fd[1] = 0;
	err->cmds = NULL;
	return (err);
}
//main a recouper pour les 25 lignes !!
int	main(int argc, char **argv, char **env)
{
	int		id_first;
	int		id_middle;
	int		id_last;
	t_err	*err;
	int		i;

	if (!env[0])
		env = NULL;
	if (argc < 5)
		return (1);
	err = init();
	err->cmds = get_cmds(argv, argc, err);
	check_access(argv[1], argv[argc - 1], err); //still the same except for here_doc
	error_exit(pipe(err->fd), -1, error_msg(err, "pipe"), err);
	//first child (handle infile)
	id_first = fork();
	error_exit(id_first, -1, error_msg(err,"first fork"), err);
	if (id_first == 0)
		first_child(err, argv[1], env);
	//middle children
	i = 3;
	while (i < argc - 2)
	{
		//creer un pipe dans la boucle ???
		err->position = i - 1; //need to start from second cmd
		id_middle = fork();
		error_exit(id_middle, -1, error_msg(err, "middle fork"), err);
		if (id_middle == 0)
			middle_child(err, argv[i], env, i);
		i++;
	}
	//last child (handle outfile)
	id_last = fork();
	error_exit(id_last, -1, error_msg(err, "lastfork"), err);
	if (id_last == 0)
		last_child(err, argv[argc - 1], env);
	//cleaning and closing the code
	free_close(err); //check que je free tout correctement meme avec une loop de children
	return (waiting(id_last));
}

/* debug function to print the command
static void	print_cmd(char ***cmds) //just for debug, delete/command at the end
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		j= 0;
		while (cmds[i][j])
		{
			printf("%s;", cmds[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
*/