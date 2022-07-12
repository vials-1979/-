#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C" {
#endif
extern int led_open(const char *devname);
extern int led_ioctl(const int no,int pin);
extern int led_close(void);
extern int led_fd;
#ifdef __cplusplus
}
#endif


#endif // LED_H
