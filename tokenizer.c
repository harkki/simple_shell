#include "shell.h"
/**
 * **custom_strtow - splits string into words. Repeat delimiters are ignored
 * @input_str: the input string
 * @delimeter: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow(char *input_str, char *delimeter)
{
​int i, j, k, m, n_words = 0;
​char **result_array;
​if (input_str == NULL || input_str[0] == 0)
​​return (NULL);
​if (!delimeter)
​​delimeter = " ";
​for (i = 0; input_str[i] != '\0'; i++)
​​if (!is_delimeter(input_str[i], d) && (is_delimeter(input_str[i + 1], delimeter) || !input_str[i + 1]))
​​​n_words++;
​if (n_words == 0)
​​return (NULL);
​result_array = malloc((1 + n_words) * sizeof(char *));
​if (!result_array)
​​return (NULL);
​for (i = 0, j = 0; j < n_words; j++)
​{
​​while (is_delimeter(input_str[i], delimeter))
​​​i++;
​​k = 0;
​​while (!is_delimeter(input_str[i + k], delimeter) && input_str[i + k])
​​​k++;
​​result_array[j] = malloc((k + 1) * sizeof(char));
​​if (!result_array[j])
​​{
​​​for (k = 0; k < j; k++)
​​​​free(result_array[k]);
​​​free(result_array);
​​​return (NULL);
​​}
​​for (m = 0; m < k; m++)
​​​result_array[j][m] = input_str[i++];
​​result_array[j][m] = 0;
​}
​result_array[j] = NULL;
​return (result_array);
}
 /**
 * **custom_strtow2 - splits a string into words
 * @ input_str: the input string
 * @delimeter: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow2(char *input_str, char delimeter)
{
​int i, j, k, m, n_words = 0;
​char **result_array;
​if (input_str == NULL || input_str[0] == 0)
​​return (NULL);
​for (i = 0; input_str[i] != '\0'; i++)
​​if ((input_str[i] != delimeter && input_str[i + 1] == delimeter) ||
​​​​    (input_str[i] != delimeter && !input_str[i + 1]) || input_str[i + 1] == delimeter)
​​​n_words++;
​if (n_words == 0)
​​return (NULL);
​result_array = malloc((1 + n_words) * sizeof(char *));
​if (!result_array)
​​return (NULL);
​for (i = 0, j = 0; j < n_words; j++)
​{
​​while (input_str[i] == delimeter && input_str[i] != delimeter)
​​​i++;
​​k = 0;
​​while (input_str[i + k] != delimeter && input_str[i + k] && input_str[i + k] != delimeter)
​​​k++;
​​result_array[j] = malloc((k + 1) * sizeof(char));
​​if (!result_array[j])
​​{
​​​for (k = 0; k < j; k++)
​​​​free(result_array[k]);
​​​free(result_array);
​​​return (NULL);
​​}
​​for (m = 0; m < k; m++)
​​​result_array[j][m] = input_str[i++];
​​result_array[j][m] = 0;
​}
​result_array[j] = NULL;
​return (result_array);
}
