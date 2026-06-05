/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:43:03 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:43:04 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node			*head;
	t_node			*tail;
	int				size;
}					t_stack;

void				init_stack(t_stack *stack);
void				error_exit(t_stack *a, t_stack *b);
void				free_stack(t_stack *stack);
int					is_sorted(t_stack *stack);
size_t				ft_strlen(const char *s);
long				ft_atol(const char *str);
char				**ft_split(char const *s, char c);
void				free_matrix(char **matrix);
void				parse_args(int argc, char **argv, t_stack *a);
t_node				*create_new_node(int value);
void				add_back(t_stack *stack, int value);
void				assign_indices(t_stack *stack);
void				sa(t_stack *a);
void				sb(t_stack *b);
void				ss(t_stack *a, t_stack *b);
void				pa(t_stack *a, t_stack *b);
void				pb(t_stack *a, t_stack *b);
void				ra(t_stack *a);
void				rb(t_stack *b);
void				rr(t_stack *a, t_stack *b);
void				rra(t_stack *a);
void				rrb(t_stack *b);
void				rrr(t_stack *a, t_stack *b);
void				sort_stack(t_stack *a, t_stack *b);
void				radix_sort(t_stack *a, t_stack *b);

#endif
