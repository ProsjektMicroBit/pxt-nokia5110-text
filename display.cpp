#include "pxt.h"
#include "MicroBit.h"
#include "mbed.h"

using namespace pxt;

enum class DigitalPin;

// function declarations used from pins-module in pxt
namespace pins {
    int spiWrite(int value);
    void spiFrequency(int frequency);
    void spiFormat(int bits, int mode);
    void spiPins(DigitalPin mosi, DigitalPin miso, DigitalPin sck);
}

MicroBitPin *getPin(int id);


enum MessageType {
        Data = 1,
        Command = 0
    };
//% color=#ff471a icon="\uf26c"
namespace display {

    

    MicroBitDisplay *disp = new MicroBitDisplay;

    // Variables used to keep track of when to change line while printing.
    uint8_t xPosition = 0;
    uint8_t yPosition = 0;

    const uint8_t font[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14, 0x24, 0x2a, 0x7f, 0x2a, 0x12, 0x23, 0x13, 0x08, 0x64, 0x62, 0x36, 0x49, 0x55, 0x22, 0x50, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, 0x14, 0x08, 0x3e, 0x08, 0x14, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x00, 0x50, 0x30, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x60, 0x60, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x3e, 0x51, 0x49, 0x45, 0x3e, 0x00, 0x42, 0x7f, 0x40, 0x00, 0x42, 0x61, 0x51, 0x49, 0x46, 0x21, 0x41, 0x45, 0x4b, 0x31, 0x18, 0x14, 0x12, 0x7f, 0x10, 0x27, 0x45, 0x45, 0x45, 0x39, 0x3c, 0x4a, 0x49, 0x49, 0x30, 0x01, 0x71, 0x09, 0x05, 0x03, 0x36, 0x49, 0x49, 0x49, 0x36, 0x06, 0x49, 0x49, 0x29, 0x1e, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x56, 0x36, 0x00, 0x00, 0x08, 0x14, 0x22, 0x41, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x41, 0x22, 0x14, 0x08, 0x02, 0x01, 0x51, 0x09, 0x06, 0x32, 0x49, 0x79, 0x41, 0x3e, 0x7e, 0x11, 0x11, 0x11, 0x7e, 0x7f, 0x49, 0x49, 0x49, 0x36, 0x3e, 0x41, 0x41, 0x41, 0x22, 0x7f, 0x41, 0x41, 0x22, 0x1c, 0x7f, 0x49, 0x49, 0x49, 0x41, 0x7f, 0x09, 0x09, 0x09, 0x01, 0x3e, 0x41, 0x49, 0x49, 0x7a, 0x7f, 0x08, 0x08, 0x08, 0x7f, 0x00, 0x41, 0x7f, 0x41, 0x00, 0x20, 0x40, 0x41, 0x3f, 0x01, 0x7f, 0x08, 0x14, 0x22, 0x41, 0x7f, 0x40, 0x40, 0x40, 0x40, 0x7f, 0x02, 0x0c, 0x02, 0x7f, 0x7f, 0x04, 0x08, 0x10, 0x7f, 0x3e, 0x41, 0x41, 0x41, 0x3e, 0x7f, 0x09, 0x09, 0x09, 0x06, 0x3e, 0x41, 0x51, 0x21, 0x5e, 0x7f, 0x09, 0x19, 0x29, 0x46, 0x46, 0x49, 0x49, 0x49, 0x31, 0x01, 0x01, 0x7f, 0x01, 0x01, 0x3f, 0x40, 0x40, 0x40, 0x3f, 0x1f, 0x20, 0x40, 0x20, 0x1f, 0x3f, 0x40, 0x38, 0x40, 0x3f, 0x63, 0x14, 0x08, 0x14, 0x63, 0x07, 0x08, 0x70, 0x08, 0x07, 0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x7f, 0x41, 0x41, 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x41, 0x41, 0x7f, 0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x01, 0x02, 0x04, 0x00, 0x20, 0x54, 0x54, 0x54, 0x78, 0x7f, 0x48, 0x44, 0x44, 0x38, 0x38, 0x44, 0x44, 0x44, 0x20, 0x38, 0x44, 0x44, 0x48, 0x7f, 0x38, 0x54, 0x54, 0x54, 0x18, 0x08, 0x7e, 0x09, 0x01, 0x02, 0x0c, 0x52, 0x52, 0x52, 0x3e, 0x7f, 0x08, 0x04, 0x04, 0x78, 0x00, 0x44, 0x7d, 0x40, 0x00, 0x20, 0x40, 0x44, 0x3d, 0x00, 0x7f, 0x10, 0x28, 0x44, 0x00, 0x00, 0x41, 0x7f, 0x40, 0x00, 0x7c, 0x04, 0x18, 0x04, 0x78, 0x7c, 0x08, 0x04, 0x04, 0x78, 0x38, 0x44, 0x44, 0x44, 0x38, 0x7c, 0x14, 0x14, 0x14, 0x08, 0x08, 0x14, 0x14, 0x18, 0x7c, 0x7c, 0x08, 0x04, 0x04, 0x08, 0x48, 0x54, 0x54, 0x54, 0x20, 0x04, 0x3f, 0x44, 0x40, 0x20, 0x3c, 0x40, 0x40, 0x20, 0x7c, 0x1c, 0x20, 0x40, 0x20, 0x1c, 0x3c, 0x40, 0x30, 0x40, 0x3c, 0x44, 0x28, 0x10, 0x28, 0x44, 0x0c, 0x50, 0x50, 0x50, 0x3c, 0x44, 0x64, 0x54, 0x4c, 0x44, 0x00, 0x08, 0x36, 0x41, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x41, 0x36, 0x08, 0x00, 0x10, 0x08, 0x08, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool initialized = false;
    bool spiPinsChanged = false;

    MicroBitPin *Rst   = getPin(MICROBIT_ID_IO_P10);
    MicroBitPin *Ce    = getPin(MICROBIT_ID_IO_P11);
    MicroBitPin *Dc    = getPin(MICROBIT_ID_IO_P12);
    MicroBitPin *Light = getPin(MICROBIT_ID_IO_P16);

    // Function declarations needed by initialize
    void write(MessageType messageType, uint8_t message);
    void clear();

    void initialize()
    {
        initialized = true;
        pins::spiFormat(8, 0);
        pins::spiFrequency(1000000);
        if (!spiPinsChanged) {
            pins::spiPins((DigitalPin)MICROBIT_ID_IO_P15, (DigitalPin)MICROBIT_ID_IO_P14, (DigitalPin)MICROBIT_ID_IO_P13);
        }
        Ce->setDigitalValue(1);
        Rst->setDigitalValue(0);
        fiber_sleep(10);
        Rst->setDigitalValue(1);
        write(Command, 0x21);
        write(Command, 0xBF);
        write(Command, 0x04);
        write(Command, 0x14);
        write(Command, 0x0C);
        write(Command, 0x20);
        write(Command, 0x0C);

        clear();
    }

    void write(MessageType messageType, uint8_t message) {
        if (!initialized) {
            initialize();
        }
        Dc->setDigitalValue(messageType);
        Ce->setDigitalValue(0);
        pins::spiWrite(message);
        Ce->setDigitalValue(1);
    }

    /**
    * Sets the x position of the cursor.
    * @param x number between 0 and 83 (inclusive).
    */
    //% blockId="display_set_x_position" block="set x position to %x"
    //% x.min=0 x.max=83
    void setXPosition(uint8_t x) {
        write(Command, 0x80 | x);
        xPosition = x;
    }

    /**
    * sets the y position of the cursor.
    * @param y number between 0 and 5 (inclusive).
    */
    //% blockId="display_set_y_position" block="set y position to %y"
    //% y.min=0 y.max=5
    void setYPosition(uint8_t y) {
        write(Command, 0x40 | y);
        yPosition = y;
    }

    /**
    * Sets boths the x and y position of the cursor.
    * @param x number between 0 and 83 (inclusive).
    * @param y number between 0 and 5 (inclusive).
    */
    //% blockId="display_set_x_y_position" block="set x to %x| and y to %y"
    //% x.min=0 x.max=83
    //% y.min=0 y.max=5
    void setXYPosition(uint8_t x, uint8_t y) {
        setXPosition(x);
        setYPosition(y);
    }

    /**
    * Clears the display.
    */
    //% blockId="display_clear" block="clear the display"
    void clear() {
        setXYPosition(0, 0);
        // Fill the screen with empty bytes (6*84=504)
        for (int i = 0; i < 504; i++) {
            write(Data, 0x00);
        }  
    }

    /**
    * Turns the backlight on (1) or off (0)
    */
    //% blockId="display_set_backlight" block="set backlight %value"
    //% value.min=0 value.max=1
    void setBacklight(uint8_t value) {
        Light->setDigitalValue((value + 1) % 2); // The baclight is active low, so transform 1->0 and vice versa
    }

    // TODO?: refactor
    /**
    * Print the provided text. Supports newline in JavaScript 
    * (but probably not in block-editor due to handling of strings),
    * continues on next line if the line is too long,
    * wont begin a character on one line, to finis on the next.
    * @param text The text to print.
    * @note If the text continues below the bottom of the screen, it will wrap around to the top.
    */
    //% blockId="display_print" block="print %text"
    void print(StringData *text) {
        ManagedString s(text);
        for (int index = 0; index < s.length(); index++) {
            if (s.charAt(index) == '\n') {
                if (yPosition == 5) {
                    yPosition = 0;
                } else {
                    yPosition++;
                }
                xPosition = 0;
                setXYPosition(xPosition, yPosition);
                continue;
            }

            // Check that it is enough space left on curren row to print a full character
            if (xPosition > 79) {
                if (yPosition == 5) {
                    yPosition = 0;
                } else {
                    yPosition++;
                }
                xPosition = 0;
                setXYPosition(xPosition, yPosition);
            }

            int i = ((int)s.charAt(index) - 32) * 5;
            for (int offset = 0; offset < 5; offset++) {
                write(Data, font[i + offset]);
                // Update x and y position
                if (xPosition == 79) {
                    if (yPosition == 5) {
                        yPosition = 0;
                    } else {
                        yPosition++;
                    }
                    xPosition = 0;
                } else {
                    xPosition++;
                }
            }
        }
    }

    #if 0 // Does not work
    ///**
    //* Change the connected pins from the default values.
    //*/
    ////% blockId="display_change_SPI_pins" block="set pins DIN %DIN| CLK %CLK| LIGHT %LIGHT| Unused pin for MISO %MISO"
    ////% advanced=true
    void changeSPIPins(DigitalPin DIN, DigitalPin CLK, DigitalPin MISO) {
        initialized = false;
        spiPinsChanged = true;
        //serial.send("SPI changing\n");
        //Clk = getPin((int)CLK);
        //Din = getPin((int)DIN);
        //Miso = getPin((int)MISO);
        //serial.send("SPI pins changed\n");
        pins::spiPins(DIN, CLK, MISO);
        //serial.send("SPI changed\n");
    }
    #endif

    /**
    * Change what pins that is used for RST, CE and DC.
    */
    //% blockId="display_change_BUS_pins" block="set pins RST %RST| CE %CE| DC %DC"
    //% advanced=true
    void changeBusPins(DigitalPin RST, DigitalPin CE, DigitalPin DC) {
        initialized = false;
        Rst = getPin((int)RST);
        Ce = getPin((int)CE);
        Dc = getPin((int)DC);

    }

    /**
    * Change what pin that is used for LIGHT.
    */
    //% blockId="display_change_LIGHT_pins" block="set pin LIGHT %LIGHT"
    //% advanced=true
    void changeLightPin(DigitalPin LIGHT) {
        Light = getPin((int)LIGHT);
    }
}