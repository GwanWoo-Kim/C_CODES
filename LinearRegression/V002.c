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

void delay(clock_t n)

{
  clock_t start = clock();
  while(clock() - start < n);
}

void main()
{
srand(time(NULL));
double k;
for(k=1;k<=9;k++)
{
int n = 1000 ;
double xmin= -1*k , xmax= +1*k;
double ymin= -1*k , ymax= +1*k;
double M = drand(-3*k,+3*k);
double x[n],y[n];
double Ycont=drand(-0.1,+0.1);
double Slope=drand(-0.1,+0.1);
double alpha = 1E-4;
double p;
double a;
double RMSE;
double error;
int i =0,j=0;
for(i=0; i < n; i ++)
{       
	x[i]=drand(xmin,xmax);
	delay(1);
	a=drand(-1*k,+1*k);
	if(a>=-1*k && a<=-1*k/3)
	{y[i]=drand(-1.0*k,-0.6*k)+x[i]*M;
	delay(1);}
	if(a>-1*k/3 && a<+1*k/3)
	{y[i]=drand(-0.2*k,+0.2*k)+x[i]*M;
	delay(1);}
	if(a>=+1*k/3 && a<=+1*k)
	{y[i]=drand(+0.6*k,+1.0*k)+x[i]*M;
	delay(1);}
}

while(j<100000*n)
{
for (i = 0; i < n; i ++) 
{
    p =  Slope * x[i] + Ycont;
    error = p - y[i];
    Ycont = Ycont - alpha * error;
    Slope = Slope - alpha * error * x[i];
    j++;
}
}

for (i = 0; i < n; i ++)
{ 
    p= Slope * x[i] + Ycont;
    error = p - y[i];
    RMSE +=pow(error,2);
}
RMSE=sqrt(RMSE/n);



FILE *A = NULL;
if (k==1)
A = fopen( "./DATA_save1.txt", "w" );
if (k==2)
A = fopen( "./DATA_save2.txt", "w" );
if (k==3)
A = fopen( "./DATA_save3.txt", "w" );
if (k==4)
A = fopen( "./DATA_save4.txt", "w" );
if (k==5)
A = fopen( "./DATA_save5.txt", "w" );
if (k==6)
A = fopen( "./DATA_save6.txt", "w" );
if (k==7)
A = fopen( "./DATA_save7.txt", "w" );
if (k==8)
A = fopen( "./DATA_save8.txt", "w" );
if (k==9)
A = fopen( "./DATA_save9.txt", "w" );


for(i=0;i<n;i++) 
{
fprintf(A," %15.12lf   %15.12lf  \n",x[i],y[i]);
}

fclose(A);

A = fopen("./VIS","w");
fprintf(A,"set term postscript eps color enhanced\n");
fprintf(A,"set output \"VISUALLIZING%1.0lf.eps\" \n",k);
fprintf(A,"set xr [%lf:%lf]\n",xmin*1.5,xmax*1.5);
fprintf(A,"set yr [%lf:%lf]\n",ymin*1.5,ymax*1.5);
fprintf(A,"set yzeroaxis lw 4\n");
fprintf(A,"set xzeroaxis lw 4\n");
fprintf(A,"set tmargin 3\n");
fprintf(A,"set bmargin 6\n");
fprintf(A,"set lmargin 12\n");
fprintf(A,"set rmargin 6\n");
fprintf(A,"f(x) =(%4.2lf)*x+%4.2lf   \n",Slope,Ycont);
fprintf(A,"set xlabel 'X, RMSE = %4.3lf' font \"Arial, 36\" offset 0,-1.5,0\n",RMSE);
fprintf(A,"set ylabel 'Y' font \"Arial, 36\" offset -2,0,0\n");
fprintf(A,"plot   \"DATA_save%1.0lf.txt\" using ($1):($2) w p lc rgb \"#00FF00\" title 'data' ,\\\n",k);
fprintf(A,"       f(x)  lw 2 lc rgb \"#FF0000\" title 'y=%4.2lfx+%4.2lf'   \n",Slope,Ycont);

fclose(A); 
system("gnuplot VIS");
}

}
