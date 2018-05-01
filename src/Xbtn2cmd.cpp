// *********************************************************
//
//     Xbtn2cmd Plugin
//
//     William Good
//
//     A plugin to create a window of buttons in VR
//     that can be mapped to commands.
//
//     Supporting  X-Plane 11.20r2+
//
// *********************************************************

#define VERSION_NUMBER "1.09 build " __DATE__ " " __TIME__

#include "XPLMDisplay.h"    // for window creation and manipulation
#include "XPLMGraphics.h"   // for window drawing
#include "XPLMDataAccess.h" // for the VR dataref
#include "XPLMPlugin.h"     // for XPLM_MSG_SCENERY_LOADED message
#include "XPLMUtilities.h"
#include "XPLMMenus.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <wchar.h>

using namespace std;

#if IBM
	#include <windows.h>
#endif
#if LIN
	#include <GL/gl.h>
#elif __GNUC__
    #include <GL/gl.h>
#else
	#include <gl.h>
#endif

#ifndef XPLM301
	#error This is made to be compiled against the XPLM301 SDK
#endif

static XPLMWindowID	xb2cvr_g_window;

void				xb2cvr_draw(XPLMWindowID in_window_id, void * in_refcon);
int					xb2cvr_handle_mouse(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon);

int					xb2cvr_dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon) { return 0; }
XPLMCursorStatus	xb2cvr_dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void * in_refcon) { return xplm_CursorDefault; }
int					xb2cvr_dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void * in_refcon) { return 0; }
void				xb2cvr_dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void * in_refcon, int losing_focus) { }

XPLMDataRef g_vr_dref;
static bool g_in_vr = false;
static float g_vr_button_lbrt[4]; // left, bottom, right, top

int xb2cvr_width = 500; // width of the widget checklist window

int vr_is_enabled = 0;

XPLMDataRef xb2cvr_g_FPS;

int                         VersionXP, VersionSDK;
XPLMHostApplicationID       HostID;

static int	coord_in_rect(float x, float y, float * bounds_lbrt)  { return ((x >= bounds_lbrt[0]) && (x < bounds_lbrt[2]) && (y < bounds_lbrt[3]) && (y >= bounds_lbrt[1])); }

void xb2cvr_create_gui_window();
void process_read_ini_file();

enum {TOGGLE_WINDOW_COMMAND, RELOAD_CONFIG_COMMAND, RELOAD_WINDOW_COMMAND, RECREATE_WINDOW_COMMAND};

int Xbtn2cmdCommandCallback(
                                   XPLMCommandRef       inCommand,
                                   XPLMCommandPhase     inPhase,
                                   void *               inRefcon);

XPLMCommandRef cmdtogglewindow;
XPLMCommandRef cmdreloadconfig;
XPLMCommandRef cmdreloadwindow;
XPLMCommandRef cmdrecreatewindow;


char scratch_buffer[150];

string page1_button_label, page2_button_label, page3_button_label, page4_button_label;

string button1_label, button1_command_once, button1_command_continue;
string button2_label, button2_command_once, button2_command_continue;
string button3_label, button3_command_once, button3_command_continue;
string button4_label, button4_command_once, button4_command_continue;
string button5_label, button5_command_once, button5_command_continue;
string button6_label, button6_command_once, button6_command_continue;
string button7_label, button7_command_once, button7_command_continue;
string button8_label, button8_command_once, button8_command_continue;
string button9_label, button9_command_once, button9_command_continue;
string button10_label, button10_command_once, button10_command_continue;
string button11_label, button11_command_once, button11_command_continue;
string button12_label, button12_command_once, button12_command_continue;



string page1_button1_label, page1_button1_command_once, page1_button1_command_continue;
string page1_button2_label, page1_button2_command_once, page1_button2_command_continue;
string page1_button3_label, page1_button3_command_once, page1_button3_command_continue;
string page1_button4_label, page1_button4_command_once, page1_button4_command_continue;
string page1_button5_label, page1_button5_command_once, page1_button5_command_continue;
string page1_button6_label, page1_button6_command_once, page1_button6_command_continue;
string page1_button7_label, page1_button7_command_once, page1_button7_command_continue;
string page1_button8_label, page1_button8_command_once, page1_button8_command_continue;
string page1_button9_label, page1_button9_command_once, page1_button9_command_continue;
string page1_button10_label, page1_button10_command_once, page1_button10_command_continue;
string page1_button11_label, page1_button11_command_once, page1_button11_command_continue;
string page1_button12_label, page1_button12_command_once, page1_button12_command_continue;


