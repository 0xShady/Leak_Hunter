#include "leak_hunter.h"

#undef	malloc
#undef 	free

t_list *mem_data = NULL;

void	*xmalloc(size_t size, char *file, size_t line)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr != NULL)
		ft_lstadd_back(&mem_data, ft_lstnew(ptr, size, line, file));
	return (ptr);
}

void	print_mem_data()
{
	t_list *tmp;

	tmp = mem_data;
	while (tmp)
	{
		printf("address: %p\n", tmp->address);
		printf("size: %zu\n", tmp->size);
		printf("file: %s\n", tmp->file);
		printf("line: %zu\n", tmp->line);
		tmp = tmp->next;
	}
}