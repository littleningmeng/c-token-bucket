#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "token_bucket.h"

static token_bucket_t *tb;
void *proc(void *arg) {
  while(1) {
    if(token_bucket_try_take(tb, 1)) {
      printf("hello: %lu\n", pthread_self());
    } else {
      sleep(0);
    }
  }
}

void *tick(void *arg) {
  while(1) {
    sleep(1);
    printf("=============================\n");
  }
}

int main(int argc, char *argv[]) {
  pthread_t t1, t2, t3, t4;

  if(argc < 2) {
    printf("Usage: ./test qps\n");
    return 0;
  }
  int qps = atoi(argv[1]);
  printf("set qps=%d\n", qps);
  tb = token_bucket_create(qps, 1);

  pthread_create(&t1, NULL, &proc, NULL);
  pthread_create(&t2, NULL, &proc, NULL);
  pthread_create(&t3, NULL, &proc, NULL);
  pthread_create(&t4, NULL, &tick, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  token_bucket_destroy(tb);

  return 0;
}