string page2_button1_label, page2_button1_command_once, page2_button1_command_continue;
string page2_button2_label, page2_button2_command_once, page2_button2_command_continue;
string page2_button3_label, page2_button3_command_once, page2_button3_command_continue;
string page2_button4_label, page2_button4_command_once, page2_button4_command_continue;
string page2_button5_label, page2_button5_command_once, page2_button5_command_continue;
string page2_button6_label, page2_button6_command_once, page2_button6_command_continue;
string page2_button7_label, page2_button7_command_once, page2_button7_command_continue;
string page2_button8_label, page2_button8_command_once, page2_button8_command_continue;
string page2_button9_label, page2_button9_command_once, page2_button9_command_continue;
string page2_button10_label, page2_button10_command_once, page2_button10_command_continue;
string page2_button11_label, page2_button11_command_once, page2_button11_command_continue;
string page2_button12_label, page2_button12_command_once, page2_button12_command_continue;


string page3_button1_label, page3_button1_command_once, page3_button1_command_continue;
string page3_button2_label, page3_button2_command_once, page3_button2_command_continue;
string page3_button3_label, page3_button3_command_once, page3_button3_command_continue;
string page3_button4_label, page3_button4_command_once, page3_button4_command_continue;
string page3_button5_label, page3_button5_command_once, page3_button5_command_continue;
string page3_button6_label, page3_button6_command_once, page3_button6_command_continue;
string page3_button7_label, page3_button7_command_once, page3_button7_command_continue;
string page3_button8_label, page3_button8_command_once, page3_button8_command_continue;
string page3_button9_label, page3_button9_command_once, page3_button9_command_continue;
string page3_button10_label, page3_button10_command_once, page3_button10_command_continue;
string page3_button11_label, page3_button11_command_once, page3_button11_command_continue;
string page3_button12_label, page3_button12_command_once, page3_button12_command_continue;


string page4_button1_label, page4_button1_command_once, page4_button1_command_continue;
string page4_button2_label, page4_button2_command_once, page4_button2_command_continue;
string page4_button3_label, page4_button3_command_once, page4_button3_command_continue;
string page4_button4_label, page4_button4_command_once, page4_button4_command_continue;
string page4_button5_label, page4_button5_command_once, page4_button5_command_continue;
string page4_button6_label, page4_button6_command_once, page4_button6_command_continue;
string page4_button7_label, page4_button7_command_once, page4_button7_command_continue;
string page4_button8_label, page4_button8_command_once, page4_button8_command_continue;
string page4_button9_label, page4_button9_command_once, page4_button9_command_continue;
string page4_button10_label, page4_button10_command_once, page4_button10_command_continue;
string page4_button11_label, page4_button11_command_once, page4_button11_command_continue;
string page4_button12_label, page4_button12_command_once, page4_button12_command_continue;




XPLMCommandRef Button1LabelCmd = NULL, Button1CommandOnceCmd = NULL, Button1CommandContinueCmd = NULL;
XPLMCommandRef Button2LabelCmd = NULL, Button2CommandOnceCmd = NULL, Button2CommandContinueCmd = NULL;
XPLMCommandRef Button3LabelCmd = NULL, Button3CommandOnceCmd = NULL, Button3CommandContinueCmd = NULL;
XPLMCommandRef Button4LabelCmd = NULL, Button4CommandOnceCmd = NULL, Button4CommandContinueCmd = NULL;
XPLMCommandRef Button5LabelCmd = NULL, Button5CommandOnceCmd = NULL, Button5CommandContinueCmd = NULL;
XPLMCommandRef Button6LabelCmd = NULL, Button6CommandOnceCmd = NULL, Button6CommandContinueCmd = NULL;
XPLMCommandRef Button7LabelCmd = NULL, Button7CommandOnceCmd = NULL, Button7CommandContinueCmd = NULL;
XPLMCommandRef Button8LabelCmd = NULL, Button8CommandOnceCmd = NULL, Button8CommandContinueCmd = NULL;
XPLMCommandRef Button9LabelCmd = NULL, Button9CommandOnceCmd = NULL, Button9CommandContinueCmd = NULL;
XPLMCommandRef Button10LabelCmd = NULL, Button10CommandOnceCmd = NULL, Button10CommandContinueCmd = NULL;
XPLMCommandRef Button11LabelCmd = NULL, Button11CommandOnceCmd = NULL, Button11CommandContinueCmd = NULL;
XPLMCommandRef Button12LabelCmd = NULL, Button12CommandOnceCmd = NULL, Button12CommandContinueCmd = NULL;



