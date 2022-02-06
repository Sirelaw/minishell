/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:32:09 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/06 22:53:28 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <libft.h>

void	wildcard(char **str);
void	insert_findings(char **str, t_list *findings);
t_list	*find_entrys(char *wildcard_str);

#endif
