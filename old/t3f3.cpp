#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "t3.h"

int getUB(int n, int k, double *iM, double *oM);
int getUA(int n, int k, double *oM);
double getV(const int n, const int k, double *M);
int getD (const int n, double *iM, double *oM);

int getB(const int n, double *iM, double *oM) {
    long int time = getTime();
    int i = 0;
    while(i < n - 1) {
        double temp = getV(n, i, iM);
        getUB(n, i, iM, oM);
        getUA(n, i, iM);
        iM[i + n * i] = temp;
        ++i;
    }
    time = getTime() - time;
    printf("Time 1: %li sec %li usec\n", time / 1000000, time % 1000000);
    getD(n, iM, oM);
    return 0;
}

int getD (const int n, double *iM, double *oM) {
    int i = 0;
    while(i < n) {
       double tmp = iM[i + i * n];
       int j = i;
       while(j < n) {
           iM[j + i * n] = iM[j + i * n] / tmp;
           ++j;
       }
       j = 0;
       while(j < n) {
           oM[j + i * n] = oM[j + i * n] / tmp;
           ++j;
       }
       ++i;
    }
    i = n - 1;
    while(i > 0) {
        int j = 0;
        while(j < i) {
            int k = 0;
            while(k < n) {
                oM[k + j * n] -= iM[i + j * n] * oM[k + i * n];
                ++k;
            }
            ++j;
        }
        --i;
    }
    return 0;
}

int getUA(int n, int k, double *M) {
    int i = k + 1;
    while(i < n) {
        double tmp = 0.;
        int j = k;
        while(j < n) {
            tmp += M[k + j * n] * M[i + j * n];
            ++j;
        }
        j = k;
        while(j < n) {
            M[i + j * n] -= 2 * tmp * M[k + j * n];
            ++j;
        }
        ++i;
    }
    return 0;
}

int getUB(int n, int k, double *V, double *M) {
    int i = 0;
    while(i < n) {
        double tmp = 0.;
        int j = k;
        while(j < n) {
            tmp += V[k + j * n] * M[i + j * n];
            ++j;
        }
        j = k;
        while(j < n) {
            M[i + j * n] -= 2 * tmp * V[k + j * n];
            ++j;
        }
        ++i;
    }
    return 0;
}

double getV(const int n, const int k, double *M) {
    double tmp = 0.;
    double tmp2;
    int i = k + 1;
    while(i < n) {
        tmp += fabs(M[k + i * n]) * fabs(M[k + i * n]);
        ++i;
    }
    tmp2 = sqrt(M[k + k * n] * M[k + k * n] + tmp);
    M[k + k * n] -= tmp2;
    tmp = sqrt(M[k + k * n] * M[k + k * n] + tmp);
    i = k;
    while(i < n) {
        M[k + i * n] /= tmp;
        ++i;
    }
    return tmp2;
}
