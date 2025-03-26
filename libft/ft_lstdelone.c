#include "libft.h"

void    ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst || !del)
        return ;
    del(lst->content);
    free(lst);
}
/*
#include <stdio.h>
#include <string.h>
void    del(void *content)
{
    free(content);
}

int main(void)
{
    t_list  *head = malloc(sizeof(t_list));
    char    *str = "Viva España";

    head->content = malloc(sizeof(char) + strlen(str)+1);
    strcpy(head->content, str);
    head->next = NULL;
    printf("%s\n", head->content);
    ft_lstdelone(head, del);
    return 0;
}*/