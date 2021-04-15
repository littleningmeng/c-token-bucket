# c-token-bucket
a ratelimiter with token bucket written by c  
lock-free with CAS  
```c
#include "token_bucket.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  token_bucket_t *tb;
  tb = token_bucket_create(1, 1); // create with QPS=1 and bucket size=1
  while(1) {
    token_bucket_take(tb, 1); // take 1 token per second
    printf("hello\n");
  }
  return 0;
}
```

