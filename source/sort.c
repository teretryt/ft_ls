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
            if (ptr1->_stat->st_mtime < ptr1->_next->_stat->st_mtime)
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

void	stringSort(char **arr, int n)
{
	char temp[4096];

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			// strcmp kullanarak stringleri karşılaştırıyoruz
			if (ft_strcmp(arr[i], arr[j]) > 0) {
				ft_strlcpy(temp, arr[i], 4096);
				ft_strlcpy(arr[i], arr[j], 4096);
				ft_strlcpy(arr[j], temp, 4096);
			}
		}
	}
}