#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "XKeyboard.h"

void write_kbd_layout(std::string filename, std::string layout) {
  std::ofstream f(filename.c_str());
  f << layout;
  f.close();

  if (system("killall -USR1 i3status")) {
    std::cerr << "Error sending SIGUSR1 to i3status process" << std::endl;
  }
}

std::string get_new_layout(XKeyboard &xkb) {
  std::string layout = xkb.currentGroupSymbol();
  std::transform(layout.begin(), layout.end(), layout.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return layout;
}

void watch_layouts(XKeyboard &xkb) {
  std::string filename = std::string(getenv("HOME")) + "/.i3status-kbd-layout";
  std::string current_layout = get_new_layout(xkb);
  write_kbd_layout(filename, current_layout);

  while (1) {
    usleep(1e5);

    std::string new_layout = get_new_layout(xkb);
    if (new_layout != current_layout) {
      current_layout = new_layout;
      write_kbd_layout(filename, current_layout);
    }
  }
}

int main(int argc, char **argv) {
  for (int retry; retry < 10; ++retry) {
    try {
      XKeyboard xkb;
      watch_layouts(xkb);
      break;
    } catch (std::exception &e) {
      std::cerr << "Error initializing XKeyboard: " << e.what() << std::endl;
      usleep(1e6);
    }
  }
}
