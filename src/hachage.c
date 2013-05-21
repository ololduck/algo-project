#include "hachage.h"

unsigned int hache(char* p) {
    unsigned int h=0, g;
    for(;*p; p++) {
        h=(h<<4)+*p;
        if(g=h&0xf000000) {
            h=h^(g>>24);
            h=h^g;
        }
    }
    return h;
}
