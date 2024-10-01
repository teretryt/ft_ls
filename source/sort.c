#include "../includes/ft_ls.h"

void swap(t_file **head, t_file *a, t_file *b)
{
    t_file *prev_a = a->_prev;
    t_file *next_b = b->_next;

    if (prev_a)
        prev_a->_next = b;
    else
        *head = b;

    if (next_b)
        next_b->_prev = a;

    b->_prev = prev_a;
    b->_next = a;
    a->_prev = b;
    a->_next = next_b;
}

t_file *sort_files_reverse(t_file *head)
{
    t_file *current;
    t_file *next;
    t_file *new_head;

    current = head;
    next = NULL;
    new_head = NULL;
    while (current)
    {
        next = current->_next;
        current->_next = new_head;
        new_head = current;
        current = next;
    }
    return new_head;
}

t_file *sort_files_time(t_file *head)
{
    int swapped;
    t_file *ptr1;
    t_file *lptr = NULL;

    if (!head)
        return NULL;

    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->_next != lptr)
        {
            if (ptr1->_stat->st_mtimespec.tv_nsec < ptr1->_next->_stat->st_mtimespec.tv_nsec)
            {
                swap(&head, ptr1, ptr1->_next);
                swapped = 1;
            }
            else
                ptr1 = ptr1->_next;
        }
        lptr = ptr1;
    }

    return head;
}

t_file *sort_files_alph(t_file *head)
{
    int swapped;
    t_file *ptr1;
    t_file *lptr = NULL;

    if (!head)
        return NULL;

    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->_next != lptr)
        {
            if (ft_strcmp(ptr1->_info->d_name, ptr1->_next->_info->d_name) > 0)
            {
                swap(&head, ptr1, ptr1->_next);
                swapped = 1;
            }
            else
                ptr1 = ptr1->_next;
        }
        lptr = ptr1;
    }

    return head;
}

void    string_sort_time(char **arr, int n, uint8_t reverse)
{
    int i;
    int j;
    struct stat stat1;
    struct stat stat2;
    char temp[PATH_MAX];

    i = -1;
    while (++i < n - 1)
    {
        j = i;
        while (++j < n)
        {
            lstat(arr[i], &stat1);
            lstat(arr[j], &stat2);
            if (reverse && stat1.st_mtime > stat2.st_mtime)
            {
                ft_strlcpy(temp, arr[i], PATH_MAX);
                ft_strlcpy(arr[i], arr[j], PATH_MAX);
                ft_strlcpy(arr[j], temp, PATH_MAX);
            }
            if (!reverse && stat1.st_mtime < stat2.st_mtime)
            {
                ft_strlcpy(temp, arr[i], PATH_MAX);
                ft_strlcpy(arr[i], arr[j], PATH_MAX);
                ft_strlcpy(arr[j], temp, PATH_MAX);
            }
        }
    }
}

void	stringSort(char **arr, int n, uint8_t reverse)
{
    int     i;
    int     j;
	char    temp[PATH_MAX];

    i = -1;
    while (++i < n - 1)
    {
        j = i;
        while (++j < n)
        {
            if (reverse && ft_strcmp(arr[i], arr[j]) > 0)
            {
				ft_strlcpy(temp, arr[i], PATH_MAX);
				ft_strlcpy(arr[i], arr[j], PATH_MAX);
				ft_strlcpy(arr[j], temp, PATH_MAX);
			}
			if (!reverse && ft_strcmp(arr[i], arr[j]) < 0)
            {
				ft_strlcpy(temp, arr[i], PATH_MAX);
				ft_strlcpy(arr[i], arr[j], PATH_MAX);
				ft_strlcpy(arr[j], temp, PATH_MAX);
			}
		}
	}
}