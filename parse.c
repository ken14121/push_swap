/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:42:59 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:44:28 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	has_duplicate(t_stack *a, int value)
{
	t_node	*cur;

	cur = a->head;
	while (cur)
	{
		if (cur->value == value)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static void	parse_token(char *token, t_stack *a)
{
	long	value;

	if (!is_valid_number(token))
		error_exit(a, NULL);
	value = ft_atol(token);
	if (value < INT_MIN || value > INT_MAX)
		error_exit(a, NULL);
	if (has_duplicate(a, (int)value))
		error_exit(a, NULL);
	add_back(a, (int)value);
	if (!a->tail)
		error_exit(a, NULL);
}

static void	parse_one_arg(char *arg, t_stack *a)
{
	char	**split;
	int		i;

	split = ft_split(arg, ' ');
	if (!split || !split[0])
	{
		free_matrix(split);
		error_exit(a, NULL);
	}
	i = 0;
	while (split[i])
	{
		parse_token(split[i], a);
		i++;
	}
	free_matrix(split);
}

void	parse_args(int argc, char **argv, t_stack *a)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		parse_one_arg(argv[i], a);
		i++;
	}
}
