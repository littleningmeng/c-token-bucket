#include "token_bucket.h"
#include <stdlib.h>

static uint64_t time_us() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * US_PER_SECOND + t.tv_usec;
}

token_bucket_t *token_bucket_create(const uint64_t qps, const size_t size) {
  token_bucket_t *tb = (token_bucket_t *)malloc(sizeof(token_bucket_t));
  tb->last_take_time = 0;
  tb->unit_time = US_PER_SECOND / qps;
  tb->burst_unit_time = size * tb->unit_time;
  return tb;
}

bool token_bucket_try_take(token_bucket_t *tb, const size_t tokens) {
  const uint64_t now = time_us();
  const uint64_t needs_time = tokens * tb->unit_time;
  const uint64_t min_time = now - tb->burst_unit_time;
  uint64_t old_time = tb->last_take_time;
  uint64_t new_time = old_time;
  if(min_time > old_time) {
    new_time = min_time;
  }
  new_time += needs_time;
  if(new_time > now) {
    return false;
  }
  return __sync_bool_compare_and_swap(&tb->last_take_time, old_time, new_time);
}

void token_bucket_take(token_bucket_t *tb, const size_t tokens) {
  while(1) {
    if(!token_bucket_try_take(tb, 1)) {
      sleep(0);
    } else {
      break;
    }
  }
}

void token_bucket_destroy(token_bucket_t *tb) {
  if(tb == NULL) {
    free(tb);
    tb = NULL;
  }
}

