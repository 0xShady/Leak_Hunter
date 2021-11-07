#include "leak_hunter.h"

#undef	malloc
#undef 	free

t_list *mem_data = NULL;

void	xfree(void *mem_ref)
{
	delete_node(&mem_data, mem_ref);
	free(mem_ref);
}

void	*xmalloc(size_t size, char *file, size_t line)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr != NULL)
		lstadd_back(&mem_data, create_node(ptr, size, line, file));
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

void	leak_report()
{
	t_list	*tmp;
	FILE	*log;
	int		leaks_size;
	int		allocated_blocks;

	leaks_size = 0;
	allocated_blocks = 0;
	if ((log = fopen(OUTPUT_FILE_NAME, "w")))
	{
		tmp = mem_data;
		while (tmp)
		{
			allocated_blocks++;
			leaks_size += tmp->size;
			tmp = tmp->next;
		}
		fprintf(log, "┌─────────┤ LEAKS LOG ├─────────┐\n");
		fprintf(log, "│ Total leaks found: %10d │\n", allocated_blocks);
		fprintf(log, "│ Total leaks size: %11d │\n", leaks_size);
		fprintf(log, "├───────────────────────────────┤\n");
		tmp = mem_data;
		if (tmp)
		{
			while (tmp)
			{
				fprintf(log, "│ address: %20p │\n", tmp->address);
				fprintf(log, "│ size (bytes): %15zu │\n", tmp->size);
				fprintf(log, "│ file: %23s │\n", tmp->file);
				fprintf(log, "│ line: %23zu │\n", tmp->line);
				if (tmp->next)
					fprintf(log, "├───────────────────────────────┤\n");
				tmp = tmp->next;
			}
			fprintf(log, "└───────────────────────────────┘");
		}
		else
			fprintf(log, "│   your code is leaks free!!   │\n");
			fprintf(log, "└───────────────────────────────┘");
		fclose(log);
	}
}