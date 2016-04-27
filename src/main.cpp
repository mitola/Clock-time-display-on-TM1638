#include "Arduino.h"
#include <TM1638.h>
// define a module on data pin 8, clock pin 9 and strobe pin 10
TM1638 module(8, 9, 10);

void setup()
{

}

void loop()
{

}

/*----------------------------------------------------------------------------*/
/* Get a single character from the host                                       */
/*----------------------------------------------------------------------------*/
static int getb(void)
{  while (!(Serial.available() > 0));  /* Wait for data to arrive             */
   return Serial.read();               /* Return next character               */
}                                      /*  end: getb()                        */
/*----------------------------------------------------------------------------*/
/* Get current date/time and set the system reset time                        */
/*----------------------------------------------------------------------------*/
void get_time(void)
{  time_t t;                           /* Current system time                 */
   int c;                              /* Input character                     */
   do                                  /* Until end of message                */
   {  Serial.println("?T");            /* Send time query to host via USB     */
      t = 0;                           /* Initialize time value               */
      while ('T' != getb()) ;          /* Watch for start of time response    */
      while (('0' <= (c = getb())) && (c <= '9')) /* Is this a decimal digit? */
      {  t = 10 * t + (c & 0x0F);      /* If so, build time value             */
      }                                /*  end: building time value           */
   }  while (c != '!');                /* Until a valid time is received      */
   set_time(ss(t));                    /* Calculate and save reset time       */
}                                      /*  end: set_time()                    */
/*----------------------------------------------------------------------------*/
