#include<stdio.h>
#include<math.h>
#define X 100
#define T 100
double fun(int x)
{
    return sin(x);
 
}
int main()
{
	FILE data*;
	
    double u[X+1][T+1],square_of_c, ut, ue;
    int i,j;
    printf("\n Enter the square of c: ");
    scanf("%lf",&square_of_c);
    printf(" Enter the value of u[0][t]:");
    scanf("%lf",&ut);
    printf(" Enter the value of u[%d][t]:",X);
    scanf("%lf",&ue);
    for(j=0;j<=T;j++)
    {
        u[0][j]=ut;
        u[X][j]=ue;
    }
    for(i=1;i<=X-1;i++)
    u[i][1]=u[i][0]=fun(i);
    for(j=1;j<=T-1;j++)
    for(i=1;i<=X-1;i++)
    u[i][j+1]=u[i-1][j]+u[i+1][j]-u[i][j-1];
    printf(" The values of u[i][j] are: \n");
    for(j=0;j<=T;j++)
    {
        for(i=0;i<=X;i++)
        printf("%6.1f",u[i][j]);
        printf("\n");
 
    }
 
}
