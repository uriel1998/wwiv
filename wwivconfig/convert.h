/**************************************************************************/
/*                                                                        */
/*                  WWIV Initialization Utility Version 5                 */
/*             Copyright (C)1998-2020, WWIV Software Services             */
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
#ifndef INCLUDED_WWIVCONFIG_CONVERT_H
#define INCLUDED_WWIVCONFIG_CONVERT_H

#include "localui/curses_win.h"
#include "sdk/config.h"

enum class config_upgrade_state_t { already_latest, upgraded };
bool ensure_offsets_are_updated(UIWindow* window, const wwiv::sdk::Config&);
void convert_config_424_to_430(UIWindow* window, const std::string& datadir,
                               const std::string& config_filename);
config_upgrade_state_t convert_config_to_52(UIWindow* window, const std::string& config_filename);
config_upgrade_state_t ensure_latest_5x_config(UIWindow* window, const std::string& datadir,
                                               const std::string& config_filename,
                                               uint32_t config_revision_number);

#endif
