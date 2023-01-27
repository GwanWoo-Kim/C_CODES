#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
int main( )
{
	int first,set1,set2;
	FILE *A = NULL;
	FILE *B = NULL; 
	FILE *C = NULL;
	FILE *D = NULL;
	char strTemp[90];

remove("POSCAR_A");
remove("POSCAR_B");
remove("POSCAR_C");

    D = fopen( "POSCAR", "r" );
    A = fopen( "POSCAR_A", "a" );
    B = fopen( "POSCAR_B", "a" );
    C = fopen( "POSCAR_C", "a" );

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

fclose(D);
D = fopen( "POSCAR", "r" );

for(first=1 ; first<9+1+set1+set2; first++)
	{
    fgets( strTemp, sizeof(strTemp), D );
	if(first > 8&& first <=8+set1)
	fprintf( A, "%3d \t %s",first-8,strTemp );
	if(first > 8+set1 && first <=8+set1+set2) 
	fprintf( B, "%3d \t %s",first-8-set1,strTemp );
	}

/*

	C = fopen( "POSCAR_C", "a" );
	A = fopen( "POSCAR_A", "r" );
	B = fopen( "POSCAR_B", "r" );

for(first=1 ; first<set1+1 ; first++)
	{
    fscanf( A, "%d %lf %lf %lf \n",&dumpA ,&setA[0] ,&setA[1] ,&setA[2]);
	B = fopen( "POSCAR_B", "r" );
	for(second=1;second<set2+1 ;second++)
	{
    fscanf( B, "%d %lf %lf %lf \n",&dumpB ,&setB[0] ,&setB[1] ,&setB[2]);
	dX=setA[0]-setB[0];
	dY=setA[1]-setB[1];
	dZ=setA[2]-setB[2];
	distance=sqrt(dX*dX+dY*dY+dZ*dZ);
	printf("%3d %lf\n",dumpB ,distance);
	fflush(stdin);
	}
	fclose(B);
	}
*/
fclose(A);
fclose(B);
fclose(C);
fclose(D);
return 0;

}

