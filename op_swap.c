/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:42:56 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:44:26 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_top(t_stack *s)
{
	t_node	*first;
	t_node	*second;

	if (!s || s->size < 2)
		return ;
	first = s->head;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	s->head = second;
	if (s->tail == second)
		s->tail = first;
}

void	sa(t_stack *a)
{
	swap_top(a);
	write(1, "sa\n", 3);
}

void	sb(t_stack *b)
{
	swap_top(b);
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
	swap_top(a);
	swap_top(b);
	write(1, "ss\n", 3);
}
