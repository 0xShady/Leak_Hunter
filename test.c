#include "leak_hunter.h"

int     main()
{
	atexit(leak_report);
	char	*s = (char *)malloc(10);
	int		*i = (int *)malloc(20 * sizeof(int));
	float	*f = (float *)malloc(5 * sizeof(float));
	/*some code*/
	free(f);
	free(s);
	free(i);
	return (0);
}