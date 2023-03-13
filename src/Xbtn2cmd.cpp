// *********************************************************
//
//     Xbtn2cmd Plugin
//
//     William Good
//
//     A plugin to create a window of buttons in VR
//     that can be mapped to commands.
//
//     Supporting  X-Plane 12.0+
//
// *********************************************************

#define VERSION_NUMBER "1.51 build " __DATE__ " " __TIME__

#include "XPLMDataAccess.h"  // for the VR dataref
#include "XPLMDisplay.h"     // for window creation and manipulation
#include "XPLMGraphics.h"    // for window drawing
#include "XPLMMenus.h"
#include "XPLMPlugin.h"  // for XPLM_MSG_SCENERY_LOADED message
#include "XPLMProcessing.h"
#include "XPLMUtilities.h"
#include "XPStandardWidgets.h"
#include "XPWidgetUtils.h"
#include "XPWidgets.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <ctime>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "clipboard.h"

using namespace std;

#if IBM
#include <unistd.h>
#include <windows.h>
#endif
#if LIN
#include <GL/gl.h>
#endif
#if __GNUC__ && APL
#include <OpenGL/gl.h>
#endif
#if __GNUC__ && IBM
#include <GL/gl.h>
#endif

#ifndef XPLM301
#error This is made to be compiled against the XPLM301 SDK
#endif

void send_delayed_ctrl_c();

const int C = 0x43;  // C key code
const int V = 0x56;  // V key code

static float DelayedControlC_Callback(float inElapsed1, float inElapsed2,
                                      int cntr, void *ref);

static XPLMWindowID xb2cvr_g_window;

void xb2cvr_draw(XPLMWindowID in_window_id, void *in_refcon);
int xb2cvr_handle_mouse(XPLMWindowID in_window_id, int x, int y, int is_down,
                        void *in_refcon);

int xb2cvr_dummy_mouse_handler(XPLMWindowID /*in_window_id*/, int /*x*/,
                               int /*y*/, int /*is_down*/,
                               void * /*in_refcon*/) {
  return 0;
}
XPLMCursorStatus xb2cvr_dummy_cursor_status_handler(
    XPLMWindowID /*in_window_id*/, int /*x*/, int /*y*/, void * /*in_refcon*/) {
  return xplm_CursorDefault;
}
int xb2cvr_dummy_wheel_handler(XPLMWindowID /*in_window_id*/, int /*x*/,
                               int /*y*/, int /*wheel*/, int /*clicks*/,
                               void * /*in_refcon*/) {
  return 0;
}
void xb2cvr_dummy_key_handler(XPLMWindowID /*in_window_id*/, char /*key*/,
                              XPLMKeyFlags /*flags*/, char /*virtual_key*/,
                              void * /*in_refcon*/, int /*losing_focus*/) {}

XPLMDataRef g_vr_dref;
static bool g_in_vr = false;

int xb2cvr_width = 500;  // width of the widget checklist window

int vr_is_enabled = 0;

XPLMDataRef xb2cvr_g_FPS;

int VersionXP, VersionSDK;
XPLMHostApplicationID HostID;

void xb2cvr_create_gui_window();
void process_read_ini_file();
void process_create_edit_window();

enum {
  TOGGLE_WINDOW_COMMAND,
  RELOAD_CONFIG_COMMAND,
  RELOAD_WINDOW_COMMAND,
  RECREATE_WINDOW_COMMAND,
  OPEN_EDIT_WINDOW_COMMAND
};

int Xbtn2cmdCommandCallback(XPLMCommandRef inCommand, XPLMCommandPhase inPhase,
                            void *inRefcon);

XPLMCommandRef cmdtogglewindow;
XPLMCommandRef cmdreloadconfig;
XPLMCommandRef cmdreloadwindow;
XPLMCommandRef cmdrecreatewindow;
XPLMCommandRef cmdopeneditwindow;

char scratch_buffer[150];

string page1_button_label, page2_button_label, page3_button_label,
    page4_button_label;
string page5_button_label, page6_button_label, page7_button_label,
    page8_button_label;
string page9_button_label, page10_button_label, page11_button_label,
    page12_button_label;

string page1_button1_label, page1_button1_command_once,
    page1_button1_command_continue;
string page1_button2_label, page1_button2_command_once,
    page1_button2_command_continue;
string page1_button3_label, page1_button3_command_once,
    page1_button3_command_continue;
string page1_button4_label, page1_button4_command_once,
    page1_button4_command_continue;
string page1_button5_label, page1_button5_command_once,
    page1_button5_command_continue;
string page1_button6_label, page1_button6_command_once,
    page1_button6_command_continue;
string page1_button7_label, page1_button7_command_once,
    page1_button7_command_continue;
string page1_button8_label, page1_button8_command_once,
    page1_button8_command_continue;
string page1_button9_label, page1_button9_command_once,
    page1_button9_command_continue;
string page1_button10_label, page1_button10_command_once,
    page1_button10_command_continue;
string page1_button11_label, page1_button11_command_once,
    page1_button11_command_continue;
string page1_button12_label, page1_button12_command_once,
    page1_button12_command_continue;

string page2_button1_label, page2_button1_command_once,
    page2_button1_command_continue;
string page2_button2_label, page2_button2_command_once,
    page2_button2_command_continue;
string page2_button3_label, page2_button3_command_once,
    page2_button3_command_continue;
string page2_button4_label, page2_button4_command_once,
    page2_button4_command_continue;
string page2_button5_label, page2_button5_command_once,
    page2_button5_command_continue;
string page2_button6_label, page2_button6_command_once,
    page2_button6_command_continue;
string page2_button7_label, page2_button7_command_once,
    page2_button7_command_continue;
string page2_button8_label, page2_button8_command_once,
    page2_button8_command_continue;
string page2_button9_label, page2_button9_command_once,
    page2_button9_command_continue;
string page2_button10_label, page2_button10_command_once,
    page2_button10_command_continue;
string page2_button11_label, page2_button11_command_once,
    page2_button11_command_continue;
string page2_button12_label, page2_button12_command_once,
    page2_button12_command_continue;

string page3_button1_label, page3_button1_command_once,
    page3_button1_command_continue;
string page3_button2_label, page3_button2_command_once,
    page3_button2_command_continue;
string page3_button3_label, page3_button3_command_once,
    page3_button3_command_continue;
string page3_button4_label, page3_button4_command_once,
    page3_button4_command_continue;
string page3_button5_label, page3_button5_command_once,
    page3_button5_command_continue;
string page3_button6_label, page3_button6_command_once,
    page3_button6_command_continue;
string page3_button7_label, page3_button7_command_once,
    page3_button7_command_continue;
string page3_button8_label, page3_button8_command_once,
    page3_button8_command_continue;
string page3_button9_label, page3_button9_command_once,
    page3_button9_command_continue;
string page3_button10_label, page3_button10_command_once,
    page3_button10_command_continue;
string page3_button11_label, page3_button11_command_once,
    page3_button11_command_continue;
string page3_button12_label, page3_button12_command_once,
    page3_button12_command_continue;

string page4_button1_label, page4_button1_command_once,
    page4_button1_command_continue;
string page4_button2_label, page4_button2_command_once,
    page4_button2_command_continue;
string page4_button3_label, page4_button3_command_once,
    page4_button3_command_continue;
string page4_button4_label, page4_button4_command_once,
    page4_button4_command_continue;
string page4_button5_label, page4_button5_command_once,
    page4_button5_command_continue;
string page4_button6_label, page4_button6_command_once,
    page4_button6_command_continue;
string page4_button7_label, page4_button7_command_once,
    page4_button7_command_continue;
string page4_button8_label, page4_button8_command_once,
    page4_button8_command_continue;
string page4_button9_label, page4_button9_command_once,
    page4_button9_command_continue;
string page4_button10_label, page4_button10_command_once,
    page4_button10_command_continue;
string page4_button11_label, page4_button11_command_once,
    page4_button11_command_continue;
string page4_button12_label, page4_button12_command_once,
    page4_button12_command_continue;

string page5_button1_label, page5_button1_command_once,
    page5_button1_command_continue;
string page5_button2_label, page5_button2_command_once,
    page5_button2_command_continue;
string page5_button3_label, page5_button3_command_once,
    page5_button3_command_continue;
string page5_button4_label, page5_button4_command_once,
    page5_button4_command_continue;
string page5_button5_label, page5_button5_command_once,
    page5_button5_command_continue;
string page5_button6_label, page5_button6_command_once,
    page5_button6_command_continue;
string page5_button7_label, page5_button7_command_once,
    page5_button7_command_continue;
string page5_button8_label, page5_button8_command_once,
    page5_button8_command_continue;
string page5_button9_label, page5_button9_command_once,
    page5_button9_command_continue;
string page5_button10_label, page5_button10_command_once,
    page5_button10_command_continue;
string page5_button11_label, page5_button11_command_once,
    page5_button11_command_continue;
string page5_button12_label, page5_button12_command_once,
    page5_button12_command_continue;

string page6_button1_label, page6_button1_command_once,
    page6_button1_command_continue;
string page6_button2_label, page6_button2_command_once,
    page6_button2_command_continue;
string page6_button3_label, page6_button3_command_once,
    page6_button3_command_continue;
string page6_button4_label, page6_button4_command_once,
    page6_button4_command_continue;
string page6_button5_label, page6_button5_command_once,
    page6_button5_command_continue;
string page6_button6_label, page6_button6_command_once,
    page6_button6_command_continue;
string page6_button7_label, page6_button7_command_once,
    page6_button7_command_continue;
string page6_button8_label, page6_button8_command_once,
    page6_button8_command_continue;
string page6_button9_label, page6_button9_command_once,
    page6_button9_command_continue;
string page6_button10_label, page6_button10_command_once,
    page6_button10_command_continue;
string page6_button11_label, page6_button11_command_once,
    page6_button11_command_continue;
string page6_button12_label, page6_button12_command_once,
    page6_button12_command_continue;

string page7_button1_label, page7_button1_command_once,
    page7_button1_command_continue;
string page7_button2_label, page7_button2_command_once,
    page7_button2_command_continue;
string page7_button3_label, page7_button3_command_once,
    page7_button3_command_continue;
string page7_button4_label, page7_button4_command_once,
    page7_button4_command_continue;
string page7_button5_label, page7_button5_command_once,
    page7_button5_command_continue;
string page7_button6_label, page7_button6_command_once,
    page7_button6_command_continue;
string page7_button7_label, page7_button7_command_once,
    page7_button7_command_continue;
string page7_button8_label, page7_button8_command_once,
    page7_button8_command_continue;
string page7_button9_label, page7_button9_command_once,
    page7_button9_command_continue;
string page7_button10_label, page7_button10_command_once,
    page7_button10_command_continue;
string page7_button11_label, page7_button11_command_once,
    page7_button11_command_continue;
string page7_button12_label, page7_button12_command_once,
    page7_button12_command_continue;

string page8_button1_label, page8_button1_command_once,
    page8_button1_command_continue;
string page8_button2_label, page8_button2_command_once,
    page8_button2_command_continue;
string page8_button3_label, page8_button3_command_once,
    page8_button3_command_continue;
string page8_button4_label, page8_button4_command_once,
    page8_button4_command_continue;
string page8_button5_label, page8_button5_command_once,
    page8_button5_command_continue;
string page8_button6_label, page8_button6_command_once,
    page8_button6_command_continue;
string page8_button7_label, page8_button7_command_once,
    page8_button7_command_continue;
string page8_button8_label, page8_button8_command_once,
    page8_button8_command_continue;
string page8_button9_label, page8_button9_command_once,
    page8_button9_command_continue;
string page8_button10_label, page8_button10_command_once,
    page8_button10_command_continue;
string page8_button11_label, page8_button11_command_once,
    page8_button11_command_continue;
string page8_button12_label, page8_button12_command_once,
    page8_button12_command_continue;


string page9_button1_label, page9_button1_command_once,
    page9_button1_command_continue;
string page9_button2_label, page9_button2_command_once,
    page9_button2_command_continue;
string page9_button3_label, page9_button3_command_once,
    page9_button3_command_continue;
string page9_button4_label, page9_button4_command_once,
    page9_button4_command_continue;
string page9_button5_label, page9_button5_command_once,
    page9_button5_command_continue;
string page9_button6_label, page9_button6_command_once,
    page9_button6_command_continue;
string page9_button7_label, page9_button7_command_once,
    page9_button7_command_continue;
string page9_button8_label, page9_button8_command_once,
    page9_button8_command_continue;
string page9_button9_label, page9_button9_command_once,
    page9_button9_command_continue;
string page9_button10_label, page9_button10_command_once,
    page9_button10_command_continue;
string page9_button11_label, page9_button11_command_once,
    page9_button11_command_continue;
string page9_button12_label, page9_button12_command_once,
    page9_button12_command_continue;
string page9_button13_label, page9_button13_command_once,
    page9_button13_command_continue;
string page9_button14_label, page9_button14_command_once,
    page9_button14_command_continue;
string page9_button15_label, page9_button15_command_once,
    page9_button15_command_continue;
string page9_button16_label, page9_button16_command_once,
    page9_button16_command_continue;
string page9_button17_label, page9_button17_command_once,
    page9_button17_command_continue;
string page9_button18_label, page9_button18_command_once,
    page9_button18_command_continue;
string page9_button19_label, page9_button19_command_once,
    page9_button19_command_continue;
string page9_button20_label, page9_button20_command_once,
    page9_button20_command_continue;
string page9_button21_label, page9_button21_command_once,
    page9_button21_command_continue;
string page9_button22_label, page9_button22_command_once,
    page9_button22_command_continue;
