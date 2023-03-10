# include <stdio.h>
# include <math.h>
# include <time.h>

int main ( );
double f ( double x );
double g ( double x );
void timestamp ( );

/******************************************************************************/

int main ( )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for STRING_SIMULATION.

  Discussion:

    This program solves the 1D wave equation of the form:

      Utt = c^2 Uxx

    over the spatial interval [X1,X2] and time interval [T1,T2],
    with initial conditions:

      U(T1,X)  = U_T1(X),
      Ut(T1,X) = UT_T1(X),

    and boundary conditions of Dirichlet type:

      U(T,X1) = U_X1(T),
      U(T,X2) = U_X2(T).

    The value C represents the propagation speed of waves.

    The program uses the finite difference method, and marches
    forward in time, solving for all the values of U at the next
    time step by using the values known at the previous two time steps.

    Central differences may be used to approximate both the time
    and space derivatives in the original differential equation.

    Thus, assuming we have available the approximated values of U
    at the current and previous times, we may write a discretized
    version of the wave equation as follows:

      Uxx(T,X) = ( U(T,   X+dX) - 2 U(T,X) + U(T,   X-dX) ) / dX^2
      Utt(T,X) = ( U(T+dt,X   ) - 2 U(T,X) + U(T-dt,X   ) ) / dT^2

    If we multiply the first term by C^2 and solve for the single
    unknown value U(T+dt,X), we have:

      U(T+dT,X) =        (     C^2 * dT^2 / dX^2 ) * U(T,   X+dX)
                  +  2 * ( 1 - C^2 * dT^2 / dX^2 ) * U(T,   X   )
                  +      (     C^2 * dT^2 / dX^2 ) * U(T,   X-dX)
                  -                                  U(T-dT,X   )

    (Equation to advance from time T to time T+dT, except for FIRST step)

    However, on the very first step, we only have the values of U
    for the initial time, but not for the previous time step.
    In that case, we use the initial condition information for dUdT
    which can be approximated by a central difference that involves
    U(T+dT,X) and U(T-dT,X):

      dU/dT(T,X) = ( U(T+dT,X) - U(T-dT,X) ) / ( 2 * dT )

    and so we can estimate U(T-dT,X) as

      U(T-dT,X) = U(T+dT,X) - 2 * dT * dU/dT(T,X)

    If we replace the "missing" value of U(T-dT,X) by the known values
    on the right hand side, we now have U(T+dT,X) on both sides of the
    equation, so we have to rearrange to get the formula we use
    for just the first time step:

      U(T+dT,X) =   1/2 * (     C^2 * dT^2 / dX^2 ) * U(T,   X+dX)
                  +       ( 1 - C^2 * dT^2 / dX^2 ) * U(T,   X   )
                  + 1/2 * (     C^2 * dT^2 / dX^2 ) * U(T,   X-dX)
                  +  dT *                         dU/dT(T,   X   )

    (Equation to advance from time T to time T+dT for FIRST step.)

    It should be clear now that the quantity ALPHA = C * DT / DX will affect
    the stability of the calculation.  If it is greater than 1, then
    the middle coefficient 1-C^2 DT^2 / DX^2 is negative, and the
    sum of the magnitudes of the three coefficients becomes unbounded.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    25 December 2012

  Author:

    John Burkardt

  Local Parameters:

    Local, double ALPHA, the CFL stability parameter.

    Local, double C, the wave speed.

    Local, double DT, the time step.

    Local, double DX, the spatial step.

    Local, int M, the number of time steps.

    Local, int N, the number of spatial intervals.

    Local, double T1, T2, the initial and final times.

    Local, double U[M+1][N+1], the computed solution.

    Local, double X1, X2, the left and right spatial endpoints.
