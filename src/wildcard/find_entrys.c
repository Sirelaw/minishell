/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:12:41 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/06 20:25:48 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wildcard.h>

static int	matches_wildcard(char *str, char *wildcard_str)
{
	size_t	idx;
	size_t	asterik;

	idx = 0;
	while (wildcard_str[idx])
	{
		asterik = idx;
		while (wildcard_str[asterik] && (wildcard_str[asterik] != '*' \
			|| (wildcard_str[asterik] == '*' && wildcard_str[asterik + 1] == '*')))
			++asterik;
		wildcard_str[asterik] = 0;
		str = ft_strnstr(str, &wildcard_str[idx], ft_strlen(str));
		wildcard_str[asterik] = '*';
		if (!str)
			return (0);
		idx = asterik;
		++idx;
	}
	return (1);
}

t_list	*find_entrys(char *wildcard_str)
{
	t_list			*entrys;
	DIR				*dir;
	struct dirent	*file;
	
	

	entrys = NULL;
	dir = opendir(getcwd(NULL, 0));
	if (!dir)
		return (NULL);
	file = readdir(dir);
	while (file)
	{
		if (matches_wildcard(file->d_name, wildcard_str))
			ft_lstadd_back(&entrys, ft_lstnew(ft_strdup(file->d_name)));
		file = readdir(dir);
	}
	return (entrys);
}