string page9_button23_label, page9_button23_command_once,
    page9_button23_command_continue;
string page9_button24_label, page9_button24_command_once,
    page9_button24_command_continue;


string page10_button1_label, page10_button1_command_once,
    page10_button1_command_continue;
string page10_button2_label, page10_button2_command_once,
    page10_button2_command_continue;
string page10_button3_label, page10_button3_command_once,
    page10_button3_command_continue;
string page10_button4_label, page10_button4_command_once,
    page10_button4_command_continue;
string page10_button5_label, page10_button5_command_once,
    page10_button5_command_continue;
string page10_button6_label, page10_button6_command_once,
    page10_button6_command_continue;
string page10_button7_label, page10_button7_command_once,
    page10_button7_command_continue;
string page10_button8_label, page10_button8_command_once,
    page10_button8_command_continue;
string page10_button9_label, page10_button9_command_once,
    page10_button9_command_continue;
string page10_button10_label, page10_button10_command_once,
    page10_button10_command_continue;
string page10_button11_label, page10_button11_command_once,
    page10_button11_command_continue;
string page10_button12_label, page10_button12_command_once,
    page10_button12_command_continue;
string page10_button13_label, page10_button13_command_once,
    page10_button13_command_continue;
string page10_button14_label, page10_button14_command_once,
    page10_button14_command_continue;
string page10_button15_label, page10_button15_command_once,
    page10_button15_command_continue;
string page10_button16_label, page10_button16_command_once,
    page10_button16_command_continue;
string page10_button17_label, page10_button17_command_once,
    page10_button17_command_continue;
string page10_button18_label, page10_button18_command_once,
    page10_button18_command_continue;
string page10_button19_label, page10_button19_command_once,
    page10_button19_command_continue;
string page10_button20_label, page10_button20_command_once,
    page10_button20_command_continue;
string page10_button21_label, page10_button21_command_once,
    page10_button21_command_continue;
string page10_button22_label, page10_button22_command_once,
    page10_button22_command_continue;
string page10_button23_label, page10_button23_command_once,
    page10_button23_command_continue;
string page10_button24_label, page10_button24_command_once,
    page10_button24_command_continue;



string page11_button1_label, page11_button1_command_once,
    page11_button1_command_continue;
string page11_button2_label, page11_button2_command_once,
    page11_button2_command_continue;
string page11_button3_label, page11_button3_command_once,
    page11_button3_command_continue;
string page11_button4_label, page11_button4_command_once,
    page11_button4_command_continue;
string page11_button5_label, page11_button5_command_once,
    page11_button5_command_continue;
string page11_button6_label, page11_button6_command_once,
    page11_button6_command_continue;
string page11_button7_label, page11_button7_command_once,
    page11_button7_command_continue;
string page11_button8_label, page11_button8_command_once,
    page11_button8_command_continue;
string page11_button9_label, page11_button9_command_once,
    page11_button9_command_continue;
string page11_button10_label, page11_button10_command_once,
    page11_button10_command_continue;
string page11_button11_label, page11_button11_command_once,
    page11_button11_command_continue;
string page11_button12_label, page11_button12_command_once,
    page11_button12_command_continue;
string page11_button13_label, page11_button13_command_once,
    page11_button13_command_continue;
string page11_button14_label, page11_button14_command_once,
    page11_button14_command_continue;
string page11_button15_label, page11_button15_command_once,
    page11_button15_command_continue;
string page11_button16_label, page11_button16_command_once,
    page11_button16_command_continue;
string page11_button17_label, page11_button17_command_once,
    page11_button17_command_continue;
string page11_button18_label, page11_button18_command_once,
    page11_button18_command_continue;
string page11_button19_label, page11_button19_command_once,
    page11_button19_command_continue;
string page11_button20_label, page11_button20_command_once,
    page11_button20_command_continue;
string page11_button21_label, page11_button21_command_once,
    page11_button21_command_continue;
string page11_button22_label, page11_button22_command_once,
    page11_button22_command_continue;
string page11_button23_label, page11_button23_command_once,
    page11_button23_command_continue;
string page11_button24_label, page11_button24_command_once,
    page11_button24_command_continue;


string page12_button1_label, page12_button1_command_once,
    page12_button1_command_continue;
string page12_button2_label, page12_button2_command_once,
    page12_button2_command_continue;
string page12_button3_label, page12_button3_command_once,
    page12_button3_command_continue;
string page12_button4_label, page12_button4_command_once,
    page12_button4_command_continue;
string page12_button5_label, page12_button5_command_once,
    page12_button5_command_continue;
string page12_button6_label, page12_button6_command_once,
    page12_button6_command_continue;
string page12_button7_label, page12_button7_command_once,
    page12_button7_command_continue;
string page12_button8_label, page12_button8_command_once,
    page12_button8_command_continue;
string page12_button9_label, page12_button9_command_once,
    page12_button9_command_continue;
string page12_button10_label, page12_button10_command_once,
    page12_button10_command_continue;
string page12_button11_label, page12_button11_command_once,
    page12_button11_command_continue;
string page12_button12_label, page12_button12_command_once,
    page12_button12_command_continue;
string page12_button13_label, page12_button13_command_once,
    page12_button13_command_continue;
string page12_button14_label, page12_button14_command_once,
    page12_button14_command_continue;
string page12_button15_label, page12_button15_command_once,
    page12_button15_command_continue;
string page12_button16_label, page12_button16_command_once,
    page12_button16_command_continue;
string page12_button17_label, page12_button17_command_once,
    page12_button17_command_continue;
string page12_button18_label, page12_button18_command_once,
    page12_button18_command_continue;
string page12_button19_label, page12_button19_command_once,
    page12_button19_command_continue;
string page12_button20_label, page12_button20_command_once,
    page12_button20_command_continue;
string page12_button21_label, page12_button21_command_once,
    page12_button21_command_continue;
string page12_button22_label, page12_button22_command_once,
    page12_button22_command_continue;
string page12_button23_label, page12_button23_command_once,
    page12_button23_command_continue;
string page12_button24_label, page12_button24_command_once,
    page12_button24_command_continue;


XPLMCommandRef Page1_Button1LabelCmd = nullptr,
               Page1_Button1CommandOnceCmd = nullptr,
               Page1_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button2LabelCmd = nullptr,
               Page1_Button2CommandOnceCmd = nullptr,
               Page1_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button3LabelCmd = nullptr,
               Page1_Button3CommandOnceCmd = nullptr,
               Page1_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button4LabelCmd = nullptr,
               Page1_Button4CommandOnceCmd = nullptr,
               Page1_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button5LabelCmd = nullptr,
               Page1_Button5CommandOnceCmd = nullptr,
               Page1_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button6LabelCmd = nullptr,
               Page1_Button6CommandOnceCmd = nullptr,
               Page1_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button7LabelCmd = nullptr,
               Page1_Button7CommandOnceCmd = nullptr,
               Page1_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button8LabelCmd = nullptr,
               Page1_Button8CommandOnceCmd = nullptr,
               Page1_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button9LabelCmd = nullptr,
               Page1_Button9CommandOnceCmd = nullptr,
               Page1_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button10LabelCmd = nullptr,
               Page1_Button10CommandOnceCmd = nullptr,
               Page1_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button11LabelCmd = nullptr,
               Page1_Button11CommandOnceCmd = nullptr,
               Page1_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page1_Button12LabelCmd = nullptr,
               Page1_Button12CommandOnceCmd = nullptr,
               Page1_Button12CommandContinueCmd = nullptr;

XPLMCommandRef Page2_Button1LabelCmd = nullptr,
               Page2_Button1CommandOnceCmd = nullptr,
               Page2_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button2LabelCmd = nullptr,
               Page2_Button2CommandOnceCmd = nullptr,
               Page2_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button3LabelCmd = nullptr,
               Page2_Button3CommandOnceCmd = nullptr,
               Page2_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button4LabelCmd = nullptr,
               Page2_Button4CommandOnceCmd = nullptr,
               Page2_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button5LabelCmd = nullptr,
               Page2_Button5CommandOnceCmd = nullptr,
               Page2_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button6LabelCmd = nullptr,
               Page2_Button6CommandOnceCmd = nullptr,
               Page2_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button7LabelCmd = nullptr,
               Page2_Button7CommandOnceCmd = nullptr,
               Page2_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button8LabelCmd = nullptr,
               Page2_Button8CommandOnceCmd = nullptr,
               Page2_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button9LabelCmd = nullptr,
               Page2_Button9CommandOnceCmd = nullptr,
               Page2_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button10LabelCmd = nullptr,
               Page2_Button10CommandOnceCmd = nullptr,
               Page2_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button11LabelCmd = nullptr,
               Page2_Button11CommandOnceCmd = nullptr,
               Page2_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page2_Button12LabelCmd = nullptr,
               Page2_Button12CommandOnceCmd = nullptr,
               Page2_Button12CommandContinueCmd = nullptr;

XPLMCommandRef Page3_Button1LabelCmd = nullptr,
               Page3_Button1CommandOnceCmd = nullptr,
               Page3_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button2LabelCmd = nullptr,
               Page3_Button2CommandOnceCmd = nullptr,
               Page3_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button3LabelCmd = nullptr,
               Page3_Button3CommandOnceCmd = nullptr,
               Page3_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button4LabelCmd = nullptr,
               Page3_Button4CommandOnceCmd = nullptr,
               Page3_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button5LabelCmd = nullptr,
               Page3_Button5CommandOnceCmd = nullptr,
               Page3_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button6LabelCmd = nullptr,
               Page3_Button6CommandOnceCmd = nullptr,
               Page3_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button7LabelCmd = nullptr,
               Page3_Button7CommandOnceCmd = nullptr,
               Page3_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button8LabelCmd = nullptr,
               Page3_Button8CommandOnceCmd = nullptr,
               Page3_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button9LabelCmd = nullptr,
               Page3_Button9CommandOnceCmd = nullptr,
               Page3_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button10LabelCmd = nullptr,
               Page3_Button10CommandOnceCmd = nullptr,
               Page3_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button11LabelCmd = nullptr,
               Page3_Button11CommandOnceCmd = nullptr,
               Page3_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page3_Button12LabelCmd = nullptr,
               Page3_Button12CommandOnceCmd = nullptr,
               Page3_Button12CommandContinueCmd = nullptr;

XPLMCommandRef Page4_Button1LabelCmd = nullptr,
               Page4_Button1CommandOnceCmd = nullptr,
               Page4_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button2LabelCmd = nullptr,
               Page4_Button2CommandOnceCmd = nullptr,
               Page4_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button3LabelCmd = nullptr,
               Page4_Button3CommandOnceCmd = nullptr,
               Page4_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button4LabelCmd = nullptr,
               Page4_Button4CommandOnceCmd = nullptr,
               Page4_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button5LabelCmd = nullptr,
               Page4_Button5CommandOnceCmd = nullptr,
               Page4_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button6LabelCmd = nullptr,
               Page4_Button6CommandOnceCmd = nullptr,
               Page4_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button7LabelCmd = nullptr,
               Page4_Button7CommandOnceCmd = nullptr,
               Page4_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button8LabelCmd = nullptr,
               Page4_Button8CommandOnceCmd = nullptr,
               Page4_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button9LabelCmd = nullptr,
               Page4_Button9CommandOnceCmd = nullptr,
               Page4_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button10LabelCmd = nullptr,
               Page4_Button10CommandOnceCmd = nullptr,
               Page4_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button11LabelCmd = nullptr,
               Page4_Button11CommandOnceCmd = nullptr,
               Page4_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page4_Button12LabelCmd = nullptr,
               Page4_Button12CommandOnceCmd = nullptr,
               Page4_Button12CommandContinueCmd = nullptr;

XPLMCommandRef Page5_Button1LabelCmd = nullptr,
               Page5_Button1CommandOnceCmd = nullptr,
               Page5_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button2LabelCmd = nullptr,
               Page5_Button2CommandOnceCmd = nullptr,
               Page5_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button3LabelCmd = nullptr,
               Page5_Button3CommandOnceCmd = nullptr,
               Page5_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button4LabelCmd = nullptr,
               Page5_Button4CommandOnceCmd = nullptr,
               Page5_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button5LabelCmd = nullptr,
               Page5_Button5CommandOnceCmd = nullptr,
               Page5_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button6LabelCmd = nullptr,
               Page5_Button6CommandOnceCmd = nullptr,
               Page5_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button7LabelCmd = nullptr,
               Page5_Button7CommandOnceCmd = nullptr,
               Page5_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button8LabelCmd = nullptr,
               Page5_Button8CommandOnceCmd = nullptr,
               Page5_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button9LabelCmd = nullptr,
               Page5_Button9CommandOnceCmd = nullptr,
               Page5_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button10LabelCmd = nullptr,
               Page5_Button10CommandOnceCmd = nullptr,
               Page5_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button11LabelCmd = nullptr,
               Page5_Button11CommandOnceCmd = nullptr,
               Page5_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page5_Button12LabelCmd = nullptr,
               Page5_Button12CommandOnceCmd = nullptr,
               Page5_Button12CommandContinueCmd = nullptr;

