/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:42:46 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:44:23 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_top(t_stack *dst, t_stack *src)
{
	t_node	*node;

	if (!src || src->size == 0)
		return ;
	node = src->head;
	src->head = node->next;
	if (src->head)
		src->head->prev = NULL;
	else
		src->tail = NULL;
	src->size--;
	node->next = dst->head;
	node->prev = NULL;
	if (dst->head)
		dst->head->prev = node;
	else
		dst->tail = node;
	dst->head = node;
	dst->size++;
}

void	pa(t_stack *a, t_stack *b)
{
	push_top(a, b);
	write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	push_top(b, a);
	write(1, "pb\n", 3);
}
