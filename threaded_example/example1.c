#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *function(void *arg) {
  int *iarg = (int*)arg;
  
  printf("arg=%d  tid=%p\n", *iarg, pthread_self());

  return NULL;
}

int main(int argn, char *arg[]) {
  pthread_t tid1, tid2;
  int ret;
  int arg1, arg2;
  
  arg1 = 1;
  ret = pthread_create(&tid1, NULL, function, &arg1);
  if (ret) return printf("Cannot create thread1!\n");
  
  arg2 = 2;
  ret = pthread_create(&tid2, NULL, function, &arg2);
  if (ret) return printf("Cannot create thread2!\n");
  
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  
  return 0;
}