XPLMCommandRef Page6_Button1LabelCmd = nullptr,
               Page6_Button1CommandOnceCmd = nullptr,
               Page6_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button2LabelCmd = nullptr,
               Page6_Button2CommandOnceCmd = nullptr,
               Page6_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button3LabelCmd = nullptr,
               Page6_Button3CommandOnceCmd = nullptr,
               Page6_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button4LabelCmd = nullptr,
               Page6_Button4CommandOnceCmd = nullptr,
               Page6_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button5LabelCmd = nullptr,
               Page6_Button5CommandOnceCmd = nullptr,
               Page6_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button6LabelCmd = nullptr,
               Page6_Button6CommandOnceCmd = nullptr,
               Page6_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button7LabelCmd = nullptr,
               Page6_Button7CommandOnceCmd = nullptr,
               Page6_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button8LabelCmd = nullptr,
               Page6_Button8CommandOnceCmd = nullptr,
               Page6_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button9LabelCmd = nullptr,
               Page6_Button9CommandOnceCmd = nullptr,
               Page6_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button10LabelCmd = nullptr,
               Page6_Button10CommandOnceCmd = nullptr,
               Page6_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button11LabelCmd = nullptr,
               Page6_Button11CommandOnceCmd = nullptr,
               Page6_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page6_Button12LabelCmd = nullptr,
               Page6_Button12CommandOnceCmd = nullptr,
               Page6_Button12CommandContinueCmd = nullptr;

XPLMCommandRef Page7_Button1LabelCmd = nullptr,
               Page7_Button1CommandOnceCmd = nullptr,
               Page7_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button2LabelCmd = nullptr,
               Page7_Button2CommandOnceCmd = nullptr,
               Page7_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button3LabelCmd = nullptr,
               Page7_Button3CommandOnceCmd = nullptr,
               Page7_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button4LabelCmd = nullptr,
               Page7_Button4CommandOnceCmd = nullptr,
               Page7_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button5LabelCmd = nullptr,
               Page7_Button5CommandOnceCmd = nullptr,
               Page7_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button6LabelCmd = nullptr,
               Page7_Button6CommandOnceCmd = nullptr,
               Page7_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button7LabelCmd = nullptr,
               Page7_Button7CommandOnceCmd = nullptr,
               Page7_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button8LabelCmd = nullptr,
               Page7_Button8CommandOnceCmd = nullptr,
               Page7_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button9LabelCmd = nullptr,
               Page7_Button9CommandOnceCmd = nullptr,
               Page7_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button10LabelCmd = nullptr,
               Page7_Button10CommandOnceCmd = nullptr,
               Page7_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button11LabelCmd = nullptr,
               Page7_Button11CommandOnceCmd = nullptr,
               Page7_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page7_Button12LabelCmd = nullptr,
               Page7_Button12CommandOnceCmd = nullptr,
               Page7_Button12CommandContinueCmd = nullptr;

XPLMCommandRef Page8_Button1LabelCmd = nullptr,
               Page8_Button1CommandOnceCmd = nullptr,
               Page8_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button2LabelCmd = nullptr,
               Page8_Button2CommandOnceCmd = nullptr,
               Page8_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button3LabelCmd = nullptr,
               Page8_Button3CommandOnceCmd = nullptr,
               Page8_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button4LabelCmd = nullptr,
               Page8_Button4CommandOnceCmd = nullptr,
               Page8_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button5LabelCmd = nullptr,
               Page8_Button5CommandOnceCmd = nullptr,
               Page8_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button6LabelCmd = nullptr,
               Page8_Button6CommandOnceCmd = nullptr,
               Page8_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button7LabelCmd = nullptr,
               Page8_Button7CommandOnceCmd = nullptr,
               Page8_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button8LabelCmd = nullptr,
               Page8_Button8CommandOnceCmd = nullptr,
               Page8_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button9LabelCmd = nullptr,
               Page8_Button9CommandOnceCmd = nullptr,
               Page8_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button10LabelCmd = nullptr,
               Page8_Button10CommandOnceCmd = nullptr,
               Page8_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button11LabelCmd = nullptr,
               Page8_Button11CommandOnceCmd = nullptr,
               Page8_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page8_Button12LabelCmd = nullptr,
               Page8_Button12CommandOnceCmd = nullptr,
               Page8_Button12CommandContinueCmd = nullptr;


XPLMCommandRef Page9_Button1LabelCmd = nullptr,
               Page9_Button1CommandOnceCmd = nullptr,
               Page9_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button2LabelCmd = nullptr,
               Page9_Button2CommandOnceCmd = nullptr,
               Page9_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button3LabelCmd = nullptr,
               Page9_Button3CommandOnceCmd = nullptr,
               Page9_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button4LabelCmd = nullptr,
               Page9_Button4CommandOnceCmd = nullptr,
               Page9_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button5LabelCmd = nullptr,
               Page9_Button5CommandOnceCmd = nullptr,
               Page9_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button6LabelCmd = nullptr,
               Page9_Button6CommandOnceCmd = nullptr,
               Page9_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button7LabelCmd = nullptr,
               Page9_Button7CommandOnceCmd = nullptr,
               Page9_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button8LabelCmd = nullptr,
               Page9_Button8CommandOnceCmd = nullptr,
               Page9_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button9LabelCmd = nullptr,
               Page9_Button9CommandOnceCmd = nullptr,
               Page9_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button10LabelCmd = nullptr,
               Page9_Button10CommandOnceCmd = nullptr,
               Page9_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button11LabelCmd = nullptr,
               Page9_Button11CommandOnceCmd = nullptr,
               Page9_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button12LabelCmd = nullptr,
               Page9_Button12CommandOnceCmd = nullptr,
               Page9_Button12CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button13LabelCmd = nullptr,
               Page9_Button13CommandOnceCmd = nullptr,
               Page9_Button13CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button14LabelCmd = nullptr,
               Page9_Button14CommandOnceCmd = nullptr,
               Page9_Button14CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button15LabelCmd = nullptr,
               Page9_Button15CommandOnceCmd = nullptr,
               Page9_Button15CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button16LabelCmd = nullptr,
               Page9_Button16CommandOnceCmd = nullptr,
               Page9_Button16CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button17LabelCmd = nullptr,
               Page9_Button17CommandOnceCmd = nullptr,
               Page9_Button17CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button18LabelCmd = nullptr,
               Page9_Button18CommandOnceCmd = nullptr,
               Page9_Button18CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button19LabelCmd = nullptr,
               Page9_Button19CommandOnceCmd = nullptr,
               Page9_Button19CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button20LabelCmd = nullptr,
               Page9_Button20CommandOnceCmd = nullptr,
               Page9_Button20CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button21LabelCmd = nullptr,
               Page9_Button21CommandOnceCmd = nullptr,
               Page9_Button21CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button22LabelCmd = nullptr,
               Page9_Button22CommandOnceCmd = nullptr,
               Page9_Button22CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button23LabelCmd = nullptr,
               Page9_Button23CommandOnceCmd = nullptr,
               Page9_Button23CommandContinueCmd = nullptr;
XPLMCommandRef Page9_Button24LabelCmd = nullptr,
               Page9_Button24CommandOnceCmd = nullptr,
               Page9_Button24CommandContinueCmd = nullptr;


XPLMCommandRef Page10_Button1LabelCmd = nullptr,
               Page10_Button1CommandOnceCmd = nullptr,
               Page10_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button2LabelCmd = nullptr,
               Page10_Button2CommandOnceCmd = nullptr,
               Page10_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button3LabelCmd = nullptr,
               Page10_Button3CommandOnceCmd = nullptr,
               Page10_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button4LabelCmd = nullptr,
               Page10_Button4CommandOnceCmd = nullptr,
               Page10_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button5LabelCmd = nullptr,
               Page10_Button5CommandOnceCmd = nullptr,
               Page10_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button6LabelCmd = nullptr,
               Page10_Button6CommandOnceCmd = nullptr,
               Page10_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button7LabelCmd = nullptr,
               Page10_Button7CommandOnceCmd = nullptr,
               Page10_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button8LabelCmd = nullptr,
               Page10_Button8CommandOnceCmd = nullptr,
               Page10_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button9LabelCmd = nullptr,
               Page10_Button9CommandOnceCmd = nullptr,
               Page10_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button10LabelCmd = nullptr,
               Page10_Button10CommandOnceCmd = nullptr,
               Page10_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button11LabelCmd = nullptr,
               Page10_Button11CommandOnceCmd = nullptr,
               Page10_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button12LabelCmd = nullptr,
               Page10_Button12CommandOnceCmd = nullptr,
               Page10_Button12CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button13LabelCmd = nullptr,
               Page10_Button13CommandOnceCmd = nullptr,
               Page10_Button13CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button14LabelCmd = nullptr,
               Page10_Button14CommandOnceCmd = nullptr,
               Page10_Button14CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button15LabelCmd = nullptr,
               Page10_Button15CommandOnceCmd = nullptr,
               Page10_Button15CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button16LabelCmd = nullptr,
               Page10_Button16CommandOnceCmd = nullptr,
               Page10_Button16CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button17LabelCmd = nullptr,
               Page10_Button17CommandOnceCmd = nullptr,
               Page10_Button17CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button18LabelCmd = nullptr,
               Page10_Button18CommandOnceCmd = nullptr,
               Page10_Button18CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button19LabelCmd = nullptr,
               Page10_Button19CommandOnceCmd = nullptr,
               Page10_Button19CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button20LabelCmd = nullptr,
               Page10_Button20CommandOnceCmd = nullptr,
               Page10_Button20CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button21LabelCmd = nullptr,
               Page10_Button21CommandOnceCmd = nullptr,
               Page10_Button21CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button22LabelCmd = nullptr,
               Page10_Button22CommandOnceCmd = nullptr,
               Page10_Button22CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button23LabelCmd = nullptr,
               Page10_Button23CommandOnceCmd = nullptr,
               Page10_Button23CommandContinueCmd = nullptr;
XPLMCommandRef Page10_Button24LabelCmd = nullptr,
               Page10_Button24CommandOnceCmd = nullptr,
               Page10_Button24CommandContinueCmd = nullptr;


XPLMCommandRef Page11_Button1LabelCmd = nullptr,
               Page11_Button1CommandOnceCmd = nullptr,
               Page11_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button2LabelCmd = nullptr,
               Page11_Button2CommandOnceCmd = nullptr,
               Page11_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button3LabelCmd = nullptr,
               Page11_Button3CommandOnceCmd = nullptr,
               Page11_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button4LabelCmd = nullptr,
               Page11_Button4CommandOnceCmd = nullptr,
               Page11_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button5LabelCmd = nullptr,
               Page11_Button5CommandOnceCmd = nullptr,
               Page11_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button6LabelCmd = nullptr,
               Page11_Button6CommandOnceCmd = nullptr,
               Page11_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button7LabelCmd = nullptr,
               Page11_Button7CommandOnceCmd = nullptr,
               Page11_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button8LabelCmd = nullptr,
               Page11_Button8CommandOnceCmd = nullptr,
               Page11_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button9LabelCmd = nullptr,
               Page11_Button9CommandOnceCmd = nullptr,
               Page11_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button10LabelCmd = nullptr,
               Page11_Button10CommandOnceCmd = nullptr,
               Page11_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button11LabelCmd = nullptr,
               Page11_Button11CommandOnceCmd = nullptr,
               Page11_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button12LabelCmd = nullptr,
               Page11_Button12CommandOnceCmd = nullptr,
               Page11_Button12CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button13LabelCmd = nullptr,
               Page11_Button13CommandOnceCmd = nullptr,
               Page11_Button13CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button14LabelCmd = nullptr,
               Page11_Button14CommandOnceCmd = nullptr,
               Page11_Button14CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button15LabelCmd = nullptr,
               Page11_Button15CommandOnceCmd = nullptr,
               Page11_Button15CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button16LabelCmd = nullptr,
               Page11_Button16CommandOnceCmd = nullptr,
               Page11_Button16CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button17LabelCmd = nullptr,
               Page11_Button17CommandOnceCmd = nullptr,
               Page11_Button17CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button18LabelCmd = nullptr,
               Page11_Button18CommandOnceCmd = nullptr,
               Page11_Button18CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button19LabelCmd = nullptr,
               Page11_Button19CommandOnceCmd = nullptr,
               Page11_Button19CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button20LabelCmd = nullptr,
               Page11_Button20CommandOnceCmd = nullptr,
               Page11_Button20CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button21LabelCmd = nullptr,
               Page11_Button21CommandOnceCmd = nullptr,
               Page11_Button21CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button22LabelCmd = nullptr,
               Page11_Button22CommandOnceCmd = nullptr,
               Page11_Button22CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button23LabelCmd = nullptr,
               Page11_Button23CommandOnceCmd = nullptr,
               Page11_Button23CommandContinueCmd = nullptr;
XPLMCommandRef Page11_Button24LabelCmd = nullptr,
               Page11_Button24CommandOnceCmd = nullptr,
               Page11_Button24CommandContinueCmd = nullptr;


