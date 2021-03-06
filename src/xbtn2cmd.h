#ifndef XBTN2CMD_H
#define XBTN2CMD_H

#include "XPLMMenus.h"
#include "XPLMUtilities.h"
#include "XPStandardWidgets.h"
#include "XPWidgets.h"

#include <string>

using namespace std;

extern int is_popped_out;
extern int was_popped_out;
extern int command_pressed;

extern XPLMDataRef xb2cvr_g_FPS;

extern int vr_is_enabled;

extern int xb2cvr_width; // width of the widget checklist window

extern char scratch_buffer[];

extern string page1_button_label, page2_button_label, page3_button_label,
    page4_button_label;
extern string page5_button_label, page6_button_label, page7_button_label,
    page8_button_label;
extern string page9_button_label, page10_button_label, page11_button_label,
    page12_button_label;


extern string page1_button1_label, page1_button1_command_once,
    page1_button1_command_continue;
extern string page1_button2_label, page1_button2_command_once,
    page1_button2_command_continue;
extern string page1_button3_label, page1_button3_command_once,
    page1_button3_command_continue;
extern string page1_button4_label, page1_button4_command_once,
    page1_button4_command_continue;
extern string page1_button5_label, page1_button5_command_once,
    page1_button5_command_continue;
extern string page1_button6_label, page1_button6_command_once,
    page1_button6_command_continue;
extern string page1_button7_label, page1_button7_command_once,
    page1_button7_command_continue;
extern string page1_button8_label, page1_button8_command_once,
    page1_button8_command_continue;
extern string page1_button9_label, page1_button9_command_once,
    page1_button9_command_continue;
extern string page1_button10_label, page1_button10_command_once,
    page1_button10_command_continue;
extern string page1_button11_label, page1_button11_command_once,
    page1_button11_command_continue;
extern string page1_button12_label, page1_button12_command_once,
    page1_button12_command_continue;

extern string page2_button1_label, page2_button1_command_once,
    page2_button1_command_continue;
extern string page2_button2_label, page2_button2_command_once,
    page2_button2_command_continue;
extern string page2_button3_label, page2_button3_command_once,
    page2_button3_command_continue;
extern string page2_button4_label, page2_button4_command_once,
    page2_button4_command_continue;
extern string page2_button5_label, page2_button5_command_once,
    page2_button5_command_continue;
extern string page2_button6_label, page2_button6_command_once,
    page2_button6_command_continue;
extern string page2_button7_label, page2_button7_command_once,
    page2_button7_command_continue;
extern string page2_button8_label, page2_button8_command_once,
    page2_button8_command_continue;
extern string page2_button9_label, page2_button9_command_once,
    page2_button9_command_continue;
extern string page2_button10_label, page2_button10_command_once,
    page2_button10_command_continue;
extern string page2_button11_label, page2_button11_command_once,
    page2_button11_command_continue;
extern string page2_button12_label, page2_button12_command_once,
    page2_button12_command_continue;

extern string page3_button1_label, page3_button1_command_once,
    page3_button1_command_continue;
extern string page3_button2_label, page3_button2_command_once,
    page3_button2_command_continue;
extern string page3_button3_label, page3_button3_command_once,
    page3_button3_command_continue;
extern string page3_button4_label, page3_button4_command_once,
    page3_button4_command_continue;
extern string page3_button5_label, page3_button5_command_once,
    page3_button5_command_continue;
extern string page3_button6_label, page3_button6_command_once,
    page3_button6_command_continue;
extern string page3_button7_label, page3_button7_command_once,
    page3_button7_command_continue;
extern string page3_button8_label, page3_button8_command_once,
    page3_button8_command_continue;
extern string page3_button9_label, page3_button9_command_once,
    page3_button9_command_continue;
extern string page3_button10_label, page3_button10_command_once,
    page3_button10_command_continue;
extern string page3_button11_label, page3_button11_command_once,
    page3_button11_command_continue;
extern string page3_button12_label, page3_button12_command_once,
    page3_button12_command_continue;

extern string page4_button1_label, page4_button1_command_once,
    page4_button1_command_continue;
extern string page4_button2_label, page4_button2_command_once,
    page4_button2_command_continue;
extern string page4_button3_label, page4_button3_command_once,
    page4_button3_command_continue;
extern string page4_button4_label, page4_button4_command_once,
    page4_button4_command_continue;
extern string page4_button5_label, page4_button5_command_once,
    page4_button5_command_continue;
extern string page4_button6_label, page4_button6_command_once,
    page4_button6_command_continue;
extern string page4_button7_label, page4_button7_command_once,
    page4_button7_command_continue;
extern string page4_button8_label, page4_button8_command_once,
    page4_button8_command_continue;
extern string page4_button9_label, page4_button9_command_once,
    page4_button9_command_continue;
extern string page4_button10_label, page4_button10_command_once,
    page4_button10_command_continue;
extern string page4_button11_label, page4_button11_command_once,
    page4_button11_command_continue;
extern string page4_button12_label, page4_button12_command_once,
    page4_button12_command_continue;

extern string page5_button1_label, page5_button1_command_once,
    page5_button1_command_continue;
extern string page5_button2_label, page5_button2_command_once,
    page5_button2_command_continue;
extern string page5_button3_label, page5_button3_command_once,
    page5_button3_command_continue;
extern string page5_button4_label, page5_button4_command_once,
    page5_button4_command_continue;
extern string page5_button5_label, page5_button5_command_once,
    page5_button5_command_continue;
extern string page5_button6_label, page5_button6_command_once,
    page5_button6_command_continue;
extern string page5_button7_label, page5_button7_command_once,
    page5_button7_command_continue;
extern string page5_button8_label, page5_button8_command_once,
    page5_button8_command_continue;
extern string page5_button9_label, page5_button9_command_once,
    page5_button9_command_continue;
extern string page5_button10_label, page5_button10_command_once,
    page5_button10_command_continue;
extern string page5_button11_label, page5_button11_command_once,
    page5_button11_command_continue;
extern string page5_button12_label, page5_button12_command_once,
    page5_button12_command_continue;

extern string page6_button1_label, page6_button1_command_once,
    page6_button1_command_continue;
extern string page6_button2_label, page6_button2_command_once,
    page6_button2_command_continue;
extern string page6_button3_label, page6_button3_command_once,
    page6_button3_command_continue;
extern string page6_button4_label, page6_button4_command_once,
    page6_button4_command_continue;
extern string page6_button5_label, page6_button5_command_once,
    page6_button5_command_continue;
extern string page6_button6_label, page6_button6_command_once,
    page6_button6_command_continue;
extern string page6_button7_label, page6_button7_command_once,
    page6_button7_command_continue;
extern string page6_button8_label, page6_button8_command_once,
    page6_button8_command_continue;
extern string page6_button9_label, page6_button9_command_once,
    page6_button9_command_continue;
extern string page6_button10_label, page6_button10_command_once,
    page6_button10_command_continue;
extern string page6_button11_label, page6_button11_command_once,
    page6_button11_command_continue;
extern string page6_button12_label, page6_button12_command_once,
    page6_button12_command_continue;

extern string page7_button1_label, page7_button1_command_once,
    page7_button1_command_continue;
extern string page7_button2_label, page7_button2_command_once,
    page7_button2_command_continue;
extern string page7_button3_label, page7_button3_command_once,
    page7_button3_command_continue;
extern string page7_button4_label, page7_button4_command_once,
    page7_button4_command_continue;
extern string page7_button5_label, page7_button5_command_once,
    page7_button5_command_continue;
extern string page7_button6_label, page7_button6_command_once,
    page7_button6_command_continue;
extern string page7_button7_label, page7_button7_command_once,
    page7_button7_command_continue;
extern string page7_button8_label, page7_button8_command_once,
    page7_button8_command_continue;
extern string page7_button9_label, page7_button9_command_once,
    page7_button9_command_continue;
