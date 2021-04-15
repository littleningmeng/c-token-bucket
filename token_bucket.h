#ifndef TOKEN_BUCKET_H
#define TOKEN_BUCKET_H

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>

#define US_PER_SECOND 1000000

#ifdef __cplusplus
extern "C" {
#endif

typedef struct token_bucket {
  uint64_t last_take_time;
  uint64_t unit_time;
  uint64_t burst_unit_time;
} token_bucket_t;

token_bucket_t *token_bucket_create(const uint64_t qps, const size_t size);
bool token_bucket_try_take(token_bucket_t *tb, const size_t tokens);
void token_bucket_take(token_bucket_t *tb, const size_t tokens);
void token_bucket_destroy(token_bucket_t *tb);

#ifdef __cplusplus
}
#endif
#endif

