#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<linux/rtc.h>
#include<linux/ioctl.h>
#include<stdio.h>
#include<stdlib.h>

#include "led.h"

int led_fd=0;
int led_open(const char*devname)
{
    led_fd=open(devname,O_RDWR);
    if(led_fd<0)
    {
        printf("open device %s failed.\n",devname);
        return -1;
    }
    else
    {
        printf("open device %s succeffully.\n",devname);
    }
    return 0;
}


int led_ioctl(const int no,int pin)
{
    int num=no;
    ioctl(led_fd,num,pin);
    return 0;
}

int led_close(void)
{
    if(led_fd)
        close(led_fd);
    return 0;
}
