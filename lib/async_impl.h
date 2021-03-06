#ifndef LWQQ_ASYNC_IMPL_H_H
#define LWQQ_ASYNC_IMPL_H_H

#include "async.h"

#define LWQQ__ASYNC_IMPL(impl) lwqq__async_impl_->impl
struct LwqqAsyncTimer {
   LwqqAsyncTimerCallback func;
   void* data;
};

struct LwqqAsyncIo {
   LwqqAsyncIoCallback func;
   void* data;
   int fd;
   int action;
};
typedef enum {
   USE_THREAD = 1<<0,
   NO_THREAD = 0
}LwqqAsyncImplFlags;
typedef struct LwqqAsyncImpl {
   const char* name;
   const LwqqAsyncImplFlags flags;
   void (*loop_create)();
   void (*loop_run)();
   void (*loop_stop)();
   void (*loop_free)();

   void* (*io_new)();
   void (*io_free)(void* h);
   void (*io_start)(void* h, int fd, int act);
   void (*io_stop)(void* h);

   void* (*timer_new)();
   void (*timer_free)(void* h);
   void (*timer_start)(void* h, unsigned int ms);
   void (*timer_stop)(void* h);
   void (*timer_again)(void* h);

   LIST_ENTRY(LwqqAsyncImpl) entries;
} LwqqAsyncImpl;

typedef LIST_HEAD(, LwqqAsyncImpl) LwqqAsyncImplList;
extern LwqqAsyncImplList lwqq__async_impl_list_;

extern LwqqAsyncImpl* lwqq__async_impl_;
void lwqq_async_implement(LwqqAsyncImpl*);
#define LWQQ_ASYNC_IMPLEMENT(impl) lwqq_async_implement(&impl);

#endif

