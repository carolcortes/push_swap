/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:57:23 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/09 16:25:46 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

long			ft_atol(char *str);
void			set_position(t_stack_node *stack);
void			set_cheapest(t_stack_node *stack);

void	stack_init(t_stack_node **stack, char **av, int splited)
{
	long	nbr;
	int		i;

	i = 0;
	while (av[i])
	{
		if (error_syntax(av[i]))
			error_free(stack, av, splited);
		nbr = ft_atol(av[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			error_free(stack, av, splited);
		if (nbr_duplicated(*stack, (int)nbr))
			error_free(stack, av, splited);
		append_node(stack, (int)nbr);
		i++;
	}
	if (splited)
		free_split(av);
}

void	init_nodes(t_stack_node *a, t_stack_node *b)
{
	set_position(a);
	set_position(b);
	set_target_node(a, b);
	set_price(a, b);
	set_cheapest(b);
}

void	set_cheapest(t_stack_node *stack)
{
	long			value;
	t_stack_node	*node;

	if (!stack)
		return ;
	value = LONG_MAX;
	while (stack)
	{
		stack->cheapest = 0;
		if (stack->price < value)
		{
			value = stack->price;
			node = stack;
		}
		stack = stack->next;
	}
	node->cheapest = 1;
}

void	set_position(t_stack_node *stack)
{
	int	i;
	int	middle;

	if (!stack)
		return ;
	i = 0;
	middle = stack_len(stack) / 2;
	while (stack)
	{
		stack->index = i;
		if (i <= middle)
			stack->above_median = 1;
		else
			stack->above_median = 0;
		stack = stack->next;
		i++;
	}
}

long	ft_atol(char *str)
{
	long	n;
	int		s;
	int		i;

	n = 0;
	s = 1;
	i = -1;
	while (str[++i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	return (n * s);
}