*/
{
# define m 250 
# define n 500

  double alpha;
  double c =  1.10;
  FILE *command_unit;
  FILE *data_unit;
  double dt;
  double dx;
  int i;
  int j;
  double t;
  double t1 =   0.0;
  double t2 =  45.0;
  double u[m+1][n+1];
  double x;
  double x1 = 0.0;
  double x2 = 100.0;

  timestamp ( );
  printf ( "\n" );
  printf ( "STRING_SIMULATION:\n" );
  printf ( "  C version\n" );
  printf ( "  Simulate the behavior of a vibrating string.\n" );

  dx = ( x2 - x1 ) / ( double ) n;
  dt = ( t2 - t1 ) / ( double ) m;
  alpha = pow ( c * dt / dx, 2 );
  printf ( "  ALPHA = ( C * dT / dX )^2 = %g\n", alpha );
/*
  Warn the user if ALPHA will cause an unstable computation.
*/
  if ( 1.0 < alpha )
  {
    printf ( "\n" );
    printf ( "  Warning!\n" );
    printf ( "  ALPHA is greater than 1.\n" );
    printf ( "  The computation is unstable.\n" );
  }
/*
  Time step 0: 
  Use the initial condition for U.
*/
  u[0][0] = 0.0;
  for ( j = 1; j < n; j++ )
  {
    x = j * dx;
    u[0][j] = f ( x );
  }
  u[0][n] = 0.0;
/*
  Time step 1:
  Use the initial condition for dUdT.
*/
  u[1][0] = 0.0;
  for ( j = 1; j < n; j++ )
  {
    x = j * dx;
    u[1][j] = 
        ( alpha / 2.0 ) * u[0][j-1]
      + ( 1.0 - alpha ) * u[0][j] 
      + ( alpha / 2.0 ) * u[0][j+1]
      + dt * g ( x );
  }
  u[1][n] = 0.0;
/*
  Time steps 2 through M:
*/
  for ( i = 2; i <= m; i++ )
  {
    u[i][0] = 0.0;
    for ( j = 1; j < n; j++ )
    {
      u[i][j] = 
                        alpha   * u[i-1][j-1]
        + 2.0 * ( 1.0 - alpha ) * u[i-1][j] 
        +               alpha   * u[i-1][j+1]
        -                         u[i-2][j];
    }
    u[i][n] = 0.0;
  }
/*
  Write data file.
*/
  data_unit = fopen ( "string_data.txt", "wt" );

  for ( i = 0; i <= m; i++ )
  {
    t = i * dt;
    for ( j = 0; j <= n; j++ )
    {
      x = j * dx;
      fprintf ( data_unit, "  %f  %f  %f\n", x, t, u[i][j] );
    }
    fprintf ( data_unit, "\n" );
  }
  fclose ( data_unit );

  printf ( "\n" );
  printf ( "  Plot data written to the file \"string_data.txt\".\n" );
/*
  Write gnuplot command file.
*/
  command_unit = fopen ( "string_commands.txt", "wt" );

  fprintf ( command_unit, "set term png\n" );
  fprintf ( command_unit, "set output \"string.png\"\n" );
  fprintf ( command_unit, "set grid\n" );
  fprintf ( command_unit, "set style data lines\n" );
  fprintf ( command_unit, "unset key\n" );
  fprintf ( command_unit, "set xlabel '<---X--->'\n" );
  fprintf ( command_unit, "set ylabel '<---Time--->'\n" );
  fprintf ( command_unit, "splot \"string_data.txt\" using 1:2:3 with lines\n" );
  fprintf ( command_unit, "quit\n" );

  fclose ( command_unit );

  printf ( "  Gnuplot command data written to the file \"string_commands.txt\".\n" );
/*
  Terminate.
*/
  printf ( "\n" );
  printf ( "STRING_SIMULATION:\n" );
  printf ( "  Normal end of execution.\n" );
  printf ( "\n" );
  timestamp ( );

  return 0;
# undef m
# undef n
}
/******************************************************************************/

double f ( double x )

/******************************************************************************/
/*
  Purpose:

    F supplies the initial condition.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    27 May 2012

  Author:

    John Burkardt

  Parameters:

    Input, double X, the location.

    Output, double F, the value of the solution at time 0 and location X.
*/
{
  const double pi = 3.14159265;
  double value;

  if ( 00.1 <= x && x <= 99.9 )
  {
    value = exp(-0.01*(x-70)*(x-70)) ;
//  value = sin(x*pi/10)  ;
//  value = exp(-0.01*(x-50)*(x-50)) ;
  }
  else
  {
    value = 0.0;
  }

  return value;
}
/******************************************************************************/

double g ( double x )

/******************************************************************************/
/*
  Purpose:

    G supplies the initial derivative.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    27 May 2012

  Author:

    John Burkardt

  Parameters:

    Input, double X, the location.

    Output, double G, the value of the time derivative of the solution 
    at time 0 and location X.
*/
{
  double value;

  value = 0.0;

  return value;
}
/******************************************************************************/

void timestamp ( )

/******************************************************************************/
/*
  Purpose:

    TIMESTAMP prints the current YMDHMS date as a time stamp.

  Example:

    31 May 2001 09:45:54 AM

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    24 September 2003

  Author:

    John Burkardt

  Parameters:

    None
*/
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  fprintf ( stdout, "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}