extern string page7_button10_label, page7_button10_command_once,
    page7_button10_command_continue;
extern string page7_button11_label, page7_button11_command_once,
    page7_button11_command_continue;
extern string page7_button12_label, page7_button12_command_once,
    page7_button12_command_continue;

extern string page8_button1_label, page8_button1_command_once,
    page8_button1_command_continue;
extern string page8_button2_label, page8_button2_command_once,
    page8_button2_command_continue;
extern string page8_button3_label, page8_button3_command_once,
    page8_button3_command_continue;
extern string page8_button4_label, page8_button4_command_once,
    page8_button4_command_continue;
extern string page8_button5_label, page8_button5_command_once,
    page8_button5_command_continue;
extern string page8_button6_label, page8_button6_command_once,
    page8_button6_command_continue;
extern string page8_button7_label, page8_button7_command_once,
    page8_button7_command_continue;
extern string page8_button8_label, page8_button8_command_once,
    page8_button8_command_continue;
extern string page8_button9_label, page8_button9_command_once,
    page8_button9_command_continue;
extern string page8_button10_label, page8_button10_command_once,
    page8_button10_command_continue;
extern string page8_button11_label, page8_button11_command_once,
    page8_button11_command_continue;
extern string page8_button12_label, page8_button12_command_once,
    page8_button12_command_continue;


extern string page9_button1_label, page9_button1_command_once,
    page9_button1_command_continue;
extern string page9_button2_label, page9_button2_command_once,
    page9_button2_command_continue;
extern string page9_button3_label, page9_button3_command_once,
    page9_button3_command_continue;
extern string page9_button4_label, page9_button4_command_once,
    page9_button4_command_continue;
extern string page9_button5_label, page9_button5_command_once,
    page9_button5_command_continue;
extern string page9_button6_label, page9_button6_command_once,
    page9_button6_command_continue;
extern string page9_button7_label, page9_button7_command_once,
    page9_button7_command_continue;
extern string page9_button8_label, page9_button8_command_once,
    page9_button8_command_continue;
extern string page9_button9_label, page9_button9_command_once,
    page9_button9_command_continue;
extern string page9_button10_label, page9_button10_command_once,
    page9_button10_command_continue;
extern string page9_button11_label, page9_button11_command_once,
    page9_button11_command_continue;
extern string page9_button12_label, page9_button12_command_once,
    page9_button12_command_continue;
extern string page9_button13_label, page9_button13_command_once,
    page9_button13_command_continue;
extern string page9_button14_label, page9_button14_command_once,
    page9_button14_command_continue;
extern string page9_button15_label, page9_button15_command_once,
    page9_button15_command_continue;
extern string page9_button16_label, page9_button16_command_once,
    page9_button16_command_continue;
extern string page9_button17_label, page9_button17_command_once,
    page9_button17_command_continue;
extern string page9_button18_label, page9_button18_command_once,
    page9_button18_command_continue;
extern string page9_button19_label, page9_button19_command_once,
    page9_button19_command_continue;
extern string page9_button20_label, page9_button20_command_once,
    page9_button20_command_continue;
extern string page9_button21_label, page9_button21_command_once,
    page9_button21_command_continue;
extern string page9_button22_label, page9_button22_command_once,
    page9_button22_command_continue;
extern string page9_button23_label, page9_button23_command_once,
    page9_button23_command_continue;
extern string page9_button24_label, page9_button24_command_once,
    page9_button24_command_continue;


extern string page10_button1_label, page10_button1_command_once,
    page10_button1_command_continue;
extern string page10_button2_label, page10_button2_command_once,
    page10_button2_command_continue;
extern string page10_button3_label, page10_button3_command_once,
    page10_button3_command_continue;
extern string page10_button4_label, page10_button4_command_once,
    page10_button4_command_continue;
extern string page10_button5_label, page10_button5_command_once,
    page10_button5_command_continue;
extern string page10_button6_label, page10_button6_command_once,
    page10_button6_command_continue;
extern string page10_button7_label, page10_button7_command_once,
    page10_button7_command_continue;
extern string page10_button8_label, page10_button8_command_once,
    page10_button8_command_continue;
extern string page10_button9_label, page10_button9_command_once,
    page10_button9_command_continue;
extern string page10_button10_label, page10_button10_command_once,
    page10_button10_command_continue;
extern string page10_button11_label, page10_button11_command_once,
    page10_button11_command_continue;
extern string page10_button12_label, page10_button12_command_once,
    page10_button12_command_continue;
extern string page10_button13_label, page10_button13_command_once,
    page10_button13_command_continue;
extern string page10_button14_label, page10_button14_command_once,
    page10_button14_command_continue;
extern string page10_button15_label, page10_button15_command_once,
    page10_button15_command_continue;
extern string page10_button16_label, page10_button16_command_once,
    page10_button16_command_continue;
extern string page10_button17_label, page10_button17_command_once,
    page10_button17_command_continue;
extern string page10_button18_label, page10_button18_command_once,
    page10_button18_command_continue;
extern string page10_button19_label, page10_button19_command_once,
    page10_button19_command_continue;
extern string page10_button20_label, page10_button20_command_once,
    page10_button20_command_continue;
extern string page10_button21_label, page10_button21_command_once,
    page10_button21_command_continue;
extern string page10_button22_label, page10_button22_command_once,
    page10_button22_command_continue;
extern string page10_button23_label, page10_button23_command_once,
    page10_button23_command_continue;
extern string page10_button24_label, page10_button24_command_once,
    page10_button24_command_continue;


extern string page11_button1_label, page11_button1_command_once,
    page11_button1_command_continue;
extern string page11_button2_label, page11_button2_command_once,
    page11_button2_command_continue;
extern string page11_button3_label, page11_button3_command_once,
    page11_button3_command_continue;
extern string page11_button4_label, page11_button4_command_once,
    page11_button4_command_continue;
extern string page11_button5_label, page11_button5_command_once,
    page11_button5_command_continue;
extern string page11_button6_label, page11_button6_command_once,
    page11_button6_command_continue;
extern string page11_button7_label, page11_button7_command_once,
    page11_button7_command_continue;
extern string page11_button8_label, page11_button8_command_once,
    page11_button8_command_continue;
extern string page11_button9_label, page11_button9_command_once,
    page11_button9_command_continue;
extern string page11_button10_label, page11_button10_command_once,
    page11_button10_command_continue;
extern string page11_button11_label, page11_button11_command_once,
    page11_button11_command_continue;
extern string page11_button12_label, page11_button12_command_once,
    page11_button12_command_continue;
extern string page11_button13_label, page11_button13_command_once,
    page11_button13_command_continue;
extern string page11_button14_label, page11_button14_command_once,
    page11_button14_command_continue;
extern string page11_button15_label, page11_button15_command_once,
    page11_button15_command_continue;
extern string page11_button16_label, page11_button16_command_once,
    page11_button16_command_continue;
extern string page11_button17_label, page11_button17_command_once,
    page11_button17_command_continue;
extern string page11_button18_label, page11_button18_command_once,
    page11_button18_command_continue;
extern string page11_button19_label, page11_button19_command_once,
    page11_button19_command_continue;
extern string page11_button20_label, page11_button20_command_once,
    page11_button20_command_continue;
extern string page11_button21_label, page11_button21_command_once,
    page11_button21_command_continue;
extern string page11_button22_label, page11_button22_command_once,
    page11_button22_command_continue;
extern string page11_button23_label, page11_button23_command_once,
    page11_button23_command_continue;
extern string page11_button24_label, page11_button24_command_once,
    page11_button24_command_continue;


extern string page12_button1_label, page12_button1_command_once,
    page12_button1_command_continue;
extern string page12_button2_label, page12_button2_command_once,
    page12_button2_command_continue;
extern string page12_button3_label, page12_button3_command_once,
    page12_button3_command_continue;
extern string page12_button4_label, page12_button4_command_once,
    page12_button4_command_continue;