XPLMCommandRef Page1_Button1LabelCmd = NULL, Page1_Button1CommandOnceCmd = NULL, Page1_Button1CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button2LabelCmd = NULL, Page1_Button2CommandOnceCmd = NULL, Page1_Button2CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button3LabelCmd = NULL, Page1_Button3CommandOnceCmd = NULL, Page1_Button3CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button4LabelCmd = NULL, Page1_Button4CommandOnceCmd = NULL, Page1_Button4CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button5LabelCmd = NULL, Page1_Button5CommandOnceCmd = NULL, Page1_Button5CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button6LabelCmd = NULL, Page1_Button6CommandOnceCmd = NULL, Page1_Button6CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button7LabelCmd = NULL, Page1_Button7CommandOnceCmd = NULL, Page1_Button7CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button8LabelCmd = NULL, Page1_Button8CommandOnceCmd = NULL, Page1_Button8CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button9LabelCmd = NULL, Page1_Button9CommandOnceCmd = NULL, Page1_Button9CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button10LabelCmd = NULL, Page1_Button10CommandOnceCmd = NULL, Page1_Button10CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button11LabelCmd = NULL, Page1_Button11CommandOnceCmd = NULL, Page1_Button11CommandContinueCmd = NULL;
XPLMCommandRef Page1_Button12LabelCmd = NULL, Page1_Button12CommandOnceCmd = NULL, Page1_Button12CommandContinueCmd = NULL;


XPLMCommandRef Page2_Button1LabelCmd = NULL, Page2_Button1CommandOnceCmd = NULL, Page2_Button1CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button2LabelCmd = NULL, Page2_Button2CommandOnceCmd = NULL, Page2_Button2CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button3LabelCmd = NULL, Page2_Button3CommandOnceCmd = NULL, Page2_Button3CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button4LabelCmd = NULL, Page2_Button4CommandOnceCmd = NULL, Page2_Button4CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button5LabelCmd = NULL, Page2_Button5CommandOnceCmd = NULL, Page2_Button5CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button6LabelCmd = NULL, Page2_Button6CommandOnceCmd = NULL, Page2_Button6CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button7LabelCmd = NULL, Page2_Button7CommandOnceCmd = NULL, Page2_Button7CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button8LabelCmd = NULL, Page2_Button8CommandOnceCmd = NULL, Page2_Button8CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button9LabelCmd = NULL, Page2_Button9CommandOnceCmd = NULL, Page2_Button9CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button10LabelCmd = NULL, Page2_Button10CommandOnceCmd = NULL, Page2_Button10CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button11LabelCmd = NULL, Page2_Button11CommandOnceCmd = NULL, Page2_Button11CommandContinueCmd = NULL;
XPLMCommandRef Page2_Button12LabelCmd = NULL, Page2_Button12CommandOnceCmd = NULL, Page2_Button12CommandContinueCmd = NULL;


XPLMCommandRef Page3_Button1LabelCmd = NULL, Page3_Button1CommandOnceCmd = NULL, Page3_Button1CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button2LabelCmd = NULL, Page3_Button2CommandOnceCmd = NULL, Page3_Button2CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button3LabelCmd = NULL, Page3_Button3CommandOnceCmd = NULL, Page3_Button3CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button4LabelCmd = NULL, Page3_Button4CommandOnceCmd = NULL, Page3_Button4CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button5LabelCmd = NULL, Page3_Button5CommandOnceCmd = NULL, Page3_Button5CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button6LabelCmd = NULL, Page3_Button6CommandOnceCmd = NULL, Page3_Button6CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button7LabelCmd = NULL, Page3_Button7CommandOnceCmd = NULL, Page3_Button7CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button8LabelCmd = NULL, Page3_Button8CommandOnceCmd = NULL, Page3_Button8CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button9LabelCmd = NULL, Page3_Button9CommandOnceCmd = NULL, Page3_Button9CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button10LabelCmd = NULL, Page3_Button10CommandOnceCmd = NULL, Page3_Button10CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button11LabelCmd = NULL, Page3_Button11CommandOnceCmd = NULL, Page3_Button11CommandContinueCmd = NULL;
XPLMCommandRef Page3_Button12LabelCmd = NULL, Page3_Button12CommandOnceCmd = NULL, Page3_Button12CommandContinueCmd = NULL;


