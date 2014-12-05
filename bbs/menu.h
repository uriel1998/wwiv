/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.0x                         */
/*             Copyright (C)1998-2014, WWIV Software Services             */
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
#ifndef __INCLUDED_MENU_H__
#define __INCLUDED_MENU_H__

#include <cstdint>
#include <map>
#include <string>

#include "bbs/vars.h"
#include "core/file.h"
#include "core/stl.h"
#include "core/textfile.h"

#define MENU
#define MENU_VERSION 0x0100

#define TEST_PADDING (5)

// 'iWhich' : Which messages to read in function ReadSelectedMessages
#define RM_ALL_MSGS   (-1)
#define RM_QSCAN_MSGS (-2)


// 'iWhere' : Which subs to read in function ReadSelectedMessages
#define RM_ALL_SUBS   (-1)
#define RM_QSCAN_SUBS (-2)

#define MENU_FLAG_DELETED   (0x01)
#define MENU_FLAG_MAINMENU  (0x02)


#define MENU_NUMFLAG_NOTHING   ( 0 )
#define MENU_NUMFLAG_SUBNUMBER ( 1 )
#define MENU_NUMFLAG_DIRNUMBER ( 2 )
#define MENU_NUMFLAG_LAST      ( 3 )

#define MENU_LOGTYPE_KEY       ( 0 )
#define MENU_LOGTYPE_NONE      ( 1 )
#define MENU_LOGTYPE_COMMAND   ( 2 )
#define MENU_LOGTYPE_DESC      ( 3 )
#define MENU_LOGTYPE_LAST      ( 4 )

#define MENU_HELP_DONTFORCE    ( 0 )
#define MENU_HELP_FORCE        ( 1 )
#define MENU_HELP_ONENTRANCE   ( 2 )
#define MENU_HELP_LAST         ( 3 )

#define MENU_HIDE_NONE         ( 0 )
#define MENU_HIDE_PULLDOWN     ( 1 )
#define MENU_HIDE_REGULAR      ( 2 )
#define MENU_HIDE_BOTH         ( 3 )
#define MENU_HIDE_LAST         ( 4 )

#define MENU_ALLOWED_BOTH      ( 0 )
#define MENU_ALLOWED_PULLDOWN  ( 1 )
#define MENU_ALLOWED_REGULAR   ( 2 )
#define MENU_ALLOWED_LAST      ( 3 )

#define PDFLAGS_NOCLEAR       (0x0001)
#define PDFLAGS_NORESTORE     (0x0002)
#define PDFLAGS_NOPAUSEAFTER  (0x0004)
#define MENU_MAX_KEYS (10)

#pragma pack(push, 1)

struct MenuHeader {
  char   szSig[10];      /* Menu Signature */
  uint16_t  nHeadBytes;  /* Size of Menu header */
  uint16_t  nBodyBytes;  /* Size of Menu Record */
  char   MISC[50];

  uint16_t  nVersion;
  uint16_t  nEmpty;
  uint8_t   nFlags;

  uint8_t   nNumbers;     /* What does a number do?  Set sub#, Dir#, nothing? */
  uint8_t   nLogging;     /* Types of logging, Key, None, command, desc       */

  uint8_t   nForceHelp;   /* force, dont force, on entrance only              */
  uint8_t   nAllowedMenu; /* Can pulldown, regular or both menus be used?     */

  uint8_t  nTitleColor, nMainBorderColor, nMainBoxColor, nMainTextColor,
           nMainTextHLColor, nMainSelectedColor, nMainSelectedHLColor;

  uint8_t  nItemBorderColor, nItemBoxColor, nItemTextColor, nItemTextHLColor,
           nItemSelectedColor, nItemSelectedHLColor;

  char   szMenuTitle[21];
  char   MISC2[60];
  char   szPassWord[21];     /* required for entry of menu */
  uint16_t nMinSL, nMinDSL;    /* required for entry of menu */
  uint16_t uAR, uDAR;          /* required for entry of menu */
  uint16_t uRestrict;          /* not allowed restrictions   */
  uint8_t  nSysop, nCoSysop;   /* Must be either sysop or co */
  char   MISC3[30];
  char   szScript[101];      /* Gets executed on entry     */
  char   szExitScript[101];  /* Executed on rtn from menu  */
};

struct MenuRec {
  uint8_t nFlags;   /* AFLAG_????? */

  char szKey[MENU_MAX_KEYS + 1]; /* Keystrock to execute menu item   */
  char szExecute[101];           /* Command to execute               */
  char szMenuText[41];           /* Menu description                 */
  char unused_szPDText[41];      /* Pulldown menu text               */

  char szHelp[81];               /* Help for this item               */
  char szSysopLog[51];           /* Msg to put in the log            */

  char szInstanceMessage[81];

  /* Security */
  uint16_t nMinSL,  iMaxSL;
  uint16_t nMinDSL, iMaxDSL;
  uint16_t uAR, uDAR;        /* Must match all specified to be able to run     */
  uint16_t uRestrict;        /* If any of these restrictions, you cant execute */
  uint8_t nSysop, nCoSysop;  /* true and false, does it take a co/sysop to run */
  char szPassWord[21];

  uint16_t nHide;            /* Hide text from PD/Regular/both or no menus */
  uint16_t unused_nPDFlags;  /* special characteristis for pulldowns       */

  char szExtendedHelp[13];   /* filename to detailed help on this item */
  char unused_data[79];
};

struct MenuRecIndex {
  char szKey[MENU_MAX_KEYS + 1];
  uint16_t nRec;        /* allows alot of records    */
  uint8_t nFlags;             /* Quick access to the flags */
};

class MenuInstanceData {
public:
  MenuInstanceData();
  ~MenuInstanceData();
  std::string menu;
  std::string path;
  File *pMenuFile;
  uint16_t nAmountRecs;
  bool finished;
  bool reload;  /* true if we are going to reload the menus */

  std::string prompt;
  MenuRecIndex *index;
  MenuHeader header;   /* Hold header info for current menu set in memory */
};

#pragma pack(pop)

namespace wwiv {
namespace menus {

class MenuDescriptions {
public:
  MenuDescriptions(const std::string& menupath);
  ~MenuDescriptions();
  const std::string description(const std::string& name);
  bool set_description(const std::string& name, const std::string& description);

private:
  std::string menupath_;
  std::map<std::string, std::string, wwiv::stl::ci_less> descriptions_;
};

}
}

// Functions used b bbs.cpp and defaults.cpp
void mainmenu();
void ConfigUserMenuSet();

// Functions used by menuedit and menu
const std::string GetMenuDirectory(const std::string menuPath);
const std::string GetMenuDirectory(const std::string menuPath, const std::string menuName, const std::string extension);
const std::string GetMenuDirectory();
void MenuSysopLog(const std::string pszMsg);

// Used by menuinterpretcommand.cpp
void TurnMCIOff();
void TurnMCIOn();
int  GetMenuIndex(const char* pszCommand);
void Menus(MenuInstanceData * pMenuData, const std::string menuDirectory, const std::string menuName);
char *MenuParseLine(char *pszSrc, char *pszCmd, char *pszParam1, char *pszParam2);
void AMDisplayHelp(MenuInstanceData * pMenuData);

#endif  // __INCLUDED_MENU_H__
