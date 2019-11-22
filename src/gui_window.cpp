#include "XPLMDataAccess.h" // for the VR dataref
#include "XPLMDisplay.h"    // for window creation and manipulation
#include "XPLMGraphics.h"   // for window drawing
#include "XPLMPlugin.h"     // for XPLM_MSG_SCENERY_LOADED message
#include "XPLMUtilities.h"  // for Various utilities
#include <cstdio>
#include <cstring>
#include <vector>

#if IBM
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

#include "xbtn2cmd.h"

static float g_hide_button_lbrt[4];     // left, bottom, right, top
static float g_in_front_button_lbrt[4]; // left, bottom, right, top
static float g_reload_button_lbrt[4];   // left, bottom, right, top
static float g_edit_button_lbrt[4];     // left, bottom, right, top
static float g_ctrl_c_button_lbrt[4];   // left, bottom, right, top

static float g_page1_button_lbrt[4]; // left, bottom, right, top
static float g_page2_button_lbrt[4]; // left, bottom, right, top
static float g_page3_button_lbrt[4]; // left, bottom, right, top
static float g_page4_button_lbrt[4]; // left, bottom, right, top
static float g_page5_button_lbrt[4]; // left, bottom, right, top
static float g_page6_button_lbrt[4]; // left, bottom, right, top
static float g_page7_button_lbrt[4]; // left, bottom, right, top
static float g_page8_button_lbrt[4]; // left, bottom, right, top
static float g_page9_button_lbrt[4]; // left, bottom, right, top
static float g_page10_button_lbrt[4]; // left, bottom, right, top
static float g_page11_button_lbrt[4]; // left, bottom, right, top
static float g_page12_button_lbrt[4]; // left, bottom, right, top

static float g_radios_button_lbrt[4];  // left, bottom, right, top
static float g_g430n1_button_lbrt[4];  // left, bottom, right, top
static float g_g430n2_button_lbrt[4];  // left, bottom, right, top
static float g_g1000n1_button_lbrt[4];  // left, bottom, right, top
static float g_g1000n2_button_lbrt[4];  // left, bottom, right, top
static float g_g1000n3_button_lbrt[4];  // left, bottom, right, top


static float g_button1_lbrt[4];  // left, bottom, right, top
static float g_button2_lbrt[4];  // left, bottom, right, top
static float g_button3_lbrt[4];  // left, bottom, right, top
static float g_button4_lbrt[4];  // left, bottom, right, top
static float g_button5_lbrt[4];  // left, bottom, right, top
static float g_button6_lbrt[4];  // left, bottom, right, top
static float g_button7_lbrt[4];  // left, bottom, right, top
static float g_button8_lbrt[4];  // left, bottom, right, top
static float g_button9_lbrt[4];  // left, bottom, right, top
static float g_button10_lbrt[4]; // left, bottom, right, top
static float g_button11_lbrt[4]; // left, bottom, right, top
static float g_button12_lbrt[4]; // left, bottom, right, top
static float g_button13_lbrt[4];  // left, bottom, right, top
static float g_button14_lbrt[4];  // left, bottom, right, top
static float g_button15_lbrt[4];  // left, bottom, right, top
static float g_button16_lbrt[4];  // left, bottom, right, top
static float g_button17_lbrt[4];  // left, bottom, right, top
static float g_button18_lbrt[4];  // left, bottom, right, top
static float g_button19_lbrt[4];  // left, bottom, right, top
static float g_button20_lbrt[4];  // left, bottom, right, top
static float g_button21_lbrt[4];  // left, bottom, right, top
static float g_button22_lbrt[4]; // left, bottom, right, top
static float g_button23_lbrt[4]; // left, bottom, right, top
static float g_button24_lbrt[4]; // left, bottom, right, top


static float g_number0_button_lbrt[4]; // left, bottom, right, top
static float g_number1_button_lbrt[4]; // left, bottom, right, top
static float g_number2_button_lbrt[4]; // left, bottom, right, top
static float g_number3_button_lbrt[4]; // left, bottom, right, top
static float g_number4_button_lbrt[4]; // left, bottom, right, top
static float g_number5_button_lbrt[4]; // left, bottom, right, top
static float g_number6_button_lbrt[4]; // left, bottom, right, top
static float g_number7_button_lbrt[4]; // left, bottom, right, top
static float g_number8_button_lbrt[4]; // left, bottom, right, top
static float g_number9_button_lbrt[4]; // left, bottom, right, top

static float g_clear_button_lbrt[4]; // left, bottom, right, top
static float g_com1a_button_lbrt[4]; // left, bottom, right, top
static float g_com1s_button_lbrt[4]; // left, bottom, right, top
static float g_com2a_button_lbrt[4]; // left, bottom, right, top
static float g_com2s_button_lbrt[4]; // left, bottom, right, top
static float g_nav1a_button_lbrt[4]; // left, bottom, right, top
static float g_nav1s_button_lbrt[4]; // left, bottom, right, top
static float g_nav2a_button_lbrt[4]; // left, bottom, right, top
static float g_nav2s_button_lbrt[4]; // left, bottom, right, top

static float g_adf1a_button_lbrt[4]; // left, bottom, right, top
static float g_adf1s_button_lbrt[4]; // left, bottom, right, top
static float g_adf2a_button_lbrt[4]; // left, bottom, right, top
static float g_adf2s_button_lbrt[4]; // left, bottom, right, top

static float g_radio_freq_button_lbrt[4]; // left, bottom, right, top

static float g_430n1_com_ff_button_lbrt[4]; // left, bottom, right, top
static float g_430n1_nav_ff_button_lbrt[4]; // left, bottom, right, top

static float g_430n1_fine_up_button_lbrt[4];   // left, bottom, right, top
static float g_430n1_fine_down_button_lbrt[4]; // left, bottom, right, top

static float g_430n1_coarse_up_button_lbrt[4];   // left, bottom, right, top
static float g_430n1_coarse_down_button_lbrt[4]; // left, bottom, right, top

static float g_430n1_nav_com_tog_button_lbrt[4]; // left, bottom, right, top

static float g_430n1_cdi_button_lbrt[4];  // left, bottom, right, top
static float g_430n1_obs_button_lbrt[4];  // left, bottom, right, top
static float g_430n1_msg_button_lbrt[4];  // left, bottom, right, top
static float g_430n1_fpl_button_lbrt[4];  // left, bottom, right, top
static float g_430n1_vnav_button_lbrt[4]; // left, bottom, right, top
static float g_430n1_proc_button_lbrt[4]; // left, bottom, right, top

static float g_430n1_zoom_in_button_lbrt[4];    // left, bottom, right, top
static float g_430n1_zoom_out_button_lbrt[4];   // left, bottom, right, top
static float g_430n1_direct_button_lbrt[4];     // left, bottom, right, top
static float g_430n1_menu_button_lbrt[4];       // left, bottom, right, top
static float g_430n1_clr_button_lbrt[4];        // left, bottom, right, top
static float g_430n1_ent_button_lbrt[4];        // left, bottom, right, top
static float g_430n1_page_up_button_lbrt[4];    // left, bottom, right, top
static float g_430n1_page_dn_button_lbrt[4];    // left, bottom, right, top
static float g_430n1_chapter_up_button_lbrt[4]; // left, bottom, right, top
static float g_430n1_chapter_dn_button_lbrt[4]; // left, bottom, right, top
static float g_430n1_cursor_button_lbrt[4];     // left, bottom, right, top

static float g_430n2_com_ff_button_lbrt[4]; // left, bottom, right, top
static float g_430n2_nav_ff_button_lbrt[4]; // left, bottom, right, top

static float g_430n2_fine_up_button_lbrt[4];   // left, bottom, right, top
static float g_430n2_fine_down_button_lbrt[4]; // left, bottom, right, top

static float g_430n2_coarse_up_button_lbrt[4];   // left, bottom, right, top
static float g_430n2_coarse_down_button_lbrt[4]; // left, bottom, right, top

static float g_430n2_nav_com_tog_button_lbrt[4]; // left, bottom, right, top

static float g_430n2_cdi_button_lbrt[4];  // left, bottom, right, top
static float g_430n2_obs_button_lbrt[4];  // left, bottom, right, top
static float g_430n2_msg_button_lbrt[4];  // left, bottom, right, top
static float g_430n2_fpl_button_lbrt[4];  // left, bottom, right, top
static float g_430n2_vnav_button_lbrt[4]; // left, bottom, right, top
static float g_430n2_proc_button_lbrt[4]; // left, bottom, right, top

static float g_430n2_zoom_in_button_lbrt[4];    // left, bottom, right, top
static float g_430n2_zoom_out_button_lbrt[4];   // left, bottom, right, top
static float g_430n2_direct_button_lbrt[4];     // left, bottom, right, top
static float g_430n2_menu_button_lbrt[4];       // left, bottom, right, top
static float g_430n2_clr_button_lbrt[4];        // left, bottom, right, top
static float g_430n2_ent_button_lbrt[4];        // left, bottom, right, top
static float g_430n2_page_up_button_lbrt[4];    // left, bottom, right, top
static float g_430n2_page_dn_button_lbrt[4];    // left, bottom, right, top
static float g_430n2_chapter_up_button_lbrt[4]; // left, bottom, right, top
static float g_430n2_chapter_dn_button_lbrt[4]; // left, bottom, right, top
static float g_430n2_cursor_button_lbrt[4];     // left, bottom, right, top

vector<int> xbtn2cmd_radio_Vector;
int radio_Vector_size = 0;

float col_white[] = {1.0, 1.0, 1.0};
float col_green[] = {0.0, 1.0, 0.0};
float col_red[] = {1.0, 0.0, 0.0};
float col_fuchsia[] = {1.0, 0.0, 1.0};
float col_blue[] = {0.0, 0.0, 1.0};
float col_black[] = {0.0, 0.0, 0.0};

float green[] = {0.282, 0.45, 0.25, 1.0};
float light_green[] = {0.43, 0.58, 0.309, 1.0};
float gost_white[] = {0.9725, 0.9725, 1.0, 1.0};

float white[] = {1.0, 1.0, 1.0, 1.0};

char *copilot_on = const_cast<char *>("+");
char *checkmark_off = const_cast<char *>("    ");
char *checkmark_on = const_cast<char *>(" X ");

int checked[25];

int line_number = 0;

int left, top, right, bottom;

int label_width = 150;
int mid_label_width = 70;
int small_button_width = 50;

size_t ii;

void xb2cvr_draw(XPLMWindowID xb2cvr_in_window_id, void *in_refcon);
int xb2cvr_handle_mouse(XPLMWindowID xb2cvr_in_window_id, int xb2cvr_x,
                        int xb2cvr_y, int xb2cvr_mouse_status, void *in_refcon);

static int coord_in_rect(float x, float y, const float *bounds_lbrt) {
  return (((x - 10) >= bounds_lbrt[0]) && ((x - 20) < bounds_lbrt[2]) &&
          (y < bounds_lbrt[3]) && (y >= bounds_lbrt[1]));
}

