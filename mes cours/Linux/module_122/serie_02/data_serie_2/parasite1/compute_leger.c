#include <stdio.h>

// to compile : gcc -lm compute_leger.c -o compute_leger
// to play    : ./compute_leger | play -t raw -c 1 -1 -r 44100 -u -



#define SAMPLE_FREQ 44100.0
#define BEEP_FREQ   800.0

void print_sound( float length, float freq, unsigned char mask )
{
   int  slength = (int )(length * SAMPLE_FREQ);
   int  on      = (int )(SAMPLE_FREQ / freq);
   int  i;
   unsigned char out = 0xff;

   for( i=0;i<slength; i++ )
   {
      if ( (i % on) == 0 ) out = ~out;
      printf( "%c", out & mask );
   }
}



int main( int argc, char *argv[] )
{
   float   speed;
   float   time_total;
   float   time_50m;
   float   time_beep = 0.5;
   float   time_stop;
   float   time_step = 120.0;
   int     num_step  = 0;
   int     count, min;
   float sec;


   printf( "RIFF%c%c%c%cWAVE", 0,0,0,0 );
   print_sound( 0.1, 800,  0xff );
   print_sound( 0.9, 800,  0x00 );
   print_sound( 0.1, 900,  0xff );
   print_sound( 0.9, 900,  0x00 );
   print_sound( 0.1, 1000, 0xff );
   print_sound( 0.9, 1000, 0x00 );
   print_sound( 0.1, 1100, 0xff );
   print_sound( 0.9, 1200, 0x00 );
   print_sound( 2.0, 1200, 0xff );

   for( speed=8.0; speed<18.0; speed+=1.0 )
   {
      time_50m   = 3600.0 * (0.05 / speed);
      time_stop  = (float )floor( time_step / time_50m) * time_50m;
      if ( time_stop < 120 ) time_stop += time_50m;
      num_step = (int )((time_stop / time_50m)+0.5);

      //printf( "%f[km/h]\t %.1f[s]\t %.1f[s]\t %d\n", speed, time_50m, time_stop, num_step );
      //printf( "\n%.0fkm/h\t", speed );
      for( count=1; count<=num_step; count++ )
      {
         time_total += time_50m;
         min = (int )(time_total / 60.0);
         sec = time_total - (float)min * 60;
         if ( count == num_step )
         {
            print_sound( time_50m-2*time_beep, 1000, 0x00 );
            print_sound( 2*time_beep,          1000, 0xff );
         }
         else
         {
            print_sound( time_50m-time_beep, 1000, 0x00 );
            print_sound( time_beep,          1000, 0xff );
         }
         //printf( "%d.%02d \t", (int )(time_total/60.0), (int )(sec+0.5) );
      }
   }
}
