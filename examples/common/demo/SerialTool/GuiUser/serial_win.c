#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

/* ---------- 全局句柄 ---------- */
static HANDLE hCom = INVALID_HANDLE_VALUE;

/* ---------- 打开串口 ---------- */
int com_open_ex(const char *port,
                unsigned long baud,
                unsigned char dataBits,
                unsigned char stopBits,
                unsigned char parity)
{
    char full[16];
    snprintf(full, sizeof(full), "\\\\.\\%s", port);

    hCom = CreateFileA(full,
                       GENERIC_READ | GENERIC_WRITE,
                       0, NULL, OPEN_EXISTING, 0, NULL);
    if (hCom == INVALID_HANDLE_VALUE)
        return 0;

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(hCom, &dcb))
        goto fail;

    dcb.BaudRate = baud;
    dcb.ByteSize = dataBits;
    dcb.Parity   = parity;      /* 0..4 直接对应 winbase.h 宏 */
    dcb.StopBits = (stopBits == 1) ? ONESTOPBIT : TWOSTOPBITS;

    /* 默认无流控，DCB 清零后即为 FALSE，无需再设 */

    if (!SetCommState(hCom, &dcb))
        goto fail;

    COMMTIMEOUTS tmo = {0};
    tmo.ReadIntervalTimeout         = 50;
    tmo.ReadTotalTimeoutConstant    = 50;
    tmo.ReadTotalTimeoutMultiplier  = 10;
    tmo.WriteTotalTimeoutConstant   = 50;
    tmo.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hCom, &tmo))
        goto fail;

    return 1;

fail:
    CloseHandle(hCom);
    hCom = INVALID_HANDLE_VALUE;
    return 0;
}

/* ---------- 关闭串口 ---------- */
void com_close(void)
{
    if (hCom != INVALID_HANDLE_VALUE) {
        CloseHandle(hCom);
        hCom = INVALID_HANDLE_VALUE;
    }
}

/* ---------- 发送 ---------- */
int com_send(const void *buf, DWORD len)
{
    DWORD act;
    if (!WriteFile(hCom, buf, len, &act, NULL))
        return -1;
    return (int)act;
}

/* ---------- 接收 ---------- */
int com_recv(void *buf, DWORD max)
{
    DWORD act;
    if (!ReadFile(hCom, buf, max, &act, NULL))
        return -1;
    return (int)act;
}

/* 返回掩码：bit0=COM1...bit31=COM32 */
static DWORD com_mask(void)
{
    DWORD mask = 0;
    /* 32 个 COM 口足够日常用 */
    for (int i = 1; i <= 32; ++i) {
        char port[16];
        wsprintfA(port, "COM%d", i);
        HANDLE h = CreateFileA(port, 0, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (h != INVALID_HANDLE_VALUE) {
            mask |= (1u << (i - 1));
            CloseHandle(h);
        }
    }
    return mask;
}

int com_count(void)          /* 数量 */
{
    DWORD m = com_mask();
    int c = 0;
    while (m) { c += (m & 1); m >>= 1; }
    return c;
}

int com_name(int idx, char *buf)  /* 第 idx 个名称 */
{
    DWORD m = com_mask();
    int cnt = 0;
    for (int i = 0; i < 32; ++i) {
        if (m & (1u << i)) {
            if (cnt == idx) {
                wsprintfA(buf, "COM%d", i + 1);
                return 1;
            }
            ++cnt;
        }
    }
    return 0;
}
