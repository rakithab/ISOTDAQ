#include "myincludes.h"

// TODO
// 1) myincludes.h
// 2) Note the error checking on pthread_create
// 3) Fix the code

typedef struct {
  int x, y;
} complex_t;

void *function(void *arg) {
  complex_t *c = (complex_t*)arg;
  printf("tid=%p  x=%d  y=%d\n", pthread_self(), c->x, c->y);
  return NULL;
}

int main(int argn, char *arg[]) {
  pthread_t tid1, tid2;
  complex_t c1, c2;

  c1.x = c1.y = 20;
  pthread_create(&tid1, NULL, function, &c1);
  
  c2.x = c2.y = 30;
  pthread_create(&tid2, NULL, function, &c2);
  
  pthread_join(tid1, NULL); //void pthread_exit(void *value_ptr);
  pthread_join(tid2, NULL);
  
  return 0;
}
