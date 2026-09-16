#include "../headers/codexion.h"

void heap_push(t_request data, t_request **heap, t_dongle *dongle)
{
    if (dongle->heap_size <= 2 && dongle->heap_size > 0)
    {
        *heap[1] = *heap[0];
        *heap[0] = data;
    }
}

t_request   *heap_pop(t_dongle *dongle, t_request *heap)
{
    t_request   *tmp;

    tmp = NULL;
    if (dongle->heap_size <= 2 && dongle->heap_size > 0)
    {
        tmp = heap;
        heap[0] = heap[1];
    }
    return (tmp);
}

int request(t_coder *coder, t_dongle *dongle)
{
    t_request *request;

    pthread_mutex_lock(&dongle->lock);
    request = (t_request *) malloc(sizeof(t_request));
    if (!request)
        return (0);
    request->id_coder = coder->id;
    heap_push(*request, dongle->request, dongle);
    pthread_mutex_unlock(&dongle->lock);
    return (1);
}
