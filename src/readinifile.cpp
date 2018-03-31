// ****** readinifile.cpp **********
// ****  William R. Good  ********

#include "XPLMPlugin.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMCamera.h"
#include "XPLMPlanes.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "XPLMMenus.h"

#include "xbtn2cmd.h"
#include "inireader.h"
#include <vector>

#include <iostream>
#include <fstream>
//#include <string>
#include <string.h>

string convert_Mac_Path(string in_path) {

    //char seperator_number_buffer[255] = {0};

    std::size_t len = in_path.length();
    std::size_t pos = in_path.find(":");

    in_path.erase (in_path.begin()+0, in_path.end()-(len - pos));

    int count = 0;
    for (int i = 0; i < in_path.size(); i++)
       if (in_path[i] == ':') count++;
            // sprintf(seperator_number_buffer, "Xsaitekpanels: How many path seperators are in the path = %d\n", count);
            // XPLMDebugString(seperator_number_buffer);

    size_t found;
    int n = count;

    while (n>0) {
       found = in_path.find(":");
       in_path.replace(found, 1,"/");
       --n;
    }

    std::size_t pos2 = in_path.find("/Aircraft");
    std::string tmp_in_path = in_path.substr (pos2);
    tmp_in_path.insert(0,".");
    in_path = tmp_in_path;

    return in_path;
}

// ***** Configuration File Process ******
void process_read_ini_file()

