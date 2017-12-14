/* software implementation
 * of random number 
 * generator
 *
 * We need an initializer and finalizer function
 * (constructor and destructor clarifiers)
 * don't forget to replace statics with externs
 */

#include "randlib.h"
#include <stdio.h>
#include <stdlib.h>
/* Software implementation.  */



__attribute__ ((constructor))
/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
extern void
software_rand64_init (void)
{
  urandstream = fopen ("/dev/urandom", "r");
  if (! urandstream)
    abort ();
}

/* Return a random value, using software operations.  */
extern  unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}


__attribute__ ((destructor))
/* Finalize the software rand64 implementation.  */
extern void
software_rand64_fini (void)
{
  fclose (urandstream);
}