extern string page12_button5_label, page12_button5_command_once,
    page12_button5_command_continue;
extern string page12_button6_label, page12_button6_command_once,
    page12_button6_command_continue;
extern string page12_button7_label, page12_button7_command_once,
    page12_button7_command_continue;
extern string page12_button8_label, page12_button8_command_once,
    page12_button8_command_continue;
extern string page12_button9_label, page12_button9_command_once,
    page12_button9_command_continue;
extern string page12_button10_label, page12_button10_command_once,
    page12_button10_command_continue;
extern string page12_button11_label, page12_button11_command_once,
    page12_button11_command_continue;
extern string page12_button12_label, page12_button12_command_once,
    page12_button12_command_continue;
extern string page12_button13_label, page12_button13_command_once,
    page12_button13_command_continue;
extern string page12_button14_label, page12_button14_command_once,
    page12_button14_command_continue;
extern string page12_button15_label, page12_button15_command_once,
    page12_button15_command_continue;
extern string page12_button16_label, page12_button16_command_once,
    page12_button16_command_continue;
extern string page12_button17_label, page12_button17_command_once,
    page12_button17_command_continue;
extern string page12_button18_label, page12_button18_command_once,
    page12_button18_command_continue;
extern string page12_button19_label, page12_button19_command_once,
    page12_button19_command_continue;
extern string page12_button20_label, page12_button20_command_once,
    page12_button20_command_continue;
extern string page12_button21_label, page12_button21_command_once,
    page12_button21_command_continue;
extern string page12_button22_label, page12_button22_command_once,
    page12_button22_command_continue;
extern string page12_button23_label, page12_button23_command_once,
    page12_button23_command_continue;
extern string page12_button24_label, page12_button24_command_once,
    page12_button24_command_continue;


extern XPLMCommandRef Page1_Button1LabelCmd, Page1_Button1CommandOnceCmd,
    Page1_Button1CommandContinueCmd;
extern XPLMCommandRef Page1_Button2LabelCmd, Page1_Button2CommandOnceCmd,
    Page1_Button2CommandContinueCmd;
extern XPLMCommandRef Page1_Button3LabelCmd, Page1_Button3CommandOnceCmd,
    Page1_Button3CommandContinueCmd;
extern XPLMCommandRef Page1_Button4LabelCmd, Page1_Button4CommandOnceCmd,
    Page1_Button4CommandContinueCmd;
extern XPLMCommandRef Page1_Button5LabelCmd, Page1_Button5CommandOnceCmd,
    Page1_Button5CommandContinueCmd;
extern XPLMCommandRef Page1_Button6LabelCmd, Page1_Button6CommandOnceCmd,
    Page1_Button6CommandContinueCmd;
extern XPLMCommandRef Page1_Button7LabelCmd, Page1_Button7CommandOnceCmd,
    Page1_Button7CommandContinueCmd;
extern XPLMCommandRef Page1_Button8LabelCmd, Page1_Button8CommandOnceCmd,
    Page1_Button8CommandContinueCmd;
extern XPLMCommandRef Page1_Button9LabelCmd, Page1_Button9CommandOnceCmd,
    Page1_Button9CommandContinueCmd;
extern XPLMCommandRef Page1_Button10LabelCmd, Page1_Button10CommandOnceCmd,
    Page1_Button10CommandContinueCmd;
extern XPLMCommandRef Page1_Button11LabelCmd, Page1_Button11CommandOnceCmd,
    Page1_Button11CommandContinueCmd;
extern XPLMCommandRef Page1_Button12LabelCmd, Page1_Button12CommandOnceCmd,
    Page1_Button12CommandContinueCmd;

extern XPLMCommandRef Page2_Button1LabelCmd, Page2_Button1CommandOnceCmd,
    Page2_Button1CommandContinueCmd;
extern XPLMCommandRef Page2_Button2LabelCmd, Page2_Button2CommandOnceCmd,
    Page2_Button2CommandContinueCmd;
extern XPLMCommandRef Page2_Button3LabelCmd, Page2_Button3CommandOnceCmd,
    Page2_Button3CommandContinueCmd;
extern XPLMCommandRef Page2_Button4LabelCmd, Page2_Button4CommandOnceCmd,
    Page2_Button4CommandContinueCmd;
extern XPLMCommandRef Page2_Button5LabelCmd, Page2_Button5CommandOnceCmd,
    Page2_Button5CommandContinueCmd;
extern XPLMCommandRef Page2_Button6LabelCmd, Page2_Button6CommandOnceCmd,
    Page2_Button6CommandContinueCmd;
extern XPLMCommandRef Page2_Button7LabelCmd, Page2_Button7CommandOnceCmd,
    Page2_Button7CommandContinueCmd;
extern XPLMCommandRef Page2_Button8LabelCmd, Page2_Button8CommandOnceCmd,
    Page2_Button8CommandContinueCmd;
extern XPLMCommandRef Page2_Button9LabelCmd, Page2_Button9CommandOnceCmd,
    Page2_Button9CommandContinueCmd;
extern XPLMCommandRef Page2_Button10LabelCmd, Page2_Button10CommandOnceCmd,
    Page2_Button10CommandContinueCmd;
extern XPLMCommandRef Page2_Button11LabelCmd, Page2_Button11CommandOnceCmd,
    Page2_Button11CommandContinueCmd;
extern XPLMCommandRef Page2_Button12LabelCmd, Page2_Button12CommandOnceCmd,
    Page2_Button12CommandContinueCmd;

extern XPLMCommandRef Page3_Button1LabelCmd, Page3_Button1CommandOnceCmd,
    Page3_Button1CommandContinueCmd;
extern XPLMCommandRef Page3_Button2LabelCmd, Page3_Button2CommandOnceCmd,
    Page3_Button2CommandContinueCmd;
extern XPLMCommandRef Page3_Button3LabelCmd, Page3_Button3CommandOnceCmd,
    Page3_Button3CommandContinueCmd;
extern XPLMCommandRef Page3_Button4LabelCmd, Page3_Button4CommandOnceCmd,
    Page3_Button4CommandContinueCmd;
extern XPLMCommandRef Page3_Button5LabelCmd, Page3_Button5CommandOnceCmd,
    Page3_Button5CommandContinueCmd;
extern XPLMCommandRef Page3_Button6LabelCmd, Page3_Button6CommandOnceCmd,
    Page3_Button6CommandContinueCmd;
extern XPLMCommandRef Page3_Button7LabelCmd, Page3_Button7CommandOnceCmd,
    Page3_Button7CommandContinueCmd;
extern XPLMCommandRef Page3_Button8LabelCmd, Page3_Button8CommandOnceCmd,
    Page3_Button8CommandContinueCmd;
extern XPLMCommandRef Page3_Button9LabelCmd, Page3_Button9CommandOnceCmd,
    Page3_Button9CommandContinueCmd;
extern XPLMCommandRef Page3_Button10LabelCmd, Page3_Button10CommandOnceCmd,
    Page3_Button10CommandContinueCmd;
extern XPLMCommandRef Page3_Button11LabelCmd, Page3_Button11CommandOnceCmd,
    Page3_Button11CommandContinueCmd;
extern XPLMCommandRef Page3_Button12LabelCmd, Page3_Button12CommandOnceCmd,
    Page3_Button12CommandContinueCmd;

extern XPLMCommandRef Page4_Button1LabelCmd, Page4_Button1CommandOnceCmd,
    Page4_Button1CommandContinueCmd;
extern XPLMCommandRef Page4_Button2LabelCmd, Page4_Button2CommandOnceCmd,
    Page4_Button2CommandContinueCmd;
extern XPLMCommandRef Page4_Button3LabelCmd, Page4_Button3CommandOnceCmd,
    Page4_Button3CommandContinueCmd;
extern XPLMCommandRef Page4_Button4LabelCmd, Page4_Button4CommandOnceCmd,
    Page4_Button4CommandContinueCmd;
