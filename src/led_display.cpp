#include "led_display.h"
#include "config.h"

LEDDisplay::LEDDisplay(HUB75_I2S_CFG config) : dma_display(config), last_row_text(PANEL_HEIGHT / 8, "")
{
  dma_display.begin();
  dma_display.clearScreen();
  dma_display.setTextWrap(false);
  dma_display.setBrightness(PANEL_BRIGHTNESS);
  dma_display.setTextColor(dma_display.color444(9, 4, 2), dma_display.color444(0, 0, 0));
  dma_display.println("Booting");
  dma_display.println("disaply");
}

// template void LEDDisplay::printRowText<std::string>(std::string, int, std::string, int);
// template void LEDDisplay::printRowText<int>(int, int, std::string, int);
// template void LEDDisplay::printRowText<float>(float, int, std::string, int);

void LEDDisplay::clearRow(int row_num)
{
  dma_display.fillRect(0, row_num * 8, PANEL_WIDTH, 8, dma_display.color444(0, 0, 0));
}

void LEDDisplay::clearScreen()
{
  dma_display.clearScreen();
}

void LEDDisplay::setTextSize(int size)
{
  dma_display.setTextSize(size);
}

void LEDDisplay::flipBuffer()
{
  dma_display.flipDMABuffer();
}