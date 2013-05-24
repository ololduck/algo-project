/**
 * test file for the Celmot struct
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../src/structs/celmot.h"

int main(int argc, char const *argv[])
{
    Celmot* l = celmot_new("AAA");
    assert(l);
    assert(strcmp("AAA", l->mot) == 0);
    Celmot* to_add = celmot_new("AAB");
    celmot_add(l, to_add);
    assert()
    return 0;
}
