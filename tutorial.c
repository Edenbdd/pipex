/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:46:07 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/07 17:55:33 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **env)
{
	(void)argc,
	(void)argv;
	(void)env;
	int	id;
	int	n;
	int	i;

	id = fork();
	printf("%d\n", id);
	if (id == 0)
		n = 1;
	if (id != 0)
	{
		n = 6;
		wait(NULL);
	}
	i = n;
	while (i < n + 5)
	{
		printf("%d\n", i);
		i++;
	}
	return (0);
}