XPLMCommandRef Page12_Button1LabelCmd = nullptr,
               Page12_Button1CommandOnceCmd = nullptr,
               Page12_Button1CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button2LabelCmd = nullptr,
               Page12_Button2CommandOnceCmd = nullptr,
               Page12_Button2CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button3LabelCmd = nullptr,
               Page12_Button3CommandOnceCmd = nullptr,
               Page12_Button3CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button4LabelCmd = nullptr,
               Page12_Button4CommandOnceCmd = nullptr,
               Page12_Button4CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button5LabelCmd = nullptr,
               Page12_Button5CommandOnceCmd = nullptr,
               Page12_Button5CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button6LabelCmd = nullptr,
               Page12_Button6CommandOnceCmd = nullptr,
               Page12_Button6CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button7LabelCmd = nullptr,
               Page12_Button7CommandOnceCmd = nullptr,
               Page12_Button7CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button8LabelCmd = nullptr,
               Page12_Button8CommandOnceCmd = nullptr,
               Page12_Button8CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button9LabelCmd = nullptr,
               Page12_Button9CommandOnceCmd = nullptr,
               Page12_Button9CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button10LabelCmd = nullptr,
               Page12_Button10CommandOnceCmd = nullptr,
               Page12_Button10CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button11LabelCmd = nullptr,
               Page12_Button11CommandOnceCmd = nullptr,
               Page12_Button11CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button12LabelCmd = nullptr,
               Page12_Button12CommandOnceCmd = nullptr,
               Page12_Button12CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button13LabelCmd = nullptr,
               Page12_Button13CommandOnceCmd = nullptr,
               Page12_Button13CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button14LabelCmd = nullptr,
               Page12_Button14CommandOnceCmd = nullptr,
               Page12_Button14CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button15LabelCmd = nullptr,
               Page12_Button15CommandOnceCmd = nullptr,
               Page12_Button15CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button16LabelCmd = nullptr,
               Page12_Button16CommandOnceCmd = nullptr,
               Page12_Button16CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button17LabelCmd = nullptr,
               Page12_Button17CommandOnceCmd = nullptr,
               Page12_Button17CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button18LabelCmd = nullptr,
               Page12_Button18CommandOnceCmd = nullptr,
               Page12_Button18CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button19LabelCmd = nullptr,
               Page12_Button19CommandOnceCmd = nullptr,
               Page12_Button19CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button20LabelCmd = nullptr,
               Page12_Button20CommandOnceCmd = nullptr,
               Page12_Button20CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button21LabelCmd = nullptr,
               Page12_Button21CommandOnceCmd = nullptr,
               Page12_Button21CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button22LabelCmd = nullptr,
               Page12_Button22CommandOnceCmd = nullptr,
               Page12_Button22CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button23LabelCmd = nullptr,
               Page12_Button23CommandOnceCmd = nullptr,
               Page12_Button23CommandContinueCmd = nullptr;
XPLMCommandRef Page12_Button24LabelCmd = nullptr,
               Page12_Button24CommandOnceCmd = nullptr,
               Page12_Button24CommandContinueCmd = nullptr;


XPLMCommandRef g430n1_cdi_cmd = nullptr, g430n1_chapter_dn_cmd = nullptr,
               g430n1_chapter_up_cmd = nullptr, g430n1_clr_cmd = nullptr;
XPLMCommandRef g430n1_coarse_down_cmd = nullptr, g430n1_coarse_up_cmd = nullptr,
               g430n1_com_ff_cmd = nullptr, g430n1_cursor_cmd = nullptr;
XPLMCommandRef g430n1_cvol_cmd = nullptr, g430n1_direct_cmd = nullptr,
               g430n1_ent_cmd = nullptr, g430n1_fine_down_cmd = nullptr;
XPLMCommandRef g430n1_fine_up_cmd = nullptr, g430n1_fpl_cmd = nullptr,
               g430n1_menu_cmd = nullptr, g430n1_msg_cmd = nullptr;
XPLMCommandRef g430n1_nav_com_tog_cmd = nullptr, g430n1_nav_ff_cmd = nullptr,
               g430n1_obs_cmd = nullptr, g430n1_page_dn_cmd = nullptr;
XPLMCommandRef g430n1_page_up_cmd = nullptr, g430n1_popout_cmd = nullptr,
               g430n1_popup_cmd = nullptr, g430n1_proc_cmd = nullptr;
XPLMCommandRef g430n1_vnav_cmd = nullptr, g430n1_vvol_cmd = nullptr,
               g430n1_zoom_in_cmd = nullptr, g430n1_zoom_out_cmd = nullptr;

XPLMCommandRef g430n2_cdi_cmd = nullptr, g430n2_chapter_dn_cmd = nullptr,
               g430n2_chapter_up_cmd = nullptr, g430n2_clr_cmd = nullptr;
XPLMCommandRef g430n2_coarse_down_cmd = nullptr, g430n2_coarse_up_cmd = nullptr,
               g430n2_com_ff_cmd = nullptr, g430n2_cursor_cmd = nullptr;
XPLMCommandRef g430n2_cvol_cmd = nullptr, g430n2_direct_cmd = nullptr,
               g430n2_ent_cmd = nullptr, g430n2_fine_down_cmd = nullptr;
XPLMCommandRef g430n2_fine_up_cmd = nullptr, g430n2_fpl_cmd = nullptr,
               g430n2_menu_cmd = nullptr, g430n2_msg_cmd = nullptr;
XPLMCommandRef g430n2_nav_com_tog_cmd = nullptr, g430n2_nav_ff_cmd = nullptr,
               g430n2_obs_cmd = nullptr, g430n2_page_dn_cmd = nullptr;
XPLMCommandRef g430n2_page_up_cmd = nullptr, g430n2_popout_cmd = nullptr,
               g430n2_popup_cmd = nullptr, g430n2_proc_cmd = nullptr;
XPLMCommandRef g430n2_vnav_cmd = nullptr, g430n2_vvol_cmd = nullptr,
               g430n2_zoom_in_cmd = nullptr, g430n2_zoom_out_cmd = nullptr;

int Page1_Button1ContinueMode = 0, Page1_Button2ContinueMode = 0,
    Page1_Button3ContinueMode = 0;
int Page1_Button4ContinueMode = 0, Page1_Button5ContinueMode = 0,
    Page1_Button6ContinueMode = 0;
int Page1_Button7ContinueMode = 0, Page1_Button8ContinueMode = 0,
    Page1_Button9ContinueMode = 0;
int Page1_Button10ContinueMode = 0, Page1_Button11ContinueMode = 0,
    Page1_Button12ContinueMode = 0;

int Page2_Button1ContinueMode = 0, Page2_Button2ContinueMode = 0,
    Page2_Button3ContinueMode = 0;
int Page2_Button4ContinueMode = 0, Page2_Button5ContinueMode = 0,
    Page2_Button6ContinueMode = 0;
int Page2_Button7ContinueMode = 0, Page2_Button8ContinueMode = 0,
    Page2_Button9ContinueMode = 0;
int Page2_Button10ContinueMode = 0, Page2_Button11ContinueMode = 0,
    Page2_Button12ContinueMode = 0;

int Page3_Button1ContinueMode = 0, Page3_Button2ContinueMode = 0,
    Page3_Button3ContinueMode = 0;
int Page3_Button4ContinueMode = 0, Page3_Button5ContinueMode = 0,
    Page3_Button6ContinueMode = 0;
int Page3_Button7ContinueMode = 0, Page3_Button8ContinueMode = 0,
    Page3_Button9ContinueMode = 0;
int Page3_Button10ContinueMode = 0, Page3_Button11ContinueMode = 0,
    Page3_Button12ContinueMode = 0;

int Page4_Button1ContinueMode = 0, Page4_Button2ContinueMode = 0,
    Page4_Button3ContinueMode = 0;
int Page4_Button4ContinueMode = 0, Page4_Button5ContinueMode = 0,
    Page4_Button6ContinueMode = 0;
int Page4_Button7ContinueMode = 0, Page4_Button8ContinueMode = 0,
    Page4_Button9ContinueMode = 0;
int Page4_Button10ContinueMode = 0, Page4_Button11ContinueMode = 0,
    Page4_Button12ContinueMode = 0;

int Page5_Button1ContinueMode = 0, Page5_Button2ContinueMode = 0,
    Page5_Button3ContinueMode = 0;
int Page5_Button4ContinueMode = 0, Page5_Button5ContinueMode = 0,
    Page5_Button6ContinueMode = 0;
int Page5_Button7ContinueMode = 0, Page5_Button8ContinueMode = 0,
    Page5_Button9ContinueMode = 0;
int Page5_Button10ContinueMode = 0, Page5_Button11ContinueMode = 0,
    Page5_Button12ContinueMode = 0;

int Page6_Button1ContinueMode = 0, Page6_Button2ContinueMode = 0,
    Page6_Button3ContinueMode = 0;
int Page6_Button4ContinueMode = 0, Page6_Button5ContinueMode = 0,
    Page6_Button6ContinueMode = 0;
int Page6_Button7ContinueMode = 0, Page6_Button8ContinueMode = 0,
    Page6_Button9ContinueMode = 0;
int Page6_Button10ContinueMode = 0, Page6_Button11ContinueMode = 0,
    Page6_Button12ContinueMode = 0;

int Page7_Button1ContinueMode = 0, Page7_Button2ContinueMode = 0,
    Page7_Button3ContinueMode = 0;
int Page7_Button4ContinueMode = 0, Page7_Button5ContinueMode = 0,
    Page7_Button6ContinueMode = 0;
int Page7_Button7ContinueMode = 0, Page7_Button8ContinueMode = 0,
    Page7_Button9ContinueMode = 0;
int Page7_Button10ContinueMode = 0, Page7_Button11ContinueMode = 0,
    Page7_Button12ContinueMode = 0;

int Page8_Button1ContinueMode = 0, Page8_Button2ContinueMode = 0,
    Page8_Button3ContinueMode = 0;
int Page8_Button4ContinueMode = 0, Page8_Button5ContinueMode = 0,
    Page8_Button6ContinueMode = 0;
int Page8_Button7ContinueMode = 0, Page8_Button8ContinueMode = 0,
    Page8_Button9ContinueMode = 0;
int Page8_Button10ContinueMode = 0, Page8_Button11ContinueMode = 0,
    Page8_Button12ContinueMode = 0;


int Page9_Button1ContinueMode = 0, Page9_Button2ContinueMode = 0;
int Page9_Button3ContinueMode = 0, Page9_Button4ContinueMode = 0;
int Page9_Button5ContinueMode = 0, Page9_Button6ContinueMode = 0;
int Page9_Button7ContinueMode = 0, Page9_Button8ContinueMode = 0;
int Page9_Button9ContinueMode = 0, Page9_Button10ContinueMode = 0;
int Page9_Button11ContinueMode = 0, Page9_Button12ContinueMode = 0;
int Page9_Button13ContinueMode = 0, Page9_Button14ContinueMode = 0;
int Page9_Button15ContinueMode = 0, Page9_Button16ContinueMode = 0;
int Page9_Button17ContinueMode = 0, Page9_Button18ContinueMode = 0;
int Page9_Button19ContinueMode = 0, Page9_Button20ContinueMode = 0;
int Page9_Button21ContinueMode = 0, Page9_Button22ContinueMode = 0;
int Page9_Button23ContinueMode = 0, Page9_Button24ContinueMode = 0;


int Page10_Button1ContinueMode = 0, Page10_Button2ContinueMode = 0;
int Page10_Button3ContinueMode = 0, Page10_Button4ContinueMode = 0;
int Page10_Button5ContinueMode = 0, Page10_Button6ContinueMode = 0;
int Page10_Button7ContinueMode = 0, Page10_Button8ContinueMode = 0;
int Page10_Button9ContinueMode = 0, Page10_Button10ContinueMode = 0;
int Page10_Button11ContinueMode = 0, Page10_Button12ContinueMode = 0;
int Page10_Button13ContinueMode = 0, Page10_Button14ContinueMode = 0;
int Page10_Button15ContinueMode = 0, Page10_Button16ContinueMode = 0;
int Page10_Button17ContinueMode = 0, Page10_Button18ContinueMode = 0;
int Page10_Button19ContinueMode = 0, Page10_Button20ContinueMode = 0;
int Page10_Button21ContinueMode = 0, Page10_Button22ContinueMode = 0;
int Page10_Button23ContinueMode = 0, Page10_Button24ContinueMode = 0;


int Page11_Button1ContinueMode = 0, Page11_Button2ContinueMode = 0;
int Page11_Button3ContinueMode = 0, Page11_Button4ContinueMode = 0;
int Page11_Button5ContinueMode = 0, Page11_Button6ContinueMode = 0;
int Page11_Button7ContinueMode = 0, Page11_Button8ContinueMode = 0;
int Page11_Button9ContinueMode = 0, Page11_Button10ContinueMode = 0;
int Page11_Button11ContinueMode = 0, Page11_Button12ContinueMode = 0;
int Page11_Button13ContinueMode = 0, Page11_Button14ContinueMode = 0;
int Page11_Button15ContinueMode = 0, Page11_Button16ContinueMode = 0;
int Page11_Button17ContinueMode = 0, Page11_Button18ContinueMode = 0;
int Page11_Button19ContinueMode = 0, Page11_Button20ContinueMode = 0;
int Page11_Button21ContinueMode = 0, Page11_Button22ContinueMode = 0;
int Page11_Button23ContinueMode = 0, Page11_Button24ContinueMode = 0;


int Page12_Button1ContinueMode = 0, Page12_Button2ContinueMode = 0;
int Page12_Button3ContinueMode = 0, Page12_Button4ContinueMode = 0;
int Page12_Button5ContinueMode = 0, Page12_Button6ContinueMode = 0;
int Page12_Button7ContinueMode = 0, Page12_Button8ContinueMode = 0;
int Page12_Button9ContinueMode = 0, Page12_Button10ContinueMode = 0;
int Page12_Button11ContinueMode = 0, Page12_Button12ContinueMode = 0;
int Page12_Button13ContinueMode = 0, Page12_Button14ContinueMode = 0;
int Page12_Button15ContinueMode = 0, Page12_Button16ContinueMode = 0;
int Page12_Button17ContinueMode = 0, Page12_Button18ContinueMode = 0;
int Page12_Button19ContinueMode = 0, Page12_Button20ContinueMode = 0;
int Page12_Button21ContinueMode = 0, Page12_Button22ContinueMode = 0;
int Page12_Button23ContinueMode = 0, Page12_Button24ContinueMode = 0;


int Xbtn2cmd_menu_container_idx;  // The index of our menu item in the Plugins
                                  // menu
XPLMMenuID
    Xbtn2cmd_menu_id;  // The menu container we'll append all our menu items to
void Xbtn2cmdmenu_handler(void *, void *);

