#include "get_next_line.h"

int	nl_found(t_gnl *stash)
{
	int		i;
	t_gnl	*current;

	if (stash == NULL)
		return (0);
	current = ft_lst_get_last(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
/*int     nl_found(char *str)
{
    int i;

    i = 0;
    if (str)
    {
        while (str[i])
        {
            if (str[i] == '\n' || str[i] == '\0')
                return (1);
            i++;
        }
    }
    return (0);
}*/

int	ft_lstsize(t_gnl *lst)
{
    int	count;

    count = 1;
    if (!lst)
        return (0);
    if (lst->next == NULL)
        return (count);
    while (lst->next != NULL)
    {
        lst = lst->next;
        count++;
    }
    return (count);
}


t_gnl	*ft_lst_get_last(t_gnl *stash)
{
	t_gnl	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	ft_broomstick(t_gnl **stash)
{
	t_gnl	*last;
	t_gnl	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_gnl));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}

void	free_stash(t_gnl *stash)
{
	t_gnl	*current;
	t_gnl	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}


int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}