#include "common.h"

real_t s273(struct args_t * func_args);

typedef real_t(*test_function_t)(struct args_t *);
void time_function(test_function_t vector_func, void * arg_info);
