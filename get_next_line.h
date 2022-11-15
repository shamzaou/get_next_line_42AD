#ifndef GNL_GET_NEXT_LINE_H
#define GNL_GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

typedef struct  gnl_list
{
    char            *content;
    struct  gnl_list  *next;
}               t_gnl;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char    *get_next_line(int fd);
void    read_file(int fd, t_gnl **stash);
int     nl_found(t_gnl *stash);
void    stash_it(t_gnl **stash, char *buff, int readed);
void    line_it(char **line, t_gnl *stash);
void    malloc_line(char **line, t_gnl *stash);
t_gnl	*ft_lst_get_last(t_gnl *stash);
void	ft_broomstick(t_gnl **stash);
void	free_stash(t_gnl *stash);
int	    ft_strlen(const char *str);



#endif //GNL_GET_NEXT_LINE_H