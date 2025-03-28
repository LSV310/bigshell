/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:54:10 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 16:31:56 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <termios.h>
# include <signal.h>
# include <stdbool.h>
# include <dirent.h>

// Bases
# define BASE_10 "0123456789"
# define BASE_16L "0123456789abcdef"
# define BASE_16U "0123456789ABCDEF"

// Readline keys
# define READ_FAILED -1
# define FINISH_READING -2
# define INVALID_SEQ -3
# define ESC 27
# define EOF_K 4
# define UARROW -12
# define DARROW -13
# define RARROW -14
# define LARROW -15
# define HOME -16
# define END -17
# define DEL -18
# define CR_ARROW -19
# define CL_ARROW -20
# define DEL_K 127

// libc functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strrcmp(const char *s1, const char *s2);
int		ft_strrncmp(const char *s1, const char *s2, int n);
int		ft_str_equals(const char *s1, const char *s2);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strlstr(const char *big, const char *little, size_t len);
int		ft_strstr_tab(char **tab, char *str);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *old_ptr, size_t size, size_t old_size);
char	*ft_strdup(const char *s);

// additional functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	*free_tab(char **tab, int nb);
int		count_words(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_ltoa(long n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	tab_len(char **tab);
void	shift_elem_up(char **tab, char *elem);
void	shift_elem_down(char **tab, char *elem);

// maths
double	q_rsqrt(double number);
int		max(int a, int b);
int		min(int a, int b);

// printf
int		ft_printf(const char *s, ...);
int		ft_fprintf(int fd, const char *s, ...);
int		ft_putchar_len_fd(int c, int fd);
int		ft_putstr_len_fd(char *s, int fd);
int		ft_putnbr_base_fd(unsigned int n, char *base, int base_len, int fd);
int		ft_putnbr_base_len_fd(int n, char *base, int base_len, int fd);
int		ft_putnbr_double_fd(double n, int accuracy, int fd);
int		ft_printptr_fd(unsigned long long ptr, int fd);
int		ft_putnbr_long_fd(long n, int fd);

// linked lists
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	free_content(void *content);
void	void_content(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	lst_remove_node(t_list **lst, t_list *node, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstprint(t_list *lst);
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstfirst(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
void	ft_dlst_top(t_dlist **lst);
void	ft_dlstdelone(t_dlist *lst, void (*del)(void*));
void	ft_dlstclear(t_dlist **lst, void (*del)(void*));
void	dlst_remove_node(t_dlist **lst, t_dlist *node, void (*del)(void*));
void	ft_dlst_shift_up(t_dlist **lst, t_dlist *node);
void	ft_dlst_shift_down(t_dlist **lst, t_dlist *node);
t_dlist	*ft_strstr_dlst(t_dlist *lst, char *str);
void	ft_dlstprint(t_dlist *lst);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// maps
typedef struct s_map
{
	char			*key;
	char			*value;
	struct s_map	*next;
}	t_map;

t_map	*newmap(char *key, char *value);
t_map	*ft_maplast(t_map *map);
void	ft_addmap(t_map **map, t_map *new);
void	ft_mapclear(t_map **map);
void	map_remove_node(t_map **map, t_map *node);
size_t	ft_mapsize(t_map *map);

// readline
typedef enum rl_quit_reason
{
	RL_INVALID,
	RL_SUCCESS,
	RL_FINISHED,
	RL_KILLED
}	t_rlqreason;

typedef struct s_rline
{
	char	*current_line;
	size_t	size;
	size_t	cursor;
	size_t	end;
	DIR		*cwd;
	bool	in_auto;
}	t_rline;

typedef struct s_readline
{
	char		*prompt;
	t_dlist		**history;
	bool		sigint_nl;
	bool		autocomplete;
	t_rlqreason	quit_reason;
}	t_readline;

char	*ft_readline(t_readline *params);
void	init_readline_params(t_readline *params);
int		new_buffer(t_rline *line, t_readline *params);
int		rl_signal_received(int key, t_rline *line, t_readline *params);
void	clear_line(t_rline *line, t_dlist **history, bool free_current);
void	set_raw(void);
void	set_dfl(void);
int		read_key(void);
int		reset_line(t_rline *line);
void	write_x_times(char *buff, char c, size_t times);
int		printkey(int key, t_rline *line, t_readline *params);
int		eof_received(t_rline *line, t_readline *params);
void	back_space(t_rline *line);
int		other_key(int key, t_rline *line, t_readline *params);
int		up_arrow(t_rline *line, t_dlist **history);
int		down_arrow(t_rline *line, t_dlist **history);
void	home_key(t_rline *line);
void	end_key(t_rline *line);
void	move_key(t_rline *line, int key);
void	move_word(t_rline *line, int key);
char	*history_up(t_dlist **history);
char	*history_down(t_dlist **history);
int		cmd_add_history(t_dlist **history, char *cmd);
int		auto_complete(int key, t_rline *line);
void	rl_init_signals(void);
void	rl_reset_signals(void);

// signals
void	init_sighandler(struct sigaction *sa, void (*action)(int));
void	init_sigaction(struct sigaction *sa,
			void (*action)(int, siginfo_t *, void *));

// readfile
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

#endif