extern XPLMCommandRef Page4_Button5LabelCmd, Page4_Button5CommandOnceCmd,
    Page4_Button5CommandContinueCmd;
extern XPLMCommandRef Page4_Button6LabelCmd, Page4_Button6CommandOnceCmd,
    Page4_Button6CommandContinueCmd;
extern XPLMCommandRef Page4_Button7LabelCmd, Page4_Button7CommandOnceCmd,
    Page4_Button7CommandContinueCmd;
extern XPLMCommandRef Page4_Button8LabelCmd, Page4_Button8CommandOnceCmd,
    Page4_Button8CommandContinueCmd;
extern XPLMCommandRef Page4_Button9LabelCmd, Page4_Button9CommandOnceCmd,
    Page4_Button9CommandContinueCmd;
extern XPLMCommandRef Page4_Button10LabelCmd, Page4_Button10CommandOnceCmd,
    Page4_Button10CommandContinueCmd;
extern XPLMCommandRef Page4_Button11LabelCmd, Page4_Button11CommandOnceCmd,
    Page4_Button11CommandContinueCmd;
extern XPLMCommandRef Page4_Button12LabelCmd, Page4_Button12CommandOnceCmd,
    Page4_Button12CommandContinueCmd;

extern XPLMCommandRef Page5_Button1LabelCmd, Page5_Button1CommandOnceCmd,
    Page5_Button1CommandContinueCmd;
extern XPLMCommandRef Page5_Button2LabelCmd, Page5_Button2CommandOnceCmd,
    Page5_Button2CommandContinueCmd;
extern XPLMCommandRef Page5_Button3LabelCmd, Page5_Button3CommandOnceCmd,
    Page5_Button3CommandContinueCmd;
extern XPLMCommandRef Page5_Button4LabelCmd, Page5_Button4CommandOnceCmd,
    Page5_Button4CommandContinueCmd;
extern XPLMCommandRef Page5_Button5LabelCmd, Page5_Button5CommandOnceCmd,
    Page5_Button5CommandContinueCmd;
extern XPLMCommandRef Page5_Button6LabelCmd, Page5_Button6CommandOnceCmd,
    Page5_Button6CommandContinueCmd;
extern XPLMCommandRef Page5_Button7LabelCmd, Page5_Button7CommandOnceCmd,
    Page5_Button7CommandContinueCmd;
extern XPLMCommandRef Page5_Button8LabelCmd, Page5_Button8CommandOnceCmd,
    Page5_Button8CommandContinueCmd;
extern XPLMCommandRef Page5_Button9LabelCmd, Page5_Button9CommandOnceCmd,
    Page5_Button9CommandContinueCmd;
extern XPLMCommandRef Page5_Button10LabelCmd, Page5_Button10CommandOnceCmd,
    Page5_Button10CommandContinueCmd;
extern XPLMCommandRef Page5_Button11LabelCmd, Page5_Button11CommandOnceCmd,
    Page5_Button11CommandContinueCmd;
extern XPLMCommandRef Page5_Button12LabelCmd, Page5_Button12CommandOnceCmd,
    Page5_Button12CommandContinueCmd;

extern XPLMCommandRef Page6_Button1LabelCmd, Page6_Button1CommandOnceCmd,
    Page6_Button1CommandContinueCmd;
extern XPLMCommandRef Page6_Button2LabelCmd, Page6_Button2CommandOnceCmd,
    Page6_Button2CommandContinueCmd;
extern XPLMCommandRef Page6_Button3LabelCmd, Page6_Button3CommandOnceCmd,
    Page6_Button3CommandContinueCmd;
extern XPLMCommandRef Page6_Button4LabelCmd, Page6_Button4CommandOnceCmd,
    Page6_Button4CommandContinueCmd;
extern XPLMCommandRef Page6_Button5LabelCmd, Page6_Button5CommandOnceCmd,
    Page6_Button5CommandContinueCmd;
extern XPLMCommandRef Page6_Button6LabelCmd, Page6_Button6CommandOnceCmd,
    Page6_Button6CommandContinueCmd;
extern XPLMCommandRef Page6_Button7LabelCmd, Page6_Button7CommandOnceCmd,
    Page6_Button7CommandContinueCmd;
extern XPLMCommandRef Page6_Button8LabelCmd, Page6_Button8CommandOnceCmd,
    Page6_Button8CommandContinueCmd;
extern XPLMCommandRef Page6_Button9LabelCmd, Page6_Button9CommandOnceCmd,
    Page6_Button9CommandContinueCmd;
extern XPLMCommandRef Page6_Button10LabelCmd, Page6_Button10CommandOnceCmd,
    Page6_Button10CommandContinueCmd;
extern XPLMCommandRef Page6_Button11LabelCmd, Page6_Button11CommandOnceCmd,
    Page6_Button11CommandContinueCmd;
extern XPLMCommandRef Page6_Button12LabelCmd, Page6_Button12CommandOnceCmd,
    Page6_Button12CommandContinueCmd;

extern XPLMCommandRef Page7_Button1LabelCmd, Page7_Button1CommandOnceCmd,
    Page7_Button1CommandContinueCmd;
extern XPLMCommandRef Page7_Button2LabelCmd, Page7_Button2CommandOnceCmd,
    Page7_Button2CommandContinueCmd;
extern XPLMCommandRef Page7_Button3LabelCmd, Page7_Button3CommandOnceCmd,
    Page7_Button3CommandContinueCmd;
extern XPLMCommandRef Page7_Button4LabelCmd, Page7_Button4CommandOnceCmd,
    Page7_Button4CommandContinueCmd;
extern XPLMCommandRef Page7_Button5LabelCmd, Page7_Button5CommandOnceCmd,
    Page7_Button5CommandContinueCmd;
extern XPLMCommandRef Page7_Button6LabelCmd, Page7_Button6CommandOnceCmd,
    Page7_Button6CommandContinueCmd;
extern XPLMCommandRef Page7_Button7LabelCmd, Page7_Button7CommandOnceCmd,
    Page7_Button7CommandContinueCmd;
extern XPLMCommandRef Page7_Button8LabelCmd, Page7_Button8CommandOnceCmd,
    Page7_Button8CommandContinueCmd;
extern XPLMCommandRef Page7_Button9LabelCmd, Page7_Button9CommandOnceCmd,
    Page7_Button9CommandContinueCmd;
extern XPLMCommandRef Page7_Button10LabelCmd, Page7_Button10CommandOnceCmd,
    Page7_Button10CommandContinueCmd;
extern XPLMCommandRef Page7_Button11LabelCmd, Page7_Button11CommandOnceCmd,
    Page7_Button11CommandContinueCmd;
extern XPLMCommandRef Page7_Button12LabelCmd, Page7_Button12CommandOnceCmd,
    Page7_Button12CommandContinueCmd;

extern XPLMCommandRef Page8_Button1LabelCmd, Page8_Button1CommandOnceCmd,
    Page8_Button1CommandContinueCmd;
extern XPLMCommandRef Page8_Button2LabelCmd, Page8_Button2CommandOnceCmd,
    Page8_Button2CommandContinueCmd;
extern XPLMCommandRef Page8_Button3LabelCmd, Page8_Button3CommandOnceCmd,
    Page8_Button3CommandContinueCmd;
extern XPLMCommandRef Page8_Button4LabelCmd, Page8_Button4CommandOnceCmd,
    Page8_Button4CommandContinueCmd;
extern XPLMCommandRef Page8_Button5LabelCmd, Page8_Button5CommandOnceCmd,
    Page8_Button5CommandContinueCmd;
extern XPLMCommandRef Page8_Button6LabelCmd, Page8_Button6CommandOnceCmd,
    Page8_Button6CommandContinueCmd;
extern XPLMCommandRef Page8_Button7LabelCmd, Page8_Button7CommandOnceCmd,
    Page8_Button7CommandContinueCmd;
