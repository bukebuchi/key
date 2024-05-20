#include <REG52.H>

sbit KEY1 = P1 ^ 0;
sbit LED1 = P0 ^ 0;
sbit LED2 = P0 ^ 1;
bit backstat = 1;
void delay(unsigned int num);
unsigned char code LedChar[] = { // 数码管显示字符转换表
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
bit KeyStat = 1;
unsigned char cnt = 0;
void main()
{
    TMOD = 0X01;
    TH0 = (65536 - 2000) / 256;
    TL0 = (65536 - 2000) % 256;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
    P1 = 0XFF;
    P0 = 0X00;
    while (1)
    {
        if (KeyStat != backstat)
        {
            
            if (backstat == 1)
            {
               
                //LED1 = ~LED1;
            }
            else
            {
                // 弹起
                 // 按下
                cnt++;
                if(cnt>=10)
                {
                    cnt = 0;
                }
                P0 = ~LedChar[cnt];
            }
            backstat = KeyStat;
        }
    }
}
void delay(unsigned int num)
{

    while (num--)
        ;
}

void timer0_isr() interrupt 1
{
    static unsigned char keybuff = 0xff;
    TH0 = (65536 - 2000) / 256;
    TL0 = (65536 - 2000) % 256;
    keybuff = (keybuff << 1) | KEY1;
    if (keybuff == 0x00)
    {
        KeyStat = 0;
    }
    else if (keybuff == 0xff)
    {
        KeyStat = 1;
    }
}