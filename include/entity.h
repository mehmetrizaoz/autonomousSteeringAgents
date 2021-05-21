#pragma once

#include <string>
#include "color.h"

using namespace std;

class graphics;

class entity{
public:
   /**   
   * @brief default constructor.
   */
   entity();

   /**   
   * @brief getter of the name
   */
   string getName();

   /**   
   * @brief name attribute setter
   * @param name setter 
   */
   void setName(string name);

   /**   
   * @brief getter of the id attibute
   */
   int getId();

   /**   
   * @brief id attribute setter
   * @param id setter
   */
   void setId(int id);
   
   /**   
   * @brief overriden by child classes
   * @param view graphics
   */
   virtual void draw(graphics view)=0;

   /**   
   * @brief getter of the color attibute
   */  
   color getColor();
   
   /**   
   * @brief getter of the color attibute
   */   
   void setColor(color color);

private:
   color entityColor;
   string name;
   int id;
};
