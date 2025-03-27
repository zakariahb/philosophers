/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouis-j <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:35:19 by alouis-j          #+#    #+#             */
/*   Updated: 2023/02/07 13:11:25 by alouis-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

/* --- Check Functions --- */

int		ft_isext(char *file, char *ext);
int		ft_isblank(char c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_areblank(char *str, int len);
int		ft_arealnum(char *str, int len);
int		ft_arealpha(char *str, int len);
int		ft_areascii(char *str, int len);
int		ft_aredigit(char *str, int len);
int		ft_areprint(char *str, int len);

/* --- Memory Functions --- */

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_free_arr(void **array);

/* --- String Functions --- */

int		ft_strlen(const char *s);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_array_size(char **array_str);
int		ft_atoi(const char *nptr);
int		ft_erratoi(const char *nptr, int *err);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_add_space(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoinf(char *s1, char *s2);
char	*ft_strtok(char *str, const char *delim);
int64_t	ft_erratoll(const char *nptr, int *err);
int64_t	ft_atoll(const char *nptr);

/* --- Write Functions --- */

int		ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_puthex_fd(unsigned long n, int lowcase, int cnt, int fd);
int		ft_putnbr_fd(long n, int cnt, int fd);
int		ft_putptr_fd(unsigned long ptr, int fd);
int		ft_putstr_fd(char *str, int fd);
int		ft_dprintf(int fd, const char *fmt, ...);

/* --- Linked Lists Functions --- */

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *newlst);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *newlst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* --- Input Functions --- */

char	*get_next_line(int fd);
#endif
