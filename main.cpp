/*
 * ----------------------------------------------------------------------------
 * Author: Caili Li
 * Email: caili@autox.ai
 *
 * Copyright (C) 2016-2018 AutoX, Inc.
 * ----------------------------------------------------------------------------
 */
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cmath>
#include "keyboard.hpp"
#include <atomic>

using namespace std::chrono;
using namespace std::chrono_literals;

int main(){

  std::atomic<bool> run_flag(true);

  std::cout << "Press 'q' to quit\n";
  while (run_flag) {

    char key = io::readKeyboard();

    switch (key) {
      case 'q':
        std::cout << "\nexit\n";
        run_flag = false;
        break;
      
      default:
        break;
    }

    std::this_thread::sleep_for(5ms);
  }
  return 0;
}
