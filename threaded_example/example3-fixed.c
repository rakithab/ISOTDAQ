#include "myincludes.h"

int counter;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *function(void *arg) {
  int i;
  printf("tid=%p\n", pthread_self());
  for (i=0;i<1000000;i++){
    pthread_mutex_lock(&counter_mutex);
    counter++;
    pthread_mutex_unlock(&counter_mutex);
  }
  return NULL;
}

int main(int argn, char *arg[]) {
  pthread_t tid1, tid2;

  pthread_create(&tid1, NULL, function, NULL);
  pthread_create(&tid2, NULL, function, NULL);
  
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  
  printf("counter = %d\n", counter);
  
  return 0;
}
