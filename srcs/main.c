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

//Only the main here

#include "pipex.h"
#include "libft.h"

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

int	main(int argc, char **argv, char **env)
{
	char	***cmds;
	int		id;
	//int		id2;
	int		fd[2];
	int		status;
	//int		status2;
	//THIS IS PARSING
	if (argc != 5) //for bonus only check that it is >= 5
	{
		printf("Nb of arg is not 4\n");
		return (1);
	}
	check_access(argv[1], argv[argc - 1]); //always first and last one
	cmds = get_cmds(argv, argc);
	print_cmd(cmds); //only for debug
	//THIS IS PIPE, for bonus I need first, middle child (loop) and last child
	pipe(fd);
	id = fork();
	if (id == 0) //first child
	{
		printf("first born\n");
		first_child(fd, cmds[0], argv[1], env); //make cmds dynamique in Bonus
	}
	waitpid(id, &status, 0); //voir de plus pret comment utiliser waitpid at some point
	printf("stauts 1 is %d\n", status);
	if (id != 0)
		printf("parent stoped waiting\n");
	/*
	id2 = fork(); //using the same id bcs first child is dead when the second one is born
	if (id2 == 0) //second child
	{
		printf("second born\n");
		sec_child(fd, cmds[1], argv[argc - 1], env);
	}
	waitpid(id2, &status2, 0); //change into waitpid
	printf("stauts 2 is %d\n", status2);
		if (id != 0)
		printf("parent stoped waiting again\n");
	*/
	if (id != 0)
		free_close(fd, cmds);
	return (0);
}

