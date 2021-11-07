# Leak_Hunter

## What is a memory leak
## How to use the leak hunter
#### let's asume we want to track the leaked blocks on the file leak.c

```c
#include <stdlib.h>
#include <stdio.h>

int     main()
{
	char	*s = (char *)malloc(10);
	int		*i = (int *)malloc(20 * sizeof(int));
	float	*f = (float *)malloc(5 * sizeof(float));
	/*some code*/
	return (0);
}
```

#### • You must include `leak_hunter.h` into your project's header file or your .c file in our case we asume the file test.c is our project:
	- `#include "leak_hunter.h"`
#### • Then add the following line at the start of your main function:
	- `atexit(leak_report);`

Now the test code should look like the code below:

```c
#include <stdlib.h>
#include <stdio.h>
#include "leak_hunter.h"

int     main()
{
	atexit(leak_report);
	char	*s = (char *)malloc(10);
	int		*i = (int *)malloc(20 * sizeof(int));
	float	*f = (float *)malloc(5 * sizeof(float));
	/*some code*/
	return (0);
}
```

In this case we should get the following output on the file `leak.log` (you can change the path the name and extension related to the file in `leak_hunter.h line:9`)

```log
┌─────────┤ LEAKS LOG ├─────────┐
│ Total leaks found:          3 │
│ Total leaks size:         110 │
├───────────────────────────────┤
│ address:       0x6020000000b0 │
│ size (bytes):              10 │
│ file:                  test.c │
│ line:                       7 │
├───────────────────────────────┤
│ address:       0x607000000020 │
│ size (bytes):              80 │
│ file:                  test.c │
│ line:                       8 │
├───────────────────────────────┤
│ address:       0x6030000019f0 │
│ size (bytes):              20 │
│ file:                  test.c │
│ line:                       9 │
└───────────────────────────────┘
```

The log contains
• summary fo the
	- Total leaks found.\n
	- Total leaks size(bytes).\n
• each leak details
	- Address\n
	- Size\n
	- File\n
	- Line\n

• after unallocate the reserved memory using the `free()` function.

``` c
#include <stdlib.h>
#include <stdio.h>
#include "leak_hunter.h"

int     main()
{
	atexit(leak_report);
	char	*s = (char *)malloc(10);
	int		*i = (int *)malloc(20 * sizeof(int));
	float	*f = (float *)malloc(5 * sizeof(float));

	/*some code*/

	free(f);
	free(i);
	free(s);
	return (0);
}
```

`leak.log` should look like this

```log
┌─────────┤ LEAKS LOG ├─────────┐
│ Total leaks found:          0 │
│ Total leaks size:           0 │
├───────────────────────────────┤
│   your code is leaks free!!   │
└───────────────────────────────┘
```
Pretty simple, right!

## How it actually works

Big thanks to [mamali](https://profile.intra.42.fr/users/mamali) && [hfadyl](https://profile.intra.42.fr/users/hfadyl) for all the emotional support

