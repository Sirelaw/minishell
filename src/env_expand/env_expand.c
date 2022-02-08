/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:38:37 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/08 00:41:34 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*env_expand(char **envp, char *var)
{
	int		i;
	int		var_len;
	char	*var_expanded;

	if ((envp == NULL) || (var == NULL) || (*var == '\0') || (*var != '$'))
		return ("");
	if (var[1] == '\0')
		return ("$");
	var_len = ft_strlen(var) - 1;
	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], (var + 1), var_len)
			|| (!(envp[i][var_len] == '='))))
		i++;
	if (envp[i] == NULL)
		return ("");
	var_expanded = &(envp[i][var_len + 1]);
	return (var_expanded);
}
