
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <omp.h>

int main ( int argc, char *argv[] );
double f ( double x, double y );
void timestamp ( );

// Define number of threads for the program 
#define NUM_THREADS 4

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for quad2d.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    28 June 2020

  Author:

    Layoneth Pareja
*/
{
  double a;
  double b;
  double error;
  double exact;
  int i;
  int j;
  int n;
  int nx;
  int ny;
  double pi;
  double total;
  double wtime;
  double x;
  double y;

  a = 0.0;
  b = 1.0;
  nx = 32768;
  ny = 32768;
  n = nx * ny;
  pi = 3.141592653589793;
  exact = pi * pi / 6.0;

  timestamp ( );
  printf ( "\n" );
  printf ( "quad2d:\n" );
  printf ( "  openMP version for Layoneth Pareja\n" );
  printf ( "  Estimate the integral of f(x,y) over [0,1]x[0,1].\n" );
  printf ( "  f(x,y) = 1 / ( 1 - x * y ).\n" );
  printf ( "\n" );
  printf ( "  A        = %f\n", a );
  printf ( "  B        = %f\n", b );
  printf ( "  NX       = %d\n", nx );
  printf ( "  NY       = %d\n", ny );
  printf ( "  N        = %d\n", n );
  printf ( "  Exact    = %24.16f\n", exact );

  wtime = omp_get_wtime ( );

  total = 0.0;
  
  /*    
    This is the area of the program where activity is most present
    and there are two iterative cycles (a nested for) therefore
    this for is parallelized.
  */
  
  // Set the number of threads
 omp_set_num_threads(NUM_THREADS);
  
  // The start of a parallel region is indicated
  #pragma omp parrallel
        
  for ( i = 1; i <= nx; i++ )
  {
    x = ( ( 2 * nx - 2 * i + 1 ) * a + ( 2 * i - 1 ) * b ) / ( 2 * nx );
    
    
    // Variables a, b, n and are shared by all threads and j, y private 
    # pragma omp parallel shared ( a, b, ny ) private ( j, y ) 
    
    // Parallelization using reduction
    # pragma omp for reduction ( + : total )
    for ( j = 1; j <= ny; j++ )
    {
      y = ( ( 2 * ny - 2 * j + 1 ) * a + ( 2 * j - 1 ) * b ) / ( 2 * ny );
      total = total + f ( x, y );
    }
  }

  wtime = omp_get_wtime ( ) - wtime;

  total = ( b - a ) * ( b - a ) * total / ( double ) ( nx ) / ( double ) ( ny );
  error = fabs ( total - exact );
 
  printf ( "\n" );
  printf ( "  Estimate = %24.16f\n", total );
  printf ( "  Error    = %e\n", error );
  printf ( "  Time     = %f\n", wtime );
/*
  Terminate.
*/
  printf ( "\n" );
  printf ( "quad2d:\n" );
  printf ( "  Normal end of execution.\n" );
  printf ( "\n" );
  timestamp ( );

  return 0;
}
/******************************************************************************/

double f ( double x, double y )

/******************************************************************************/
/*
  Purpose:

    F evaluates the function.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    28 June 2020

  Author:

    Layoneth Pareja

  Parameters:

    Input, double X, Y, the coordinates of a point.

    Output the function value at (X,Y).
*/
{

  return 1.0 / ( 1.0 - x * y );
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
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}
