/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:08:39 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 22:46:19 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		errors(void)
{
	ft_putendl_fd("Error", 2);
	return (-1);
}

void			browse_cmd(struct load_command *com, struct mach_header_64 *mo)
{
	unsigned int		i;

	i = 0;
	while (i < mo->ncmds)
	{
		if (com->cmd == LC_SEGMENT_64)
			check_64(com, mo);
		com += com->cmdsize / sizeof(void *);
		i++;
	}
}

static int		if_forest(int i, char **av)
{
	t_stat		stat;
	void		*mem;
	int			fd;

	if ((fd = open(av[i], O_RDONLY)) == -1)
		fd = errors();
	if (fd != -1 && (fstat(fd, &stat) == -1))
		fd = errors();
	if (fd != -1 &&
			!(mem = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
		fd = errors();
	if (fd != -1)
		ft_otool(mem, av[i]);
	if (fd != -1 && munmap(mem, stat.st_size) < 0)
	{
		fd = errors();
		return (0);
	}
	return (1);
}

int				main(int ac, char **av)
{
	int		i;

	if (ac < 2)
		ft_printf("bad argument\n");
	i = 1;
	while (i < ac)
	{
		ft_printf("\n%s:\n", av[i]);
		if (!if_forest(i, av))
			break ;
		i++;
	}
	return (0);
}
