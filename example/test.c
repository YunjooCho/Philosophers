#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Same as 'task', but meant to be called from different threads. */
void *threaded_task(void *t) {
  long id = (long) t;
  printf("Thread %ld started\n", id);
  printf("Thread %ld done\n", id);
  pthread_exit(0);
  return (NULL);
}

/* Run 'task' num_tasks times, creating a separate thread for each
   call to 'task'. */
void *parallel(int num_tasks)
{
  int num_threads = num_tasks;
  pthread_t thread[num_threads];
  int rc;
  long t;
  for (t = 0; t < num_threads; t++) {
    printf("Creating thread %ld\n", t);
    rc = pthread_create(&thread[t], NULL, threaded_task, (void *)t);
    if (rc) {
      printf("ERROR: return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  return (NULL);
}

void *print_usage(int argc, char *argv[]) {
  (void) argc;
  printf("Usage: %s serial|parallel num_tasks\n", argv[0]);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc != 3) {print_usage(argc, argv);}

  int num_tasks = atoi(argv[2]);

  if (!strcmp(argv[1], "parallel")) {
    parallel(num_tasks);
  }
  else {
    print_usage(argc, argv);
  }

  printf("Main completed\n");
  pthread_exit(NULL);
}


//컴파일 : time ./test parallel 4