extern XPLMCommandRef Page8_Button8LabelCmd, Page8_Button8CommandOnceCmd,
    Page8_Button8CommandContinueCmd;
extern XPLMCommandRef Page8_Button9LabelCmd, Page8_Button9CommandOnceCmd,
    Page8_Button9CommandContinueCmd;
extern XPLMCommandRef Page8_Button10LabelCmd, Page8_Button10CommandOnceCmd,
    Page8_Button10CommandContinueCmd;
extern XPLMCommandRef Page8_Button11LabelCmd, Page8_Button11CommandOnceCmd,
    Page8_Button11CommandContinueCmd;
extern XPLMCommandRef Page8_Button12LabelCmd, Page8_Button12CommandOnceCmd,
    Page8_Button12CommandContinueCmd;


extern XPLMCommandRef Page9_Button1LabelCmd, Page9_Button1CommandOnceCmd,
               Page9_Button1CommandContinueCmd;
extern XPLMCommandRef Page9_Button2LabelCmd, Page9_Button2CommandOnceCmd,
               Page9_Button2CommandContinueCmd;
extern XPLMCommandRef Page9_Button3LabelCmd, Page9_Button3CommandOnceCmd,
               Page9_Button3CommandContinueCmd;
extern XPLMCommandRef Page9_Button4LabelCmd, Page9_Button4CommandOnceCmd,
               Page9_Button4CommandContinueCmd;
extern XPLMCommandRef Page9_Button5LabelCmd, Page9_Button5CommandOnceCmd,
               Page9_Button5CommandContinueCmd;
extern XPLMCommandRef Page9_Button6LabelCmd, Page9_Button6CommandOnceCmd,
               Page9_Button6CommandContinueCmd;
extern XPLMCommandRef Page9_Button7LabelCmd, Page9_Button7CommandOnceCmd,
               Page9_Button7CommandContinueCmd;
extern XPLMCommandRef Page9_Button8LabelCmd, Page9_Button8CommandOnceCmd,
               Page9_Button8CommandContinueCmd;
extern XPLMCommandRef Page9_Button9LabelCmd, Page9_Button9CommandOnceCmd,
               Page9_Button9CommandContinueCmd;
extern XPLMCommandRef Page9_Button10LabelCmd, Page9_Button10CommandOnceCmd,
               Page9_Button10CommandContinueCmd;
extern XPLMCommandRef Page9_Button11LabelCmd, Page9_Button11CommandOnceCmd,
               Page9_Button11CommandContinueCmd;
extern XPLMCommandRef Page9_Button12LabelCmd, Page9_Button12CommandOnceCmd,
               Page9_Button12CommandContinueCmd;
extern XPLMCommandRef Page9_Button13LabelCmd, Page9_Button13CommandOnceCmd,
               Page9_Button13CommandContinueCmd;
extern XPLMCommandRef Page9_Button14LabelCmd, Page9_Button14CommandOnceCmd,
               Page9_Button14CommandContinueCmd;
extern XPLMCommandRef Page9_Button15LabelCmd, Page9_Button15CommandOnceCmd,
               Page9_Button15CommandContinueCmd;
extern XPLMCommandRef Page9_Button16LabelCmd, Page9_Button16CommandOnceCmd,
               Page9_Button16CommandContinueCmd;
extern XPLMCommandRef Page9_Button17LabelCmd, Page9_Button17CommandOnceCmd,
               Page9_Button17CommandContinueCmd;
extern XPLMCommandRef Page9_Button18LabelCmd, Page9_Button18CommandOnceCmd,
               Page9_Button18CommandContinueCmd;
extern XPLMCommandRef Page9_Button19LabelCmd, Page9_Button19CommandOnceCmd,
               Page9_Button19CommandContinueCmd;
extern XPLMCommandRef Page9_Button20LabelCmd, Page9_Button20CommandOnceCmd,
               Page9_Button20CommandContinueCmd;
extern XPLMCommandRef Page9_Button21LabelCmd, Page9_Button21CommandOnceCmd,
               Page9_Button21CommandContinueCmd;
extern XPLMCommandRef Page9_Button22LabelCmd, Page9_Button22CommandOnceCmd,
               Page9_Button22CommandContinueCmd;
extern XPLMCommandRef Page9_Button23LabelCmd, Page9_Button23CommandOnceCmd,
               Page9_Button23CommandContinueCmd;
extern XPLMCommandRef Page9_Button24LabelCmd, Page9_Button24CommandOnceCmd,
               Page9_Button24CommandContinueCmd;


extern XPLMCommandRef Page10_Button1LabelCmd, Page10_Button1CommandOnceCmd,
               Page10_Button1CommandContinueCmd;
extern XPLMCommandRef Page10_Button2LabelCmd, Page10_Button2CommandOnceCmd,
               Page10_Button2CommandContinueCmd;
extern XPLMCommandRef Page10_Button3LabelCmd, Page10_Button3CommandOnceCmd,
               Page10_Button3CommandContinueCmd;
extern XPLMCommandRef Page10_Button4LabelCmd, Page10_Button4CommandOnceCmd,
               Page10_Button4CommandContinueCmd;
extern XPLMCommandRef Page10_Button5LabelCmd, Page10_Button5CommandOnceCmd,
               Page10_Button5CommandContinueCmd;
extern XPLMCommandRef Page10_Button6LabelCmd, Page10_Button6CommandOnceCmd,
               Page10_Button6CommandContinueCmd;
extern XPLMCommandRef Page10_Button7LabelCmd, Page10_Button7CommandOnceCmd,
               Page10_Button7CommandContinueCmd;
extern XPLMCommandRef Page10_Button8LabelCmd, Page10_Button8CommandOnceCmd,
               Page10_Button8CommandContinueCmd;
extern XPLMCommandRef Page10_Button9LabelCmd, Page10_Button9CommandOnceCmd,
               Page10_Button9CommandContinueCmd;
extern XPLMCommandRef Page10_Button10LabelCmd, Page10_Button10CommandOnceCmd,
               Page10_Button10CommandContinueCmd;
extern XPLMCommandRef Page10_Button11LabelCmd, Page10_Button11CommandOnceCmd,
               Page10_Button11CommandContinueCmd;
extern XPLMCommandRef Page10_Button12LabelCmd, Page10_Button12CommandOnceCmd,
               Page10_Button12CommandContinueCmd;
extern XPLMCommandRef Page10_Button13LabelCmd, Page10_Button13CommandOnceCmd,
               Page10_Button13CommandContinueCmd;
extern XPLMCommandRef Page10_Button14LabelCmd, Page10_Button14CommandOnceCmd,
               Page10_Button14CommandContinueCmd;
extern XPLMCommandRef Page10_Button15LabelCmd, Page10_Button15CommandOnceCmd,
               Page10_Button15CommandContinueCmd;
extern XPLMCommandRef Page10_Button16LabelCmd, Page10_Button16CommandOnceCmd,
               Page10_Button16CommandContinueCmd;
extern XPLMCommandRef Page10_Button17LabelCmd, Page10_Button17CommandOnceCmd,
               Page10_Button17CommandContinueCmd;
extern XPLMCommandRef Page10_Button18LabelCmd, Page10_Button18CommandOnceCmd,
               Page10_Button18CommandContinueCmd;
extern XPLMCommandRef Page10_Button19LabelCmd, Page10_Button19CommandOnceCmd,
               Page10_Button19CommandContinueCmd;
extern XPLMCommandRef Page10_Button20LabelCmd, Page10_Button20CommandOnceCmd,
               Page10_Button20CommandContinueCmd;
extern XPLMCommandRef Page10_Button21LabelCmd, Page10_Button21CommandOnceCmd,
               Page10_Button21CommandContinueCmd;
extern XPLMCommandRef Page10_Button22LabelCmd, Page10_Button22CommandOnceCmd,
               Page10_Button22CommandContinueCmd;
