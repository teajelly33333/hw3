#include "mbed.h"
#include "TextLCD.h"

// Host PC Communication channels
static BufferedSerial pc(USBTX, USBRX); // tx, rx
static BufferedSerial device(D10, D9);
int serialCount;
char serialInBuffer[32];
// I2C Communication
I2C i2c_lcd(D14, D15); // SDA, SCL

//TextLCD_SPI lcd(&spi_lcd, p8, TextLCD::LCD40x4);   // SPI bus, 74595 expander, CS pin, LCD Type
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2);   // I2C bus, PCF8574 Slaveaddress, LCD Type
                                                     //TextLCD_I2C lcd(&i2c_lcd, 0x42, TextLCD::LCD16x2, TextLCD::WS0010);
                                                     // I2C bus, PCF8574 Slaveaddress, LCD Type, Device Type
                                                     //TextLCD_SPI_N lcd(&spi_lcd, p8, p9);
                                                     // SPI bus, CS pin, RS pin, LCDType=LCD16x2, BL=NC, LCDTCtrl=ST7032_3V3
//TextLCD_I2C_N lcd(&i2c_lcd, ST7032_SA, TextLCD::LCD16x2, NC, TextLCD::ST7032_3V3);
// I2C bus, Slaveaddress, LCD Type, BL=NC, LCDTCtrl=ST7032_3V3

FileHandle *mbed::mbed_override_console(int fd)
{
   return &pc;
}

int main()
{
    char byteIn, I;
    char rowc[6] = {'r', 'o', 'w', 's', ':', '\0'};
    char columnc[8] = {'c', 'o', 'l', 'u', 'm', 'n', ':', '\0'};
    int store;
    while(1){
        pc.read(&byteIn, 1);
        switch(byteIn){
            case '1': 
                lcd.locate(0, 1);
                ThisThread::sleep_for(1000ms);
                break;
            case '2':
                lcd.cls();
                ThisThread::sleep_for(1000ms);
                break;
            case '3':
                store = lcd.rows();
                I = store + '0';
                lcd.puts(rowc);
                lcd.putc(I);
                ThisThread::sleep_for(1000ms);
                break;
            case '4':
                store = lcd.columns();
                lcd.puts(columnc);
                I = (store / 10) + '0'; 
                lcd.putc(I);
                I = (store % 10) + '0';
                lcd.putc(I);
                ThisThread::sleep_for(1000ms);
                break;
            case '5':
                while(byteIn != ' ')
                {
                    pc.read(&byteIn, 1);
                    lcd.putc(byteIn);          
                }
                ThisThread::sleep_for(1000ms);
                break;
        }
    }
}