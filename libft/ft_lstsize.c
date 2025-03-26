#include "libft.h"

int ft_lstsize(t_list *lst)
{
    int i;

    i = 0;
    while(lst)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}
/*
#include <stdio.h>
int main(void)
{
    t_list  *node = ft_lstnew("A");
    t_list  *node2 = ft_lstnew("B");
    t_list  *node3 = ft_lstnew("C");

    node->next = node2;
    node2->next = node3;
    node3->next = NULL;
    printf("El numero de nodos en la lista es: %d\n", ft_lstsize(node));
    printf("Y su contenido es: %s, %s y %s, respectivamente.\n", (char *)node->content, (char *)node2->content, (char *)node3->content);
    free(node);
    free(node2);
    free(node3);
    return (0);
}*/