#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static t_gnl    *stash = NULL;
    char            *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    line = NULL;
    //void func that takes the fd, read through it and each read is a linked list
    read_file(fd, &stash);
    if (!stash)
        return (NULL);
    line_it(&line, stash);

    ft_broomstick(&stash);

    /// A REVOIR !!!!!!!!!!!!!!!!
    if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
    /// WARNING !!!!!!!!!!!!!
    return (line);
}

void    read_file(int fd, t_gnl **stash)
{
    int     readed;
    char    *buff;

    readed = 1; // PUT IT ZERO LATER
    // buff = NULL;
    while (!nl_found(*stash) && readed != 0)
    {
        buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
        if (!buff)
            return ;
        readed = (int)read(fd, buff, BUFFER_SIZE);
        if ((stash == NULL && readed == 0) || readed == -1) // NULL STASH CONDITION, SHOULD IT BE ADDED ????
        {
            free(buff);
            return ;
        }
        buff[readed] = '\0';
        stash_it(stash, buff, readed);
        free(buff);
    }
}

void    stash_it(t_gnl **stash, char *buff, int readed)
{
    int     i;
    t_gnl   *node;
    t_gnl   *last;

    i = 0;
    node = malloc(sizeof(t_gnl));
    if (!node)
        return ;
    node->next = NULL;
    node->content = malloc((readed + 1) * sizeof(char));
    if (!node->content)
        return ;

    while (buff[i] && i < readed)
    {
        node->content[i] = buff[i];
        i++;
    }
    node->content[i] = '\0';
    if(*stash == NULL)
    {
        *stash = node;
        return ;
    }
    last = ft_lst_get_last(*stash);
    last->next = node;
}

void    line_it(char **line, t_gnl *stash)
{
    int     i;
    int     j;

    if (!stash)
        return ;
    malloc_line(line, stash);
    if (*line == NULL)
        return ;
    j = 0;
    while (stash)
    {
        i = 0;
        while (stash->content[i])
        {
            if (stash->content[i] == '\n')
            {
                (*line)[j++] = stash->content[i];
                break;
            }
            (*line)[j++] = stash->content[i++];
        }
        stash = stash->next;
    }
    (*line)[j] = '\0';
}

void    malloc_line(char **line, t_gnl *stash)
{
    int i;
    int len;

    len = 0;
    while (stash)
    {
        i = 0;
        while (stash->content[i])
        {
            if (stash->content[i] == '\n')
            {
                len++;
                break;
            }
            len++;
            i++;
        }
        stash = stash->next;
    }
    *line = malloc((len + 1) * sizeof(char));
}