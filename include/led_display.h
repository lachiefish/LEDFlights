#pragma once

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <sstream>
#include <vector>
#include <string>

class LEDDisplay
{
private:
  MatrixPanel_I2S_DMA dma_display;
  std::vector<std::string> last_row_text;

public:
  LEDDisplay(HUB75_I2S_CFG config = HUB75_I2S_CFG(64, 32, 1)); // Default is 64x32 with 1 panel

  template <typename T>
  void printRowText(T value, int row_num, std::string append = "", int column_num = 0)
  {
    std::ostringstream oss;
    oss << value << append;
    std::string text = oss.str();

    if (last_row_text[row_num] == text)
    {
      return;
    }
    else
    {
      if (column_num != 0)
      {
        dma_display.setCursor(0, (row_num * 8));
        dma_display.print(std::string((column_num / 6) + 1, ' ').c_str()); // Clears the start of a line beacause it won't be written over if column_num is not 0.
      }
      last_row_text[row_num] = text;
    }

    dma_display.fillRect(dma_display.width() - 4, row_num * 8, 4, 8, dma_display.color444(0, 0, 0)); // Can't use characters to clear the row (' '). Need to draw a rect over the final character because an offset may have been used.
    dma_display.setCursor(column_num, (row_num * 8));
    if (text.length() > 10)
    {
      text = text.substr(0, 10);
    }
    else if (text.length() < 10)
    {
      text += std::string(10 - text.length(), ' ');
    }
    dma_display.print(text.c_str());
  }

  void clearRow(int row_number);
  void clearScreen();
  void setTextSize(int size);
  void setBrightness(int brightness);
  void flipBuffer();
};