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

//Main + helper functions

#include "../includes/libft.h"
#include "../includes_bonus/pipex_bonus.h"

t_err	*init(void)
{
	t_err	*err;

	err = ft_calloc(sizeof(t_err), 1);
	if (!err)
		exit(1);
	err->heredoc = 0;
	err->cmd_index = 0;
	err->fd[0] = -1;
	err->fd[1] = -1;
	err->previous_fd = -1;
	err->cmd_nb = 0;
	err->cmds = NULL;
	return (err);
}

int	main(int argc, char **argv, char **env)
{
	t_err	*err;
	int		id;
	
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
	id = children_generator(argv, env, argc, err);
	free_close(err);
	return (waiting(id));
}

int	children_generator(char **argv, char **env, int argc, t_err *err)
{
	int	i;
	int	id;
	int	stop;

	i = 2;
	err->cmd_nb = argc - 4;
	if (err->heredoc)
		stop = argc - 3;
	else
		stop = argc - 2;
	while (i <= stop)
	{
		err->cmd_index = i - 2;
		error_exit(pipe(err->fd), -1, error_msg(err, "pipe failed "), err);
		id = fork();
		printf("%d\n", id);
		error_exit(id, -1, error_msg(err, "fork failed "), err);
		if (id == 0 && !err->heredoc)
			child_process(err, argv[1], argv[argc - 1], env);
		else if (id == 0 && err->heredoc)
			heredoc_child_process(err, argv[argc - 1], env);
		err->cmd_index = 1;
		close(err->fd[1]);
		if (err->cmd_index > 1)
			close(err->previous_fd);
		err->previous_fd = err->fd[0];
		i++;
	}
	return (id);
}