/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:38:37 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/25 17:46:57 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*cat_s1_s2(char *s1, char *s2)
{
	size_t	len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = (char *)malloc(len);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, s1, len);
	ft_strlcat(str, s2, len);
	free(s1);
	free(s2);
	return (str);
}

char	*env_expand(char **envp, char *var)
{
	int		i;
	int		var_len;
	char	*var_expanded;

	if ((envp == NULL) || (var == NULL) || (*var == '\0') || (*var != '$'))
		return (ft_strdup(""));
	if (var[1] == '\0')
		return (ft_strdup("$"));
	if (!ft_strcmp("$?", var))
		return (ft_itoa(g_shell_env.last_exit_code));
	i = 0;
	var_len = 0;
	while (var[++i] && var[i] != '$')
		var_len++;
	var_expanded = env_expand(envp, &(var[i]));
	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], (var + 1), var_len)
			|| (!(envp[i][var_len] == '='))))
		i++;
	if (envp[i] == NULL)
		return (cat_s1_s2(ft_strdup(""), var_expanded));
	return (cat_s1_s2(ft_strdup(&(envp[i][var_len + 1])), var_expanded));
}
