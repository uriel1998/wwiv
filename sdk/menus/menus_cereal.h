/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*                  Copyright (C)2020, WWIV Software Services             */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/

#ifndef INCLUDED_SDK_FILES_MENUS_CEREAL_H
#define INCLUDED_SDK_FILES_MENUS_CEREAL_H

#include "core/cereal_utils.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "sdk/uuid_cereal.h"
#include "sdk/menus/menu.h"

namespace wwiv::sdk::menus {


template <class Archive>
void serialize (Archive& ar, menu_action_56_t& d) {
  SERIALIZE(d, cmd);
  SERIALIZE(d, data);
  SERIALIZE(d, acs);
}

template <class Archive>
void serialize(Archive & ar, menu_item_56_t& s) {
  SERIALIZE(s, item_key);
  SERIALIZE(s, item_text);
  SERIALIZE(s, help_text);
  SERIALIZE(s, log_text);
  SERIALIZE(s, instance_message);
  SERIALIZE(s, acs);
  SERIALIZE(s, password);
  SERIALIZE(s, actions);
}

template <class Archive>
void serialize(Archive & ar, menu_56_t& s) {
  SERIALIZE(s, num_action);
  SERIALIZE(s, logging_action);
  SERIALIZE(s, help_type);
  SERIALIZE(s, color_title);
  SERIALIZE(s, color_item_key);
  SERIALIZE(s, color_item_text);
  SERIALIZE(s, color_item_braces);
  SERIALIZE(s, title);
  SERIALIZE(s, acs);
  SERIALIZE(s, password);
  SERIALIZE(s, enter_actions);
  SERIALIZE(s, exit_actions);
  SERIALIZE(s, items);
}


}


#endif
