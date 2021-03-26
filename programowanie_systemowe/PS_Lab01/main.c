// PS IN1 320 LAB01
// Maciej Lewicki
// lm34410@zut.edu.pl

#include <stdlib.h>
#include <string.h>

int main() {
    unsigned char *p1 = malloc(10*sizeof(unsigned char));
    unsigned char *p2 = malloc(20*sizeof(unsigned char));
    memset(p1, 1, 10);
    p1[9] = 2;  // change p1[10] to p1[9] array index out of bounds

    free(p1);   // free allocated memory
    free(p2);   // free allocated memory
    return 0;
}
