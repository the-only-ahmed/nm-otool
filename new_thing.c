/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_thing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/26 19:43:14 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 21:24:48 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_things	*add_before(t_things *yolo, t_things *to_add)
{
	t_things	*ret;

	ret = NULL;
	if (yolo->prev == NULL)
	{
		yolo->prev = to_add;
		to_add->next = yolo;
		ret = to_add;
	}
	else
	{
		to_add->next = yolo;
		to_add->prev = yolo->prev;
		yolo->prev->next = to_add;
		yolo->prev = to_add;
	}
	return (ret);
}

void		add_tail(t_things *yolo, t_things *to_add)
{
	to_add->prev = yolo;
	yolo->next = to_add;
}

t_things	*new_thing(struct nlist_64 list, char *strtable, t_lsection *sec)
{
	t_things	*tmp;

	tmp = (t_things*)malloc(sizeof(t_things));
	tmp->value = list.n_value;
	tmp->type = typing(list.n_type, list.n_sect, sec, list.n_value);
	tmp->str = ft_strdup(strtable + list.n_un.n_strx);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_things	*add_things(t_things *thing,\
					struct nlist_64 list, char *strtable, t_lsection *sec)
{
	t_things	*bws_word;
	t_things	*tmp;
	t_things	*ret;

	tmp = new_thing(list, strtable, sec);
	if (thing == NULL)
		return (tmp);
	bws_word = thing;
	while (bws_word)
	{
		if (ft_strcmp(bws_word->str, tmp->str) > 0)
		{
			ret = add_before(bws_word, tmp);
			if (ret)
				thing = ret;
			break ;
		}
		else if (bws_word->next == NULL)
		{
			add_tail(bws_word, tmp);
			break ;
		}
		bws_word = bws_word->next;
	}
	return (thing);
}