extern XPLMCommandRef Page10_Button23LabelCmd, Page10_Button23CommandOnceCmd,
               Page10_Button23CommandContinueCmd;
extern XPLMCommandRef Page10_Button24LabelCmd, Page10_Button24CommandOnceCmd,
               Page10_Button24CommandContinueCmd;






extern XPLMCommandRef Page11_Button1LabelCmd, Page11_Button1CommandOnceCmd,
               Page11_Button1CommandContinueCmd;
extern XPLMCommandRef Page11_Button2LabelCmd, Page11_Button2CommandOnceCmd,
               Page11_Button2CommandContinueCmd;
extern XPLMCommandRef Page11_Button3LabelCmd, Page11_Button3CommandOnceCmd,
               Page11_Button3CommandContinueCmd;
extern XPLMCommandRef Page11_Button4LabelCmd, Page11_Button4CommandOnceCmd,
               Page11_Button4CommandContinueCmd;
extern XPLMCommandRef Page11_Button5LabelCmd, Page11_Button5CommandOnceCmd,
               Page11_Button5CommandContinueCmd;
extern XPLMCommandRef Page11_Button6LabelCmd, Page11_Button6CommandOnceCmd,
               Page11_Button6CommandContinueCmd;
extern XPLMCommandRef Page11_Button7LabelCmd, Page11_Button7CommandOnceCmd,
               Page11_Button7CommandContinueCmd;
extern XPLMCommandRef Page11_Button8LabelCmd, Page11_Button8CommandOnceCmd,
               Page11_Button8CommandContinueCmd;
extern XPLMCommandRef Page11_Button9LabelCmd, Page11_Button9CommandOnceCmd,
               Page11_Button9CommandContinueCmd;
extern XPLMCommandRef Page11_Button10LabelCmd, Page11_Button10CommandOnceCmd,
               Page11_Button10CommandContinueCmd;
extern XPLMCommandRef Page11_Button11LabelCmd, Page11_Button11CommandOnceCmd,
               Page11_Button11CommandContinueCmd;
extern XPLMCommandRef Page11_Button12LabelCmd, Page11_Button12CommandOnceCmd,
               Page11_Button12CommandContinueCmd;
extern XPLMCommandRef Page11_Button13LabelCmd, Page11_Button13CommandOnceCmd,
               Page11_Button13CommandContinueCmd;
extern XPLMCommandRef Page11_Button14LabelCmd, Page11_Button14CommandOnceCmd,
               Page11_Button14CommandContinueCmd;
extern XPLMCommandRef Page11_Button15LabelCmd, Page11_Button15CommandOnceCmd,
               Page11_Button15CommandContinueCmd;
extern XPLMCommandRef Page11_Button16LabelCmd, Page11_Button16CommandOnceCmd,
               Page11_Button16CommandContinueCmd;
extern XPLMCommandRef Page11_Button17LabelCmd, Page11_Button17CommandOnceCmd,
               Page11_Button17CommandContinueCmd;
extern XPLMCommandRef Page11_Button18LabelCmd, Page11_Button18CommandOnceCmd,
               Page11_Button18CommandContinueCmd;
extern XPLMCommandRef Page11_Button19LabelCmd, Page11_Button19CommandOnceCmd,
               Page11_Button19CommandContinueCmd;
extern XPLMCommandRef Page11_Button20LabelCmd, Page11_Button20CommandOnceCmd,
               Page11_Button20CommandContinueCmd;
extern XPLMCommandRef Page11_Button21LabelCmd, Page11_Button21CommandOnceCmd,
               Page11_Button21CommandContinueCmd;
extern XPLMCommandRef Page11_Button22LabelCmd, Page11_Button22CommandOnceCmd,
               Page11_Button22CommandContinueCmd;
extern XPLMCommandRef Page11_Button23LabelCmd, Page11_Button23CommandOnceCmd,
               Page11_Button23CommandContinueCmd;
extern XPLMCommandRef Page11_Button24LabelCmd, Page11_Button24CommandOnceCmd,
               Page11_Button24CommandContinueCmd;


extern XPLMCommandRef Page12_Button1LabelCmd, Page12_Button1CommandOnceCmd,
               Page12_Button1CommandContinueCmd;
extern XPLMCommandRef Page12_Button2LabelCmd, Page12_Button2CommandOnceCmd,
               Page12_Button2CommandContinueCmd;
extern XPLMCommandRef Page12_Button3LabelCmd, Page12_Button3CommandOnceCmd,
               Page12_Button3CommandContinueCmd;
extern XPLMCommandRef Page12_Button4LabelCmd, Page12_Button4CommandOnceCmd,
               Page12_Button4CommandContinueCmd;
extern XPLMCommandRef Page12_Button5LabelCmd, Page12_Button5CommandOnceCmd,
               Page12_Button5CommandContinueCmd;
extern XPLMCommandRef Page12_Button6LabelCmd, Page12_Button6CommandOnceCmd,
               Page12_Button6CommandContinueCmd;
extern XPLMCommandRef Page12_Button7LabelCmd, Page12_Button7CommandOnceCmd,
               Page12_Button7CommandContinueCmd;
extern XPLMCommandRef Page12_Button8LabelCmd, Page12_Button8CommandOnceCmd,
               Page12_Button8CommandContinueCmd;
extern XPLMCommandRef Page12_Button9LabelCmd, Page12_Button9CommandOnceCmd,
               Page12_Button9CommandContinueCmd;
extern XPLMCommandRef Page12_Button10LabelCmd, Page12_Button10CommandOnceCmd,
               Page12_Button10CommandContinueCmd;
extern XPLMCommandRef Page12_Button11LabelCmd, Page12_Button11CommandOnceCmd,
               Page12_Button11CommandContinueCmd;
extern XPLMCommandRef Page12_Button12LabelCmd, Page12_Button12CommandOnceCmd,
               Page12_Button12CommandContinueCmd;
extern XPLMCommandRef Page12_Button13LabelCmd, Page12_Button13CommandOnceCmd,
               Page12_Button13CommandContinueCmd;
extern XPLMCommandRef Page12_Button14LabelCmd, Page12_Button14CommandOnceCmd,
               Page12_Button14CommandContinueCmd;
extern XPLMCommandRef Page12_Button15LabelCmd, Page12_Button15CommandOnceCmd,
               Page12_Button15CommandContinueCmd;
extern XPLMCommandRef Page12_Button16LabelCmd, Page12_Button16CommandOnceCmd,
               Page12_Button16CommandContinueCmd;
extern XPLMCommandRef Page12_Button17LabelCmd, Page12_Button17CommandOnceCmd,
               Page12_Button17CommandContinueCmd;
extern XPLMCommandRef Page12_Button18LabelCmd, Page12_Button18CommandOnceCmd,
               Page12_Button18CommandContinueCmd;
extern XPLMCommandRef Page12_Button19LabelCmd, Page12_Button19CommandOnceCmd,
               Page12_Button19CommandContinueCmd;
extern XPLMCommandRef Page12_Button20LabelCmd, Page12_Button20CommandOnceCmd,
               Page12_Button20CommandContinueCmd;
extern XPLMCommandRef Page12_Button21LabelCmd, Page12_Button21CommandOnceCmd,
               Page12_Button21CommandContinueCmd;
extern XPLMCommandRef Page12_Button22LabelCmd, Page12_Button22CommandOnceCmd,
               Page12_Button22CommandContinueCmd;
extern XPLMCommandRef Page12_Button23LabelCmd, Page12_Button23CommandOnceCmd,
               Page12_Button23CommandContinueCmd;
extern XPLMCommandRef Page12_Button24LabelCmd, Page12_Button24CommandOnceCmd,
               Page12_Button24CommandContinueCmd;


extern XPLMCommandRef g430n1_cdi_cmd, g430n1_chapter_dn_cmd,
    g430n1_chapter_up_cmd, g430n1_clr_cmd;