XPLMCommandRef Page4_Button1LabelCmd = NULL, Page4_Button1CommandOnceCmd = NULL, Page4_Button1CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button2LabelCmd = NULL, Page4_Button2CommandOnceCmd = NULL, Page4_Button2CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button3LabelCmd = NULL, Page4_Button3CommandOnceCmd = NULL, Page4_Button3CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button4LabelCmd = NULL, Page4_Button4CommandOnceCmd = NULL, Page4_Button4CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button5LabelCmd = NULL, Page4_Button5CommandOnceCmd = NULL, Page4_Button5CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button6LabelCmd = NULL, Page4_Button6CommandOnceCmd = NULL, Page4_Button6CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button7LabelCmd = NULL, Page4_Button7CommandOnceCmd = NULL, Page4_Button7CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button8LabelCmd = NULL, Page4_Button8CommandOnceCmd = NULL, Page4_Button8CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button9LabelCmd = NULL, Page4_Button9CommandOnceCmd = NULL, Page4_Button9CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button10LabelCmd = NULL, Page4_Button10CommandOnceCmd = NULL, Page4_Button10CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button11LabelCmd = NULL, Page4_Button11CommandOnceCmd = NULL, Page4_Button11CommandContinueCmd = NULL;
XPLMCommandRef Page4_Button12LabelCmd = NULL, Page4_Button12CommandOnceCmd = NULL, Page4_Button12CommandContinueCmd = NULL;



int Button1ContinueMode = 0, Button2ContinueMode = 0, Button3ContinueMode = 0;
int Button4ContinueMode = 0, Button5ContinueMode = 0, Button6ContinueMode = 0;
int Button7ContinueMode = 0, Button8ContinueMode = 0, Button9ContinueMode = 0;
int Button10ContinueMode = 0, Button11ContinueMode = 0, Button12ContinueMode = 0;



int Page1_Button1ContinueMode = 0, Page1_Button2ContinueMode = 0, Page1_Button3ContinueMode = 0;
int Page1_Button4ContinueMode = 0, Page1_Button5ContinueMode = 0, Page1_Button6ContinueMode = 0;
int Page1_Button7ContinueMode = 0, Page1_Button8ContinueMode = 0, Page1_Button9ContinueMode = 0;
int Page1_Button10ContinueMode = 0, Page1_Button11ContinueMode = 0, Page1_Button12ContinueMode = 0;


int Page2_Button1ContinueMode = 0, Page2_Button2ContinueMode = 0, Page2_Button3ContinueMode = 0;
int Page2_Button4ContinueMode = 0, Page2_Button5ContinueMode = 0, Page2_Button6ContinueMode = 0;
int Page2_Button7ContinueMode = 0, Page2_Button8ContinueMode = 0, Page2_Button9ContinueMode = 0;
int Page2_Button10ContinueMode = 0, Page2_Button11ContinueMode = 0, Page2_Button12ContinueMode = 0;


int Page3_Button1ContinueMode = 0, Page3_Button2ContinueMode = 0, Page3_Button3ContinueMode = 0;
int Page3_Button4ContinueMode = 0, Page3_Button5ContinueMode = 0, Page3_Button6ContinueMode = 0;
int Page3_Button7ContinueMode = 0, Page3_Button8ContinueMode = 0, Page3_Button9ContinueMode = 0;
int Page3_Button10ContinueMode = 0, Page3_Button11ContinueMode = 0, Page3_Button12ContinueMode = 0;


int Page4_Button1ContinueMode = 0, Page4_Button2ContinueMode = 0, Page4_Button3ContinueMode = 0;
int Page4_Button4ContinueMode = 0, Page4_Button5ContinueMode = 0, Page4_Button6ContinueMode = 0;
int Page4_Button7ContinueMode = 0, Page4_Button8ContinueMode = 0, Page4_Button9ContinueMode = 0;
int Page4_Button10ContinueMode = 0, Page4_Button11ContinueMode = 0, Page4_Button12ContinueMode = 0;





