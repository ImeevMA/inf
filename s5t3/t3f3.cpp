#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "t3.h"

int getUB(const int n, const int k, const int kMin, const int kMax, double *iM, double *oM);
int getUA(const int n, const int k, const int kMin, const int kMax, double *oM);
double getV(const int n, const int k, double *M);
int getD (const int n, const int t, const int kMin, const int kMax, double *iM, double *oM);

int getB(const int n, const int t, const int tNum, double *iM, double *oM) {
    int i = 0;
    int kMin = n * tNum / t;
    int kMax = n * (tNum + 1) / t;
    while(i < n - 1) {
        double temp = 0.;
        if(tNum == 0) temp = getV(n, i, iM);
        synchronize(t);
        getUB(n, i, kMin, kMax, iM, oM);
        int jMin = i + 1 + (n - i - 1) * tNum / t;
        int jMax = i + 1 + (n - i - 1) * (tNum + 1) / t;
        getUA(n, i, jMin, jMax, iM);
        synchronize(t);
        if(tNum == 0) iM[i + n * i] = temp;
        ++i;
    }
    getD(n, t, kMin, kMax, iM, oM);
    return 0;
}

int getD (const int n, const int t, const int kMin, const int kMax, double *iM, double *oM) {
    int i = kMin;
    while(i < kMax) {
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
    synchronize(t);
    i = n - 1;
    while(i > 0) {
        int j = 0;
        while(j < i) {
            int k = kMin;
            while(k < kMax) {
                oM[k + j * n] -= iM[i + j * n] * oM[k + i * n];
                ++k;
            }
            ++j;
        }
        --i;
    }
    return 0;
}

int getUA(const int n, const int k, const int kMin, const int kMax, double *M) {
    int i = kMin;
    while(i < kMax) {
        double tmp = 0.;
        int j = k;
        while(j < n) {
            tmp += M[k + j * n] * M[i + j * n];
            ++j;
        }
        tmp *= 2;
        j = k;
        while(j < n) {
            M[i + j * n] -= tmp * M[k + j * n];
            ++j;
        }
        ++i;
    }
    return 0;
}

int getUB(const int n, const int k, const int kMin, const int kMax, double *V, double *M) {
    int i = kMin;
    while(i < kMax) {
        double tmp = 0.;
        int j = k;
        while(j < n) {
            tmp += V[k + j * n] * M[i + j * n];
            ++j;
        }
        tmp *= 2;
        j = k;
        while(j < n) {
            M[i + j * n] -= tmp * V[k + j * n];
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
