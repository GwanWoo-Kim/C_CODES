#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
int main( )
{
	int first,second,set1,set2,dumpA,dumpB;
	FILE *B = NULL; 
	FILE *C = NULL;
	FILE *D = NULL;
	char strTemp[90];
	double dX,dY,dZ,distance;
remove("POSCAR_D");
    B = fopen( "POSCAR_B", "r" );
    C = fopen( "POSCAR_C", "r" );
    D = fopen( "POSCAR_D", "a" );               
for(first=1 ; first<99 ; first++)             
    {                                         
    fgets( strTemp, sizeof(strTemp), C );     
    }                                         
                                              
printf("how many atoms in 1 kind? : ");       
scanf("%d",&set1);                            
printf("\n");                                 
printf("how many atoms in 2 kind? : ");       
scanf("%d",&set2);                            
printf("\n");                                 

    double setA[3][set1], setB[3][set2];

fclose(B);
fclose(C);
    B = fopen( "POSCAR_B", "r" );
    C = fopen( "POSCAR_C", "r" );

for(first=1 ; first<set1+1 ; first++)
{
fscanf( C, "%d %lf %lf %lf \n",&dumpA ,&setA[0][first-1] ,&setA[1][first-1] ,&setA[2][first-1]);
printf("%3d %lf %lf %lf \n",dumpA,setA[0][first-1],setA[1][first-1],setA[2][first-1]);
}
for(second=1;second<set2+1 ;second++)
{
fscanf( B, "%d %lf %lf %lf \n",&dumpB ,&setB[0][second-1] ,&setB[1][second-1] ,&setB[2][second-1]);
//printf("%3d %lf %lf %lf\n",dumpB,setB[0][second-1],setB[1][second-1],setB[2][second-1]);
}
	for(second=1 ;second<set2+1 ;second++)
	{
	for( first=1 ; first<set1+1 ; first++)
	{
	dX=setA[0][first-1]-setB[0][second-1];
	dY=setA[1][first-1]-setB[1][second-1];
	dZ=setA[2][first-1]-setB[2][second-1];
	distance = sqrt(dX*dX+dY*dY+dZ*dZ);
	if(distance<3.0)
	{
//	fprintf( D,"%lf \t %lf \t %lf \t %lf \n",distance,dX,dY,dZ);
	fprintf( D,"%3d \t %lf \t %lf \t %lf \n",second,setB[0][second-1],setB[1][second-1],setB[2][second-1]);
	break;
	}
	}
	}
fclose(D);
return 0;

}