void xb2cvr_draw(XPLMWindowID xb2cvr_in_window_id, void * /*in_refcon*/) {

  XPLMSetGraphicsState(0 /* no fog */, 0 /* 0 texture units */,
                       0 /* no lighting */, 0 /* no alpha testing */,
                       1 /* do alpha blend */, 1 /* do depth testing */,
                       0 /* no depth writing */
                       );

  // We draw our rudimentary button boxes based on the height of the button text
  int char_height;
  XPLMGetFontDimensions(xplmFont_Proportional, nullptr, &char_height, nullptr);

  if(XPLMWindowIsPoppedOut) {
      is_popped_out = XPLMWindowIsPoppedOut(xb2cvr_in_window_id);
  } else {
      // Old windows can't be popped out
      is_popped_out = 0;
  }

  int l, t, r, b;
  XPLMGetWindowGeometry(xb2cvr_in_window_id, &l, &t, &r, &b);

  PageNumberValue = page_number;

  // Draw the main body of the button window.

  line_number = 1;

  // Find out how big to make the buttons so they always fit on the window

  // Draw the page 1 button
  const char *page1_btn_label = page1_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page1_button_lbrt[0] = l;
  g_page1_button_lbrt[3] = t - (line_number * char_height);
  g_page1_button_lbrt[2] =
      g_page1_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page1_button_lbrt[1] =
      g_page1_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 1) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page1_button_lbrt[0]),
               static_cast<GLint>(g_page1_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page1_button_lbrt[2]),
               static_cast<GLint>(g_page1_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page1_button_lbrt[2]),
               static_cast<GLint>(g_page1_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page1_button_lbrt[0]),
               static_cast<GLint>(g_page1_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page1 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page1_button_lbrt[0] = g_page1_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page1_button_lbrt[0]),
                 static_cast<int>(g_page1_button_lbrt[1] + 8),
                 (char *)page1_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 2 button
  const char *page2_btn_label = page2_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page2_button_lbrt[0] = l + 115;
  g_page2_button_lbrt[3] = t - (line_number * char_height);
  g_page2_button_lbrt[2] =
      g_page2_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page2_button_lbrt[1] =
      g_page2_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 2) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page2_button_lbrt[0]),
               static_cast<GLint>(g_page2_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page2_button_lbrt[2]),
               static_cast<GLint>(g_page2_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page2_button_lbrt[2]),
               static_cast<GLint>(g_page2_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page2_button_lbrt[0]),
               static_cast<GLint>(g_page2_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page2 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page2_button_lbrt[0] = g_page2_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page2_button_lbrt[0]),
                 static_cast<int>(g_page2_button_lbrt[1] + 8),
                 (char *)page2_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 3 button
  const char *page3_btn_label = page3_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page3_button_lbrt[0] = l + 230;
  g_page3_button_lbrt[3] = t - (line_number * char_height);
  g_page3_button_lbrt[2] =
      g_page3_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page3_button_lbrt[1] =
      g_page3_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 3) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page3_button_lbrt[0]),
               static_cast<GLint>(g_page3_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page3_button_lbrt[2]),
               static_cast<GLint>(g_page3_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page3_button_lbrt[2]),
               static_cast<GLint>(g_page3_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page3_button_lbrt[0]),
               static_cast<GLint>(g_page3_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page3 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page3_button_lbrt[0] = g_page3_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page3_button_lbrt[0]),
                 static_cast<int>(g_page3_button_lbrt[1] + 8),
                 (char *)page3_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 4 button
  const char *page4_btn_label = page4_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page4_button_lbrt[0] = l + 345;
  g_page4_button_lbrt[3] = t - (line_number * char_height);
  g_page4_button_lbrt[2] =
      g_page4_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page4_button_lbrt[1] =
      g_page4_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 4) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page4_button_lbrt[0]),
               static_cast<GLint>(g_page4_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page4_button_lbrt[2]),
               static_cast<GLint>(g_page4_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page4_button_lbrt[2]),
               static_cast<GLint>(g_page4_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page4_button_lbrt[0]),
               static_cast<GLint>(g_page4_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page4 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page4_button_lbrt[0] = g_page4_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page4_button_lbrt[0]),
                 static_cast<int>(g_page4_button_lbrt[1] + 8),
                 (char *)page4_btn_label, nullptr, xplmFont_Proportional);

  // Draw the hide button
  const char *hide_btn_label = "Hide";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_hide_button_lbrt[0] = l + 460;
  g_hide_button_lbrt[3] = t - (line_number * char_height);
  g_hide_button_lbrt[2] =
      g_hide_button_lbrt[0] + 50; // *just* wide enough to fit the button text
  g_hide_button_lbrt[1] =
      g_hide_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (mouse_down_hide) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_hide_button_lbrt[0]),
               static_cast<GLint>(g_hide_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_hide_button_lbrt[2]),
               static_cast<GLint>(g_hide_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_hide_button_lbrt[2]),
               static_cast<GLint>(g_hide_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_hide_button_lbrt[0]),
               static_cast<GLint>(g_hide_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Hide button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_hide_button_lbrt[0] = g_hide_button_lbrt[0] + 10;
  XPLMDrawString(col_black, static_cast<int>(g_hide_button_lbrt[0]),
                 static_cast<int>(g_hide_button_lbrt[1] + 8),
                 (char *)hide_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 5 button
  line_number = line_number + 4;
  const char *page5_btn_label = page5_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page5_button_lbrt[0] = l;
  g_page5_button_lbrt[3] = t - (line_number * char_height);
  g_page5_button_lbrt[2] =
      g_page5_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page5_button_lbrt[1] =
      g_page5_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 5) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page5_button_lbrt[0]),
               static_cast<GLint>(g_page5_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page5_button_lbrt[2]),
               static_cast<GLint>(g_page5_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page5_button_lbrt[2]),
               static_cast<GLint>(g_page5_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page5_button_lbrt[0]),
               static_cast<GLint>(g_page5_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page5 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page5_button_lbrt[0] = g_page5_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page5_button_lbrt[0]),
                 static_cast<int>(g_page5_button_lbrt[1] + 8),
                 (char *)page5_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 6 button
  const char *page6_btn_label = page6_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page6_button_lbrt[0] = l + 115;
  g_page6_button_lbrt[3] = t - (line_number * char_height);
  g_page6_button_lbrt[2] =
      g_page6_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page6_button_lbrt[1] =
      g_page6_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 6) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page6_button_lbrt[0]),
               static_cast<GLint>(g_page6_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page6_button_lbrt[2]),
               static_cast<GLint>(g_page6_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page6_button_lbrt[2]),
               static_cast<GLint>(g_page6_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page6_button_lbrt[0]),
               static_cast<GLint>(g_page6_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page6 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page6_button_lbrt[0] = g_page6_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page6_button_lbrt[0]),
                 static_cast<int>(g_page6_button_lbrt[1] + 8),
                 (char *)page6_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 7 button
  const char *page7_btn_label = page7_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page7_button_lbrt[0] = l + 230;
  g_page7_button_lbrt[3] = t - (line_number * char_height);
  g_page7_button_lbrt[2] =
      g_page7_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page7_button_lbrt[1] =
      g_page7_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 7) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page7_button_lbrt[0]),
               static_cast<GLint>(g_page7_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page7_button_lbrt[2]),
               static_cast<GLint>(g_page7_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page7_button_lbrt[2]),
               static_cast<GLint>(g_page7_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page7_button_lbrt[0]),
               static_cast<GLint>(g_page7_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page7 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page7_button_lbrt[0] = g_page7_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page7_button_lbrt[0]),
                 static_cast<int>(g_page7_button_lbrt[1] + 8),
                 (char *)page7_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 8 button
  const char *page8_btn_label = page8_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page8_button_lbrt[0] = l + 345;
  g_page8_button_lbrt[3] = t - (line_number * char_height);
  g_page8_button_lbrt[2] =
      g_page8_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page8_button_lbrt[1] =
      g_page8_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 8) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page8_button_lbrt[0]),
               static_cast<GLint>(g_page8_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page8_button_lbrt[2]),
               static_cast<GLint>(g_page8_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page8_button_lbrt[2]),
               static_cast<GLint>(g_page8_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page8_button_lbrt[0]),
               static_cast<GLint>(g_page8_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page8 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page8_button_lbrt[0] = g_page8_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page8_button_lbrt[0]),
                 static_cast<int>(g_page8_button_lbrt[1] + 8),
                 (char *)page8_btn_label, nullptr, xplmFont_Proportional);

  // Draw the In Front box
  // line_number = line_number + 3;
  const char *in_front_btn_label = "In Front";
  int in_front = XPLMIsWindowInFront(xb2cvr_in_window_id);

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_in_front_button_lbrt[0] = l + 460;
  g_in_front_button_lbrt[3] = t - (line_number * char_height);
  g_in_front_button_lbrt[2] =
      g_in_front_button_lbrt[0] +
      XPLMMeasureString(xplmFont_Proportional, in_front_btn_label,
                        static_cast<int>(strlen(in_front_btn_label))) +
      5; // *just* wide enough to fit the button text
  g_in_front_button_lbrt[1] =
      g_in_front_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (in_front) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_in_front_button_lbrt[0]),
               static_cast<GLint>(g_in_front_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_in_front_button_lbrt[2]),
               static_cast<GLint>(g_in_front_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_in_front_button_lbrt[2]),
               static_cast<GLint>(g_in_front_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_in_front_button_lbrt[0]),
               static_cast<GLint>(g_in_front_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the In Front button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_in_front_button_lbrt[0] = g_in_front_button_lbrt[0] + 3;
  XPLMDrawString(col_black, static_cast<int>(g_in_front_button_lbrt[0]),
                 static_cast<int>(g_in_front_button_lbrt[1] + 8),
                 (char *)in_front_btn_label, nullptr, xplmFont_Proportional);




  // Draw the page 9 button
  line_number = line_number + 4;
  const char *page9_btn_label = page9_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page9_button_lbrt[0] = l;
  g_page9_button_lbrt[3] = t - (line_number * char_height);
  g_page9_button_lbrt[2] =
      g_page9_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page9_button_lbrt[1] =
      g_page9_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 9) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page9_button_lbrt[0]),
               static_cast<GLint>(g_page9_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page9_button_lbrt[2]),
               static_cast<GLint>(g_page9_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page9_button_lbrt[2]),
               static_cast<GLint>(g_page9_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page9_button_lbrt[0]),
               static_cast<GLint>(g_page9_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page9 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page9_button_lbrt[0] = g_page9_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page9_button_lbrt[0]),
                 static_cast<int>(g_page9_button_lbrt[1] + 8),
                 (char *)page9_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 10 button
  const char *page10_btn_label = page10_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page10_button_lbrt[0] = l + 115;
  g_page10_button_lbrt[3] = t - (line_number * char_height);
  g_page10_button_lbrt[2] =
      g_page10_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page10_button_lbrt[1] =
      g_page10_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 10) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page10_button_lbrt[0]),
               static_cast<GLint>(g_page10_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page10_button_lbrt[2]),
               static_cast<GLint>(g_page10_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page10_button_lbrt[2]),
               static_cast<GLint>(g_page10_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page10_button_lbrt[0]),
               static_cast<GLint>(g_page10_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page6 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page10_button_lbrt[0] = g_page10_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page10_button_lbrt[0]),
                 static_cast<int>(g_page10_button_lbrt[1] + 8),
                 (char *)page10_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 11 button
  const char *page11_btn_label = page11_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page11_button_lbrt[0] = l + 230;
  g_page11_button_lbrt[3] = t - (line_number * char_height);
  g_page11_button_lbrt[2] =
      g_page11_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page11_button_lbrt[1] =
      g_page11_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 11) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page11_button_lbrt[0]),
               static_cast<GLint>(g_page11_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page11_button_lbrt[2]),
               static_cast<GLint>(g_page11_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page11_button_lbrt[2]),
               static_cast<GLint>(g_page11_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page11_button_lbrt[0]),
               static_cast<GLint>(g_page11_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page11 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page11_button_lbrt[0] = g_page11_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page11_button_lbrt[0]),
                 static_cast<int>(g_page11_button_lbrt[1] + 8),
                 (char *)page11_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page 12 button
  const char *page12_btn_label = page12_button_label.c_str();

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_page12_button_lbrt[0] = l + 345;
  g_page12_button_lbrt[3] = t - (line_number * char_height);
  g_page12_button_lbrt[2] =
      g_page12_button_lbrt[0] + 90; // *just* wide enough to fit the button text
  g_page12_button_lbrt[1] =
      g_page12_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (page_number == 12) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_page12_button_lbrt[0]),
               static_cast<GLint>(g_page12_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page12_button_lbrt[2]),
               static_cast<GLint>(g_page12_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_page12_button_lbrt[2]),
               static_cast<GLint>(g_page12_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_page12_button_lbrt[0]),
               static_cast<GLint>(g_page12_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page12 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_page12_button_lbrt[0] = g_page12_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_page12_button_lbrt[0]),
                 static_cast<int>(g_page12_button_lbrt[1] + 8),
                 (char *)page12_btn_label, nullptr, xplmFont_Proportional);


  // Draw the reload button
  const char *reload_btn_label = "Reload";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_reload_button_lbrt[0] = l + 460;
  g_reload_button_lbrt[3] = t - (line_number * char_height);
  g_reload_button_lbrt[2] =
      g_reload_button_lbrt[0] + 50; // *just* wide enough to fit the button text
  g_reload_button_lbrt[1] =
      g_reload_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (mouse_down_reload) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_reload_button_lbrt[0]),
               static_cast<GLint>(g_reload_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_reload_button_lbrt[2]),
               static_cast<GLint>(g_reload_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_reload_button_lbrt[2]),
               static_cast<GLint>(g_reload_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_reload_button_lbrt[0]),
               static_cast<GLint>(g_reload_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Reload button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_reload_button_lbrt[0] = g_reload_button_lbrt[0] + 10;
  XPLMDrawString(col_black, static_cast<int>(g_reload_button_lbrt[0] - 4),
                 static_cast<int>(g_reload_button_lbrt[1] + 8),
                 (char *)reload_btn_label, nullptr, xplmFont_Proportional);



  // Draw the page Radios button
  line_number = line_number + 4;
  const char *radios_btn_label = "Radios";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_radios_button_lbrt[0] = l;
  g_radios_button_lbrt[3] = t - (line_number * char_height);
  g_radios_button_lbrt[2] =
      g_radios_button_lbrt[0] + 50; // *just* wide enough to fit the button text
  g_radios_button_lbrt[1] =
      g_radios_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button

  if (page_number == 13) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_radios_button_lbrt[0]),
               static_cast<GLint>(g_radios_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_radios_button_lbrt[2]),
               static_cast<GLint>(g_radios_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_radios_button_lbrt[2]),
               static_cast<GLint>(g_radios_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_radios_button_lbrt[0]),
               static_cast<GLint>(g_radios_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Radios button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_radios_button_lbrt[0] = g_radios_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_radios_button_lbrt[0]),
                 static_cast<int>(g_radios_button_lbrt[1] + 8),
                 (char *)radios_btn_label, nullptr, xplmFont_Proportional);

  // Draw the page g430n1 button
  // line_number = line_number + 4;
  const char *g430n1_btn_label = "g430n1";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_g430n1_button_lbrt[0] = l + 75;
  g_g430n1_button_lbrt[3] = t - (line_number * char_height);
  g_g430n1_button_lbrt[2] =
      g_g430n1_button_lbrt[0] + 50; // *just* wide enough to fit the button text
  g_g430n1_button_lbrt[1] =
      g_g430n1_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button

  if (page_number == 14) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_g430n1_button_lbrt[0]),
               static_cast<GLint>(g_g430n1_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_g430n1_button_lbrt[2]),
               static_cast<GLint>(g_g430n1_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_g430n1_button_lbrt[2]),
               static_cast<GLint>(g_g430n1_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_g430n1_button_lbrt[0]),
               static_cast<GLint>(g_g430n1_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the g430n1 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_g430n1_button_lbrt[0] = g_g430n1_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_g430n1_button_lbrt[0]),
                 static_cast<int>(g_g430n1_button_lbrt[1] + 8),
                 (char *)g430n1_btn_label, nullptr, xplmFont_Proportional);

  // Draw the g430n2 button
  // line_number = line_number + 4;
  const char *g430n2_btn_label = "g430n2";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_g430n2_button_lbrt[0] = l + 150;
  g_g430n2_button_lbrt[3] = t - (line_number * char_height);
  g_g430n2_button_lbrt[2] =
      g_g430n2_button_lbrt[0] + 50; // *just* wide enough to fit the button text
  g_g430n2_button_lbrt[1] =
      g_g430n2_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button

  if (page_number == 15) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_g430n2_button_lbrt[0]),
               static_cast<GLint>(g_g430n2_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_g430n2_button_lbrt[2]),
               static_cast<GLint>(g_g430n2_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_g430n2_button_lbrt[2]),
               static_cast<GLint>(g_g430n2_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_g430n2_button_lbrt[0]),
               static_cast<GLint>(g_g430n2_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Page11 g430n2 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_g430n2_button_lbrt[0] = g_g430n2_button_lbrt[0] + 1;
  XPLMDrawString(col_black, static_cast<int>(g_g430n2_button_lbrt[0]),
                 static_cast<int>(g_g430n2_button_lbrt[1] + 8),
                 (char *)g430n2_btn_label, nullptr, xplmFont_Proportional);

  /*

  // Draw the page 16 g1000n1 button
  // line_number = line_number + 4;
  const char * g1000n1_btn_label = "g1000n1";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  button text)
  g_g1000n1_button_lbrt[0] = l + 225;
  g_g1000n1_button_lbrt[3] = t - (line_number * char_height);
  g_g1000n1_button_lbrt[2] = g_g1000n1_button_lbrt[0] + 50; // *just* wide enough
  to fit the button text
  g_g1000n1_button_lbrt[1] = g_g1000n1_button_lbrt[3] - (2.00f * char_height); //
  a bit taller than the button text

  // Draw the box around our rudimentary button
  // sprintf(scratch_buffer, "Xbtn2cmd: page_number = %d\n", page_number);
  // XPLMDebugString(scratch_buffer);
  if (page_number == 16) {
      glColor4fv(light_green);
  }
  else {
     glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
      glVertex2i(g_g1000n1_button_lbrt[0], g_g1000n1_button_lbrt[3]);
      glVertex2i(g_g1000n1_button_lbrt[2], g_g1000n1_button_lbrt[3]);
      glVertex2i(g_g1000n1_button_lbrt[2], g_g1000n1_button_lbrt[1]);
      glVertex2i(g_g1000n1_button_lbrt[0], g_g1000n1_button_lbrt[1]);
  }
  glEnd();

  // Draw the text on the Page16 g1000n1 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_g1000n1_button_lbrt[0] = g_g1000n1_button_lbrt[0] + 1;
  XPLMDrawString(col_black, g_g1000n1_button_lbrt[0], g_page16_button_lbrt[1] +
  8, (char *)g1000n1_btn_label, NULL, xplmFont_Proportional);


  // Draw the page 17 g1000n2 button
  // line_number = line_number + 4;
  const char * g1000n2_btn_label = "g1000n2";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  button text)
  g_g1000n2_button_lbrt[0] = l + 300;
  g_g1000n2_button_lbrt[3] = t - (line_number * char_height);
  g_g1000n2_button_lbrt[2] = g_g1000n2_button_lbrt[0] + 50; // *just* wide enough
  to fit the button text
  g_g1000n2_button_lbrt[1] = g_g1000n2_button_lbrt[3] - (2.00f * char_height); //
  a bit taller than the button text

  // Draw the box around our rudimentary button
  // sprintf(scratch_buffer, "Xbtn2cmd: page_number = %d\n", page_number);
  // XPLMDebugString(scratch_buffer);
  if (page_number == 17) {
      glColor4fv(light_green);
  }
  else {
     glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
      glVertex2i(g_g1000n2_button_lbrt[0], g_g1000n2_button_lbrt[3]);
      glVertex2i(g_g1000n2_button_lbrt[2], g_g1000n2_button_lbrt[3]);
      glVertex2i(g_g1000n2_button_lbrt[2], g_g1000n2_button_lbrt[1]);
      glVertex2i(g_g1000n2_button_lbrt[0], g_g1000n2_button_lbrt[1]);
  }
  glEnd();

  // Draw the text on the Page17 g1000n2 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_g1000n2_button_lbrt[0] = g_g1000n2_button_lbrt[0] + 1;
  XPLMDrawString(col_black, g_g1000n2_button_lbrt[0], g_g1000n2_button_lbrt[1] +
  8, (char *)g1000n2_btn_label, NULL, xplmFont_Proportional);


  // Draw the page 18 g1000n3 button
  // line_number = line_number + 4;
  const char * g1000n3_btn_label = "g1000n3";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  button text)
  g_g1000n3_button_lbrt[0] = l + 375;
  g_g1000n3_button_lbrt[3] = t - (line_number * char_height);
  g_g1000n3_button_lbrt[2] = g_g1000n3_button_lbrt[0] + 50; // *just* wide enough
  to fit the button text
  g_g1000n3_button_lbrt[1] = g_g1000n3_button_lbrt[3] - (2.00f * char_height); //
  a bit taller than the button text

  // Draw the box around our rudimentary button
  // sprintf(scratch_buffer, "Xbtn2cmd: page_number = %d\n", page_number);
  // XPLMDebugString(scratch_buffer);
  if (page_number == 18) {
      glColor4fv(light_green);
  }
  else {
     glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
      glVertex2i(g_g1000n3_button_lbrt[0], g_g1000n3_button_lbrt[3]);
      glVertex2i(g_g1000n3_button_lbrt[2], g_g1000n3_button_lbrt[3]);
      glVertex2i(g_g1000n3_button_lbrt[2], g_g1000n3_button_lbrt[1]);
      glVertex2i(g_g1000n3_button_lbrt[0], g_g1000n3_button_lbrt[1]);
  }
  glEnd();

  // Draw the text on the Page18 g1000n3 button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_g1000n3_button_lbrt[0] = g_g1000n3_button_lbrt[0] + 1;
  XPLMDrawString(col_black, g_g1000n3_button_lbrt[0], g_g1000n3_button_lbrt[1] +
  8, (char *)g1000n3_btn_label, NULL, xplmFont_Proportional);

  */

  // Draw the crtl c button
  const char *ctrl_c_btn_label = "Ctrl C";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_ctrl_c_button_lbrt[0] = l + 385;
  g_ctrl_c_button_lbrt[3] = t - (line_number * char_height);
  g_ctrl_c_button_lbrt[2] =
      g_ctrl_c_button_lbrt[0] + 50; // *just* wide enough to fit the button text
  g_ctrl_c_button_lbrt[1] =
      g_ctrl_c_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (mouse_down_ctrl_c) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_ctrl_c_button_lbrt[0]),
               static_cast<GLint>(g_ctrl_c_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_ctrl_c_button_lbrt[2]),
               static_cast<GLint>(g_ctrl_c_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_ctrl_c_button_lbrt[2]),
               static_cast<GLint>(g_ctrl_c_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_ctrl_c_button_lbrt[0]),
               static_cast<GLint>(g_ctrl_c_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Ctrl C button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_ctrl_c_button_lbrt[0] = g_ctrl_c_button_lbrt[0] + 10;
  XPLMDrawString(col_black, static_cast<int>(g_ctrl_c_button_lbrt[0] - 4),
                 static_cast<int>(g_ctrl_c_button_lbrt[1] + 8),
                 (char *)ctrl_c_btn_label, nullptr, xplmFont_Proportional);

  // Draw the edit button
  const char *edit_btn_label = "Edit";

  // 0 left, 1 bottom, 2 right, 3 top
  // Position the button in the upper left of the window (sized to fit the
  // button text)
  g_edit_button_lbrt[0] = l + 460;
  g_edit_button_lbrt[3] = t - (line_number * char_height);
  g_edit_button_lbrt[2] =
      g_edit_button_lbrt[0] + 50; // *just* wide enough to fit the button text
  g_edit_button_lbrt[1] =
      g_edit_button_lbrt[3] -
      (2.00f * char_height); // a bit taller than the button text

  // Draw the box around our rudimentary button
  if (mouse_down_edit) {
    glColor4fv(light_green);
  } else {
    glColor4fv(green);
  }
  glBegin(GL_POLYGON);
  {
    glVertex2i(static_cast<GLint>(g_edit_button_lbrt[0]),
               static_cast<GLint>(g_edit_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_edit_button_lbrt[2]),
               static_cast<GLint>(g_edit_button_lbrt[3]));
    glVertex2i(static_cast<GLint>(g_edit_button_lbrt[2]),
               static_cast<GLint>(g_edit_button_lbrt[1]));
    glVertex2i(static_cast<GLint>(g_edit_button_lbrt[0]),
               static_cast<GLint>(g_edit_button_lbrt[1]));
  }
  glEnd();

  // Draw the text on the Edit button.
  // 0 left, 1 bottom, 2 right, 3 top
  g_edit_button_lbrt[0] = g_edit_button_lbrt[0] + 10;
  XPLMDrawString(col_black, static_cast<int>(g_edit_button_lbrt[0] - 4),
                 static_cast<int>(g_edit_button_lbrt[1] + 8),
                 (char *)edit_btn_label, nullptr, xplmFont_Proportional);



  if (page_number < 9) {

    // Draw the Button1 button
    line_number = line_number + 4;
    const char *btn1_label = nullptr;
    if (page_number == 1) {
      btn1_label = page1_button1_label.c_str();
    } else if (page_number == 2) {
      btn1_label = page2_button1_label.c_str();
    } else if (page_number == 3) {
      btn1_label = page3_button1_label.c_str();
    } else if (page_number == 4) {
      btn1_label = page4_button1_label.c_str();
    } else if (page_number == 5) {
      btn1_label = page5_button1_label.c_str();
    } else if (page_number == 6) {
      btn1_label = page6_button1_label.c_str();
    } else if (page_number == 7) {
      btn1_label = page7_button1_label.c_str();
    } else if (page_number == 8) {
      btn1_label = page8_button1_label.c_str();
    }


    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button1_lbrt[0] = l;
    g_button1_lbrt[3] = t - (line_number * char_height);
    g_button1_lbrt[2] =
        g_button1_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button1_lbrt[1] =
        g_button1_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[0]) {
      glColor4fv(light_green);
      ButtonNumberValue = 1;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button1_lbrt[0]),
                 static_cast<GLint>(g_button1_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button1_lbrt[2]),
                 static_cast<GLint>(g_button1_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button1_lbrt[2]),
                 static_cast<GLint>(g_button1_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button1_lbrt[0]),
                 static_cast<GLint>(g_button1_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button1 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button1_lbrt[0] = g_button1_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button1_lbrt[0]),
                   static_cast<int>(g_button1_lbrt[1] + 8), (char *)btn1_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button2 button
    const char *btn2_label = nullptr;
    if (page_number == 1) {
      btn2_label = page1_button2_label.c_str();
    } else if (page_number == 2) {
      btn2_label = page2_button2_label.c_str();
    } else if (page_number == 3) {
      btn2_label = page3_button2_label.c_str();
    } else if (page_number == 4) {
      btn2_label = page4_button2_label.c_str();
    } else if (page_number == 5) {
      btn2_label = page5_button2_label.c_str();
    } else if (page_number == 6) {
      btn2_label = page6_button2_label.c_str();
    } else if (page_number == 7) {
      btn2_label = page7_button2_label.c_str();
    } else if (page_number == 8) {
      btn2_label = page8_button2_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button2_lbrt[0] = l + 180;
    g_button2_lbrt[3] = t - (line_number * char_height);
    g_button2_lbrt[2] =
        g_button2_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button2_lbrt[1] =
        g_button2_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[1]) {
      glColor4fv(light_green);
      ButtonNumberValue = 2;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button2_lbrt[0]),
                 static_cast<GLint>(g_button2_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button2_lbrt[2]),
                 static_cast<GLint>(g_button2_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button2_lbrt[2]),
                 static_cast<GLint>(g_button2_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button2_lbrt[0]),
                 static_cast<GLint>(g_button2_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button2 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button2_lbrt[0] = g_button2_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button2_lbrt[0]),
                   static_cast<int>(g_button2_lbrt[1] + 8), (char *)btn2_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button3 button
    const char *btn3_label = nullptr;
    if (page_number == 1) {
      btn3_label = page1_button3_label.c_str();
    } else if (page_number == 2) {
      btn3_label = page2_button3_label.c_str();
    } else if (page_number == 3) {
      btn3_label = page3_button3_label.c_str();
    } else if (page_number == 4) {
      btn3_label = page4_button3_label.c_str();
    } else if (page_number == 5) {
      btn3_label = page5_button3_label.c_str();
    } else if (page_number == 6) {
      btn3_label = page6_button3_label.c_str();
    } else if (page_number == 7) {
      btn3_label = page7_button3_label.c_str();
    } else if (page_number == 8) {
      btn3_label = page8_button3_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button3_lbrt[0] = l + 360;
    g_button3_lbrt[3] = t - (line_number * char_height);
    g_button3_lbrt[2] =
        g_button3_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button3_lbrt[1] =
        g_button3_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[2]) {
      glColor4fv(light_green);
      ButtonNumberValue = 3;
    } else {
      glColor4fv(green);
    }

    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button3_lbrt[0]),
                 static_cast<GLint>(g_button3_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button3_lbrt[2]),
                 static_cast<GLint>(g_button3_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button3_lbrt[2]),
                 static_cast<GLint>(g_button3_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button3_lbrt[0]),
                 static_cast<GLint>(g_button3_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button3 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button3_lbrt[0] = g_button3_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button3_lbrt[0]),
                   static_cast<int>(g_button3_lbrt[1] + 8), (char *)btn3_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button4 button
    line_number = line_number + 4;
    const char *btn4_label = nullptr;
    if (page_number == 1) {
      btn4_label = page1_button4_label.c_str();
    } else if (page_number == 2) {
      btn4_label = page2_button4_label.c_str();
    } else if (page_number == 3) {
      btn4_label = page3_button4_label.c_str();
    } else if (page_number == 4) {
      btn4_label = page4_button4_label.c_str();
    } else if (page_number == 5) {
      btn4_label = page5_button4_label.c_str();
    } else if (page_number == 6) {
      btn4_label = page6_button4_label.c_str();
    } else if (page_number == 7) {
      btn4_label = page7_button4_label.c_str();
    } else if (page_number == 8) {
      btn4_label = page8_button4_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button4_lbrt[0] = l;
    g_button4_lbrt[3] = t - (line_number * char_height);
    g_button4_lbrt[2] =
        g_button4_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button4_lbrt[1] =
        g_button4_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[3]) {
      glColor4fv(light_green);
      ButtonNumberValue = 4;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button4_lbrt[0]),
                 static_cast<GLint>(g_button4_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button4_lbrt[2]),
                 static_cast<GLint>(g_button4_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button4_lbrt[2]),
                 static_cast<GLint>(g_button4_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button4_lbrt[0]),
                 static_cast<GLint>(g_button4_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button4 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button4_lbrt[0] = g_button4_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button4_lbrt[0]),
                   static_cast<int>(g_button4_lbrt[1] + 8), (char *)btn4_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button5 button
    const char *btn5_label = nullptr;
    if (page_number == 1) {
      btn5_label = page1_button5_label.c_str();
    } else if (page_number == 2) {
      btn5_label = page2_button5_label.c_str();
    } else if (page_number == 3) {
      btn5_label = page3_button5_label.c_str();
    } else if (page_number == 4) {
      btn5_label = page4_button5_label.c_str();
    } else if (page_number == 5) {
      btn5_label = page5_button5_label.c_str();
    } else if (page_number == 6) {
      btn5_label = page6_button5_label.c_str();
    } else if (page_number == 7) {
      btn5_label = page7_button5_label.c_str();
    } else if (page_number == 8) {
      btn5_label = page8_button5_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button5_lbrt[0] = l + 180;
    g_button5_lbrt[3] = t - (line_number * char_height);
    g_button5_lbrt[2] =
        g_button5_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button5_lbrt[1] =
        g_button5_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[4]) {
      glColor4fv(light_green);
      ButtonNumberValue = 5;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button5_lbrt[0]),
                 static_cast<GLint>(g_button5_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button5_lbrt[2]),
                 static_cast<GLint>(g_button5_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button5_lbrt[2]),
                 static_cast<GLint>(g_button5_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button5_lbrt[0]),
                 static_cast<GLint>(g_button5_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button5 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button5_lbrt[0] = g_button5_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button5_lbrt[0]),
                   static_cast<int>(g_button5_lbrt[1] + 8), (char *)btn5_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button6 button
    const char *btn6_label = nullptr;
    if (page_number == 1) {
      btn6_label = page1_button6_label.c_str();
    } else if (page_number == 2) {
      btn6_label = page2_button6_label.c_str();
    } else if (page_number == 3) {
      btn6_label = page3_button6_label.c_str();
    } else if (page_number == 4) {
      btn6_label = page4_button6_label.c_str();
    } else if (page_number == 5) {
      btn6_label = page5_button6_label.c_str();
    } else if (page_number == 6) {
      btn6_label = page6_button6_label.c_str();
    } else if (page_number == 7) {
      btn6_label = page7_button6_label.c_str();
    } else if (page_number == 8) {
      btn6_label = page8_button6_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button6_lbrt[0] = l + 360;
    g_button6_lbrt[3] = t - (line_number * char_height);
    g_button6_lbrt[2] =
        g_button6_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button6_lbrt[1] =
        g_button6_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[5]) {
      glColor4fv(light_green);
      ButtonNumberValue = 6;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button6_lbrt[0]),
                 static_cast<GLint>(g_button6_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button6_lbrt[2]),
                 static_cast<GLint>(g_button6_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button6_lbrt[2]),
                 static_cast<GLint>(g_button6_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button6_lbrt[0]),
                 static_cast<GLint>(g_button6_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button3 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button6_lbrt[0] = g_button6_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button6_lbrt[0]),
                   static_cast<int>(g_button6_lbrt[1] + 8), (char *)btn6_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button7 button
    line_number = line_number + 4;
    const char *btn7_label = nullptr;
    if (page_number == 1) {
      btn7_label = page1_button7_label.c_str();
    } else if (page_number == 2) {
      btn7_label = page2_button7_label.c_str();
    } else if (page_number == 3) {
      btn7_label = page3_button7_label.c_str();
    } else if (page_number == 4) {
      btn7_label = page4_button7_label.c_str();
    } else if (page_number == 5) {
      btn7_label = page5_button7_label.c_str();
    } else if (page_number == 6) {
      btn7_label = page6_button7_label.c_str();
    } else if (page_number == 7) {
      btn7_label = page7_button7_label.c_str();
    } else if (page_number == 8) {
      btn7_label = page8_button7_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button7_lbrt[0] = l;
    g_button7_lbrt[3] = t - (line_number * char_height);
    g_button7_lbrt[2] =
        g_button7_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button7_lbrt[1] =
        g_button7_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[6]) {
      glColor4fv(light_green);
      ButtonNumberValue = 7;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button7_lbrt[0]),
                 static_cast<GLint>(g_button7_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button7_lbrt[2]),
                 static_cast<GLint>(g_button7_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button7_lbrt[2]),
                 static_cast<GLint>(g_button7_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button7_lbrt[0]),
                 static_cast<GLint>(g_button7_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button7 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button7_lbrt[0] = g_button7_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button7_lbrt[0]),
                   static_cast<int>(g_button7_lbrt[1] + 8), (char *)btn7_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button8 button
    const char *btn8_label = nullptr;
    if (page_number == 1) {
      btn8_label = page1_button8_label.c_str();
    } else if (page_number == 2) {
      btn8_label = page2_button8_label.c_str();
    } else if (page_number == 3) {
      btn8_label = page3_button8_label.c_str();
    } else if (page_number == 4) {
      btn8_label = page4_button8_label.c_str();
    } else if (page_number == 5) {
      btn8_label = page5_button8_label.c_str();
    } else if (page_number == 6) {
      btn8_label = page6_button8_label.c_str();
    } else if (page_number == 7) {
      btn8_label = page7_button8_label.c_str();
    } else if (page_number == 8) {
      btn8_label = page8_button8_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button8_lbrt[0] = l + 180;
    g_button8_lbrt[3] = t - (line_number * char_height);
    g_button8_lbrt[2] =
        g_button8_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button8_lbrt[1] =
        g_button8_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[7]) {
      glColor4fv(light_green);
      ButtonNumberValue = 8;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button8_lbrt[0]),
                 static_cast<GLint>(g_button8_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button8_lbrt[2]),
                 static_cast<GLint>(g_button8_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button8_lbrt[2]),
                 static_cast<GLint>(g_button8_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button8_lbrt[0]),
                 static_cast<GLint>(g_button8_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button8 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button8_lbrt[0] = g_button8_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button8_lbrt[0]),
                   static_cast<int>(g_button8_lbrt[1] + 8), (char *)btn8_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button9 button
    const char *btn9_label = nullptr;
    if (page_number == 1) {
      btn9_label = page1_button9_label.c_str();
    } else if (page_number == 2) {
      btn9_label = page2_button9_label.c_str();
    } else if (page_number == 3) {
      btn9_label = page3_button9_label.c_str();
    } else if (page_number == 4) {
      btn9_label = page4_button9_label.c_str();
    } else if (page_number == 5) {
      btn9_label = page5_button9_label.c_str();
    } else if (page_number == 6) {
      btn9_label = page6_button9_label.c_str();
    } else if (page_number == 7) {
      btn9_label = page7_button9_label.c_str();
    } else if (page_number == 8) {
      btn9_label = page8_button9_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button9_lbrt[0] = l + 360;
    g_button9_lbrt[3] = t - (line_number * char_height);
    g_button9_lbrt[2] =
        g_button9_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button9_lbrt[1] =
        g_button9_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[8]) {
      glColor4fv(light_green);
      ButtonNumberValue = 9;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button9_lbrt[0]),
                 static_cast<GLint>(g_button9_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button9_lbrt[2]),
                 static_cast<GLint>(g_button9_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button9_lbrt[2]),
                 static_cast<GLint>(g_button9_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button9_lbrt[0]),
                 static_cast<GLint>(g_button9_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button9 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button9_lbrt[0] = g_button9_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button9_lbrt[0]),
                   static_cast<int>(g_button9_lbrt[1] + 8), (char *)btn9_label,
                   nullptr, xplmFont_Proportional);

    // Draw the Button10 button
    line_number = line_number + 4;
    const char *btn10_label = nullptr;
    if (page_number == 1) {
      btn10_label = page1_button10_label.c_str();
    } else if (page_number == 2) {
      btn10_label = page2_button10_label.c_str();
    } else if (page_number == 3) {
      btn10_label = page3_button10_label.c_str();
    } else if (page_number == 4) {
      btn10_label = page4_button10_label.c_str();
    } else if (page_number == 5) {
      btn10_label = page5_button10_label.c_str();
    } else if (page_number == 6) {
      btn10_label = page6_button10_label.c_str();
    } else if (page_number == 7) {
      btn10_label = page7_button10_label.c_str();
    } else if (page_number == 8) {
      btn10_label = page8_button10_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button10_lbrt[0] = l;
    g_button10_lbrt[3] = t - (line_number * char_height);
    g_button10_lbrt[2] =
        g_button10_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button10_lbrt[1] =
        g_button10_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[9]) {
      glColor4fv(light_green);
      ButtonNumberValue = 10;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button10_lbrt[0]),
                 static_cast<GLint>(g_button10_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button10_lbrt[2]),
                 static_cast<GLint>(g_button10_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button10_lbrt[2]),
                 static_cast<GLint>(g_button10_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button10_lbrt[0]),
                 static_cast<GLint>(g_button10_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button10 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button10_lbrt[0] = g_button10_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button10_lbrt[0]),
                   static_cast<int>(g_button10_lbrt[1] + 8),
                   (char *)btn10_label, nullptr, xplmFont_Proportional);

    // Draw the Button11 button
    const char *btn11_label = nullptr;
    if (page_number == 1) {
      btn11_label = page1_button11_label.c_str();
    } else if (page_number == 2) {
      btn11_label = page2_button11_label.c_str();
    } else if (page_number == 3) {
      btn11_label = page3_button11_label.c_str();
    } else if (page_number == 4) {
      btn11_label = page4_button11_label.c_str();
    } else if (page_number == 5) {
      btn11_label = page5_button11_label.c_str();
    } else if (page_number == 6) {
      btn11_label = page6_button11_label.c_str();
    } else if (page_number == 7) {
      btn11_label = page7_button11_label.c_str();
    } else if (page_number == 8) {
      btn11_label = page8_button11_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button11_lbrt[0] = l + 180;
    g_button11_lbrt[3] = t - (line_number * char_height);
    g_button11_lbrt[2] =
        g_button11_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button11_lbrt[1] =
        g_button11_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[10]) {
      glColor4fv(light_green);
      ButtonNumberValue = 11;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button11_lbrt[0]),
                 static_cast<GLint>(g_button11_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button11_lbrt[2]),
                 static_cast<GLint>(g_button11_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button11_lbrt[2]),
                 static_cast<GLint>(g_button11_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button11_lbrt[0]),
                 static_cast<GLint>(g_button11_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button11 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button11_lbrt[0] = g_button11_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button11_lbrt[0]),
                   static_cast<int>(g_button11_lbrt[1] + 8),
                   (char *)btn11_label, nullptr, xplmFont_Proportional);

    // Draw the Button12 button
    const char *btn12_label = nullptr;
    if (page_number == 1) {
      btn12_label = page1_button12_label.c_str();
    } else if (page_number == 2) {
      btn12_label = page2_button12_label.c_str();
    } else if (page_number == 3) {
      btn12_label = page3_button12_label.c_str();
    } else if (page_number == 4) {
      btn12_label = page4_button12_label.c_str();
    } else if (page_number == 5) {
      btn12_label = page5_button12_label.c_str();
    } else if (page_number == 6) {
      btn12_label = page6_button12_label.c_str();
    } else if (page_number == 7) {
      btn12_label = page7_button12_label.c_str();
    } else if (page_number == 8) {
      btn12_label = page8_button12_label.c_str();
    }

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_button12_lbrt[0] = l + 360;
    g_button12_lbrt[3] = t - (line_number * char_height);
    g_button12_lbrt[2] =
        g_button12_lbrt[0] +
        label_width; // *just* wide enough to fit the button text
    g_button12_lbrt[1] =
        g_button12_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (mouse_down[11]) {
      glColor4fv(light_green);
      ButtonNumberValue = 12;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_button12_lbrt[0]),
                 static_cast<GLint>(g_button12_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button12_lbrt[2]),
                 static_cast<GLint>(g_button12_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_button12_lbrt[2]),
                 static_cast<GLint>(g_button12_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_button12_lbrt[0]),
                 static_cast<GLint>(g_button12_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Button12 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_button12_lbrt[0] = g_button12_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_button12_lbrt[0]),
                   static_cast<int>(g_button12_lbrt[1] + 8),
                   (char *)btn12_label, nullptr, xplmFont_Proportional);
  }


  if ((page_number == 9) || (page_number == 10) || (page_number == 11) || (page_number == 12))
  {

      // Draw the Button1 button
      line_number = line_number + 4;
      const char *btn1_label = nullptr;
      if (page_number == 9) {
        btn1_label = page9_button1_label.c_str();
      } else if (page_number == 10) {
        btn1_label = page10_button1_label.c_str();
      } else if (page_number == 11) {
        btn1_label = page11_button1_label.c_str();
      } else if (page_number == 12) {
        btn1_label = page12_button1_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button1_lbrt[0] = l;
      g_button1_lbrt[3] = t - (line_number * char_height);
      g_button1_lbrt[2] =
          g_button1_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button1_lbrt[1] =
          g_button1_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[0]) {
        glColor4fv(light_green);
        ButtonNumberValue = 1;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button1_lbrt[0]),
                   static_cast<GLint>(g_button1_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button1_lbrt[2]),
                   static_cast<GLint>(g_button1_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button1_lbrt[2]),
                   static_cast<GLint>(g_button1_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button1_lbrt[0]),
                   static_cast<GLint>(g_button1_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button1 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button1_lbrt[0] = g_button1_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button1_lbrt[0]),
                     static_cast<int>(g_button1_lbrt[1] + 8), (char *)btn1_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button2 button
      const char *btn2_label = nullptr;
      if (page_number == 9) {
        btn2_label = page9_button2_label.c_str();
      } else if (page_number == 10) {
        btn2_label = page10_button2_label.c_str();
      } else if (page_number == 11) {
        btn2_label = page11_button2_label.c_str();
      } else if (page_number == 12) {
        btn2_label = page12_button2_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button2_lbrt[0] = l + 95;
      g_button2_lbrt[3] = t - (line_number * char_height);
      g_button2_lbrt[2] =
          g_button2_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button2_lbrt[1] =
          g_button2_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[1]) {
        glColor4fv(light_green);
        ButtonNumberValue = 2;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button2_lbrt[0]),
                   static_cast<GLint>(g_button2_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button2_lbrt[2]),
                   static_cast<GLint>(g_button2_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button2_lbrt[2]),
                   static_cast<GLint>(g_button2_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button2_lbrt[0]),
                   static_cast<GLint>(g_button2_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button2 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button2_lbrt[0] = g_button2_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button2_lbrt[0]),
                     static_cast<int>(g_button2_lbrt[1] + 8), (char *)btn2_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button3 button
      const char *btn3_label = nullptr;
      if (page_number == 9) {
        btn3_label = page9_button3_label.c_str();
      } else if (page_number == 10) {
        btn3_label = page10_button3_label.c_str();
      } else if (page_number == 11) {
        btn3_label = page11_button3_label.c_str();
      } else if (page_number == 12) {
        btn3_label = page12_button3_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button3_lbrt[0] = l + 190;
      g_button3_lbrt[3] = t - (line_number * char_height);
      g_button3_lbrt[2] =
          g_button3_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button3_lbrt[1] =
          g_button3_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[2]) {
        glColor4fv(light_green);
        ButtonNumberValue = 3;
      } else {
        glColor4fv(green);
      }

      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button3_lbrt[0]),
                   static_cast<GLint>(g_button3_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button3_lbrt[2]),
                   static_cast<GLint>(g_button3_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button3_lbrt[2]),
                   static_cast<GLint>(g_button3_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button3_lbrt[0]),
                   static_cast<GLint>(g_button3_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button3 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button3_lbrt[0] = g_button3_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button3_lbrt[0]),
                     static_cast<int>(g_button3_lbrt[1] + 8), (char *)btn3_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button4 button
      // line_number = line_number + 6;
      const char *btn4_label = nullptr;
      if (page_number == 9) {
        btn4_label = page9_button4_label.c_str();
      } else if (page_number == 10) {
        btn4_label = page10_button4_label.c_str();
      } else if (page_number == 11) {
        btn4_label = page11_button4_label.c_str();
      } else if (page_number == 12) {
        btn4_label = page12_button4_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button4_lbrt[0] = l + 285;
      g_button4_lbrt[3] = t - (line_number * char_height);
      g_button4_lbrt[2] =
          g_button4_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button4_lbrt[1] =
          g_button4_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[3]) {
        glColor4fv(light_green);
        ButtonNumberValue = 4;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button4_lbrt[0]),
                   static_cast<GLint>(g_button4_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button4_lbrt[2]),
                   static_cast<GLint>(g_button4_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button4_lbrt[2]),
                   static_cast<GLint>(g_button4_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button4_lbrt[0]),
                   static_cast<GLint>(g_button4_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button4 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button4_lbrt[0] = g_button4_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button4_lbrt[0]),
                     static_cast<int>(g_button4_lbrt[1] + 8), (char *)btn4_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button5 button
      const char *btn5_label = nullptr;
      if (page_number == 9) {
        btn5_label = page9_button5_label.c_str();
      } else if (page_number == 10) {
        btn5_label = page10_button5_label.c_str();
      } else if (page_number == 11) {
        btn5_label = page11_button5_label.c_str();
      } else if (page_number == 12) {
        btn5_label = page12_button5_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button5_lbrt[0] = l + 380;
      g_button5_lbrt[3] = t - (line_number * char_height);
      g_button5_lbrt[2] =
          g_button5_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button5_lbrt[1] =
          g_button5_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[4]) {
        glColor4fv(light_green);
        ButtonNumberValue = 5;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button5_lbrt[0]),
                   static_cast<GLint>(g_button5_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button5_lbrt[2]),
                   static_cast<GLint>(g_button5_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button5_lbrt[2]),
                   static_cast<GLint>(g_button5_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button5_lbrt[0]),
                   static_cast<GLint>(g_button5_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button5 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button5_lbrt[0] = g_button5_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button5_lbrt[0]),
                     static_cast<int>(g_button5_lbrt[1] + 8), (char *)btn5_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button6 button
      const char *btn6_label = nullptr;
      if (page_number == 9) {
        btn6_label = page9_button6_label.c_str();
      } else if (page_number == 10) {
        btn6_label = page10_button6_label.c_str();
      } else if (page_number == 11) {
        btn6_label = page11_button6_label.c_str();
      } else if (page_number == 12) {
        btn6_label = page12_button6_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button6_lbrt[0] = l + 475;
      g_button6_lbrt[3] = t - (line_number * char_height);
      g_button6_lbrt[2] =
          g_button6_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button6_lbrt[1] =
          g_button6_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[5]) {
        glColor4fv(light_green);
        ButtonNumberValue = 6;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button6_lbrt[0]),
                   static_cast<GLint>(g_button6_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button6_lbrt[2]),
                   static_cast<GLint>(g_button6_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button6_lbrt[2]),
                   static_cast<GLint>(g_button6_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button6_lbrt[0]),
                   static_cast<GLint>(g_button6_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button3 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button6_lbrt[0] = g_button6_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button6_lbrt[0]),
                     static_cast<int>(g_button6_lbrt[1] + 8), (char *)btn6_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button7 button
      line_number = line_number + 4;
      const char *btn7_label = nullptr;
      if (page_number == 9) {
        btn7_label = page9_button7_label.c_str();
      } else if (page_number == 10) {
        btn7_label = page10_button7_label.c_str();
      } else if (page_number == 11) {
        btn7_label = page11_button7_label.c_str();
      } else if (page_number == 12) {
        btn7_label = page12_button7_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button7_lbrt[0] = l;
      g_button7_lbrt[3] = t - (line_number * char_height);
      g_button7_lbrt[2] =
          g_button7_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button7_lbrt[1] =
          g_button7_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[6]) {
        glColor4fv(light_green);
        ButtonNumberValue = 7;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button7_lbrt[0]),
                   static_cast<GLint>(g_button7_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button7_lbrt[2]),
                   static_cast<GLint>(g_button7_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button7_lbrt[2]),
                   static_cast<GLint>(g_button7_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button7_lbrt[0]),
                   static_cast<GLint>(g_button7_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button7 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button7_lbrt[0] = g_button7_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button7_lbrt[0]),
                     static_cast<int>(g_button7_lbrt[1] + 8), (char *)btn7_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button8 button
      const char *btn8_label = nullptr;
      if (page_number == 9) {
        btn8_label = page9_button8_label.c_str();
      } else if (page_number == 10) {
        btn8_label = page10_button8_label.c_str();
      } else if (page_number == 11) {
        btn8_label = page11_button8_label.c_str();
      } else if (page_number == 12) {
        btn8_label = page12_button8_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button8_lbrt[0] = l + 95;
      g_button8_lbrt[3] = t - (line_number * char_height);
      g_button8_lbrt[2] =
          g_button8_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button8_lbrt[1] =
          g_button8_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[7]) {
        glColor4fv(light_green);
        ButtonNumberValue = 8;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button8_lbrt[0]),
                   static_cast<GLint>(g_button8_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button8_lbrt[2]),
                   static_cast<GLint>(g_button8_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button8_lbrt[2]),
                   static_cast<GLint>(g_button8_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button8_lbrt[0]),
                   static_cast<GLint>(g_button8_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button8 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button8_lbrt[0] = g_button8_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button8_lbrt[0]),
                     static_cast<int>(g_button8_lbrt[1] + 8), (char *)btn8_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button9 button
      const char *btn9_label = nullptr;
      if (page_number == 9) {
        btn9_label = page9_button9_label.c_str();
      } else if (page_number == 10) {
        btn9_label = page10_button9_label.c_str();
      } else if (page_number == 11) {
        btn9_label = page11_button9_label.c_str();
      } else if (page_number == 12) {
        btn9_label = page12_button9_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button9_lbrt[0] = l + 190;
      g_button9_lbrt[3] = t - (line_number * char_height);
      g_button9_lbrt[2] =
          g_button9_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button9_lbrt[1] =
          g_button9_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[8]) {
        glColor4fv(light_green);
        ButtonNumberValue = 9;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button9_lbrt[0]),
                   static_cast<GLint>(g_button9_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button9_lbrt[2]),
                   static_cast<GLint>(g_button9_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button9_lbrt[2]),
                   static_cast<GLint>(g_button9_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button9_lbrt[0]),
                   static_cast<GLint>(g_button9_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button9 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button9_lbrt[0] = g_button9_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button9_lbrt[0]),
                     static_cast<int>(g_button9_lbrt[1] + 8), (char *)btn9_label,
                     nullptr, xplmFont_Proportional);

      // Draw the Button10 button
      // line_number = line_number + 6;
      const char *btn10_label = nullptr;
      if (page_number == 9) {
        btn10_label = page9_button10_label.c_str();
      } else if (page_number == 10) {
        btn10_label = page10_button10_label.c_str();
      } else if (page_number == 11) {
        btn10_label = page11_button10_label.c_str();
      } else if (page_number == 12) {
        btn10_label = page12_button10_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button10_lbrt[0] = l + 285;
      g_button10_lbrt[3] = t - (line_number * char_height);
      g_button10_lbrt[2] =
          g_button10_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button10_lbrt[1] =
          g_button10_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[9]) {
        glColor4fv(light_green);
        ButtonNumberValue = 10;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button10_lbrt[0]),
                   static_cast<GLint>(g_button10_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button10_lbrt[2]),
                   static_cast<GLint>(g_button10_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button10_lbrt[2]),
                   static_cast<GLint>(g_button10_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button10_lbrt[0]),
                   static_cast<GLint>(g_button10_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button10 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button10_lbrt[0] = g_button10_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button10_lbrt[0]),
                     static_cast<int>(g_button10_lbrt[1] + 8),
                     (char *)btn10_label, nullptr, xplmFont_Proportional);

      // Draw the Button11 button
      const char *btn11_label = nullptr;
      if (page_number == 9) {
        btn11_label = page9_button11_label.c_str();
      } else if (page_number == 10) {
        btn11_label = page10_button11_label.c_str();
      } else if (page_number == 11) {
        btn11_label = page11_button11_label.c_str();
      } else if (page_number == 12) {
        btn11_label = page12_button11_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button11_lbrt[0] = l + 380;
      g_button11_lbrt[3] = t - (line_number * char_height);
      g_button11_lbrt[2] =
          g_button11_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button11_lbrt[1] =
          g_button11_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[10]) {
        glColor4fv(light_green);
        ButtonNumberValue = 11;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button11_lbrt[0]),
                   static_cast<GLint>(g_button11_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button11_lbrt[2]),
                   static_cast<GLint>(g_button11_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button11_lbrt[2]),
                   static_cast<GLint>(g_button11_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button11_lbrt[0]),
                   static_cast<GLint>(g_button11_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button11 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button11_lbrt[0] = g_button11_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button11_lbrt[0]),
                     static_cast<int>(g_button11_lbrt[1] + 8),
                     (char *)btn11_label, nullptr, xplmFont_Proportional);

      // Draw the Button12 button
      const char *btn12_label = nullptr;
      if (page_number == 9) {
        btn12_label = page9_button12_label.c_str();
      } else if (page_number == 10) {
        btn12_label = page10_button12_label.c_str();
      } else if (page_number == 11) {
        btn12_label = page11_button12_label.c_str();
      } else if (page_number == 12) {
        btn12_label = page12_button12_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button12_lbrt[0] = l + 475;
      g_button12_lbrt[3] = t - (line_number * char_height);
      g_button12_lbrt[2] =
          g_button12_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button12_lbrt[1] =
          g_button12_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[11]) {
        glColor4fv(light_green);
        ButtonNumberValue = 12;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button12_lbrt[0]),
                   static_cast<GLint>(g_button12_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button12_lbrt[2]),
                   static_cast<GLint>(g_button12_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button12_lbrt[2]),
                   static_cast<GLint>(g_button12_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button12_lbrt[0]),
                   static_cast<GLint>(g_button12_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button12 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button12_lbrt[0] = g_button12_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button12_lbrt[0]),
                     static_cast<int>(g_button12_lbrt[1] + 8),
                     (char *)btn12_label, nullptr, xplmFont_Proportional);


      // Draw the Button13 button
      line_number = line_number + 4;
      const char *btn13_label = nullptr;
      if (page_number == 9) {
        btn13_label = page9_button13_label.c_str();
      } else if (page_number == 10) {
        btn13_label = page10_button13_label.c_str();
      } else if (page_number == 11) {
        btn13_label = page11_button13_label.c_str();
      } else if (page_number == 12) {
        btn13_label = page12_button13_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button13_lbrt[0] = l;
      g_button13_lbrt[3] = t - (line_number * char_height);
      g_button13_lbrt[2] =
          g_button13_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button13_lbrt[1] =
          g_button13_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[12]) {
        glColor4fv(light_green);
        ButtonNumberValue = 13;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button13_lbrt[0]),
                   static_cast<GLint>(g_button13_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button13_lbrt[2]),
                   static_cast<GLint>(g_button13_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button13_lbrt[2]),
                   static_cast<GLint>(g_button13_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button13_lbrt[0]),
                   static_cast<GLint>(g_button13_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button13 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button13_lbrt[0] = g_button13_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button13_lbrt[0]),
                     static_cast<int>(g_button13_lbrt[1] + 8), (char *)btn13_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button14 button
      const char *btn14_label = nullptr;
      if (page_number == 9) {
        btn14_label = page9_button14_label.c_str();
      } else if (page_number == 10) {
        btn14_label = page10_button14_label.c_str();
      } else if (page_number == 11) {
        btn14_label = page11_button14_label.c_str();
      } else if (page_number == 12) {
        btn14_label = page12_button14_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button14_lbrt[0] = l + 95;
      g_button14_lbrt[3] = t - (line_number * char_height);
      g_button14_lbrt[2] =
          g_button14_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button14_lbrt[1] =
          g_button14_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[13]) {
        glColor4fv(light_green);
        ButtonNumberValue = 14;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button14_lbrt[0]),
                   static_cast<GLint>(g_button14_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button14_lbrt[2]),
                   static_cast<GLint>(g_button14_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button14_lbrt[2]),
                   static_cast<GLint>(g_button14_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button14_lbrt[0]),
                   static_cast<GLint>(g_button14_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button14 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button14_lbrt[0] = g_button14_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button14_lbrt[0]),
                     static_cast<int>(g_button14_lbrt[1] + 8), (char *)btn14_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button15 button
      const char *btn15_label = nullptr;
      if (page_number == 9) {
        btn15_label = page9_button15_label.c_str();
      } else if (page_number == 10) {
        btn15_label = page10_button15_label.c_str();
      } else if (page_number == 11) {
        btn15_label = page11_button15_label.c_str();
      } else if (page_number == 12) {
        btn15_label = page12_button15_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button15_lbrt[0] = l + 190;
      g_button15_lbrt[3] = t - (line_number * char_height);
      g_button15_lbrt[2] =
          g_button15_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button15_lbrt[1] =
          g_button15_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[14]) {
        glColor4fv(light_green);
        ButtonNumberValue = 15;
      } else {
        glColor4fv(green);
      }

      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button15_lbrt[0]),
                   static_cast<GLint>(g_button15_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button15_lbrt[2]),
                   static_cast<GLint>(g_button15_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button15_lbrt[2]),
                   static_cast<GLint>(g_button15_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button15_lbrt[0]),
                   static_cast<GLint>(g_button15_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button3 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button15_lbrt[0] = g_button15_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button15_lbrt[0]),
                     static_cast<int>(g_button15_lbrt[1] + 8), (char *)btn15_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button16 button
      // line_number = line_number + 6;
      const char *btn16_label = nullptr;
      if (page_number == 9) {
        btn16_label = page9_button16_label.c_str();
      } else if (page_number == 10) {
        btn16_label = page10_button16_label.c_str();
      } else if (page_number == 11) {
        btn16_label = page11_button16_label.c_str();
      } else if (page_number == 12) {
        btn16_label = page12_button16_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button16_lbrt[0] = l + 285;
      g_button16_lbrt[3] = t - (line_number * char_height);
      g_button16_lbrt[2] =
          g_button16_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button16_lbrt[1] =
          g_button16_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[15]) {
        glColor4fv(light_green);
        ButtonNumberValue = 16;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button16_lbrt[0]),
                   static_cast<GLint>(g_button16_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button16_lbrt[2]),
                   static_cast<GLint>(g_button16_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button16_lbrt[2]),
                   static_cast<GLint>(g_button16_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button16_lbrt[0]),
                   static_cast<GLint>(g_button16_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button16 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button16_lbrt[0] = g_button16_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button16_lbrt[0]),
                     static_cast<int>(g_button16_lbrt[1] + 8), (char *)btn16_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button17 button
      const char *btn17_label = nullptr;
      if (page_number == 9) {
        btn17_label = page9_button17_label.c_str();
      } else if (page_number == 10) {
        btn17_label = page10_button17_label.c_str();
      } else if (page_number == 11) {
        btn17_label = page11_button17_label.c_str();
      } else if (page_number == 12) {
        btn17_label = page12_button17_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button17_lbrt[0] = l + 380;
      g_button17_lbrt[3] = t - (line_number * char_height);
      g_button17_lbrt[2] =
          g_button17_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button17_lbrt[1] =
          g_button17_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[16]) {
        glColor4fv(light_green);
        ButtonNumberValue = 17;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button17_lbrt[0]),
                   static_cast<GLint>(g_button17_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button17_lbrt[2]),
                   static_cast<GLint>(g_button17_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button17_lbrt[2]),
                   static_cast<GLint>(g_button17_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button17_lbrt[0]),
                   static_cast<GLint>(g_button17_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button17 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button17_lbrt[0] = g_button17_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button17_lbrt[0]),
                     static_cast<int>(g_button17_lbrt[1] + 8), (char *)btn17_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button18 button
      const char *btn18_label = nullptr;
      if (page_number == 9) {
        btn18_label = page9_button18_label.c_str();
      } else if (page_number == 10) {
        btn18_label = page10_button18_label.c_str();
      } else if (page_number == 11) {
        btn18_label = page11_button18_label.c_str();
      } else if (page_number == 12) {
        btn18_label = page12_button18_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button18_lbrt[0] = l + 475;
      g_button18_lbrt[3] = t - (line_number * char_height);
      g_button18_lbrt[2] =
          g_button18_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button18_lbrt[1] =
          g_button18_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[17]) {
        glColor4fv(light_green);
        ButtonNumberValue = 18;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button18_lbrt[0]),
                   static_cast<GLint>(g_button18_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button18_lbrt[2]),
                   static_cast<GLint>(g_button18_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button18_lbrt[2]),
                   static_cast<GLint>(g_button18_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button18_lbrt[0]),
                   static_cast<GLint>(g_button18_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button3 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button18_lbrt[0] = g_button18_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button18_lbrt[0]),
                     static_cast<int>(g_button18_lbrt[1] + 8), (char *)btn18_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button19 button
      line_number = line_number + 4;
      const char *btn19_label = nullptr;
      if (page_number == 9) {
        btn19_label = page9_button19_label.c_str();
      } else if (page_number == 10) {
        btn19_label = page10_button19_label.c_str();
      } else if (page_number == 11) {
        btn19_label = page11_button19_label.c_str();
      } else if (page_number == 12) {
        btn19_label = page12_button19_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button19_lbrt[0] = l;
      g_button19_lbrt[3] = t - (line_number * char_height);
      g_button19_lbrt[2] =
          g_button19_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button19_lbrt[1] =
          g_button19_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[18]) {
        glColor4fv(light_green);
        ButtonNumberValue = 19;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button19_lbrt[0]),
                   static_cast<GLint>(g_button19_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button19_lbrt[2]),
                   static_cast<GLint>(g_button19_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button19_lbrt[2]),
                   static_cast<GLint>(g_button19_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button19_lbrt[0]),
                   static_cast<GLint>(g_button19_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button19 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button19_lbrt[0] = g_button19_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button19_lbrt[0]),
                     static_cast<int>(g_button19_lbrt[1] + 8), (char *)btn19_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button20 button
      const char *btn20_label = nullptr;
      if (page_number == 9) {
        btn20_label = page9_button20_label.c_str();
      } else if (page_number == 10) {
        btn20_label = page10_button20_label.c_str();
      } else if (page_number == 11) {
        btn20_label = page11_button20_label.c_str();
      } else if (page_number == 12) {
        btn20_label = page12_button20_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button20_lbrt[0] = l + 95;
      g_button20_lbrt[3] = t - (line_number * char_height);
      g_button20_lbrt[2] =
          g_button20_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button20_lbrt[1] =
          g_button20_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[19]) {
        glColor4fv(light_green);
        ButtonNumberValue = 20;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button20_lbrt[0]),
                   static_cast<GLint>(g_button20_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button20_lbrt[2]),
                   static_cast<GLint>(g_button20_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button20_lbrt[2]),
                   static_cast<GLint>(g_button20_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button20_lbrt[0]),
                   static_cast<GLint>(g_button20_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button20 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button20_lbrt[0] = g_button20_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button20_lbrt[0]),
                     static_cast<int>(g_button20_lbrt[1] + 8), (char *)btn20_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button21 button
      const char *btn21_label = nullptr;
      if (page_number == 9) {
        btn21_label = page9_button21_label.c_str();
      } else if (page_number == 10) {
        btn21_label = page10_button21_label.c_str();
      } else if (page_number == 11) {
        btn21_label = page11_button21_label.c_str();
      } else if (page_number == 12) {
        btn21_label = page12_button21_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button21_lbrt[0] = l + 190;
      g_button21_lbrt[3] = t - (line_number * char_height);
      g_button21_lbrt[2] =
          g_button21_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button21_lbrt[1] =
          g_button21_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[20]) {
        glColor4fv(light_green);
        ButtonNumberValue = 21;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button21_lbrt[0]),
                   static_cast<GLint>(g_button21_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button21_lbrt[2]),
                   static_cast<GLint>(g_button21_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button21_lbrt[2]),
                   static_cast<GLint>(g_button21_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button21_lbrt[0]),
                   static_cast<GLint>(g_button21_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button21 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button21_lbrt[0] = g_button21_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button21_lbrt[0]),
                     static_cast<int>(g_button21_lbrt[1] + 8), (char *)btn21_label,
                     nullptr, xplmFont_Proportional);


      // Draw the Button22 button
      // line_number = line_number + 6;
      const char *btn22_label = nullptr;
      if (page_number == 9) {
        btn22_label = page9_button22_label.c_str();
      } else if (page_number == 10) {
        btn22_label = page10_button22_label.c_str();
      } else if (page_number == 11) {
        btn22_label = page11_button22_label.c_str();
      } else if (page_number == 12) {
        btn22_label = page12_button22_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button22_lbrt[0] = l + 285;
      g_button22_lbrt[3] = t - (line_number * char_height);
      g_button22_lbrt[2] =
          g_button22_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button22_lbrt[1] =
          g_button22_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[21]) {
        glColor4fv(light_green);
        ButtonNumberValue = 22;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button22_lbrt[0]),
                   static_cast<GLint>(g_button22_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button22_lbrt[2]),
                   static_cast<GLint>(g_button22_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button22_lbrt[2]),
                   static_cast<GLint>(g_button22_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button22_lbrt[0]),
                   static_cast<GLint>(g_button22_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button22 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button22_lbrt[0] = g_button22_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button22_lbrt[0]),
                     static_cast<int>(g_button22_lbrt[1] + 8),
                     (char *)btn22_label, nullptr, xplmFont_Proportional);


      // Draw the Button23 button
      const char *btn23_label = nullptr;
      if (page_number == 9) {
        btn23_label = page9_button23_label.c_str();
      } else if (page_number == 10) {
        btn23_label = page10_button23_label.c_str();
      } else if (page_number == 11) {
        btn23_label = page11_button23_label.c_str();
      } else if (page_number == 12) {
        btn23_label = page12_button23_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button23_lbrt[0] = l + 380;
      g_button23_lbrt[3] = t - (line_number * char_height);
      g_button23_lbrt[2] =
          g_button23_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button23_lbrt[1] =
          g_button23_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[22]) {
        glColor4fv(light_green);
        ButtonNumberValue = 23;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button23_lbrt[0]),
                   static_cast<GLint>(g_button23_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button23_lbrt[2]),
                   static_cast<GLint>(g_button23_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button23_lbrt[2]),
                   static_cast<GLint>(g_button23_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button23_lbrt[0]),
                   static_cast<GLint>(g_button23_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button23 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button23_lbrt[0] = g_button23_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button23_lbrt[0]),
                     static_cast<int>(g_button23_lbrt[1] + 8),
                     (char *)btn23_label, nullptr, xplmFont_Proportional);


      // Draw the Button24 button
      const char *btn24_label = nullptr;
      if (page_number == 9) {
        btn24_label = page9_button24_label.c_str();
      } else if (page_number == 10) {
        btn24_label = page10_button24_label.c_str();
      } else if (page_number == 11) {
        btn24_label = page11_button24_label.c_str();
      } else if (page_number == 12) {
        btn24_label = page12_button24_label.c_str();
      }

      // 0 left, 1 bottom, 2 right, 3 top
      // Position the button in the upper left of the window (sized to fit the
      // button text)
      g_button24_lbrt[0] = l + 475;
      g_button24_lbrt[3] = t - (line_number * char_height);
      g_button24_lbrt[2] =
          g_button24_lbrt[0] +
          mid_label_width; // *just* wide enough to fit the button text
      g_button24_lbrt[1] =
          g_button24_lbrt[3] -
          (2.00f * char_height); // a bit taller than the button text

      // Draw the box around our rudimentary button
      if (mouse_down[23]) {
        glColor4fv(light_green);
        ButtonNumberValue = 24;
      } else {
        glColor4fv(green);
      }
      glBegin(GL_POLYGON);
      {
        glVertex2i(static_cast<GLint>(g_button24_lbrt[0]),
                   static_cast<GLint>(g_button24_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button24_lbrt[2]),
                   static_cast<GLint>(g_button24_lbrt[3]));
        glVertex2i(static_cast<GLint>(g_button24_lbrt[2]),
                   static_cast<GLint>(g_button24_lbrt[1]));
        glVertex2i(static_cast<GLint>(g_button24_lbrt[0]),
                   static_cast<GLint>(g_button24_lbrt[1]));
      }
      glEnd();

      // Draw the text on the Button12 button.
      // 0 left, 1 bottom, 2 right, 3 top
      g_button24_lbrt[0] = g_button24_lbrt[0] + 5;
      XPLMDrawString(col_black, static_cast<int>(g_button24_lbrt[0]),
                     static_cast<int>(g_button24_lbrt[1] + 8),
                     (char *)btn24_label, nullptr, xplmFont_Proportional);

  }

  // Radio Page
  if (page_number == 13) {

    // Draw the Number7 button
    line_number = line_number + 4;
    const char *number7_btn_label;
    number7_btn_label = "7";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number7_button_lbrt[0] = l;
    g_number7_button_lbrt[3] = t - (line_number * char_height);
    g_number7_button_lbrt[2] =
        g_number7_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number7_button_lbrt[1] =
        g_number7_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number7_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 1;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number7_button_lbrt[0]),
                 static_cast<GLint>(g_number7_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number7_button_lbrt[2]),
                 static_cast<GLint>(g_number7_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number7_button_lbrt[2]),
                 static_cast<GLint>(g_number7_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number7_button_lbrt[0]),
                 static_cast<GLint>(g_number7_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number7 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number7_button_lbrt[0] = g_number7_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number7_button_lbrt[0]),
                   static_cast<int>(g_number7_button_lbrt[1] + 8),
                   (char *)number7_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number8 button
    const char *number8_btn_label;
    number8_btn_label = "8";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number8_button_lbrt[0] = l + 80;
    g_number8_button_lbrt[3] = t - (line_number * char_height);
    g_number8_button_lbrt[2] =
        g_number8_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number8_button_lbrt[1] =
        g_number8_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number8_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 2;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number8_button_lbrt[0]),
                 static_cast<GLint>(g_number8_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number8_button_lbrt[2]),
                 static_cast<GLint>(g_number8_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number8_button_lbrt[2]),
                 static_cast<GLint>(g_number8_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number8_button_lbrt[0]),
                 static_cast<GLint>(g_number8_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number8 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number8_button_lbrt[0] = g_number8_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number8_button_lbrt[0]),
                   static_cast<int>(g_number8_button_lbrt[1] + 8),
                   (char *)number8_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number9 button
    const char *number9_btn_label;
    number9_btn_label = "9";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number9_button_lbrt[0] = l + 160;
    g_number9_button_lbrt[3] = t - (line_number * char_height);
    g_number9_button_lbrt[2] =
        g_number9_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number9_button_lbrt[1] =
        g_number9_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number9_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 3;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number9_button_lbrt[0]),
                 static_cast<GLint>(g_number9_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number9_button_lbrt[2]),
                 static_cast<GLint>(g_number9_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number9_button_lbrt[2]),
                 static_cast<GLint>(g_number9_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number9_button_lbrt[0]),
                 static_cast<GLint>(g_number9_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number9 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number9_button_lbrt[0] = g_number9_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number9_button_lbrt[0]),
                   static_cast<int>(g_number9_button_lbrt[1] + 8),
                   (char *)number9_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Com1 Active button
    const char *com1a_btn_label;
    com1a_btn_label = "Com1 A";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_com1a_button_lbrt[0] = l + 240;
    g_com1a_button_lbrt[3] = t - (line_number * char_height);
    g_com1a_button_lbrt[2] =
        g_com1a_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_com1a_button_lbrt[1] =
        g_com1a_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (com1a_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 4;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_com1a_button_lbrt[0]),
                 static_cast<GLint>(g_com1a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_com1a_button_lbrt[2]),
                 static_cast<GLint>(g_com1a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_com1a_button_lbrt[2]),
                 static_cast<GLint>(g_com1a_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_com1a_button_lbrt[0]),
                 static_cast<GLint>(g_com1a_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Com1 active button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_com1a_button_lbrt[0] = g_com1a_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_com1a_button_lbrt[0]),
                   static_cast<int>(g_com1a_button_lbrt[1] + 8),
                   (char *)com1a_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Com1 Standby button
    const char *com1s_btn_label;
    com1s_btn_label = "Com1 S";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_com1s_button_lbrt[0] = l + 320;
    g_com1s_button_lbrt[3] = t - (line_number * char_height);
    g_com1s_button_lbrt[2] =
        g_com1s_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_com1s_button_lbrt[1] =
        g_com1s_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (com1s_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 5;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_com1s_button_lbrt[0]),
                 static_cast<GLint>(g_com1s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_com1s_button_lbrt[2]),
                 static_cast<GLint>(g_com1s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_com1s_button_lbrt[2]),
                 static_cast<GLint>(g_com1s_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_com1s_button_lbrt[0]),
                 static_cast<GLint>(g_com1s_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Com1 standby button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_com1s_button_lbrt[0] = g_com1s_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_com1s_button_lbrt[0]),
                   static_cast<int>(g_com1s_button_lbrt[1] + 8),
                   (char *)com1s_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Adf1 Active button
    const char *adf1a_btn_label;
    adf1a_btn_label = "Adf1 A";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_adf1a_button_lbrt[0] = l + 400;
    g_adf1a_button_lbrt[3] = t - (line_number * char_height);
    g_adf1a_button_lbrt[2] =
        g_adf1a_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_adf1a_button_lbrt[1] =
        g_adf1a_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (adf1a_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 6;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_adf1a_button_lbrt[0]),
                 static_cast<GLint>(g_adf1a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_adf1a_button_lbrt[2]),
                 static_cast<GLint>(g_adf1a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_adf1a_button_lbrt[2]),
                 static_cast<GLint>(g_adf1a_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_adf1a_button_lbrt[0]),
                 static_cast<GLint>(g_adf1a_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Adf1 active button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_adf1a_button_lbrt[0] = g_adf1a_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_adf1a_button_lbrt[0]),
                   static_cast<int>(g_adf1a_button_lbrt[1] + 8),
                   (char *)adf1a_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Adf1 Standby button
    const char *adf1s_btn_label;
    adf1s_btn_label = "Adf1 S";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_adf1s_button_lbrt[0] = l + 480;
    g_adf1s_button_lbrt[3] = t - (line_number * char_height);
    g_adf1s_button_lbrt[2] =
        g_adf1s_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_adf1s_button_lbrt[1] =
        g_adf1s_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (adf1s_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 7;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_adf1s_button_lbrt[0]),
                 static_cast<GLint>(g_adf1s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_adf1s_button_lbrt[2]),
                 static_cast<GLint>(g_adf1s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_adf1s_button_lbrt[2]),
                 static_cast<GLint>(g_adf1s_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_adf1s_button_lbrt[0]),
                 static_cast<GLint>(g_adf1s_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Com1 standby button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_adf1s_button_lbrt[0] = g_adf1s_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_adf1s_button_lbrt[0]),
                   static_cast<int>(g_adf1s_button_lbrt[1] + 8),
                   (char *)adf1s_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number4 button
    line_number = line_number + 4;
    const char *number4_btn_label;
    number4_btn_label = "4";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number4_button_lbrt[0] = l;
    g_number4_button_lbrt[3] = t - (line_number * char_height);
    g_number4_button_lbrt[2] =
        g_number4_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number4_button_lbrt[1] =
        g_number4_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number4_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 8;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number4_button_lbrt[0]),
                 static_cast<GLint>(g_number4_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number4_button_lbrt[2]),
                 static_cast<GLint>(g_number4_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number4_button_lbrt[2]),
                 static_cast<GLint>(g_number4_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number4_button_lbrt[0]),
                 static_cast<GLint>(g_number4_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number4 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number4_button_lbrt[0] = g_number4_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number4_button_lbrt[0]),
                   static_cast<int>(g_number4_button_lbrt[1] + 8),
                   (char *)number4_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number5 button
    const char *number5_btn_label;
    number5_btn_label = "5";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number5_button_lbrt[0] = l + 80;
    g_number5_button_lbrt[3] = t - (line_number * char_height);
    g_number5_button_lbrt[2] =
        g_number5_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number5_button_lbrt[1] =
        g_number5_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number5_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 9;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number5_button_lbrt[0]),
                 static_cast<GLint>(g_number5_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number5_button_lbrt[2]),
                 static_cast<GLint>(g_number5_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number5_button_lbrt[2]),
                 static_cast<GLint>(g_number5_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number5_button_lbrt[0]),
                 static_cast<GLint>(g_number5_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number5 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number5_button_lbrt[0] = g_number5_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number5_button_lbrt[0]),
                   static_cast<int>(g_number5_button_lbrt[1] + 8),
                   (char *)number5_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number6 button
    const char *number6_btn_label;
    number6_btn_label = "6";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number6_button_lbrt[0] = l + 160;
    g_number6_button_lbrt[3] = t - (line_number * char_height);
    g_number6_button_lbrt[2] =
        g_number6_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number6_button_lbrt[1] =
        g_number6_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number6_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 10;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number6_button_lbrt[0]),
                 static_cast<GLint>(g_number6_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number6_button_lbrt[2]),
                 static_cast<GLint>(g_number6_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number6_button_lbrt[2]),
                 static_cast<GLint>(g_number6_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number6_button_lbrt[0]),
                 static_cast<GLint>(g_number6_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number6 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number6_button_lbrt[0] = g_number6_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number6_button_lbrt[0]),
                   static_cast<int>(g_number6_button_lbrt[1] + 8),
                   (char *)number6_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Com2 Active button
    const char *com2a_btn_label;
    com2a_btn_label = "Com2 A";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_com2a_button_lbrt[0] = l + 240;
    g_com2a_button_lbrt[3] = t - (line_number * char_height);
    g_com2a_button_lbrt[2] =
        g_com2a_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_com2a_button_lbrt[1] =
        g_com2a_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (com2a_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 11;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_com2a_button_lbrt[0]),
                 static_cast<GLint>(g_com2a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_com2a_button_lbrt[2]),
                 static_cast<GLint>(g_com2a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_com2a_button_lbrt[2]),
                 static_cast<GLint>(g_com2a_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_com2a_button_lbrt[0]),
                 static_cast<GLint>(g_com2a_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Com2 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_com2a_button_lbrt[0] = g_com2a_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_com2a_button_lbrt[0]),
                   static_cast<int>(g_com2a_button_lbrt[1] + 8),
                   (char *)com2a_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Com2 Standby button
    const char *com2s_btn_label;
    com2s_btn_label = "Com2 S";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_com2s_button_lbrt[0] = l + 320;
    g_com2s_button_lbrt[3] = t - (line_number * char_height);
    g_com2s_button_lbrt[2] =
        g_com2s_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_com2s_button_lbrt[1] =
        g_com2s_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (com2s_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 12;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_com2s_button_lbrt[0]),
                 static_cast<GLint>(g_com2s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_com2s_button_lbrt[2]),
                 static_cast<GLint>(g_com2s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_com2s_button_lbrt[2]),
                 static_cast<GLint>(g_com2s_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_com2s_button_lbrt[0]),
                 static_cast<GLint>(g_com2s_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Com2 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_com2s_button_lbrt[0] = g_com2s_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_com2s_button_lbrt[0]),
                   static_cast<int>(g_com2s_button_lbrt[1] + 8),
                   (char *)com2s_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Adf2 Active button
    const char *adf2a_btn_label;
    adf2a_btn_label = "Adf2 A";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_adf2a_button_lbrt[0] = l + 400;
    g_adf2a_button_lbrt[3] = t - (line_number * char_height);
    g_adf2a_button_lbrt[2] =
        g_adf2a_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_adf2a_button_lbrt[1] =
        g_adf2a_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (adf2a_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 13;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_adf2a_button_lbrt[0]),
                 static_cast<GLint>(g_adf2a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_adf2a_button_lbrt[2]),
                 static_cast<GLint>(g_adf2a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_adf2a_button_lbrt[2]),
                 static_cast<GLint>(g_adf2a_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_adf2a_button_lbrt[0]),
                 static_cast<GLint>(g_adf2a_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Afd2 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_adf2a_button_lbrt[0] = g_adf2a_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_adf2a_button_lbrt[0]),
                   static_cast<int>(g_adf2a_button_lbrt[1] + 8),
                   (char *)adf2a_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Afd2 Standby button
    const char *adf2s_btn_label;
    adf2s_btn_label = "Afd2 S";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_adf2s_button_lbrt[0] = l + 480;
    g_adf2s_button_lbrt[3] = t - (line_number * char_height);
    g_adf2s_button_lbrt[2] =
        g_adf2s_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_adf2s_button_lbrt[1] =
        g_adf2s_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (adf2s_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 14;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_adf2s_button_lbrt[0]),
                 static_cast<GLint>(g_adf2s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_adf2s_button_lbrt[2]),
                 static_cast<GLint>(g_adf2s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_adf2s_button_lbrt[2]),
                 static_cast<GLint>(g_adf2s_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_adf2s_button_lbrt[0]),
                 static_cast<GLint>(g_adf2s_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Afd2 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_adf2s_button_lbrt[0] = g_adf2s_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_adf2s_button_lbrt[0]),
                   static_cast<int>(g_adf2s_button_lbrt[1] + 8),
                   (char *)adf2s_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number1 button
    line_number = line_number + 4;
    const char *number1_btn_label;
    number1_btn_label = "1";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number1_button_lbrt[0] = l;
    g_number1_button_lbrt[3] = t - (line_number * char_height);
    g_number1_button_lbrt[2] =
        g_number1_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number1_button_lbrt[1] =
        g_number1_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number1_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 15;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number1_button_lbrt[0]),
                 static_cast<GLint>(g_number1_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number1_button_lbrt[2]),
                 static_cast<GLint>(g_number1_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number1_button_lbrt[2]),
                 static_cast<GLint>(g_number1_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number1_button_lbrt[0]),
                 static_cast<GLint>(g_number1_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number1 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number1_button_lbrt[0] = g_number1_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number1_button_lbrt[0]),
                   static_cast<int>(g_number1_button_lbrt[1] + 8),
                   (char *)number1_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number2 button
    const char *number2_btn_label;
    number2_btn_label = "2";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number2_button_lbrt[0] = l + 80;
    g_number2_button_lbrt[3] = t - (line_number * char_height);
    g_number2_button_lbrt[2] =
        g_number2_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number2_button_lbrt[1] =
        g_number2_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number2_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 16;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number2_button_lbrt[0]),
                 static_cast<GLint>(g_number2_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number2_button_lbrt[2]),
                 static_cast<GLint>(g_number2_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number2_button_lbrt[2]),
                 static_cast<GLint>(g_number2_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number2_button_lbrt[0]),
                 static_cast<GLint>(g_number2_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number2 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number2_button_lbrt[0] = g_number2_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number2_button_lbrt[0]),
                   static_cast<int>(g_number2_button_lbrt[1] + 8),
                   (char *)number2_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number3 button
    const char *number3_btn_label;
    number3_btn_label = "3";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number3_button_lbrt[0] = l + 160;
    g_number3_button_lbrt[3] = t - (line_number * char_height);
    g_number3_button_lbrt[2] =
        g_number3_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number3_button_lbrt[1] =
        g_number3_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number3_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 17;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number3_button_lbrt[0]),
                 static_cast<GLint>(g_number3_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number3_button_lbrt[2]),
                 static_cast<GLint>(g_number3_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number3_button_lbrt[2]),
                 static_cast<GLint>(g_number3_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number3_button_lbrt[0]),
                 static_cast<GLint>(g_number3_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number3 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number3_button_lbrt[0] = g_number3_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number3_button_lbrt[0]),
                   static_cast<int>(g_number3_button_lbrt[1] + 8),
                   (char *)number3_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Nav1 active button
    const char *nav1a_btn_label;
    nav1a_btn_label = "Nav1 A";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_nav1a_button_lbrt[0] = l + 240;
    g_nav1a_button_lbrt[3] = t - (line_number * char_height);
    g_nav1a_button_lbrt[2] =
        g_nav1a_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_nav1a_button_lbrt[1] =
        g_nav1a_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (nav1a_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 18;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_nav1a_button_lbrt[0]),
                 static_cast<GLint>(g_nav1a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_nav1a_button_lbrt[2]),
                 static_cast<GLint>(g_nav1a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_nav1a_button_lbrt[2]),
                 static_cast<GLint>(g_nav1a_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_nav1a_button_lbrt[0]),
                 static_cast<GLint>(g_nav1a_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Nav1 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_nav1a_button_lbrt[0] = g_nav1a_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_nav1a_button_lbrt[0]),
                   static_cast<int>(g_nav1a_button_lbrt[1] + 8),
                   (char *)nav1a_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Nav1 standby button
    const char *nav1s_btn_label;
    nav1s_btn_label = "Nav1 S";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_nav1s_button_lbrt[0] = l + 320;
    g_nav1s_button_lbrt[3] = t - (line_number * char_height);
    g_nav1s_button_lbrt[2] =
        g_nav1s_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_nav1s_button_lbrt[1] =
        g_nav1s_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (nav1s_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 19;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_nav1s_button_lbrt[0]),
                 static_cast<GLint>(g_nav1s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_nav1s_button_lbrt[2]),
                 static_cast<GLint>(g_nav1s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_nav1s_button_lbrt[2]),
                 static_cast<GLint>(g_nav1s_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_nav1s_button_lbrt[0]),
                 static_cast<GLint>(g_nav1s_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Nav1 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_nav1s_button_lbrt[0] = g_nav1s_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_nav1s_button_lbrt[0]),
                   static_cast<int>(g_nav1s_button_lbrt[1] + 8),
                   (char *)nav1s_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Number0 button
    line_number = line_number + 4;
    const char *number0_btn_label;
    number0_btn_label = "0";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_number0_button_lbrt[0] = l;
    g_number0_button_lbrt[3] = t - (line_number * char_height);
    g_number0_button_lbrt[2] =
        g_number0_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_number0_button_lbrt[1] =
        g_number0_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number0_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 20;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_number0_button_lbrt[0]),
                 static_cast<GLint>(g_number0_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number0_button_lbrt[2]),
                 static_cast<GLint>(g_number0_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_number0_button_lbrt[2]),
                 static_cast<GLint>(g_number0_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_number0_button_lbrt[0]),
                 static_cast<GLint>(g_number0_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Number0 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_number0_button_lbrt[0] = g_number0_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_number0_button_lbrt[0]),
                   static_cast<int>(g_number0_button_lbrt[1] + 8),
                   (char *)number0_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Radio Freq button
    const char *radio_freq_btn_label;
    char radio_buffer[10] = {};

    if (radio_Vector_size == 1) {
      sprintf(radio_buffer, "%d\n", xbtn2cmd_radio_Vector[0]);
    }
    if (radio_Vector_size == 2) {
      sprintf(radio_buffer, "%d%d\n", xbtn2cmd_radio_Vector[0],
              xbtn2cmd_radio_Vector[1]);
    }
    if (radio_Vector_size == 3) {
      sprintf(radio_buffer, "%d%d%d\n", xbtn2cmd_radio_Vector[0],
              xbtn2cmd_radio_Vector[1], xbtn2cmd_radio_Vector[2]);
    }
    if (radio_Vector_size == 4) {
      sprintf(radio_buffer, "%d%d%d%d\n", xbtn2cmd_radio_Vector[0],
              xbtn2cmd_radio_Vector[1], xbtn2cmd_radio_Vector[2],
              xbtn2cmd_radio_Vector[3]);
    }
    if (radio_Vector_size == 5) {
      sprintf(radio_buffer, "%d%d%d%d%d\n", xbtn2cmd_radio_Vector[0],
              xbtn2cmd_radio_Vector[1], xbtn2cmd_radio_Vector[2],
              xbtn2cmd_radio_Vector[3], xbtn2cmd_radio_Vector[4]);
    }

    radio_freq_btn_label = radio_buffer;

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_radio_freq_button_lbrt[0] = l + 80;
    g_radio_freq_button_lbrt[3] = t - (line_number * char_height);
    g_radio_freq_button_lbrt[2] =
        g_radio_freq_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_radio_freq_button_lbrt[1] =
        g_radio_freq_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (number9_mouse_down) {
      glColor4fv(light_green);
    } else {
      glColor4fv(green);
    }
    glColor4fv(green);
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_radio_freq_button_lbrt[0]),
                 static_cast<GLint>(g_radio_freq_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_radio_freq_button_lbrt[2]),
                 static_cast<GLint>(g_radio_freq_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_radio_freq_button_lbrt[2]),
                 static_cast<GLint>(g_radio_freq_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_radio_freq_button_lbrt[0]),
                 static_cast<GLint>(g_radio_freq_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Radio Freq button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_radio_freq_button_lbrt[0] = g_radio_freq_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_radio_freq_button_lbrt[0]),
                   static_cast<int>(g_radio_freq_button_lbrt[1] + 8),
                   (char *)radio_freq_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the clear button
    const char *clear_btn_label;
    clear_btn_label = "Clr";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_clear_button_lbrt[0] = l + 160;
    g_clear_button_lbrt[3] = t - (line_number * char_height);
    g_clear_button_lbrt[2] =
        g_clear_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_clear_button_lbrt[1] =
        g_clear_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (clear_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 21;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_clear_button_lbrt[0]),
                 static_cast<GLint>(g_clear_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_clear_button_lbrt[2]),
                 static_cast<GLint>(g_clear_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_clear_button_lbrt[2]),
                 static_cast<GLint>(g_clear_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_clear_button_lbrt[0]),
                 static_cast<GLint>(g_clear_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the clear button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_clear_button_lbrt[0] = g_clear_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_clear_button_lbrt[0]),
                   static_cast<int>(g_clear_button_lbrt[1] + 8),
                   (char *)clear_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Nav2 active button
    const char *nav2a_btn_label;
    nav2a_btn_label = "Nav2 A";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_nav2a_button_lbrt[0] = l + 240;
    g_nav2a_button_lbrt[3] = t - (line_number * char_height);
    g_nav2a_button_lbrt[2] =
        g_nav2a_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_nav2a_button_lbrt[1] =
        g_nav2a_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (nav2a_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 22;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_nav2a_button_lbrt[0]),
                 static_cast<GLint>(g_nav2a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_nav2a_button_lbrt[2]),
                 static_cast<GLint>(g_nav2a_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_nav2a_button_lbrt[2]),
                 static_cast<GLint>(g_nav2a_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_nav2a_button_lbrt[0]),
                 static_cast<GLint>(g_nav2a_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Nav2 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_nav2a_button_lbrt[0] = g_nav2a_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_nav2a_button_lbrt[0]),
                   static_cast<int>(g_nav2a_button_lbrt[1] + 8),
                   (char *)nav2a_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Nav2 standby button
    const char *nav2s_btn_label;
    nav2s_btn_label = "Nav2 S";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_nav2s_button_lbrt[0] = l + 320;
    g_nav2s_button_lbrt[3] = t - (line_number * char_height);
    g_nav2s_button_lbrt[2] =
        g_nav2s_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_nav2s_button_lbrt[1] =
        g_nav2s_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (nav2s_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 22;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_nav2s_button_lbrt[0]),
                 static_cast<GLint>(g_nav2s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_nav2s_button_lbrt[2]),
                 static_cast<GLint>(g_nav2s_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_nav2s_button_lbrt[2]),
                 static_cast<GLint>(g_nav2s_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_nav2s_button_lbrt[0]),
                 static_cast<GLint>(g_nav2s_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Nav2 button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_nav2s_button_lbrt[0] = g_nav2s_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_nav2s_button_lbrt[0]),
                   static_cast<int>(g_nav2s_button_lbrt[1] + 8),
                   (char *)nav2s_btn_label, nullptr, xplmFont_Proportional);
  }

  // g430n1 Page
  if (page_number == 14) {

    // Draw the Com FF button
    line_number = line_number + 4;
    const char *g_430n1_com_ff_btn_label;
    g_430n1_com_ff_btn_label = "Com FF";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_com_ff_button_lbrt[0] = l;
    g_430n1_com_ff_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_com_ff_button_lbrt[2] =
        g_430n1_com_ff_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_com_ff_button_lbrt[1] =
        g_430n1_com_ff_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_com_ff_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 1;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_com_ff_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_com_ff_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_com_ff_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_com_ff_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_com_ff_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_com_ff_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_com_ff_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_com_ff_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Com FF button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_com_ff_button_lbrt[0] = g_430n1_com_ff_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_com_ff_button_lbrt[0]),
                   static_cast<int>(g_430n1_com_ff_button_lbrt[1] + 8),
                   (char *)g_430n1_com_ff_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Nav FF button
    const char *g_430n1_nav_ff_btn_label;
    g_430n1_nav_ff_btn_label = "Nav FF";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_nav_ff_button_lbrt[0] = l + 75;
    g_430n1_nav_ff_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_nav_ff_button_lbrt[2] =
        g_430n1_nav_ff_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_nav_ff_button_lbrt[1] =
        g_430n1_nav_ff_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_nav_ff_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 2;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_nav_ff_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_nav_ff_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_nav_ff_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_nav_ff_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_nav_ff_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_nav_ff_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_nav_ff_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_nav_ff_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Nav FF button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_nav_ff_button_lbrt[0] = g_430n1_nav_ff_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_nav_ff_button_lbrt[0]),
                   static_cast<int>(g_430n1_nav_ff_button_lbrt[1] + 8),
                   (char *)g_430n1_nav_ff_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Zoom In button
    const char *g_430n1_zoom_in_btn_label;
    g_430n1_zoom_in_btn_label = "Zoom In";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_zoom_in_button_lbrt[0] = l + 290;
    g_430n1_zoom_in_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_zoom_in_button_lbrt[2] =
        g_430n1_zoom_in_button_lbrt[0] + small_button_width +
        5; // *just* wide enough to fit the button text
    g_430n1_zoom_in_button_lbrt[1] =
        g_430n1_zoom_in_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_zoom_in_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 3;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_zoom_in_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_zoom_in_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_zoom_in_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_zoom_in_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_zoom_in_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_zoom_in_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_zoom_in_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_zoom_in_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Zoom In button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_zoom_in_button_lbrt[0] = g_430n1_zoom_in_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_zoom_in_button_lbrt[0]),
                   static_cast<int>(g_430n1_zoom_in_button_lbrt[1] + 8),
                   (char *)g_430n1_zoom_in_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Zoom Out button
    const char *g_430n1_zoom_out_btn_label;
    g_430n1_zoom_out_btn_label = "Zoom Out";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_zoom_out_button_lbrt[0] = l + 375;
    g_430n1_zoom_out_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_zoom_out_button_lbrt[2] =
        g_430n1_zoom_out_button_lbrt[0] + small_button_width +
        9; // *just* wide enough to fit the button text
    g_430n1_zoom_out_button_lbrt[1] =
        g_430n1_zoom_out_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_zoom_out_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 4;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_zoom_out_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_zoom_out_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_zoom_out_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_zoom_out_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_zoom_out_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_zoom_out_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_zoom_out_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_zoom_out_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Zoom Out button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_zoom_out_button_lbrt[0] = g_430n1_zoom_out_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n1_zoom_out_button_lbrt[0]),
                   static_cast<int>(g_430n1_zoom_out_button_lbrt[1] + 8),
                   (char *)g_430n1_zoom_out_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Direct button
    const char *g_430n1_direct_btn_label;
    g_430n1_direct_btn_label = "Direct";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_direct_button_lbrt[0] = l + 460;
    g_430n1_direct_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_direct_button_lbrt[2] =
        g_430n1_direct_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_direct_button_lbrt[1] =
        g_430n1_direct_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_direct_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 5;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_direct_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_direct_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_direct_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_direct_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_direct_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_direct_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_direct_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_direct_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Direct button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_direct_button_lbrt[0] = g_430n1_direct_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_direct_button_lbrt[0]),
                   static_cast<int>(g_430n1_direct_button_lbrt[1] + 8),
                   (char *)g_430n1_direct_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Fine Dn button
    line_number = line_number + 4;
    const char *g_430n1_fine_down_btn_label;
    g_430n1_fine_down_btn_label = "Fine Dn";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_fine_down_button_lbrt[0] = l;
    g_430n1_fine_down_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_fine_down_button_lbrt[2] =
        g_430n1_fine_down_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_fine_down_button_lbrt[1] =
        g_430n1_fine_down_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_fine_down_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 6;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_fine_down_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_fine_down_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_fine_down_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_fine_down_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_fine_down_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_fine_down_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_fine_down_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_fine_down_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Fine Dn button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_fine_down_button_lbrt[0] = g_430n1_fine_down_button_lbrt[0] + 5;
    XPLMDrawString(
        col_black, static_cast<int>(g_430n1_fine_down_button_lbrt[0]),
        static_cast<int>(g_430n1_fine_down_button_lbrt[1] + 8),
        (char *)g_430n1_fine_down_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Fine Up button
    const char *g_430n1_fine_up_btn_label;
    g_430n1_fine_up_btn_label = "Fine Up";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_fine_up_button_lbrt[0] = l + 75;
    g_430n1_fine_up_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_fine_up_button_lbrt[2] =
        g_430n1_fine_up_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_fine_up_button_lbrt[1] =
        g_430n1_fine_up_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_fine_up_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 7;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_fine_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_fine_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_fine_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_fine_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_fine_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_fine_up_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_fine_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_fine_up_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Fine Up button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_fine_up_button_lbrt[0] = g_430n1_fine_up_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_fine_up_button_lbrt[0]),
                   static_cast<int>(g_430n1_fine_up_button_lbrt[1] + 8),
                   (char *)g_430n1_fine_up_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Com Nav Toggle button
    const char *g_430n1_nav_com_tog_btn_label;
    g_430n1_nav_com_tog_btn_label = "Com/Nav";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_nav_com_tog_button_lbrt[0] = l + 150;
    g_430n1_nav_com_tog_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_nav_com_tog_button_lbrt[2] =
        g_430n1_nav_com_tog_button_lbrt[0] + small_button_width +
        2; // *just* wide enough to fit the button text
    g_430n1_nav_com_tog_button_lbrt[1] =
        g_430n1_nav_com_tog_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_nav_com_tog_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 8;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_nav_com_tog_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_nav_com_tog_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_nav_com_tog_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_nav_com_tog_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_nav_com_tog_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_nav_com_tog_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_nav_com_tog_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_nav_com_tog_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Fine Dn button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_nav_com_tog_button_lbrt[0] = g_430n1_nav_com_tog_button_lbrt[0];
    XPLMDrawString(
        col_black, static_cast<int>(g_430n1_nav_com_tog_button_lbrt[0]),
        static_cast<int>(g_430n1_nav_com_tog_button_lbrt[1] + 8),
        (char *)g_430n1_nav_com_tog_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Menu button
    const char *g_430n1_menu_btn_label;
    g_430n1_menu_btn_label = "Menu";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_menu_button_lbrt[0] = l + 290;
    g_430n1_menu_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_menu_button_lbrt[2] =
        g_430n1_menu_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_menu_button_lbrt[1] =
        g_430n1_menu_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_menu_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 9;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_menu_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_menu_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_menu_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_menu_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_menu_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_menu_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_menu_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_menu_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Menu button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_menu_button_lbrt[0] = g_430n1_menu_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_menu_button_lbrt[0]),
                   static_cast<int>(g_430n1_menu_button_lbrt[1] + 8),
                   (char *)g_430n1_menu_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Clr button
    const char *g_430n1_clr_btn_label;
    g_430n1_clr_btn_label = "Clr";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_clr_button_lbrt[0] = l + 375;
    g_430n1_clr_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_clr_button_lbrt[2] =
        g_430n1_clr_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_clr_button_lbrt[1] =
        g_430n1_clr_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_clr_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 10;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_clr_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_clr_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_clr_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_clr_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_clr_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_clr_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_clr_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_clr_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Clr button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_clr_button_lbrt[0] = g_430n1_clr_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_clr_button_lbrt[0]),
                   static_cast<int>(g_430n1_clr_button_lbrt[1] + 8),
                   (char *)g_430n1_clr_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Ent button
    const char *g_430n1_ent_btn_label;
    g_430n1_ent_btn_label = "Ent";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_ent_button_lbrt[0] = l + 460;
    g_430n1_ent_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_ent_button_lbrt[2] =
        g_430n1_ent_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_ent_button_lbrt[1] =
        g_430n1_ent_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_ent_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 11;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_ent_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_ent_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_ent_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_ent_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_ent_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_ent_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_ent_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_ent_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Ent button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_ent_button_lbrt[0] = g_430n1_ent_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_ent_button_lbrt[0]),
                   static_cast<int>(g_430n1_ent_button_lbrt[1] + 8),
                   (char *)g_430n1_ent_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Coarse Dn button
    line_number = line_number + 4;
    const char *g_430n1_coarse_down_btn_label;
    g_430n1_coarse_down_btn_label = "Crs Dn";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_coarse_down_button_lbrt[0] = l;
    g_430n1_coarse_down_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_coarse_down_button_lbrt[2] =
        g_430n1_coarse_down_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_coarse_down_button_lbrt[1] =
        g_430n1_coarse_down_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_coarse_down_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 12;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_coarse_down_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_coarse_down_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_coarse_down_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_coarse_down_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_coarse_down_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_coarse_down_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_coarse_down_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_coarse_down_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Fine Dn button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_coarse_down_button_lbrt[0] = g_430n1_coarse_down_button_lbrt[0] + 5;
    XPLMDrawString(
        col_black, static_cast<int>(g_430n1_coarse_down_button_lbrt[0]),
        static_cast<int>(g_430n1_coarse_down_button_lbrt[1] + 8),
        (char *)g_430n1_coarse_down_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Coarse Up button
    const char *g_430n1_coarse_up_btn_label;
    g_430n1_coarse_up_btn_label = "Crs Up";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_coarse_up_button_lbrt[0] = l + 75;
    g_430n1_coarse_up_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_coarse_up_button_lbrt[2] =
        g_430n1_coarse_up_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_coarse_up_button_lbrt[1] =
        g_430n1_coarse_up_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_coarse_up_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 13;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_coarse_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_coarse_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_coarse_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_coarse_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_coarse_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_coarse_up_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_coarse_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_coarse_up_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Coarse Up button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_coarse_up_button_lbrt[0] = g_430n1_coarse_up_button_lbrt[0] + 5;
    XPLMDrawString(
        col_black, static_cast<int>(g_430n1_coarse_up_button_lbrt[0]),
        static_cast<int>(g_430n1_coarse_up_button_lbrt[1] + 8),
        (char *)g_430n1_coarse_up_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Cursor button
    const char *g_430n1_cursor_btn_label;
    g_430n1_cursor_btn_label = "Cursor";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_cursor_button_lbrt[0] = l + 290;
    g_430n1_cursor_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_cursor_button_lbrt[2] =
        g_430n1_cursor_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_cursor_button_lbrt[1] =
        g_430n1_cursor_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_cursor_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 14;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_cursor_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_cursor_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_cursor_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_cursor_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_cursor_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_cursor_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_cursor_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_cursor_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Page Down button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_cursor_button_lbrt[0] = g_430n1_cursor_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_cursor_button_lbrt[0]),
                   static_cast<int>(g_430n1_cursor_button_lbrt[1] + 8),
                   (char *)g_430n1_cursor_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Page Down button
    const char *g_430n1_page_dn_btn_label;
    g_430n1_page_dn_btn_label = "Page Dn";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_page_dn_button_lbrt[0] = l + 375;
    g_430n1_page_dn_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_page_dn_button_lbrt[2] =
        g_430n1_page_dn_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_page_dn_button_lbrt[1] =
        g_430n1_page_dn_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_page_dn_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 15;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_page_dn_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_page_dn_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_page_dn_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_page_dn_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_page_dn_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_page_dn_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_page_dn_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_page_dn_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Page Down button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_page_dn_button_lbrt[0] = g_430n1_page_dn_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n1_page_dn_button_lbrt[0]),
                   static_cast<int>(g_430n1_page_dn_button_lbrt[1] + 8),
                   (char *)g_430n1_page_dn_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Page Up button
    const char *g_430n1_page_up_btn_label;
    g_430n1_page_up_btn_label = "Page Up";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_page_up_button_lbrt[0] = l + 460;
    g_430n1_page_up_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_page_up_button_lbrt[2] =
        g_430n1_page_up_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_page_up_button_lbrt[1] =
        g_430n1_page_up_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_page_up_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 16;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_page_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_page_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_page_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_page_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_page_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_page_up_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_page_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_page_up_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Page Up button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_page_up_button_lbrt[0] = g_430n1_page_up_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n1_page_up_button_lbrt[0]),
                   static_cast<int>(g_430n1_page_up_button_lbrt[1] + 8),
                   (char *)g_430n1_page_up_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the CDI button
    line_number = line_number + 4;
    const char *g_430n1_cdi_btn_label;
    g_430n1_cdi_btn_label = "CDI";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_cdi_button_lbrt[0] = l;
    g_430n1_cdi_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_cdi_button_lbrt[2] =
        g_430n1_cdi_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n1_cdi_button_lbrt[1] =
        g_430n1_cdi_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_cdi_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 17;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_cdi_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_cdi_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_cdi_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_cdi_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_cdi_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_cdi_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_cdi_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_cdi_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the CDI button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_cdi_button_lbrt[0] = g_430n1_cdi_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_cdi_button_lbrt[0]),
                   static_cast<int>(g_430n1_cdi_button_lbrt[1] + 8),
                   (char *)g_430n1_cdi_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the OBS button
    const char *g_430n1_obs_btn_label;
    g_430n1_obs_btn_label = "OBS";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_obs_button_lbrt[0] = l + 60;
    g_430n1_obs_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_obs_button_lbrt[2] =
        g_430n1_obs_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n1_obs_button_lbrt[1] =
        g_430n1_obs_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_obs_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 18;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_obs_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_obs_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_obs_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_obs_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_obs_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_obs_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_obs_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_obs_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the OBS button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_obs_button_lbrt[0] = g_430n1_obs_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_obs_button_lbrt[0]),
                   static_cast<int>(g_430n1_obs_button_lbrt[1] + 8),
                   (char *)g_430n1_obs_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the MSG button
    const char *g_430n1_msg_btn_label;
    g_430n1_msg_btn_label = "MSG";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_msg_button_lbrt[0] = l + 120;
    g_430n1_msg_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_msg_button_lbrt[2] =
        g_430n1_msg_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n1_msg_button_lbrt[1] =
        g_430n1_msg_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_msg_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 19;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_msg_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_msg_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_msg_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_msg_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_msg_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_msg_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_msg_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_msg_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the MSG button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_msg_button_lbrt[0] = g_430n1_msg_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_msg_button_lbrt[0]),
                   static_cast<int>(g_430n1_msg_button_lbrt[1] + 8),
                   (char *)g_430n1_msg_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the FPL button
    const char *g_430n1_fpl_btn_label;
    g_430n1_fpl_btn_label = "FPL";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_fpl_button_lbrt[0] = l + 180;
    g_430n1_fpl_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_fpl_button_lbrt[2] =
        g_430n1_fpl_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n1_fpl_button_lbrt[1] =
        g_430n1_fpl_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_fpl_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 20;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_fpl_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_fpl_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_fpl_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_fpl_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_fpl_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_fpl_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_fpl_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_fpl_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the FPL button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_fpl_button_lbrt[0] = g_430n1_fpl_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n1_fpl_button_lbrt[0]),
                   static_cast<int>(g_430n1_fpl_button_lbrt[1] + 8),
                   (char *)g_430n1_fpl_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the VNAV button
    const char *g_430n1_vnav_btn_label;
    g_430n1_vnav_btn_label = "VNAV";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_vnav_button_lbrt[0] = l + 240;
    g_430n1_vnav_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_vnav_button_lbrt[2] =
        g_430n1_vnav_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n1_vnav_button_lbrt[1] =
        g_430n1_vnav_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_vnav_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 21;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_vnav_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_vnav_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_vnav_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_vnav_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_vnav_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_vnav_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_vnav_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_vnav_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the VNAV button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_vnav_button_lbrt[0] = g_430n1_vnav_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n1_vnav_button_lbrt[0]),
                   static_cast<int>(g_430n1_vnav_button_lbrt[1] + 8),
                   (char *)g_430n1_vnav_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the PROC button
    const char *g_430n1_proc_btn_label;
    g_430n1_proc_btn_label = "PROC";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_proc_button_lbrt[0] = l + 300;
    g_430n1_proc_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_proc_button_lbrt[2] =
        g_430n1_proc_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n1_proc_button_lbrt[1] =
        g_430n1_proc_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_proc_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 22;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_proc_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_proc_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_proc_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_proc_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_proc_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_proc_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_proc_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_proc_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the PROC button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_proc_button_lbrt[0] = g_430n1_proc_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n1_proc_button_lbrt[0]),
                   static_cast<int>(g_430n1_proc_button_lbrt[1] + 8),
                   (char *)g_430n1_proc_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Chapter Down button
    const char *g_430n1_chapter_dn_btn_label;
    g_430n1_chapter_dn_btn_label = "Chap Dn";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_chapter_dn_button_lbrt[0] = l + 375;
    g_430n1_chapter_dn_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_chapter_dn_button_lbrt[2] =
        g_430n1_chapter_dn_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_chapter_dn_button_lbrt[1] =
        g_430n1_chapter_dn_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_chapter_dn_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 23;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_chapter_dn_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_chapter_dn_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_chapter_dn_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_chapter_dn_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_chapter_dn_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_chapter_dn_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_chapter_dn_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_chapter_dn_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Chapter Down button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_chapter_dn_button_lbrt[0] = g_430n1_chapter_dn_button_lbrt[0];
    XPLMDrawString(
        col_black, static_cast<int>(g_430n1_chapter_dn_button_lbrt[0]),
        static_cast<int>(g_430n1_chapter_dn_button_lbrt[1] + 8),
        (char *)g_430n1_chapter_dn_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Chapter Up button
    const char *g_430n1_chapter_up_btn_label;
    g_430n1_chapter_up_btn_label = "Chap Up";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n1_chapter_up_button_lbrt[0] = l + 460;
    g_430n1_chapter_up_button_lbrt[3] = t - (line_number * char_height);
    g_430n1_chapter_up_button_lbrt[2] =
        g_430n1_chapter_up_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n1_chapter_up_button_lbrt[1] =
        g_430n1_chapter_up_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n1_chapter_up_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 24;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n1_chapter_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_chapter_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_chapter_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_chapter_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n1_chapter_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n1_chapter_up_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n1_chapter_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n1_chapter_up_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Chapter Up button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n1_chapter_up_button_lbrt[0] = g_430n1_chapter_up_button_lbrt[0];
    XPLMDrawString(
        col_black, static_cast<int>(g_430n1_chapter_up_button_lbrt[0]),
        static_cast<int>(g_430n1_chapter_up_button_lbrt[1] + 8),
        (char *)g_430n1_chapter_up_btn_label, nullptr, xplmFont_Proportional);
  }

  // g430n2 Page
  if (page_number == 15) {

    // Draw the Com FF button
    line_number = line_number + 4;
    const char *g_430n2_com_ff_btn_label;
    g_430n2_com_ff_btn_label = "Com FF";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_com_ff_button_lbrt[0] = l;
    g_430n2_com_ff_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_com_ff_button_lbrt[2] =
        g_430n2_com_ff_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_com_ff_button_lbrt[1] =
        g_430n2_com_ff_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_com_ff_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 1;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_com_ff_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_com_ff_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_com_ff_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_com_ff_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_com_ff_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_com_ff_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_com_ff_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_com_ff_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Com FF button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_com_ff_button_lbrt[0] = g_430n2_com_ff_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_com_ff_button_lbrt[0]),
                   static_cast<int>(g_430n2_com_ff_button_lbrt[1] + 8),
                   (char *)g_430n2_com_ff_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Nav FF button
    const char *g_430n2_nav_ff_btn_label;
    g_430n2_nav_ff_btn_label = "Nav FF";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_nav_ff_button_lbrt[0] = l + 75;
    g_430n2_nav_ff_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_nav_ff_button_lbrt[2] =
        g_430n2_nav_ff_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_nav_ff_button_lbrt[1] =
        g_430n2_nav_ff_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_nav_ff_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 2;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_nav_ff_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_nav_ff_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_nav_ff_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_nav_ff_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_nav_ff_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_nav_ff_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_nav_ff_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_nav_ff_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Nav FF button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_nav_ff_button_lbrt[0] = g_430n2_nav_ff_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_nav_ff_button_lbrt[0]),
                   static_cast<int>(g_430n2_nav_ff_button_lbrt[1] + 8),
                   (char *)g_430n2_nav_ff_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Zoom In button
    const char *g_430n2_zoom_in_btn_label;
    g_430n2_zoom_in_btn_label = "Zoom In";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_zoom_in_button_lbrt[0] = l + 290;
    g_430n2_zoom_in_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_zoom_in_button_lbrt[2] =
        g_430n2_zoom_in_button_lbrt[0] + small_button_width +
        5; // *just* wide enough to fit the button text
    g_430n2_zoom_in_button_lbrt[1] =
        g_430n2_zoom_in_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_zoom_in_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 3;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_zoom_in_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_zoom_in_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_zoom_in_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_zoom_in_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_zoom_in_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_zoom_in_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_zoom_in_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_zoom_in_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Zoom In button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_zoom_in_button_lbrt[0] = g_430n2_zoom_in_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_zoom_in_button_lbrt[0]),
                   static_cast<int>(g_430n2_zoom_in_button_lbrt[1] + 8),
                   (char *)g_430n2_zoom_in_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Zoom Out button
    const char *g_430n2_zoom_out_btn_label;
    g_430n2_zoom_out_btn_label = "Zoom Out";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_zoom_out_button_lbrt[0] = l + 375;
    g_430n2_zoom_out_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_zoom_out_button_lbrt[2] =
        g_430n2_zoom_out_button_lbrt[0] + small_button_width +
        9; // *just* wide enough to fit the button text
    g_430n2_zoom_out_button_lbrt[1] =
        g_430n2_zoom_out_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_zoom_out_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 4;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_zoom_out_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_zoom_out_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_zoom_out_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_zoom_out_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_zoom_out_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_zoom_out_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_zoom_out_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_zoom_out_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Zoom Out button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_zoom_out_button_lbrt[0] = g_430n2_zoom_out_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n2_zoom_out_button_lbrt[0]),
                   static_cast<int>(g_430n2_zoom_out_button_lbrt[1] + 8),
                   (char *)g_430n2_zoom_out_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Direct button
    const char *g_430n2_direct_btn_label;
    g_430n2_direct_btn_label = "Direct";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_direct_button_lbrt[0] = l + 460;
    g_430n2_direct_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_direct_button_lbrt[2] =
        g_430n2_direct_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_direct_button_lbrt[1] =
        g_430n2_direct_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_direct_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 5;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_direct_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_direct_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_direct_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_direct_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_direct_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_direct_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_direct_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_direct_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Direct button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_direct_button_lbrt[0] = g_430n2_direct_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_direct_button_lbrt[0]),
                   static_cast<int>(g_430n2_direct_button_lbrt[1] + 8),
                   (char *)g_430n2_direct_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Fine Dn button
    line_number = line_number + 4;
    const char *g_430n2_fine_down_btn_label;
    g_430n2_fine_down_btn_label = "Fine Dn";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_fine_down_button_lbrt[0] = l;
    g_430n2_fine_down_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_fine_down_button_lbrt[2] =
        g_430n2_fine_down_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_fine_down_button_lbrt[1] =
        g_430n2_fine_down_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_fine_down_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 6;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_fine_down_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_fine_down_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_fine_down_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_fine_down_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_fine_down_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_fine_down_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_fine_down_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_fine_down_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Fine Dn button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_fine_down_button_lbrt[0] = g_430n2_fine_down_button_lbrt[0] + 5;
    XPLMDrawString(
        col_black, static_cast<int>(g_430n2_fine_down_button_lbrt[0]),
        static_cast<int>(g_430n2_fine_down_button_lbrt[1] + 8),
        (char *)g_430n2_fine_down_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Fine Up button
    const char *g_430n2_fine_up_btn_label;
    g_430n2_fine_up_btn_label = "Fine Up";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_fine_up_button_lbrt[0] = l + 75;
    g_430n2_fine_up_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_fine_up_button_lbrt[2] =
        g_430n2_fine_up_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_fine_up_button_lbrt[1] =
        g_430n2_fine_up_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_fine_up_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 7;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_fine_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_fine_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_fine_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_fine_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_fine_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_fine_up_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_fine_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_fine_up_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Fine Up button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_fine_up_button_lbrt[0] = g_430n2_fine_up_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_fine_up_button_lbrt[0]),
                   static_cast<int>(g_430n2_fine_up_button_lbrt[1] + 8),
                   (char *)g_430n2_fine_up_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Com Nav Toggle button
    const char *g_430n2_nav_com_tog_btn_label;
    g_430n2_nav_com_tog_btn_label = "Com/Nav";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_nav_com_tog_button_lbrt[0] = l + 150;
    g_430n2_nav_com_tog_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_nav_com_tog_button_lbrt[2] =
        g_430n2_nav_com_tog_button_lbrt[0] + small_button_width +
        2; // *just* wide enough to fit the button text
    g_430n2_nav_com_tog_button_lbrt[1] =
        g_430n2_nav_com_tog_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_nav_com_tog_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 8;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_nav_com_tog_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_nav_com_tog_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_nav_com_tog_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_nav_com_tog_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_nav_com_tog_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_nav_com_tog_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_nav_com_tog_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_nav_com_tog_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Fine Dn button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_nav_com_tog_button_lbrt[0] = g_430n2_nav_com_tog_button_lbrt[0];
    XPLMDrawString(
        col_black, static_cast<int>(g_430n2_nav_com_tog_button_lbrt[0]),
        static_cast<int>(g_430n2_nav_com_tog_button_lbrt[1] + 8),
        (char *)g_430n2_nav_com_tog_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Menu button
    const char *g_430n2_menu_btn_label;
    g_430n2_menu_btn_label = "Menu";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_menu_button_lbrt[0] = l + 290;
    g_430n2_menu_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_menu_button_lbrt[2] =
        g_430n2_menu_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_menu_button_lbrt[1] =
        g_430n2_menu_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_menu_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 9;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_menu_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_menu_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_menu_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_menu_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_menu_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_menu_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_menu_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_menu_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Menu button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_menu_button_lbrt[0] = g_430n2_menu_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_menu_button_lbrt[0]),
                   static_cast<int>(g_430n2_menu_button_lbrt[1] + 8),
                   (char *)g_430n2_menu_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Clr button
    const char *g_430n2_clr_btn_label;
    g_430n2_clr_btn_label = "Clr";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_clr_button_lbrt[0] = l + 375;
    g_430n2_clr_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_clr_button_lbrt[2] =
        g_430n2_clr_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_clr_button_lbrt[1] =
        g_430n2_clr_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_clr_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 10;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_clr_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_clr_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_clr_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_clr_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_clr_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_clr_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_clr_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_clr_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Clr button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_clr_button_lbrt[0] = g_430n2_clr_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_clr_button_lbrt[0]),
                   static_cast<int>(g_430n2_clr_button_lbrt[1] + 8),
                   (char *)g_430n2_clr_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Ent button
    const char *g_430n2_ent_btn_label;
    g_430n2_ent_btn_label = "Ent";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_ent_button_lbrt[0] = l + 460;
    g_430n2_ent_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_ent_button_lbrt[2] =
        g_430n2_ent_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_ent_button_lbrt[1] =
        g_430n2_ent_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_ent_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 11;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_ent_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_ent_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_ent_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_ent_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_ent_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_ent_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_ent_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_ent_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Ent button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_ent_button_lbrt[0] = g_430n2_ent_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_ent_button_lbrt[0]),
                   static_cast<int>(g_430n2_ent_button_lbrt[1] + 8),
                   (char *)g_430n2_ent_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Coarse Dn button
    line_number = line_number + 4;
    const char *g_430n2_coarse_down_btn_label;
    g_430n2_coarse_down_btn_label = "Crs Dn";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_coarse_down_button_lbrt[0] = l;
    g_430n2_coarse_down_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_coarse_down_button_lbrt[2] =
        g_430n2_coarse_down_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_coarse_down_button_lbrt[1] =
        g_430n2_coarse_down_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_coarse_down_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 12;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_coarse_down_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_coarse_down_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_coarse_down_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_coarse_down_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_coarse_down_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_coarse_down_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_coarse_down_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_coarse_down_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Fine Dn button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_coarse_down_button_lbrt[0] = g_430n2_coarse_down_button_lbrt[0] + 5;
    XPLMDrawString(
        col_black, static_cast<int>(g_430n2_coarse_down_button_lbrt[0]),
        static_cast<int>(g_430n2_coarse_down_button_lbrt[1] + 8),
        (char *)g_430n2_coarse_down_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Coarse Up button
    const char *g_430n2_coarse_up_btn_label;
    g_430n2_coarse_up_btn_label = "Crs Up";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_coarse_up_button_lbrt[0] = l + 75;
    g_430n2_coarse_up_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_coarse_up_button_lbrt[2] =
        g_430n2_coarse_up_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_coarse_up_button_lbrt[1] =
        g_430n2_coarse_up_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_coarse_up_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 13;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_coarse_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_coarse_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_coarse_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_coarse_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_coarse_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_coarse_up_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_coarse_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_coarse_up_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Coarse Up button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_coarse_up_button_lbrt[0] = g_430n2_coarse_up_button_lbrt[0] + 5;
    XPLMDrawString(
        col_black, static_cast<int>(g_430n2_coarse_up_button_lbrt[0]),
        static_cast<int>(g_430n2_coarse_up_button_lbrt[1] + 8),
        (char *)g_430n2_coarse_up_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Cursor button
    const char *g_430n2_cursor_btn_label;
    g_430n2_cursor_btn_label = "Cursor";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_cursor_button_lbrt[0] = l + 290;
    g_430n2_cursor_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_cursor_button_lbrt[2] =
        g_430n2_cursor_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_cursor_button_lbrt[1] =
        g_430n2_cursor_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_cursor_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 14;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_cursor_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_cursor_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_cursor_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_cursor_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_cursor_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_cursor_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_cursor_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_cursor_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Page Down button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_cursor_button_lbrt[0] = g_430n2_cursor_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_cursor_button_lbrt[0]),
                   static_cast<int>(g_430n2_cursor_button_lbrt[1] + 8),
                   (char *)g_430n2_cursor_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Page Down button
    const char *g_430n2_page_dn_btn_label;
    g_430n2_page_dn_btn_label = "Page Dn";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_page_dn_button_lbrt[0] = l + 375;
    g_430n2_page_dn_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_page_dn_button_lbrt[2] =
        g_430n2_page_dn_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_page_dn_button_lbrt[1] =
        g_430n2_page_dn_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_page_dn_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 15;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_page_dn_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_page_dn_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_page_dn_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_page_dn_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_page_dn_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_page_dn_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_page_dn_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_page_dn_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Page Down button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_page_dn_button_lbrt[0] = g_430n2_page_dn_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n2_page_dn_button_lbrt[0]),
                   static_cast<int>(g_430n2_page_dn_button_lbrt[1] + 8),
                   (char *)g_430n2_page_dn_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Page Up button
    const char *g_430n2_page_up_btn_label;
    g_430n2_page_up_btn_label = "Page Up";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_page_up_button_lbrt[0] = l + 460;
    g_430n2_page_up_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_page_up_button_lbrt[2] =
        g_430n2_page_up_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_page_up_button_lbrt[1] =
        g_430n2_page_up_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_page_up_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 16;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_page_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_page_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_page_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_page_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_page_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_page_up_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_page_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_page_up_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Page Up button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_page_up_button_lbrt[0] = g_430n2_page_up_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n2_page_up_button_lbrt[0]),
                   static_cast<int>(g_430n2_page_up_button_lbrt[1] + 8),
                   (char *)g_430n2_page_up_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the CDI button
    line_number = line_number + 4;
    const char *g_430n2_cdi_btn_label;
    g_430n2_cdi_btn_label = "CDI";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_cdi_button_lbrt[0] = l;
    g_430n2_cdi_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_cdi_button_lbrt[2] =
        g_430n2_cdi_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n2_cdi_button_lbrt[1] =
        g_430n2_cdi_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_cdi_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 17;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_cdi_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_cdi_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_cdi_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_cdi_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_cdi_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_cdi_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_cdi_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_cdi_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the CDI button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_cdi_button_lbrt[0] = g_430n2_cdi_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_cdi_button_lbrt[0]),
                   static_cast<int>(g_430n2_cdi_button_lbrt[1] + 8),
                   (char *)g_430n2_cdi_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the OBS button
    const char *g_430n2_obs_btn_label;
    g_430n2_obs_btn_label = "OBS";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_obs_button_lbrt[0] = l + 60;
    g_430n2_obs_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_obs_button_lbrt[2] =
        g_430n2_obs_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n2_obs_button_lbrt[1] =
        g_430n2_obs_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_obs_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 18;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_obs_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_obs_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_obs_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_obs_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_obs_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_obs_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_obs_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_obs_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the OBS button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_obs_button_lbrt[0] = g_430n2_obs_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_obs_button_lbrt[0]),
                   static_cast<int>(g_430n2_obs_button_lbrt[1] + 8),
                   (char *)g_430n2_obs_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the MSG button
    const char *g_430n2_msg_btn_label;
    g_430n2_msg_btn_label = "MSG";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_msg_button_lbrt[0] = l + 120;
    g_430n2_msg_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_msg_button_lbrt[2] =
        g_430n2_msg_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n2_msg_button_lbrt[1] =
        g_430n2_msg_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_msg_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 19;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_msg_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_msg_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_msg_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_msg_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_msg_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_msg_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_msg_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_msg_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the MSG button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_msg_button_lbrt[0] = g_430n2_msg_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_msg_button_lbrt[0]),
                   static_cast<int>(g_430n2_msg_button_lbrt[1] + 8),
                   (char *)g_430n2_msg_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the FPL button
    const char *g_430n2_fpl_btn_label;
    g_430n2_fpl_btn_label = "FPL";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_fpl_button_lbrt[0] = l + 180;
    g_430n2_fpl_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_fpl_button_lbrt[2] =
        g_430n2_fpl_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n2_fpl_button_lbrt[1] =
        g_430n2_fpl_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_fpl_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 20;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_fpl_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_fpl_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_fpl_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_fpl_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_fpl_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_fpl_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_fpl_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_fpl_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the FPL button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_fpl_button_lbrt[0] = g_430n2_fpl_button_lbrt[0] + 5;
    XPLMDrawString(col_black, static_cast<int>(g_430n2_fpl_button_lbrt[0]),
                   static_cast<int>(g_430n2_fpl_button_lbrt[1] + 8),
                   (char *)g_430n2_fpl_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the VNAV button
    const char *g_430n2_vnav_btn_label;
    g_430n2_vnav_btn_label = "VNAV";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_vnav_button_lbrt[0] = l + 240;
    g_430n2_vnav_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_vnav_button_lbrt[2] =
        g_430n2_vnav_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n2_vnav_button_lbrt[1] =
        g_430n2_vnav_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_vnav_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 21;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_vnav_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_vnav_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_vnav_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_vnav_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_vnav_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_vnav_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_vnav_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_vnav_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the VNAV button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_vnav_button_lbrt[0] = g_430n2_vnav_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n2_vnav_button_lbrt[0]),
                   static_cast<int>(g_430n2_vnav_button_lbrt[1] + 8),
                   (char *)g_430n2_vnav_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the PROC button
    const char *g_430n2_proc_btn_label;
    g_430n2_proc_btn_label = "PROC";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_proc_button_lbrt[0] = l + 300;
    g_430n2_proc_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_proc_button_lbrt[2] =
        g_430n2_proc_button_lbrt[0] + small_button_width -
        15; // *just* wide enough to fit the button text
    g_430n2_proc_button_lbrt[1] =
        g_430n2_proc_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_proc_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 22;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_proc_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_proc_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_proc_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_proc_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_proc_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_proc_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_proc_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_proc_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the PROC button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_proc_button_lbrt[0] = g_430n2_proc_button_lbrt[0];
    XPLMDrawString(col_black, static_cast<int>(g_430n2_proc_button_lbrt[0]),
                   static_cast<int>(g_430n2_proc_button_lbrt[1] + 8),
                   (char *)g_430n2_proc_btn_label, nullptr,
                   xplmFont_Proportional);

    // Draw the Chapter Down button
    const char *g_430n2_chapter_dn_btn_label;
    g_430n2_chapter_dn_btn_label = "Chap Dn";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_chapter_dn_button_lbrt[0] = l + 375;
    g_430n2_chapter_dn_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_chapter_dn_button_lbrt[2] =
        g_430n2_chapter_dn_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_chapter_dn_button_lbrt[1] =
        g_430n2_chapter_dn_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_chapter_dn_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 23;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_chapter_dn_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_chapter_dn_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_chapter_dn_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_chapter_dn_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_chapter_dn_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_chapter_dn_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_chapter_dn_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_chapter_dn_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Chapter Down button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_chapter_dn_button_lbrt[0] = g_430n2_chapter_dn_button_lbrt[0];
    XPLMDrawString(
        col_black, static_cast<int>(g_430n2_chapter_dn_button_lbrt[0]),
        static_cast<int>(g_430n2_chapter_dn_button_lbrt[1] + 8),
        (char *)g_430n2_chapter_dn_btn_label, nullptr, xplmFont_Proportional);

    // Draw the Chapter Up button
    const char *g_430n2_chapter_up_btn_label;
    g_430n2_chapter_up_btn_label = "Chap Up";

    // 0 left, 1 bottom, 2 right, 3 top
    // Position the button in the upper left of the window (sized to fit the
    // button text)
    g_430n2_chapter_up_button_lbrt[0] = l + 460;
    g_430n2_chapter_up_button_lbrt[3] = t - (line_number * char_height);
    g_430n2_chapter_up_button_lbrt[2] =
        g_430n2_chapter_up_button_lbrt[0] +
        small_button_width; // *just* wide enough to fit the button text
    g_430n2_chapter_up_button_lbrt[1] =
        g_430n2_chapter_up_button_lbrt[3] -
        (2.00f * char_height); // a bit taller than the button text

    // Draw the box around our rudimentary button
    if (g_430n2_chapter_up_mouse_down) {
      glColor4fv(light_green);
      ButtonNumberValue = 24;
    } else {
      glColor4fv(green);
    }
    glBegin(GL_POLYGON);
    {
      glVertex2i(static_cast<GLint>(g_430n2_chapter_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_chapter_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_chapter_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_chapter_up_button_lbrt[3]));
      glVertex2i(static_cast<GLint>(g_430n2_chapter_up_button_lbrt[2]),
                 static_cast<GLint>(g_430n2_chapter_up_button_lbrt[1]));
      glVertex2i(static_cast<GLint>(g_430n2_chapter_up_button_lbrt[0]),
                 static_cast<GLint>(g_430n2_chapter_up_button_lbrt[1]));
    }
    glEnd();

    // Draw the text on the Chapter Up button.
    // 0 left, 1 bottom, 2 right, 3 top
    g_430n2_chapter_up_button_lbrt[0] = g_430n2_chapter_up_button_lbrt[0];
    XPLMDrawString(
        col_black, static_cast<int>(g_430n2_chapter_up_button_lbrt[0]),
        static_cast<int>(g_430n2_chapter_up_button_lbrt[1] + 8),
        (char *)g_430n2_chapter_up_btn_label, nullptr, xplmFont_Proportional);
  }

  // g10001 Page
  if (page_number == 12) {
  }

  // g1000n2 Page
  if (page_number == 13) {
  }

  // g1000n3 Page
  if (page_number == 14) {
  }
}

