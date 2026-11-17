#include <stdio.h>

void display_list(int n) {
    for (int entier = 1; entier != n+1; entier++) {
        printf("%d\n", entier);
    }


int main (void){
    display_list(100);
    return 0;
}