void Xbtn2hide_window();

int page1_mouse_down[12] = {};
int page2_mouse_down[12] = {};
int page3_mouse_down[12] = {};
int page4_mouse_down[12] = {};
int page5_mouse_down[12] = {};
int page6_mouse_down[12] = {};
int page7_mouse_down[12] = {};
int page8_mouse_down[12] = {};
int page9_mouse_down[12] = {};
int page10_mouse_down[12] = {};
int page11_mouse_down[12] = {};
int page12_mouse_down[12] = {};

int mouse_down[24] = {};

int mouse_down_hide = 0;
int mouse_down_reload = 0;
int mouse_down_edit = 0;
int mouse_down_ctrl_c = 0;

int mouse_down_page1 = 0;
int mouse_down_page2 = 0;
int mouse_down_page3 = 0;
int mouse_down_page4 = 0;
int mouse_down_page5 = 0;
int mouse_down_page6 = 0;
int mouse_down_page7 = 0;
int mouse_down_page8 = 0;
int mouse_down_page9 = 0;
int mouse_down_page10 = 0;
int mouse_down_page11 = 0;
int mouse_down_page12 = 0;
int mouse_down_page13 = 0;
int mouse_down_page14 = 0;

int mouse_down_radios = 0;
int mouse_down_g430n1 = 0;
int mouse_down_g430n2 = 0;


int number0_mouse_down = 0, number1_mouse_down = 0, number2_mouse_down = 0,
    number3_mouse_down = 0;
int number4_mouse_down = 0, number5_mouse_down = 0, number6_mouse_down = 0,
    number7_mouse_down = 0;
int number8_mouse_down = 0, number9_mouse_down = 0, clear_mouse_down = 0;
int com1a_mouse_down = 0, com2a_mouse_down = 0, nav1a_mouse_down = 0,
    nav2a_mouse_down = 0;
int com1s_mouse_down = 0, com2s_mouse_down = 0, nav1s_mouse_down = 0,
    nav2s_mouse_down = 0;

int adf1a_mouse_down = 0, adf2a_mouse_down = 0;
int adf1s_mouse_down = 0, adf2s_mouse_down = 0;

int number_mouse_down_value = 0;
int number_position = 0;

int g_430n1_com_ff_mouse_down = 0, g_430n1_nav_ff_mouse_down = 0,
    g_430n1_fine_down_mouse_down = 0, g_430n1_fine_up_mouse_down = 0;
int g_430n1_coarse_down_mouse_down = 0, g_430n1_coarse_up_mouse_down = 0,
    g_430n1_nav_com_tog_mouse_down = 0, g_430n1_cdi_mouse_down = 0;
int g_430n1_obs_mouse_down = 0, g_430n1_msg_mouse_down = 0,
    g_430n1_fpl_mouse_down = 0, g_430n1_vnav_mouse_down = 0,
    g_430n1_proc_mouse_down = 0;
int g_430n1_zoom_in_mouse_down = 0, g_430n1_zoom_out_mouse_down = 0,
    g_430n1_direct_mouse_down = 0, g_430n1_menu_mouse_down = 0,
    g_430n1_clr_mouse_down = 0;
int g_430n1_ent_mouse_down = 0, g_430n1_cursor_mouse_down = 0;
int g_430n1_page_dn_mouse_down = 0, g_430n1_page_up_mouse_down = 0,
    g_430n1_chapter_dn_mouse_down = 0, g_430n1_chapter_up_mouse_down = 0;

int g_430n2_com_ff_mouse_down = 0, g_430n2_nav_ff_mouse_down = 0,
    g_430n2_fine_down_mouse_down = 0, g_430n2_fine_up_mouse_down = 0;
int g_430n2_coarse_down_mouse_down = 0, g_430n2_coarse_up_mouse_down = 0,
    g_430n2_nav_com_tog_mouse_down = 0, g_430n2_cdi_mouse_down = 0;
int g_430n2_obs_mouse_down = 0, g_430n2_msg_mouse_down = 0,
    g_430n2_fpl_mouse_down = 0, g_430n2_vnav_mouse_down = 0,
    g_430n2_proc_mouse_down = 0;
int g_430n2_zoom_in_mouse_down = 0, g_430n2_zoom_out_mouse_down = 0,
    g_430n2_direct_mouse_down = 0, g_430n2_menu_mouse_down = 0,
    g_430n2_clr_mouse_down = 0;
int g_430n2_ent_mouse_down = 0, g_430n2_cursor_mouse_down = 0;
int g_430n2_page_dn_mouse_down = 0, g_430n2_page_up_mouse_down = 0,
    g_430n2_chapter_dn_mouse_down = 0, g_430n2_chapter_up_mouse_down = 0;

int page_number = 1;

int first_time = 0;

XPWidgetID Xbtn2cmdEditWidget = nullptr;

static void CreateXbtn2cmdEditWidget(int xx, int yy, int ww, int hh);

void populate_edit_window();
void update_current_button();
void write_ini_file_from_array();
void process_find_xplane_radios_commands();

string search_current_page_label;
string search_current_page_button_label;
string search_current_page_button_command_once;
string search_current_page_button_command_continue;

string search_current_page_button_once_label;
string search_current_page_button_continue_label;

int current_line_number = 0;
int current_page_label_line_number = 0;
int current_page_button_label_line_number = 0;
int current_page_button_command_once_line_number = 0;
int current_page_button_command_continue_line_number = 0;

int current_page_label_line_length = 0;
int current_page_button_label_line_length = 0;
int current_page_button_command_once_line_length = 0;
int current_page_button_command_continue_line_length = 0;

int current_page_label_write_start_position = 0;
int current_page_button_label_write_start_position = 0;
int current_page_button_command_once_write_start_position = 0;
int current_page_button_command_continue_write_start_position = 0;

string current_page_label_line;
string current_page_button_label_line;
string current_page_button_command_once_line;
string current_page_button_command_continue_line;

string updated_page_label_line;
string updated_page_button_label_line;
string updated_page_button_command_once_line;
string updated_page_button_command_continue_line;

string current_page_label;
string current_page_button_label;
string current_page_button_command_once;
string current_page_button_command_continue;

string xbtn2cmdini_path_name;

static int Xbtn2cmdEditHandler(XPWidgetMessage inMessage, XPWidgetID inWidget,
                               intptr_t inParam1, intptr_t inParam2);

static XPLMWindowID xbtn2cmd_edit_window;

XPWidgetID CurrentPageLabelLineTextBoxWidget = nullptr;
XPWidgetID CopyPageLabelLineTextBoxButtonWidget = nullptr;
XPWidgetID PastePageLabelLineTextBoxButtonWidget = nullptr;

XPWidgetID CurrentPageButtonLabelLineTextBoxWidget = nullptr;
XPWidgetID CopyPageButtonLabelLineTextBoxButtonWidget = nullptr;
XPWidgetID PastePageButtonLabelLineTextBoxButtonWidget = nullptr;

XPWidgetID CurrentPageButtonCommandOnceLineTextBoxWidget = nullptr;
XPWidgetID CopyPageButtonCommandOnceLineTextBoxButtonWidget = nullptr;
XPWidgetID PastePageButtonCommandOnceLineTextBoxButtonWidget = nullptr;

XPWidgetID CurrentPageButtonCommandContinueLineTextBoxWidget = nullptr;
XPWidgetID CopyPageButtonCommandContinueLineTextBoxButtonWidget = nullptr;
XPWidgetID PastePageButtonCommandContinueLineTextBoxButtonWidget = nullptr;

XPWidgetID WriteIniFileButtonWidget = nullptr;
XPWidgetID UpdatePageLabelButtonWidget = nullptr;

XPWidgetID Xbtn2cmdEditPageButtonLabelTextBoxWidget = nullptr;

int edit_mode = 0;
int update_widget = 0;

vector<string> xbtn2cmdiniVector;

int vector_size;

bool XSBGetTextFromClipboard(std::string &outText);
bool XSBSetTextToClipboard(const std::string &inText);

int paste_button_pushed = 0;
int copy_button_pushed = 0;

int radio_freq = 0;
int radio_freq1 = 0;
int radio_freq2 = 0;
int radio_freq3 = 0;
int radio_freq4 = 0;
int radio_freq5 = 0;
int radio_freq6 = 0;

int radio_com1_actv_freq = 0;
int radio_com2_actv_freq = 0;
int radio_nav1_actv_freq = 0;
int radio_nav2_actv_freq = 0;
int radio_adf1_actv_freq = 0;
int radio_adf2_actv_freq = 0;

int radio_com1_stby_freq = 0;
int radio_com2_stby_freq = 0;
int radio_nav1_stby_freq = 0;
int radio_nav2_stby_freq = 0;
int radio_adf1_stby_freq = 0;
int radio_adf2_stby_freq = 0;

XPLMDataRef XPLM_radio_com1_actv_freq;
XPLMDataRef XPLM_radio_com2_actv_freq;
XPLMDataRef XPLM_radio_nav1_actv_freq;
XPLMDataRef XPLM_radio_nav2_actv_freq;
XPLMDataRef XPLM_radio_adf1_actv_freq;
XPLMDataRef XPLM_radio_adf2_actv_freq;

XPLMDataRef XPLM_radio_com1_stby_freq;
XPLMDataRef XPLM_radio_com2_stby_freq;
XPLMDataRef XPLM_radio_nav1_stby_freq;
XPLMDataRef XPLM_radio_nav2_stby_freq;
XPLMDataRef XPLM_radio_adf1_stby_freq;
XPLMDataRef XPLM_radio_adf2_stby_freq;

XPLMDataRef PageNumberDataRef = nullptr;
XPLMDataRef ButtonNumberDataRef = nullptr;

int PageNumberValue;
int ButtonNumberValue;

int GetPageNumberDataRefCB(void *inRefcon);
void SetPageNumberDataRefCB(void *inRefcon, int inValue);

int GetButtonNumberDataRefCB(void *inRefcon);
void SetButtonNumberDataRefCB(void *inRefcon, int inValue);

static bool toggle_gui();
int is_popped_out = 0;
int was_popped_out = 0;
int command_pressed = 0;

int left1 = 0, top1 = 0, right1 = 0, bottom1 = 0;

PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
  XPLMDebugString("Xbtn2cmd: ver " VERSION_NUMBER "\n");
  strcpy(outName, "Xbtn2cmd: ver " VERSION_NUMBER);
  strcpy(outSig, "sparker.example.xbtn2cmdplugin");
  strcpy(outDesc,
         "A plug-in that demonstrates a window of buttons in VR than "
         "can be mapped to commands.");

  XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);
  XPLMEnableFeature("XPLM_USE_NATIVE_WIDGET_WINDOWS", 1);

  // NOTE: We do *not* create the window here, because our plugin initialization
  //       happens *before* VR gets initialized. So, the sim will *always*
  //       report
  //       that VR is disabled at this point.
  //       Instead, we'll wait for the first "scenery loaded" message to create
  //       our window. (See XPluginReceiveMessage() below.)

  g_vr_dref = XPLMFindDataRef("sim/graphics/VR/enabled");
  xb2cvr_g_FPS = XPLMFindDataRef("sim/operation/misc/frame_rate_period");

  XPLMGetVersions(&VersionXP, &VersionSDK, &HostID);

  // Create our menu

  Xbtn2cmd_menu_container_idx =
      XPLMAppendMenuItem(XPLMFindPluginsMenu(), "Xbtn2cmd", nullptr, 0);
  Xbtn2cmd_menu_id = XPLMCreateMenu("Xbtn2cmd", XPLMFindPluginsMenu(),
                                    Xbtn2cmd_menu_container_idx,
                                    Xbtn2cmdmenu_handler, nullptr);
  XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Toggle Window", (void *)"Menu Item 1",
                     1);
  XPLMAppendMenuSeparator(Xbtn2cmd_menu_id);
  XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Reload xbtn2cmd.ini",
                     (void *)"Menu Item 2", 1);
  XPLMAppendMenuSeparator(Xbtn2cmd_menu_id);
  XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Reload Window", (void *)"Menu Item 3",
                     1);
  XPLMAppendMenuSeparator(Xbtn2cmd_menu_id);
  XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Recreate Window", (void *)"Menu Item 4",
                     1);
  XPLMAppendMenuSeparator(Xbtn2cmd_menu_id);
  XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Edit Current Button",
                     (void *)"Menu Item 5", 1);

  cmdtogglewindow =
      XPLMCreateCommand("bgood/xbtn2cmd/toggle_window", "Toggle Window");
  cmdreloadconfig =
      XPLMCreateCommand("bgood/xbtn2cmd/reload_config", "Reload xbtn2cmd.ini");
  cmdreloadwindow =
      XPLMCreateCommand("bgood/xbtn2cmd/reload_window", "Reload Window");
  cmdrecreatewindow =
      XPLMCreateCommand("bgood/xbtn2cmd/recreate_window", "Recreate Window");
  cmdopeneditwindow =
      XPLMCreateCommand("bgood/xbtn2cmd/open_edit_window", "Open Edit Window");

  XPLM_radio_com1_actv_freq =
      XPLMFindDataRef("sim/cockpit2/radios/actuators/com1_frequency_hz");
  XPLM_radio_com2_actv_freq =
      XPLMFindDataRef("sim/cockpit2/radios/actuators/com2_frequency_hz");
  XPLM_radio_nav1_actv_freq =
      XPLMFindDataRef("sim/cockpit2/radios/actuators/nav1_frequency_hz");
  XPLM_radio_nav2_actv_freq =
      XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_frequency_hz");
  XPLM_radio_adf1_actv_freq =
      XPLMFindDataRef("sim/cockpit2/radios/actuators/adf1_frequency_hz");
  XPLM_radio_adf2_actv_freq =
      XPLMFindDataRef("sim/cockpit2/radios/actuators/adf2_frequency_hz");

  XPLM_radio_com1_stby_freq = XPLMFindDataRef(
      "sim/cockpit2/radios/actuators/com1_standby_frequency_hz");
  XPLM_radio_com2_stby_freq = XPLMFindDataRef(
      "sim/cockpit2/radios/actuators/com2_standby_frequency_hz");
  XPLM_radio_nav1_stby_freq = XPLMFindDataRef(
      "sim/cockpit2/radios/actuators/nav1_standby_frequency_hz");
  XPLM_radio_nav2_stby_freq = XPLMFindDataRef(
      "sim/cockpit2/radios/actuators/nav2_standby_frequency_hz");
  XPLM_radio_adf1_stby_freq = XPLMFindDataRef(
      "sim/cockpit2/radios/actuators/adf1_standby_frequency_hz");
  XPLM_radio_adf2_stby_freq = XPLMFindDataRef(
      "sim/cockpit2/radios/actuators/adf2_standby_frequency_hz");

  process_find_xplane_radios_commands();

  XPLMRegisterCommandHandler(cmdtogglewindow, Xbtn2cmdCommandCallback, true,
                             (void *)TOGGLE_WINDOW_COMMAND);

  XPLMRegisterCommandHandler(cmdreloadconfig, Xbtn2cmdCommandCallback, true,
                             (void *)RELOAD_CONFIG_COMMAND);

  XPLMRegisterCommandHandler(cmdreloadwindow, Xbtn2cmdCommandCallback, true,
                             (void *)RELOAD_WINDOW_COMMAND);

  XPLMRegisterCommandHandler(cmdrecreatewindow, Xbtn2cmdCommandCallback, true,
                             (void *)RECREATE_WINDOW_COMMAND);

  XPLMRegisterCommandHandler(cmdopeneditwindow, Xbtn2cmdCommandCallback, true,
                             (void *)OPEN_EDIT_WINDOW_COMMAND);

  //  Create our custom integer datarefs
  PageNumberDataRef = XPLMRegisterDataAccessor(
      "bgood/xbtn2cmd/page_number_value",
      xplmType_Int,                                    // The types we support
      1,                                               // Writable
      GetPageNumberDataRefCB, SetPageNumberDataRefCB,  // Integer accessors
      nullptr, nullptr,                                // Float accessors
      nullptr, nullptr,                                // Doubles accessors
      nullptr, nullptr,                                // Int array accessors
      nullptr, nullptr,                                // Float array accessors
      nullptr, nullptr,                                // Raw data accessors
      nullptr, nullptr);                               // Refcons not used

  ButtonNumberDataRef = XPLMRegisterDataAccessor(
      "bgood/xbtn2cmd/button_number_value",
      xplmType_Int,  // The types we support
      1,             // Writable
      GetButtonNumberDataRefCB, SetButtonNumberDataRefCB,  // Integer accessors
      nullptr, nullptr,                                    // Float accessors
      nullptr, nullptr,                                    // Doubles accessors
      nullptr, nullptr,  // Int array accessors
      nullptr, nullptr,  // Float array accessors
      nullptr, nullptr,  // Raw data accessors
      nullptr, nullptr);

  // Find and intialize our Page and Button dataref
  PageNumberDataRef = XPLMFindDataRef("bgood/xbtn2cmd/page_number_value");
  XPLMSetDatai(PageNumberDataRef, 0);

  ButtonNumberDataRef = XPLMFindDataRef("bgood/xbtn2cmd/button_number_value");
  XPLMSetDatai(ButtonNumberDataRef, 0);

  return g_vr_dref != nullptr;
}

PLUGIN_API void XPluginStop(void) {
  // Since we created the window, we'll be good citizens and clean it up
  XPLMDestroyWindow(xb2cvr_g_window);
  xb2cvr_g_window = nullptr;
  xbtn2cmdiniVector.clear();
  XPLMUnregisterDataAccessor(PageNumberDataRef);
  XPLMUnregisterDataAccessor(ButtonNumberDataRef);
}

PLUGIN_API void XPluginDisable(void) {}
PLUGIN_API int XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID /*inFrom*/, int inMsg,
                                      void * /*inParam*/) {
  // We want to wait to create our window until *after* the first scenery load,
  // so that VR will actually be available.

  if (VersionXP > 11200) {
    if (inMsg == XPLM_MSG_SCENERY_LOADED) {
      xb2cvr_create_gui_window();
      process_read_ini_file();
      if (first_time == 0) {
        XPLMSetWindowIsVisible(xb2cvr_g_window, 0);
        first_time = 1;
      }
      XPLMDebugString("Xbtn2cmd: inMsg == XPLM_MSG_SCENERY_LOADED\n");
    }

#if XPLM301
    if (inMsg == XPLM_MSG_ENTERED_VR) {
      if (xb2cvr_g_window) {
        xb2cvr_g_window = nullptr;
        XPLMDebugString(
            "Xbtn2cmd: inMsg == XPLM_MSG_ENTERED_VR   if (xb2cvr_g_window)\n");
      }
      xb2cvr_create_gui_window();
      process_read_ini_file();
      XPLMSetWindowIsVisible(xb2cvr_g_window, 0);
      XPLMDebugString("Xbtn2cmd: inMsg == XPLM_MSG_ENTERED_VR\n");
    }
#endif
  }
}

void send_delayed_ctrl_c() {
  XPLMSpeakString("Sending control C in 10 seconds");
  XPLMRegisterFlightLoopCallback(DelayedControlC_Callback, 10, nullptr);
}

float DelayedControlC_Callback(float /*inElapsed1*/, float /*inElapsed2*/,
                               int /*cntr*/, void * /*ref*/) {
#if IBM
  XPLMSpeakString("Sending control C now");
  // Hold Control down and press C
  keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
  keybd_event(C, 0, KEYEVENTF_EXTENDEDKEY, 0);
  keybd_event(C, 0, KEYEVENTF_KEYUP, 0);
  keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
  return 0;
#endif

  return 0;
}

int GetPageNumberDataRefCB(void * /*inRefcon*/) { return PageNumberValue; }

void SetPageNumberDataRefCB(void * /*inRefcon*/, int inValue) {
  PageNumberValue = inValue;
}

int GetButtonNumberDataRefCB(void * /*inRefcon*/) { return ButtonNumberValue; }

void SetButtonNumberDataRefCB(void * /*inRefcon*/, int inValue) {
  ButtonNumberValue = inValue;
}


bool toggle_gui()
{
    if (XPLMGetWindowIsVisible(xb2cvr_g_window)) {
        if (is_popped_out) {
            was_popped_out = is_popped_out;
            XPLMGetWindowGeometryOS(xb2cvr_g_window, &left1, &top1, &right1, &bottom1);
        } else {
            XPLMGetWindowGeometry(xb2cvr_g_window, &left1, &top1, &right1, &bottom1);
        }
        XPLMSetWindowIsVisible(xb2cvr_g_window,0);
    } else {
        if (was_popped_out) {
            XPLMSetWindowPositioningMode(xb2cvr_g_window, xplm_WindowPopOut, 0);
            #if LIN
            XPLMSetWindowGeometryOS(xb2cvr_g_window, left1 + ((right1 - left1) / 2), top1 - ((top1 - bottom1) /2) + 14, right1 + ((right1 - left1) / 2), bottom1 - ((top1 - bottom1) /2) + 14);
            #else
            XPLMSetWindowGeometryOS(xb2cvr_g_window, left1, top1, right1, bottom1);
            #endif
            XPLMSetWindowIsVisible(xb2cvr_g_window,1);
            was_popped_out = 0;
        }
        if (!is_popped_out) {
            XPLMSetWindowGeometryOS(xb2cvr_g_window, left1, top1, right1, bottom1);
            XPLMSetWindowIsVisible(xb2cvr_g_window,1);
        }
    }
    return true;
}

void xb2cvr_create_gui_window() {
  vr_is_enabled = XPLMGetDatai(g_vr_dref);

  if (xb2cvr_g_window == nullptr) {
    // We're not guaranteed that the main monitor's lower left is at (0, 0)...
    // we'll need to query for the global desktop bounds!
    int xb2cvr_global_desktop_bounds[4];  // left, bottom, right, top
    XPLMGetScreenBoundsGlobal(
        &xb2cvr_global_desktop_bounds[0], &xb2cvr_global_desktop_bounds[3],
        &xb2cvr_global_desktop_bounds[2], &xb2cvr_global_desktop_bounds[1]);

    XPLMCreateWindow_t params;
    params.structSize = sizeof(params);
    params.left = xb2cvr_global_desktop_bounds[0] + 50;
    params.bottom = xb2cvr_global_desktop_bounds[1] + 100;
    params.right = xb2cvr_global_desktop_bounds[0] + 600;
    params.top = xb2cvr_global_desktop_bounds[1] + 420;
    params.visible = 1;
    params.drawWindowFunc = xb2cvr_draw;
    params.handleMouseClickFunc = xb2cvr_handle_mouse;
    params.handleRightClickFunc = xb2cvr_dummy_mouse_handler;
    params.handleMouseWheelFunc = xb2cvr_dummy_wheel_handler;
    params.handleKeyFunc = xb2cvr_dummy_key_handler;
    params.handleCursorFunc = xb2cvr_dummy_cursor_status_handler;
    params.refcon = nullptr;
    params.layer = xplm_WindowLayerFloatingWindows;
    if (vr_is_enabled) {
      params.decorateAsFloatingWindow = xplm_WindowDecorationSelfDecorated;
    } else {
      params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
    }

    xb2cvr_g_window = XPLMCreateWindowEx(&params);
    XPLMSetWindowPositioningMode(
        xb2cvr_g_window,
        vr_is_enabled ? xplm_WindowVR : xplm_WindowPositionFree, -1);
    g_in_vr = static_cast<bool>(vr_is_enabled);

    XPLMSetWindowResizingLimits(xb2cvr_g_window, 550, 320, 600,
                                370);  // Limit resizing our window: maintain a
                                       // minimum width/height of 200 boxels and
                                       // a max width/height of 500

    XPLMSetWindowTitle(xb2cvr_g_window, "Xbtn2cmd     Buttons 2 Commands");
  } else {
    XPLMDebugString("Xbtn2cmd: xb2cvr_g_window NOT == NULL\n");
    XPLMSetWindowIsVisible(xb2cvr_g_window, 1);
    XPLMSetWindowPositioningMode(
        xb2cvr_g_window,
        vr_is_enabled ? xplm_WindowVR : xplm_WindowPositionFree, -1);
  }
}

// Menu handler

void Xbtn2cmdmenu_handler(void * /*in_menu_ref*/, void *in_item_ref) {
  if (!strcmp((const char *)in_item_ref, "Menu Item 1")) {
    process_read_ini_file();

    if (XPLMGetWindowIsVisible(xb2cvr_g_window)) {
      XPLMSetWindowIsVisible(xb2cvr_g_window, 0);
    } else {
      XPLMSetWindowIsVisible(xb2cvr_g_window, 1);
    }


    /*
    #if IBM
    if (is_popped_out) {
        command_pressed = command_pressed + 1;
        if (command_pressed == 1) {
            toggle_gui();
        }
        sprintf(scratch_buffer, "\nXbtn2cmd: command_pressed = %d\n", command_pressed);
        XPLMDebugString(scratch_buffer);
        if (command_pressed == 2) {
            command_pressed = 0;
        }
    } else {
        toggle_gui();
    }
    #else
    toggle_gui();
    #endif
    */
    mouse_down_hide = 0, mouse_down_reload = 0, mouse_down_edit = 0;
    mouse_down_ctrl_c = 0, ButtonNumberValue = 0;
    mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
    mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
    mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
    mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
    mouse_down[12] = 0, mouse_down[13] = 0, mouse_down[14] = 0;
    mouse_down[15] = 0, mouse_down[16] = 0, mouse_down[17] = 0;
    mouse_down[18] = 0, mouse_down[19] = 0, mouse_down[20] = 0;
    mouse_down[21] = 0, mouse_down[22] = 0, mouse_down[23] = 0;

  } else if (!strcmp((const char *)in_item_ref, "Menu Item 2")) {
    process_read_ini_file();
  } else if (!strcmp((const char *)in_item_ref, "Menu Item 3")) {
    process_read_ini_file();
    xb2cvr_create_gui_window();
    mouse_down_hide = 0, mouse_down_reload = 0, mouse_down_edit = 0;
    mouse_down_ctrl_c = 0, ButtonNumberValue = 0;
    mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
    mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
    mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
    mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
    mouse_down[12] = 0, mouse_down[13] = 0, mouse_down[14] = 0;
    mouse_down[15] = 0, mouse_down[16] = 0, mouse_down[17] = 0;
    mouse_down[18] = 0, mouse_down[19] = 0, mouse_down[20] = 0;
    mouse_down[21] = 0, mouse_down[22] = 0, mouse_down[23] = 0;
  } else if (!strcmp((const char *)in_item_ref, "Menu Item 4")) {
    process_read_ini_file();
    xb2cvr_g_window = nullptr;
    xb2cvr_create_gui_window();
    mouse_down_hide = 0, mouse_down_reload = 0, mouse_down_edit = 0;
    mouse_down_ctrl_c = 0, ButtonNumberValue = 0;
    mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
    mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
    mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
    mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
    mouse_down[12] = 0, mouse_down[13] = 0, mouse_down[14] = 0;
    mouse_down[15] = 0, mouse_down[16] = 0, mouse_down[17] = 0;
    mouse_down[18] = 0, mouse_down[19] = 0, mouse_down[20] = 0;
    mouse_down[21] = 0, mouse_down[22] = 0, mouse_down[23] = 0;
  }

  else if (!strcmp((const char *)in_item_ref, "Menu Item 5")) {
    if (Xbtn2cmdEditWidget == nullptr) {
      CreateXbtn2cmdEditWidget(400, 550, 580,
                               250);  // left, top, right, bottom.
    } else {
      if (!XPIsWidgetVisible(Xbtn2cmdEditWidget))
        XPShowWidget(Xbtn2cmdEditWidget);
    }
    edit_mode = 1;
  }
}

