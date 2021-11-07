#ifndef LEAK_HUNTER_H
# define LEAK_HUNTER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define OUTPUT_FILE_NAME	"leak.log"
# define malloc(size)		xmalloc(size, __FILE__, __LINE__)
# define free(mem_ref)		xfree(mem_ref)

typedef struct s_list
{
	void			*address;
	size_t			size;
	char			*file;
	size_t			line;
	struct s_list	*next;
}				t_list;

/*list tools*/
t_list			*lstlast(t_list *lst);
void			lstadd_back(t_list **alst, t_list *new);
t_list  		*create_node(void *address, size_t size, size_t line, char *file);
void			delete_node(t_list** head, void *key);

/*core functions*/
void			*xmalloc(size_t size, char *file, size_t line);
void			xfree(void *mem_ref);
void			print_mem_data();
void			leak_report();

#endif /*LEAK_HUNTER_H*/