int Xbtn2cmd_menu_container_idx; // The index of our menu item in the Plugins menu
XPLMMenuID Xbtn2cmd_menu_id; // The menu container we'll append all our menu items to
void Xbtn2cmdmenu_handler(void *, void *);

void Xbtn2hide_window();

int page1_mouse_down[12] = {};
int page2_mouse_down[12] = {};
int page3_mouse_down[12] = {};
int page4_mouse_down[12] = {};

int mouse_down[12] = {};

int mouse_down_hide = 0;

int mouse_down_page1 = 0;
int mouse_down_page2 = 0;
int mouse_down_page3 = 0;
int mouse_down_page4 = 0;

int page_number = 1;

PLUGIN_API int XPluginStart(
						char *		outName,
						char *		outSig,
						char *		outDesc)
{
    XPLMDebugString("Xbtn2cmd: ver " VERSION_NUMBER  "\n");
    strcpy(outName, "Xbtn2cmd: ver " VERSION_NUMBER);
    strcpy(outSig, "sparker.example.xbtn2cmdplugin");
    strcpy(outDesc, "A plug-in that demonstrates a window of buttons in VR than can be mapped to commands.");

	// NOTE: We do *not* create the window here, because our plugin initialization
	//       happens *before* VR gets initialized. So, the sim will *always* report
	//       that VR is disabled at this point.
	//       Instead, we'll wait for the first "scenery loaded" message to create
	//       our window. (See XPluginReceiveMessage() below.)

	g_vr_dref = XPLMFindDataRef("sim/graphics/VR/enabled");
    xb2cvr_g_FPS = XPLMFindDataRef("sim/operation/misc/frame_rate_period");

    XPLMGetVersions(&VersionXP, &VersionSDK, &HostID);

    // Create our menu

    Xbtn2cmd_menu_container_idx = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "Xbtn2cmd", 0, 0);
    Xbtn2cmd_menu_id = XPLMCreateMenu("Xbtn2cmd", XPLMFindPluginsMenu(), Xbtn2cmd_menu_container_idx, Xbtn2cmdmenu_handler, NULL);
    XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Toggle Window", (void *)"Menu Item 1", 1);
    XPLMAppendMenuSeparator(Xbtn2cmd_menu_id);
    XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Reload xbtn2cmd.ini", (void *)"Menu Item 2", 1);
    XPLMAppendMenuSeparator(Xbtn2cmd_menu_id);
    XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Reload Window", (void *)"Menu Item 3", 1);
    XPLMAppendMenuSeparator(Xbtn2cmd_menu_id);
    XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Recreate Window", (void *)"Menu Item 4", 1);
    XPLMAppendMenuSeparator(Xbtn2cmd_menu_id);
    XPLMAppendMenuItem(Xbtn2cmd_menu_id, "Hide Window", (void *)"Menu Item 5", 1);

    // Changed your mind? You can destroy the submenu you created with XPLMDestroyMenu(),
    // then remove the "Sample Menu" item from the "Plugins" menu with XPLMRemoveMenuItem().
    //XPLMDestroyMenu(g_menu_id);
    //XPLMRemoveMenuItem(XPLMFindPluginsMenu(), g_menu_container_idx);

	// If this dataref is for some reason not available,
	// we won't be able to move the window to VR anyway,
	// so go ahead an disable us!

    cmdtogglewindow = XPLMCreateCommand("bgood/xbtn2cmd/toggle_window","Toggle Window");
    cmdreloadconfig = XPLMCreateCommand("bgood/xbtn2cmd/reload_config","Reload xbtn2cmd.ini");
    cmdreloadwindow = XPLMCreateCommand("bgood/xbtn2cmd/reload_window","Reload Window");
    cmdrecreatewindow = XPLMCreateCommand("bgood/xbtn2cmd/recreate_window","Recreate Window");

    XPLMRegisterCommandHandler(
                cmdtogglewindow,
                Xbtn2cmdCommandCallback,
                true,
                (void *)TOGGLE_WINDOW_COMMAND);

    XPLMRegisterCommandHandler(
                cmdreloadconfig,
                Xbtn2cmdCommandCallback,
                true,
                (void *)RELOAD_CONFIG_COMMAND);

    XPLMRegisterCommandHandler(
                cmdreloadwindow,
                Xbtn2cmdCommandCallback,
                true,
                (void *)RELOAD_WINDOW_COMMAND);

    XPLMRegisterCommandHandler(
                cmdrecreatewindow,
                Xbtn2cmdCommandCallback,
                true,
                (void *)RECREATE_WINDOW_COMMAND);

	return g_vr_dref != NULL;
}

