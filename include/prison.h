#pragma once

/**
 * @file   prison.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  agents cant escape from field scenario
 * @date   15.05.2021
*/

#include "scenario.h"
#include <vector>

using namespace std;

class prison: public scenario{
public:
   /**
   * @brief default constructor.
   */
   prison();

   /**
   * prison loop function
   * @brief prisoning scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

