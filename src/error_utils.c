/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:14:16 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/09 16:32:52 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	free_split(char **av)
{
	int	i;

	i = 0;
	if (!av || !*av)
		return ;
	while (av[i])
		free(av[i++]);
	free(av[i]);
	free((av - 1)[0]);
	free(av - 1);
}

void	free_stack(t_stack_node **stack)
{
	t_stack_node	*tmp;
	t_stack_node	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

void	error_free(t_stack_node **a, char **argv, int splited)
{
	free_stack(a);
	if (splited)
		free_split(argv);
	write(1, "Error\n", 6);
	exit(1);
}

int	error_syntax(char *str)
{
	if (!(*str == '+' || *str == '-'
			|| (*str >= '0' && *str <= '9')))
		return (1);
	if ((*str == '+' || *str == '-')
		&& !(str[1] >= '0' && str[1] <= '9'))
		return (1);
	while (*++str)
		if (!(*str >= '0' && *str <= '9'))
			return (1);
	return (0);
}
