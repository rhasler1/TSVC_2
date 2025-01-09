#include <immintrin.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "benchmark.h"
#include "common.h"
#include "array_defs.h"

// array definitions
__attribute__((aligned(ARRAY_ALIGNMENT))) real_t flat_2d_array[LEN_2D*LEN_2D];

__attribute__((aligned(ARRAY_ALIGNMENT))) real_t x[LEN_1D];

__attribute__((aligned(ARRAY_ALIGNMENT))) real_t a[LEN_1D],b[LEN_1D],c[LEN_1D],d[LEN_1D],e[LEN_1D],
                                   aa[LEN_2D][LEN_2D],bb[LEN_2D][LEN_2D],cc[LEN_2D][LEN_2D],tt[LEN_2D][LEN_2D];

__attribute__((aligned(ARRAY_ALIGNMENT))) int indx[LEN_1D];

real_t* __restrict__ xx;
real_t* yy;

real_t s273(struct args_t * func_args)
{
    initialise_arrays(__func__);
    gettimeofday(&func_args->t1, NULL);

    for (int nl = 0; nl < iterations; nl++) {
        for (int i = 0; i < LEN_1D; i+=8) {
            __m256 d_vec = _mm256_load_ps(&d[i]);
            __m256 e_vec = _mm256_load_ps(&e[i]);
            __m256 a_vec = _mm256_load_ps(&a[i]);
            __m256 b_vec = _mm256_load_ps(&b[i]);
            __m256 c_vec = _mm256_load_ps(&c[i]);

            __m256 de_mul = _mm256_mul_ps(d_vec, e_vec);
            a_vec = _mm256_add_ps(a_vec, de_mul);
            _mm256_store_ps(&a[i], a_vec);

            __m256 mask = _mm256_cmp_ps(a_vec, _mm256_set1_ps(0.0), _CMP_LT_OS);
            b_vec = _mm256_add_ps(b_vec, _mm256_and_ps(mask, de_mul));
            _mm256_store_ps(&b[i], b_vec);

            de_mul = _mm256_mul_ps(a_vec, d_vec);
            c_vec = _mm256_add_ps(c_vec, de_mul);
            _mm256_store_ps(&c[i], c_vec);
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    gettimeofday(&func_args->t2, NULL);
    return calc_checksum(__func__);
}

typedef real_t(*test_function_t)(struct args_t *);
void time_function(test_function_t vector_func, void * arg_info)
{
    struct args_t func_args = {.arg_info=arg_info};

    double result = vector_func(&func_args);

    double tic=func_args.t1.tv_sec+(func_args.t1.tv_usec/1000000.0);
    double toc=func_args.t2.tv_sec+(func_args.t2.tv_usec/1000000.0);

    double taken = toc-tic;

    printf("%10.3f\t%f\n", taken, result);
}