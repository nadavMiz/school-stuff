#ifndef ADTERR_H
#define ADTERR_H
typedef enum

{

    /* General ADT Errors */

    ERR_OK                            =0,

    ERR_GENERAL,

    ERR_NOT_INITIALIZED,

    ERR_ALLOCATION_FAILED,

    ERR_REALLOCATION_FAILED,

    ERR_UNDERFLOW,

    ERR_OVERFLOW,

    ERR_WRONG_INDEX,

      /* Vector Errors */

    /* Stack  Errors */

    ERR_STACK_BBBBB = 30

    /* LinkedList  Errors */

    /* Bit Vector*/

} ADTErr;

#endif /* ifndef ADTERR_H */
