#include <stdio.h>
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
    printf("===============\n");
  }
}

int main(int argc, char *argv[]) {
  pthread_t t1, t2, t3, t4;

  tb = token_bucket_create(2, 1);

  pthread_create(&t1, NULL, &proc, NULL);
  pthread_create(&t2, NULL, &proc, NULL);
  pthread_create(&t3, NULL, &proc, NULL);
  pthread_create(&t4, NULL, &tick, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
