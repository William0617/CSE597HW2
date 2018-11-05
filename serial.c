#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define m 500
#define n 500
#define tol 0.0001
double t[m+2][n+2];
double tnew[m+1][n+1];
double diff, difmax;

void getMatrix()
{
    // initialise array
    for (int i=0; i <= m+1; i++) {
        for (int j=0; j <= n+1; j++) {
            t[i][j] = 30.0;
        }
    }
    //boundary conditions
    for (int i=1; i <= m; i++) {
        t[i][0] = 10.0;
        t[i][n+1] = 140.0;
    }
    for (int j=1; j <= n; j++) {
        t[0][j] = 20.0;
        t[m+1][j] = 100.0;
    }
}

void Jacobi()
{
    difmax = 1000000.0;
    // main loop
    int iter = 0;
    while (difmax > tol) {
        iter++;
        // update values for next iteration
        for (int i=1; i <= m; i++) {
            for (int j=1; j <= n; j++) {
                tnew[i][j] = (t[i-1][j]+t[i+1][j]+t[i][j-1]+t[i][j+1])/4.0;
            }
        }
        // work out maximum difference between old and new values
        difmax = 0.0;
        for (int i=1; i <= m; i++) {
            for (int j=1; j <= n; j++) {
                diff = fabs(tnew[i][j]-t[i][j]);
                if (diff > difmax) {
                    difmax = diff;
                }
                // copy new to old values
                t[i][j] = tnew[i][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    getMatrix();
    Jacobi();
}
