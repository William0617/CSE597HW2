#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>


int main(int argc, char *argv[])
{
	int m = 500;
	int n = 500;
	double tol = 0.0001;
	int i, j, iter;
	int nthreads = 8;  // Initilise  number of threads

	double t[m+2][n+2], tnew[m+1][n+1], diff, difmax;      // parallel Array
	double s[m+2][n+2], snew[m+1][n+1];                   // Serial Array
	double sub[m+2][m+2];                                // (Serial-Parallel)o/p will be shown here
	omp_set_num_threads(nthreads);
													// initialise array
	for (i=0; i <= m+1; i++) {
		 for (j=0; j <= n+1; j++) {
		 	t[i][j] = 30.0;
		}
	}


	for (i=1; i <= m; i++)
		for (j=1; j <= n; j++) {
		 	t[i][0] = 10.0;
		 	t[i][n+1] = 140.0;
		 	t[0][j] = 20.0;
		 	t[m+1][j] = 100.0;
		 }


	#pragma omp parallel default(shared) private(i,j,diff)
	 {
		// main loop
	 	iter = 0;
	 	difmax = 1000000.0;
		while (difmax > tol) {
			iter++;
			// update values for next iteration
			#pragma omp for schedule(static) collapse(2)
			for (i=1; i <= m; i++) {
				for (j=1; j <= n; j++) {
					tnew[i][j] = (t[i-1][j]+t[i+1][j]+t[i][j-1]+t[i][j+1])/4.0;
				}
			}
			// work out maximum difference between old and new values
			difmax = 0.0;
			#pragma omp for schedule(static) collapse(2)
			for (i=1; i <= m; i++) {
				for (j=1; j <= n; j++) {
						diff = fabs(tnew[i][j]-t[i][j]); 
						if (diff > difmax) {
						#pragma omp critical
						difmax = diff;
					}
					// copy new to old values
					t[i][j] = tnew[i][j];
				}
			}
		}
 	}
}
