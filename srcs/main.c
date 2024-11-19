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

#include "libft.h"
#include "../includes/pipex.h"

t_err	*init(void)
{
	t_err	*err;

	err = ft_calloc(sizeof(t_err), 1);
	if (!err)
		exit(1);
	err->fd = ft_calloc(sizeof(int), 2);
	if (!err->fd)
		exit(1);
	err->fd[0] = 0;
	err->fd[1] = 0;
	err->cmds = NULL;
	return (err);
}

int	main(int argc, char **argv, char **env)
{
	int		id;
	int		id2;
	t_err	*err;

	if (!env[0])
		env = NULL;
	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		return (1);
	}
	err = init();
	err->cmds = get_cmds(argv, argc, err);
	check_access(argv[1], argv[argc - 1], err);
	error_exit(pipe(err->fd), -1, "pipe : ", err);
	id = fork();
	error_exit(id, -1, "first fork : ", err);
	if (id == 0)
		first_child(err, argv[1], env);
	id2 = fork();
	error_exit(id, -1, "second fork : ", err);
	if (id2 == 0)
		sec_child(err, argv[argc - 1], env);
	free_close(err);
	return (waiting(id, id2));
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