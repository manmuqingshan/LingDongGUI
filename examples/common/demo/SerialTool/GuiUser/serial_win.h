#ifndef SERIAL_WIN32_H
#define SERIAL_WIN32_H

#ifdef __cplusplus
extern "C" {
#endif

int com_open_ex(const char *port,
                unsigned long baud,
                unsigned char dataBits,
                unsigned char stopBits,
                unsigned char parity);    // 0=NOPARITY,1=ODD,2=EVEN,3=MARK,4=SPACE

// 简化8N1
static inline int com_open(const char *port, unsigned long baud)
{
    return com_open_ex(port, baud, 8, 1, 0);
}

void com_close(void);
int  com_send(const void *buf, unsigned long len);
int  com_recv(void *buf, unsigned long max);
int com_count(void);
int com_name(int idx, char *buf);

#ifdef __cplusplus
}
#endif

#endif // SERIAL_WIN32_H
