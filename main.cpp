/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

void write_reg(SPI spi, DigitalOut DC, DigitalOut CS, int val){
    DC = 0;
    CS = 0;
    spi.write(val);
    CS = 1;
    printf("Bip boop");
}

void write_data(SPI spi, DigitalOut DC, DigitalOut CS,int val){
    DC = 1;
    CS = 0;
    spi.write(val);
    CS = 1;
    printf("Bip Boop");
}

void init_screen(SPI spi, DigitalOut DC, DigitalOut CS){
    printf("Initializing the screen");
    write_reg(spi,DC,CS,0xfd);  // command lock
    write_data(spi,DC,CS,0x12);
    write_reg(spi,DC,CS,0xfd);  // command lock
    write_data(spi,DC,CS,0xB1);

    write_reg(spi,DC,CS,0xae);  // display off
    write_reg(spi,DC,CS,0xa4);  // Normal Display mode

    write_reg(spi,DC,CS,0x15);  //set column address
    write_data(spi,DC,CS,0x00);     //column address start 00
    write_data(spi,DC,CS,0x7f);     //column address end 127
    write_reg(spi,DC,CS,0x75);  //set row address
    write_data(spi,DC,CS,0x00);     //row address start 00
    write_data(spi,DC,CS,0x7f);     //row address end 127    

    write_reg(spi,DC,CS,0xB3);
    write_data(spi,DC,CS,0xF1);

    write_reg(spi,DC,CS,0xCA);  
    write_data(spi,DC,CS,0x7F);

    write_reg(spi,DC,CS,0xa0);  //set re-map & data format
    write_data(spi,DC,CS,0x74);     //Horizontal address increment

    write_reg(spi,DC,CS,0xa1);  //set display start line
    write_data(spi,DC,CS,0x00);     //start 00 line

    write_reg(spi,DC,CS,0xa2);  //set display offset
    write_data(spi,DC,CS,0x00);

    write_reg(spi,DC,CS,0xAB);  
    write_reg(spi,DC,CS,0x01);  

    write_reg(spi,DC,CS,0xB4);  
    write_data(spi,DC,CS,0xA0);   
    write_data(spi,DC,CS,0xB5);  
    write_data(spi,DC,CS,0x55);    

    write_reg(spi,DC,CS,0xC1);  
    write_data(spi,DC,CS,0xC8); 
    write_data(spi,DC,CS,0x80);
    write_data(spi,DC,CS,0xC0);

    write_reg(spi,DC,CS,0xC7);  
    write_data(spi,DC,CS,0x0F);

    write_reg(spi,DC,CS,0xB1);  
    write_data(spi,DC,CS,0x32);

    write_reg(spi,DC,CS,0xB2);  
    write_data(spi,DC,CS,0xA4);
    write_data(spi,DC,CS,0x00);
    write_data(spi,DC,CS,0x00);

    write_reg(spi,DC,CS,0xBB);  
    write_data(spi,DC,CS,0x17);

    write_reg(spi,DC,CS,0xB6);
    write_data(spi,DC,CS,0x01);

    write_reg(spi,DC,CS,0xBE);
    write_data(spi,DC,CS,0x05);

    write_reg(spi,DC,CS,0xA6);

}



int main()
{
    // Initialise the digital pin LED1 as an output
    //D10 is PB6 is Chip select
    //D11 is PA7 is Mosi
    //SCLK is D13 is PA5
    //D7 is PA8
    //D8 is PA9
    //D12 is MISO PA6 UNUSED
    DigitalOut led(LED1);
    //Initialise SPI
    SPI spi(PA_6,PA_7,PA_5);//miso,mosi,sclk
    DigitalIn miso(PA_6);
    DigitalOut mosi(PA_7);//Need to change the ref after
    DigitalOut cs(PB_6);
    DigitalOut DC(PA_8);
    mosi = 0;
    cs = 1;
    init_screen(spi,DC,CS)
    while (true) {
        cs = 0;//SPI Should be initialized need to write now
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
        
        
    }
}
