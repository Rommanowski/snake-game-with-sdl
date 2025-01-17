#define RANDOM(a, b) ((a) + rand() % ((b) - (a) + 1)) 
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdlib> 
#include <ctime>

using namespace std;

int main()
{
    int x=1000;
    int y = float(x) / 1.5;

    printf("%d\n", y);
}