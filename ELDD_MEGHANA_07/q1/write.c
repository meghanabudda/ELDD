#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
    int fp,ret;
    char buff[50];
    if(fp<0)
    {
        printf("Device file cannot be opened in the path....");
    }
    else
    {
        printf("Device file can be opened in the path...");
        return 0;
    }
}