void Xbtn2hide_window() { XPLMSetWindowIsVisible(xb2cvr_g_window, 0); }

void process_create_edit_window() {
  if (Xbtn2cmdEditWidget == nullptr) {
    CreateXbtn2cmdEditWidget(400, 550, 580, 250);  // left, top, right, bottom.
  } else {
    if (!XPIsWidgetVisible(Xbtn2cmdEditWidget))
      XPShowWidget(Xbtn2cmdEditWidget);
  }
  edit_mode = 1;
}

void CreateXbtn2cmdEditWidget(int xx, int yy, int ww, int hh) {
  int xx2 = xx + ww;
  int yy2 = yy - hh;

  int yOffset;

  // Create the Edit Widget window.
  Xbtn2cmdEditWidget =
      XPCreateWidget(xx, yy, xx2, yy2,
                     1,                                      // Visible
                     "Xbtn2cmd Current Button Edit Window",  // desc
                     1,                                      // root
                     nullptr,                                // no container
                     xpWidgetClass_MainWindow);
  // Add Close Box to the Setup Widget.  Other options are available.  See the
  // SDK Documentation.
  XPSetWidgetProperty(Xbtn2cmdEditWidget, xpProperty_MainWindowHasCloseBoxes,
                      1);

  XPSetWidgetProperty(Xbtn2cmdEditWidget, xpProperty_MainWindowType,
                      xpMainWindowStyle_Translucent);

  int l = 0;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist item description text widget
  CurrentPageLabelLineTextBoxWidget =
      XPCreateWidget(xx + 10, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,                              // Visible
                     "page1_button_label = Page 1",  // desc
                     0,                              // root
                     Xbtn2cmdEditWidget, xpWidgetClass_TextField);

  // Set it to be text entry
  XPSetWidgetProperty(CurrentPageLabelLineTextBoxWidget,
                      xpProperty_TextFieldType, xpTextEntryField);

  l = 1;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist item description text widget
  CopyPageLabelLineTextBoxButtonWidget =
      XPCreateWidget(xx + 10, yy - yOffset, xx + 60, yy - yOffset - 20,
                     1,       // Visible
                     "Copy",  // desc
                     0,       // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(CopyPageLabelLineTextBoxButtonWidget,
                      xpProperty_ButtonType, xpPushButton);

  // Create a checklist item description text widget
  PastePageLabelLineTextBoxButtonWidget =
      XPCreateWidget(xx + 510, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,        // Visible
                     "Paste",  // desc
                     0,        // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(PastePageLabelLineTextBoxButtonWidget,
                      xpProperty_ButtonType, xpPushButton);

  l = 2;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist item description text widget
  CurrentPageButtonLabelLineTextBoxWidget =
      XPCreateWidget(xx + 10, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,                                 // Visible
                     "page1_button1_label = Button 1",  // desc
                     0,                                 // root
                     Xbtn2cmdEditWidget, xpWidgetClass_TextField);

  // Set it to be text entry
  XPSetWidgetProperty(CurrentPageButtonLabelLineTextBoxWidget,
                      xpProperty_TextFieldType, xpTextEntryField);

  l = 3;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist item description text widget
  CopyPageButtonLabelLineTextBoxButtonWidget =
      XPCreateWidget(xx + 10, yy - yOffset, xx + 60, yy - yOffset - 20,
                     1,       // Visible
                     "Copy",  // desc
                     0,       // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(PastePageButtonLabelLineTextBoxButtonWidget,
                      xpProperty_ButtonType, xpPushButton);

  // Create a checklist item description text widget
  PastePageButtonLabelLineTextBoxButtonWidget =
      XPCreateWidget(xx + 510, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,        // Visible
                     "Paste",  // desc
                     0,        // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(PastePageButtonLabelLineTextBoxButtonWidget,
                      xpProperty_ButtonType, xpPushButton);

  l = 4;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist item description text widget
  CurrentPageButtonCommandOnceLineTextBoxWidget =
      XPCreateWidget(xx + 10, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,                               // Visible
                     "page1_button1_command_once =",  // desc
                     0,                               // root
                     Xbtn2cmdEditWidget, xpWidgetClass_TextField);

  // Set it to be text entry
  XPSetWidgetProperty(CurrentPageButtonCommandOnceLineTextBoxWidget,
                      xpProperty_TextFieldType, xpTextEntryField);

  l = 5;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist itPastePageButtonCommandOnceLineTextBoxButtonWidgetem
  // description text widget
  CopyPageButtonCommandOnceLineTextBoxButtonWidget =
      XPCreateWidget(xx + 10, yy - yOffset, xx + 60, yy - yOffset - 20,
                     1,       // Visible
                     "Copy",  // desc
                     0,       // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(PastePageButtonCommandOnceLineTextBoxButtonWidget,
                      xpProperty_ButtonType, xpPushButton);

  // Create a checklist itPastePageButtonCommandOnceLineTextBoxButtonWidgetem
  // description text widget
  PastePageButtonCommandOnceLineTextBoxButtonWidget =
      XPCreateWidget(xx + 510, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,        // Visible
                     "Paste",  // desc
                     0,        // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(PastePageButtonCommandOnceLineTextBoxButtonWidget,
                      xpProperty_ButtonType, xpPushButton);

  l = 6;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist item description text widget
  CurrentPageButtonCommandContinueLineTextBoxWidget =
      XPCreateWidget(xx + 10, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,                                   // Visible
                     "page1_button1_command_continue =",  // desc
                     0,                                   // root
                     Xbtn2cmdEditWidget, xpWidgetClass_TextField);

  // Set it to be text entry
  XPSetWidgetProperty(CurrentPageButtonCommandContinueLineTextBoxWidget,
                      xpProperty_TextFieldType, xpTextEntryField);

  l = 7;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist itPastePageButtonCommandOnceLineTextBoxButtonWidgetem
  // description text widget
  CopyPageButtonCommandContinueLineTextBoxButtonWidget =
      XPCreateWidget(xx + 10, yy - yOffset, xx + 60, yy - yOffset - 20,
                     1,       // Visible
                     "Copy",  // desc
                     0,       // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(PastePageButtonCommandContinueLineTextBoxButtonWidget,
                      xpProperty_ButtonType, xpPushButton);

  // Create a checklist itPastePageButtonCommandOnceLineTextBoxButtonWidgetem
  // description text widget
  PastePageButtonCommandContinueLineTextBoxButtonWidget =
      XPCreateWidget(xx + 510, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,        // Visible
                     "Paste",  // desc
                     0,        // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(PastePageButtonCommandContinueLineTextBoxButtonWidget,
                      xpProperty_ButtonType, xpPushButton);

  l = 8;

  yOffset = (5 + 18 + (l * 25));

  // Create a checklist item description text widget
  WriteIniFileButtonWidget =
      XPCreateWidget(xx + 5, yy - yOffset, xx + 60 + 200, yy - yOffset - 20,
                     1,                                           // Visible
                     "Write Array To Current xbtn2cmd.ini File",  // desc
                     0,                                           // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(WriteIniFileButtonWidget, xpProperty_ButtonType,
                      xpPushButton);

  // Create a checklist item description text widget
  UpdatePageLabelButtonWidget =
      XPCreateWidget(xx + 380, yy - yOffset, xx + 60 + 510, yy - yOffset - 20,
                     1,                              // Visible
                     "Update Current Button Array",  // desc
                     0,                              // root
                     Xbtn2cmdEditWidget, xpWidgetClass_Button);

  XPSetWidgetProperty(UpdatePageLabelButtonWidget, xpProperty_ButtonType,
                      xpPushButton);

  // Register our setup widget handler
  XPAddWidgetCallback(Xbtn2cmdEditWidget, Xbtn2cmdEditHandler);
#if XPLM301
  xbtn2cmd_edit_window = XPGetWidgetUnderlyingWindow(Xbtn2cmdEditWidget);
#endif

  XPLMSetWindowIsVisible(xbtn2cmd_edit_window, 1);
  vr_is_enabled = XPLMGetDatai(g_vr_dref);

#if XPLM301
  XPLMSetWindowPositioningMode(
      xbtn2cmd_edit_window,
      vr_is_enabled ? xplm_WindowVR : xplm_WindowPositionFree, -1);
#endif
}

// This is our setup widget handler.  In this example we are only interested
// when the close box is pressed.
int Xbtn2cmdEditHandler(XPWidgetMessage inMessage, XPWidgetID inWidget,
                        intptr_t inParam1, intptr_t /*inParam2*/) {
  if (inMessage == xpMessage_CloseButtonPushed) {
    if (inWidget == Xbtn2cmdEditWidget) {
      XPHideWidget(Xbtn2cmdEditWidget);
      edit_mode = 0;
      return 1;
    }
  }

  if (update_widget) {
    XPSetWidgetDescriptor(CurrentPageLabelLineTextBoxWidget,
                          current_page_label_line.c_str());
    XPSetWidgetDescriptor(CurrentPageButtonLabelLineTextBoxWidget,
                          current_page_button_label_line.c_str());
    XPSetWidgetDescriptor(CurrentPageButtonCommandOnceLineTextBoxWidget,
                          current_page_button_command_once_line.c_str());
    XPSetWidgetDescriptor(CurrentPageButtonCommandContinueLineTextBoxWidget,
                          current_page_button_command_continue_line.c_str());

    update_widget = 0;
  }

  if (inMessage == xpMsg_PushButtonPressed) {
    if (inParam1 == (intptr_t)CopyPageLabelLineTextBoxButtonWidget) {
      inWidget = CurrentPageLabelLineTextBoxWidget;
      copy_button_pushed = 1;
      XPLMDebugString(
          "Xbtn2cmd: CopyPageLabelLineTextBoxButtonWidget pushed\n");
    }

    if (inParam1 == (intptr_t)PastePageLabelLineTextBoxButtonWidget) {
      inWidget = CurrentPageLabelLineTextBoxWidget;
      paste_button_pushed = 1;
      XPLMDebugString(
          "Xbtn2cmd: PastePageLabelLineTextBoxButtonWidget pushed\n");
    }

    if (inParam1 == (intptr_t)CopyPageButtonLabelLineTextBoxButtonWidget) {
      inWidget = CurrentPageButtonLabelLineTextBoxWidget;
      copy_button_pushed = 1;
      XPLMDebugString(
          "Xbtn2cmd: CopyPageButtonLabelLineTextBoxButtonWidget pushed\n");
    }

    if (inParam1 == (intptr_t)PastePageButtonLabelLineTextBoxButtonWidget) {
      inWidget = CurrentPageButtonLabelLineTextBoxWidget;
      paste_button_pushed = 1;
      XPLMDebugString(
          "Xbtn2cmd: PastePageButtonLabelLineTextBoxButtonWidget pushed\n");
    }

    if (inParam1 ==
        (intptr_t)CopyPageButtonCommandOnceLineTextBoxButtonWidget) {
      inWidget = CurrentPageButtonCommandOnceLineTextBoxWidget;
      copy_button_pushed = 1;
      XPLMDebugString(
          "Xbtn2cmd: "
          "CopyPageButtonCommandOnceLineTextBoxButtonWidget "
          "pushed\n");
    }

    if (inParam1 ==
        (intptr_t)PastePageButtonCommandOnceLineTextBoxButtonWidget) {
      inWidget = CurrentPageButtonCommandOnceLineTextBoxWidget;
      paste_button_pushed = 1;
      XPLMDebugString(
          "Xbtn2cmd: "
          "PastePageButtonCommandOnceLineTextBoxButtonWidget "
          "pushed\n");
    }

    if (inParam1 ==
        (intptr_t)CopyPageButtonCommandContinueLineTextBoxButtonWidget) {
      inWidget = CurrentPageButtonCommandContinueLineTextBoxWidget;
      copy_button_pushed = 1;
      XPLMDebugString(
          "Xbtn2cmd: "
          "CopyPageButtonCommandContinueLineTextBoxButtonWidget "
          "pushed\n");
    }

    if (inParam1 ==
        (intptr_t)PastePageButtonCommandContinueLineTextBoxButtonWidget) {
      inWidget = CurrentPageButtonCommandContinueLineTextBoxWidget;
      paste_button_pushed = 1;
      XPLMDebugString(
          "Xbtn2cmd: "
          "PastePageButtonCommandContinueLineTextBoxButtonWidget "
          "pushed\n");
    }

    if (copy_button_pushed || paste_button_pushed) {
      intptr_t selStart =
          XPGetWidgetProperty(inWidget, xpProperty_EditFieldSelStart, nullptr);
      intptr_t selEnd =
          XPGetWidgetProperty(inWidget, xpProperty_EditFieldSelEnd, nullptr);
      int strLen = XPGetWidgetDescriptor(inWidget, nullptr, 0);
      std::string txt;
      txt.resize(static_cast<unsigned long>(strLen));
      XPGetWidgetDescriptor(inWidget, &*txt.begin(),
                            static_cast<int>(txt.size() + 1));

      if (copy_button_pushed) {
        if ((selStart >= 0) && (selStart < selEnd) && (selEnd <= strLen)) {
          std::string scrap =
              txt.substr(static_cast<unsigned long>(selStart),
                         static_cast<unsigned long>(selEnd - selStart));
#if IBM
          XSBSetTextToClipboard(scrap);
#endif
#if LIN
          XSBSetTextToClipboard(scrap);
#endif
#if APL
// XSBSetTextToClipboard(scrap);
#endif
        }
        copy_button_pushed = 0;
        return 1;
      }

      if (paste_button_pushed) {
        std::string scrap;
        if (XSBGetTextFromClipboard(scrap) && !scrap.empty()) {
          if ((selEnd > selStart) && (selStart >= 0) && (selEnd <= strLen)) {
            txt.replace(static_cast<unsigned long>(selStart),
                        static_cast<unsigned long>(selEnd - selStart), scrap);
            XPSetWidgetDescriptor(inWidget, txt.c_str());
            XPSetWidgetProperty(inWidget, xpProperty_EditFieldSelStart,
                                selStart + scrap.size());
            XPSetWidgetProperty(inWidget, xpProperty_EditFieldSelEnd,
                                selStart + scrap.size());
          } else if ((selStart >= 0) && (selStart <= strLen)) {
            txt.insert(static_cast<unsigned long>(selStart), scrap);
            XPSetWidgetDescriptor(inWidget, txt.c_str());
            XPSetWidgetProperty(inWidget, xpProperty_EditFieldSelStart,
                                selStart + scrap.size());
            XPSetWidgetProperty(inWidget, xpProperty_EditFieldSelEnd,
                                selStart + scrap.size());
          }
        }
        paste_button_pushed = 0;
        return 1;
      }
    }

    if (inParam1 == (intptr_t)WriteIniFileButtonWidget) {
      write_ini_file_from_array();
      XPLMDebugString("Xbtn2cmd: WriteIniFileButtonWidget pushed\n");
    }

    if (inParam1 == (intptr_t)UpdatePageLabelButtonWidget) {
      update_current_button();
      XPLMDebugString("Xbtn2cmd: UpdatePageLabelButtonWidget pushed\n");
    }
  }

  return 0;
}

