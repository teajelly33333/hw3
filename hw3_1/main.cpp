#include "mbed.h"

Thread thread_master;
Thread thread_slave;

//master

SPI spi(D11, D12, D13); // mosi, miso, sclk
DigitalOut cs(D9);

SPISlave device(PD_4, PD_3, PD_1, PD_0); //mosi, miso, sclk, cs; PMOD pins

//DigitalOut led(LED3);

int slave()
{

   device.format(16, 3);
   device.frequency(1000000);
   //device.reply(0x00); // Prime SPI with first reply
   int v, a;
   uint16_t data;
   uint16_t library[256];

   for(int i = 0; i < 256; i++) // Initializztion
   {
       library[i] = 0;
   }

   while (1)
   {
     // if (device.receive())
      //{
            v = device.read(); // Read byte from master
            printf("Command read from master: v = %0x\n", (v>>8));
            a = v;
            if (v >= 0x0100)
            {                      //Verify the command
                a = a - 0x0100;
               printf("Address read from master: %0x    ", a);
               data = device.read();
               printf("Data read from master: %0x\n", data);
               library[a] = data;
            }
            else if ( v >= 0x0000)
            {
                device.reply(library[a]);
                device.read();
            }
            else
            {
               printf("Default reply to master: 0x00\n");
               device.reply(0x00); //Reply default value
            }
     // }
   }
}

void master()
{
   uint16_t command = 0x00A1;
   uint16_t data = 0xABCD;
   int response;

   // Setup the spi for 8 bit data, high steady state clock,
   // second edge capture, with a 1MHz clock rate
   spi.format(16, 3);
   spi.frequency(1000000);

   for(int i=0; i<3; ++i){
      // Chip must be deselected
      cs = 1;
      // Select the device by seting chip select low
      cs = 0;

      printf("Send message to slave %0x\n",command);
      spi.write(command); //Send ID
      cs = 1;                       // Deselect the device
      ThisThread::sleep_for(100ms); //Wait for debug print
      cs = 0;
      response = spi.write(data);
      ThisThread::sleep_for(100ms);
      cs = 1;
      
      if(command > 0x0100)
      {
           command = command - 0x0100;
      }
      else {
           printf("Data received: %0x\n", response);
           command = command + 0x0100;
      }
     printf("\n");
   }
}

int main()
{
    printf("--------------------------------\n");
   thread_slave.start(slave);
   thread_master.start(master);
   while(1){
       
   }
}