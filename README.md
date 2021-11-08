# Leak_Hunter

### Efficient yet simple leak detector for your c project

## What is a memory leak
In computer science, a memory leak is a type of resource leak that occurs when a computer program incorrectly manages [memory allocations](https://en.wikipedia.org/wiki/Memory_management#ALLOCATION) in a way that memory which is no longer needed is not released. A memory leak may also happen when an object is stored in memory but cannot be accessed by the running code. A memory leak has symptoms similar to a number of other problems and generally can only be diagnosed by a programmer with access to the program's source code.
* more about [memory leaks](https://en.wikipedia.org/wiki/Memory_leak)
## How to use the leak hunter
#### let's asume we want to track the leaked blocks on the file `test.c`

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
	#include "leak_hunter.h"
#### • Then add the following line at the start of your main function:
	atexit(leak_report);

* Now the test code should look like the code below:

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
### • Compile all the files (in our case)
	gcc test.c leak_hunter.c -o test
	./test

* In this case we should get the following output on the file `leak.log` (you can change the path the name and extension related to the file in `leak_hunter.h line:9`)

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

The log contains<br />
* Summary fo the<br />
	* Total leaks found<br />
	* Total leaks size(bytes)<br />
* Each leak details<br />
	* Address<br />
	* Size<br />
	* File<br />
	* Line<br />

### After unallocating the reserved memory using the `free()` function.

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

Now lets have look into the code and how it works .

The leak_hunter.h file contains some macros and the preprocessor replaces the call of malloc and free functions with xmalloc and xfree respectively.

While calling `malloc()` `xmalloc()` is called and We keep all information of the allocated memory (like the address, size, file name and line number) in a linked list. while the code call the `free()` function, it actually calls `xfree()` and we manage to do the cleanup task (remove the entry of the allocated memory from the list and free up the allocated memory).

At the end of the program, we can get the unallocated memory references from the list.

The line `atexit(leak_report)` registers the `leak_report()` function to be called at the end of the program and this function writes the memory leak summary in to the `leak.log` file. you can also use `#pragma` exit dirctive instead of `atexit()`.

## l3aaaz

Big thanks to [mamali](https://profile.intra.42.fr/users/mamali) & [hfadyl](https://profile.intra.42.fr/users/hfadyl) for all the emotional support