extern XPLMCommandRef g430n1_coarse_down_cmd, g430n1_coarse_up_cmd,
    g430n1_com_ff_cmd, g430n1_cursor_cmd;
extern XPLMCommandRef g430n1_cvol_cmd, g430n1_direct_cmd, g430n1_ent_cmd,
    g430n1_fine_down_cmd;
extern XPLMCommandRef g430n1_fine_up_cmd, g430n1_fpl_cmd, g430n1_menu_cmd,
    g430n1_msg_cmd;
extern XPLMCommandRef g430n1_nav_com_tog_cmd, g430n1_nav_ff_cmd, g430n1_obs_cmd,
    g430n1_page_dn_cmd;
extern XPLMCommandRef g430n1_page_up_cmd, g430n1_popout_cmd, g430n1_popup_cmd,
    g430n1_proc_cmd;
extern XPLMCommandRef g430n1_vnav_cmd, g430n1_vvol_cmd, g430n1_zoom_in_cmd,
    g430n1_zoom_out_cmd;

extern XPLMCommandRef g430n2_cdi_cmd, g430n2_chapter_dn_cmd,
    g430n2_chapter_up_cmd, g430n2_clr_cmd;
extern XPLMCommandRef g430n2_coarse_down_cmd, g430n2_coarse_up_cmd,
    g430n2_com_ff_cmd, g430n2_cursor_cmd;
extern XPLMCommandRef g430n2_cvol_cmd, g430n2_direct_cmd, g430n2_ent_cmd,
    g430n2_fine_down_cmd;
extern XPLMCommandRef g430n2_fine_up_cmd, g430n2_fpl_cmd, g430n2_menu_cmd,
    g430n2_msg_cmd;
extern XPLMCommandRef g430n2_nav_com_tog_cmd, g430n2_nav_ff_cmd, g430n2_obs_cmd,
    g430n2_page_dn_cmd;
extern XPLMCommandRef g430n2_page_up_cmd, g430n2_popout_cmd, g430n2_popup_cmd,
    g430n2_proc_cmd;
extern XPLMCommandRef g430n2_vnav_cmd, g430n2_vvol_cmd, g430n2_zoom_in_cmd,
    g430n2_zoom_out_cmd;

extern int Page1_Button1ContinueMode, Page1_Button2ContinueMode,
    Page1_Button3ContinueMode;
extern int Page1_Button4ContinueMode, Page1_Button5ContinueMode,
    Page1_Button6ContinueMode;
extern int Page1_Button7ContinueMode, Page1_Button8ContinueMode,
    Page1_Button9ContinueMode;
extern int Page1_Button10ContinueMode, Page1_Button11ContinueMode,
    Page1_Button12ContinueMode;

extern int Page2_Button1ContinueMode, Page2_Button2ContinueMode,
    Page2_Button3ContinueMode;
extern int Page2_Button4ContinueMode, Page2_Button5ContinueMode,
    Page2_Button6ContinueMode;
extern int Page2_Button7ContinueMode, Page2_Button8ContinueMode,
    Page2_Button9ContinueMode;
extern int Page2_Button10ContinueMode, Page2_Button11ContinueMode,
    Page2_Button12ContinueMode;

extern int Page3_Button1ContinueMode, Page3_Button2ContinueMode,
    Page3_Button3ContinueMode;
extern int Page3_Button4ContinueMode, Page3_Button5ContinueMode,
    Page3_Button6ContinueMode;
extern int Page3_Button7ContinueMode, Page3_Button8ContinueMode,
    Page3_Button9ContinueMode;
extern int Page3_Button10ContinueMode, Page3_Button11ContinueMode,
    Page3_Button12ContinueMode;

extern int Page4_Button1ContinueMode, Page4_Button2ContinueMode,
    Page4_Button3ContinueMode;
extern int Page4_Button4ContinueMode, Page4_Button5ContinueMode,
    Page4_Button6ContinueMode;
extern int Page4_Button7ContinueMode, Page4_Button8ContinueMode,
    Page4_Button9ContinueMode;
extern int Page4_Button10ContinueMode, Page4_Button11ContinueMode,
    Page4_Button12ContinueMode;

extern int Page5_Button1ContinueMode, Page5_Button2ContinueMode,
    Page5_Button3ContinueMode;
extern int Page5_Button4ContinueMode, Page5_Button5ContinueMode,
    Page5_Button6ContinueMode;
extern int Page5_Button7ContinueMode, Page5_Button8ContinueMode,
    Page5_Button9ContinueMode;
extern int Page5_Button10ContinueMode, Page5_Button11ContinueMode,
    Page5_Button12ContinueMode;

extern int Page6_Button1ContinueMode, Page6_Button2ContinueMode,
    Page6_Button3ContinueMode;
extern int Page6_Button4ContinueMode, Page6_Button5ContinueMode,
    Page6_Button6ContinueMode;
extern int Page6_Button7ContinueMode, Page6_Button8ContinueMode,
    Page6_Button9ContinueMode;
extern int Page6_Button10ContinueMode, Page6_Button11ContinueMode,
    Page6_Button12ContinueMode;

extern int Page7_Button1ContinueMode, Page7_Button2ContinueMode,
    Page7_Button3ContinueMode;
extern int Page7_Button4ContinueMode, Page7_Button5ContinueMode,
    Page7_Button6ContinueMode;
extern int Page7_Button7ContinueMode, Page7_Button8ContinueMode,
    Page7_Button9ContinueMode;
extern int Page7_Button10ContinueMode, Page7_Button11ContinueMode,
    Page7_Button12ContinueMode;

extern int Page8_Button1ContinueMode, Page8_Button2ContinueMode,
    Page8_Button3ContinueMode;
extern int Page8_Button4ContinueMode, Page8_Button5ContinueMode,
    Page8_Button6ContinueMode;
extern int Page8_Button7ContinueMode, Page8_Button8ContinueMode,
    Page8_Button9ContinueMode;
extern int Page8_Button10ContinueMode, Page8_Button11ContinueMode,
    Page8_Button12ContinueMode;


extern int Page9_Button1ContinueMode, Page9_Button2ContinueMode;
extern int Page9_Button3ContinueMode, Page9_Button4ContinueMode;
extern int Page9_Button5ContinueMode, Page9_Button6ContinueMode;
extern int Page9_Button7ContinueMode, Page9_Button8ContinueMode;
extern int Page9_Button9ContinueMode, Page9_Button10ContinueMode;
extern int Page9_Button11ContinueMode, Page9_Button12ContinueMode;
extern int Page9_Button13ContinueMode, Page9_Button14ContinueMode;
extern int Page9_Button15ContinueMode, Page9_Button16ContinueMode;
extern int Page9_Button17ContinueMode, Page9_Button18ContinueMode;
extern int Page9_Button19ContinueMode, Page9_Button20ContinueMode;
extern int Page9_Button21ContinueMode, Page9_Button22ContinueMode;
extern int Page9_Button23ContinueMode, Page9_Button24ContinueMode;

extern int Page10_Button1ContinueMode, Page10_Button2ContinueMode;
extern int Page10_Button3ContinueMode, Page10_Button4ContinueMode;
extern int Page10_Button5ContinueMode, Page10_Button6ContinueMode;
extern int Page10_Button7ContinueMode, Page10_Button8ContinueMode;
extern int Page10_Button9ContinueMode, Page10_Button10ContinueMode;
extern int Page10_Button11ContinueMode, Page10_Button12ContinueMode;
extern int Page10_Button13ContinueMode, Page10_Button14ContinueMode;
extern int Page10_Button15ContinueMode, Page10_Button16ContinueMode;
extern int Page10_Button17ContinueMode, Page10_Button18ContinueMode;
extern int Page10_Button19ContinueMode, Page10_Button20ContinueMode;
extern int Page10_Button21ContinueMode, Page10_Button22ContinueMode;
extern int Page10_Button23ContinueMode, Page10_Button24ContinueMode;

