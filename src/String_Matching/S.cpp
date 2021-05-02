// Naive algorithm for building suffix array of a given text
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sys/mman.h>
#include "tool.h"
#include <stdio.h>
using namespace std;


//Please modify this function
void search(char *pat, char *txt, int *suffArr, int n)
{
 
    // Do simple binary search for the pat in txt using the
    // built suffix array
    int l = 0, r = n-1;  // Initialize left and right indexes
    // Find the top index
    while (l != r)
    {
        int mid = (l + r) / 2;
        const char * cmpStr = txt+suffArr[mid];
        int res = strncmp(pat, cmpStr, strlen(cmpStr));
        if (res < 0) r = mid;
        else if (res == 0) break;
        else l = mid + 1;
    }
    int top = l;

    // Find the bottom index
    const size_t pat_size = strlen(pat);
    l = 0, r = n-1;
    while (l != r)
    {
        int mid = (l + r + 1) / 2;
        int res = strncmp(pat, txt+suffArr[mid], pat_size);
        if (res == 0 || res > 0) l = mid;
        else r = mid - 1;
    }
    int down = l;

    for(int i = top; i <= down; i++){
        cout << "pattern matched at pos " << suffArr[i] << "\n";
    }
    // cout<<"hi"<<endl;
}

// Driver program to test above functions

//*****************************************************

// Do not Modify main function
// You are only allowed to modify the search function

//*****************************************************
int main()
{
    char txt[100000] ;  // text
    char pat[] = "ana";   // pattern to be searched in text
    FILE* infile=fopen( "reference_string.txt", "r");
    fscanf(infile, "%s", txt);
 
    // Build suffix array
    int n = strlen(txt);
    int *suffArr = buildSuffixArray(txt, n);
    // cout << "Following is suffix array for " << txt << endl;
    // printArr(suffArr, n);
 
    // search pat in txt using the built suffix array
    mremap(0,0,0,1);
    search(pat, txt, suffArr, n);
    mremap(0,0,0,1);
 
    return 0;
}
//*****************************************************
