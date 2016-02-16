#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include "t3.h"

double myF(const int i, const int j) {
    return (double) 1 / (i + j + 1);
}

int setA(const int n, const int m, double *myM) {
    if(m == 1) {
        char tIn[] = "matrix.txt";
        FILE* fIn = fopen(tIn, "rt");
        if(fIn == NULL) return -4;
        int i = 0;
        while(i < n) {
            int j = 0;
            while(j < n) {
                if(fscanf(fIn, "%lf", &myM[j + n * i]) < 1) {
                    fclose(fIn);
                    return -2;
                }
                ++j;
            }
            ++i;
        }
	fclose(fIn);
    } else {
        int i = 0;
        while(i < n) {
            int j = 0;
            while(j < n) {
                myM[j + n * i] = myF(i, j);
                ++j;
            }
            ++i;
        }
    }
    return 0;
}

int setB(const int n, double *myM) {
    int i = 0;
    while(i < n) {
        int j = 0;
	while(j < n) {
	    if(i == j) myM[i + n * j] = 1.; else myM[i + n * j] = 0.;
	    ++j;
	}
	++i;
    }
    return 0;
}

int printM(const int n, const int m, double *myM, const char *str) {
    if(printf("%s", str) < 1) return -1;
    int i = 0;
    int k = n;
    if(m < n) k = m;
    while(i < k) {
        int j = 0;
        while(j < k) {
            if(printf("%.1g\t", myM[j + n * i]) < 1) return -1;
            ++j;
        }
        if(printf("\n") < 1) return -1;
        ++i;
    }
    return 0;
}

double getDelta(const int n, double *A, double *B) {
    double mDelta = 0.;
    int i = 0;
    while(i < n) {
        int j = 0;
        double vDelta = 0.;
	    while(j < n) {
	        double tmp = 0.;
	        int k = 0;
	        while(k < n) {
	            tmp += A[k + n * i] * B[j + n * k];
        		++k;
	        }
            if(i == j) tmp -= 1.;
            vDelta += fabs(tmp);
	        ++j;
	    }
        if(mDelta < vDelta) mDelta = vDelta;
	    ++i;
    }
    return mDelta;
}

long int get_time() {
    struct timeval buf;
    gettimeofday(&buf, 0);
    return 1000000 * buf.tv_sec + buf.tv_usec;
}

void synchronize (int total_threads) {
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
    static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
    static int threads_in = 0;
    static int threads_out = 0;
    
    pthread_mutex_lock(&mutex);
    ++threads_in;
    if(threads_in >= total_threads) {
        threads_out = 0;
        pthread_cond_broadcast (&condvar_in);
    } else {
        while(threads_in < total_threads)
            pthread_cond_wait (&condvar_in, &mutex);
    }
    ++threads_out;
    if(threads_out >= total_threads) {
        threads_in = 0;
        pthread_cond_broadcast (&condvar_out);
    } else {
        while(threads_out < total_threads)
            pthread_cond_wait (&condvar_out, &mutex);
    }
    pthread_mutex_unlock (&mutex);
}
