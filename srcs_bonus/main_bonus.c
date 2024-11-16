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

/*
// debug function to print the command
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
t_err	*init(void)
{
	t_err	*err;

	err = ft_calloc(sizeof(t_err), 1);
	if (!err)
		exit(1);
	err->cmd_index = 0;
	err->fd[0] = -1;
	err->fd[1] = -1;
	err->previous_fd = -1;
	err->cmd_nb = 0;
	err->cmds = NULL;
	return (err);
}
//main a recouper pour les 25 lignes !!
int	main(int argc, char **argv, char **env)
{
	int		id;
	t_err	*err;
	int		i;

	if (!env[0])
		env = NULL;
	if (argc < 5)
		return (1);
	err = init();
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		heredoc_exec(argv, env, err);
		return (0);
	}
	check_access(argv[1], argv[argc - 1], err);
	err->cmds = get_cmds(argv, argc, err, 2);
	i = 2;
	err->cmd_nb = argc - 4;
	while (i <= argc - 2)
	{
		err->cmd_index = i - 2;
		error_exit(pipe(err->fd), -1, error_msg(err, "pipe failed "), err);
		id = fork();
		error_exit(id, -1, error_msg(err, "fork failed "), err);
		if (id == 0)
			child_process(err, argv[1], argv[argc - 1], env);
		close(err->fd[1]);
		if (err->cmd_index > 1)
			close(err->previous_fd);
		err->previous_fd = err->fd[0];
		i++;
	}
	free_close(err);
	return (waiting(id));
}