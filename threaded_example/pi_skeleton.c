// Global variables accessible by the threads and the main program
long long counter_max;
long long counter = 1;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
double *sum_res;

void *pi_thread(void *arg) {
  while (1) {
    //...
    pthread_mutex_lock(&counter_mutex);
    beg = counter;
    counter += 1000000;
    pthread_mutex_unlock(&counter_mutex);
    //...
  }
  //...
}


int main(int argn, char *arg[]) {
  // Get n and N (counter_max) via arg...
  //...
  sum_res = (double *)malloc(n*sizeof(double));
  tid = (pthread_t *)malloc(n*sizeof(pthread_t));
  id = (int *)malloc(n*sizeof(int));
  //...

  for (i=0;i<n;i++)
    pthread_create(tid+i, NULL, pi_thread, id+i);

  // Wait th threads to exit
  
  // gether the results
  pi = 0.0;
  for (i=0;i<n;i++)
    pi += sum_res[i];

  //...
}

