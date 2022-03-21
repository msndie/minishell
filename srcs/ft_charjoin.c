/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:17:39 by jkieth            #+#    #+#             */
/*   Updated: 2022/03/08 15:19:55 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_charjoin(char *s1, char symbol)
{
	char	*dest;
	int		i;

	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i++] = symbol;
	dest[i] = '\0';
	free(s1);
	return (dest);
}
