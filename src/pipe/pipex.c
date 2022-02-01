/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 22:25:05 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/01 10:44:59 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_input(int argc, char **argv, char **envp, t_input *input)
{
	if ((argc > 1) && (!ft_strcmp(argv[1], "here_doc")))
	{
		if (argc <= 4)
			write(1, "./pipex here_doc LIMITER cmd1 ... cmdn outfile\n", 47);
		if ((argc <= 4) || (here_doc(argc, argv, envp, input)))
			return (1);
		else
			return (0);
	}
	if (argc <= 3)
	{
		write(1, "*****************************************\n", 42);
		write(1, "*  Enter the required set of arguments. *\n", 42);
		write(1, "*Input should have the following format.*\n", 42);
		write(1, "* ./pipex infile cmd1 ... cmdn outfile  *\n", 42);
		write(1, "*****************************************\n", 42);
		return (1);
	}
	if (access(argv[1], F_OK))
	{
		perror(argv[1]);
		return (1);
	}
	return (0);
}

static void	struct_init(int argc, char **argv, char **envp, t_input *input)
{
	input->infile = argv[1];
	input->outfile = argv[argc - 1];
	input->cmdcount = argc - 3;
	input->cmds = &(argv[2]);
	input->envp = envp;
	input->mcmds = NULL;
	input->mpath = NULL;
}

static int	check_for_files(char **argv, t_input *input)
{
	(input->fd)[0][0] = open(input->infile, O_RDONLY);
	if ((((input->fd)[0][0]) < 0) && (!ft_strcmp(argv[1], "here_doc")))
	{
		perror(input->infile);
		exit(EXIT_FAILURE);
	}
	if (!ft_strcmp(argv[0], "here_doc"))
	{
		ft_putstr_fd("here_doc >>\n", 1);
		(input->fd)[0][1] = open(input->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	else
		(input->fd)[0][1] = open(input->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (((input->fd)[0][1]) < 0)
	{
		perror(input->outfile);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	do_init(int argc, char **argv, char **envp, t_input *input)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (1);
	input->path = ft_split(&(envp[i][5]), ':');
	if ((input->path) == NULL)
		return (1);
	struct_init(argc, argv, envp, input);
	if (pipe((input->fd)[1]) == -1)
		return (1);
	if (pipe((input->fd)[2]) == -1)
		return (1);
	check_for_files(argv, input);
	return (0);
}

int	pipex(int argc, char **argv, char **envp)
{
	t_input	input;

	errno = 0;
	if (check_input(argc, argv, envp, &input))
		exit (EXIT_FAILURE);
	if (!ft_strcmp(argv[1], "here_doc"))
		exit (EXIT_SUCCESS);
	if (do_init(argc, argv, envp, &input))
		exit (EXIT_FAILURE);
	if (check_cmds(&input))
		exit (EXIT_FAILURE);
	if (exec_cmds(&input))
		exit (EXIT_FAILURE);
	ft_free(&input);
	exit (EXIT_SUCCESS);
}
