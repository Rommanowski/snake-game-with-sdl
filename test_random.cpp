#define RANDOM(a, b) ((a) + rand() % ((b) - (a) + 1)) 
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdlib> 
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));

    for(int i=0; i<1000; ++i){
        printf("%d\n", RANDOM(0, 10));
    }
}