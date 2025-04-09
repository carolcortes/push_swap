/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:49:38 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/09 11:50:51 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	move_nodes(t_stack_node **a, t_stack_node **b);
void	rotate_stacks(t_stack_node **a,
			t_stack_node **b,
			t_stack_node *cheapest);
void	reverse_rotate_stacks(t_stack_node **a,
			t_stack_node **b,
			t_stack_node *cheapest);
void	single_rotate(t_stack_node **stack, t_stack_node *node, int rotate_a);

void	push_swap(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*smallest;
	int				len_a;

	len_a = stack_len(*a);
	if (len_a == 5)
		sort_five(a, b);
	else
	{
		while (len_a-- > 3)
			pb(b, a);
	}
	simple_sort(a);
	while (*b)
	{
		init_nodes(*a, *b);
		move_nodes(a, b);
	}
	set_position(*a);
	smallest = find_smallest(*a);
	if (smallest->above_median)
		while (*a != smallest)
			ra(a);
	else
		while (*a != smallest)
			rra(a);
}

void	move_nodes(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*cheapest;

	cheapest = get_chepeast(*b);
	if (cheapest->above_median && cheapest->target_node->above_median)
		rotate_stacks(a, b, cheapest);
	else if (!(cheapest->above_median)
		&& !(cheapest->target_node->above_median))
		reverse_rotate_stacks(a, b, cheapest);
	single_rotate(b, cheapest, 0);
	single_rotate(a, cheapest->target_node, 1);
	pa(a, b);
}

void	rotate_stacks(t_stack_node **a,
			t_stack_node **b,
			t_stack_node *cheapest)
{
	while (*a != cheapest->target_node && *b != cheapest)
		rr(a, b);
	set_position(*a);
	set_position(*b);
}

void	reverse_rotate_stacks(t_stack_node **a,
			t_stack_node **b,
			t_stack_node *cheapest)
{
	while (*a != cheapest->target_node && *b != cheapest)
		rrr(a, b);
	set_position(*a);
	set_position(*b);
}

void	single_rotate(t_stack_node **stack, t_stack_node *node, int rotate_a)
{
	while (*stack != node)
	{
		if (rotate_a)
		{
			if (node->above_median)
				ra(stack);
			else
				rra(stack);
		}
		else
		{
			if (node->above_median)
				rb(stack);
			else
				rrb(stack);
		}
	}
}
