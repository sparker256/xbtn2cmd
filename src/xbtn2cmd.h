#ifndef XBTN2CMD_H
#define XBTN2CMD_H

#include "XPLMUtilities.h"
#include "XPLMMenus.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"



#include <string>

using namespace std;


extern XPLMDataRef xb2cvr_g_FPS;

extern int vr_is_enabled;

extern int xb2cvr_width; // width of the widget checklist window

extern char scratch_buffer[];

extern string button1_label, button1_command_once, button1_command_continue;
extern string button2_label, button2_command_once, button2_command_continue;
extern string button3_label, button3_command_once, button3_command_continue;
extern string button4_label, button4_command_once, button4_command_continue;
extern string button5_label, button5_command_once, button5_command_continue;
extern string button6_label, button6_command_once, button6_command_continue;
extern string button7_label, button7_command_once, button7_command_continue;
extern string button8_label, button8_command_once, button8_command_continue;
extern string button9_label, button9_command_once, button9_command_continue;
extern string button10_label, button10_command_once, button10_command_continue;
extern string button11_label, button11_command_once, button11_command_continue;
extern string button12_label, button12_command_once, button12_command_continue;


extern XPLMCommandRef Button1LabelCmd, Button1CommandOnceCmd, Button1CommandContinueCmd;
extern XPLMCommandRef Button2LabelCmd, Button2CommandOnceCmd, Button2CommandContinueCmd;
extern XPLMCommandRef Button3LabelCmd, Button3CommandOnceCmd, Button3CommandContinueCmd;
extern XPLMCommandRef Button4LabelCmd, Button4CommandOnceCmd, Button4CommandContinueCmd;
extern XPLMCommandRef Button5LabelCmd, Button5CommandOnceCmd, Button5CommandContinueCmd;
extern XPLMCommandRef Button6LabelCmd, Button6CommandOnceCmd, Button6CommandContinueCmd;
extern XPLMCommandRef Button7LabelCmd, Button7CommandOnceCmd, Button7CommandContinueCmd;
extern XPLMCommandRef Button8LabelCmd, Button8CommandOnceCmd, Button8CommandContinueCmd;
extern XPLMCommandRef Button9LabelCmd, Button9CommandOnceCmd, Button9CommandContinueCmd;
extern XPLMCommandRef Button10LabelCmd, Button10CommandOnceCmd, Button10CommandContinueCmd;
extern XPLMCommandRef Button11LabelCmd, Button11CommandOnceCmd, Button11CommandContinueCmd;
extern XPLMCommandRef Button12LabelCmd, Button12CommandOnceCmd, Button12CommandContinueCmd;


extern int Button1ContinueMode, Button2ContinueMode, Button3ContinueMode;
extern int Button4ContinueMode, Button5ContinueMode, Button6ContinueMode;
extern int Button7ContinueMode, Button8ContinueMode, Button9ContinueMode;
extern int Button10ContinueMode, Button11ContinueMode, Button12ContinueMode;

extern void Xbtn2hide_window();

extern int mouse_down[];
extern int mouse_down_hide;


#endif
