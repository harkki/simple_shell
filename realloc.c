#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @mem_dest: the pointer to the memory area
 * @byte: the byte to fill memory with
 * @size: the number of bytes to be filled
 * Return: A pointer to the memory area s
 */
char *_memset(char *mem_dest, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		mem_dest[i] = byte;

	return (mem_dest);
}

/**
 * free_str - frees a string of strings
 * @str_array: Array of strings to be freed
 */
void free_str(char **str_array)
{
	char **temp_ptr = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp_ptr);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previously allocated block
 * @old_size: size of previous block in byte
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if  (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = (old_size < new_size) ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
