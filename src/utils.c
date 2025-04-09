/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:35 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/09 11:50:51 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

t_stack_node	*find_highest(t_stack_node *stack)
{
	t_stack_node	*highest;

	if (!stack)
		return (NULL);
	highest = stack;
	while (stack->next)
	{
		if (stack->next->data > highest->data)
			highest = stack->next;
		stack = stack->next;
	}
	return (highest);
}

t_stack_node	*find_smallest(t_stack_node *stack)
{
	long			smallest;
	t_stack_node	*smallest_node;

	if (!stack)
		return (NULL);
	smallest = LONG_MAX;
	while (stack)
	{
		if (stack->data < smallest)
		{
			smallest = stack->data;
			smallest_node = stack;
		}
		stack = stack->next;
	}
	return (smallest_node);
}

t_stack_node	*find_last_node(t_stack_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_stack_node	*get_chepeast(t_stack_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

int	nbr_duplicated(t_stack_node *stack, int nbr)
{
	if (!stack)
		return (0);
	while (stack)
	{
		if (stack->data == nbr)
			return (1);
		stack = stack->next;
	}
	return (0);
}