int xb2cvr_handle_mouse(XPLMWindowID xb2cvr_in_window_id, int xb2cvr_x,
                        int xb2cvr_y, XPLMMouseStatus xb2cvr_mouse_status,
                        void * /*in_refcon*/) {

  if (xb2cvr_mouse_status == xplm_MouseDown) {
    if (!XPLMIsWindowInFront(xb2cvr_in_window_id)) {
      XPLMBringWindowToFront(xb2cvr_in_window_id);
    } else {

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page1_button_lbrt)) {
        mouse_down_page1 = 1;
        page_number = 1;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page2_button_lbrt)) {
        mouse_down_page2 = 1;
        page_number = 2;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page3_button_lbrt)) {
        mouse_down_page3 = 1;
        page_number = 3;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page4_button_lbrt)) {
        mouse_down_page4 = 1;
        page_number = 4;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_hide_button_lbrt)) {
        XPLMDebugString("Xbtn2cmd: Hide button pushed\n");
        if (is_popped_out) {
            was_popped_out = is_popped_out;
        }
        mouse_down_hide = 1;
        Xbtn2hide_window();
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page5_button_lbrt)) {
        mouse_down_page5 = 1;
        page_number = 5;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page6_button_lbrt)) {
        mouse_down_page6 = 1;
        page_number = 6;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page7_button_lbrt)) {
        mouse_down_page7 = 1;
        page_number = 7;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page8_button_lbrt)) {
        mouse_down_page8 = 1;
        page_number = 8;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page9_button_lbrt)) {
        mouse_down_page9 = 1;
        page_number = 9;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page10_button_lbrt)) {
        mouse_down_page10 = 1;
        page_number = 10;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page11_button_lbrt)) {
        mouse_down_page11 = 1;
        page_number = 11;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_page12_button_lbrt)) {
        mouse_down_page12 = 1;
        page_number = 12;
      }



      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_radios_button_lbrt)) {
        mouse_down_radios = 1;
        page_number = 13;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_g430n1_button_lbrt)) {
        mouse_down_g430n1 = 1;
        page_number = 14;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_g430n2_button_lbrt)) {
        mouse_down_g430n2 = 1;
        page_number = 15;
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_ctrl_c_button_lbrt)) {
        XPLMDebugString("Xbtn2cmd: Ctrl C button pushed\n");
        mouse_down_ctrl_c = 1;
        send_delayed_ctrl_c();
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_edit_button_lbrt)) {
        XPLMDebugString("Xbtn2cmd: Edit button pushed\n");
        mouse_down_edit = 1;
        process_create_edit_window();
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_reload_button_lbrt)) {
        XPLMDebugString("Xbtn2cmd: Reload button pushed\n");
        mouse_down_reload = 1;
        process_read_ini_file();
      }

      if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button1_lbrt)) {
        mouse_down[0] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button1CommandOnceCmd);
            if (Page1_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button1CommandContinueCmd);
              Page1_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button1_label =";
            search_current_page_button_command_once =
                "page1_button1_command_once =";
            search_current_page_button_command_continue =
                "page1_button1_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button1CommandOnceCmd);
            if (Page2_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button1CommandContinueCmd);
              Page2_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button1_label =";
            search_current_page_button_command_once =
                "page2_button1_command_once =";
            search_current_page_button_command_continue =
                "page2_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button1CommandOnceCmd);
            if (Page3_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button1CommandContinueCmd);
              Page3_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button1_label =";
            search_current_page_button_command_once =
                "page3_button1_command_once =";
            search_current_page_button_command_continue =
                "page3_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button1CommandOnceCmd);
            if (Page4_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button1CommandContinueCmd);
              Page4_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button1_label =";
            search_current_page_button_command_once =
                "page4_button1_command_once =";
            search_current_page_button_command_continue =
                "page4_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button1CommandOnceCmd);
            if (Page2_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button1CommandContinueCmd);
              Page5_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button1_label =";
            search_current_page_button_command_once =
                "page5_button1_command_once =";
            search_current_page_button_command_continue =
                "page5_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button1CommandOnceCmd);
            if (Page6_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button1CommandContinueCmd);
              Page6_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button1_label =";
            search_current_page_button_command_once =
                "page6_button1_command_once =";
            search_current_page_button_command_continue =
                "page6_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button1CommandOnceCmd);
            if (Page7_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button1CommandContinueCmd);
              Page7_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button1_label =";
            search_current_page_button_command_once =
                "page7_button1_command_once =";
            search_current_page_button_command_continue =
                "page7_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button1CommandOnceCmd);
            if (Page8_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button1CommandContinueCmd);
              Page8_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button1_label =";
            search_current_page_button_command_once =
                "page8_button1_command_once =";
            search_current_page_button_command_continue =
                "page8_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button1CommandOnceCmd);
            if (Page9_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button1CommandContinueCmd);
              Page9_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button1_label =";
            search_current_page_button_command_once =
                "page9_button1_command_once =";
            search_current_page_button_command_continue =
                "page9_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button1CommandOnceCmd);
            if (Page10_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button1CommandContinueCmd);
              Page10_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button1_label =";
            search_current_page_button_command_once =
                "page10_button1_command_once =";
            search_current_page_button_command_continue =
                "page10_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button1CommandOnceCmd);
            if (Page11_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button1CommandContinueCmd);
              Page11_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button1_label =";
            search_current_page_button_command_once =
                "page11_button1_command_once =";
            search_current_page_button_command_continue =
                "page11_button1_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button1CommandOnceCmd);
            if (Page12_Button1ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button1CommandContinueCmd);
              Page12_Button1ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button1_label =";
            search_current_page_button_command_once =
                "page12_button1_command_once =";
            search_current_page_button_command_continue =
                "page12_button1_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button2_lbrt)) {
        mouse_down[1] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button2CommandOnceCmd);
            if (Page1_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button2CommandContinueCmd);
              Page1_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button2_label =";
            search_current_page_button_command_once =
                "page1_button2_command_once =";
            search_current_page_button_command_continue =
                "page1_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button2CommandOnceCmd);
            if (Page2_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button2CommandContinueCmd);
              Page2_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button2_label =";
            search_current_page_button_command_once =
                "page2_button2_command_once =";
            search_current_page_button_command_continue =
                "page2_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button2CommandOnceCmd);
            if (Page3_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button2CommandContinueCmd);
              Page3_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button2_label =";
            search_current_page_button_command_once =
                "page3_button2_command_once =";
            search_current_page_button_command_continue =
                "page3_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button2CommandOnceCmd);
            if (Page4_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button2CommandContinueCmd);
              Page4_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button2_label =";
            search_current_page_button_command_once =
                "page4_button2_command_once =";
            search_current_page_button_command_continue =
                "page4_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button2CommandOnceCmd);
            if (Page5_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button2CommandContinueCmd);
              Page5_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button2_label =";
            search_current_page_button_command_once =
                "page5_button2_command_once =";
            search_current_page_button_command_continue =
                "page5_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button2CommandOnceCmd);
            if (Page6_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button2CommandContinueCmd);
              Page6_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button2_label =";
            search_current_page_button_command_once =
                "page6_button2_command_once =";
            search_current_page_button_command_continue =
                "page6_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button2CommandOnceCmd);
            if (Page7_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button2CommandContinueCmd);
              Page7_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button2_label =";
            search_current_page_button_command_once =
                "page7_button2_command_once =";
            search_current_page_button_command_continue =
                "page7_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button2CommandOnceCmd);
            if (Page8_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button2CommandContinueCmd);
              Page8_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button2_label =";
            search_current_page_button_command_once =
                "page8_button2_command_once =";
            search_current_page_button_command_continue =
                "page8_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button2CommandOnceCmd);
            if (Page9_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button2CommandContinueCmd);
              Page9_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button2_label =";
            search_current_page_button_command_once =
                "page9_button2_command_once =";
            search_current_page_button_command_continue =
                "page9_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button2CommandOnceCmd);
            if (Page10_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button2CommandContinueCmd);
              Page10_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button2_label =";
            search_current_page_button_command_once =
                "page10_button2_command_once =";
            search_current_page_button_command_continue =
                "page10_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button2CommandOnceCmd);
            if (Page11_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button2CommandContinueCmd);
              Page11_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button2_label =";
            search_current_page_button_command_once =
                "page11_button2_command_once =";
            search_current_page_button_command_continue =
                "page11_button2_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button2CommandOnceCmd);
            if (Page12_Button2ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button2CommandContinueCmd);
              Page12_Button2ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button2_label =";
            search_current_page_button_command_once =
                "page12_button2_command_once =";
            search_current_page_button_command_continue =
                "page12_button2_command_continue =";
            populate_edit_window();
          }
        }

      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button3_lbrt)) {
        mouse_down[2] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button3CommandOnceCmd);
            if (Page1_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button3CommandContinueCmd);
              Page1_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button3_label =";
            search_current_page_button_command_once =
                "page1_button3_command_once =";
            search_current_page_button_command_continue =
                "page1_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button3CommandOnceCmd);
            if (Page2_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button3CommandContinueCmd);
              Page2_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button3_label =";
            search_current_page_button_command_once =
                "page2_button3_command_once =";
            search_current_page_button_command_continue =
                "page2_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button3CommandOnceCmd);
            if (Page3_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button3CommandContinueCmd);
              Page3_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button3_label =";
            search_current_page_button_command_once =
                "page3_button3_command_once =";
            search_current_page_button_command_continue =
                "page3_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button3CommandOnceCmd);
            if (Page4_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button3CommandContinueCmd);
              Page4_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button3_label =";
            search_current_page_button_command_once =
                "page4_button3_command_once =";
            search_current_page_button_command_continue =
                "page4_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button3CommandOnceCmd);
            if (Page5_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button3CommandContinueCmd);
              Page5_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button3_label =";
            search_current_page_button_command_once =
                "page5_button3_command_once =";
            search_current_page_button_command_continue =
                "page5_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button3CommandOnceCmd);
            if (Page6_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button3CommandContinueCmd);
              Page6_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button3_label =";
            search_current_page_button_command_once =
                "page6_button3_command_once =";
            search_current_page_button_command_continue =
                "page6_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button3CommandOnceCmd);
            if (Page7_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button3CommandContinueCmd);
              Page7_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button3_label =";
            search_current_page_button_command_once =
                "page7_button3_command_once =";
            search_current_page_button_command_continue =
                "page7_button3_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button3CommandOnceCmd);
            if (Page8_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button3CommandContinueCmd);
              Page8_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button3_label =";
            search_current_page_button_command_once =
                "page8_button3_command_once =";
            search_current_page_button_command_continue =
                "page8_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button3CommandOnceCmd);
            if (Page9_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button3CommandContinueCmd);
              Page9_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button3_label =";
            search_current_page_button_command_once =
                "page9_button3_command_once =";
            search_current_page_button_command_continue =
                "page9_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button3CommandOnceCmd);
            if (Page10_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button3CommandContinueCmd);
              Page10_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button3_label =";
            search_current_page_button_command_once =
                "page10_button3_command_once =";
            search_current_page_button_command_continue =
                "page10_button3_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button3CommandOnceCmd);
            if (Page11_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button3CommandContinueCmd);
              Page11_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button3_label =";
            search_current_page_button_command_once =
                "page11_button3_command_once =";
            search_current_page_button_command_continue =
                "page11_button3_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button3CommandOnceCmd);
            if (Page12_Button3ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button3CommandContinueCmd);
              Page12_Button3ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button3_label =";
            search_current_page_button_command_once =
                "page12_button3_command_once =";
            search_current_page_button_command_continue =
                "page12_button3_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button4_lbrt)) {
        mouse_down[3] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button4CommandOnceCmd);
            if (Page1_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button4CommandContinueCmd);
              Page1_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button4_label =";
            search_current_page_button_command_once =
                "page1_button4_command_once =";
            search_current_page_button_command_continue =
                "page1_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button4CommandOnceCmd);
            if (Page2_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button4CommandContinueCmd);
              Page2_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button4_label =";
            search_current_page_button_command_once =
                "page2_button4_command_once =";
            search_current_page_button_command_continue =
                "page2_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button4CommandOnceCmd);
            if (Page3_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button4CommandContinueCmd);
              Page3_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button4_label =";
            search_current_page_button_command_once =
                "page3_button4_command_once =";
            search_current_page_button_command_continue =
                "page3_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button4CommandOnceCmd);
            if (Page4_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button4CommandContinueCmd);
              Page4_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button4_label =";
            search_current_page_button_command_once =
                "page4_button4_command_once =";
            search_current_page_button_command_continue =
                "page4_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button4CommandOnceCmd);
            if (Page5_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button4CommandContinueCmd);
              Page5_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button4_label =";
            search_current_page_button_command_once =
                "page5_button4_command_once =";
            search_current_page_button_command_continue =
                "page5_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button4CommandOnceCmd);
            if (Page6_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button4CommandContinueCmd);
              Page6_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button4_label =";
            search_current_page_button_command_once =
                "page6_button4_command_once =";
            search_current_page_button_command_continue =
                "page6_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button4CommandOnceCmd);
            if (Page7_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button4CommandContinueCmd);
              Page7_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button4_label =";
            search_current_page_button_command_once =
                "page7_button4_command_once =";
            search_current_page_button_command_continue =
                "page7_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button4CommandOnceCmd);
            if (Page8_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button4CommandContinueCmd);
              Page8_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button4_label =";
            search_current_page_button_command_once =
                "page8_button4_command_once =";
            search_current_page_button_command_continue =
                "page8_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button4CommandOnceCmd);
            if (Page9_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button4CommandContinueCmd);
              Page9_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button4_label =";
            search_current_page_button_command_once =
                "page9_button4_command_once =";
            search_current_page_button_command_continue =
                "page9_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button4CommandOnceCmd);
            if (Page10_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button4CommandContinueCmd);
              Page10_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button4_label =";
            search_current_page_button_command_once =
                "page10_button4_command_once =";
            search_current_page_button_command_continue =
                "page10_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button4CommandOnceCmd);
            if (Page11_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button4CommandContinueCmd);
              Page11_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button4_label =";
            search_current_page_button_command_once =
                "page11_button4_command_once =";
            search_current_page_button_command_continue =
                "page11_button4_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button4CommandOnceCmd);
            if (Page12_Button4ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button4CommandContinueCmd);
              Page12_Button4ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button4_label =";
            search_current_page_button_command_once =
                "page12_button4_command_once =";
            search_current_page_button_command_continue =
                "page12_button4_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button5_lbrt)) {
        mouse_down[4] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button5CommandOnceCmd);
            if (Page1_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button5CommandContinueCmd);
              Page1_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button5_label =";
            search_current_page_button_command_once =
                "page1_button5_command_once =";
            search_current_page_button_command_continue =
                "page1_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button5CommandOnceCmd);
            if (Page2_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button5CommandContinueCmd);
              Page2_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button5_label =";
            search_current_page_button_command_once =
                "page2_button5_command_once =";
            search_current_page_button_command_continue =
                "page2_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button5CommandOnceCmd);
            if (Page3_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button5CommandContinueCmd);
              Page3_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button5_label =";
            search_current_page_button_command_once =
                "page3_button5_command_once =";
            search_current_page_button_command_continue =
                "page3_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button5CommandOnceCmd);
            if (Page4_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button5CommandContinueCmd);
              Page4_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button5_label =";
            search_current_page_button_command_once =
                "page4_button5_command_once =";
            search_current_page_button_command_continue =
                "page4_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button5CommandOnceCmd);
            if (Page5_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button5CommandContinueCmd);
              Page5_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button5_label =";
            search_current_page_button_command_once =
                "page5_button5_command_once =";
            search_current_page_button_command_continue =
                "page5_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button5CommandOnceCmd);
            if (Page6_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button5CommandContinueCmd);
              Page6_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button5_label =";
            search_current_page_button_command_once =
                "page6_button5_command_once =";
            search_current_page_button_command_continue =
                "page6_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button5CommandOnceCmd);
            if (Page7_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button5CommandContinueCmd);
              Page7_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button5_label =";
            search_current_page_button_command_once =
                "page7_button5_command_once =";
            search_current_page_button_command_continue =
                "page7_button5_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button5CommandOnceCmd);
            if (Page8_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button5CommandContinueCmd);
              Page8_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button5_label =";
            search_current_page_button_command_once =
                "page8_button5_command_once =";
            search_current_page_button_command_continue =
                "page8_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button5CommandOnceCmd);
            if (Page9_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button5CommandContinueCmd);
              Page9_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button5_label =";
            search_current_page_button_command_once =
                "page9_button5_command_once =";
            search_current_page_button_command_continue =
                "page9_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button5CommandOnceCmd);
            if (Page10_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button5CommandContinueCmd);
              Page10_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button5_label =";
            search_current_page_button_command_once =
                "page10_button5_command_once =";
            search_current_page_button_command_continue =
                "page10_button5_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button5CommandOnceCmd);
            if (Page11_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button5CommandContinueCmd);
              Page11_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button5_label =";
            search_current_page_button_command_once =
                "page11_button5_command_once =";
            search_current_page_button_command_continue =
                "page11_button5_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button5CommandOnceCmd);
            if (Page12_Button5ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button5CommandContinueCmd);
              Page12_Button5ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button5_label =";
            search_current_page_button_command_once =
                "page12_button5_command_once =";
            search_current_page_button_command_continue =
                "page12_button5_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button6_lbrt)) {
        mouse_down[5] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button6CommandOnceCmd);
            if (Page1_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button6CommandContinueCmd);
              Page1_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button6_label =";
            search_current_page_button_command_once =
                "page1_button6_command_once =";
            search_current_page_button_command_continue =
                "page1_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button6CommandOnceCmd);
            if (Page2_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button6CommandContinueCmd);
              Page2_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button6_label =";
            search_current_page_button_command_once =
                "page2_button6_command_once =";
            search_current_page_button_command_continue =
                "page2_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button6CommandOnceCmd);
            if (Page3_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button6CommandContinueCmd);
              Page3_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button6_label =";
            search_current_page_button_command_once =
                "page3_button6_command_once =";
            search_current_page_button_command_continue =
                "page3_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button6CommandOnceCmd);
            if (Page4_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button6CommandContinueCmd);
              Page4_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button6_label =";
            search_current_page_button_command_once =
                "page4_button6_command_once =";
            search_current_page_button_command_continue =
                "page4_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button6CommandOnceCmd);
            if (Page5_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button6CommandContinueCmd);
              Page5_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button6_label =";
            search_current_page_button_command_once =
                "page5_button6_command_once =";
            search_current_page_button_command_continue =
                "page5_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button6CommandOnceCmd);
            if (Page6_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button6CommandContinueCmd);
              Page6_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button6_label =";
            search_current_page_button_command_once =
                "page6_button6_command_once =";
            search_current_page_button_command_continue =
                "page6_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button6CommandOnceCmd);
            if (Page7_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button6CommandContinueCmd);
              Page7_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button6_label =";
            search_current_page_button_command_once =
                "page7_button6_command_once =";
            search_current_page_button_command_continue =
                "page7_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button6CommandOnceCmd);
            if (Page8_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button6CommandContinueCmd);
              Page8_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button6_label =";
            search_current_page_button_command_once =
                "page8_button6_command_once =";
            search_current_page_button_command_continue =
                "page8_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button6CommandOnceCmd);
            if (Page9_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button6CommandContinueCmd);
              Page9_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button6_label =";
            search_current_page_button_command_once =
                "page9_button6_command_once =";
            search_current_page_button_command_continue =
                "page9_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button6CommandOnceCmd);
            if (Page10_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button6CommandContinueCmd);
              Page10_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button6_label =";
            search_current_page_button_command_once =
                "page10_button6_command_once =";
            search_current_page_button_command_continue =
                "page10_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button6CommandOnceCmd);
            if (Page11_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button6CommandContinueCmd);
              Page11_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button6_label =";
            search_current_page_button_command_once =
                "page11_button6_command_once =";
            search_current_page_button_command_continue =
                "page11_button6_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button6CommandOnceCmd);
            if (Page12_Button6ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button6CommandContinueCmd);
              Page12_Button6ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button6_label =";
            search_current_page_button_command_once =
                "page12_button6_command_once =";
            search_current_page_button_command_continue =
                "page12_button6_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button7_lbrt)) {
        mouse_down[6] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button7CommandOnceCmd);
            if (Page1_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button7CommandContinueCmd);
              Page1_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button7_label =";
            search_current_page_button_command_once =
                "page1_button7_command_once =";
            search_current_page_button_command_continue =
                "page1_button7_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button7CommandOnceCmd);
            if (Page2_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button7CommandContinueCmd);
              Page2_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button7_label =";
            search_current_page_button_command_once =
                "page2_button7_command_once =";
            search_current_page_button_command_continue =
                "page2_button7_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button7CommandOnceCmd);
            if (Page3_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button7CommandContinueCmd);
              Page3_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button7_label =";
            search_current_page_button_command_once =
                "page3_button7_command_once =";
            search_current_page_button_command_continue =
                "page3_button7_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button7CommandOnceCmd);
            if (Page4_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button7CommandContinueCmd);
              Page4_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button7_label =";
            search_current_page_button_command_once =
                "page4_button7_command_once =";
            search_current_page_button_command_continue =
                "page4_button7_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button7CommandOnceCmd);
            if (Page5_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button7CommandContinueCmd);
              Page5_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button7_label =";
            search_current_page_button_command_once =
                "page5_button7_command_once =";
            search_current_page_button_command_continue =
                "page5_button7_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button7CommandOnceCmd);
            if (Page6_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button7CommandContinueCmd);
              Page6_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button7_label =";
            search_current_page_button_command_once =
                "page6_button7_command_once =";
            search_current_page_button_command_continue =
                "page6_button7_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button7CommandOnceCmd);
            if (Page7_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button7CommandContinueCmd);
              Page7_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button7_label =";
            search_current_page_button_command_once =
                "page7_button7_command_once =";
            search_current_page_button_command_continue =
                "page7_button7_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button7CommandOnceCmd);
            if (Page8_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button7CommandContinueCmd);
              Page8_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button7_label =";
            search_current_page_button_command_once =
                "page8_button7_command_once =";
            search_current_page_button_command_continue =
                "page8_button7_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button7CommandOnceCmd);
            if (Page9_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button7CommandContinueCmd);
              Page9_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button7_label =";
            search_current_page_button_command_once =
                "page9_button7_command_once =";
            search_current_page_button_command_continue =
                "page9_button7_command_continue =";
            populate_edit_window();
          }

        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button7CommandOnceCmd);
            if (Page10_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button7CommandContinueCmd);
              Page10_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button7_label =";
            search_current_page_button_command_once =
                "page10_button7_command_once =";
            search_current_page_button_command_continue =
                "page10_button7_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button7CommandOnceCmd);
            if (Page11_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button7CommandContinueCmd);
              Page11_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button7_label =";
            search_current_page_button_command_once =
                "page11_button7_command_once =";
            search_current_page_button_command_continue =
                "page11_button7_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button7CommandOnceCmd);
            if (Page12_Button7ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button7CommandContinueCmd);
              Page12_Button7ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button7_label =";
            search_current_page_button_command_once =
                "page12_button7_command_once =";
            search_current_page_button_command_continue =
                "page12_button7_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button8_lbrt)) {
        mouse_down[7] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button8CommandOnceCmd);
            if (Page1_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button8CommandContinueCmd);
              Page1_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button8_label =";
            search_current_page_button_command_once =
                "page1_button8_command_once =";
            search_current_page_button_command_continue =
                "page1_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button8CommandOnceCmd);
            if (Page2_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button8CommandContinueCmd);
              Page2_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button8_label =";
            search_current_page_button_command_once =
                "page2_button8_command_once =";
            search_current_page_button_command_continue =
                "page2_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button8CommandOnceCmd);
            if (Page3_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button8CommandContinueCmd);
              Page3_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button8_label =";
            search_current_page_button_command_once =
                "page3_button8_command_once =";
            search_current_page_button_command_continue =
                "page3_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button8CommandOnceCmd);
            if (Page4_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button8CommandContinueCmd);
              Page4_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button8_label =";
            search_current_page_button_command_once =
                "page4_button8_command_once =";
            search_current_page_button_command_continue =
                "page4_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button8CommandOnceCmd);
            if (Page5_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button8CommandContinueCmd);
              Page5_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button8_label =";
            search_current_page_button_command_once =
                "page5_button8_command_once =";
            search_current_page_button_command_continue =
                "page5_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button8CommandOnceCmd);
            if (Page6_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button8CommandContinueCmd);
              Page6_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button8_label =";
            search_current_page_button_command_once =
                "page6_button8_command_once =";
            search_current_page_button_command_continue =
                "page6_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button8CommandOnceCmd);
            if (Page7_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button8CommandContinueCmd);
              Page7_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button8_label =";
            search_current_page_button_command_once =
                "page7_button8_command_once =";
            search_current_page_button_command_continue =
                "page7_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button8CommandOnceCmd);
            if (Page8_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button8CommandContinueCmd);
              Page8_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button8_label =";
            search_current_page_button_command_once =
                "page8_button8_command_once =";
            search_current_page_button_command_continue =
                "page8_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button8CommandOnceCmd);
            if (Page9_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button8CommandContinueCmd);
              Page9_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button8_label =";
            search_current_page_button_command_once =
                "page9_button8_command_once =";
            search_current_page_button_command_continue =
                "page9_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button8CommandOnceCmd);
            if (Page10_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button8CommandContinueCmd);
              Page10_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button8_label =";
            search_current_page_button_command_once =
                "page10_button8_command_once =";
            search_current_page_button_command_continue =
                "page10_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button8CommandOnceCmd);
            if (Page11_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button8CommandContinueCmd);
              Page11_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button8_label =";
            search_current_page_button_command_once =
                "page11_button8_command_once =";
            search_current_page_button_command_continue =
                "page11_button8_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button8CommandOnceCmd);
            if (Page12_Button8ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button8CommandContinueCmd);
              Page12_Button8ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button8_label =";
            search_current_page_button_command_once =
                "page12_button8_command_once =";
            search_current_page_button_command_continue =
                "page12_button8_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button9_lbrt)) {
        mouse_down[8] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button9CommandOnceCmd);
            if (Page1_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button9CommandContinueCmd);
              Page1_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button9_label =";
            search_current_page_button_command_once =
                "page1_button9_command_once =";
            search_current_page_button_command_continue =
                "page1_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button9CommandOnceCmd);
            if (Page2_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button9CommandContinueCmd);
              Page2_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button9_label =";
            search_current_page_button_command_once =
                "page2_button9_command_once =";
            search_current_page_button_command_continue =
                "page2_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button9CommandOnceCmd);
            if (Page3_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button9CommandContinueCmd);
              Page3_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button9_label =";
            search_current_page_button_command_once =
                "page3_button9_command_once =";
            search_current_page_button_command_continue =
                "page3_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button9CommandOnceCmd);
            if (Page4_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button9CommandContinueCmd);
              Page4_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button9_label =";
            search_current_page_button_command_once =
                "page4_button9_command_once =";
            search_current_page_button_command_continue =
                "page4_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button9CommandOnceCmd);
            if (Page5_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button9CommandContinueCmd);
              Page5_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button9_label =";
            search_current_page_button_command_once =
                "page5_button9_command_once =";
            search_current_page_button_command_continue =
                "page5_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button9CommandOnceCmd);
            if (Page6_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button9CommandContinueCmd);
              Page6_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button9_label =";
            search_current_page_button_command_once =
                "page6_button9_command_once =";
            search_current_page_button_command_continue =
                "page6_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button9CommandOnceCmd);
            if (Page7_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button9CommandContinueCmd);
              Page7_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button9_label =";
            search_current_page_button_command_once =
                "page7_button9_command_once =";
            search_current_page_button_command_continue =
                "page7_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button9CommandOnceCmd);
            if (Page8_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button9CommandContinueCmd);
              Page8_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button9_label =";
            search_current_page_button_command_once =
                "page8_button9_command_once =";
            search_current_page_button_command_continue =
                "page8_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button9CommandOnceCmd);
            if (Page9_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button9CommandContinueCmd);
              Page9_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button9_label =";
            search_current_page_button_command_once =
                "page9_button9_command_once =";
            search_current_page_button_command_continue =
                "page9_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button9CommandOnceCmd);
            if (Page10_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button9CommandContinueCmd);
              Page10_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button9_label =";
            search_current_page_button_command_once =
                "page10_button9_command_once =";
            search_current_page_button_command_continue =
                "page10_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button9CommandOnceCmd);
            if (Page11_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button9CommandContinueCmd);
              Page11_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button9_label =";
            search_current_page_button_command_once =
                "page11_button9_command_once =";
            search_current_page_button_command_continue =
                "page11_button9_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button9CommandOnceCmd);
            if (Page12_Button9ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button9CommandContinueCmd);
              Page12_Button9ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button9_label =";
            search_current_page_button_command_once =
                "page12_button9_command_once =";
            search_current_page_button_command_continue =
                "page12_button9_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button10_lbrt)) {
        mouse_down[9] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button10CommandOnceCmd);
            if (Page1_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button10CommandContinueCmd);
              Page1_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button10_label =";
            search_current_page_button_command_once =
                "page1_button10_command_once =";
            search_current_page_button_command_continue =
                "page1_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button10CommandOnceCmd);
            if (Page2_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button10CommandContinueCmd);
              Page2_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label";
            search_current_page_button_label = "page2_button10_label =";
            search_current_page_button_command_once =
                "page2_button10_command_once =";
            search_current_page_button_command_continue =
                "page2_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button10CommandOnceCmd);
            if (Page3_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button10CommandContinueCmd);
              Page3_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button10_label =";
            search_current_page_button_command_once =
                "page3_button10_command_once =";
            search_current_page_button_command_continue =
                "page3_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button10CommandOnceCmd);
            if (Page4_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button10CommandContinueCmd);
              Page4_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button10_label =";
            search_current_page_button_command_once =
                "page4_button10_command_once =";
            search_current_page_button_command_continue =
                "page4_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button10CommandOnceCmd);
            if (Page5_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button10CommandContinueCmd);
              Page5_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button10_label =";
            search_current_page_button_command_once =
                "page5_button10_command_once =";
            search_current_page_button_command_continue =
                "page5_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button10CommandOnceCmd);
            if (Page6_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button10CommandContinueCmd);
              Page6_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button10_label =";
            search_current_page_button_command_once =
                "page6_button10_command_once =";
            search_current_page_button_command_continue =
                "page6_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button10CommandOnceCmd);
            if (Page7_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button10CommandContinueCmd);
              Page7_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button10_label =";
            search_current_page_button_command_once =
                "page7_button10_command_once =";
            search_current_page_button_command_continue =
                "page7_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button10CommandOnceCmd);
            if (Page8_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button10CommandContinueCmd);
              Page8_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button10_label =";
            search_current_page_button_command_once =
                "page8_button10_command_once =";
            search_current_page_button_command_continue =
                "page8_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button10CommandOnceCmd);
            if (Page9_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button10CommandContinueCmd);
              Page9_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button10_label =";
            search_current_page_button_command_once =
                "page9_button10_command_once =";
            search_current_page_button_command_continue =
                "page9_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button10CommandOnceCmd);
            if (Page10_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button10CommandContinueCmd);
              Page10_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button10_label =";
            search_current_page_button_command_once =
                "page10_button10_command_once =";
            search_current_page_button_command_continue =
                "page10_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button10CommandOnceCmd);
            if (Page11_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button10CommandContinueCmd);
              Page11_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button10_label =";
            search_current_page_button_command_once =
                "page11_button10_command_once =";
            search_current_page_button_command_continue =
                "page11_button10_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button10CommandOnceCmd);
            if (Page12_Button10ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button10CommandContinueCmd);
              Page12_Button10ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button10_label =";
            search_current_page_button_command_once =
                "page12_button10_command_once =";
            search_current_page_button_command_continue =
                "page12_button10_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button11_lbrt)) {
        mouse_down[10] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button11CommandOnceCmd);
            if (Page1_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button11CommandContinueCmd);
              Page1_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button11_label =";
            search_current_page_button_command_once =
                "page1_button11_command_once =";
            search_current_page_button_command_continue =
                "page1_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button11CommandOnceCmd);
            if (Page2_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button11CommandContinueCmd);
              Page2_Button11ContinueMode = 1;
            }

          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button11_label =";
            search_current_page_button_command_once =
                "page2_button11_command_once =";
            search_current_page_button_command_continue =
                "page2_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button11CommandOnceCmd);
            if (Page3_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button11CommandContinueCmd);
              Page3_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button11_label =";
            search_current_page_button_command_once =
                "page3_button11_command_once =";
            search_current_page_button_command_continue =
                "page3_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button11CommandOnceCmd);
            if (Page4_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button11CommandContinueCmd);
              Page4_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button11_label =";
            search_current_page_button_command_once =
                "page4_button11_command_once =";
            search_current_page_button_command_continue =
                "page4_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button11CommandOnceCmd);
            if (Page5_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button11CommandContinueCmd);
              Page5_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button11_label =";
            search_current_page_button_command_once =
                "page5_button11_command_once =";
            search_current_page_button_command_continue =
                "page5_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button11CommandOnceCmd);
            if (Page6_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button11CommandContinueCmd);
              Page6_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button11_label =";
            search_current_page_button_command_once =
                "page6_button11_command_once =";
            search_current_page_button_command_continue =
                "page6_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button11CommandOnceCmd);
            if (Page7_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button11CommandContinueCmd);
              Page7_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button11_label =";
            search_current_page_button_command_once =
                "page7_button11_command_once =";
            search_current_page_button_command_continue =
                "page7_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button11CommandOnceCmd);
            if (Page8_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button11CommandContinueCmd);
              Page8_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button11_label =";
            search_current_page_button_command_once =
                "page8_button11_command_once =";
            search_current_page_button_command_continue =
                "page8_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button11CommandOnceCmd);
            if (Page9_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button11CommandContinueCmd);
              Page9_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button11_label =";
            search_current_page_button_command_once =
                "page9_button11_command_once =";
            search_current_page_button_command_continue =
                "page9_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button11CommandOnceCmd);
            if (Page10_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button11CommandContinueCmd);
              Page10_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button11_label =";
            search_current_page_button_command_once =
                "page10_button11_command_once =";
            search_current_page_button_command_continue =
                "page10_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button11CommandOnceCmd);
            if (Page11_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button11CommandContinueCmd);
              Page11_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button11_label =";
            search_current_page_button_command_once =
                "page11_button11_command_once =";
            search_current_page_button_command_continue =
                "page11_button11_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button11CommandOnceCmd);
            if (Page12_Button11ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button11CommandContinueCmd);
              Page12_Button11ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button11_label =";
            search_current_page_button_command_once =
                "page12_button11_command_once =";
            search_current_page_button_command_continue =
                "page12_button11_command_continue =";
            populate_edit_window();
          }
        }
      }

      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button12_lbrt)) {
        mouse_down[11] = 1;
        if (page_number == 1) {
          if (!edit_mode) {
            XPLMCommandOnce(Page1_Button12CommandOnceCmd);
            if (Page1_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page1_Button12CommandContinueCmd);
              Page1_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page1_button_label =";
            search_current_page_button_label = "page1_button12_label =";
            search_current_page_button_command_once =
                "page1_button12_command_once =";
            search_current_page_button_command_continue =
                "page1_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 2) {
          if (!edit_mode) {
            XPLMCommandOnce(Page2_Button12CommandOnceCmd);
            if (Page2_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page2_Button12CommandContinueCmd);
              Page2_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page2_button_label =";
            search_current_page_button_label = "page2_button12_label =";
            search_current_page_button_command_once =
                "page2_button12_command_once =";
            search_current_page_button_command_continue =
                "page2_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 3) {
          if (!edit_mode) {
            XPLMCommandOnce(Page3_Button12CommandOnceCmd);
            if (Page3_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page3_Button12CommandContinueCmd);
              Page3_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page3_button_label =";
            search_current_page_button_label = "page3_button12_label =";
            search_current_page_button_command_once =
                "page3_button12_command_once =";
            search_current_page_button_command_continue =
                "page3_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 4) {
          if (!edit_mode) {
            XPLMCommandOnce(Page4_Button12CommandOnceCmd);
            if (Page4_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page4_Button12CommandContinueCmd);
              Page4_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page4_button_label =";
            search_current_page_button_label = "page4_button12_label =";
            search_current_page_button_command_once =
                "page4_button12_command_once =";
            search_current_page_button_command_continue =
                "page4_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 5) {
          if (!edit_mode) {
            XPLMCommandOnce(Page5_Button12CommandOnceCmd);
            if (Page5_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page5_Button12CommandContinueCmd);
              Page5_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page5_button_label =";
            search_current_page_button_label = "page5_button12_label =";
            search_current_page_button_command_once =
                "page5_button12_command_once =";
            search_current_page_button_command_continue =
                "page5_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 6) {
          if (!edit_mode) {
            XPLMCommandOnce(Page6_Button12CommandOnceCmd);
            if (Page6_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page6_Button12CommandContinueCmd);
              Page6_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page6_button_label =";
            search_current_page_button_label = "page6_button12_label =";
            search_current_page_button_command_once =
                "page6_button12_command_once =";
            search_current_page_button_command_continue =
                "page6_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 7) {
          if (!edit_mode) {
            XPLMCommandOnce(Page7_Button12CommandOnceCmd);
            if (Page7_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page7_Button12CommandContinueCmd);
              Page7_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page7_button_label =";
            search_current_page_button_label = "page7_button12_label =";
            search_current_page_button_command_once =
                "page7_button12_command_once =";
            search_current_page_button_command_continue =
                "page7_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 8) {
          if (!edit_mode) {
            XPLMCommandOnce(Page8_Button12CommandOnceCmd);
            if (Page8_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page8_Button12CommandContinueCmd);
              Page8_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page8_button_label =";
            search_current_page_button_label = "page8_button12_label =";
            search_current_page_button_command_once =
                "page8_button12_command_once =";
            search_current_page_button_command_continue =
                "page8_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button12CommandOnceCmd);
            if (Page9_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button12CommandContinueCmd);
              Page9_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button12_label =";
            search_current_page_button_command_once =
                "page9_button12_command_once =";
            search_current_page_button_command_continue =
                "page9_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button12CommandOnceCmd);
            if (Page10_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button12CommandContinueCmd);
              Page10_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button12_label =";
            search_current_page_button_command_once =
                "page10_button12_command_once =";
            search_current_page_button_command_continue =
                "page10_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button12CommandOnceCmd);
            if (Page11_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button12CommandContinueCmd);
              Page11_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button12_label =";
            search_current_page_button_command_once =
                "page11_button12_command_once =";
            search_current_page_button_command_continue =
                "page11_button12_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button12CommandOnceCmd);
            if (Page12_Button12ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button12CommandContinueCmd);
              Page12_Button12ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button12_label =";
            search_current_page_button_command_once =
                "page12_button12_command_once =";
            search_current_page_button_command_continue =
                "page12_button12_command_continue =";
            populate_edit_window();
          }
        }
      }


      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button13_lbrt)) {
        mouse_down[12] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button13CommandOnceCmd);
            if (Page9_Button13ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button13CommandContinueCmd);
              Page9_Button13ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button13_label =";
            search_current_page_button_command_once =
                "page9_button13_command_once =";
            search_current_page_button_command_continue =
                "page9_button13_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button13CommandOnceCmd);
            if (Page10_Button13ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button13CommandContinueCmd);
              Page10_Button13ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button13_label =";
            search_current_page_button_command_once =
                "page10_button13_command_once =";
            search_current_page_button_command_continue =
                "page10_button13_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button13CommandOnceCmd);
            if (Page11_Button13ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button13CommandContinueCmd);
              Page11_Button13ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button13_label =";
            search_current_page_button_command_once =
                "page11_button13_command_once =";
            search_current_page_button_command_continue =
                "page11_button13_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button13CommandOnceCmd);
            if (Page12_Button13ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button13CommandContinueCmd);
              Page12_Button13ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button13_label =";
            search_current_page_button_command_once =
                "page12_button13_command_once =";
            search_current_page_button_command_continue =
                "page12_button13_command_continue =";
            populate_edit_window();
          }
        }
      }




      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button14_lbrt)) {
        mouse_down[13] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button14CommandOnceCmd);
            if (Page9_Button14ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button14CommandContinueCmd);
              Page9_Button14ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button14_label =";
            search_current_page_button_command_once =
                "page9_button14_command_once =";
            search_current_page_button_command_continue =
                "page9_button14_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button14CommandOnceCmd);
            if (Page10_Button14ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button14CommandContinueCmd);
              Page10_Button14ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button14_label =";
            search_current_page_button_command_once =
                "page10_button14_command_once =";
            search_current_page_button_command_continue =
                "page10_button14_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button14CommandOnceCmd);
            if (Page11_Button14ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button14CommandContinueCmd);
              Page11_Button14ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button14_label =";
            search_current_page_button_command_once =
                "page11_button14_command_once =";
            search_current_page_button_command_continue =
                "page11_button14_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button14CommandOnceCmd);
            if (Page12_Button14ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button14CommandContinueCmd);
              Page12_Button14ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button14_label =";
            search_current_page_button_command_once =
                "page12_button14_command_once =";
            search_current_page_button_command_continue =
                "page12_button14_command_continue =";
            populate_edit_window();
          }
        }
      }







      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button15_lbrt)) {
        mouse_down[14] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button15CommandOnceCmd);
            if (Page9_Button15ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button15CommandContinueCmd);
              Page9_Button15ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button15_label =";
            search_current_page_button_command_once =
                "page9_button15_command_once =";
            search_current_page_button_command_continue =
                "page9_button15_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button15CommandOnceCmd);
            if (Page10_Button15ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button15CommandContinueCmd);
              Page10_Button15ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button15_label =";
            search_current_page_button_command_once =
                "page10_button15_command_once =";
            search_current_page_button_command_continue =
                "page10_button15_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button15CommandOnceCmd);
            if (Page11_Button15ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button15CommandContinueCmd);
              Page11_Button15ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button15_label =";
            search_current_page_button_command_once =
                "page11_button15_command_once =";
            search_current_page_button_command_continue =
                "page11_button15_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button15CommandOnceCmd);
            if (Page12_Button15ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button15CommandContinueCmd);
              Page12_Button15ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button15_label =";
            search_current_page_button_command_once =
                "page12_button15_command_once =";
            search_current_page_button_command_continue =
                "page12_button15_command_continue =";
            populate_edit_window();
          }
        }
      }






      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button16_lbrt)) {
        mouse_down[15] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button16CommandOnceCmd);
            if (Page9_Button16ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button16CommandContinueCmd);
              Page9_Button16ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button16_label =";
            search_current_page_button_command_once =
                "page9_button16_command_once =";
            search_current_page_button_command_continue =
                "page9_button16_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button16CommandOnceCmd);
            if (Page10_Button16ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button16CommandContinueCmd);
              Page10_Button16ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button16_label =";
            search_current_page_button_command_once =
                "page10_button16_command_once =";
            search_current_page_button_command_continue =
                "page10_button16_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button16CommandOnceCmd);
            if (Page11_Button16ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button16CommandContinueCmd);
              Page11_Button16ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button16_label =";
            search_current_page_button_command_once =
                "page11_button16_command_once =";
            search_current_page_button_command_continue =
                "page11_button16_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button16CommandOnceCmd);
            if (Page12_Button16ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button16CommandContinueCmd);
              Page12_Button16ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button16_label =";
            search_current_page_button_command_once =
                "page12_button16_command_once =";
            search_current_page_button_command_continue =
                "page12_button16_command_continue =";
            populate_edit_window();
          }
        }
      }




      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button17_lbrt)) {
        mouse_down[16] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button17CommandOnceCmd);
            if (Page9_Button17ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button17CommandContinueCmd);
              Page9_Button17ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button17_label =";
            search_current_page_button_command_once =
                "page9_button17_command_once =";
            search_current_page_button_command_continue =
                "page9_button17_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button17CommandOnceCmd);
            if (Page10_Button17ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button17CommandContinueCmd);
              Page10_Button17ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button17_label =";
            search_current_page_button_command_once =
                "page10_button17_command_once =";
            search_current_page_button_command_continue =
                "page10_button17_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button17CommandOnceCmd);
            if (Page11_Button17ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button17CommandContinueCmd);
              Page11_Button17ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button17_label =";
            search_current_page_button_command_once =
                "page11_button17_command_once =";
            search_current_page_button_command_continue =
                "page11_button17_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button17CommandOnceCmd);
            if (Page12_Button17ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button17CommandContinueCmd);
              Page12_Button17ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button17_label =";
            search_current_page_button_command_once =
                "page12_button17_command_once =";
            search_current_page_button_command_continue =
                "page12_button17_command_continue =";
            populate_edit_window();
          }
        }
      }




      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button18_lbrt)) {
        mouse_down[17] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button18CommandOnceCmd);
            if (Page9_Button18ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button18CommandContinueCmd);
              Page9_Button18ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button18_label =";
            search_current_page_button_command_once =
                "page9_button18_command_once =";
            search_current_page_button_command_continue =
                "page9_button18_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button18CommandOnceCmd);
            if (Page10_Button18ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button18CommandContinueCmd);
              Page10_Button18ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button18_label =";
            search_current_page_button_command_once =
                "page10_button18_command_once =";
            search_current_page_button_command_continue =
                "page10_button18_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button18CommandOnceCmd);
            if (Page11_Button18ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button18CommandContinueCmd);
              Page11_Button18ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button18_label =";
            search_current_page_button_command_once =
                "page11_button18_command_once =";
            search_current_page_button_command_continue =
                "page11_button18_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button18CommandOnceCmd);
            if (Page12_Button18ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button18CommandContinueCmd);
              Page12_Button18ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button18_label =";
            search_current_page_button_command_once =
                "page12_button18_command_once =";
            search_current_page_button_command_continue =
                "page12_button18_command_continue =";
            populate_edit_window();
          }
        }
      }





      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button19_lbrt)) {
        mouse_down[18] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button19CommandOnceCmd);
            if (Page9_Button19ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button19CommandContinueCmd);
              Page9_Button19ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button19_label =";
            search_current_page_button_command_once =
                "page9_button19_command_once =";
            search_current_page_button_command_continue =
                "page9_button19_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button19CommandOnceCmd);
            if (Page10_Button19ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button19CommandContinueCmd);
              Page10_Button19ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button19_label =";
            search_current_page_button_command_once =
                "page10_button19_command_once =";
            search_current_page_button_command_continue =
                "page10_button19_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button19CommandOnceCmd);
            if (Page11_Button19ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button19CommandContinueCmd);
              Page11_Button19ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button19_label =";
            search_current_page_button_command_once =
                "page11_button19_command_once =";
            search_current_page_button_command_continue =
                "page11_button19_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button19CommandOnceCmd);
            if (Page12_Button19ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button19CommandContinueCmd);
              Page12_Button19ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button19_label =";
            search_current_page_button_command_once =
                "page12_button19_command_once =";
            search_current_page_button_command_continue =
                "page12_button19_command_continue =";
            populate_edit_window();
          }
        }
      }




      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button20_lbrt)) {
        mouse_down[19] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button20CommandOnceCmd);
            if (Page9_Button20ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button20CommandContinueCmd);
              Page9_Button20ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button20_label =";
            search_current_page_button_command_once =
                "page9_button20_command_once =";
            search_current_page_button_command_continue =
                "page9_button20_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button20CommandOnceCmd);
            if (Page10_Button20ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button20CommandContinueCmd);
              Page10_Button20ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button20_label =";
            search_current_page_button_command_once =
                "page10_button20_command_once =";
            search_current_page_button_command_continue =
                "page10_button20_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button20CommandOnceCmd);
            if (Page11_Button20ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button20CommandContinueCmd);
              Page11_Button20ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button20_label =";
            search_current_page_button_command_once =
                "page11_button20_command_once =";
            search_current_page_button_command_continue =
                "page11_button20_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button20CommandOnceCmd);
            if (Page12_Button20ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button20CommandContinueCmd);
              Page12_Button20ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button20_label =";
            search_current_page_button_command_once =
                "page12_button20_command_once =";
            search_current_page_button_command_continue =
                "page12_button20_command_continue =";
            populate_edit_window();
          }
        }
      }




      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button21_lbrt)) {
        mouse_down[20] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button21CommandOnceCmd);
            if (Page9_Button21ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button21CommandContinueCmd);
              Page9_Button21ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button21_label =";
            search_current_page_button_command_once =
                "page9_button21_command_once =";
            search_current_page_button_command_continue =
                "page9_button21_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button21CommandOnceCmd);
            if (Page10_Button21ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button21CommandContinueCmd);
              Page10_Button21ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button21_label =";
            search_current_page_button_command_once =
                "page10_button21_command_once =";
            search_current_page_button_command_continue =
                "page10_button21_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button21CommandOnceCmd);
            if (Page11_Button21ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button21CommandContinueCmd);
              Page11_Button21ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button21_label =";
            search_current_page_button_command_once =
                "page11_button21_command_once =";
            search_current_page_button_command_continue =
                "page11_button21_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button21CommandOnceCmd);
            if (Page12_Button21ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button21CommandContinueCmd);
              Page12_Button21ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button21_label =";
            search_current_page_button_command_once =
                "page12_button21_command_once =";
            search_current_page_button_command_continue =
                "page12_button21_command_continue =";
            populate_edit_window();
          }
        }
      }



      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button22_lbrt)) {
        mouse_down[21] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button22CommandOnceCmd);
            if (Page9_Button22ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button22CommandContinueCmd);
              Page9_Button22ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button22_label =";
            search_current_page_button_command_once =
                "page9_button22_command_once =";
            search_current_page_button_command_continue =
                "page9_button22_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button22CommandOnceCmd);
            if (Page10_Button22ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button22CommandContinueCmd);
              Page10_Button22ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button22_label =";
            search_current_page_button_command_once =
                "page10_button22_command_once =";
            search_current_page_button_command_continue =
                "page10_button22_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button22CommandOnceCmd);
            if (Page11_Button22ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button22CommandContinueCmd);
              Page11_Button22ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button22_label =";
            search_current_page_button_command_once =
                "page11_button22_command_once =";
            search_current_page_button_command_continue =
                "page11_button22_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button22CommandOnceCmd);
            if (Page12_Button22ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button22CommandContinueCmd);
              Page12_Button22ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button22_label =";
            search_current_page_button_command_once =
                "page12_button22_command_once =";
            search_current_page_button_command_continue =
                "page12_button22_command_continue =";
            populate_edit_window();
          }
        }
      }





      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button23_lbrt)) {
        mouse_down[22] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button23CommandOnceCmd);
            if (Page9_Button23ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button23CommandContinueCmd);
              Page9_Button23ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button23_label =";
            search_current_page_button_command_once =
                "page9_button23_command_once =";
            search_current_page_button_command_continue =
                "page9_button23_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button23CommandOnceCmd);
            if (Page10_Button23ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button23CommandContinueCmd);
              Page10_Button23ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button23_label =";
            search_current_page_button_command_once =
                "page10_button23_command_once =";
            search_current_page_button_command_continue =
                "page10_button23_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button23CommandOnceCmd);
            if (Page11_Button23ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button23CommandContinueCmd);
              Page11_Button23ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button23_label =";
            search_current_page_button_command_once =
                "page11_button23_command_once =";
            search_current_page_button_command_continue =
                "page11_button23_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button23CommandOnceCmd);
            if (Page12_Button23ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button23CommandContinueCmd);
              Page12_Button23ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button23_label =";
            search_current_page_button_command_once =
                "page12_button23_command_once =";
            search_current_page_button_command_continue =
                "page12_button23_command_continue =";
            populate_edit_window();
          }
        }
      }






      else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button24_lbrt)) {
        mouse_down[23] = 1;
        if (page_number == 9) {
          if (!edit_mode) {
            XPLMCommandOnce(Page9_Button24CommandOnceCmd);
            if (Page9_Button24ContinueMode < 1) {
              XPLMCommandBegin(Page9_Button24CommandContinueCmd);
              Page9_Button24ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page9_button_label =";
            search_current_page_button_label = "page9_button24_label =";
            search_current_page_button_command_once =
                "page9_button24_command_once =";
            search_current_page_button_command_continue =
                "page9_button24_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 10) {
          if (!edit_mode) {
            XPLMCommandOnce(Page10_Button24CommandOnceCmd);
            if (Page10_Button24ContinueMode < 1) {
              XPLMCommandBegin(Page10_Button24CommandContinueCmd);
              Page10_Button24ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page10_button_label =";
            search_current_page_button_label = "page10_button24_label =";
            search_current_page_button_command_once =
                "page10_button24_command_once =";
            search_current_page_button_command_continue =
                "page10_button24_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 11) {
          if (!edit_mode) {
            XPLMCommandOnce(Page11_Button24CommandOnceCmd);
            if (Page11_Button24ContinueMode < 1) {
              XPLMCommandBegin(Page11_Button24CommandContinueCmd);
              Page11_Button24ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page11_button_label =";
            search_current_page_button_label = "page11_button24_label =";
            search_current_page_button_command_once =
                "page11_button24_command_once =";
            search_current_page_button_command_continue =
                "page11_button24_command_continue =";
            populate_edit_window();
          }
        } else if (page_number == 12) {
          if (!edit_mode) {
            XPLMCommandOnce(Page12_Button24CommandOnceCmd);
            if (Page12_Button24ContinueMode < 1) {
              XPLMCommandBegin(Page12_Button24CommandContinueCmd);
              Page12_Button24ContinueMode = 1;
            }
          } else {
            search_current_page_label = "page12_button_label =";
            search_current_page_button_label = "page12_button24_label =";
            search_current_page_button_command_once =
                "page12_button24_command_once =";
            search_current_page_button_command_continue =
                "page12_button24_command_continue =";
            populate_edit_window();
          }
        }
      }















      if (page_number == 13) {
        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number0_button_lbrt)) {
          number0_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 0;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number1_button_lbrt)) {
          number1_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 1;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number2_button_lbrt)) {
          number2_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 2;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number3_button_lbrt)) {
          number3_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 3;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number4_button_lbrt)) {
          number4_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 4;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number5_button_lbrt)) {
          number5_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 5;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number6_button_lbrt)) {
          number6_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 6;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number7_button_lbrt)) {
          number7_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 7;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number8_button_lbrt)) {
          number8_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 8;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_number9_button_lbrt)) {
          number9_mouse_down = 1;
          if (number_position < 5) {
            number_position = number_position + 1;
            number_mouse_down_value = 9;
            xbtn2cmd_radio_Vector.push_back(number_mouse_down_value);
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_clear_button_lbrt)) {
          clear_mouse_down = 1;
          number_position = 0;
          xbtn2cmd_radio_Vector.clear();
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_com1a_button_lbrt)) {
          com1a_mouse_down = 1;
          if (radio_Vector_size == 5) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 10000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 1000;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 100;
            radio_freq4 = xbtn2cmd_radio_Vector[3] * 10;
            radio_freq5 = xbtn2cmd_radio_Vector[4];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_com1_actv_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_com1_actv_freq, radio_com1_actv_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_com1s_button_lbrt)) {
          com1s_mouse_down = 1;
          if (radio_Vector_size == 5) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 10000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 1000;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 100;
            radio_freq4 = xbtn2cmd_radio_Vector[3] * 10;
            radio_freq5 = xbtn2cmd_radio_Vector[4];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_com1_stby_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_com1_stby_freq, radio_com1_stby_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_adf1a_button_lbrt)) {
          adf1a_mouse_down = 1;
          if (radio_Vector_size == 4) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 1000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 100;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 10;
            radio_freq4 = xbtn2cmd_radio_Vector[3];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_adf1_actv_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_adf1_actv_freq, radio_adf1_actv_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_adf1s_button_lbrt)) {
          adf1s_mouse_down = 1;
          if (radio_Vector_size == 4) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 1000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 100;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 10;
            radio_freq4 = xbtn2cmd_radio_Vector[3];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_adf1_stby_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_adf1_stby_freq, radio_adf1_stby_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_com2a_button_lbrt)) {
          com2a_mouse_down = 1;
          if (radio_Vector_size == 5) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 10000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 1000;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 100;
            radio_freq4 = xbtn2cmd_radio_Vector[3] * 10;
            radio_freq5 = xbtn2cmd_radio_Vector[4];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_com2_actv_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_com2_actv_freq, radio_com2_actv_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_com2s_button_lbrt)) {
          com2s_mouse_down = 1;
          if (radio_Vector_size == 5) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 10000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 1000;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 100;
            radio_freq4 = xbtn2cmd_radio_Vector[3] * 10;
            radio_freq5 = xbtn2cmd_radio_Vector[4];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_com2_stby_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_com2_stby_freq, radio_com2_stby_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_adf2a_button_lbrt)) {
          adf2a_mouse_down = 1;
          if (radio_Vector_size == 4) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 1000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 100;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 10;
            radio_freq4 = xbtn2cmd_radio_Vector[3];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_adf2_actv_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_adf2_actv_freq, radio_adf2_actv_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_adf2s_button_lbrt)) {
          adf2s_mouse_down = 1;
          if (radio_Vector_size == 4) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 1000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 100;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 10;
            radio_freq4 = xbtn2cmd_radio_Vector[3];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_adf2_stby_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_adf2_stby_freq, radio_adf2_stby_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_nav1a_button_lbrt)) {
          nav1a_mouse_down = 1;
          if (radio_Vector_size == 5) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 10000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 1000;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 100;
            radio_freq4 = xbtn2cmd_radio_Vector[3] * 10;
            radio_freq5 = xbtn2cmd_radio_Vector[4];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_nav1_actv_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_nav1_actv_freq, radio_nav1_actv_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_nav1s_button_lbrt)) {
          nav1s_mouse_down = 1;
          if (radio_Vector_size == 5) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 10000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 1000;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 100;
            radio_freq4 = xbtn2cmd_radio_Vector[3] * 10;
            radio_freq5 = xbtn2cmd_radio_Vector[4];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_nav1_stby_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_nav1_stby_freq, radio_nav1_stby_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_nav2a_button_lbrt)) {
          nav2a_mouse_down = 1;
          if (radio_Vector_size == 5) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 10000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 1000;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 100;
            radio_freq4 = xbtn2cmd_radio_Vector[3] * 10;
            radio_freq5 = xbtn2cmd_radio_Vector[4];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_nav2_actv_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_nav2_actv_freq, radio_nav2_actv_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_nav2s_button_lbrt)) {
          nav2s_mouse_down = 1;
          if (radio_Vector_size == 5) {
            radio_freq1 = xbtn2cmd_radio_Vector[0] * 10000;
            radio_freq2 = xbtn2cmd_radio_Vector[1] * 1000;
            radio_freq3 = xbtn2cmd_radio_Vector[2] * 100;
            radio_freq4 = xbtn2cmd_radio_Vector[3] * 10;
            radio_freq5 = xbtn2cmd_radio_Vector[4];
            radio_freq = radio_freq1 + radio_freq2 + radio_freq3 + radio_freq4 +
                         radio_freq5;
            radio_nav2_stby_freq = radio_freq;
            XPLMSetDatai(XPLM_radio_nav2_stby_freq, radio_nav2_stby_freq);
            number_position = 0;
            xbtn2cmd_radio_Vector.clear();
          }
        }
      }

      if (page_number == 14) {
        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_com_ff_button_lbrt)) {
          g_430n1_com_ff_mouse_down = 1;
          XPLMCommandOnce(g430n1_com_ff_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_nav_ff_button_lbrt)) {
          g_430n1_nav_ff_mouse_down = 1;
          XPLMCommandOnce(g430n1_nav_ff_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_fine_down_button_lbrt)) {
          g_430n1_fine_down_mouse_down = 1;
          XPLMCommandOnce(g430n1_fine_down_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_fine_up_button_lbrt)) {
          g_430n1_fine_up_mouse_down = 1;
          XPLMCommandOnce(g430n1_fine_up_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y,
                          g_430n1_nav_com_tog_button_lbrt)) {
          g_430n1_nav_com_tog_mouse_down = 1;
          XPLMCommandOnce(g430n1_nav_com_tog_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y,
                          g_430n1_coarse_down_button_lbrt)) {
          g_430n1_coarse_down_mouse_down = 1;
          XPLMCommandOnce(g430n1_coarse_down_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_coarse_up_button_lbrt)) {
          g_430n1_coarse_up_mouse_down = 1;
          XPLMCommandOnce(g430n1_coarse_up_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_cdi_button_lbrt)) {
          g_430n1_cdi_mouse_down = 1;
          XPLMCommandOnce(g430n1_cdi_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_obs_button_lbrt)) {
          g_430n1_obs_mouse_down = 1;
          XPLMCommandOnce(g430n1_obs_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_msg_button_lbrt)) {
          g_430n1_msg_mouse_down = 1;
          XPLMCommandOnce(g430n1_msg_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_fpl_button_lbrt)) {
          g_430n1_fpl_mouse_down = 1;
          XPLMCommandOnce(g430n1_fpl_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_vnav_button_lbrt)) {
          g_430n1_vnav_mouse_down = 1;
          XPLMCommandOnce(g430n1_vnav_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_proc_button_lbrt)) {
          g_430n1_proc_mouse_down = 1;
          XPLMCommandOnce(g430n1_proc_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_zoom_in_button_lbrt)) {
          g_430n1_zoom_in_mouse_down = 1;
          XPLMCommandOnce(g430n1_zoom_in_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_zoom_out_button_lbrt)) {
          g_430n1_zoom_out_mouse_down = 1;
          XPLMCommandOnce(g430n1_zoom_out_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_direct_button_lbrt)) {
          g_430n1_direct_mouse_down = 1;
          XPLMCommandOnce(g430n1_direct_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_menu_button_lbrt)) {
          g_430n1_menu_mouse_down = 1;
          XPLMCommandOnce(g430n1_menu_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_clr_button_lbrt)) {
          g_430n1_clr_mouse_down = 1;
          XPLMCommandOnce(g430n1_clr_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_ent_button_lbrt)) {
          g_430n1_ent_mouse_down = 1;
          XPLMCommandOnce(g430n1_ent_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_cursor_button_lbrt)) {
          g_430n1_cursor_mouse_down = 1;
          XPLMCommandOnce(g430n1_cursor_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_page_up_button_lbrt)) {
          g_430n1_page_up_mouse_down = 1;
          XPLMCommandOnce(g430n1_page_up_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_page_dn_button_lbrt)) {
          g_430n1_page_dn_mouse_down = 1;
          XPLMCommandOnce(g430n1_page_dn_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_chapter_up_button_lbrt)) {
          g_430n1_chapter_up_mouse_down = 1;
          XPLMCommandOnce(g430n1_chapter_up_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n1_chapter_dn_button_lbrt)) {
          g_430n1_chapter_dn_mouse_down = 1;
          XPLMCommandOnce(g430n1_chapter_dn_cmd);
        }
      }

      if (page_number == 15) {
        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_com_ff_button_lbrt)) {
          g_430n2_com_ff_mouse_down = 1;
          XPLMCommandOnce(g430n2_com_ff_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_nav_ff_button_lbrt)) {
          g_430n2_nav_ff_mouse_down = 1;
          XPLMCommandOnce(g430n2_nav_ff_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_fine_down_button_lbrt)) {
          g_430n2_fine_down_mouse_down = 1;
          XPLMCommandOnce(g430n2_fine_down_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_fine_up_button_lbrt)) {
          g_430n2_fine_up_mouse_down = 1;
          XPLMCommandOnce(g430n2_fine_up_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y,
                          g_430n2_nav_com_tog_button_lbrt)) {
          g_430n2_nav_com_tog_mouse_down = 1;
          XPLMCommandOnce(g430n2_nav_com_tog_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y,
                          g_430n2_coarse_down_button_lbrt)) {
          g_430n2_coarse_down_mouse_down = 1;
          XPLMCommandOnce(g430n2_coarse_down_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_coarse_up_button_lbrt)) {
          g_430n2_coarse_up_mouse_down = 1;
          XPLMCommandOnce(g430n2_coarse_up_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_cdi_button_lbrt)) {
          g_430n2_cdi_mouse_down = 1;
          XPLMCommandOnce(g430n2_cdi_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_obs_button_lbrt)) {
          g_430n2_obs_mouse_down = 1;
          XPLMCommandOnce(g430n2_obs_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_msg_button_lbrt)) {
          g_430n2_msg_mouse_down = 1;
          XPLMCommandOnce(g430n2_msg_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_fpl_button_lbrt)) {
          g_430n2_fpl_mouse_down = 1;
          XPLMCommandOnce(g430n2_fpl_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_vnav_button_lbrt)) {
          g_430n2_vnav_mouse_down = 1;
          XPLMCommandOnce(g430n2_vnav_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_proc_button_lbrt)) {
          g_430n2_proc_mouse_down = 1;
          XPLMCommandOnce(g430n2_proc_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_zoom_in_button_lbrt)) {
          g_430n2_zoom_in_mouse_down = 1;
          XPLMCommandOnce(g430n2_zoom_in_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_zoom_out_button_lbrt)) {
          g_430n2_zoom_out_mouse_down = 1;
          XPLMCommandOnce(g430n2_zoom_out_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_direct_button_lbrt)) {
          g_430n2_direct_mouse_down = 1;
          XPLMCommandOnce(g430n2_direct_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_menu_button_lbrt)) {
          g_430n2_menu_mouse_down = 1;
          XPLMCommandOnce(g430n2_menu_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_clr_button_lbrt)) {
          g_430n2_clr_mouse_down = 1;
          XPLMCommandOnce(g430n2_clr_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_ent_button_lbrt)) {
          g_430n2_ent_mouse_down = 1;
          XPLMCommandOnce(g430n2_ent_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_cursor_button_lbrt)) {
          g_430n2_cursor_mouse_down = 1;
          XPLMCommandOnce(g430n2_cursor_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_page_up_button_lbrt)) {
          g_430n2_page_up_mouse_down = 1;
          XPLMCommandOnce(g430n2_page_up_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_page_dn_button_lbrt)) {
          g_430n2_page_dn_mouse_down = 1;
          XPLMCommandOnce(g430n2_page_dn_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_chapter_up_button_lbrt)) {
          g_430n2_chapter_up_mouse_down = 1;
          XPLMCommandOnce(g430n2_chapter_up_cmd);
        }

        if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_430n2_chapter_dn_button_lbrt)) {
          g_430n2_chapter_dn_mouse_down = 1;
          XPLMCommandOnce(g430n2_chapter_dn_cmd);
        }
      }
    }
    radio_Vector_size = static_cast<int>(xbtn2cmd_radio_Vector.size());
  }

  if (xb2cvr_mouse_status == xplm_MouseUp) {
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

    number0_mouse_down = 0, number1_mouse_down = 0, number2_mouse_down = 0,
    number3_mouse_down = 0;
    number4_mouse_down = 0, number5_mouse_down = 0, number6_mouse_down = 0,
    number7_mouse_down = 0;
    number8_mouse_down = 0, number9_mouse_down = 0, clear_mouse_down = 0;
    com1a_mouse_down = 0, com2a_mouse_down = 0, nav1a_mouse_down = 0,
    nav2a_mouse_down = 0;
    com1s_mouse_down = 0, com2s_mouse_down = 0, nav1s_mouse_down = 0,
    nav2s_mouse_down = 0;
    adf1a_mouse_down = 0, adf2a_mouse_down = 0;
    adf1s_mouse_down = 0, adf2s_mouse_down = 0;

    g_430n1_com_ff_mouse_down = 0, g_430n1_nav_ff_mouse_down = 0,
    g_430n1_fine_down_mouse_down = 0;
    g_430n1_fine_up_mouse_down = 0, g_430n1_nav_com_tog_mouse_down = 0,
    g_430n1_coarse_down_mouse_down = 0;
    g_430n1_coarse_up_mouse_down = 0, g_430n1_cdi_mouse_down = 0,
    g_430n1_obs_mouse_down = 0, g_430n1_msg_mouse_down = 0;
    g_430n1_fpl_mouse_down = 0, g_430n1_vnav_mouse_down = 0,
    g_430n1_proc_mouse_down = 0, g_430n1_zoom_in_mouse_down = 0;
    g_430n1_zoom_out_mouse_down = 0, g_430n1_direct_mouse_down = 0,
    g_430n1_menu_mouse_down = 0, g_430n1_clr_mouse_down = 0;
    g_430n1_ent_mouse_down = 0, g_430n1_cursor_mouse_down = 0,
    g_430n1_page_up_mouse_down = 0, g_430n1_page_dn_mouse_down = 0;
    g_430n1_chapter_up_mouse_down = 0, g_430n1_chapter_dn_mouse_down = 0;

    g_430n2_com_ff_mouse_down = 0, g_430n2_nav_ff_mouse_down = 0,
    g_430n2_fine_down_mouse_down = 0;
    g_430n2_fine_up_mouse_down = 0, g_430n2_nav_com_tog_mouse_down = 0,
    g_430n2_coarse_down_mouse_down = 0;
    g_430n2_coarse_up_mouse_down = 0, g_430n2_cdi_mouse_down = 0,
    g_430n2_obs_mouse_down = 0, g_430n2_msg_mouse_down = 0;
    g_430n2_fpl_mouse_down = 0, g_430n2_vnav_mouse_down = 0,
    g_430n2_proc_mouse_down = 0, g_430n2_zoom_in_mouse_down = 0;
    g_430n2_zoom_out_mouse_down = 0, g_430n2_direct_mouse_down = 0,
    g_430n2_menu_mouse_down = 0, g_430n2_clr_mouse_down = 0;
    g_430n2_ent_mouse_down = 0, g_430n2_cursor_mouse_down = 0,
    g_430n2_page_up_mouse_down = 0, g_430n2_page_dn_mouse_down = 0;
    g_430n2_chapter_up_mouse_down = 0, g_430n2_chapter_dn_mouse_down = 0;

    if (page_number == 1) {
      if (Page1_Button1ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button1CommandContinueCmd);
        Page1_Button1ContinueMode = 0;
      }

      if (Page1_Button2ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button2CommandContinueCmd);
        Page1_Button2ContinueMode = 0;
      }

      if (Page1_Button3ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button3CommandContinueCmd);
        Page1_Button3ContinueMode = 0;
      }

      if (Page1_Button4ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button4CommandContinueCmd);
        Page1_Button4ContinueMode = 0;
      }

      if (Page1_Button5ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button5CommandContinueCmd);
        Page1_Button5ContinueMode = 0;
      }

      if (Page1_Button6ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button6CommandContinueCmd);
        Page1_Button6ContinueMode = 0;
      }

      if (Page1_Button7ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button7CommandContinueCmd);
        Page1_Button7ContinueMode = 0;
      }

      if (Page1_Button8ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button8CommandContinueCmd);
        Page1_Button8ContinueMode = 0;
      }

      if (Page1_Button9ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button9CommandContinueCmd);
        Page1_Button9ContinueMode = 0;
      }

      if (Page1_Button10ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button10CommandContinueCmd);
        Page1_Button10ContinueMode = 0;
      }

      if (Page1_Button11ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button11CommandContinueCmd);
        Page1_Button11ContinueMode = 0;
      }

      if (Page1_Button12ContinueMode == 1) {
        XPLMCommandEnd(Page1_Button12CommandContinueCmd);
        Page1_Button12ContinueMode = 0;
      }

    } else if (page_number == 2) {
      if (Page2_Button1ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button1CommandContinueCmd);
        Page2_Button1ContinueMode = 0;
      }

      if (Page2_Button2ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button2CommandContinueCmd);
        Page2_Button2ContinueMode = 0;
      }

      if (Page2_Button3ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button3CommandContinueCmd);
        Page2_Button3ContinueMode = 0;
      }

      if (Page2_Button4ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button4CommandContinueCmd);
        Page2_Button4ContinueMode = 0;
      }

      if (Page2_Button5ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button5CommandContinueCmd);
        Page2_Button5ContinueMode = 0;
      }

      if (Page2_Button6ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button6CommandContinueCmd);
        Page2_Button6ContinueMode = 0;
      }

      if (Page2_Button7ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button7CommandContinueCmd);
        Page2_Button7ContinueMode = 0;
      }

      if (Page2_Button8ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button8CommandContinueCmd);
        Page2_Button8ContinueMode = 0;
      }

      if (Page2_Button9ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button9CommandContinueCmd);
        Page2_Button9ContinueMode = 0;
      }

      if (Page2_Button10ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button10CommandContinueCmd);
        Page2_Button10ContinueMode = 0;
      }

      if (Page2_Button11ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button11CommandContinueCmd);
        Page2_Button11ContinueMode = 0;
      }

      if (Page2_Button12ContinueMode == 1) {
        XPLMCommandEnd(Page2_Button12CommandContinueCmd);
        Page2_Button12ContinueMode = 0;
      }

    } else if (page_number == 3) {
      if (Page3_Button1ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button1CommandContinueCmd);
        Page3_Button1ContinueMode = 0;
      }

      if (Page3_Button2ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button2CommandContinueCmd);
        Page3_Button2ContinueMode = 0;
      }

      if (Page3_Button3ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button3CommandContinueCmd);
        Page3_Button3ContinueMode = 0;
      }

      if (Page3_Button4ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button4CommandContinueCmd);
        Page3_Button4ContinueMode = 0;
      }

      if (Page3_Button5ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button5CommandContinueCmd);
        Page3_Button5ContinueMode = 0;
      }

      if (Page3_Button6ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button6CommandContinueCmd);
        Page3_Button6ContinueMode = 0;
      }

      if (Page3_Button7ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button7CommandContinueCmd);
        Page3_Button7ContinueMode = 0;
      }

      if (Page3_Button8ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button8CommandContinueCmd);
        Page3_Button8ContinueMode = 0;
      }

      if (Page3_Button9ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button9CommandContinueCmd);
        Page3_Button9ContinueMode = 0;
      }

      if (Page3_Button10ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button10CommandContinueCmd);
        Page3_Button10ContinueMode = 0;
      }

      if (Page3_Button11ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button11CommandContinueCmd);
        Page3_Button11ContinueMode = 0;
      }

      if (Page3_Button12ContinueMode == 1) {
        XPLMCommandEnd(Page3_Button12CommandContinueCmd);
        Page3_Button12ContinueMode = 0;
      }

    } else if (page_number == 4) {
      if (Page4_Button1ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button1CommandContinueCmd);
        Page4_Button1ContinueMode = 0;
      }

      if (Page4_Button2ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button2CommandContinueCmd);
        Page4_Button2ContinueMode = 0;
      }

      if (Page4_Button3ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button3CommandContinueCmd);
        Page4_Button3ContinueMode = 0;
      }

      if (Page4_Button4ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button4CommandContinueCmd);
        Page4_Button4ContinueMode = 0;
      }

      if (Page4_Button5ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button5CommandContinueCmd);
        Page4_Button5ContinueMode = 0;
      }

      if (Page4_Button6ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button6CommandContinueCmd);
        Page4_Button6ContinueMode = 0;
      }

      if (Page4_Button7ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button7CommandContinueCmd);
        Page4_Button7ContinueMode = 0;
      }

      if (Page4_Button8ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button8CommandContinueCmd);
        Page4_Button8ContinueMode = 0;
      }

      if (Page4_Button9ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button9CommandContinueCmd);
        Page4_Button9ContinueMode = 0;
      }

      if (Page4_Button10ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button10CommandContinueCmd);
        Page4_Button10ContinueMode = 0;
      }

      if (Page4_Button11ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button11CommandContinueCmd);
        Page4_Button11ContinueMode = 0;
      }

      if (Page4_Button12ContinueMode == 1) {
        XPLMCommandEnd(Page4_Button12CommandContinueCmd);
        Page4_Button12ContinueMode = 0;
      }
    } else if (page_number == 5) {
      if (Page5_Button1ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button1CommandContinueCmd);
        Page5_Button1ContinueMode = 0;
      }

      if (Page5_Button2ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button2CommandContinueCmd);
        Page5_Button2ContinueMode = 0;
      }

      if (Page5_Button3ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button3CommandContinueCmd);
        Page5_Button3ContinueMode = 0;
      }

      if (Page5_Button4ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button4CommandContinueCmd);
        Page5_Button4ContinueMode = 0;
      }

      if (Page5_Button5ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button5CommandContinueCmd);
        Page5_Button5ContinueMode = 0;
      }

      if (Page5_Button6ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button6CommandContinueCmd);
        Page5_Button6ContinueMode = 0;
      }

      if (Page5_Button7ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button7CommandContinueCmd);
        Page5_Button7ContinueMode = 0;
      }

      if (Page5_Button8ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button8CommandContinueCmd);
        Page5_Button8ContinueMode = 0;
      }

      if (Page5_Button9ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button9CommandContinueCmd);
        Page5_Button9ContinueMode = 0;
      }

      if (Page5_Button10ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button10CommandContinueCmd);
        Page5_Button10ContinueMode = 0;
      }

      if (Page5_Button11ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button11CommandContinueCmd);
        Page5_Button11ContinueMode = 0;
      }

      if (Page5_Button12ContinueMode == 1) {
        XPLMCommandEnd(Page5_Button12CommandContinueCmd);
        Page5_Button12ContinueMode = 0;
      }
    } else if (page_number == 6) {
      if (Page6_Button1ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button1CommandContinueCmd);
        Page6_Button1ContinueMode = 0;
      }

      if (Page6_Button2ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button2CommandContinueCmd);
        Page6_Button2ContinueMode = 0;
      }

      if (Page6_Button3ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button3CommandContinueCmd);
        Page6_Button3ContinueMode = 0;
      }

      if (Page6_Button4ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button4CommandContinueCmd);
        Page6_Button4ContinueMode = 0;
      }

      if (Page6_Button5ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button5CommandContinueCmd);
        Page6_Button5ContinueMode = 0;
      }

      if (Page6_Button6ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button6CommandContinueCmd);
        Page6_Button6ContinueMode = 0;
      }

      if (Page6_Button7ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button7CommandContinueCmd);
        Page6_Button7ContinueMode = 0;
      }

      if (Page6_Button8ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button8CommandContinueCmd);
        Page6_Button8ContinueMode = 0;
      }

      if (Page6_Button9ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button9CommandContinueCmd);
        Page6_Button9ContinueMode = 0;
      }

      if (Page6_Button10ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button10CommandContinueCmd);
        Page6_Button10ContinueMode = 0;
      }

      if (Page6_Button11ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button11CommandContinueCmd);
        Page6_Button11ContinueMode = 0;
      }

      if (Page6_Button12ContinueMode == 1) {
        XPLMCommandEnd(Page6_Button12CommandContinueCmd);
        Page6_Button12ContinueMode = 0;
      }
    } else if (page_number == 7) {
      if (Page7_Button1ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button1CommandContinueCmd);
        Page7_Button1ContinueMode = 0;
      }

      if (Page7_Button2ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button2CommandContinueCmd);
        Page7_Button2ContinueMode = 0;
      }

      if (Page7_Button3ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button3CommandContinueCmd);
        Page7_Button3ContinueMode = 0;
      }

      if (Page7_Button4ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button4CommandContinueCmd);
        Page7_Button4ContinueMode = 0;
      }

      if (Page7_Button5ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button5CommandContinueCmd);
        Page7_Button5ContinueMode = 0;
      }

      if (Page7_Button6ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button6CommandContinueCmd);
        Page7_Button6ContinueMode = 0;
      }

      if (Page7_Button7ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button7CommandContinueCmd);
        Page7_Button7ContinueMode = 0;
      }

      if (Page7_Button8ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button8CommandContinueCmd);
        Page7_Button8ContinueMode = 0;
      }

      if (Page7_Button9ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button9CommandContinueCmd);
        Page7_Button9ContinueMode = 0;
      }

      if (Page7_Button10ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button10CommandContinueCmd);
        Page7_Button10ContinueMode = 0;
      }

      if (Page7_Button11ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button11CommandContinueCmd);
        Page7_Button11ContinueMode = 0;
      }

      if (Page7_Button12ContinueMode == 1) {
        XPLMCommandEnd(Page7_Button12CommandContinueCmd);
        Page7_Button12ContinueMode = 0;
      }
    } else if (page_number == 8) {
      if (Page8_Button1ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button1CommandContinueCmd);
        Page8_Button1ContinueMode = 0;
      }

      if (Page8_Button2ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button2CommandContinueCmd);
        Page8_Button2ContinueMode = 0;
      }

      if (Page8_Button3ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button3CommandContinueCmd);
        Page8_Button3ContinueMode = 0;
      }

      if (Page8_Button4ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button4CommandContinueCmd);
        Page8_Button4ContinueMode = 0;
      }

      if (Page8_Button5ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button5CommandContinueCmd);
        Page8_Button5ContinueMode = 0;
      }

      if (Page8_Button6ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button6CommandContinueCmd);
        Page8_Button6ContinueMode = 0;
      }

      if (Page8_Button7ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button7CommandContinueCmd);
        Page8_Button7ContinueMode = 0;
      }

      if (Page8_Button8ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button8CommandContinueCmd);
        Page8_Button8ContinueMode = 0;
      }

      if (Page8_Button9ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button9CommandContinueCmd);
        Page8_Button9ContinueMode = 0;
      }

      if (Page8_Button10ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button10CommandContinueCmd);
        Page8_Button10ContinueMode = 0;
      }

      if (Page8_Button11ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button11CommandContinueCmd);
        Page8_Button11ContinueMode = 0;
      }

      if (Page8_Button12ContinueMode == 1) {
        XPLMCommandEnd(Page8_Button12CommandContinueCmd);
        Page8_Button12ContinueMode = 0;
      }
    }
  }

  return 1;
}
