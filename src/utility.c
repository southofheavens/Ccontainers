#include <utility.h>
#include <stdarg.h>
#include <stdlib.h>

void check_null_pointers(char *msg, size_t arg_count, ...)
{
    va_list ap; 
    va_start(ap,arg_count);
    size_t i;
    void *p;

    for (i = 0; i < arg_count; ++i) {
        p = va_arg(ap,void *);
        if (!p)
        {
            fprintf(stderr,"%s",msg);
            exit(EXIT_FAILURE);
        }
    }

    va_end(ap);
}