#include "shell.h"

/**
 * _create_pathnode - create path node
 * @path: path string
 *
 * Return: pointer to new node
 */
pathnode *create_pathnode(char *path)
{
	pathnode *node;

	node = malloc(sizeof(pathnode)); /* not working */
	if (node == NULL)
	{
		printf("create node: node finally null\n");
		return (NULL);
	}
	node->path = path;
	node->next = NULL;
	return (node);
}

/**
 * make_pathlist - create's pathlist
 * Return: path linked list
 */
pathnode *make_pathlist()
{
	pathnode *head = NULL;
	char *delims = ":";
	char *paths = NULL;
	char *buffer = NULL;
	pathnode *p;

	paths = getenv("PATH");
	paths = strdup(paths); /*gotta free this paths duplicate once per sess*/
	buffer = strtok(paths, delims);
	if (buffer == NULL)
		return (NULL);
	head = create_pathnode(buffer);
	if (!head)
		return (NULL);
	p = head;
	while (buffer = strtok(NULL, delims))
	{ /*pathlist reliant on paths duplicate so free head to free duplicate*/
		p->next = create_pathnode(buffer);
		if (!p->next)
			break; /* must free path list & paths duplicate*/
		p = p->next;
	}
	return (head);
}

/**
 * pathsearch - search for executable pathname
 * @command: command name
 * @head: pointer to head
 * Return: full string name of found command or NULL
 */
char *pathsearch(char *command, pathnode *head)
{
	pathnode *p = head;
	char *result;
	struct stat st;

	if (stat(command, &st) == 0)
		return (command);

	while (p != NULL)
	{/*must free result*/
		result = malloc(strlen(p->path) + strlen(command) + 2);
		if (!result)
			return (NULL);
		strcpy(result, p->path);
		result[strlen(p->path)] = '/';
		result[strlen(p->path) + 1] = '\0';
		strcat(result, command);
		if (stat(result, &st) == 0)
			return (result);/*must free result*/
		free(result);
		p = p->next;
	}
	printf("command not found\n");
	return (NULL);
}
