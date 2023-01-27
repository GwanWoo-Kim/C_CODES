#include <stdio.h>
 
int main( )
{
	int first,second,nband,set;
	FILE *A = NULL;
	FILE *B = NULL; 
	FILE *C = NULL;
	FILE *D = NULL;
	char strTemp[150];
remove("EIGENVAL-up");
remove("EIGENVAL-down");
remove("EIGENVAL-tempt");

    A = fopen( "EIGENVAL", "r" );
    B = fopen( "EIGENVAL-tempt" , "a" );
    C = fopen( "EIGENVAL-up", "a" );
    D = fopen( "EIGENVAL-down", "a" );
    if( A != NULL )
    {
for(first=1 ; first<8 ; first++)
        {
        fgets( strTemp, sizeof(strTemp), A );
	if(first==6)
	printf( "%s", strTemp );
        }
    }
    else
    {
    }
fclose(A);
A = fopen( "EIGENVAL-save", "r" );
printf("\nhowmany band? : ");
scanf("%d",&nband);
nband = nband+2;
printf("\nhowmany set? : ");
scanf("%d",&set);
printf("\n");
for(first=1 ; first<(nband*set)+6+1 ; first++)
        {
        fgets( strTemp, sizeof(strTemp), A );
        if(first>6){
	if((first-6)%nband!=1&&(first-6)%nband!=2)
	{
	fprintf( B, "%d  %s  ",first,strTemp );
	}
	else 
	{
	}
        }
	}
fclose(A);
fclose(B);
	
    B = fopen( "EIGENVAL-tempt" , "r" );
    C = fopen( "EIGENVAL-up", "a" );
    D = fopen( "EIGENVAL-down", "a" );
    float up, down;
    int count, level=1;
nband = nband -2;
for(first=1 ; first<nband*set+1 ; first++){
	fscanf( B, "%d %f %f\n", &count, &up, &down );
	if(first==1){
	fprintf( C, "%d",level);
        fprintf( D, "%d",level);
	fprintf( C, "\t%f", up );
        fprintf( D, "\t%f", down );
	}
	else
	{
	fprintf( C, "\t%f", up ); 
	fprintf( D, "\t%f", down );
	if(count==nband&&first!=nband*set){
	++level;
	fprintf( C, "\n%d",level);
	fprintf( D, "\n%d",level);
	}
	}
	}
fclose(B);
fclose(C);
fclose(D);
//remove("EIGENVAL-tempt");
    return 0;
}
