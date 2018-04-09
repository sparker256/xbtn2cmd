// *********************************************************
//
//     Xbtn2cmd Plugin
//
//     William Good
//
//     A plugin to create a window of buttons in VR
//     that can be mapped to commands.
//
//     Supporting  X-Plane 11.20b3+
//
// *********************************************************



#define VERSION_NUMBER "1.05 build " __DATE__ " " __TIME__

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

char scratch_buffer[150];


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


int Button1ContinueMode = 0, Button2ContinueMode = 0, Button3ContinueMode = 0;
int Button4ContinueMode = 0, Button5ContinueMode = 0, Button6ContinueMode = 0;
int Button7ContinueMode = 0, Button8ContinueMode = 0, Button9ContinueMode = 0;
int Button10ContinueMode = 0, Button11ContinueMode = 0, Button12ContinueMode = 0;



int Xbtn2cmd_menu_container_idx; // The index of our menu item in the Plugins menu
XPLMMenuID Xbtn2cmd_menu_id; // The menu container we'll append all our menu items to
void Xbtn2cmdmenu_handler(void *, void *);


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
        }

        if(inMsg == XPLM_MSG_WILL_WRITE_PREFS)
        {
            xb2cvr_create_gui_window();
            process_read_ini_file();
            XPLMSetWindowIsVisible(xb2cvr_g_window,0);
        }
    }

}


void xb2cvr_create_gui_window() {

    vr_is_enabled = XPLMGetDatai(g_vr_dref);
    sprintf(scratch_buffer, "Xchecklist:In xcvr_create_gui_window() function vr_is_enabled = %d\n", vr_is_enabled);
    XPLMDebugString(scratch_buffer);
    // xcDebug("Xchecklist:In xcvr_create_gui_window() function vr_is_enabled = %d\n", vr_is_enabled);

    if (xb2cvr_g_window==NULL) {
        XPLMDebugString("Xchecklist: xcvr_g_window==NULL\n");
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
        params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;

        xb2cvr_g_window = XPLMCreateWindowEx(&params);

        // vr_is_enabled = XPLMGetDatai(g_vr_dref);
        // xcDebug("Xchecklist: xcvr_create_gui_window vr_is_enabled = %d\n", vr_is_enabled);
        sprintf(scratch_buffer, "Xchecklist: xcvr_create_gui_window vr_is_enabled = %d\n", vr_is_enabled);
        XPLMDebugString(scratch_buffer);
        XPLMSetWindowPositioningMode(xb2cvr_g_window, vr_is_enabled ? xplm_WindowVR : xplm_WindowPositionFree, -1);
        g_in_vr = vr_is_enabled;

        XPLMSetWindowResizingLimits(xb2cvr_g_window, 550, 250, 700, 900); // Limit resizing our window: maintain a minimum width/height of 200 boxels and a max width/height of 500

        XPLMSetWindowTitle(xb2cvr_g_window, "Xbtn2cmd     Buttons 2 Commands"); }

    else {
        XPLMDebugString("Xchecklist: xcvr_g_window not == NULL\n");
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
    }
    else if(!strcmp((const char *)in_item_ref, "Menu Item 2"))
    {
        process_read_ini_file();
    }
    else if(!strcmp((const char *)in_item_ref, "Menu Item 3"))
    {
        process_read_ini_file();
        xb2cvr_create_gui_window();
    }
    else if(!strcmp((const char *)in_item_ref, "Menu Item 4"))
    {
        process_read_ini_file();
        xb2cvr_g_window = NULL;
        xb2cvr_create_gui_window();
    }
    else if(!strcmp((const char *)in_item_ref, "Menu Item 5"))
    {
        XPLMSetWindowIsVisible(xb2cvr_g_window,0);
    }

}