PLUGIN_API void	XPluginStop(void)
{
	// Since we created the window, we'll be good citizens and clean it up
    XPLMDestroyWindow(xb2cvr_g_window);
    xb2cvr_g_window = NULL;
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void)  { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam)
{
	// We want to wait to create our window until *after* the first scenery load,
	// so that VR will actually be available.

    if (VersionXP > 11200) {

        // We want to wait to create our window until *after* the first scenery load,
        // so that VR will actually be available.
        // if(!xcvr_g_window && inMsg == XPLM_MSG_SCENERY_LOADED)

        if(inMsg == XPLM_MSG_SCENERY_LOADED)
        {
            xb2cvr_create_gui_window();
            process_read_ini_file();
            XPLMSetWindowIsVisible(xb2cvr_g_window,0);
            XPLMDebugString("Xbtn2cmd: inMsg == XPLM_MSG_SCENERY_LOADED\n");
        }

        if(inMsg == XPLM_MSG_WILL_WRITE_PREFS)
        {
            xb2cvr_create_gui_window();
            process_read_ini_file();
            XPLMSetWindowIsVisible(xb2cvr_g_window,0);
            XPLMDebugString("Xbtn2cmd: inMsg == XPLM_MSG_SCENERY_LOADED\n");
        }

        if(inFrom == XPLM_PLUGIN_XPLANE && inMsg == XPLM_MSG_ENTERED_VR)
        {
            XPLMDebugString("Xbtn2cmd: inFrom == XPLM_PLUGIN_XPLANE && inMsg == XPLM_MSG_ENTERED_VR\n");
        }
        else if(inFrom == XPLM_PLUGIN_XPLANE && inMsg == XPLM_MSG_EXITING_VR && XPLMWindowIsInVR(xb2cvr_g_window))
        {
            XPLMDebugString("Xbtn2cmd: inFrom == XPLM_PLUGIN_XPLANE && inMsg == XPLM_MSG_EXITING_VR && XPLMWindowIsInVR(xb2cvr_g_window\n");
        }
    }
}


void xb2cvr_create_gui_window() {

    vr_is_enabled = XPLMGetDatai(g_vr_dref);
    sprintf(scratch_buffer, "Xbtn2cmd:In xb2cvr_create_gui_window() function vr_is_enabled = %d\n", vr_is_enabled);
    XPLMDebugString(scratch_buffer);

    if (xb2cvr_g_window == NULL) {
        XPLMDebugString("Xbtn2cmd: xcvr_g_window == NULL\n");
        // We're not guaranteed that the main monitor's lower left is at (0, 0)...
        // we'll need to query for the global desktop bounds!
        int xb2cvr_global_desktop_bounds[4]; // left, bottom, right, top
        XPLMGetScreenBoundsGlobal(&xb2cvr_global_desktop_bounds[0], &xb2cvr_global_desktop_bounds[3], &xb2cvr_global_desktop_bounds[2], &xb2cvr_global_desktop_bounds[1]);

        XPLMCreateWindow_t params;
        params.structSize = sizeof(params);
        params.left = xb2cvr_global_desktop_bounds[0] + 50;
        params.bottom = xb2cvr_global_desktop_bounds[1] + 100;
        params.right = xb2cvr_global_desktop_bounds[0] + 600;
        params.top = xb2cvr_global_desktop_bounds[1] + 250;
        params.visible = 1;
        params.drawWindowFunc = xb2cvr_draw;
        params.handleMouseClickFunc = xb2cvr_handle_mouse;
        params.handleRightClickFunc = xb2cvr_dummy_mouse_handler;
        params.handleMouseWheelFunc = xb2cvr_dummy_wheel_handler;
        params.handleKeyFunc = xb2cvr_dummy_key_handler;
        params.handleCursorFunc = xb2cvr_dummy_cursor_status_handler;
        params.refcon = NULL;
        params.layer = xplm_WindowLayerFloatingWindows;
        if (vr_is_enabled) {
            params.decorateAsFloatingWindow = xplm_WindowDecorationSelfDecorated;
        }
        else {
            params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
        }

        xb2cvr_g_window = XPLMCreateWindowEx(&params);

        sprintf(scratch_buffer, "Xbtn2cmd: xb2cvr_create_gui_window vr_is_enabled = %d\n", vr_is_enabled);
        XPLMDebugString(scratch_buffer);
        XPLMSetWindowPositioningMode(xb2cvr_g_window, vr_is_enabled ? xplm_WindowVR : xplm_WindowPositionFree, -1);
        g_in_vr = vr_is_enabled;

        XPLMSetWindowResizingLimits(xb2cvr_g_window, 550, 270, 700, 900); // Limit resizing our window: maintain a minimum width/height of 200 boxels and a max width/height of 500

        XPLMSetWindowTitle(xb2cvr_g_window, "Xbtn2cmd     Buttons 2 Commands");
    }
    else {
        XPLMDebugString("Xbtn2cmd: xb2cvr_g_window NOT == NULL\n");
        XPLMSetWindowIsVisible(xb2cvr_g_window,1);
        XPLMSetWindowPositioningMode(xb2cvr_g_window, vr_is_enabled ? xplm_WindowVR : xplm_WindowPositionFree, -1);
    }
}


