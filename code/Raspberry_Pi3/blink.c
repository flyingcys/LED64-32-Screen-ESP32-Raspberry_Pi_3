#include <wiringPi.h>
#include <stdio.h>

typedef unsigned char byte;

#define RowA 0
#define RowB 1
#define RowC 2
#define RowD 3
#define OE 7 //EN口

#define R11 22         //数据出    MOSI 输出 main out
#define R12 23
#define G11 24
#define G12 25
#define R21 26        
#define R22 27
#define G21 28
#define G22 29
#define LE 4       //时钟    SCK
#define CLK 5      //595 刷新显示  SS 片选
//int DATAIN  12     //数据入,读FLASH时有用  MISO 输入 main in

byte ShowG11[16][8] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

byte ShowG12[16][8] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

byte ShowR11[16][8] = {
	0x20, 0x80, 0x12, 0x10, 0x20, 0x00, 0x42, 0x00,
	0x3E, 0xFE, 0x1A, 0x18, 0x10, 0x00, 0x22, 0x3C,
	0x50, 0xA0, 0x17, 0xD0, 0x13, 0xFC, 0x22, 0x24,
	0x49, 0x10, 0x22, 0x10, 0x00, 0x40, 0x02, 0x24,
	0x82, 0x08, 0x27, 0xBE, 0x88, 0x40, 0x8F, 0xBC,
	0x00, 0xF0, 0x62, 0x24, 0x48, 0x40, 0x52, 0x24,
	0x3F, 0x00, 0xAF, 0xE4, 0x50, 0x40, 0x12, 0x24,
	0x01, 0x00, 0x24, 0x14, 0x10, 0x40, 0x2F, 0xBC,
	0x01, 0x00, 0x24, 0x14, 0x10, 0x40, 0x28, 0xA4,
	0x7F, 0xFC, 0x27, 0x88, 0x20, 0x40, 0x28, 0xA4,
	0x02, 0x80, 0x24, 0x88, 0xE0, 0x40, 0xC8, 0xA4,
	0x02, 0x40, 0x24, 0x94, 0x20, 0x40, 0x48, 0xA4,
	0x04, 0x20, 0x28, 0x94, 0x20, 0x40, 0x4F, 0xC4,
	0x08, 0x18, 0x2B, 0xA6, 0x2F, 0xFE, 0x40, 0x44,
	0x30, 0x0E, 0x31, 0x44, 0x20, 0x00, 0x40, 0x94,
	0xC0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x41, 0x08,
};

byte ShowR12[16][8] = {
	0x20, 0x80, 0x12, 0x10, 0x20, 0x00, 0x42, 0x00,
	0x3E, 0xFE, 0x1A, 0x18, 0x10, 0x00, 0x22, 0x3C,
	0x50, 0xA0, 0x17, 0xD0, 0x13, 0xFC, 0x22, 0x24,
	0x49, 0x10, 0x22, 0x10, 0x00, 0x40, 0x02, 0x24,
	0x82, 0x08, 0x27, 0xBE, 0x88, 0x40, 0x8F, 0xBC,
	0x00, 0xF0, 0x62, 0x24, 0x48, 0x40, 0x52, 0x24,
	0x3F, 0x00, 0xAF, 0xE4, 0x50, 0x40, 0x12, 0x24,
	0x01, 0x00, 0x24, 0x14, 0x10, 0x40, 0x2F, 0xBC,
	0x01, 0x00, 0x24, 0x14, 0x10, 0x40, 0x28, 0xA4,
	0x7F, 0xFC, 0x27, 0x88, 0x20, 0x40, 0x28, 0xA4,
	0x02, 0x80, 0x24, 0x88, 0xE0, 0x40, 0xC8, 0xA4,
	0x02, 0x40, 0x24, 0x94, 0x20, 0x40, 0x48, 0xA4,
	0x04, 0x20, 0x28, 0x94, 0x20, 0x40, 0x4F, 0xC4,
	0x08, 0x18, 0x2B, 0xA6, 0x2F, 0xFE, 0x40, 0x44,
	0x30, 0x0E, 0x31, 0x44, 0x20, 0x00, 0x40, 0x94,
	0xC0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x41, 0x08,
};

byte ShowG21[16][8] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

byte ShowG22[16][8] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


byte ShowR21[16][8] = {
	0x20, 0x80, 0x12, 0x10, 0x20, 0x00, 0x42, 0x00,
	0x3E, 0xFE, 0x1A, 0x18, 0x10, 0x00, 0x22, 0x3C,
	0x50, 0xA0, 0x17, 0xD0, 0x13, 0xFC, 0x22, 0x24,
	0x49, 0x10, 0x22, 0x10, 0x00, 0x40, 0x02, 0x24,
	0x82, 0x08, 0x27, 0xBE, 0x88, 0x40, 0x8F, 0xBC,
	0x00, 0xF0, 0x62, 0x24, 0x48, 0x40, 0x52, 0x24,
	0x3F, 0x00, 0xAF, 0xE4, 0x50, 0x40, 0x12, 0x24,
	0x01, 0x00, 0x24, 0x14, 0x10, 0x40, 0x2F, 0xBC,
	0x01, 0x00, 0x24, 0x14, 0x10, 0x40, 0x28, 0xA4,
	0x7F, 0xFC, 0x27, 0x88, 0x20, 0x40, 0x28, 0xA4,
	0x02, 0x80, 0x24, 0x88, 0xE0, 0x40, 0xC8, 0xA4,
	0x02, 0x40, 0x24, 0x94, 0x20, 0x40, 0x48, 0xA4,
	0x04, 0x20, 0x28, 0x94, 0x20, 0x40, 0x4F, 0xC4,
	0x08, 0x18, 0x2B, 0xA6, 0x2F, 0xFE, 0x40, 0x44,
	0x30, 0x0E, 0x31, 0x44, 0x20, 0x00, 0x40, 0x94,
	0xC0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x41, 0x08,
};

