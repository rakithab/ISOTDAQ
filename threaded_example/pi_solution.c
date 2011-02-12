#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>


long long counter_max;
long long counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
double *sum_res;

void printout_the_result(double pi);


void *pi_thread(void *arg) {
  double sum;
  long long i, beg, end, unit;
  
  while (1) {
    pthread_mutex_lock(&counter_mutex);
    unit = counter;
    counter++;
    pthread_mutex_unlock(&counter_mutex);
    
    if (unit>=counter_max) return NULL;
   
    beg = unit*1000000;
    end = beg + 1000000;

    sum = 0.0; 
    for (i=beg+1;i<end;i+=4)
      sum += 1.0/(double)i - 1.0/(double)(i+2);
    
    sum_res[unit] = sum*4.0;
  }
  return NULL;
}


int main(int argn, char *arg[]) {
  pthread_t *tid;
  double pi;
  int i, n;
  
  if (argn!=3) return printf("Usage: pi <n_threads> <N>\n");
  
  n = atol(arg[1]);
  counter_max = atol(arg[2]);

  printf("\nN = %lldx1000000\n", counter_max);

  sum_res = (double *)malloc(counter_max*sizeof(double));
  tid = (pthread_t *)malloc(n*sizeof(pthread_t));
  
  printf("Running %d threads...\n", n);

  for (i=0;i<n;i++)
    pthread_create(tid+i, NULL, pi_thread, NULL);

  for (i=0;i<n;i++)
    pthread_join(tid[i], NULL);

  pi = 0.0;
  for (i=0;i<counter_max;i++)
    pi += sum_res[i];
  
  printout_the_result(pi);
  
  free(sum_res);
  free(tid);
  
  return 0;
}


void printout_the_result(double pi) {
  int sig_figures;
  char str_correct[32];
  char str_wrong[32];

  sig_figures = (int)(-log10(fabs((pi-M_PI)/M_PI)));
  if (sig_figures<0) sig_figures=0;
  if (sig_figures>30) sig_figures=30;
  sprintf(str_correct, "%19.17lf", pi);
  sprintf(str_wrong, "%19.17lf", pi);
  str_correct[sig_figures+1] = 0;
  printf("pi = \033[32;1m%s\033[0m%s    (%d sig-figs)\n\n",
         str_correct, str_wrong+sig_figures+1, sig_figures);
}