{

    char *iniDefaultPluginPath;
    //const char *defaultConfigFileName;

    iniDefaultPluginPath = "./Resources/plugins/Xbtn2cmd/xbtn2cmd.ini";
    //defaultConfigFileName = "xsaitekpanels.ini";
    int Index2;
    string version;






    //char *configPath;

    cleanupIniReader();

    char xpsacfname[512];
    char xpsacfpath[512];
    XPLMGetNthAircraftModel(0, xpsacfname, xpsacfpath);

    char	radtestbuf1[256];

    //XPLMDebugString("\nXsaitekpanels: Raw Current aircraft path is \n");
    //XPLMDebugString(xpsacfpath);
    //XPLMDebugString("\n");

    if(strlen(xpsacfpath) == 0){
      return;
    }

    std::string xpsini_path_name = xpsacfpath;
    std::size_t pos = xpsini_path_name.find(xpsacfname);
    xpsini_path_name = xpsini_path_name.substr(0, pos);

    std::string xpsini_aircraft_name = xpsacfname;
    std::size_t pos1 = xpsini_aircraft_name.find(".acf");
    xpsini_aircraft_name = xpsini_aircraft_name.substr(0, pos1);

    #if APL && __MACH__
        std::string mac_converted_path = convert_Mac_Path(xpsini_path_name);
        XPLMDebugString("\nXbtn2cmd: mac_converted_path is \n");
        XPLMDebugString(mac_converted_path.c_str());
        XPLMDebugString("\n");
        //mac_converted_path = "./Aircraft/General Aviation/KingAir C90B/";
        xpsini_path_name = mac_converted_path;
    #endif

    std::string xpsini_path_name1 = xpsini_path_name;

    xpsini_path_name1.append("xbtn2cmd.ini");

    xpsini_path_name.append(xpsini_aircraft_name);

    xpsini_path_name.append("_xbtn2cmd.ini");

    int found_file = 0;

    std::vector<char> parse_ini_path_name(xpsini_path_name.size() + 1);
    std::copy(xpsini_path_name.begin(), xpsini_path_name.end(), parse_ini_path_name.begin());

    std::ifstream ifile(&parse_ini_path_name[0]);
    if (ifile) {
        XPLMDebugString("\nXbtn2cmd: Found xbtn2cmd.ini in the current aircraft path and it is\n");
        XPLMDebugString(&parse_ini_path_name[0]);
        XPLMDebugString("\n");

        parseIniFile(&parse_ini_path_name[0]);
        found_file = 1;

    } else if (!ifile) {
        std::vector<char> parse_ini_path_name1(xpsini_path_name1.size() + 1);
        std::copy(xpsini_path_name1.begin(), xpsini_path_name1.end(), parse_ini_path_name1.begin());

        std::ifstream ifile1(&parse_ini_path_name1[0]);
        if (ifile1) {
            XPLMDebugString("\nXbtn2cmd: Found xbtn2cmd.ini in the current aircraft path and it is\n");
            XPLMDebugString(&parse_ini_path_name1[0]);
            XPLMDebugString("\n");

            parseIniFile(&parse_ini_path_name1[0]);
            found_file = 1;

        }
        if (found_file == 0) {
            XPLMDebugString("\nXbtn2cmd: Did not find xbtn2cms.ini in the current aircraft path\n");
        }

        std::ifstream ifile2(iniDefaultPluginPath);
        if (ifile2) {
            if (found_file == 0) {

                XPLMDebugString("\nXbtn2cmd: Found xbtn2cmd.ini in the Xbtn2cmd plugin path and it is\n");
                XPLMDebugString(iniDefaultPluginPath);
                XPLMDebugString("\n");

                parseIniFile(iniDefaultPluginPath);
            }
       } else {
           return;
       }

    }

    // get xbtn2cmd.ini version
    version = getOptionToString("Version");
    XPLMDebugString("\nXbtn2cmd: xbtn2cmd.ini is version   ");
    XPLMDebugString(version.c_str());
    XPLMDebugString("\n");

    // Do we want to enable data reference editor?
    // readOptionAsInt("Data Reference Editor enable", &dre_enable);

    // Do we want to display the plane icao on screen?
    // readOptionAsInt("Display Plane ICAO On Screen Enable", &icao_enable);

    // Do we want debug loging enabled
    // readOptionAsInt("Add Debug Entries To Log Enable", &log_enable);

    // sprintf(buf, "Xsaitekpanels: dre_enable = %d  icao_enable = %d  log_enable = %d\n",dre_enable, icao_enable, log_enable);
    // XPLMDebugString(buf);


    button1_label = getOptionToString("button1_label");
    button1_command = getOptionToString("button1_command");
    Button1LabelCmd = XPLMFindCommand(button1_label.c_str());
    Button1CommandCmd = XPLMFindCommand(button1_command.c_str());

    button2_label = getOptionToString("button2_label");
    button2_command = getOptionToString("button2_command");
    Button2LabelCmd = XPLMFindCommand(button2_label.c_str());
    Button2CommandCmd = XPLMFindCommand(button2_command.c_str());

    button3_label = getOptionToString("button3_label");
    button3_command = getOptionToString("button3_command");
    Button3LabelCmd = XPLMFindCommand(button3_label.c_str());
    Button3CommandCmd = XPLMFindCommand(button3_command.c_str());

    button4_label = getOptionToString("button4_label");
    button4_command = getOptionToString("button4_command");
    Button4LabelCmd = XPLMFindCommand(button4_label.c_str());
    Button4CommandCmd = XPLMFindCommand(button4_command.c_str());

    button5_label = getOptionToString("button5_label");
    button5_command = getOptionToString("button5_command");
    Button5LabelCmd = XPLMFindCommand(button5_label.c_str());
    Button5CommandCmd = XPLMFindCommand(button5_command.c_str());


    button6_label = getOptionToString("button6_label");
    button6_command = getOptionToString("button6_command");
    Button6LabelCmd = XPLMFindCommand(button6_label.c_str());
    Button6CommandCmd = XPLMFindCommand(button6_command.c_str());

    button7_label = getOptionToString("button7_label");
    button7_command = getOptionToString("button7_command");
    Button7LabelCmd = XPLMFindCommand(button7_label.c_str());
    Button7CommandCmd = XPLMFindCommand(button7_command.c_str());

    button8_label = getOptionToString("button8_label");
    button8_command = getOptionToString("button8_command");
    Button8LabelCmd = XPLMFindCommand(button8_label.c_str());
    Button8CommandCmd = XPLMFindCommand(button8_command.c_str());

    button9_label = getOptionToString("button9_label");
    button9_command = getOptionToString("button9_command");
    Button9LabelCmd = XPLMFindCommand(button9_label.c_str());
    Button9CommandCmd = XPLMFindCommand(button9_command.c_str());

    button10_label = getOptionToString("button10_label");
    button10_command = getOptionToString("button10_command");
    Button10LabelCmd = XPLMFindCommand(button10_label.c_str());
    Button10CommandCmd = XPLMFindCommand(button10_command.c_str());



    button11_label = getOptionToString("button11_label");
    button11_command = getOptionToString("button11_command");
    Button11LabelCmd = XPLMFindCommand(button11_label.c_str());
    Button11CommandCmd = XPLMFindCommand(button11_command.c_str());

    button12_label = getOptionToString("button12_label");
    button12_command = getOptionToString("button12_command");
    Button12LabelCmd = XPLMFindCommand(button12_label.c_str());
    Button12CommandCmd = XPLMFindCommand(button12_command.c_str());

  return;
}
