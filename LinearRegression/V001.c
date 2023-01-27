#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h> 

double drand(double low, double high)   
{   
    double d;   
    d = (double) rand() / RAND_MAX;  
    return (low + d * (high - low));   
}   


void main() 
{ 
	double X[10];
	double Y[10]; 
	double INI;
	double lr = 1.0E-3; 
	double a = 3; 
	double b = 0; 
	double delta_a; 
	double delta_b; 
	int i,n=0; 
	double previous_error = 999; 
	double error = 0 ;
	double xmax=6,xmin=3;
	double ymax=9,ymin=0;
srand(time(NULL));
for(i=0;i<10;i++) //Initializing the data set using random function.
{
	X[i]=drand(xmin,xmax);
	Y[i]=drand(ymin,ymax);
	printf("%f\n",X[i]);
}
while (1)  //break condition
{ 
	delta_a = 0; 
	delta_b = 0; 
	for (int i = 0; i < 10; i++) 
	{ 
		double y ;
		y = a * X[i] + b; 
		delta_a += (Y[i] - y)*X[i]; 
		delta_b += (Y[i] - y); 
	} 
	
	a = a + lr * delta_a; 
	b = b + lr * delta_b;
       
	for (int i = 0; i < 10; i++) 
	{ 
	       double d ;
		d = (Y[i] - a*X[i] - b)*(Y[i] - a*X[i] - b); 
	       error += d; 
        } 
       
        error = error / 10.0; 
        n++; 
        if(fabs(previous_error - error)<=1.0E-4)
	{
		printf("%d \t %1.6lf \t %1.2lf \t %1.2lf \t %1.2lf \n", n, previous_error,error, a, b);
		break;
	}
	previous_error = error;

}
}
