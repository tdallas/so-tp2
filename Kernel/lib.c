#include <stdint.h>
#include <pageAllocator.h>
#include <lib.h>

void *malloc(uint64_t size)
{
	if (size <= PAGE_SIZE)
	{
		return (void *)getAvailablePage();
	}
	else
	{
		return (void *)getStackPage();
	}
}

void free(void *page)
{
	if ((uint64_t)page < MEMORY_PAGES_END)
	{
		releasePage((uint64_t)page);
	}
	else if ((uint64_t)page > MEMORY_PAGES_END)
	{
		releaseStackPage((uint64_t)page);
	}
	else
	{
		printString("Error in freeing memory\n", 0, 0, 255);
	}
}


void *memcpy(void *destination, const void *source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
			(uint64_t)source % sizeof(uint32_t) == 0 &&
			length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *)destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t *d = (uint8_t *)destination;
		const uint8_t *s = (const uint8_t *)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void *realloc(void *ptr, uint64_t size)
{
	void *newptr = malloc(size);
	memcpy(newptr, ptr, size);
	free(ptr);
	return newptr;
}


void *memset(void *destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char *dst = (char *)destination;

	while (length--)
		dst[length] = chr;

	return destination;
}


int strcmpKernel(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int strlenKernel(const char *s)
{
	const char *p = s;
	while (*s)
		++s;
	return s - p;
}

void strcpyKernel(char *d, const char *s)
{
	while (*s != '\0')
	{
		*d = *s;
		d++;
		s++;
	}
	*d = '\0';
}

void strcatKernel(char *d, const char *s){
    int i,j;
    for (i = 0; d[i] != '\0'; i++);
    for (j = 0; s[j] != '\0'; j++)
        d[i+j] = s[j];
    d[i+j] = '\0';
}