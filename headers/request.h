#ifndef REQUEST_H
# define REQUEST_H

typedef struct s_coder	    t_coder;
typedef struct s_request	t_request;
typedef struct s_dongle 	t_dongle;

int         request(t_coder *coder, t_dongle *dongle);
void        heap_push(t_request data, t_request **heap, t_dongle *dongle);
t_request   *heap_pop(t_dongle *dongle, t_request **heap);

#endif
