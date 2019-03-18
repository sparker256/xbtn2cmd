// ****** readinifile.cpp **********
// ****  William R. Good  ********

#include "XPLMCamera.h"
#include "XPLMDataAccess.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMMenus.h"
#include "XPLMPlanes.h"
#include "XPLMPlugin.h"
#include "XPLMProcessing.h"
#include "XPLMUtilities.h"

#include "inireader.h"
#include "xbtn2cmd.h"
#include <vector>

#include <fstream>
#include <iostream>
//#include <string>
#include <cstring>

string convert_Mac_Path(string in_path) {

  std::size_t len = in_path.length();
  std::size_t pos = in_path.find(':');

  in_path.erase(in_path.begin() + 0, in_path.end() - (len - pos));

  int count = 0;
  for (char i : in_path)
    if (i == ':')
      count++;

  size_t found;
  int n = count;

  while (n > 0) {
    found = in_path.find(':');
    in_path.replace(found, 1, "/");
    --n;
  }

  std::size_t pos2 = in_path.find("/Aircraft");
  std::string tmp_in_path = in_path.substr(pos2);
  tmp_in_path.insert(0, ".");
  in_path = tmp_in_path;

  return in_path;
}

// ***** Configuration File Process ******
void process_read_ini_file()

{
  char *iniDefaultPluginPath;

  iniDefaultPluginPath =
      const_cast<char *>("./Resources/plugins/Xbtn2cmd/xbtn2cmd.ini");
  string version;

  cleanupIniReader();

  char xpsacfname[512];
  char xpsacfpath[512];
  XPLMGetNthAircraftModel(0, xpsacfname, xpsacfpath);

  if (strlen(xpsacfpath) == 0) {
    return;
  }

  std::string xpsini_path_name = xpsacfpath;
  std::size_t pos = xpsini_path_name.find(xpsacfname);
  xpsini_path_name = xpsini_path_name.substr(0, pos);

  std::string xpsini_aircraft_name = xpsacfname;
  std::size_t pos1 = xpsini_aircraft_name.find(".acf");
  xpsini_aircraft_name = xpsini_aircraft_name.substr(0, pos1);

  std::string xpsini_path_name1 = xpsini_path_name;

  xpsini_path_name1.append("xbtn2cmd.ini");

  xpsini_path_name.append(xpsini_aircraft_name);

  xpsini_path_name.append("_xbtn2cmd.ini");

  int found_file = 0;

  std::vector<char> parse_ini_path_name(xpsini_path_name.size() + 1);
  std::copy(xpsini_path_name.begin(), xpsini_path_name.end(),
            parse_ini_path_name.begin());

  std::ifstream ifile(&parse_ini_path_name[0]);
  if (ifile) {
    XPLMDebugString("\nXbtn2cmd: Found xbtn2cmd.ini in the current aircraft "
                    "path and it is\n");
    XPLMDebugString(&parse_ini_path_name[0]);
    XPLMDebugString("\n");

    parseIniFile(&parse_ini_path_name[0]);
    found_file = 1;
    xbtn2cmdini_path_name = &parse_ini_path_name[0];

  } else if (!ifile) {
    std::vector<char> parse_ini_path_name1(xpsini_path_name1.size() + 1);
    std::copy(xpsini_path_name1.begin(), xpsini_path_name1.end(),
              parse_ini_path_name1.begin());

    std::ifstream ifile1(&parse_ini_path_name1[0]);
    if (ifile1) {
      XPLMDebugString("\nXbtn2cmd: Found xbtn2cmd.ini in the current aircraft "
                      "path and it is\n");
      XPLMDebugString(&parse_ini_path_name1[0]);
      XPLMDebugString("\n");

      parseIniFile(&parse_ini_path_name1[0]);
      found_file = 1;
      xbtn2cmdini_path_name = &parse_ini_path_name1[0];
    }
    if (found_file == 0) {
      XPLMDebugString("\nXbtn2cmd: Did not find xbtn2cmd.ini in the current "
                      "aircraft path\n");
    }

    std::ifstream ifile2(iniDefaultPluginPath);
    if (ifile2) {
      if (found_file == 0) {

        XPLMDebugString("\nXbtn2cmd: Found xbtn2cmd.ini in the Xbtn2cmd plugin "
                        "path and it is\n");
        XPLMDebugString(iniDefaultPluginPath);
        XPLMDebugString("\n");

        parseIniFile(iniDefaultPluginPath);
        xbtn2cmdini_path_name = iniDefaultPluginPath;
      }
    } else {
      return;
    }
  }

  version = getOptionToString("Version");
  XPLMDebugString("\nXbtn2cmd: xbtn2cmd.ini is version   ");
  XPLMDebugString(version.c_str());
  XPLMDebugString("\n");

  // ****************** page one   ***************************

  page1_button_label = getOptionToString("page1_button_label");

  page1_button1_label = getOptionToString("page1_button1_label");
  page1_button1_command_once = getOptionToString("page1_button1_command_once");
  page1_button1_command_continue =
      getOptionToString("page1_button1_command_continue");
  Page1_Button1LabelCmd = XPLMFindCommand(page1_button1_label.c_str());
  Page1_Button1CommandOnceCmd =
      XPLMFindCommand(page1_button1_command_once.c_str());
  Page1_Button1CommandContinueCmd =
      XPLMFindCommand(page1_button1_command_continue.c_str());

  page1_button2_label = getOptionToString("page1_button2_label");
  page1_button2_command_once = getOptionToString("page1_button2_command_once");
  page1_button2_command_continue =
      getOptionToString("page1_button2_command_continue");
  Page1_Button2LabelCmd = XPLMFindCommand(page1_button2_label.c_str());
  Page1_Button2CommandOnceCmd =
      XPLMFindCommand(page1_button2_command_once.c_str());
  Page1_Button2CommandContinueCmd =
      XPLMFindCommand(page1_button2_command_continue.c_str());

  page1_button3_label = getOptionToString("page1_button3_label");
  page1_button3_command_once = getOptionToString("page1_button3_command_once");
  page1_button3_command_continue =
      getOptionToString("page1_button3_command_continue");
  Page1_Button3LabelCmd = XPLMFindCommand(page1_button3_label.c_str());
  Page1_Button3CommandOnceCmd =
      XPLMFindCommand(page1_button3_command_once.c_str());
  Page1_Button3CommandContinueCmd =
      XPLMFindCommand(page1_button3_command_continue.c_str());

  page1_button4_label = getOptionToString("page1_button4_label");
  page1_button4_command_once = getOptionToString("page1_button4_command_once");
  page1_button4_command_continue =
      getOptionToString("page1_button4_command_continue");
  Page1_Button4LabelCmd = XPLMFindCommand(page1_button4_label.c_str());
  Page1_Button4CommandOnceCmd =
      XPLMFindCommand(page1_button4_command_once.c_str());
  Page1_Button4CommandContinueCmd =
      XPLMFindCommand(page1_button4_command_continue.c_str());

  page1_button5_label = getOptionToString("page1_button5_label");
  page1_button5_command_once = getOptionToString("page1_button5_command_once");
  page1_button5_command_continue =
      getOptionToString("page1_button5_command_continue");
  Page1_Button5LabelCmd = XPLMFindCommand(page1_button5_label.c_str());
  Page1_Button5CommandOnceCmd =
      XPLMFindCommand(page1_button5_command_once.c_str());
  Page1_Button5CommandContinueCmd =
      XPLMFindCommand(page1_button5_command_continue.c_str());

  page1_button6_label = getOptionToString("page1_button6_label");
  page1_button6_command_once = getOptionToString("page1_button6_command_once");
  page1_button6_command_continue =
      getOptionToString("page1_button6_command_continue");
  Page1_Button6LabelCmd = XPLMFindCommand(page1_button6_label.c_str());
  Page1_Button6CommandOnceCmd =
      XPLMFindCommand(page1_button6_command_once.c_str());
  Page1_Button6CommandContinueCmd =
      XPLMFindCommand(page1_button6_command_continue.c_str());

  page1_button7_label = getOptionToString("page1_button7_label");
  page1_button7_command_once = getOptionToString("page1_button7_command_once");
  page1_button7_command_continue =
      getOptionToString("page1_button7_command_continue");
  Page1_Button7LabelCmd = XPLMFindCommand(page1_button7_label.c_str());
  Page1_Button7CommandOnceCmd =
      XPLMFindCommand(page1_button7_command_once.c_str());
  Page1_Button7CommandContinueCmd =
      XPLMFindCommand(page1_button7_command_continue.c_str());

  page1_button8_label = getOptionToString("page1_button8_label");
  page1_button8_command_once = getOptionToString("page1_button8_command_once");
  page1_button8_command_continue =
      getOptionToString("page1_button8_command_continue");
  Page1_Button8LabelCmd = XPLMFindCommand(page1_button8_label.c_str());
  Page1_Button8CommandOnceCmd =
      XPLMFindCommand(page1_button8_command_once.c_str());
  Page1_Button8CommandContinueCmd =
      XPLMFindCommand(page1_button8_command_continue.c_str());

  page1_button9_label = getOptionToString("page1_button9_label");
  page1_button9_command_once = getOptionToString("page1_button9_command_once");
  page1_button9_command_continue =
      getOptionToString("page1_button9_command_continue");
  Page1_Button9LabelCmd = XPLMFindCommand(page1_button9_label.c_str());
  Page1_Button9CommandOnceCmd =
      XPLMFindCommand(page1_button9_command_once.c_str());
  Page1_Button9CommandContinueCmd =
      XPLMFindCommand(page1_button9_command_continue.c_str());

  page1_button10_label = getOptionToString("page1_button10_label");
  page1_button10_command_once =
      getOptionToString("page1_button10_command_once");
  page1_button10_command_continue =
      getOptionToString("page1_button10_command_continue");
  Page1_Button10LabelCmd = XPLMFindCommand(page1_button10_label.c_str());
  Page1_Button10CommandOnceCmd =
      XPLMFindCommand(page1_button10_command_once.c_str());
  Page1_Button10CommandContinueCmd =
      XPLMFindCommand(page1_button10_command_continue.c_str());

  page1_button11_label = getOptionToString("page1_button11_label");
  page1_button11_command_once =
      getOptionToString("page1_button11_command_once");
  page1_button11_command_continue =
      getOptionToString("page1_button11_command_continue");
  Page1_Button11LabelCmd = XPLMFindCommand(page1_button11_label.c_str());
  Page1_Button11CommandOnceCmd =
      XPLMFindCommand(page1_button11_command_once.c_str());
  Page1_Button11CommandContinueCmd =
      XPLMFindCommand(page1_button11_command_continue.c_str());

  page1_button12_label = getOptionToString("page1_button12_label");
  page1_button12_command_once =
      getOptionToString("page1_button12_command_once");
  page1_button12_command_continue =
      getOptionToString("page1_button12_command_continue");
  Page1_Button12LabelCmd = XPLMFindCommand(page1_button12_label.c_str());
  Page1_Button12CommandOnceCmd =
      XPLMFindCommand(page1_button12_command_once.c_str());
  Page1_Button12CommandContinueCmd =
      XPLMFindCommand(page1_button12_command_continue.c_str());

  //  ************************   page two    ********************

  page2_button_label = getOptionToString("page2_button_label");

  page2_button1_label = getOptionToString("page2_button1_label");
  page2_button1_command_once = getOptionToString("page2_button1_command_once");
  page2_button1_command_continue =
      getOptionToString("page2_button1_command_continue");
  Page2_Button1LabelCmd = XPLMFindCommand(page2_button1_label.c_str());
  Page2_Button1CommandOnceCmd =
      XPLMFindCommand(page2_button1_command_once.c_str());
  Page2_Button1CommandContinueCmd =
      XPLMFindCommand(page2_button1_command_continue.c_str());

  page2_button2_label = getOptionToString("page2_button2_label");
  page2_button2_command_once = getOptionToString("page2_button2_command_once");
  page2_button2_command_continue =
      getOptionToString("page2_button2_command_continue");
  Page2_Button2LabelCmd = XPLMFindCommand(page2_button2_label.c_str());
  Page2_Button2CommandOnceCmd =
      XPLMFindCommand(page2_button2_command_once.c_str());
  Page2_Button2CommandContinueCmd =
      XPLMFindCommand(page2_button2_command_continue.c_str());

  page2_button3_label = getOptionToString("page2_button3_label");
  page2_button3_command_once = getOptionToString("page2_button3_command_once");
  page2_button3_command_continue =
      getOptionToString("page2_button3_command_continue");
  Page2_Button3LabelCmd = XPLMFindCommand(page2_button3_label.c_str());
  Page2_Button3CommandOnceCmd =
      XPLMFindCommand(page2_button3_command_once.c_str());
  Page2_Button3CommandContinueCmd =
      XPLMFindCommand(page2_button3_command_continue.c_str());

  page2_button4_label = getOptionToString("page2_button4_label");
  page2_button4_command_once = getOptionToString("page2_button4_command_once");
  page2_button4_command_continue =
      getOptionToString("page2_button4_command_continue");
  Page2_Button4LabelCmd = XPLMFindCommand(page2_button4_label.c_str());
  Page2_Button4CommandOnceCmd =
      XPLMFindCommand(page2_button4_command_once.c_str());
  Page2_Button4CommandContinueCmd =
      XPLMFindCommand(page2_button4_command_continue.c_str());

  page2_button5_label = getOptionToString("page2_button5_label");
  page2_button5_command_once = getOptionToString("page2_button5_command_once");
  page2_button5_command_continue =
      getOptionToString("page2_button5_command_continue");
  Page2_Button5LabelCmd = XPLMFindCommand(page2_button5_label.c_str());
  Page2_Button5CommandOnceCmd =
      XPLMFindCommand(page2_button5_command_once.c_str());
  Page2_Button5CommandContinueCmd =
      XPLMFindCommand(page2_button5_command_continue.c_str());

  page2_button6_label = getOptionToString("page2_button6_label");
  page2_button6_command_once = getOptionToString("page2_button6_command_once");
  page2_button6_command_continue =
      getOptionToString("page2_button6_command_continue");
  Page2_Button6LabelCmd = XPLMFindCommand(page2_button6_label.c_str());
  Page2_Button6CommandOnceCmd =
      XPLMFindCommand(page2_button6_command_once.c_str());
  Page2_Button6CommandContinueCmd =
      XPLMFindCommand(page2_button6_command_continue.c_str());

  page2_button7_label = getOptionToString("page2_button7_label");
  page2_button7_command_once = getOptionToString("page2_button7_command_once");
  page2_button7_command_continue =
      getOptionToString("page2_button7_command_continue");
  Page2_Button7LabelCmd = XPLMFindCommand(page2_button7_label.c_str());
  Page2_Button7CommandOnceCmd =
      XPLMFindCommand(page2_button7_command_once.c_str());
  Page2_Button7CommandContinueCmd =
      XPLMFindCommand(page2_button7_command_continue.c_str());

  page2_button8_label = getOptionToString("page2_button8_label");
  page2_button8_command_once = getOptionToString("page2_button8_command_once");
  page2_button8_command_continue =
      getOptionToString("page2_button8_command_continue");
  Page2_Button8LabelCmd = XPLMFindCommand(page2_button8_label.c_str());
  Page2_Button8CommandOnceCmd =
      XPLMFindCommand(page2_button8_command_once.c_str());
  Page2_Button8CommandContinueCmd =
      XPLMFindCommand(page2_button8_command_continue.c_str());

  page2_button9_label = getOptionToString("page2_button9_label");
  page2_button9_command_once = getOptionToString("page2_button9_command_once");
  page2_button9_command_continue =
      getOptionToString("page2_button9_command_continue");
  Page2_Button9LabelCmd = XPLMFindCommand(page2_button9_label.c_str());
  Page2_Button9CommandOnceCmd =
      XPLMFindCommand(page2_button9_command_once.c_str());
  Page2_Button9CommandContinueCmd =
      XPLMFindCommand(page2_button9_command_continue.c_str());

  page2_button10_label = getOptionToString("page2_button10_label");
  page2_button10_command_once =
      getOptionToString("page2_button10_command_once");
  page2_button10_command_continue =
      getOptionToString("page2_button10_command_continue");
  Page2_Button10LabelCmd = XPLMFindCommand(page2_button10_label.c_str());
  Page2_Button10CommandOnceCmd =
      XPLMFindCommand(page2_button10_command_once.c_str());
  Page2_Button10CommandContinueCmd =
      XPLMFindCommand(page2_button10_command_continue.c_str());

  page2_button11_label = getOptionToString("page2_button11_label");
  page2_button11_command_once =
      getOptionToString("page2_button11_command_once");
  page2_button11_command_continue =
      getOptionToString("page2_button11_command_continue");
  Page2_Button11LabelCmd = XPLMFindCommand(page2_button11_label.c_str());
  Page2_Button11CommandOnceCmd =
      XPLMFindCommand(page2_button11_command_once.c_str());
  Page2_Button11CommandContinueCmd =
      XPLMFindCommand(page2_button11_command_continue.c_str());

  page2_button12_label = getOptionToString("page2_button12_label");
  page2_button12_command_once =
      getOptionToString("page2_button12_command_once");
  page2_button12_command_continue =
      getOptionToString("page2_button12_command_continue");
  Page2_Button12LabelCmd = XPLMFindCommand(page2_button12_label.c_str());
  Page2_Button12CommandOnceCmd =
      XPLMFindCommand(page2_button12_command_once.c_str());
  Page2_Button12CommandContinueCmd =
      XPLMFindCommand(page2_button12_command_continue.c_str());

  //  ******************************  page three
  //  ***********************************

  page3_button_label = getOptionToString("page3_button_label");

  page3_button1_label = getOptionToString("page3_button1_label");
  page3_button1_command_once = getOptionToString("page3_button1_command_once");
  page3_button1_command_continue =
      getOptionToString("page3_button1_command_continue");
  Page3_Button1LabelCmd = XPLMFindCommand(page3_button1_label.c_str());
  Page3_Button1CommandOnceCmd =
      XPLMFindCommand(page3_button1_command_once.c_str());
  Page3_Button1CommandContinueCmd =
      XPLMFindCommand(page3_button1_command_continue.c_str());

  page3_button2_label = getOptionToString("page3_button2_label");
  page3_button2_command_once = getOptionToString("page3_button2_command_once");
  page3_button2_command_continue =
      getOptionToString("page3_button2_command_continue");
  Page3_Button2LabelCmd = XPLMFindCommand(page3_button2_label.c_str());
  Page3_Button2CommandOnceCmd =
      XPLMFindCommand(page3_button2_command_once.c_str());
  Page3_Button2CommandContinueCmd =
      XPLMFindCommand(page3_button2_command_continue.c_str());

  page3_button3_label = getOptionToString("page3_button3_label");
  page3_button3_command_once = getOptionToString("page3_button3_command_once");
  page3_button3_command_continue =
      getOptionToString("page3_button3_command_continue");
  Page3_Button3LabelCmd = XPLMFindCommand(page3_button3_label.c_str());
  Page3_Button3CommandOnceCmd =
      XPLMFindCommand(page3_button3_command_once.c_str());
  Page3_Button3CommandContinueCmd =
      XPLMFindCommand(page3_button3_command_continue.c_str());

  page3_button4_label = getOptionToString("page3_button4_label");
  page3_button4_command_once = getOptionToString("page3_button4_command_once");
  page3_button4_command_continue =
      getOptionToString("page3_button4_command_continue");
  Page3_Button4LabelCmd = XPLMFindCommand(page3_button4_label.c_str());
  Page3_Button4CommandOnceCmd =
      XPLMFindCommand(page3_button4_command_once.c_str());
  Page3_Button4CommandContinueCmd =
      XPLMFindCommand(page3_button4_command_continue.c_str());

  page3_button5_label = getOptionToString("page3_button5_label");
  page3_button5_command_once = getOptionToString("page3_button5_command_once");
  page3_button5_command_continue =
      getOptionToString("page3_button5_command_continue");
  Page3_Button5LabelCmd = XPLMFindCommand(page3_button5_label.c_str());
  Page3_Button5CommandOnceCmd =
      XPLMFindCommand(page3_button5_command_once.c_str());
  Page3_Button5CommandContinueCmd =
      XPLMFindCommand(page3_button5_command_continue.c_str());

  page3_button6_label = getOptionToString("page3_button6_label");
  page3_button6_command_once = getOptionToString("page3_button6_command_once");
  page3_button6_command_continue =
      getOptionToString("page3_button6_command_continue");
  Page3_Button6LabelCmd = XPLMFindCommand(page3_button6_label.c_str());
  Page3_Button6CommandOnceCmd =
      XPLMFindCommand(page3_button6_command_once.c_str());
  Page3_Button6CommandContinueCmd =
      XPLMFindCommand(page3_button6_command_continue.c_str());

  page3_button7_label = getOptionToString("page3_button7_label");
  page3_button7_command_once = getOptionToString("page3_button7_command_once");
  page3_button7_command_continue =
      getOptionToString("page3_button7_command_continue");
  Page3_Button7LabelCmd = XPLMFindCommand(page3_button7_label.c_str());
  Page3_Button7CommandOnceCmd =
      XPLMFindCommand(page3_button7_command_once.c_str());
  Page3_Button7CommandContinueCmd =
      XPLMFindCommand(page3_button7_command_continue.c_str());

  page3_button8_label = getOptionToString("page3_button8_label");
  page3_button8_command_once = getOptionToString("page3_button8_command_once");
  page3_button8_command_continue =
      getOptionToString("page3_button8_command_continue");
  Page3_Button8LabelCmd = XPLMFindCommand(page3_button8_label.c_str());
  Page3_Button8CommandOnceCmd =
      XPLMFindCommand(page3_button8_command_once.c_str());
  Page3_Button8CommandContinueCmd =
      XPLMFindCommand(page3_button8_command_continue.c_str());

  page3_button9_label = getOptionToString("page3_button9_label");
  page3_button9_command_once = getOptionToString("page3_button9_command_once");
  page3_button9_command_continue =
      getOptionToString("page3_button9_command_continue");
  Page3_Button9LabelCmd = XPLMFindCommand(page3_button9_label.c_str());
  Page3_Button9CommandOnceCmd =
      XPLMFindCommand(page3_button9_command_once.c_str());
  Page3_Button9CommandContinueCmd =
      XPLMFindCommand(page3_button9_command_continue.c_str());

  page3_button10_label = getOptionToString("page3_button10_label");
  page3_button10_command_once =
      getOptionToString("page3_button10_command_once");
  page3_button10_command_continue =
      getOptionToString("page3_button10_command_continue");
  Page3_Button10LabelCmd = XPLMFindCommand(page3_button10_label.c_str());
  Page3_Button10CommandOnceCmd =
      XPLMFindCommand(page3_button10_command_once.c_str());
  Page3_Button10CommandContinueCmd =
      XPLMFindCommand(page3_button10_command_continue.c_str());

  page3_button11_label = getOptionToString("page3_button11_label");
  page3_button11_command_once =
      getOptionToString("page3_button11_command_once");
  page3_button11_command_continue =
      getOptionToString("page3_button11_command_continue");
  Page3_Button11LabelCmd = XPLMFindCommand(page3_button11_label.c_str());
  Page3_Button11CommandOnceCmd =
      XPLMFindCommand(page3_button11_command_once.c_str());
  Page3_Button11CommandContinueCmd =
      XPLMFindCommand(page3_button11_command_continue.c_str());

  page3_button12_label = getOptionToString("page3_button12_label");
  page3_button12_command_once =
      getOptionToString("page3_button12_command_once");
  page3_button12_command_continue =
      getOptionToString("page3_button12_command_continue");
  Page3_Button12LabelCmd = XPLMFindCommand(page3_button12_label.c_str());
  Page3_Button12CommandOnceCmd =
      XPLMFindCommand(page3_button12_command_once.c_str());
  Page3_Button12CommandContinueCmd =
      XPLMFindCommand(page3_button12_command_continue.c_str());

  //  **************************  page four   **********************************

  page4_button_label = getOptionToString("page4_button_label");

  page4_button1_label = getOptionToString("page4_button1_label");
  page4_button1_command_once = getOptionToString("page4_button1_command_once");
  page4_button1_command_continue =
      getOptionToString("page4_button1_command_continue");
  Page4_Button1LabelCmd = XPLMFindCommand(page4_button1_label.c_str());
  Page4_Button1CommandOnceCmd =
      XPLMFindCommand(page4_button1_command_once.c_str());
  Page4_Button1CommandContinueCmd =
      XPLMFindCommand(page4_button1_command_continue.c_str());

  page4_button2_label = getOptionToString("page4_button2_label");
  page4_button2_command_once = getOptionToString("page4_button2_command_once");
  page4_button2_command_continue =
      getOptionToString("page4_button2_command_continue");
  Page4_Button2LabelCmd = XPLMFindCommand(page4_button2_label.c_str());
  Page4_Button2CommandOnceCmd =
      XPLMFindCommand(page4_button2_command_once.c_str());
  Page4_Button2CommandContinueCmd =
      XPLMFindCommand(page4_button2_command_continue.c_str());

  page4_button3_label = getOptionToString("page4_button3_label");
  page4_button3_command_once = getOptionToString("page4_button3_command_once");
  page4_button3_command_continue =
      getOptionToString("page4_button3_command_continue");
  Page4_Button3LabelCmd = XPLMFindCommand(page4_button3_label.c_str());
  Page4_Button3CommandOnceCmd =
      XPLMFindCommand(page4_button3_command_once.c_str());
  Page4_Button3CommandContinueCmd =
      XPLMFindCommand(page4_button3_command_continue.c_str());

  page4_button4_label = getOptionToString("page4_button4_label");
  page4_button4_command_once = getOptionToString("page4_button4_command_once");
  page4_button4_command_continue =
      getOptionToString("page4_button4_command_continue");
  Page4_Button4LabelCmd = XPLMFindCommand(page4_button4_label.c_str());
  Page4_Button4CommandOnceCmd =
      XPLMFindCommand(page4_button4_command_once.c_str());
  Page4_Button4CommandContinueCmd =
      XPLMFindCommand(page4_button4_command_continue.c_str());

  page4_button5_label = getOptionToString("page4_button5_label");
  page4_button5_command_once = getOptionToString("page4_button5_command_once");
  page4_button5_command_continue =
      getOptionToString("page4_button5_command_continue");
  Page4_Button5LabelCmd = XPLMFindCommand(page4_button5_label.c_str());
  Page4_Button5CommandOnceCmd =
      XPLMFindCommand(page4_button5_command_once.c_str());
  Page4_Button5CommandContinueCmd =
      XPLMFindCommand(page4_button5_command_continue.c_str());

  page4_button6_label = getOptionToString("page4_button6_label");
  page4_button6_command_once = getOptionToString("page4_button6_command_once");
  page4_button6_command_continue =
      getOptionToString("page4_button6_command_continue");
  Page4_Button6LabelCmd = XPLMFindCommand(page4_button6_label.c_str());
  Page4_Button6CommandOnceCmd =
      XPLMFindCommand(page4_button6_command_once.c_str());
  Page4_Button6CommandContinueCmd =
      XPLMFindCommand(page4_button6_command_continue.c_str());

  page4_button7_label = getOptionToString("page4_button7_label");
  page4_button7_command_once = getOptionToString("page4_button7_command_once");
  page4_button7_command_continue =
      getOptionToString("page4_button7_command_continue");
  Page4_Button7LabelCmd = XPLMFindCommand(page4_button7_label.c_str());
  Page4_Button7CommandOnceCmd =
      XPLMFindCommand(page4_button7_command_once.c_str());
  Page4_Button7CommandContinueCmd =
      XPLMFindCommand(page4_button7_command_continue.c_str());

  page4_button8_label = getOptionToString("page4_button8_label");
  page4_button8_command_once = getOptionToString("page4_button8_command_once");
  page4_button8_command_continue =
      getOptionToString("page4_button8_command_continue");
  Page4_Button8LabelCmd = XPLMFindCommand(page4_button8_label.c_str());
  Page4_Button8CommandOnceCmd =
      XPLMFindCommand(page4_button8_command_once.c_str());
  Page4_Button8CommandContinueCmd =
      XPLMFindCommand(page4_button8_command_continue.c_str());

  page4_button9_label = getOptionToString("page4_button9_label");
  page4_button9_command_once = getOptionToString("page4_button9_command_once");
  page4_button9_command_continue =
      getOptionToString("page4_button9_command_continue");
  Page4_Button9LabelCmd = XPLMFindCommand(page4_button9_label.c_str());
  Page4_Button9CommandOnceCmd =
      XPLMFindCommand(page4_button9_command_once.c_str());
  Page4_Button9CommandContinueCmd =
      XPLMFindCommand(page4_button9_command_continue.c_str());

  page4_button10_label = getOptionToString("page4_button10_label");
  page4_button10_command_once =
      getOptionToString("page4_button10_command_once");
  page4_button10_command_continue =
      getOptionToString("page4_button10_command_continue");
  Page4_Button10LabelCmd = XPLMFindCommand(page4_button10_label.c_str());
  Page4_Button10CommandOnceCmd =
      XPLMFindCommand(page4_button10_command_once.c_str());
  Page4_Button10CommandContinueCmd =
      XPLMFindCommand(page4_button10_command_continue.c_str());

  page4_button11_label = getOptionToString("page4_button11_label");
  page4_button11_command_once =
      getOptionToString("page4_button11_command_once");
  page4_button11_command_continue =
      getOptionToString("page4_button11_command_continue");
  Page4_Button11LabelCmd = XPLMFindCommand(page4_button11_label.c_str());
  Page4_Button11CommandOnceCmd =
      XPLMFindCommand(page4_button11_command_once.c_str());
  Page4_Button11CommandContinueCmd =
      XPLMFindCommand(page4_button11_command_continue.c_str());

  page4_button12_label = getOptionToString("page4_button12_label");
  page4_button12_command_once =
      getOptionToString("page4_button12_command_once");
  page4_button12_command_continue =
      getOptionToString("page4_button12_command_continue");
  Page4_Button12LabelCmd = XPLMFindCommand(page4_button12_label.c_str());
  Page4_Button12CommandOnceCmd =
      XPLMFindCommand(page4_button12_command_once.c_str());
  Page4_Button12CommandContinueCmd =
      XPLMFindCommand(page4_button12_command_continue.c_str());

  // ****************** page five   ***************************

  page5_button_label = getOptionToString("page5_button_label");

  page5_button1_label = getOptionToString("page5_button1_label");
  page5_button1_command_once = getOptionToString("page5_button1_command_once");
  page5_button1_command_continue =
      getOptionToString("page5_button1_command_continue");
  Page5_Button1LabelCmd = XPLMFindCommand(page5_button1_label.c_str());
  Page5_Button1CommandOnceCmd =
      XPLMFindCommand(page5_button1_command_once.c_str());
  Page5_Button1CommandContinueCmd =
      XPLMFindCommand(page5_button1_command_continue.c_str());

  page5_button2_label = getOptionToString("page5_button2_label");
  page5_button2_command_once = getOptionToString("page5_button2_command_once");
  page5_button2_command_continue =
      getOptionToString("page5_button2_command_continue");
  Page5_Button2LabelCmd = XPLMFindCommand(page5_button2_label.c_str());
  Page5_Button2CommandOnceCmd =
      XPLMFindCommand(page5_button2_command_once.c_str());
  Page5_Button2CommandContinueCmd =
      XPLMFindCommand(page5_button2_command_continue.c_str());

  page5_button3_label = getOptionToString("page5_button3_label");
  page5_button3_command_once = getOptionToString("page5_button3_command_once");
  page5_button3_command_continue =
      getOptionToString("page5_button3_command_continue");
  Page5_Button3LabelCmd = XPLMFindCommand(page5_button3_label.c_str());
  Page5_Button3CommandOnceCmd =
      XPLMFindCommand(page5_button3_command_once.c_str());
  Page5_Button3CommandContinueCmd =
      XPLMFindCommand(page5_button3_command_continue.c_str());

  page5_button4_label = getOptionToString("page5_button4_label");
  page5_button4_command_once = getOptionToString("page5_button4_command_once");
  page5_button4_command_continue =
      getOptionToString("page5_button4_command_continue");
  Page5_Button4LabelCmd = XPLMFindCommand(page5_button4_label.c_str());
  Page5_Button4CommandOnceCmd =
      XPLMFindCommand(page5_button4_command_once.c_str());
  Page5_Button4CommandContinueCmd =
      XPLMFindCommand(page5_button4_command_continue.c_str());

  page5_button5_label = getOptionToString("page5_button5_label");
  page5_button5_command_once = getOptionToString("page5_button5_command_once");
  page5_button5_command_continue =
      getOptionToString("page5_button5_command_continue");
  Page5_Button5LabelCmd = XPLMFindCommand(page5_button5_label.c_str());
  Page5_Button5CommandOnceCmd =
      XPLMFindCommand(page5_button5_command_once.c_str());
  Page5_Button5CommandContinueCmd =
      XPLMFindCommand(page5_button5_command_continue.c_str());

  page5_button6_label = getOptionToString("page5_button6_label");
  page5_button6_command_once = getOptionToString("page5_button6_command_once");
  page5_button6_command_continue =
      getOptionToString("page5_button6_command_continue");
  Page5_Button6LabelCmd = XPLMFindCommand(page5_button6_label.c_str());
  Page5_Button6CommandOnceCmd =
      XPLMFindCommand(page5_button6_command_once.c_str());
  Page5_Button6CommandContinueCmd =
      XPLMFindCommand(page5_button6_command_continue.c_str());

  page5_button7_label = getOptionToString("page5_button7_label");
  page5_button7_command_once = getOptionToString("page5_button7_command_once");
  page5_button7_command_continue =
      getOptionToString("page5_button7_command_continue");
  Page5_Button7LabelCmd = XPLMFindCommand(page5_button7_label.c_str());
  Page5_Button7CommandOnceCmd =
      XPLMFindCommand(page5_button7_command_once.c_str());
  Page5_Button7CommandContinueCmd =
      XPLMFindCommand(page5_button7_command_continue.c_str());

  page5_button8_label = getOptionToString("page5_button8_label");
  page5_button8_command_once = getOptionToString("page5_button8_command_once");
  page5_button8_command_continue =
      getOptionToString("page5_button8_command_continue");
  Page5_Button8LabelCmd = XPLMFindCommand(page5_button8_label.c_str());
  Page5_Button8CommandOnceCmd =
      XPLMFindCommand(page5_button8_command_once.c_str());
  Page5_Button8CommandContinueCmd =
      XPLMFindCommand(page5_button8_command_continue.c_str());

  page5_button9_label = getOptionToString("page5_button9_label");
  page5_button9_command_once = getOptionToString("page5_button9_command_once");
  page5_button9_command_continue =
      getOptionToString("page5_button9_command_continue");
  Page5_Button9LabelCmd = XPLMFindCommand(page5_button9_label.c_str());
  Page5_Button9CommandOnceCmd =
      XPLMFindCommand(page5_button9_command_once.c_str());
  Page5_Button9CommandContinueCmd =
      XPLMFindCommand(page5_button9_command_continue.c_str());

  page5_button10_label = getOptionToString("page5_button10_label");
  page5_button10_command_once =
      getOptionToString("page5_button10_command_once");
  page5_button10_command_continue =
      getOptionToString("page5_button10_command_continue");
  Page5_Button10LabelCmd = XPLMFindCommand(page5_button10_label.c_str());
  Page5_Button10CommandOnceCmd =
      XPLMFindCommand(page5_button10_command_once.c_str());
  Page5_Button10CommandContinueCmd =
      XPLMFindCommand(page5_button10_command_continue.c_str());

  page5_button11_label = getOptionToString("page5_button11_label");
  page5_button11_command_once =
      getOptionToString("page5_button11_command_once");
  page5_button11_command_continue =
      getOptionToString("page5_button11_command_continue");
  Page5_Button11LabelCmd = XPLMFindCommand(page5_button11_label.c_str());
  Page5_Button11CommandOnceCmd =
      XPLMFindCommand(page5_button11_command_once.c_str());
  Page5_Button11CommandContinueCmd =
      XPLMFindCommand(page5_button11_command_continue.c_str());

  page5_button12_label = getOptionToString("page5_button12_label");
  page5_button12_command_once =
      getOptionToString("page5_button12_command_once");
  page5_button12_command_continue =
      getOptionToString("page5_button12_command_continue");
  Page5_Button12LabelCmd = XPLMFindCommand(page5_button12_label.c_str());
  Page5_Button12CommandOnceCmd =
      XPLMFindCommand(page5_button12_command_once.c_str());
  Page5_Button12CommandContinueCmd =
      XPLMFindCommand(page5_button12_command_continue.c_str());

  //  ************************   page six   ********************

  page6_button_label = getOptionToString("page6_button_label");

  page6_button1_label = getOptionToString("page6_button1_label");
  page6_button1_command_once = getOptionToString("page6_button1_command_once");
  page6_button1_command_continue =
      getOptionToString("page6_button1_command_continue");
  Page6_Button1LabelCmd = XPLMFindCommand(page6_button1_label.c_str());
  Page6_Button1CommandOnceCmd =
      XPLMFindCommand(page6_button1_command_once.c_str());
  Page6_Button1CommandContinueCmd =
      XPLMFindCommand(page6_button1_command_continue.c_str());

  page6_button2_label = getOptionToString("page6_button2_label");
  page6_button2_command_once = getOptionToString("page6_button2_command_once");
  page6_button2_command_continue =
      getOptionToString("page6_button2_command_continue");
  Page6_Button2LabelCmd = XPLMFindCommand(page2_button6_label.c_str());
  Page6_Button2CommandOnceCmd =
      XPLMFindCommand(page6_button2_command_once.c_str());
  Page6_Button2CommandContinueCmd =
      XPLMFindCommand(page6_button2_command_continue.c_str());

  page6_button3_label = getOptionToString("page6_button3_label");
  page6_button3_command_once = getOptionToString("page6_button3_command_once");
  page6_button3_command_continue =
      getOptionToString("page6_button3_command_continue");
  Page6_Button3LabelCmd = XPLMFindCommand(page6_button3_label.c_str());
  Page6_Button3CommandOnceCmd =
      XPLMFindCommand(page6_button3_command_once.c_str());
  Page6_Button3CommandContinueCmd =
      XPLMFindCommand(page6_button3_command_continue.c_str());

  page6_button4_label = getOptionToString("page6_button4_label");
  page6_button4_command_once = getOptionToString("page6_button4_command_once");
  page6_button4_command_continue =
      getOptionToString("page6_button4_command_continue");
  Page6_Button4LabelCmd = XPLMFindCommand(page6_button4_label.c_str());
  Page6_Button4CommandOnceCmd =
      XPLMFindCommand(page6_button4_command_once.c_str());
  Page6_Button4CommandContinueCmd =
      XPLMFindCommand(page6_button4_command_continue.c_str());

  page6_button5_label = getOptionToString("page6_button5_label");
  page6_button5_command_once = getOptionToString("page6_button5_command_once");
  page6_button5_command_continue =
      getOptionToString("page6_button5_command_continue");
  Page6_Button5LabelCmd = XPLMFindCommand(page6_button5_label.c_str());
  Page6_Button5CommandOnceCmd =
      XPLMFindCommand(page6_button5_command_once.c_str());
  Page6_Button5CommandContinueCmd =
      XPLMFindCommand(page6_button5_command_continue.c_str());

  page6_button6_label = getOptionToString("page6_button6_label");
  page6_button6_command_once = getOptionToString("page6_button6_command_once");
  page6_button6_command_continue =
      getOptionToString("page6_button6_command_continue");
  Page6_Button6LabelCmd = XPLMFindCommand(page6_button6_label.c_str());
  Page6_Button6CommandOnceCmd =
      XPLMFindCommand(page6_button6_command_once.c_str());
  Page6_Button6CommandContinueCmd =
      XPLMFindCommand(page6_button6_command_continue.c_str());

  page6_button7_label = getOptionToString("page6_button7_label");
  page6_button7_command_once = getOptionToString("page6_button7_command_once");
  page6_button7_command_continue =
      getOptionToString("page6_button7_command_continue");
  Page6_Button7LabelCmd = XPLMFindCommand(page6_button7_label.c_str());
  Page6_Button7CommandOnceCmd =
      XPLMFindCommand(page6_button7_command_once.c_str());
  Page6_Button7CommandContinueCmd =
      XPLMFindCommand(page6_button7_command_continue.c_str());

  page6_button8_label = getOptionToString("page6_button8_label");
  page6_button8_command_once = getOptionToString("page6_button8_command_once");
  page6_button8_command_continue =
      getOptionToString("page6_button8_command_continue");
  Page6_Button8LabelCmd = XPLMFindCommand(page6_button8_label.c_str());
  Page6_Button8CommandOnceCmd =
      XPLMFindCommand(page6_button8_command_once.c_str());
  Page6_Button8CommandContinueCmd =
      XPLMFindCommand(page6_button8_command_continue.c_str());

  page6_button9_label = getOptionToString("page6_button9_label");
  page6_button9_command_once = getOptionToString("page6_button9_command_once");
  page6_button9_command_continue =
      getOptionToString("page6_button9_command_continue");
  Page6_Button9LabelCmd = XPLMFindCommand(page6_button9_label.c_str());
  Page6_Button9CommandOnceCmd =
      XPLMFindCommand(page6_button9_command_once.c_str());
  Page6_Button9CommandContinueCmd =
      XPLMFindCommand(page6_button9_command_continue.c_str());

  page6_button10_label = getOptionToString("page6_button10_label");
  page6_button10_command_once =
      getOptionToString("page6_button10_command_once");
  page6_button10_command_continue =
      getOptionToString("page6_button10_command_continue");
  Page6_Button10LabelCmd = XPLMFindCommand(page6_button10_label.c_str());
  Page6_Button10CommandOnceCmd =
      XPLMFindCommand(page6_button10_command_once.c_str());
  Page6_Button10CommandContinueCmd =
      XPLMFindCommand(page6_button10_command_continue.c_str());

  page6_button11_label = getOptionToString("page6_button11_label");
  page6_button11_command_once =
      getOptionToString("page6_button11_command_once");
  page6_button11_command_continue =
      getOptionToString("page6_button11_command_continue");
  Page6_Button11LabelCmd = XPLMFindCommand(page6_button11_label.c_str());
  Page6_Button11CommandOnceCmd =
      XPLMFindCommand(page6_button11_command_once.c_str());
  Page6_Button11CommandContinueCmd =
      XPLMFindCommand(page6_button11_command_continue.c_str());

  page6_button12_label = getOptionToString("page6_button12_label");
  page6_button12_command_once =
      getOptionToString("page6_button12_command_once");
  page6_button12_command_continue =
      getOptionToString("page6_button12_command_continue");
  Page6_Button12LabelCmd = XPLMFindCommand(page6_button12_label.c_str());
  Page6_Button12CommandOnceCmd =
      XPLMFindCommand(page6_button12_command_once.c_str());
  Page6_Button12CommandContinueCmd =
      XPLMFindCommand(page6_button12_command_continue.c_str());

  //  ******************************  page seven
  //  ***********************************

  page7_button_label = getOptionToString("page7_button_label");

  page7_button1_label = getOptionToString("page7_button1_label");
  page7_button1_command_once = getOptionToString("page7_button1_command_once");
  page7_button1_command_continue =
      getOptionToString("page7_button1_command_continue");
  Page7_Button1LabelCmd = XPLMFindCommand(page7_button1_label.c_str());
  Page7_Button1CommandOnceCmd =
      XPLMFindCommand(page7_button1_command_once.c_str());
  Page7_Button1CommandContinueCmd =
      XPLMFindCommand(page7_button1_command_continue.c_str());

  page7_button2_label = getOptionToString("page7_button2_label");
  page7_button2_command_once = getOptionToString("page7_button2_command_once");
  page7_button2_command_continue =
      getOptionToString("page7_button2_command_continue");
  Page7_Button2LabelCmd = XPLMFindCommand(page7_button2_label.c_str());
  Page7_Button2CommandOnceCmd =
      XPLMFindCommand(page7_button2_command_once.c_str());
  Page7_Button2CommandContinueCmd =
      XPLMFindCommand(page7_button2_command_continue.c_str());

  page7_button3_label = getOptionToString("page7_button3_label");
  page7_button3_command_once = getOptionToString("page7_button3_command_once");
  page7_button3_command_continue =
      getOptionToString("page7_button3_command_continue");
  Page7_Button3LabelCmd = XPLMFindCommand(page7_button3_label.c_str());
  Page7_Button3CommandOnceCmd =
      XPLMFindCommand(page7_button3_command_once.c_str());
  Page7_Button3CommandContinueCmd =
      XPLMFindCommand(page7_button3_command_continue.c_str());

  page7_button4_label = getOptionToString("page7_button4_label");
  page7_button4_command_once = getOptionToString("page7_button4_command_once");
  page7_button4_command_continue =
      getOptionToString("page7_button4_command_continue");
  Page7_Button4LabelCmd = XPLMFindCommand(page7_button4_label.c_str());
  Page7_Button4CommandOnceCmd =
      XPLMFindCommand(page7_button4_command_once.c_str());
  Page7_Button4CommandContinueCmd =
      XPLMFindCommand(page7_button4_command_continue.c_str());

  page7_button5_label = getOptionToString("page7_button5_label");
  page7_button5_command_once = getOptionToString("page7_button5_command_once");
  page7_button5_command_continue =
      getOptionToString("page7_button5_command_continue");
  Page7_Button5LabelCmd = XPLMFindCommand(page7_button5_label.c_str());
  Page7_Button5CommandOnceCmd =
      XPLMFindCommand(page7_button5_command_once.c_str());
  Page7_Button5CommandContinueCmd =
      XPLMFindCommand(page7_button5_command_continue.c_str());

  page7_button6_label = getOptionToString("page7_button6_label");
  page7_button6_command_once = getOptionToString("page7_button6_command_once");
  page7_button6_command_continue =
      getOptionToString("page7_button6_command_continue");
  Page7_Button6LabelCmd = XPLMFindCommand(page7_button6_label.c_str());
  Page7_Button6CommandOnceCmd =
      XPLMFindCommand(page7_button6_command_once.c_str());
  Page7_Button6CommandContinueCmd =
      XPLMFindCommand(page7_button6_command_continue.c_str());

  page7_button7_label = getOptionToString("page7_button7_label");
  page7_button7_command_once = getOptionToString("page7_button7_command_once");
  page7_button7_command_continue =
      getOptionToString("page7_button7_command_continue");
  Page7_Button7LabelCmd = XPLMFindCommand(page7_button7_label.c_str());
  Page7_Button7CommandOnceCmd =
      XPLMFindCommand(page7_button7_command_once.c_str());
  Page7_Button7CommandContinueCmd =
      XPLMFindCommand(page7_button7_command_continue.c_str());

  page7_button8_label = getOptionToString("page7_button8_label");
  page7_button8_command_once = getOptionToString("page7_button8_command_once");
  page7_button8_command_continue =
      getOptionToString("page7_button8_command_continue");
  Page7_Button8LabelCmd = XPLMFindCommand(page7_button8_label.c_str());
  Page7_Button8CommandOnceCmd =
      XPLMFindCommand(page7_button8_command_once.c_str());
  Page7_Button8CommandContinueCmd =
      XPLMFindCommand(page7_button8_command_continue.c_str());

  page7_button9_label = getOptionToString("page7_button9_label");
  page7_button9_command_once = getOptionToString("page7_button9_command_once");
  page7_button9_command_continue =
      getOptionToString("page7_button9_command_continue");
  Page7_Button9LabelCmd = XPLMFindCommand(page7_button9_label.c_str());
  Page7_Button9CommandOnceCmd =
      XPLMFindCommand(page7_button9_command_once.c_str());
  Page7_Button9CommandContinueCmd =
      XPLMFindCommand(page7_button9_command_continue.c_str());

  page7_button10_label = getOptionToString("page7_button10_label");
  page7_button10_command_once =
      getOptionToString("page7_button10_command_once");
  page7_button10_command_continue =
      getOptionToString("page7_button10_command_continue");
  Page7_Button10LabelCmd = XPLMFindCommand(page7_button10_label.c_str());
  Page7_Button10CommandOnceCmd =
      XPLMFindCommand(page7_button10_command_once.c_str());
  Page7_Button10CommandContinueCmd =
      XPLMFindCommand(page7_button10_command_continue.c_str());

  page7_button11_label = getOptionToString("page7_button11_label");
  page7_button11_command_once =
      getOptionToString("page7_button11_command_once");
  page7_button11_command_continue =
      getOptionToString("page7_button11_command_continue");
  Page7_Button11LabelCmd = XPLMFindCommand(page7_button11_label.c_str());
  Page7_Button11CommandOnceCmd =
      XPLMFindCommand(page7_button11_command_once.c_str());
  Page7_Button11CommandContinueCmd =
      XPLMFindCommand(page7_button11_command_continue.c_str());

  page7_button12_label = getOptionToString("page7_button12_label");
  page7_button12_command_once =
      getOptionToString("page7_button12_command_once");
  page7_button12_command_continue =
      getOptionToString("page7_button12_command_continue");
  Page7_Button12LabelCmd = XPLMFindCommand(page7_button12_label.c_str());
  Page7_Button12CommandOnceCmd =
      XPLMFindCommand(page7_button12_command_once.c_str());
  Page7_Button12CommandContinueCmd =
      XPLMFindCommand(page7_button12_command_continue.c_str());

  //  **************************  page eight **********************************

  page8_button_label = getOptionToString("page8_button_label");

  page8_button1_label = getOptionToString("page8_button1_label");
  page8_button1_command_once = getOptionToString("page8_button1_command_once");
  page8_button1_command_continue =
      getOptionToString("page8_button1_command_continue");
  Page8_Button1LabelCmd = XPLMFindCommand(page8_button1_label.c_str());
  Page8_Button1CommandOnceCmd =
      XPLMFindCommand(page8_button1_command_once.c_str());
  Page8_Button1CommandContinueCmd =
      XPLMFindCommand(page8_button1_command_continue.c_str());

  page8_button2_label = getOptionToString("page8_button2_label");
  page8_button2_command_once = getOptionToString("page8_button2_command_once");
  page8_button2_command_continue =
      getOptionToString("page8_button2_command_continue");
  Page8_Button2LabelCmd = XPLMFindCommand(page8_button2_label.c_str());
  Page8_Button2CommandOnceCmd =
      XPLMFindCommand(page8_button2_command_once.c_str());
  Page8_Button2CommandContinueCmd =
      XPLMFindCommand(page8_button2_command_continue.c_str());

  page8_button3_label = getOptionToString("page8_button3_label");
  page8_button3_command_once = getOptionToString("page8_button3_command_once");
  page8_button3_command_continue =
      getOptionToString("page8_button3_command_continue");
  Page8_Button3LabelCmd = XPLMFindCommand(page8_button3_label.c_str());
  Page8_Button3CommandOnceCmd =
      XPLMFindCommand(page8_button3_command_once.c_str());
  Page8_Button3CommandContinueCmd =
      XPLMFindCommand(page8_button3_command_continue.c_str());

  page8_button4_label = getOptionToString("page8_button4_label");
  page8_button4_command_once = getOptionToString("page8_button4_command_once");
  page8_button4_command_continue =
      getOptionToString("page8_button4_command_continue");
  Page8_Button4LabelCmd = XPLMFindCommand(page8_button4_label.c_str());
  Page8_Button4CommandOnceCmd =
      XPLMFindCommand(page8_button4_command_once.c_str());
  Page8_Button4CommandContinueCmd =
      XPLMFindCommand(page8_button4_command_continue.c_str());

  page8_button5_label = getOptionToString("page8_button5_label");
  page8_button5_command_once = getOptionToString("page8_button5_command_once");
  page8_button5_command_continue =
      getOptionToString("page8_button5_command_continue");
  Page8_Button5LabelCmd = XPLMFindCommand(page8_button5_label.c_str());
  Page8_Button5CommandOnceCmd =
      XPLMFindCommand(page8_button5_command_once.c_str());
  Page8_Button5CommandContinueCmd =
      XPLMFindCommand(page8_button5_command_continue.c_str());

  page8_button6_label = getOptionToString("page8_button6_label");
  page8_button6_command_once = getOptionToString("page8_button6_command_once");
  page8_button6_command_continue =
      getOptionToString("page8_button6_command_continue");
  Page8_Button6LabelCmd = XPLMFindCommand(page8_button6_label.c_str());
  Page8_Button6CommandOnceCmd =
      XPLMFindCommand(page8_button6_command_once.c_str());
  Page8_Button6CommandContinueCmd =
      XPLMFindCommand(page8_button6_command_continue.c_str());

  page8_button7_label = getOptionToString("page8_button7_label");
  page8_button7_command_once = getOptionToString("page8_button7_command_once");
  page8_button7_command_continue =
      getOptionToString("page8_button7_command_continue");
  Page8_Button7LabelCmd = XPLMFindCommand(page8_button7_label.c_str());
  Page8_Button7CommandOnceCmd =
      XPLMFindCommand(page8_button7_command_once.c_str());
  Page8_Button7CommandContinueCmd =
      XPLMFindCommand(page8_button7_command_continue.c_str());

  page8_button8_label = getOptionToString("page8_button8_label");
  page8_button8_command_once = getOptionToString("page8_button8_command_once");
  page8_button8_command_continue =
      getOptionToString("page8_button8_command_continue");
  Page8_Button8LabelCmd = XPLMFindCommand(page8_button8_label.c_str());
  Page8_Button8CommandOnceCmd =
      XPLMFindCommand(page8_button8_command_once.c_str());
  Page8_Button8CommandContinueCmd =
      XPLMFindCommand(page8_button8_command_continue.c_str());

  page8_button9_label = getOptionToString("page8_button9_label");
  page8_button9_command_once = getOptionToString("page8_button9_command_once");
  page8_button9_command_continue =
      getOptionToString("page8_button9_command_continue");
  Page8_Button9LabelCmd = XPLMFindCommand(page8_button9_label.c_str());
  Page8_Button9CommandOnceCmd =
      XPLMFindCommand(page8_button9_command_once.c_str());
  Page8_Button9CommandContinueCmd =
      XPLMFindCommand(page8_button9_command_continue.c_str());

  page8_button10_label = getOptionToString("page8_button10_label");
  page8_button10_command_once =
      getOptionToString("page8_button10_command_once");
  page8_button10_command_continue =
      getOptionToString("page8_button10_command_continue");
  Page8_Button10LabelCmd = XPLMFindCommand(page8_button10_label.c_str());
  Page8_Button10CommandOnceCmd =
      XPLMFindCommand(page8_button10_command_once.c_str());
  Page8_Button10CommandContinueCmd =
      XPLMFindCommand(page8_button10_command_continue.c_str());

  page8_button11_label = getOptionToString("page8_button11_label");
  page8_button11_command_once =
      getOptionToString("page8_button11_command_once");
  page8_button11_command_continue =
      getOptionToString("page8_button11_command_continue");
  Page8_Button11LabelCmd = XPLMFindCommand(page8_button11_label.c_str());
  Page8_Button11CommandOnceCmd =
      XPLMFindCommand(page8_button11_command_once.c_str());
  Page8_Button11CommandContinueCmd =
      XPLMFindCommand(page8_button11_command_continue.c_str());

  page8_button12_label = getOptionToString("page8_button12_label");
  page8_button12_command_once =
      getOptionToString("page8_button12_command_once");
  page8_button12_command_continue =
      getOptionToString("page8_button12_command_continue");
  Page8_Button12LabelCmd = XPLMFindCommand(page8_button12_label.c_str());
  Page8_Button12CommandOnceCmd =
      XPLMFindCommand(page8_button12_command_once.c_str());
  Page8_Button12CommandContinueCmd =
      XPLMFindCommand(page8_button12_command_continue.c_str());


  //  **************************  page nine **********************************

  page9_button_label = getOptionToString("page9_button_label");

  page9_button1_label = getOptionToString("page9_button1_label");
  page9_button1_command_once = getOptionToString("page9_button1_command_once");
  page9_button1_command_continue =
      getOptionToString("page9_button1_command_continue");
  Page9_Button1LabelCmd = XPLMFindCommand(page9_button1_label.c_str());
  Page9_Button1CommandOnceCmd =
      XPLMFindCommand(page9_button1_command_once.c_str());
  Page9_Button1CommandContinueCmd =
      XPLMFindCommand(page9_button1_command_continue.c_str());

  page9_button2_label = getOptionToString("page9_button2_label");
  page9_button2_command_once = getOptionToString("page9_button2_command_once");
  page9_button2_command_continue =
      getOptionToString("page9_button2_command_continue");
  Page9_Button2LabelCmd = XPLMFindCommand(page9_button2_label.c_str());
  Page9_Button2CommandOnceCmd =
      XPLMFindCommand(page9_button2_command_once.c_str());
  Page9_Button2CommandContinueCmd =
      XPLMFindCommand(page9_button2_command_continue.c_str());

  page9_button3_label = getOptionToString("page9_button3_label");
  page9_button3_command_once = getOptionToString("page9_button3_command_once");
  page9_button3_command_continue =
      getOptionToString("page9_button3_command_continue");
  Page9_Button3LabelCmd = XPLMFindCommand(page9_button3_label.c_str());
  Page9_Button3CommandOnceCmd =
      XPLMFindCommand(page9_button3_command_once.c_str());
  Page9_Button3CommandContinueCmd =
      XPLMFindCommand(page9_button3_command_continue.c_str());

  page9_button4_label = getOptionToString("page9_button4_label");
  page9_button4_command_once = getOptionToString("page9_button4_command_once");
  page9_button4_command_continue =
      getOptionToString("page9_button4_command_continue");
  Page9_Button4LabelCmd = XPLMFindCommand(page9_button4_label.c_str());
  Page9_Button4CommandOnceCmd =
      XPLMFindCommand(page9_button4_command_once.c_str());
  Page9_Button4CommandContinueCmd =
      XPLMFindCommand(page9_button4_command_continue.c_str());

  page9_button5_label = getOptionToString("page9_button5_label");
  page9_button5_command_once = getOptionToString("page9_button5_command_once");
  page9_button5_command_continue =
      getOptionToString("page9_button5_command_continue");
  Page9_Button5LabelCmd = XPLMFindCommand(page9_button5_label.c_str());
  Page9_Button5CommandOnceCmd =
      XPLMFindCommand(page9_button5_command_once.c_str());
  Page9_Button5CommandContinueCmd =
      XPLMFindCommand(page9_button5_command_continue.c_str());

  page9_button6_label = getOptionToString("page9_button6_label");
  page9_button6_command_once = getOptionToString("page9_button6_command_once");
  page9_button6_command_continue =
      getOptionToString("page9_button6_command_continue");
  Page9_Button6LabelCmd = XPLMFindCommand(page9_button6_label.c_str());
  Page9_Button6CommandOnceCmd =
      XPLMFindCommand(page9_button6_command_once.c_str());
  Page9_Button6CommandContinueCmd =
      XPLMFindCommand(page9_button6_command_continue.c_str());

  page9_button7_label = getOptionToString("page9_button7_label");
  page9_button7_command_once = getOptionToString("page9_button7_command_once");
  page9_button7_command_continue =
      getOptionToString("page9_button7_command_continue");
  Page9_Button7LabelCmd = XPLMFindCommand(page9_button7_label.c_str());
  Page9_Button7CommandOnceCmd =
      XPLMFindCommand(page9_button7_command_once.c_str());
  Page9_Button7CommandContinueCmd =
      XPLMFindCommand(page9_button7_command_continue.c_str());

  page9_button8_label = getOptionToString("page9_button8_label");
  page9_button8_command_once = getOptionToString("page9_button8_command_once");
  page9_button8_command_continue =
      getOptionToString("page9_button8_command_continue");
  Page9_Button8LabelCmd = XPLMFindCommand(page9_button8_label.c_str());
  Page9_Button8CommandOnceCmd =
      XPLMFindCommand(page9_button8_command_once.c_str());
  Page9_Button8CommandContinueCmd =
      XPLMFindCommand(page9_button8_command_continue.c_str());

  page9_button9_label = getOptionToString("page9_button9_label");
  page9_button9_command_once = getOptionToString("page9_button9_command_once");
  page9_button9_command_continue =
      getOptionToString("page9_button9_command_continue");
  Page9_Button9LabelCmd = XPLMFindCommand(page9_button9_label.c_str());
  Page9_Button9CommandOnceCmd =
      XPLMFindCommand(page9_button9_command_once.c_str());
  Page9_Button9CommandContinueCmd =
      XPLMFindCommand(page9_button9_command_continue.c_str());

  page9_button10_label = getOptionToString("page9_button10_label");
  page9_button10_command_once =
      getOptionToString("page9_button10_command_once");
  page9_button10_command_continue =
      getOptionToString("page9_button10_command_continue");
  Page9_Button10LabelCmd = XPLMFindCommand(page9_button10_label.c_str());
  Page9_Button10CommandOnceCmd =
      XPLMFindCommand(page9_button10_command_once.c_str());
  Page9_Button10CommandContinueCmd =
      XPLMFindCommand(page9_button10_command_continue.c_str());

  page9_button11_label = getOptionToString("page9_button11_label");
  page9_button11_command_once =
      getOptionToString("page9_button11_command_once");
  page9_button11_command_continue =
      getOptionToString("page9_button11_command_continue");
  Page9_Button11LabelCmd = XPLMFindCommand(page9_button11_label.c_str());
  Page9_Button11CommandOnceCmd =
      XPLMFindCommand(page9_button11_command_once.c_str());
  Page9_Button11CommandContinueCmd =
      XPLMFindCommand(page9_button11_command_continue.c_str());

  page9_button12_label = getOptionToString("page9_button12_label");
  page9_button12_command_once =
      getOptionToString("page9_button12_command_once");
  page9_button12_command_continue =
      getOptionToString("page9_button12_command_continue");
  Page9_Button12LabelCmd = XPLMFindCommand(page9_button12_label.c_str());
  Page9_Button12CommandOnceCmd =
      XPLMFindCommand(page9_button12_command_once.c_str());
  Page9_Button12CommandContinueCmd =
      XPLMFindCommand(page9_button12_command_continue.c_str());

  page9_button13_label = getOptionToString("page9_button13_label");
  page9_button13_command_once = getOptionToString("page9_button13_command_once");
  page9_button13_command_continue =
      getOptionToString("page9_button13_command_continue");
  Page9_Button13LabelCmd = XPLMFindCommand(page9_button13_label.c_str());
  Page9_Button13CommandOnceCmd =
      XPLMFindCommand(page9_button13_command_once.c_str());
  Page9_Button13CommandContinueCmd =
      XPLMFindCommand(page9_button13_command_continue.c_str());

  page9_button14_label = getOptionToString("page9_button14_label");
  page9_button14_command_once = getOptionToString("page9_button14_command_once");
  page9_button14_command_continue =
      getOptionToString("page9_button14_command_continue");
  Page9_Button14LabelCmd = XPLMFindCommand(page9_button14_label.c_str());
  Page9_Button14CommandOnceCmd =
      XPLMFindCommand(page9_button14_command_once.c_str());
  Page9_Button14CommandContinueCmd =
      XPLMFindCommand(page9_button14_command_continue.c_str());

  page9_button15_label = getOptionToString("page9_button15_label");
  page9_button15_command_once = getOptionToString("page9_button15_command_once");
  page9_button15_command_continue =
      getOptionToString("page9_button15_command_continue");
  Page9_Button15LabelCmd = XPLMFindCommand(page9_button15_label.c_str());
  Page9_Button15CommandOnceCmd =
      XPLMFindCommand(page9_button15_command_once.c_str());
  Page9_Button15CommandContinueCmd =
      XPLMFindCommand(page9_button15_command_continue.c_str());

  page9_button16_label = getOptionToString("page9_button16_label");
  page9_button16_command_once = getOptionToString("page9_button16_command_once");
  page9_button16_command_continue =
      getOptionToString("page9_button16_command_continue");
  Page9_Button16LabelCmd = XPLMFindCommand(page9_button16_label.c_str());
  Page9_Button16CommandOnceCmd =
      XPLMFindCommand(page9_button16_command_once.c_str());
  Page9_Button16CommandContinueCmd =
      XPLMFindCommand(page9_button16_command_continue.c_str());

  page9_button17_label = getOptionToString("page9_button17_label");
  page9_button17_command_once = getOptionToString("page9_button17_command_once");
  page9_button17_command_continue =
      getOptionToString("page9_button17_command_continue");
  Page9_Button17LabelCmd = XPLMFindCommand(page9_button17_label.c_str());
  Page9_Button17CommandOnceCmd =
      XPLMFindCommand(page9_button17_command_once.c_str());
  Page9_Button17CommandContinueCmd =
      XPLMFindCommand(page9_button17_command_continue.c_str());

  page9_button18_label = getOptionToString("page9_button18_label");
  page9_button18_command_once = getOptionToString("page9_button18_command_once");
  page9_button18_command_continue =
      getOptionToString("page9_button18_command_continue");
  Page9_Button18LabelCmd = XPLMFindCommand(page9_button18_label.c_str());
  Page9_Button18CommandOnceCmd =
      XPLMFindCommand(page9_button18_command_once.c_str());
  Page9_Button18CommandContinueCmd =
      XPLMFindCommand(page9_button18_command_continue.c_str());

  page9_button19_label = getOptionToString("page9_button19_label");
  page9_button19_command_once = getOptionToString("page9_button19_command_once");
  page9_button19_command_continue =
      getOptionToString("page9_button19_command_continue");
  Page9_Button19LabelCmd = XPLMFindCommand(page9_button19_label.c_str());
  Page9_Button19CommandOnceCmd =
      XPLMFindCommand(page9_button19_command_once.c_str());
  Page9_Button19CommandContinueCmd =
      XPLMFindCommand(page9_button19_command_continue.c_str());

  page9_button20_label = getOptionToString("page9_button20_label");
  page9_button20_command_once = getOptionToString("page9_button20_command_once");
  page9_button20_command_continue =
      getOptionToString("page9_button20_command_continue");
  Page9_Button20LabelCmd = XPLMFindCommand(page9_button20_label.c_str());
  Page9_Button20CommandOnceCmd =
      XPLMFindCommand(page9_button20_command_once.c_str());
  Page9_Button20CommandContinueCmd =
      XPLMFindCommand(page9_button20_command_continue.c_str());

  page9_button21_label = getOptionToString("page9_button21_label");
  page9_button21_command_once = getOptionToString("page9_button21_command_once");
  page9_button21_command_continue =
      getOptionToString("page9_button21_command_continue");
  Page9_Button21LabelCmd = XPLMFindCommand(page9_button21_label.c_str());
  Page9_Button21CommandOnceCmd =
      XPLMFindCommand(page9_button21_command_once.c_str());
  Page9_Button21CommandContinueCmd =
      XPLMFindCommand(page9_button21_command_continue.c_str());

  page9_button22_label = getOptionToString("page9_button22_label");
  page9_button22_command_once =
      getOptionToString("page9_button22_command_once");
  page9_button22_command_continue =
      getOptionToString("page9_button22_command_continue");
  Page9_Button22LabelCmd = XPLMFindCommand(page9_button22_label.c_str());
  Page9_Button22CommandOnceCmd =
      XPLMFindCommand(page9_button22_command_once.c_str());
  Page9_Button22CommandContinueCmd =
      XPLMFindCommand(page9_button22_command_continue.c_str());

  page9_button23_label = getOptionToString("page9_button23_label");
  page9_button23_command_once =
      getOptionToString("page9_button23_command_once");
  page9_button23_command_continue =
      getOptionToString("page9_button23_command_continue");
  Page9_Button23LabelCmd = XPLMFindCommand(page9_button23_label.c_str());
  Page9_Button23CommandOnceCmd =
      XPLMFindCommand(page9_button23_command_once.c_str());
  Page9_Button23CommandContinueCmd =
      XPLMFindCommand(page9_button23_command_continue.c_str());

  page9_button24_label = getOptionToString("page9_button24_label");
  page9_button24_command_once =
      getOptionToString("page9_button24_command_once");
  page9_button24_command_continue =
      getOptionToString("page9_button24_command_continue");
  Page9_Button24LabelCmd = XPLMFindCommand(page9_button24_label.c_str());
  Page9_Button24CommandOnceCmd =
      XPLMFindCommand(page9_button24_command_once.c_str());
  Page9_Button24CommandContinueCmd =
      XPLMFindCommand(page9_button24_command_continue.c_str());


  //  **************************  page ten **********************************

  page10_button_label = getOptionToString("page10_button_label");

  page10_button1_label = getOptionToString("page10_button1_label");
  page10_button1_command_once = getOptionToString("page10_button1_command_once");
  page10_button1_command_continue =
      getOptionToString("page10_button1_command_continue");
  Page10_Button1LabelCmd = XPLMFindCommand(page10_button1_label.c_str());
  Page10_Button1CommandOnceCmd =
      XPLMFindCommand(page10_button1_command_once.c_str());
  Page10_Button1CommandContinueCmd =
      XPLMFindCommand(page10_button1_command_continue.c_str());

  page10_button2_label = getOptionToString("page10_button2_label");
  page10_button2_command_once = getOptionToString("page10_button2_command_once");
  page10_button2_command_continue =
      getOptionToString("page10_button2_command_continue");
  Page10_Button2LabelCmd = XPLMFindCommand(page10_button2_label.c_str());
  Page10_Button2CommandOnceCmd =
      XPLMFindCommand(page10_button2_command_once.c_str());
  Page10_Button2CommandContinueCmd =
      XPLMFindCommand(page10_button2_command_continue.c_str());

  page10_button3_label = getOptionToString("page10_button3_label");
  page10_button3_command_once = getOptionToString("page10_button3_command_once");
  page10_button3_command_continue =
      getOptionToString("page10_button3_command_continue");
  Page10_Button3LabelCmd = XPLMFindCommand(page10_button3_label.c_str());
  Page10_Button3CommandOnceCmd =
      XPLMFindCommand(page10_button3_command_once.c_str());
  Page10_Button3CommandContinueCmd =
      XPLMFindCommand(page10_button3_command_continue.c_str());

  page10_button4_label = getOptionToString("page10_button4_label");
  page10_button4_command_once = getOptionToString("page10_button4_command_once");
  page10_button4_command_continue =
      getOptionToString("page10_button4_command_continue");
  Page10_Button4LabelCmd = XPLMFindCommand(page10_button4_label.c_str());
  Page10_Button4CommandOnceCmd =
      XPLMFindCommand(page10_button4_command_once.c_str());
  Page10_Button4CommandContinueCmd =
      XPLMFindCommand(page10_button4_command_continue.c_str());

  page10_button5_label = getOptionToString("page10_button5_label");
  page10_button5_command_once = getOptionToString("page10_button5_command_once");
  page10_button5_command_continue =
      getOptionToString("page10_button5_command_continue");
  Page10_Button5LabelCmd = XPLMFindCommand(page10_button5_label.c_str());
  Page10_Button5CommandOnceCmd =
      XPLMFindCommand(page10_button5_command_once.c_str());
  Page10_Button5CommandContinueCmd =
      XPLMFindCommand(page10_button5_command_continue.c_str());

  page10_button6_label = getOptionToString("page10_button6_label");
  page10_button6_command_once = getOptionToString("page10_button6_command_once");
  page10_button6_command_continue =
      getOptionToString("page10_button6_command_continue");
  Page10_Button6LabelCmd = XPLMFindCommand(page10_button6_label.c_str());
  Page10_Button6CommandOnceCmd =
      XPLMFindCommand(page10_button6_command_once.c_str());
  Page10_Button6CommandContinueCmd =
      XPLMFindCommand(page10_button6_command_continue.c_str());

  page10_button7_label = getOptionToString("page10_button7_label");
  page10_button7_command_once = getOptionToString("page10_button7_command_once");
  page10_button7_command_continue =
      getOptionToString("page10_button7_command_continue");
  Page10_Button7LabelCmd = XPLMFindCommand(page10_button7_label.c_str());
  Page10_Button7CommandOnceCmd =
      XPLMFindCommand(page10_button7_command_once.c_str());
  Page10_Button7CommandContinueCmd =
      XPLMFindCommand(page10_button7_command_continue.c_str());

  page10_button8_label = getOptionToString("page10_button8_label");
  page10_button8_command_once = getOptionToString("page10_button8_command_once");
  page10_button8_command_continue =
      getOptionToString("page10_button8_command_continue");
  Page10_Button8LabelCmd = XPLMFindCommand(page10_button8_label.c_str());
  Page10_Button8CommandOnceCmd =
      XPLMFindCommand(page10_button8_command_once.c_str());
  Page10_Button8CommandContinueCmd =
      XPLMFindCommand(page10_button8_command_continue.c_str());

  page10_button9_label = getOptionToString("page10_button9_label");
  page10_button9_command_once = getOptionToString("page10_button9_command_once");
  page10_button9_command_continue =
      getOptionToString("page10_button9_command_continue");
  Page10_Button9LabelCmd = XPLMFindCommand(page10_button9_label.c_str());
  Page10_Button9CommandOnceCmd =
      XPLMFindCommand(page10_button9_command_once.c_str());
  Page10_Button9CommandContinueCmd =
      XPLMFindCommand(page10_button9_command_continue.c_str());

  page10_button10_label = getOptionToString("page10_button10_label");
  page10_button10_command_once =
      getOptionToString("page10_button10_command_once");
  page10_button10_command_continue =
      getOptionToString("page10_button10_command_continue");
  Page10_Button10LabelCmd = XPLMFindCommand(page10_button10_label.c_str());
  Page10_Button10CommandOnceCmd =
      XPLMFindCommand(page10_button10_command_once.c_str());
  Page10_Button10CommandContinueCmd =
      XPLMFindCommand(page10_button10_command_continue.c_str());

  page10_button11_label = getOptionToString("page10_button11_label");
  page10_button11_command_once =
      getOptionToString("page10_button11_command_once");
  page10_button11_command_continue =
      getOptionToString("page10_button11_command_continue");
  Page10_Button11LabelCmd = XPLMFindCommand(page10_button11_label.c_str());
  Page10_Button11CommandOnceCmd =
      XPLMFindCommand(page10_button11_command_once.c_str());
  Page10_Button11CommandContinueCmd =
      XPLMFindCommand(page10_button11_command_continue.c_str());

  page10_button12_label = getOptionToString("page10_button12_label");
  page10_button12_command_once =
      getOptionToString("page10_button12_command_once");
  page10_button12_command_continue =
      getOptionToString("page10_button12_command_continue");
  Page10_Button12LabelCmd = XPLMFindCommand(page10_button12_label.c_str());
  Page10_Button12CommandOnceCmd =
      XPLMFindCommand(page10_button12_command_once.c_str());
  Page10_Button12CommandContinueCmd =
      XPLMFindCommand(page10_button12_command_continue.c_str());

  page10_button13_label = getOptionToString("page10_button13_label");
  page10_button13_command_once = getOptionToString("page10_button13_command_once");
  page10_button13_command_continue =
      getOptionToString("page10_button13_command_continue");
  Page10_Button13LabelCmd = XPLMFindCommand(page10_button13_label.c_str());
  Page10_Button13CommandOnceCmd =
      XPLMFindCommand(page10_button13_command_once.c_str());
  Page10_Button13CommandContinueCmd =
      XPLMFindCommand(page10_button13_command_continue.c_str());

  page10_button14_label = getOptionToString("page10_button14_label");
  page10_button14_command_once = getOptionToString("page10_button14_command_once");
  page10_button14_command_continue =
      getOptionToString("page10_button14_command_continue");
  Page10_Button14LabelCmd = XPLMFindCommand(page10_button14_label.c_str());
  Page10_Button14CommandOnceCmd =
      XPLMFindCommand(page10_button14_command_once.c_str());
  Page10_Button14CommandContinueCmd =
      XPLMFindCommand(page10_button14_command_continue.c_str());

  page10_button15_label = getOptionToString("page10_button15_label");
  page10_button15_command_once = getOptionToString("page10_button15_command_once");
  page10_button15_command_continue =
      getOptionToString("page10_button15_command_continue");
  Page10_Button15LabelCmd = XPLMFindCommand(page10_button15_label.c_str());
  Page10_Button15CommandOnceCmd =
      XPLMFindCommand(page10_button15_command_once.c_str());
  Page10_Button15CommandContinueCmd =
      XPLMFindCommand(page10_button15_command_continue.c_str());

  page10_button16_label = getOptionToString("page10_button16_label");
  page10_button16_command_once = getOptionToString("page10_button16_command_once");
  page10_button16_command_continue =
      getOptionToString("page10_button16_command_continue");
  Page10_Button16LabelCmd = XPLMFindCommand(page10_button16_label.c_str());
  Page10_Button16CommandOnceCmd =
      XPLMFindCommand(page10_button16_command_once.c_str());
  Page10_Button16CommandContinueCmd =
      XPLMFindCommand(page10_button16_command_continue.c_str());

  page10_button17_label = getOptionToString("page10_button17_label");
  page10_button17_command_once = getOptionToString("page10_button17_command_once");
  page10_button17_command_continue =
      getOptionToString("page10_button17_command_continue");
  Page10_Button17LabelCmd = XPLMFindCommand(page10_button17_label.c_str());
  Page10_Button17CommandOnceCmd =
      XPLMFindCommand(page10_button17_command_once.c_str());
  Page10_Button17CommandContinueCmd =
      XPLMFindCommand(page10_button17_command_continue.c_str());

  page10_button18_label = getOptionToString("page10_button18_label");
  page10_button18_command_once = getOptionToString("page10_button18_command_once");
  page10_button18_command_continue =
      getOptionToString("page10_button18_command_continue");
  Page10_Button18LabelCmd = XPLMFindCommand(page10_button18_label.c_str());
  Page10_Button18CommandOnceCmd =
      XPLMFindCommand(page10_button18_command_once.c_str());
  Page10_Button18CommandContinueCmd =
      XPLMFindCommand(page10_button18_command_continue.c_str());

  page10_button19_label = getOptionToString("page10_button19_label");
  page10_button19_command_once = getOptionToString("page10_button19_command_once");
  page10_button19_command_continue =
      getOptionToString("page10_button19_command_continue");
  Page10_Button19LabelCmd = XPLMFindCommand(page10_button19_label.c_str());
  Page10_Button19CommandOnceCmd =
      XPLMFindCommand(page10_button19_command_once.c_str());
  Page10_Button19CommandContinueCmd =
      XPLMFindCommand(page10_button19_command_continue.c_str());

  page10_button20_label = getOptionToString("page10_button20_label");
  page10_button20_command_once = getOptionToString("page10_button20_command_once");
  page10_button20_command_continue =
      getOptionToString("page10_button20_command_continue");
  Page10_Button20LabelCmd = XPLMFindCommand(page10_button20_label.c_str());
  Page10_Button20CommandOnceCmd =
      XPLMFindCommand(page10_button20_command_once.c_str());
  Page10_Button20CommandContinueCmd =
      XPLMFindCommand(page10_button20_command_continue.c_str());

  page10_button21_label = getOptionToString("page10_button21_label");
  page10_button21_command_once = getOptionToString("page10_button21_command_once");
  page10_button21_command_continue =
      getOptionToString("page10_button21_command_continue");
  Page10_Button21LabelCmd = XPLMFindCommand(page10_button21_label.c_str());
  Page10_Button21CommandOnceCmd =
      XPLMFindCommand(page10_button21_command_once.c_str());
  Page10_Button21CommandContinueCmd =
      XPLMFindCommand(page10_button21_command_continue.c_str());

  page10_button22_label = getOptionToString("page10_button22_label");
  page10_button22_command_once =
      getOptionToString("page10_button22_command_once");
  page10_button22_command_continue =
      getOptionToString("page10_button22_command_continue");
  Page10_Button22LabelCmd = XPLMFindCommand(page10_button22_label.c_str());
  Page10_Button22CommandOnceCmd =
      XPLMFindCommand(page10_button22_command_once.c_str());
  Page10_Button22CommandContinueCmd =
      XPLMFindCommand(page10_button22_command_continue.c_str());

  page10_button23_label = getOptionToString("page10_button23_label");
  page10_button23_command_once =
      getOptionToString("page10_button23_command_once");
  page10_button23_command_continue =
      getOptionToString("page10_button23_command_continue");
  Page10_Button23LabelCmd = XPLMFindCommand(page10_button23_label.c_str());
  Page10_Button23CommandOnceCmd =
      XPLMFindCommand(page10_button23_command_once.c_str());
  Page10_Button23CommandContinueCmd =
      XPLMFindCommand(page10_button23_command_continue.c_str());

  page10_button24_label = getOptionToString("page10_button24_label");
  page10_button24_command_once =
      getOptionToString("page10_button24_command_once");
  page10_button24_command_continue =
      getOptionToString("page10_button24_command_continue");
  Page10_Button24LabelCmd = XPLMFindCommand(page10_button24_label.c_str());
  Page10_Button24CommandOnceCmd =
      XPLMFindCommand(page10_button24_command_once.c_str());
  Page10_Button24CommandContinueCmd =
      XPLMFindCommand(page10_button24_command_continue.c_str());


  //  **************************  page eleven **********************************

  page11_button_label = getOptionToString("page11_button_label");

  page11_button1_label = getOptionToString("page11_button1_label");
  page11_button1_command_once = getOptionToString("page11_button1_command_once");
  page11_button1_command_continue =
      getOptionToString("page11_button1_command_continue");
  Page11_Button1LabelCmd = XPLMFindCommand(page11_button1_label.c_str());
  Page11_Button1CommandOnceCmd =
      XPLMFindCommand(page11_button1_command_once.c_str());
  Page11_Button1CommandContinueCmd =
      XPLMFindCommand(page11_button1_command_continue.c_str());

  page11_button2_label = getOptionToString("page11_button2_label");
  page11_button2_command_once = getOptionToString("page11_button2_command_once");
  page11_button2_command_continue =
      getOptionToString("page11_button2_command_continue");
  Page11_Button2LabelCmd = XPLMFindCommand(page11_button2_label.c_str());
  Page11_Button2CommandOnceCmd =
      XPLMFindCommand(page11_button2_command_once.c_str());
  Page11_Button2CommandContinueCmd =
      XPLMFindCommand(page11_button2_command_continue.c_str());

  page11_button3_label = getOptionToString("page11_button3_label");
  page11_button3_command_once = getOptionToString("page11_button3_command_once");
  page11_button3_command_continue =
      getOptionToString("page11_button3_command_continue");
  Page11_Button3LabelCmd = XPLMFindCommand(page11_button3_label.c_str());
  Page11_Button3CommandOnceCmd =
      XPLMFindCommand(page11_button3_command_once.c_str());
  Page11_Button3CommandContinueCmd =
      XPLMFindCommand(page11_button3_command_continue.c_str());

  page11_button4_label = getOptionToString("page11_button4_label");
  page11_button4_command_once = getOptionToString("page11_button4_command_once");
  page11_button4_command_continue =
      getOptionToString("page11_button4_command_continue");
  Page11_Button4LabelCmd = XPLMFindCommand(page11_button4_label.c_str());
  Page11_Button4CommandOnceCmd =
      XPLMFindCommand(page11_button4_command_once.c_str());
  Page11_Button4CommandContinueCmd =
      XPLMFindCommand(page11_button4_command_continue.c_str());

  page11_button5_label = getOptionToString("page11_button5_label");
  page11_button5_command_once = getOptionToString("page11_button5_command_once");
  page11_button5_command_continue =
      getOptionToString("page11_button5_command_continue");
  Page11_Button5LabelCmd = XPLMFindCommand(page11_button5_label.c_str());
  Page11_Button5CommandOnceCmd =
      XPLMFindCommand(page11_button5_command_once.c_str());
  Page11_Button5CommandContinueCmd =
      XPLMFindCommand(page11_button5_command_continue.c_str());

  page11_button6_label = getOptionToString("page11_button6_label");
  page11_button6_command_once = getOptionToString("page11_button6_command_once");
  page11_button6_command_continue =
      getOptionToString("page11_button6_command_continue");
  Page11_Button6LabelCmd = XPLMFindCommand(page11_button6_label.c_str());
  Page11_Button6CommandOnceCmd =
      XPLMFindCommand(page11_button6_command_once.c_str());
  Page11_Button6CommandContinueCmd =
      XPLMFindCommand(page11_button6_command_continue.c_str());

  page11_button7_label = getOptionToString("page11_button7_label");
  page11_button7_command_once = getOptionToString("page11_button7_command_once");
  page11_button7_command_continue =
      getOptionToString("page11_button7_command_continue");
  Page11_Button7LabelCmd = XPLMFindCommand(page11_button7_label.c_str());
  Page11_Button7CommandOnceCmd =
      XPLMFindCommand(page11_button7_command_once.c_str());
  Page11_Button7CommandContinueCmd =
      XPLMFindCommand(page11_button7_command_continue.c_str());

  page11_button8_label = getOptionToString("page11_button8_label");
  page11_button8_command_once = getOptionToString("page11_button8_command_once");
  page11_button8_command_continue =
      getOptionToString("page11_button8_command_continue");
  Page11_Button8LabelCmd = XPLMFindCommand(page11_button8_label.c_str());
  Page11_Button8CommandOnceCmd =
      XPLMFindCommand(page11_button8_command_once.c_str());
  Page11_Button8CommandContinueCmd =
      XPLMFindCommand(page11_button8_command_continue.c_str());

  page11_button9_label = getOptionToString("page11_button9_label");
  page11_button9_command_once = getOptionToString("page11_button9_command_once");
  page11_button9_command_continue =
      getOptionToString("page11_button9_command_continue");
  Page11_Button9LabelCmd = XPLMFindCommand(page11_button9_label.c_str());
  Page11_Button9CommandOnceCmd =
      XPLMFindCommand(page11_button9_command_once.c_str());
  Page11_Button9CommandContinueCmd =
      XPLMFindCommand(page11_button9_command_continue.c_str());

  page11_button10_label = getOptionToString("page11_button10_label");
  page11_button10_command_once =
      getOptionToString("page11_button10_command_once");
  page11_button10_command_continue =
      getOptionToString("page11_button10_command_continue");
  Page11_Button10LabelCmd = XPLMFindCommand(page11_button10_label.c_str());
  Page11_Button10CommandOnceCmd =
      XPLMFindCommand(page11_button10_command_once.c_str());
  Page11_Button10CommandContinueCmd =
      XPLMFindCommand(page11_button10_command_continue.c_str());

  page11_button11_label = getOptionToString("page11_button11_label");
  page11_button11_command_once =
      getOptionToString("page11_button11_command_once");
  page11_button11_command_continue =
      getOptionToString("page11_button11_command_continue");
  Page11_Button11LabelCmd = XPLMFindCommand(page11_button11_label.c_str());
  Page11_Button11CommandOnceCmd =
      XPLMFindCommand(page11_button11_command_once.c_str());
  Page11_Button11CommandContinueCmd =
      XPLMFindCommand(page11_button11_command_continue.c_str());

  page11_button12_label = getOptionToString("page11_button12_label");
  page11_button12_command_once =
      getOptionToString("page11_button12_command_once");
  page11_button12_command_continue =
      getOptionToString("page11_button12_command_continue");
  Page11_Button12LabelCmd = XPLMFindCommand(page11_button12_label.c_str());
  Page11_Button12CommandOnceCmd =
      XPLMFindCommand(page11_button12_command_once.c_str());
  Page11_Button12CommandContinueCmd =
      XPLMFindCommand(page11_button12_command_continue.c_str());

  page11_button13_label = getOptionToString("page11_button13_label");
  page11_button13_command_once = getOptionToString("page11_button13_command_once");
  page11_button13_command_continue =
      getOptionToString("page11_button13_command_continue");
  Page11_Button13LabelCmd = XPLMFindCommand(page11_button13_label.c_str());
  Page11_Button13CommandOnceCmd =
      XPLMFindCommand(page11_button13_command_once.c_str());
  Page11_Button13CommandContinueCmd =
      XPLMFindCommand(page11_button13_command_continue.c_str());

  page11_button14_label = getOptionToString("page11_button14_label");
  page11_button14_command_once = getOptionToString("page11_button14_command_once");
  page11_button14_command_continue =
      getOptionToString("page11_button14_command_continue");
  Page11_Button14LabelCmd = XPLMFindCommand(page11_button14_label.c_str());
  Page11_Button14CommandOnceCmd =
      XPLMFindCommand(page11_button14_command_once.c_str());
  Page11_Button14CommandContinueCmd =
      XPLMFindCommand(page11_button14_command_continue.c_str());

  page11_button15_label = getOptionToString("page11_button15_label");
  page11_button15_command_once = getOptionToString("page11_button15_command_once");
  page11_button15_command_continue =
      getOptionToString("page11_button15_command_continue");
  Page11_Button15LabelCmd = XPLMFindCommand(page11_button15_label.c_str());
  Page11_Button15CommandOnceCmd =
      XPLMFindCommand(page11_button15_command_once.c_str());
  Page11_Button15CommandContinueCmd =
      XPLMFindCommand(page11_button15_command_continue.c_str());

  page11_button16_label = getOptionToString("page11_button16_label");
  page11_button16_command_once = getOptionToString("page11_button16_command_once");
  page11_button16_command_continue =
      getOptionToString("page11_button16_command_continue");
  Page11_Button16LabelCmd = XPLMFindCommand(page11_button16_label.c_str());
  Page11_Button16CommandOnceCmd =
      XPLMFindCommand(page11_button16_command_once.c_str());
  Page11_Button16CommandContinueCmd =
      XPLMFindCommand(page11_button16_command_continue.c_str());

  page11_button17_label = getOptionToString("page11_button17_label");
  page11_button17_command_once = getOptionToString("page11_button17_command_once");
  page11_button17_command_continue =
      getOptionToString("page11_button17_command_continue");
  Page11_Button17LabelCmd = XPLMFindCommand(page11_button17_label.c_str());
  Page11_Button17CommandOnceCmd =
      XPLMFindCommand(page11_button17_command_once.c_str());
  Page11_Button17CommandContinueCmd =
      XPLMFindCommand(page11_button17_command_continue.c_str());

  page11_button18_label = getOptionToString("page11_button18_label");
  page11_button18_command_once = getOptionToString("page11_button18_command_once");
  page11_button18_command_continue =
      getOptionToString("page11_button18_command_continue");
  Page11_Button18LabelCmd = XPLMFindCommand(page11_button18_label.c_str());
  Page11_Button18CommandOnceCmd =
      XPLMFindCommand(page11_button18_command_once.c_str());
  Page11_Button18CommandContinueCmd =
      XPLMFindCommand(page11_button18_command_continue.c_str());

  page11_button19_label = getOptionToString("page11_button19_label");
  page11_button19_command_once = getOptionToString("page11_button19_command_once");
  page11_button19_command_continue =
      getOptionToString("page11_button19_command_continue");
  Page11_Button19LabelCmd = XPLMFindCommand(page11_button19_label.c_str());
  Page11_Button19CommandOnceCmd =
      XPLMFindCommand(page11_button19_command_once.c_str());
  Page11_Button19CommandContinueCmd =
      XPLMFindCommand(page11_button19_command_continue.c_str());

  page11_button20_label = getOptionToString("page11_button20_label");
  page11_button20_command_once = getOptionToString("page11_button20_command_once");
  page11_button20_command_continue =
      getOptionToString("page11_button20_command_continue");
  Page11_Button20LabelCmd = XPLMFindCommand(page11_button20_label.c_str());
  Page11_Button20CommandOnceCmd =
      XPLMFindCommand(page11_button20_command_once.c_str());
  Page11_Button20CommandContinueCmd =
      XPLMFindCommand(page11_button20_command_continue.c_str());

  page11_button21_label = getOptionToString("page11_button21_label");
  page11_button21_command_once = getOptionToString("page11_button21_command_once");
  page11_button21_command_continue =
      getOptionToString("page11_button21_command_continue");
  Page11_Button21LabelCmd = XPLMFindCommand(page11_button21_label.c_str());
  Page11_Button21CommandOnceCmd =
      XPLMFindCommand(page11_button21_command_once.c_str());
  Page11_Button21CommandContinueCmd =
      XPLMFindCommand(page11_button21_command_continue.c_str());

  page11_button22_label = getOptionToString("page11_button22_label");
  page11_button22_command_once =
      getOptionToString("page11_button22_command_once");
  page11_button22_command_continue =
      getOptionToString("page11_button22_command_continue");
  Page11_Button22LabelCmd = XPLMFindCommand(page10_button22_label.c_str());
  Page11_Button22CommandOnceCmd =
      XPLMFindCommand(page11_button22_command_once.c_str());
  Page11_Button22CommandContinueCmd =
      XPLMFindCommand(page11_button22_command_continue.c_str());

  page11_button23_label = getOptionToString("page11_button23_label");
  page11_button23_command_once =
      getOptionToString("page11_button23_command_once");
  page11_button23_command_continue =
      getOptionToString("page11_button23_command_continue");
  Page11_Button23LabelCmd = XPLMFindCommand(page11_button23_label.c_str());
  Page11_Button23CommandOnceCmd =
      XPLMFindCommand(page11_button23_command_once.c_str());
  Page11_Button23CommandContinueCmd =
      XPLMFindCommand(page11_button23_command_continue.c_str());

  page11_button24_label = getOptionToString("page11_button24_label");
  page11_button24_command_once =
      getOptionToString("page11_button24_command_once");
  page11_button24_command_continue =
      getOptionToString("page11_button24_command_continue");
  Page11_Button24LabelCmd = XPLMFindCommand(page11_button24_label.c_str());
  Page11_Button24CommandOnceCmd =
      XPLMFindCommand(page11_button24_command_once.c_str());
  Page11_Button24CommandContinueCmd =
      XPLMFindCommand(page11_button24_command_continue.c_str());


  //  **************************  page twelve **********************************

  page12_button_label = getOptionToString("page12_button_label");

  page12_button1_label = getOptionToString("page12_button1_label");
  page12_button1_command_once = getOptionToString("page12_button1_command_once");
  page12_button1_command_continue =
      getOptionToString("page12_button1_command_continue");
  Page12_Button1LabelCmd = XPLMFindCommand(page12_button1_label.c_str());
  Page12_Button1CommandOnceCmd =
      XPLMFindCommand(page12_button1_command_once.c_str());
  Page12_Button1CommandContinueCmd =
      XPLMFindCommand(page12_button1_command_continue.c_str());

  page12_button2_label = getOptionToString("page12_button2_label");
  page12_button2_command_once = getOptionToString("page12_button2_command_once");
  page12_button2_command_continue =
      getOptionToString("page12_button2_command_continue");
  Page12_Button2LabelCmd = XPLMFindCommand(page12_button2_label.c_str());
  Page12_Button2CommandOnceCmd =
      XPLMFindCommand(page12_button2_command_once.c_str());
  Page12_Button2CommandContinueCmd =
      XPLMFindCommand(page12_button2_command_continue.c_str());

  page12_button3_label = getOptionToString("page12_button3_label");
  page12_button3_command_once = getOptionToString("page12_button3_command_once");
  page12_button3_command_continue =
      getOptionToString("page12_button3_command_continue");
  Page12_Button3LabelCmd = XPLMFindCommand(page12_button3_label.c_str());
  Page12_Button3CommandOnceCmd =
      XPLMFindCommand(page12_button3_command_once.c_str());
  Page12_Button3CommandContinueCmd =
      XPLMFindCommand(page12_button3_command_continue.c_str());

  page12_button4_label = getOptionToString("page12_button4_label");
  page12_button4_command_once = getOptionToString("page12_button4_command_once");
  page12_button4_command_continue =
      getOptionToString("page12_button4_command_continue");
  Page12_Button4LabelCmd = XPLMFindCommand(page12_button4_label.c_str());
  Page12_Button4CommandOnceCmd =
      XPLMFindCommand(page12_button4_command_once.c_str());
  Page12_Button4CommandContinueCmd =
      XPLMFindCommand(page12_button4_command_continue.c_str());

  page12_button5_label = getOptionToString("page12_button5_label");
  page12_button5_command_once = getOptionToString("page12_button5_command_once");
  page12_button5_command_continue =
      getOptionToString("page12_button5_command_continue");
  Page12_Button5LabelCmd = XPLMFindCommand(page12_button5_label.c_str());
  Page12_Button5CommandOnceCmd =
      XPLMFindCommand(page12_button5_command_once.c_str());
  Page12_Button5CommandContinueCmd =
      XPLMFindCommand(page12_button5_command_continue.c_str());

  page12_button6_label = getOptionToString("page12_button6_label");
  page12_button6_command_once = getOptionToString("page12_button6_command_once");
  page12_button6_command_continue =
      getOptionToString("page12_button6_command_continue");
  Page12_Button6LabelCmd = XPLMFindCommand(page12_button6_label.c_str());
  Page12_Button6CommandOnceCmd =
      XPLMFindCommand(page12_button6_command_once.c_str());
  Page12_Button6CommandContinueCmd =
      XPLMFindCommand(page12_button6_command_continue.c_str());

  page12_button7_label = getOptionToString("page12_button7_label");
  page12_button7_command_once = getOptionToString("page12_button7_command_once");
  page12_button7_command_continue =
      getOptionToString("page12_button7_command_continue");
  Page12_Button7LabelCmd = XPLMFindCommand(page12_button7_label.c_str());
  Page12_Button7CommandOnceCmd =
      XPLMFindCommand(page12_button7_command_once.c_str());
  Page12_Button7CommandContinueCmd =
      XPLMFindCommand(page12_button7_command_continue.c_str());

  page12_button8_label = getOptionToString("page12_button8_label");
  page12_button8_command_once = getOptionToString("page12_button8_command_once");
  page12_button8_command_continue =
      getOptionToString("page12_button8_command_continue");
  Page12_Button8LabelCmd = XPLMFindCommand(page12_button8_label.c_str());
  Page12_Button8CommandOnceCmd =
      XPLMFindCommand(page12_button8_command_once.c_str());
  Page12_Button8CommandContinueCmd =
      XPLMFindCommand(page12_button8_command_continue.c_str());

  page12_button9_label = getOptionToString("page12_button9_label");
  page12_button9_command_once = getOptionToString("page12_button9_command_once");
  page12_button9_command_continue =
      getOptionToString("page12_button9_command_continue");
  Page12_Button9LabelCmd = XPLMFindCommand(page11_button9_label.c_str());
  Page12_Button9CommandOnceCmd =
      XPLMFindCommand(page12_button9_command_once.c_str());
  Page12_Button9CommandContinueCmd =
      XPLMFindCommand(page12_button9_command_continue.c_str());

  page12_button10_label = getOptionToString("page12_button10_label");
  page12_button10_command_once =
      getOptionToString("page12_button10_command_once");
  page12_button10_command_continue =
      getOptionToString("page12_button10_command_continue");
  Page12_Button10LabelCmd = XPLMFindCommand(page12_button10_label.c_str());
  Page12_Button10CommandOnceCmd =
      XPLMFindCommand(page12_button10_command_once.c_str());
  Page12_Button10CommandContinueCmd =
      XPLMFindCommand(page12_button10_command_continue.c_str());

  page12_button11_label = getOptionToString("page12_button11_label");
  page12_button11_command_once =
      getOptionToString("page12_button11_command_once");
  page12_button11_command_continue =
      getOptionToString("page12_button11_command_continue");
  Page12_Button11LabelCmd = XPLMFindCommand(page11_button11_label.c_str());
  Page12_Button11CommandOnceCmd =
      XPLMFindCommand(page12_button11_command_once.c_str());
  Page12_Button11CommandContinueCmd =
      XPLMFindCommand(page12_button11_command_continue.c_str());

  page12_button12_label = getOptionToString("page12_button12_label");
  page12_button12_command_once =
      getOptionToString("page12_button12_command_once");
  page12_button12_command_continue =
      getOptionToString("page12_button12_command_continue");
  Page12_Button12LabelCmd = XPLMFindCommand(page11_button12_label.c_str());
  Page12_Button12CommandOnceCmd =
      XPLMFindCommand(page12_button12_command_once.c_str());
  Page12_Button12CommandContinueCmd =
      XPLMFindCommand(page12_button12_command_continue.c_str());

  page12_button13_label = getOptionToString("page12_button13_label");
  page12_button13_command_once = getOptionToString("page12_button13_command_once");
  page12_button13_command_continue =
      getOptionToString("page12_button13_command_continue");
  Page12_Button13LabelCmd = XPLMFindCommand(page12_button13_label.c_str());
  Page12_Button13CommandOnceCmd =
      XPLMFindCommand(page12_button13_command_once.c_str());
  Page12_Button13CommandContinueCmd =
      XPLMFindCommand(page12_button13_command_continue.c_str());

  page12_button14_label = getOptionToString("page12_button14_label");
  page12_button14_command_once = getOptionToString("page12_button14_command_once");
  page12_button14_command_continue =
      getOptionToString("page12_button14_command_continue");
  Page12_Button14LabelCmd = XPLMFindCommand(page12_button14_label.c_str());
  Page12_Button14CommandOnceCmd =
      XPLMFindCommand(page12_button14_command_once.c_str());
  Page12_Button14CommandContinueCmd =
      XPLMFindCommand(page12_button14_command_continue.c_str());

  page12_button15_label = getOptionToString("page12_button15_label");
  page12_button15_command_once = getOptionToString("page12_button15_command_once");
  page12_button15_command_continue =
      getOptionToString("page12_button15_command_continue");
  Page12_Button15LabelCmd = XPLMFindCommand(page12_button15_label.c_str());
  Page12_Button15CommandOnceCmd =
      XPLMFindCommand(page12_button15_command_once.c_str());
  Page12_Button15CommandContinueCmd =
      XPLMFindCommand(page12_button15_command_continue.c_str());

  page12_button16_label = getOptionToString("page12_button16_label");
  page12_button16_command_once = getOptionToString("page12_button16_command_once");
  page12_button16_command_continue =
      getOptionToString("page12_button16_command_continue");
  Page12_Button16LabelCmd = XPLMFindCommand(page12_button16_label.c_str());
  Page12_Button16CommandOnceCmd =
      XPLMFindCommand(page12_button16_command_once.c_str());
  Page12_Button16CommandContinueCmd =
      XPLMFindCommand(page12_button16_command_continue.c_str());

  page12_button17_label = getOptionToString("page12_button17_label");
  page12_button17_command_once = getOptionToString("page12_button17_command_once");
  page12_button17_command_continue =
      getOptionToString("page12_button17_command_continue");
  Page12_Button17LabelCmd = XPLMFindCommand(page12_button17_label.c_str());
  Page12_Button17CommandOnceCmd =
      XPLMFindCommand(page12_button17_command_once.c_str());
  Page12_Button17CommandContinueCmd =
      XPLMFindCommand(page12_button17_command_continue.c_str());

  page12_button18_label = getOptionToString("page12_button18_label");
  page12_button18_command_once = getOptionToString("page12_button18_command_once");
  page12_button18_command_continue =
      getOptionToString("page12_button18_command_continue");
  Page12_Button18LabelCmd = XPLMFindCommand(page12_button18_label.c_str());
  Page12_Button18CommandOnceCmd =
      XPLMFindCommand(page12_button18_command_once.c_str());
  Page12_Button18CommandContinueCmd =
      XPLMFindCommand(page12_button18_command_continue.c_str());

  page12_button19_label = getOptionToString("page12_button19_label");
  page12_button19_command_once = getOptionToString("page12_button19_command_once");
  page12_button19_command_continue =
      getOptionToString("page12_button19_command_continue");
  Page12_Button19LabelCmd = XPLMFindCommand(page12_button19_label.c_str());
  Page12_Button19CommandOnceCmd =
      XPLMFindCommand(page12_button19_command_once.c_str());
  Page12_Button19CommandContinueCmd =
      XPLMFindCommand(page12_button19_command_continue.c_str());

  page12_button20_label = getOptionToString("page12_button20_label");
  page12_button20_command_once = getOptionToString("page12_button20_command_once");
  page12_button20_command_continue =
      getOptionToString("page12_button20_command_continue");
  Page12_Button20LabelCmd = XPLMFindCommand(page12_button20_label.c_str());
  Page12_Button20CommandOnceCmd =
      XPLMFindCommand(page12_button20_command_once.c_str());
  Page12_Button20CommandContinueCmd =
      XPLMFindCommand(page12_button20_command_continue.c_str());

  page12_button21_label = getOptionToString("page12_button21_label");
  page12_button21_command_once = getOptionToString("page12_button21_command_once");
  page12_button21_command_continue =
      getOptionToString("page12_button21_command_continue");
  Page12_Button21LabelCmd = XPLMFindCommand(page12_button21_label.c_str());
  Page12_Button21CommandOnceCmd =
      XPLMFindCommand(page12_button21_command_once.c_str());
  Page12_Button21CommandContinueCmd =
      XPLMFindCommand(page12_button21_command_continue.c_str());

  page12_button22_label = getOptionToString("page12_button22_label");
  page12_button22_command_once =
      getOptionToString("page12_button22_command_once");
  page12_button22_command_continue =
      getOptionToString("page12_button22_command_continue");
  Page12_Button22LabelCmd = XPLMFindCommand(page12_button22_label.c_str());
  Page12_Button22CommandOnceCmd =
      XPLMFindCommand(page12_button22_command_once.c_str());
  Page12_Button22CommandContinueCmd =
      XPLMFindCommand(page12_button22_command_continue.c_str());

  page12_button23_label = getOptionToString("page12_button23_label");
  page12_button23_command_once =
      getOptionToString("page12_button23_command_once");
  page12_button23_command_continue =
      getOptionToString("page12_button23_command_continue");
  Page12_Button23LabelCmd = XPLMFindCommand(page12_button23_label.c_str());
  Page12_Button23CommandOnceCmd =
      XPLMFindCommand(page12_button23_command_once.c_str());
  Page12_Button23CommandContinueCmd =
      XPLMFindCommand(page12_button23_command_continue.c_str());

  page12_button24_label = getOptionToString("page12_button24_label");
  page12_button24_command_once =
      getOptionToString("page12_button24_command_once");
  page12_button24_command_continue =
      getOptionToString("page12_button24_command_continue");
  Page12_Button24LabelCmd = XPLMFindCommand(page12_button24_label.c_str());
  Page12_Button24CommandOnceCmd =
      XPLMFindCommand(page12_button24_command_once.c_str());
  Page12_Button24CommandContinueCmd =
      XPLMFindCommand(page12_button24_command_continue.c_str());
}
