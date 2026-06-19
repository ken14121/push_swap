/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kentarou1412 <kentarou1412@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:42:53 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/19 12:02:56 by kentarou141      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack *s)
{
	t_node	*node;

	if (!s || s->size < 2)
		return ;
	node = s->head;
	s->head = node->next;
	s->head->prev = NULL;
	node->next = NULL;
	node->prev = s->tail;
	s->tail->next = node;
	s->tail = node;
}

void	ra(t_stack *a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

void	rb(t_stack *b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}
