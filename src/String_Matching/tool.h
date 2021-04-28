
// Naive algorithm for building suffix array of a given text
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sys/mman.h>
using namespace std;
// Structure to store information of a suffix
struct suffix;

// A comparison function used by sort() to compare two suffixes

extern int cmp(struct suffix a, struct suffix b);

extern int *buildSuffixArray(char *txt, int n);
// A utility function to print an array of given size
extern void printArr(int arr[], int n);
