#include "shell.h"
/**
 * **cus_strtow - splits string into words.
 * @in_str: the input string
 * @de: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **cus_strtow(char *in_str, char *de)
{
​int i, j, k, m, n_words = 0;
​char **result_array;
​if (in_str == NULL || in_str[0] == 0)
​​return (NULL);
​if (!de)
​​delim = " ";
​for (i = 0; in_str[i] != '\0'; i++)
​​if (!is_de(in_str[i], d) && (is_de(in_str[i + 1], de) || !in_str[i + 1]))
​​​n_words++;
​if (n_words == 0)
​​return (NULL);
​result_array = malloc((1 + n_words) * sizeof(char *));
​if (!result_array)
​​return (NULL);
​for (i = 0, j = 0; j < n_words; j++)
​{
​​while (is_de(in_str[i], de))
​​​i++;
​​k = 0;
​​while (!is_de(in_str[i + k], de) && in_str[i + k])
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
​​​result_array[j][m] = in_str[i++];
​​result_array[j][m] = 0;
​}
​result_array[j] = NULL;
​return (result_array);
}
 /**
 * **cus_strtow2 - splits a string into words
 * @in_str: the input string
 * @de: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **cus_strtow2(char *in_str, char de)
{
​int i, j, k, m, n_words = 0;
​char **result_array;
​if (in_str == NULL || in_str[0] == 0)
​​return (NULL);
​for (i = 0; in_str[i] != '\0'; i++)
​​if ((in_str[i] != de && in_str[i + 1] == de) ||
​​​​    (in_str[i] != de && !in_str[i + 1]) || in_str[i + 1] == de)
​​​n_words++;
​if (n_words == 0)
​​return (NULL);
​result_array = malloc((1 + n_words) * sizeof(char *));
​if (!result_array)
​​return (NULL);
​for (i = 0, j = 0; j < n_words; j++)
​{
​​while (in_str[i] == de && in_str[i] != de)
​​​i++;
​​k = 0;
​​while (in_str[i + k] != de && in_str[i + k] && in_str[i + k] != de)
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
​​​result_array[j][m] = in_str[i++];
​​result_array[j][m] = 0;
​}
​result_array[j] = NULL;
​return (result_array);
}
