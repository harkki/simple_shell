#include "shell.h"
/**
 * add_node - adds a node to the start of the linked list
 * @head: address of pointer to head node
 * @str: string field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
​list_t *new_node = NULL;
​if (!head)
​​return (NULL);
​list_t *new_node = malloc(sizeof(list_t));
​if (!new_node)
​​return (NULL);
​new_node->num = num
new_head->str = _strdup(str);
​if (!new_node->str)
​{
​​free(new_node);
​​return (NULL);
​}
​new_ node->next = *head;
​ *head = new_node;
​return (new_node);
}
/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
​list_t *new_node = NULL, *node = NULL;
​if (!head)
​​return (NULL);
​list_t *new_node = malloc(sizeof(list_t));
​if (!new_node)
​​return (NULL);
​new_node->num = num;
​new_node->str = _strdup(str);
​if (!new_node->str)
​{
​​free(new_node);
​​return (NULL);
​}
new_node->next = NULL;
​if (!*head)
​​ *head = new_node;
​else
​{
​​list_t *last = *head;
​​while (node->next)
​​​last = last->next;
​​last->next = new_node;
​}
​return (new_node);
}
/**
 * print_list_str - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *head)
{
​size_t count = 0;
​while (head)
​{
​​_puts(head->str ? head->str : "(nil)");
​​_puts("\n");
​​head = head->next;
​​count++;
​}
​return (count);
}
/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
​if (!head || !*head)
​​return (0);
​if (index == 0)
​{
​​list_t *temp = *head;
​​ *head = (*head)->next;
​​free(temp->str);
​​free(temp);
​​return (1);
​}
​list_t *prev = NULL;
list_t *current = *head;
​unsigned int count = 0;
​while (current && count < index)
​{
​​prev = current;
​​current = current->next;
count++;
​}
​If(current)
​{
​​prev->next = current->next;
​​free(current->str);
​​free(current);
​​return (1);
​}
​return (0);
}
/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
​list_t *node, *next_node, *head;
​if (!head_ptr || !*head_ptr)
​​return;
​head = *head_ptr;
​node = head;
​while (node)
​{
​​next_node = node->next;
​​free(node->str);
​​free(node);
​​node = next_node;
​}
​ *head_ptr = NULL;
}
