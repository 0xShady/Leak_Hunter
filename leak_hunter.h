#ifndef LEAK_HUNTER_H
#define LEAK_HUNTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OUTPUT_FILE_NAME	"leak_log.txt"
#define malloc(size)		xmalloc(size, __FILE__, __LINE__)
#define free(men_ref)		xfree(mem_ref)

typedef struct s_list
{
	void			*address;
	size_t			size;
	char			*file;
	size_t			line;
	struct s_list	*next;
}				t_list;

/*list tools*/
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
t_list  		*ft_lstnew(void *address, size_t size, size_t line, char *file);

/*core functions*/
void			*xmalloc(size_t size, char *file, size_t line);
void			xfree(void *mem_ref);
void			print_mem_data();


#endif /*LEAK_HUNTER_H*/