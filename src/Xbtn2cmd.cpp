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



#define VERSION_NUMBER "1.00 build " __DATE__ " " __TIME__

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
	#include <GL/gl.h>
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


string button1_label, button1_command;
string button2_label, button2_command;
string button3_label, button3_command;
string button4_label, button4_command;
string button5_label, button5_command;
string button6_label, button6_command;
string button7_label, button7_command;
string button8_label, button8_command;
string button9_label, button9_command;
string button10_label, button10_command;
string button11_label, button11_command;
string button12_label, button12_command;


XPLMCommandRef Button1LabelCmd = NULL, Button1CommandCmd = NULL;
XPLMCommandRef Button2LabelCmd = NULL, Button2CommandCmd = NULL;
XPLMCommandRef Button3LabelCmd = NULL, Button3CommandCmd = NULL;
XPLMCommandRef Button4LabelCmd = NULL, Button4CommandCmd = NULL;
XPLMCommandRef Button5LabelCmd = NULL, Button5CommandCmd = NULL;
XPLMCommandRef Button6LabelCmd = NULL, Button6CommandCmd = NULL;
XPLMCommandRef Button7LabelCmd = NULL, Button7CommandCmd = NULL;
XPLMCommandRef Button8LabelCmd = NULL, Button8CommandCmd = NULL;
XPLMCommandRef Button9LabelCmd = NULL, Button9CommandCmd = NULL;
XPLMCommandRef Button10LabelCmd = NULL, Button10CommandCmd = NULL;
XPLMCommandRef Button11LabelCmd = NULL, Button11CommandCmd = NULL;
XPLMCommandRef Button12LabelCmd = NULL, Button12CommandCmd = NULL;


void Xbtn2cmdMenuHandler(void *, void *);
int  Xbtn2cmdMenuItem;

XPLMMenuID  Xbtn2cmdMenu;
XPLMMenuID  ConfigMenuId;


PLUGIN_API int XPluginStart(
						char *		outName,
						char *		outSig,
						char *		outDesc)
{
    int ConfigSubMenuItem;

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

    Xbtn2cmdMenuItem = XPLMAppendMenuItem(
                XPLMFindPluginsMenu(),
                "Xbtn2cmd",
                 NULL,
                 1);

     Xbtn2cmdMenu = XPLMCreateMenu(
                 "Xsaitekpanels",
                 XPLMFindPluginsMenu(),
                 Xbtn2cmdMenuItem,
                 Xbtn2cmdMenuHandler,
                 (void *)0);

     ConfigSubMenuItem = XPLMAppendMenuItem(
             Xbtn2cmdMenu,
             "xbtn2cmd.ini",
             NULL,
             1);

     ConfigMenuId = XPLMCreateMenu(
             "xbtn2cmd.ini",
             Xbtn2cmdMenu,
             ConfigSubMenuItem,
             Xbtn2cmdMenuHandler,
             (void *)1);

      XPLMClearAllMenuItems(ConfigMenuId);
      XPLMAppendMenuItem(ConfigMenuId, "Reload xbtn2cmd.ini", (void *) "TRUE", 1);

	
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
        }

        if(inMsg == XPLM_MSG_WILL_WRITE_PREFS)
        {
            xb2cvr_create_gui_window();
            process_read_ini_file();
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
        params.right = xb2cvr_global_desktop_bounds[0] + 550;
        params.top = xb2cvr_global_desktop_bounds[1] + 400;
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

        XPLMSetWindowResizingLimits(xb2cvr_g_window, 200, 200, 700, 900); // Limit resizing our window: maintain a minimum width/height of 200 boxels and a max width/height of 500

        XPLMSetWindowTitle(xb2cvr_g_window, "Xbtn2cmd VR Window"); }

    else {
        XPLMDebugString("Xchecklist: xcvr_g_window not == NULL\n");
        XPLMSetWindowIsVisible(xb2cvr_g_window,1);
        XPLMSetWindowPositioningMode(xb2cvr_g_window, vr_is_enabled ? xplm_WindowVR : xplm_WindowPositionFree, -1);
    }
}


// Menu handler

void Xbtn2cmdMenuHandler(void * inMenuRef, void * inItemRef)
{

    if((intptr_t)inMenuRef == 1){
         if (strcmp((char *) inItemRef, "TRUE") == 0) {
             xb2cvr_g_window = NULL;
             xb2cvr_create_gui_window();
             process_read_ini_file();

         }

    }

    return;
}
