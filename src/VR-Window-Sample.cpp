// Downloaded from https://developer.x-plane.com/code-sample/vr-window-sample/

#include "XPLMDisplay.h"    // for window creation and manipulation
#include "XPLMGraphics.h"   // for window drawing
#include "XPLMDataAccess.h" // for the VR dataref
#include "XPLMPlugin.h"     // for XPLM_MSG_SCENERY_LOADED message
#include <string.h>
#if IBM
	#include <windows.h>
#endif
#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#ifndef XPLM301
	#error This is made to be compiled against the XPLM301 SDK
#endif

static XPLMWindowID	g_window;

void				draw(XPLMWindowID in_window_id, void * in_refcon);
int					handle_mouse(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon);

int					dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon) { return 0; }
XPLMCursorStatus	dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void * in_refcon) { return xplm_CursorDefault; }
int					dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void * in_refcon) { return 0; }
void				dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void * in_refcon, int losing_focus) { }

XPLMDataRef g_vr_dref;
static bool g_in_vr = false;
static float g_vr_button_lbrt[4]; // left, bottom, right, top

static int	coord_in_rect(float x, float y, float * bounds_lbrt)  { return ((x >= bounds_lbrt[0]) && (x < bounds_lbrt[2]) && (y < bounds_lbrt[3]) && (y >= bounds_lbrt[1])); }


PLUGIN_API int XPluginStart(
						char *		outName,
						char *		outSig,
						char *		outDesc)
{
	strcpy(outName, "VRSamplePlugin");
	strcpy(outSig, "xpsdk.examples.vrsampleplugin");
	strcpy(outDesc, "A test plug-in that demonstrates moving a window into VR.");

	// NOTE: We do *not* create the window here, because our plugin initialization
	//       happens *before* VR gets initialized. So, the sim will *always* report
	//       that VR is disabled at this point.
	//       Instead, we'll wait for the first "scenery loaded" message to create
	//       our window. (See XPluginReceiveMessage() below.)

	g_vr_dref = XPLMFindDataRef("sim/graphics/VR/enabled");
	
	// If this dataref is for some reason not available,
	// we won't be able to move the window to VR anyway,
	// so go ahead an disable us!
	return g_vr_dref != NULL;
}

PLUGIN_API void	XPluginStop(void)
{
	// Since we created the window, we'll be good citizens and clean it up
	XPLMDestroyWindow(g_window);
	g_window = NULL;
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void)  { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int msg, void * inParam)
{
	// We want to wait to create our window until *after* the first scenery load,
	// so that VR will actually be available.
	if(!g_window && msg == XPLM_MSG_SCENERY_LOADED)
	{
		// We're not guaranteed that the main monitor's lower left is at (0, 0)...
		// we'll need to query for the global desktop bounds!
		int global_desktop_bounds[4]; // left, bottom, right, top
		XPLMGetScreenBoundsGlobal(&global_desktop_bounds[0], &global_desktop_bounds[3], &global_desktop_bounds[2], &global_desktop_bounds[1]);
		
		XPLMCreateWindow_t params;
		params.structSize = sizeof(params);
		params.left = global_desktop_bounds[0] + 50;
		params.bottom = global_desktop_bounds[1] + 150;
		params.right = global_desktop_bounds[0] + 350;
		params.top = global_desktop_bounds[1] + 450;
		params.visible = 1;
		params.drawWindowFunc = draw;
		params.handleMouseClickFunc = handle_mouse;
		params.handleRightClickFunc = dummy_mouse_handler;
		params.handleMouseWheelFunc = dummy_wheel_handler;
		params.handleKeyFunc = dummy_key_handler;
		params.handleCursorFunc = dummy_cursor_status_handler;
		params.refcon = NULL;
		params.layer = xplm_WindowLayerFloatingWindows;
		params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
		
		g_window = XPLMCreateWindowEx(&params);
		
		const int vr_is_enabled = XPLMGetDatai(g_vr_dref);
		XPLMSetWindowPositioningMode(g_window, vr_is_enabled ? xplm_WindowVR : xplm_WindowPositionFree, -1);
		g_in_vr = vr_is_enabled;
		
		XPLMSetWindowResizingLimits(g_window, 200, 200, 500, 500); // Limit resizing our window: maintain a minimum width/height of 200 boxels and a max width/height of 500
		XPLMSetWindowTitle(g_window, "Sample VR Window");
	}
}

void	draw(XPLMWindowID in_window_id, void * in_refcon)
{
	char scratch_buffer[150];
	float col_white[] = {1.0, 1.0, 1.0};

	XPLMSetGraphicsState(
			0 /* no fog */,
			0 /* 0 texture units */,
			0 /* no lighting */,
			0 /* no alpha testing */,
			1 /* do alpha blend */,
			1 /* do depth testing */,
			0 /* no depth writing */
	);

	// We draw our rudimentary button boxes based on the height of the button text
	int char_height;
	XPLMGetFontDimensions(xplmFont_Proportional, NULL, &char_height, NULL);

	int l, t, r, b;
	XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);

	const int vr_is_enabled = XPLMGetDatai(g_vr_dref);
	if(vr_is_enabled)
	{
		// Draw the VR toggle button
		const char * btn_label = "Toggle VR";
		
		// Position the button in the upper left of the window (sized to fit the button text)
		g_vr_button_lbrt[0] = l + 10;
		g_vr_button_lbrt[3] = t - 15;
		g_vr_button_lbrt[2] = g_vr_button_lbrt[0] + XPLMMeasureString(xplmFont_Proportional, btn_label, strlen(btn_label)); // *just* wide enough to fit the button text
		g_vr_button_lbrt[1] = g_vr_button_lbrt[3] - (1.25f * char_height); // a bit taller than the button text
		
		// Draw the box around our rudimentary button
		float green[] = {0.0, 1.0, 0.0, 1.0};
		glColor4fv(green);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2i(g_vr_button_lbrt[0], g_vr_button_lbrt[3]);
			glVertex2i(g_vr_button_lbrt[2], g_vr_button_lbrt[3]);
			glVertex2i(g_vr_button_lbrt[2], g_vr_button_lbrt[1]);
			glVertex2i(g_vr_button_lbrt[0], g_vr_button_lbrt[1]);
		}
		glEnd();
		
		// Draw the button text (pop in/pop out)
		XPLMDrawString(col_white, g_vr_button_lbrt[0], g_vr_button_lbrt[1] + 4, (char *)btn_label, NULL, xplmFont_Proportional);
	}
	else // Draw some text to say VR isn't available
	{
		char * line1 = "VR must be enabled before you";
		char * line2 = "can toggle this window into VR.";
		XPLMDrawString(col_white, l, t - 2 * char_height, line1, NULL, xplmFont_Proportional);
		XPLMDrawString(col_white, l, t - 4 * char_height, line2, NULL, xplmFont_Proportional);
	}
}

int	handle_mouse(XPLMWindowID in_window_id, int x, int y, XPLMMouseStatus mouse_status, void * in_refcon)
{
	if(mouse_status == xplm_MouseDown)
	{
		if(!XPLMIsWindowInFront(in_window_id))
		{
			XPLMBringWindowToFront(in_window_id);
		}
		else
		{
			const int vr_is_enabled = XPLMGetDatai(g_vr_dref);
			if(vr_is_enabled && coord_in_rect(x, y, g_vr_button_lbrt)) // user clicked the "toggle VR mode" button
			{
				XPLMSetWindowPositioningMode(in_window_id, g_in_vr ? xplm_WindowPositionFree : xplm_WindowVR, 0);
				g_in_vr = !g_in_vr;
			}
		}
	}
	return 1;
}


