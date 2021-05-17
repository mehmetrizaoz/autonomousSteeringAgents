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
   * @brief color of the entity
   */
   color entityColor;

private:
   string name;
   int id;
};