bool XSBGetTextFromClipboard(std::string &outText) {
#if IBM
  std::string ret;

  if (TRUE == OpenClipboard(NULL)) {
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (NULL != hData) {
      char *pszText = static_cast<char *>(GlobalLock(hData));
      if (NULL != pszText) {
        ret.assign(pszText);
      }

      GlobalUnlock(hData);
    }

    CloseClipboard();
  }

  outText = ret.c_str();
  return 1;
#endif

#if APL
  outText = getClipboard();
  return 1;
#endif

#if LIN

  FILE *f = popen("xclip -sel clip -o", "r");
  if (f == nullptr) {
    fprintf(stderr, "Could not execute\n");
    return false;
  }
  const int BUFSIZE = 1000;
  char buf[BUFSIZE];
  while (fgets(buf, BUFSIZE, f)) {
    fprintf(stdout, "%s", buf);
  }
  pclose(f);
  sprintf(scratch_buffer, "Xbtn2cmd: buf = %s\n", buf);
  XPLMDebugString(scratch_buffer);
  outText = buf;
  sprintf(scratch_buffer, "Xbtn2cmd: outText.c_str() = %s\n", outText.c_str());
  XPLMDebugString(scratch_buffer);

  outText = buf;
  return true;
#endif
}

bool XSBSetTextToClipboard(const std::string &inText) {
#if IBM
  if (TRUE == OpenClipboard(NULL)) {
    EmptyClipboard();

    HGLOBAL hClipboardData = GlobalAlloc(GMEM_FIXED, inText.size() + 1);
    if (NULL != hClipboardData) {
      char *pchData = (char *)GlobalLock(hClipboardData);
      if (NULL != pchData) {
        strcpy(pchData, LPCSTR(inText.c_str()));

        GlobalUnlock(hClipboardData);

        SetClipboardData(CF_TEXT, hClipboardData);
      }
    }

    CloseClipboard();
  }

#endif
#if APL
  XPLMDebugString("Xbtn2cmd: setClipboard(inText)\n");
  setClipboard(inText.c_str());
#endif
#if LIN
  std::string command = "echo -n " + inText + " | xclip -sel c";
  if (0 != system(command.c_str())) {
    XPLMDebugString("Copy command failed. Do you have xclip on your system?");
  }
#endif
  return false;
}

void populate_edit_window() {
  size_t pos;
  string line;
  string find_end = "=";
  int line_length;
  current_line_number = 0;
  xbtn2cmdiniVector.clear();
  string vector_line;
  int vector_line_number = 0;

  sprintf(scratch_buffer, "Xbtn2cmd: Current xbtn2cmd.ini file path = %s\n",
          xbtn2cmdini_path_name.c_str());
  XPLMDebugString(scratch_buffer);

  std::ifstream inFile;
  inFile.open(xbtn2cmdini_path_name.c_str());

  if (inFile.fail()) {
    XPLMDebugString(
        "Xbtn2cmd: Could not open Cessna_172SP_xbtn2cmd.ini file\n");
    return;
  }

  while (inFile.good()) {
    getline(inFile, line);  // get line from file
    xbtn2cmdiniVector.push_back(line);
  }

  inFile.close();
  update_widget = 1;
  vector_size = static_cast<int>(xbtn2cmdiniVector.size());
  sprintf(scratch_buffer, "Xbtn2cmd: vector_size = %d\n", vector_size);
  XPLMDebugString(scratch_buffer);

  while (vector_line_number < vector_size) {
    vector_line = xbtn2cmdiniVector[vector_line_number];

    pos = vector_line.find(search_current_page_label);  // search
    if (pos !=
        string::npos) {  // string::npos is returned if string is not found
      line_length = static_cast<int>(vector_line.length());
      current_page_label_line_number = vector_line_number;
      current_page_label_line = vector_line;
      current_page_label_line_length = line_length;
      current_page_label_write_start_position =
          static_cast<int>(vector_line.find(find_end) + 2);
      if (line_length > current_page_label_write_start_position) {
        current_page_label = vector_line.substr(static_cast<unsigned long>(
            current_page_label_write_start_position));
      } else {
        current_page_label = "";
      }
    }

    pos = vector_line.find(search_current_page_button_label);  // search
    if (pos !=
        string::npos) {  // string::npos is returned if string is not found
      line_length = static_cast<int>(vector_line.length());
      current_page_button_label_line_number = vector_line_number;
      current_page_button_label_line = vector_line;
      current_page_button_label_line_length = line_length;
      current_page_button_label_write_start_position =
          static_cast<int>(vector_line.find(find_end) + 2);
      if (line_length > current_page_button_label_write_start_position) {
        current_page_button_label =
            vector_line.substr(static_cast<unsigned long>(
                current_page_button_label_write_start_position));
      } else {
        current_page_button_label = "";
      }
    }

    pos = vector_line.find(search_current_page_button_command_once);  // search
    if (pos !=
        string::npos) {  // string::npos is returned if string is not found
      line_length = static_cast<int>(vector_line.length());
      current_page_button_command_once_line_number = vector_line_number;
      current_page_button_command_once_line = vector_line;
      current_page_button_command_once_line_length = line_length;
      current_page_button_command_once_write_start_position =
          static_cast<int>(vector_line.find(find_end) + 2);
      if (line_length > current_page_button_command_once_write_start_position) {
        current_page_button_command_once =
            vector_line.substr(static_cast<unsigned long>(
                current_page_button_command_once_write_start_position));
      } else {
        current_page_button_command_once = "";
      }
    }

    pos = vector_line.find(
        search_current_page_button_command_continue);  // search
    if (pos !=
        string::npos) {  // string::npos is returned if string is not found
      line_length = static_cast<int>(vector_line.length());
      current_page_button_command_continue_line_number = vector_line_number;
      current_page_button_command_continue_line = vector_line;
      current_page_button_command_continue_line_length = line_length;
      current_page_button_command_continue_write_start_position =
          static_cast<int>(vector_line.find(find_end) + 2);
      if (line_length >
          current_page_button_command_continue_write_start_position) {
        current_page_button_command_continue =
            vector_line.substr(static_cast<unsigned long>(
                current_page_button_command_continue_write_start_position));
      } else {
        current_page_button_command_continue = "";
      }
    }

    vector_line_number = vector_line_number + 1;
  }
}

void update_current_button() {
  char buffer[100];
  string tmp;

  memset(buffer, 0, sizeof(buffer));
  XPGetWidgetDescriptor(CurrentPageLabelLineTextBoxWidget, buffer,
                        sizeof(buffer));
  tmp = string(buffer);
  xbtn2cmdiniVector[current_page_label_line_number] = tmp;

  memset(buffer, 0, sizeof(buffer));
  XPGetWidgetDescriptor(CurrentPageButtonLabelLineTextBoxWidget, buffer,
                        sizeof(buffer));
  tmp = string(buffer);
  xbtn2cmdiniVector[current_page_button_label_line_number] = tmp;

  memset(buffer, 0, sizeof(buffer));
  XPGetWidgetDescriptor(CurrentPageButtonCommandOnceLineTextBoxWidget, buffer,
                        sizeof(buffer));
  tmp = string(buffer);
  xbtn2cmdiniVector[current_page_button_command_once_line_number] = tmp;

  memset(buffer, 0, sizeof(buffer));
  XPGetWidgetDescriptor(CurrentPageButtonCommandContinueLineTextBoxWidget,
                        buffer, sizeof(buffer));
  tmp = string(buffer);
  xbtn2cmdiniVector[current_page_button_command_continue_line_number] = tmp;
}

void write_ini_file_from_array() {
  int count = 0;
  std::ofstream outFile;
  outFile.open(xbtn2cmdini_path_name.c_str());

  if (outFile.fail()) {
    XPLMDebugString(
        "Xbtn2cmd: Could not open Cessna_172SP_xbtn2cmd.ini file\n");
    return;
  }
  if (outFile.is_open()) {
    XPLMDebugString(
        "Xbtn2cmd: Found Cessna_172SP_xbtn2cmd.ini open for "
        "writing now will close it\n\n");
    while (count < vector_size - 1) {
      outFile << xbtn2cmdiniVector[count] << "\n";
      count = count + 1;
    }
  }

  XPLMDebugString("Xbtn2cmd: outFile.close()\n");
  outFile.close();
}

int Xbtn2cmdCommandCallback(XPLMCommandRef inCommand, XPLMCommandPhase inPhase,
                            void *inRefcon) {
  (void)inCommand;

  if (inPhase == xplm_CommandBegin) {
    switch ((intptr_t)inRefcon) {
      case TOGGLE_WINDOW_COMMAND:
        /*
        if (XPLMGetWindowIsVisible(xb2cvr_g_window)) {
          XPLMSetWindowIsVisible(xb2cvr_g_window, 0);
        } else {
          XPLMSetWindowIsVisible(xb2cvr_g_window, 1);
        }
        */
        #if IBM
        if (is_popped_out) {
            command_pressed = command_pressed + 1;
            if (command_pressed == 1) {
                toggle_gui();
            }
            sprintf(scratch_buffer, "\nXbtn2cmd: command_pressed = %d\n", command_pressed);
            XPLMDebugString(scratch_buffer);
            if (command_pressed == 2) {
                command_pressed = 0;
            }
        } else {
            toggle_gui();
        }
        #else
        toggle_gui();
        #endif
        mouse_down_hide = 0, mouse_down_reload = 0, mouse_down_edit = 0;
        mouse_down_ctrl_c = 0, ButtonNumberValue = 0;
        mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
        mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
        mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
        mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
        mouse_down[12] = 0, mouse_down[13] = 0, mouse_down[14] = 0;
        mouse_down[15] = 0, mouse_down[16] = 0, mouse_down[17] = 0;
        mouse_down[18] = 0, mouse_down[19] = 0, mouse_down[20] = 0;
        mouse_down[21] = 0, mouse_down[22] = 0, mouse_down[23] = 0;
        break;
      case RELOAD_CONFIG_COMMAND:
        process_read_ini_file();
        break;
      case RELOAD_WINDOW_COMMAND:
        process_read_ini_file();
        xb2cvr_create_gui_window();
        mouse_down_hide = 0, mouse_down_reload = 0, mouse_down_edit = 0;
        mouse_down_ctrl_c = 0, ButtonNumberValue = 0;
        mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
        mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
        mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
        mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
        mouse_down[12] = 0, mouse_down[13] = 0, mouse_down[14] = 0;
        mouse_down[15] = 0, mouse_down[16] = 0, mouse_down[17] = 0;
        mouse_down[18] = 0, mouse_down[19] = 0, mouse_down[20] = 0;
        mouse_down[21] = 0, mouse_down[22] = 0, mouse_down[23] = 0;
        break;
      case RECREATE_WINDOW_COMMAND:
        process_read_ini_file();
        xb2cvr_g_window = nullptr;
        xb2cvr_create_gui_window();
        mouse_down_hide = 0, mouse_down_reload = 0, mouse_down_edit = 0;
        mouse_down_ctrl_c = 0, ButtonNumberValue = 0;
        mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
        mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
        mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
        mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
        mouse_down[12] = 0, mouse_down[13] = 0, mouse_down[14] = 0;
        mouse_down[15] = 0, mouse_down[16] = 0, mouse_down[17] = 0;
        mouse_down[18] = 0, mouse_down[19] = 0, mouse_down[20] = 0;
        mouse_down[21] = 0, mouse_down[22] = 0, mouse_down[23] = 0;
        break;
      case OPEN_EDIT_WINDOW_COMMAND:
        process_create_edit_window();
        break;
    }
  }
  return 1;
}
