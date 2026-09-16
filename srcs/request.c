#include "../headers/codexion.h"

void	heap_push(t_request data, t_request **heap, t_dongle *dongle)
{
    t_request	*new_request;

    if (!heap || !dongle || dongle->heap_size >= 2)
        return ;
    new_request = malloc(sizeof(t_request));
    if (!new_request)
        return ;
    *new_request = data;
    heap[dongle->heap_size] = new_request;
    dongle->heap_size++;
}

t_request	*heap_pop(t_dongle *dongle, t_request **heap)
{
    t_request	*tmp;

    if (!dongle || !heap || dongle->heap_size <= 0)
        return (NULL);
    tmp = heap[0];
    heap[0] = heap[1];
    heap[1] = NULL;
    dongle->heap_size--;
    return (tmp);
}

int	request(t_coder *coder, t_dongle *dongle)
{
	t_request	new_request;

	if (!coder || !dongle)
		return (0);
	pthread_mutex_lock(&coder->all->gle_lock);
	new_request.id_coder = coder->id;
	heap_push(new_request, dongle->request, dongle);
	pthread_mutex_unlock(&coder->all->gle_lock);
	return (1);
}
