int setA(const int n, const int m, double *M);
int setB(const int n, double *M);
int getB(const int n, const int t, const int tNum, double *iM, double *oM);
int printM(const int n, const int m, double *M, const char *str);
double getDelta(const int n, double *A, double *B);
long int get_time();
void synchronize (int total_threads);
