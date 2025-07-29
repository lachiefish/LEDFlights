#include "led_display.h"

LEDDisplay::LEDDisplay(HUB75_I2S_CFG config) : dma_display(config), last_row_text(dma_display.height() / 8, "")
{
  dma_display.begin();
  dma_display.clearScreen();
  dma_display.setTextWrap(false);
  dma_display.setTextColor(dma_display.color444(9, 4, 2), dma_display.color444(0, 0, 0));
  dma_display.println("Booting");
  dma_display.println("disaply");
}

void LEDDisplay::clearRow(int row_num)
{
  dma_display.fillRect(0, row_num * 8, dma_display.width(), 8, dma_display.color444(0, 0, 0));
}

void LEDDisplay::clearScreen()
{
  dma_display.clearScreen();
}

void LEDDisplay::setTextSize(int size)
{
  dma_display.setTextSize(size);
}

void LEDDisplay::setBrightness(int brightness)
{
  if (brightness < 0 || brightness > 255)
  {
    Serial.println("Brightness must be between 0 and 255");
    return;
  }
  dma_display.setBrightness(brightness);
}

void LEDDisplay::flipBuffer()
{
  dma_display.flipDMABuffer();
}