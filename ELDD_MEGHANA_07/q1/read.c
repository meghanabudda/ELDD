#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>

int main()
{
        int fp,arg=54,ret;
        char buff[]="MEGHA";
        fp= open("/dev/mydevice", O_RDWR);
        if(fp > 0) 
        {
            printf("Device File Opened successfully in the path...\n");
        }
        else 
        {
            printf("Cannot open device file...\n");
            return 0;
        }

        
}