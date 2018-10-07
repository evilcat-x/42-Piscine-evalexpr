/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 02:50:46 by seli              #+#    #+#             */
/*   Updated: 2018/10/07 03:51:11 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int		eval_expr(char *str)
{
	int		result;
	char	*padded;

	padded = ft_strpad(str);
	ft_eval_replace(padded);
	result = ft_atoi(padded);
	free(padded);
	return (result);
}

int		ft_str_last_left(char *str)
{
	int i;
	int len;

	len = ft_strlen(str);
	i = len - 1;
	while (i >= 0 && str[i] != '(')
		i--;
	return (i >= 0 ? i : NO_MATCH);
}

void	ft_eval_simple(char *str)
{
	int	i;
	int	match;

	i = 0;
	match = 1;
	if (str[i] == '(')
	{
		str[i] = ' ';
		while (str[i] != ')')
			i++;
		str[i] = ' ';
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '*' || str[i] == '/' || str[i] == '%')
			ft_eval_op(&str[i], ft_ctot(str[i]));
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' || (str[i] == '-' && ft_is_neg_sign(str, i)))
			ft_eval_op(&str[i], ft_ctot(str[i]));
	}
}

void	ft_eval_op(char *str, t_ops operation)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (str[i] == ' ')
		i--;
	while (str[i] != ' ')
		i--;
	x = ft_atoi(&str[i]);
	i += (str[i] == ' ');
	y = ft_atoi(&str[1]);
	ft_strclear(&str[i]);
	ft_strnbr(&str[i], operation(x, y));
}

void	ft_eval_replace(char *str)
{
	int	next_left;

	next_left = 0;
	while ((next_left = ft_str_last_left(str)) != NO_MATCH)
	{
		ft_eval_simple(&str[next_left]);
	}
	ft_eval_simple(str);
}
