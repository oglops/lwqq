#ifndef LWQQ_WIN32_H_H
#define LWQQ_WIN32_H_H

double drand48(void);
void srand48(unsigned int i);

#define mkdir(a, b) mkdir(a)

#ifdef WITH_LIBEV
// copy from libev
int ev_pipe(int filedes[2]);
#endif

#endif