// Menu handler

void Xbtn2cmdmenu_handler(void * in_menu_ref, void * in_item_ref)
{
    if(!strcmp((const char *)in_item_ref, "Menu Item 1"))
    {
        if (XPLMGetWindowIsVisible(xb2cvr_g_window)) {
            XPLMSetWindowIsVisible(xb2cvr_g_window,0);
        }
        else {
            XPLMSetWindowIsVisible(xb2cvr_g_window,1);
        }
        mouse_down_hide = 0;
        mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
        mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
        mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
        mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
    }
    else if(!strcmp((const char *)in_item_ref, "Menu Item 2"))
    {
        process_read_ini_file();
    }
    else if(!strcmp((const char *)in_item_ref, "Menu Item 3"))
    {
        process_read_ini_file();
        xb2cvr_create_gui_window();
        mouse_down_hide = 0;
        mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
        mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
        mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
        mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
    }
    else if(!strcmp((const char *)in_item_ref, "Menu Item 4"))
    {
        process_read_ini_file();
        xb2cvr_g_window = NULL;
        xb2cvr_create_gui_window();
        mouse_down_hide = 0;
        mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
        mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
        mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
        mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
    }
    else if(!strcmp((const char *)in_item_ref, "Menu Item 5"))
    {
        XPLMSetWindowIsVisible(xb2cvr_g_window,0);
    }
}

void Xbtn2hide_window()
{
    XPLMSetWindowIsVisible(xb2cvr_g_window,0);
}


int Xbtn2cmdCommandCallback(XPLMCommandRef       inCommand,
                      XPLMCommandPhase     inPhase,
                      void *               inRefcon)
{
    (void) inCommand;
    //(void) inPhase;
    //(void) inRefcon;

    if (inPhase == xplm_CommandBegin) {
        switch((intptr_t)inRefcon){
        case TOGGLE_WINDOW_COMMAND:
            if (XPLMGetWindowIsVisible(xb2cvr_g_window)) {
                XPLMSetWindowIsVisible(xb2cvr_g_window,0);
            }
            else {
                XPLMSetWindowIsVisible(xb2cvr_g_window,1);
            }
            mouse_down_hide = 0;
            mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
            mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
            mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
            mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
            break;
        case RELOAD_CONFIG_COMMAND:
            process_read_ini_file();
            break;
        case RELOAD_WINDOW_COMMAND:
            process_read_ini_file();
            xb2cvr_create_gui_window();
            mouse_down_hide = 0;
            mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
            mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
            mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
            mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
            break;
        case RECREATE_WINDOW_COMMAND:
            process_read_ini_file();
            xb2cvr_g_window = NULL;
            xb2cvr_create_gui_window();
            mouse_down_hide = 0;
            mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
            mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
            mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
            mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;
            break;
        }
    }

    return 1;
}