byte ShowR22[16][8] = {
	0x20, 0x80, 0x12, 0x10, 0x20, 0x00, 0x42, 0x00,
	0x3E, 0xFE, 0x1A, 0x18, 0x10, 0x00, 0x22, 0x3C,
	0x50, 0xA0, 0x17, 0xD0, 0x13, 0xFC, 0x22, 0x24,
	0x49, 0x10, 0x22, 0x10, 0x00, 0x40, 0x02, 0x24,
	0x82, 0x08, 0x27, 0xBE, 0x88, 0x40, 0x8F, 0xBC,
	0x00, 0xF0, 0x62, 0x24, 0x48, 0x40, 0x52, 0x24,
	0x3F, 0x00, 0xAF, 0xE4, 0x50, 0x40, 0x12, 0x24,
	0x01, 0x00, 0x24, 0x14, 0x10, 0x40, 0x2F, 0xBC,
	0x01, 0x00, 0x24, 0x14, 0x10, 0x40, 0x28, 0xA4,
	0x7F, 0xFC, 0x27, 0x88, 0x20, 0x40, 0x28, 0xA4,
	0x02, 0x80, 0x24, 0x88, 0xE0, 0x40, 0xC8, 0xA4,
	0x02, 0x40, 0x24, 0x94, 0x20, 0x40, 0x48, 0xA4,
	0x04, 0x20, 0x28, 0x94, 0x20, 0x40, 0x4F, 0xC4,
	0x08, 0x18, 0x2B, 0xA6, 0x2F, 0xFE, 0x40, 0x44,
	0x30, 0x0E, 0x31, 0x44, 0x20, 0x00, 0x40, 0x94,
	0xC0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x41, 0x08,
};


byte Rownumber = 0;


void setuppinmode()
{
  pinMode(RowA, OUTPUT);
  pinMode(RowB, OUTPUT);
  pinMode(RowC, OUTPUT);
  pinMode(RowD, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(LE, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(G12, OUTPUT);
  pinMode(G11, OUTPUT);
  pinMode(R12, OUTPUT);
  pinMode(R11, OUTPUT);
  pinMode(R21, OUTPUT);
  pinMode(G21, OUTPUT);
  pinMode(R22, OUTPUT);
  pinMode(G22, OUTPUT);
  //初始化引脚
  digitalWrite(OE, LOW);
  digitalWrite(LE, LOW);
  digitalWrite(CLK, LOW);
  //初始化软件SPI
}
void hc138sacn(byte r) {  //输出行线状态ABCD
  digitalWrite(RowA, (r & 0x01));
  digitalWrite(RowB, (r & 0x02));
  digitalWrite(RowC, (r & 0x04));
  digitalWrite(RowD, (r & 0x08));
}

void hc595senddata(byte datar11, byte datar12, byte datag11, byte datag12, byte datar21, byte datar22, byte datag21, byte datag22)
{
  for (byte i = 0; i < 8; i++)
  {
	//The first screen
    digitalWrite(R11, datar11 & 0x80);
    datar11 = datar11 << 1;
//    digitalWrite(G11, datag11 & 0x80);
//    datag11 = datag11 << 1;
    digitalWrite(R12, datar12 & 0x80);
    datar12 = datar12 << 1;
//    digitalWrite(G12, datag12 & 0x80);
//    datag12 = datag12 << 1;

	//The second screen
	digitalWrite(R21, datar21 & 0x80);
	datar21 = datar21 << 1;
//	digitalWrite(G21, datag21 & 0x80);
//	datag21 = datag21 << 1;
	digitalWrite(R22, datar22 & 0x80);
	datar22 = datar22 << 1;
//	digitalWrite(G22, datag22 & 0x80);
//	datag22 = datag22 << 1;

    digitalWrite(CLK, HIGH);//拉高时钟信号，上升沿发送数据
    digitalWrite(CLK, LOW);//恢复低电平
  }
}

void display()
{
  for (Rownumber = 0; Rownumber < 16; Rownumber = Rownumber + 1)
  {
    for (int i = 0; i < 8; i++)
    {
      hc595senddata(ShowR11[Rownumber][i], ShowR12[Rownumber][i], ShowG11[Rownumber][i], ShowG12[Rownumber][i], ShowR21[Rownumber][i], ShowR22[Rownumber][i], ShowG21[Rownumber][i], ShowG22[Rownumber][i]);
    }
    digitalWrite(OE, HIGH);//关闭LED不仅仅是为了省电，还有清空的作用，这会帮助你解决一些在你看来是玄学的问题，比如为什么我没有给某些点供电，但是某些点却以极其不引人注目的微弱之光闪耀着
    hc138sacn(Rownumber);
    digitalWrite(LE, HIGH);
    digitalWrite(LE, LOW);
    digitalWrite(OE, LOW);
  }
}

int main (void)
{
  wiringPiSetup();
  setuppinmode();
  while(1)
  {
  	display();
  }
}
