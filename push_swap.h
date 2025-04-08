/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:08:07 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/08 12:50:10 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_stack_node
{
	int					data;
	int					index;
	int					price;
	int					above_median;
	int					cheapest;
	struct s_stack_node	*target_node;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}				t_stack_node;

char			**ft_split(char *str, char separator);

void			stack_init(t_stack_node **stack, char **av, int splited);
void			init_nodes(t_stack_node *a, t_stack_node *b);
void			set_position(t_stack_node *stack);

void			append_node(t_stack_node **stack, int nbr);
void			set_price(t_stack_node *a, t_stack_node *b);
void			set_target_node(t_stack_node *a, t_stack_node *b);
int				nbr_duplicated(t_stack_node *stack, int nbr);
int				stack_sorted(t_stack_node *stack);
int				stack_len(t_stack_node *stack);
t_stack_node	*find_highest(t_stack_node *stack);
t_stack_node	*find_smallest(t_stack_node *stack);
t_stack_node	*find_last_node(t_stack_node *head);
t_stack_node	*get_chepeast(t_stack_node *stack);
void			single_rotate(t_stack_node **stack,
					t_stack_node *node,
					int rotate_a);

int				error_syntax(char *str_nbr);
void			error_free(t_stack_node **a, char **argv, int splited);
void			free_split(char **av);
void			free_stack(t_stack_node **stack);

void			sa(t_stack_node **a);
void			sb(t_stack_node **b);
void			ss(t_stack_node **a, t_stack_node **b);

void			ra(t_stack_node **a);
void			rb(t_stack_node **b);
void			rr(t_stack_node **a, t_stack_node **b);

void			pa(t_stack_node **a, t_stack_node **b);
void			pb(t_stack_node **b, t_stack_node **a);

void			rra(t_stack_node **a);
void			rrb(t_stack_node **a);
void			rrr(t_stack_node **a, t_stack_node **b);

void			simple_sort(t_stack_node **stack);
void			sort_five(t_stack_node **a, t_stack_node **b);
void			push_swap(t_stack_node **a, t_stack_node **b);

#endif
