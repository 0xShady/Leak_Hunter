#include "leak_hunter.h"

#undef	malloc
#undef 	free

t_list	*lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_list **alst, t_list *new)
{
	new->next = NULL;
	if (!(*alst))
		*alst = new;
	else
		lstlast(*alst)->next = new;
}

t_list  *create_node(void *address, size_t size, size_t line, char *file)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->address = address;
	new->size = size;
	new->line = line;
	new->file = strdup(file);
	new->next = NULL;
	return (new);
}

void    delete_node(t_list** head, void *key)
{
    t_list *tmp, *prev;

    tmp = *head;
    if (tmp != NULL && tmp->address == key) {
        *head = tmp->next;
        free(tmp->file);
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp->address != key) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}
