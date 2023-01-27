#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
int main( )
{
	int first,second,set1,set2,dumpA,dumpB;
	FILE *A = NULL;
	FILE *B = NULL; 
	FILE *C = NULL;
	FILE *D = NULL;
	char strTemp[90];
	double dX,dY,dZ,distance;
remove("POSCAR_C");
	A = fopen( "POSCAR_A", "r" );
    B = fopen( "POSCAR_B", "r" );
    C = fopen( "POSCAR_C", "a" );
    D = fopen( "POSCAR", "r" );               
remove("POSCAR_C"); 
for(first=1 ; first<15 ; first++)             
    {                                         
    fgets( strTemp, sizeof(strTemp), D );     
    if(first>5&&first<8)                      
    printf(" %3d \t %s \n",first,strTemp );   
    }                                         
                                              
printf("how many atoms in 1 kind? : ");       
scanf("%d",&set1);                            
printf("\n");                                 
printf("how many atoms in 2 kind? : ");       
scanf("%d",&set2);                            
printf("\n");                                 

    double setA[3][set1], setB[3][set2];

for(first=1 ; first<set1+1 ; first++)
fscanf( A, "%d %lf %lf %lf \n",&dumpA ,&setA[0][first-1] ,&setA[1][first-1] ,&setA[2][first-1]);
for(second=1;second<set2+1 ;second++)
fscanf( B, "%d %lf %lf %lf \n",&dumpB ,&setB[0][second-1] ,&setB[1][second-1] ,&setB[2][second-1]);
//printf("how many atoms in 1 kind? :%lf ",setB[1][400]);
	for(first=1 ; first<set1+1 ; first++)
	{
	for(second=1;second<set2+1 ;second++)
	{
	dX=setA[0][first-1]-setB[0][second-1];
	dY=setA[1][first-1]-setB[1][second-1];
	dZ=setA[2][first-1]-setB[2][second-1];
	distance = sqrt(dX*dX+dY*dY+dZ*dZ);
	if(distance<3.0)
	{
//	fprintf( C,"%lf \t %lf \t %lf \t %lf \n",distance,dX,dY,dZ);
	fprintf( C,"%3d \t %lf \t %lf \t %lf \n",first,setA[0][first-1],setA[1][first-1],setA[2][first-1]);
	break;
	}
	}
	}
fclose(C);
return 0;

}

