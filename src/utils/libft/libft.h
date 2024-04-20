/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosra <yosra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:34:01 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/05 20:26:48 by yosra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strcmp(char *s1, char *s2);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t elements_count, size_t element_size);
void	ft_free(char **splited);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_is_space(char c);
char	*ft_itoa(int n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