extern int Page11_Button1ContinueMode, Page11_Button2ContinueMode;
extern int Page11_Button3ContinueMode, Page11_Button4ContinueMode;
extern int Page11_Button5ContinueMode, Page11_Button6ContinueMode;
extern int Page11_Button7ContinueMode, Page11_Button8ContinueMode;
extern int Page11_Button9ContinueMode, Page11_Button10ContinueMode;
extern int Page11_Button11ContinueMode, Page11_Button12ContinueMode;
extern int Page11_Button13ContinueMode, Page11_Button14ContinueMode;
extern int Page11_Button15ContinueMode, Page11_Button16ContinueMode;
extern int Page11_Button17ContinueMode, Page11_Button18ContinueMode;
extern int Page11_Button19ContinueMode, Page11_Button20ContinueMode;
extern int Page11_Button21ContinueMode, Page11_Button22ContinueMode;
extern int Page11_Button23ContinueMode, Page11_Button24ContinueMode;

extern int Page12_Button1ContinueMode, Page12_Button2ContinueMode;
extern int Page12_Button3ContinueMode, Page12_Button4ContinueMode;
extern int Page12_Button5ContinueMode, Page12_Button6ContinueMode;
extern int Page12_Button7ContinueMode, Page12_Button8ContinueMode;
extern int Page12_Button9ContinueMode, Page12_Button10ContinueMode;
extern int Page12_Button11ContinueMode, Page12_Button12ContinueMode;
extern int Page12_Button13ContinueMode, Page12_Button14ContinueMode;
extern int Page12_Button15ContinueMode, Page12_Button16ContinueMode;
extern int Page12_Button17ContinueMode, Page12_Button18ContinueMode;
extern int Page12_Button19ContinueMode, Page12_Button20ContinueMode;
extern int Page12_Button21ContinueMode, Page12_Button22ContinueMode;
extern int Page12_Button23ContinueMode, Page12_Button24ContinueMode;


extern void Xbtn2hide_window();
extern void process_read_ini_file();
extern void process_create_edit_window();
extern void send_delayed_ctrl_c();

extern int mouse_down[];

extern int page1_mouse_down[];
extern int page2_mouse_down[];
extern int page3_mouse_down[];
extern int page4_mouse_down[];
extern int page5_mouse_down[];
extern int page6_mouse_down[];
extern int page7_mouse_down[];
extern int page8_mouse_down[];

extern int mouse_down_hide;
extern int mouse_down_reload;
extern int mouse_down_edit;
extern int mouse_down_ctrl_c;

extern int mouse_down_page1;
extern int mouse_down_page2;
extern int mouse_down_page3;
extern int mouse_down_page4;
extern int mouse_down_page5;
extern int mouse_down_page6;
extern int mouse_down_page7;
extern int mouse_down_page8;
extern int mouse_down_page9;
extern int mouse_down_page10;
extern int mouse_down_page11;
extern int mouse_down_page12;


extern int mouse_down_page13;
extern int mouse_down_page14;

extern int mouse_down_radios;
extern int mouse_down_g430n1;
extern int mouse_down_g430n2;

extern int number0_mouse_down, number1_mouse_down, number2_mouse_down,
    number3_mouse_down;
extern int number4_mouse_down, number5_mouse_down, number6_mouse_down,
    number7_mouse_down;
extern int number8_mouse_down, number9_mouse_down, clear_mouse_down;
extern int com1a_mouse_down, com2a_mouse_down, nav1a_mouse_down,
    nav2a_mouse_down;
extern int com1s_mouse_down, com2s_mouse_down, nav1s_mouse_down,
    nav2s_mouse_down;

extern int adf1a_mouse_down, adf2a_mouse_down;
extern int adf1s_mouse_down, adf2s_mouse_down;

extern int number_mouse_down_value;
extern int number_position;

extern int g_430n1_com_ff_mouse_down, g_430n1_nav_ff_mouse_down,
    g_430n1_fine_down_mouse_down, g_430n1_fine_up_mouse_down;
extern int g_430n1_coarse_down_mouse_down, g_430n1_coarse_up_mouse_down,
    g_430n1_nav_com_tog_mouse_down, g_430n1_cdi_mouse_down;
extern int g_430n1_obs_mouse_down, g_430n1_msg_mouse_down,
    g_430n1_fpl_mouse_down, g_430n1_vnav_mouse_down, g_430n1_proc_mouse_down;
extern int g_430n1_zoom_in_mouse_down, g_430n1_zoom_out_mouse_down,
    g_430n1_direct_mouse_down, g_430n1_menu_mouse_down, g_430n1_clr_mouse_down;
extern int g_430n1_ent_mouse_down, g_430n1_cursor_mouse_down;
extern int g_430n1_page_dn_mouse_down, g_430n1_page_up_mouse_down,
    g_430n1_chapter_dn_mouse_down, g_430n1_chapter_up_mouse_down;

extern int g_430n2_com_ff_mouse_down, g_430n2_nav_ff_mouse_down,
    g_430n2_fine_down_mouse_down, g_430n2_fine_up_mouse_down;
extern int g_430n2_coarse_down_mouse_down, g_430n2_coarse_up_mouse_down,
    g_430n2_nav_com_tog_mouse_down, g_430n2_cdi_mouse_down;
extern int g_430n2_obs_mouse_down, g_430n2_msg_mouse_down,
    g_430n2_fpl_mouse_down, g_430n2_vnav_mouse_down, g_430n2_proc_mouse_down;
extern int g_430n2_zoom_in_mouse_down, g_430n2_zoom_out_mouse_down,
    g_430n2_direct_mouse_down, g_430n2_menu_mouse_down, g_430n2_clr_mouse_down;
extern int g_430n2_ent_mouse_down, g_430n2_cursor_mouse_down;
extern int g_430n2_page_dn_mouse_down, g_430n2_page_up_mouse_down,
    g_430n2_chapter_dn_mouse_down, g_430n2_chapter_up_mouse_down;

extern int page_number;

extern int edit_mode;

extern string search_current_page_label;

extern string search_current_page_button_label;
extern string search_current_page_button_command_once;
extern string search_current_page_button_command_continue;

extern string search_current_page_button_once_label;
extern string search_current_page_button_continue_label;

extern void populate_edit_window();

extern string xbtn2cmdini_path_name;

extern int radio_freq;
extern int radio_freq1;
extern int radio_freq2;
extern int radio_freq3;
extern int radio_freq4;
extern int radio_freq5;
extern int radio_freq6;

extern int radio_com1_actv_freq;
extern int radio_com2_actv_freq;
extern int radio_nav1_actv_freq;
extern int radio_nav2_actv_freq;
extern int radio_adf1_actv_freq;
extern int radio_adf2_actv_freq;

extern int radio_com1_stby_freq;
extern int radio_com2_stby_freq;
extern int radio_nav1_stby_freq;
extern int radio_nav2_stby_freq;
extern int radio_adf1_stby_freq;
extern int radio_adf2_stby_freq;

extern XPLMDataRef XPLM_radio_com1_actv_freq;
extern XPLMDataRef XPLM_radio_com2_actv_freq;
extern XPLMDataRef XPLM_radio_nav1_actv_freq;
extern XPLMDataRef XPLM_radio_nav2_actv_freq;
extern XPLMDataRef XPLM_radio_adf1_actv_freq;
extern XPLMDataRef XPLM_radio_adf2_actv_freq;

extern XPLMDataRef XPLM_radio_com1_stby_freq;
extern XPLMDataRef XPLM_radio_com2_stby_freq;
extern XPLMDataRef XPLM_radio_nav1_stby_freq;
extern XPLMDataRef XPLM_radio_nav2_stby_freq;
extern XPLMDataRef XPLM_radio_adf1_stby_freq;
extern XPLMDataRef XPLM_radio_adf2_stby_freq;

extern int PageNumberValue;
extern int ButtonNumberValue;

#endif
