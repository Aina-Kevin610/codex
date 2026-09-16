#include "../headers/codexion.h"
#include <pthread.h>

static int  am_i_priority(t_coder *coder, t_dongle *dongle)
{
    if (coder->id == dongle->request[0]->id_coder)
        return (1);
    return (0);
}

void    take_dongle(t_coder *coder)
{
    pthread_mutex_lock(&coder->dongle_left->lock);
    while (
        !(am_i_priority(coder, coder->dongle_left) && am_i_priority(coder, coder->dongle_left))
    )
        pthread_cond_wait(&coder->dongle_left->cond, &coder->dongle_left->lock);
    pthread_mutex_unlock(&coder->dongle_left->lock);
    pthread_mutex_lock(&coder->dongle_right->lock);
    while (
        !(am_i_priority(coder, coder->dongle_right) && am_i_priority(coder, coder->dongle_right))
    )
        pthread_cond_wait(&coder->dongle_right->cond, &coder->dongle_right->lock);
    pthread_mutex_unlock(&coder->dongle_right->lock);
}

// void    release_dongle(t_coder *coder)
// {

// }