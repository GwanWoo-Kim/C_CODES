#include <stdio.h>
#include <math.h>
int main()
{
int i,D_A,D_D,m;
double a[100002],b[100002],c[100002],d[100002],f[100002],Interval;
double k = 8.61734315E-5 ; //(eV/K)
double e = 1.60217656E-19 ; //(C)
double T=300,N_dA,N_dD,N_iA,N_iD,V_0;
double X_A,X_D,e_A,e_D;
double E_iA,E_iD,E_iF=0;
FILE *fp;
fp=fopen("poisson.dat","w");
Interval=1E-6; //total 1 micro, interval = 1 angstrom represented by 1cm

printf("\n P type side Doping density?{unit is #/cubic cm}	(example 1.00E+18) = ");
scanf("%lf",&N_dA);
printf("\n P type side intrinsic density?{unit is #/cubic cm}	(example 1.50E+10) = ");
scanf("%lf",&N_iA);
printf("\n P type side relative permittivity?			(example 1.18E1 ) = ");
scanf("%lf",&e_A);
printf("\n N type side Doping density?{unit is #/cubic cm}	(example 5.00E+15) = ");
scanf("%lf",&N_dD);
printf("\n N type side intrinsic density?{unit is #/cubic cm}	(example 1.50E+10) = ");
scanf("%lf",&N_iD);
printf("\n N type side relative permittivity?			(example 1.18E1 ) = ");
scanf("%lf",&e_D);

/*
N_dA	= 1E18		;
N_iA	= 1.5E10	;
e_A	= 1.18E1	;
N_dD	= 5E15		;
N_iD	= 1.5E10	;
e_D	= 1.18E1	;
*/
e_A = e_A*8.85E-14; 
e_D = e_D*8.85E-14; 
E_iA = k*T*log(N_dA/N_iA) + E_iF ; // E difference from fermi in P side
E_iD = E_iF - k*T*log(N_dD/N_iD) ; // E difference from fermi in N side 
V_0 = E_iA - E_iD ; // Voltage diffence P-N
X_A = sqrt((2*e_A*V_0/e)*(N_dD/(N_dA*(N_dA+N_dD))));//P side depletion length (cm)
X_D = sqrt((2*e_D*V_0/e)*(N_dA/(N_dD*(N_dA+N_dD))));//N side depletion length (cm)
/*
//checking the calculation part.
printf("\n V0 = %E(eV)",V_0);
printf("\n E_iA = %E(eV)",E_iA);
printf("\n E_iD = %E(eV)",E_iD);
*/
D_A = (int)(X_A/Interval);//angstrom per length 
D_D = (int)(X_D/Interval);//angstrom per length 
printf("\n depletion length in P side %E (cm),\t total charge = %E (C),\t D_A=%4d,\t Pside Vp :%E (eV)",X_A,N_dA*X_A*e*7.85E-7,D_A,E_iA);
printf("\n depletion length in N side %E (cm),\t total charge = %E (C),\t D_D=%4d,\t Nside Vn :%E (eV)",X_D,N_dD*X_D*e*7.85E-7,D_D,E_iD);

for(i=0;i<=100001;i++)
 	{
 		c[i]=0;
		if(i<50000&&i>50000-D_A)c[i]=  -1.0E00*N_dA;//(cm^3 -> cm)
		if(i>=50001&&i<50001+D_D)c[i]= +1.0E00*N_dD;//(cm^3 -> cm)
//		a[i]=E_iD;
//		d[i]=E_iD;
		if(i<=50001) a[i]=E_iD;
                if(i>=50001) a[i]=0;

		if(i>=50001) d[i]=E_iA;
                if(i<=50001) d[i]=0;
		
		b[i]=0;
		f[i]=0;
 	}
//for(m=1;m<500;m++)
//{
for(i=1;i<=50000;i++)
b[i]=b[i-1]+(c[i-1])*Interval*e/e_A;
//for(i=50001;i<=100000;i++)
//b[i]=b[i-1]+(c[i-1])*Interval*e/e_D/3.0;
for(i=1;i<=50000;i++)
a[i]=(a[i-1]-(b[i-1])*Interval);
for(i=100000;i>=50001;i--)
f[i]=f[i+1]-(c[i+1])*Interval*e/e_D;
//for(i=50000;i>=1;i--)
//f[i]=f[i+1]-(c[i+1])*Interval*e/e_A/3.0;
for(i=100000;i>=50001;i--)
d[i]=(d[i+1]+(f[i+1])*Interval);

for(i=1;i<=100000;i++)
{
a[i]=(a[i]+d[i])/1.0;
b[i]=(b[i]+f[i])/1.0;
}
//}
//calculation by Gauss-Seidel Method
printf("\nDONE!!!\n");
printf("recording the data in poisson.dat file\n");
for(i=0;i<=100001;i++)
{
fprintf(fp,"%5d \t %15.14E \t %15.14E \t %15.14E  \n",i,a[i],b[i],c[i]);
}
printf("\nall process is fully DONE!!!\n");
return 0;
}
