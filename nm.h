/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 16:34:31 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 23:25:30 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <libft.h>
# include <fcntl.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include "list.h"

# define TXT "__TEXT"
# define TUT "__text"

void		ft_nm(char *ptr, char *name);
int			func_error();
t_things	*add_things(t_things *thing, struct nlist_64 list,\
						char *strtable, t_lsection *sec);
t_things	*del_things(t_things *thing);
t_lsection	*get_section(struct load_command *cmd, struct mach_header_64 *mo);
char		secto(t_lsection *sec, unsigned int n_sect);
t_offlist	*add_off(t_offlist *lst, uint32_t off, uint32_t strx);

void		aff_things(t_things *thing);
void		browse_ar(t_offlist *lst, char *ptr, char *name);

int			catch_size(char *name);
char		*catch_name(char *name);
uint32_t	swap_uint32(uint32_t val);

void		go_fat(char *ptr);
void		go_archive(char *ptr, char *name);
char		typing(uint32_t type, uint32_t n_sect, t_lsection *sec, int addr);

void		print_res(long unsigned int addr, unsigned int size, char *ptr);
void		check_64(struct load_command *com, struct mach_header_64 *mo);
void		ft_otool(void *mem, char *file);
void		browse_art(t_offlist *lst, char *ptr, char *name);
t_offlist	*add_offt(t_offlist *lst, uint32_t off, uint32_t strx);
void		browse_cmd(struct load_command *com, struct mach_header_64 *mo);

#endif
