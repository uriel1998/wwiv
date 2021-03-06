/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*                   Copyright (C)2020, WWIV Software Services            */
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
#include "bbs/acs.h"

#include "bbs/application.h"
#include "bbs/bbs.h"
#include "common/input.h"
#include "core/stl.h"
#include "sdk/acs/acs.h"
#include "sdk/acs/uservalueprovider.h"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;
using namespace wwiv::stl;
using namespace wwiv::sdk::acs;
using namespace wwiv::strings;

namespace wwiv::bbs {

bool check_acs(const std::string& expression, acs_debug_t debug) {
  if (StringTrim(expression).empty()) {
    // Empty expression is always allowed.
    return true;
  }
  auto [result, debug_info] = sdk::acs::check_acs(*a()->config(), a()->user(),
                                                  a()->sess().effective_sl(), expression, debug);
  for (const auto& l : debug_info) {
    if (debug == acs_debug_t::local) {
      LOG(INFO) << l;
    } else if (debug == acs_debug_t::remote) {
      bout << l << endl;
    }
  }

  return result;
}

bool validate_acs(const std::string& expression, acs_debug_t debug) {
  auto [result, ex_what, debug_info] =
      sdk::acs::validate_acs(*a()->config(), a()->user(), a()->sess().effective_sl(), expression);
  if (result) {
    return true;
  }
  if (debug == acs_debug_t::local) {
    LOG(INFO) << ex_what;
  } else if (debug == acs_debug_t::remote) {
    bout << ex_what << wwiv::endl;
  }
  for (const auto& l : debug_info) {
    if (debug == acs_debug_t::local) {
      LOG(INFO) << l;
    } else if (debug == acs_debug_t::remote) {
      bout << l << endl;
    }
  }
  return false;
}

std::string input_acs(wwiv::common::Input& in, wwiv::common::Output& out,
                      const std::string& orig_text, int max_length) {
  auto s = in.input_text(orig_text, max_length);

  if (!validate_acs(s, acs_debug_t::remote)) {
    out.pausescr();
    return orig_text;
  }
  return s;
}

} // namespace wwiv::bbs
