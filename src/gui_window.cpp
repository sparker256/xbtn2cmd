#include "XPLMDisplay.h"    // for window creation and manipulation
#include "XPLMGraphics.h"   // for window drawing
#include "XPLMDataAccess.h" // for the VR dataref
#include "XPLMPlugin.h"     // for XPLM_MSG_SCENERY_LOADED message
#include "XPLMUtilities.h"  // for Various utilities
#include <stdio.h>
#include <string.h>
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


#include "xbtn2cmd.h"


static float g_check_box_lbrt[25][4]; // left, bottom, right, top
static float g_previous_button_lbrt[4]; // left, bottom, right, top
static float g_next_button_lbrt[4]; // left, bottom, right, top
static float g_check_item_button_lbrt[4]; // left, bottom, right, top

static float g_hide_button_lbrt[4]; // left, bottom, right, top

static float g_page1_button_lbrt[4]; // left, bottom, right, top
static float g_page2_button_lbrt[4]; // left, bottom, right, top
static float g_page3_button_lbrt[4]; // left, bottom, right, top
static float g_page4_button_lbrt[4]; // left, bottom, right, top


static float g_button1_lbrt[4]; // left, bottom, right, top
static float g_button2_lbrt[4]; // left, bottom, right, top
static float g_button3_lbrt[4]; // left, bottom, right, top
static float g_button4_lbrt[4]; // left, bottom, right, top
static float g_button5_lbrt[4]; // left, bottom, right, top
static float g_button6_lbrt[4]; // left, bottom, right, top
static float g_button7_lbrt[4]; // left, bottom, right, top
static float g_button8_lbrt[4]; // left, bottom, right, top
static float g_button9_lbrt[4]; // left, bottom, right, top
static float g_button10_lbrt[4]; // left, bottom, right, top
static float g_button11_lbrt[4]; // left, bottom, right, top
static float g_button12_lbrt[4]; // left, bottom, right, top


// char scratch_buffer[150];
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

char * copilot_on = "+";
char * checkmark_off = "    ";
char * checkmark_on = " X ";

int checked [25];

int line_number = 0;

int left, top, right, bottom;

int label_width = 150;


size_t ii;

void				xb2cvr_draw(XPLMWindowID in_window_id, void * in_refcon);
int					xb2cvr_handle_mouse(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon);


// bounds_lbrt  0 left,  1 bottom,  2 right,  3 top
static int	coord_in_rect(float x, float y, float * bounds_lbrt)  { return (((x - 10) >= bounds_lbrt[0]) && ((x - 20) < bounds_lbrt[2]) && (y < bounds_lbrt[3]) && (y >= bounds_lbrt[1])); }


void	xb2cvr_draw(XPLMWindowID xb2cvr_in_window_id, void * in_refcon)
{

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
    XPLMGetWindowGeometry(xb2cvr_in_window_id, &l, &t, &r, &b);


        // Draw the main body of the button window.

        line_number = 1;

        // Find out how big to make the buttons so they always fit on the window



        // Draw the hide button
        // line_number = line_number + 2;
        const char * page1_btn_label = "Page 1";

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_page1_button_lbrt[0] = l;
        g_page1_button_lbrt[3] = t - (line_number * char_height);
        g_page1_button_lbrt[2] = g_page1_button_lbrt[0] + 90; // *just* wide enough to fit the button text
        g_page1_button_lbrt[1] = g_page1_button_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (page_number == 1) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_page1_button_lbrt[0], g_page1_button_lbrt[3]);
            glVertex2i(g_page1_button_lbrt[2], g_page1_button_lbrt[3]);
            glVertex2i(g_page1_button_lbrt[2], g_page1_button_lbrt[1]);
            glVertex2i(g_page1_button_lbrt[0], g_page1_button_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button1 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_page1_button_lbrt[0] = g_page1_button_lbrt[0] + 10;
        XPLMDrawString(col_black, g_page1_button_lbrt[0], g_page1_button_lbrt[1] + 8, (char *)page1_btn_label, NULL, xplmFont_Proportional);


        // Draw the hide button
        // line_number = line_number + 2;
        const char * page2_btn_label = "Page 2";

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_page2_button_lbrt[0] = l + 115;
        g_page2_button_lbrt[3] = t - (line_number * char_height);
        g_page2_button_lbrt[2] = g_page2_button_lbrt[0] + 90; // *just* wide enough to fit the button text
        g_page2_button_lbrt[1] = g_page2_button_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (page_number == 2) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_page2_button_lbrt[0], g_page2_button_lbrt[3]);
            glVertex2i(g_page2_button_lbrt[2], g_page2_button_lbrt[3]);
            glVertex2i(g_page2_button_lbrt[2], g_page2_button_lbrt[1]);
            glVertex2i(g_page2_button_lbrt[0], g_page2_button_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button1 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_page2_button_lbrt[0] = g_page2_button_lbrt[0] + 10;
        XPLMDrawString(col_black, g_page2_button_lbrt[0], g_page2_button_lbrt[1] + 8, (char *)page2_btn_label, NULL, xplmFont_Proportional);


        // Draw the hide button
        // line_number = line_number + 2;
        const char * page3_btn_label = "Page 3";

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_page3_button_lbrt[0] = l + 230;
        g_page3_button_lbrt[3] = t - (line_number * char_height);
        g_page3_button_lbrt[2] = g_page3_button_lbrt[0] + 90; // *just* wide enough to fit the button text
        g_page3_button_lbrt[1] = g_page3_button_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (page_number == 3) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_page3_button_lbrt[0], g_page3_button_lbrt[3]);
            glVertex2i(g_page3_button_lbrt[2], g_page3_button_lbrt[3]);
            glVertex2i(g_page3_button_lbrt[2], g_page3_button_lbrt[1]);
            glVertex2i(g_page3_button_lbrt[0], g_page3_button_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button1 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_page3_button_lbrt[0] = g_page3_button_lbrt[0] + 10;
        XPLMDrawString(col_black, g_page3_button_lbrt[0], g_page3_button_lbrt[1] + 8, (char *)page3_btn_label, NULL, xplmFont_Proportional);


        // Draw the hide button
        // line_number = line_number + 2;
        const char * page4_btn_label = "Page 4";

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_page4_button_lbrt[0] = l + 345;
        g_page4_button_lbrt[3] = t - (line_number * char_height);
        g_page4_button_lbrt[2] = g_page4_button_lbrt[0] + 90; // *just* wide enough to fit the button text
        g_page4_button_lbrt[1] = g_page4_button_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (page_number == 4) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_page4_button_lbrt[0], g_page4_button_lbrt[3]);
            glVertex2i(g_page4_button_lbrt[2], g_page4_button_lbrt[3]);
            glVertex2i(g_page4_button_lbrt[2], g_page4_button_lbrt[1]);
            glVertex2i(g_page4_button_lbrt[0], g_page4_button_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button1 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_page4_button_lbrt[0] = g_page4_button_lbrt[0] + 10;
        XPLMDrawString(col_black, g_page4_button_lbrt[0], g_page4_button_lbrt[1] + 8, (char *)page4_btn_label, NULL, xplmFont_Proportional);


        // Draw the hide button
        // line_number = line_number + 2;
        const char * hide_btn_label = "HIDE";

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_hide_button_lbrt[0] = l + 460;
        g_hide_button_lbrt[3] = t - (line_number * char_height);
        g_hide_button_lbrt[2] = g_hide_button_lbrt[0] + 50; // *just* wide enough to fit the button text
        g_hide_button_lbrt[1] = g_hide_button_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down_hide) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_hide_button_lbrt[0], g_hide_button_lbrt[3]);
            glVertex2i(g_hide_button_lbrt[2], g_hide_button_lbrt[3]);
            glVertex2i(g_hide_button_lbrt[2], g_hide_button_lbrt[1]);
            glVertex2i(g_hide_button_lbrt[0], g_hide_button_lbrt[1]);
        }
        glEnd();


        // Draw the text on the Button1 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_hide_button_lbrt[0] = g_hide_button_lbrt[0] + 10;
        XPLMDrawString(col_black, g_hide_button_lbrt[0], g_hide_button_lbrt[1] + 8, (char *)hide_btn_label, NULL, xplmFont_Proportional);



        // Draw the Button1 button
        line_number = line_number + 6;
        const char * btn1_label;
        if (page_number == 1) {
            btn1_label = page1_button1_label.c_str();
        } else if (page_number == 2) {
            btn1_label = page2_button1_label.c_str();
        } else if (page_number == 3) {
            btn1_label = page3_button1_label.c_str();
        } else if (page_number == 4) {
            btn1_label = page4_button1_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button1_lbrt[0] = l;
        g_button1_lbrt[3] = t - (line_number * char_height);
        g_button1_lbrt[2] = g_button1_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button1_lbrt[1] = g_button1_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[0]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button1_lbrt[0], g_button1_lbrt[3]);
            glVertex2i(g_button1_lbrt[2], g_button1_lbrt[3]);
            glVertex2i(g_button1_lbrt[2], g_button1_lbrt[1]);
            glVertex2i(g_button1_lbrt[0], g_button1_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button1 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button1_lbrt[0] = g_button1_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button1_lbrt[0], g_button1_lbrt[1] + 8, (char *)btn1_label, NULL, xplmFont_Proportional);


        // Draw the Button2 button
        // const char * btn2_label = button2_label.c_str();
        const char * btn2_label;
        if (page_number == 1) {
            btn2_label = page1_button2_label.c_str();
        } else if (page_number == 2) {
            btn2_label = page2_button2_label.c_str();
        } else if (page_number == 3) {
            btn2_label = page3_button2_label.c_str();
        } else if (page_number == 4) {
            btn2_label = page4_button2_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button2_lbrt[0] = l + 180;
        g_button2_lbrt[3] = t - (line_number * char_height);
        g_button2_lbrt[2] = g_button2_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button2_lbrt[1] = g_button2_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[1]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button2_lbrt[0], g_button2_lbrt[3]);
            glVertex2i(g_button2_lbrt[2], g_button2_lbrt[3]);
            glVertex2i(g_button2_lbrt[2], g_button2_lbrt[1]);
            glVertex2i(g_button2_lbrt[0], g_button2_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button2 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button2_lbrt[0] = g_button2_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button2_lbrt[0], g_button2_lbrt[1] + 8, (char *)btn2_label, NULL, xplmFont_Proportional);


        // Draw the Button3 button
        // const char * btn3_label = button3_label.c_str();
        const char * btn3_label;
        if (page_number == 1) {
            btn3_label = page1_button3_label.c_str();
        } else if (page_number == 2) {
            btn3_label = page2_button3_label.c_str();
        } else if (page_number == 3) {
            btn3_label = page3_button3_label.c_str();
        } else if (page_number == 4) {
            btn3_label = page4_button3_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button3_lbrt[0] = l + 360;
        g_button3_lbrt[3] = t - (line_number * char_height);
        g_button3_lbrt[2] = g_button3_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button3_lbrt[1] = g_button3_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[2]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }

        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button3_lbrt[0], g_button3_lbrt[3]);
            glVertex2i(g_button3_lbrt[2], g_button3_lbrt[3]);
            glVertex2i(g_button3_lbrt[2], g_button3_lbrt[1]);
            glVertex2i(g_button3_lbrt[0], g_button3_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button3 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button3_lbrt[0] = g_button3_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button3_lbrt[0], g_button3_lbrt[1] + 8, (char *)btn3_label, NULL, xplmFont_Proportional);


        // Draw the Button4 button
        line_number = line_number + 6;
        // const char * btn4_label = button4_label.c_str();
        const char * btn4_label;
        if (page_number == 1) {
            btn4_label = page1_button4_label.c_str();
        } else if (page_number == 2) {
            btn4_label = page2_button4_label.c_str();
        } else if (page_number == 3) {
            btn4_label = page3_button4_label.c_str();
        } else if (page_number == 4) {
            btn4_label = page4_button4_label.c_str();
        }


        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button4_lbrt[0] = l;
        g_button4_lbrt[3] = t - (line_number * char_height);
        g_button4_lbrt[2] = g_button4_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button4_lbrt[1] = g_button4_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[3]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button4_lbrt[0], g_button4_lbrt[3]);
            glVertex2i(g_button4_lbrt[2], g_button4_lbrt[3]);
            glVertex2i(g_button4_lbrt[2], g_button4_lbrt[1]);
            glVertex2i(g_button4_lbrt[0], g_button4_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button4 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button4_lbrt[0] = g_button4_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button4_lbrt[0], g_button4_lbrt[1] + 8, (char *)btn4_label, NULL, xplmFont_Proportional);


        // Draw the Button5 button
        // const char * btn5_label = button5_label.c_str();
        const char * btn5_label;
        if (page_number == 1) {
            btn5_label = page1_button5_label.c_str();
        } else if (page_number == 2) {
            btn5_label = page2_button5_label.c_str();
        } else if (page_number == 3) {
            btn5_label = page3_button5_label.c_str();
        } else if (page_number == 4) {
            btn5_label = page4_button5_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button5_lbrt[0] = l + 180;
        g_button5_lbrt[3] = t - (line_number * char_height);
        g_button5_lbrt[2] = g_button5_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button5_lbrt[1] = g_button5_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[4]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button5_lbrt[0], g_button5_lbrt[3]);
            glVertex2i(g_button5_lbrt[2], g_button5_lbrt[3]);
            glVertex2i(g_button5_lbrt[2], g_button5_lbrt[1]);
            glVertex2i(g_button5_lbrt[0], g_button5_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button5 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button5_lbrt[0] = g_button5_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button5_lbrt[0], g_button5_lbrt[1] + 8, (char *)btn5_label, NULL, xplmFont_Proportional);


        // Draw the Button6 button
        // const char * previous_btn_label = "Previous";
        // const char * btn6_label = button6_label.c_str();
        const char * btn6_label;
        if (page_number == 1) {
            btn6_label = page1_button6_label.c_str();
        } else if (page_number == 2) {
            btn6_label = page2_button6_label.c_str();
        } else if (page_number == 3) {
            btn6_label = page3_button6_label.c_str();
        } else if (page_number == 4) {
            btn6_label = page4_button6_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button6_lbrt[0] = l + 360;
        g_button6_lbrt[3] = t - (line_number * char_height);
        g_button6_lbrt[2] = g_button6_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button6_lbrt[1] = g_button6_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[5]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button6_lbrt[0], g_button6_lbrt[3]);
            glVertex2i(g_button6_lbrt[2], g_button6_lbrt[3]);
            glVertex2i(g_button6_lbrt[2], g_button6_lbrt[1]);
            glVertex2i(g_button6_lbrt[0], g_button6_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button3 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button6_lbrt[0] = g_button6_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button6_lbrt[0], g_button6_lbrt[1] + 8, (char *)btn6_label, NULL, xplmFont_Proportional);


        // Draw the Button7 button
        line_number = line_number + 6;
        // const char * btn7_label = button7_label.c_str();
        const char * btn7_label;
        if (page_number == 1) {
            btn7_label = page1_button7_label.c_str();
        } else if (page_number == 2) {
            btn7_label = page2_button7_label.c_str();
        } else if (page_number == 3) {
            btn7_label = page3_button7_label.c_str();
        } else if (page_number == 4) {
            btn7_label = page4_button7_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button7_lbrt[0] = l;
        g_button7_lbrt[3] = t - (line_number * char_height);
        g_button7_lbrt[2] = g_button7_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button7_lbrt[1] = g_button7_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[6]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button7_lbrt[0], g_button7_lbrt[3]);
            glVertex2i(g_button7_lbrt[2], g_button7_lbrt[3]);
            glVertex2i(g_button7_lbrt[2], g_button7_lbrt[1]);
            glVertex2i(g_button7_lbrt[0], g_button7_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button7 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button7_lbrt[0] = g_button7_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button7_lbrt[0], g_button7_lbrt[1] + 8, (char *)btn7_label, NULL, xplmFont_Proportional);


        // Draw the Button8 button
        // const char * btn8_label = button8_label.c_str();
        const char * btn8_label;
        if (page_number == 1) {
            btn8_label = page1_button8_label.c_str();
        } else if (page_number == 2) {
            btn8_label = page2_button8_label.c_str();
        } else if (page_number == 3) {
            btn8_label = page3_button8_label.c_str();
        } else if (page_number == 4) {
            btn8_label = page4_button8_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button8_lbrt[0] = l + 180;
        g_button8_lbrt[3] = t - (line_number * char_height);
        g_button8_lbrt[2] = g_button8_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button8_lbrt[1] = g_button8_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[7]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button8_lbrt[0], g_button8_lbrt[3]);
            glVertex2i(g_button8_lbrt[2], g_button8_lbrt[3]);
            glVertex2i(g_button8_lbrt[2], g_button8_lbrt[1]);
            glVertex2i(g_button8_lbrt[0], g_button8_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button8 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button8_lbrt[0] = g_button8_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button8_lbrt[0], g_button8_lbrt[1] + 8, (char *)btn8_label, NULL, xplmFont_Proportional);


        // Draw the Button9 button
        // const char * btn9_label = button9_label.c_str();
        const char * btn9_label;
        if (page_number == 1) {
            btn9_label = page1_button9_label.c_str();
        } else if (page_number == 2) {
            btn9_label = page2_button9_label.c_str();
        } else if (page_number == 3) {
            btn9_label = page3_button9_label.c_str();
        } else if (page_number == 4) {
            btn9_label = page4_button9_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button9_lbrt[0] = l + 360;
        g_button9_lbrt[3] = t - (line_number * char_height);
        g_button9_lbrt[2] = g_button9_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button9_lbrt[1] = g_button9_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[8]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button9_lbrt[0], g_button9_lbrt[3]);
            glVertex2i(g_button9_lbrt[2], g_button9_lbrt[3]);
            glVertex2i(g_button9_lbrt[2], g_button9_lbrt[1]);
            glVertex2i(g_button9_lbrt[0], g_button9_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button9 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button9_lbrt[0] = g_button9_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button9_lbrt[0], g_button9_lbrt[1] + 8, (char *)btn9_label, NULL, xplmFont_Proportional);


        // Draw the Button10 button
        line_number = line_number + 6;
        // const char * btn10_label = button10_label.c_str();
        const char * btn10_label;
        if (page_number == 1) {
            btn10_label = page1_button10_label.c_str();
        } else if (page_number == 2) {
            btn10_label = page2_button10_label.c_str();
        } else if (page_number == 3) {
            btn10_label = page3_button10_label.c_str();
        } else if (page_number == 4) {
            btn10_label = page4_button10_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button10_lbrt[0] = l;
        g_button10_lbrt[3] = t - (line_number * char_height);
        g_button10_lbrt[2] = g_button10_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button10_lbrt[1] = g_button10_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[9]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button10_lbrt[0], g_button10_lbrt[3]);
            glVertex2i(g_button10_lbrt[2], g_button10_lbrt[3]);
            glVertex2i(g_button10_lbrt[2], g_button10_lbrt[1]);
            glVertex2i(g_button10_lbrt[0], g_button10_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button10 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button10_lbrt[0] = g_button10_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button10_lbrt[0], g_button10_lbrt[1] + 8, (char *)btn10_label, NULL, xplmFont_Proportional);


        // Draw the Button11 button
        // const char * btn11_label = button11_label.c_str();
        const char * btn11_label;
        if (page_number == 1) {
            btn11_label = page1_button11_label.c_str();
        } else if (page_number == 2) {
            btn11_label = page2_button11_label.c_str();
        } else if (page_number == 3) {
            btn11_label = page3_button11_label.c_str();
        } else if (page_number == 4) {
            btn11_label = page4_button11_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button11_lbrt[0] = l + 180;
        g_button11_lbrt[3] = t - (line_number * char_height);
        g_button11_lbrt[2] = g_button11_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button11_lbrt[1] = g_button11_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[10]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button11_lbrt[0], g_button11_lbrt[3]);
            glVertex2i(g_button11_lbrt[2], g_button11_lbrt[3]);
            glVertex2i(g_button11_lbrt[2], g_button11_lbrt[1]);
            glVertex2i(g_button11_lbrt[0], g_button11_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button11 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button11_lbrt[0] = g_button11_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button11_lbrt[0], g_button11_lbrt[1] + 8, (char *)btn11_label, NULL, xplmFont_Proportional);


        // Draw the Button12 button
        // const char * btn12_label = button12_label.c_str();
        const char * btn12_label;
        if (page_number == 1) {
            btn12_label = page1_button12_label.c_str();
        } else if (page_number == 2) {
            btn12_label = page2_button12_label.c_str();
        } else if (page_number == 3) {
            btn12_label = page3_button12_label.c_str();
        } else if (page_number == 4) {
            btn12_label = page4_button12_label.c_str();
        }

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button12_lbrt[0] = l + 360;
        g_button12_lbrt[3] = t - (line_number * char_height);
        // g_previous_button_lbrt[2] = g_previous_button_lbrt[0] + XPLMMeasureString(xplmFont_Proportional, previous_btn_label, strlen(previous_btn_label) * 3.5); // *just* wide enough to fit the button text
        g_button12_lbrt[2] = g_button12_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button12_lbrt[1] = g_button12_lbrt[3] - (2.00f * char_height); // a bit taller than the button text

        // Draw the box around our rudimentary button
        if (mouse_down[11]) {
            glColor4fv(light_green);
        }
        else {
           glColor4fv(green);
        }
        glBegin(GL_POLYGON);
        {
            glVertex2i(g_button12_lbrt[0], g_button12_lbrt[3]);
            glVertex2i(g_button12_lbrt[2], g_button12_lbrt[3]);
            glVertex2i(g_button12_lbrt[2], g_button12_lbrt[1]);
            glVertex2i(g_button12_lbrt[0], g_button12_lbrt[1]);
        }
        glEnd();

        // Draw the text on the Button12 button.
        // 0 left, 1 bottom, 2 right, 3 top
        g_button12_lbrt[0] = g_button12_lbrt[0] + 5;
        XPLMDrawString(col_black, g_button12_lbrt[0], g_button12_lbrt[1] + 8, (char *)btn12_label, NULL, xplmFont_Proportional);

}


int	xb2cvr_handle_mouse(XPLMWindowID xb2cvr_in_window_id, int xb2cvr_x, int xb2cvr_y, XPLMMouseStatus xb2cvr_mouse_status, void * in_refcon)
{

    if(xb2cvr_mouse_status == xplm_MouseDown)
    {
        if(!XPLMIsWindowInFront(xb2cvr_in_window_id))
        {
            XPLMBringWindowToFront(xb2cvr_in_window_id);
        }
        else
        {
            if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_hide_button_lbrt)) {
                mouse_down_hide = 1;
                Xbtn2hide_window();
            }



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


            if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button1_lbrt)) {
                mouse_down[0] = 1;
                if (page_number == 1) {
                    XPLMCommandOnce(Page1_Button1CommandOnceCmd);
                    if (Page1_Button2ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button1CommandContinueCmd);
                        Page1_Button1ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    XPLMCommandOnce(Page2_Button1CommandOnceCmd);
                    if (Page2_Button2ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button1CommandContinueCmd);
                        Page2_Button1ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    XPLMCommandOnce(Page3_Button1CommandOnceCmd);
                    if (Page3_Button1ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button1CommandContinueCmd);
                        Page3_Button1ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    XPLMCommandOnce(Page4_Button1CommandOnceCmd);
                    if (Page4_Button1ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button1CommandContinueCmd);
                        Page4_Button1ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button2_lbrt))
            {
                mouse_down[1] = 1;
                if (page_number == 1) {
                    page1_mouse_down[1];
                    XPLMCommandOnce(Page1_Button2CommandOnceCmd);
                    if (Page1_Button2ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button2CommandContinueCmd);
                        Page1_Button2ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[1];
                    XPLMCommandOnce(Page2_Button2CommandOnceCmd);
                    if (Page2_Button2ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button2CommandContinueCmd);
                        Page2_Button2ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[1];
                    XPLMCommandOnce(Page3_Button2CommandOnceCmd);
                    if (Page3_Button2ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button2CommandContinueCmd);
                        Page3_Button2ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[1];
                    XPLMCommandOnce(Page4_Button2CommandOnceCmd);
                    if (Page4_Button2ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button2CommandContinueCmd);
                        Page4_Button2ContinueMode = 1;
                    }
                }
            }





            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button3_lbrt))
            {
                mouse_down[2] = 1;
                if (page_number == 1) {
                    page1_mouse_down[2];
                    XPLMCommandOnce(Page1_Button3CommandOnceCmd);
                    if (Page1_Button3ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button3CommandContinueCmd);
                        Page1_Button3ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[2];
                    XPLMCommandOnce(Page2_Button3CommandOnceCmd);
                    if (Page2_Button3ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button3CommandContinueCmd);
                        Page2_Button3ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[2];
                    XPLMCommandOnce(Page3_Button3CommandOnceCmd);
                    if (Page3_Button3ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button3CommandContinueCmd);
                        Page3_Button3ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                   page4_mouse_down[2];
                    XPLMCommandOnce(Page4_Button3CommandOnceCmd);
                    if (Page4_Button3ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button3CommandContinueCmd);
                        Page4_Button3ContinueMode = 1;
                    }
                }

            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button4_lbrt))
            {
                mouse_down[3] = 1;
                if (page_number == 1) {
                    page1_mouse_down[3];
                    XPLMCommandOnce(Page1_Button4CommandOnceCmd);
                    if (Page1_Button4ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button4CommandContinueCmd);
                        Page1_Button4ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[3];
                    XPLMCommandOnce(Page2_Button4CommandOnceCmd);
                    if (Page2_Button4ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button4CommandContinueCmd);
                        Page2_Button4ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[3];
                    XPLMCommandOnce(Page3_Button4CommandOnceCmd);
                    if (Page3_Button4ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button4CommandContinueCmd);
                        Page3_Button4ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[3];
                    XPLMCommandOnce(Page4_Button4CommandOnceCmd);
                    if (Page4_Button4ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button4CommandContinueCmd);
                        Page4_Button4ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button5_lbrt))
            {
                mouse_down[4] = 1;
                if (page_number == 1) {
                    page1_mouse_down[4];
                    XPLMCommandOnce(Page1_Button5CommandOnceCmd);
                    if (Page1_Button5ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button5CommandContinueCmd);
                        Page1_Button5ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[4];
                    XPLMCommandOnce(Page2_Button5CommandOnceCmd);
                    if (Page2_Button5ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button5CommandContinueCmd);
                        Page2_Button5ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[4];
                    XPLMCommandOnce(Page3_Button5CommandOnceCmd);
                    if (Page3_Button5ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button5CommandContinueCmd);
                        Page3_Button5ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[4];
                    XPLMCommandOnce(Page4_Button5CommandOnceCmd);
                    if (Page4_Button5ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button5CommandContinueCmd);
                        Page4_Button5ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button6_lbrt))
            {
                mouse_down[5] = 1;
                if (page_number == 1) {
                    page1_mouse_down[5];
                    XPLMCommandOnce(Page1_Button6CommandOnceCmd);
                    if (Page1_Button6ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button6CommandContinueCmd);
                        Page1_Button6ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[5];
                    XPLMCommandOnce(Page2_Button6CommandOnceCmd);
                    if (Page2_Button6ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button6CommandContinueCmd);
                        Page2_Button6ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[5];
                    XPLMCommandOnce(Page3_Button6CommandOnceCmd);
                    if (Page3_Button6ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button6CommandContinueCmd);
                        Page3_Button6ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[5];
                    XPLMCommandOnce(Page4_Button6CommandOnceCmd);
                    if (Page4_Button6ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button6CommandContinueCmd);
                        Page4_Button6ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button7_lbrt))
            {
                mouse_down[6] = 1;
                if (page_number == 1) {
                    page1_mouse_down[6];
                    XPLMCommandOnce(Page1_Button7CommandOnceCmd);
                    if (Page1_Button7ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button7CommandContinueCmd);
                        Page1_Button7ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[6];
                    XPLMCommandOnce(Page2_Button7CommandOnceCmd);
                    if (Page2_Button7ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button7CommandContinueCmd);
                        Page2_Button7ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[6];
                    XPLMCommandOnce(Page3_Button7CommandOnceCmd);
                    if (Page3_Button7ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button7CommandContinueCmd);
                        Page3_Button7ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[6];
                    XPLMCommandOnce(Page4_Button7CommandOnceCmd);
                    if (Page4_Button7ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button7CommandContinueCmd);
                        Page4_Button7ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button8_lbrt))
            {
                mouse_down[7] = 1;
                if (page_number == 1) {
                    page1_mouse_down[7];
                    XPLMCommandOnce(Page1_Button8CommandOnceCmd);
                    if (Page1_Button8ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button8CommandContinueCmd);
                        Page1_Button8ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[7];
                    XPLMCommandOnce(Page2_Button8CommandOnceCmd);
                    if (Page2_Button8ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button8CommandContinueCmd);
                        Page2_Button8ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[7];
                    XPLMCommandOnce(Page3_Button8CommandOnceCmd);
                    if (Page3_Button8ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button8CommandContinueCmd);
                        Page3_Button8ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[7];
                    XPLMCommandOnce(Page4_Button8CommandOnceCmd);
                    if (Page4_Button8ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button8CommandContinueCmd);
                        Page4_Button8ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button9_lbrt))
            {
                mouse_down[8] = 1;
                if (page_number == 1) {
                    page1_mouse_down[8];
                    XPLMCommandOnce(Page1_Button9CommandOnceCmd);
                    if (Page1_Button9ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button9CommandContinueCmd);
                        Page1_Button9ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[8];
                    XPLMCommandOnce(Page2_Button9CommandOnceCmd);
                    if (Page2_Button9ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button9CommandContinueCmd);
                        Page2_Button9ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[8];
                    XPLMCommandOnce(Page3_Button9CommandOnceCmd);
                    if (Page3_Button9ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button9CommandContinueCmd);
                        Page3_Button9ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[8];
                    XPLMCommandOnce(Page4_Button9CommandOnceCmd);
                    if (Page4_Button9ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button9CommandContinueCmd);
                        Page4_Button9ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button10_lbrt))
            {
                mouse_down[9] = 1;
                if (page_number == 1) {
                    page1_mouse_down[9];
                    XPLMCommandOnce(Page1_Button10CommandOnceCmd);
                    if (Page1_Button10ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button10CommandContinueCmd);
                        Page1_Button10ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[9];
                    XPLMCommandOnce(Page2_Button10CommandOnceCmd);
                    if (Page2_Button10ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button10CommandContinueCmd);
                        Page2_Button10ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[9];
                    XPLMCommandOnce(Page3_Button10CommandOnceCmd);
                    if (Page3_Button10ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button10CommandContinueCmd);
                        Page3_Button10ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[9];
                    XPLMCommandOnce(Page4_Button10CommandOnceCmd);
                    if (Page4_Button10ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button10CommandContinueCmd);
                        Page4_Button10ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button11_lbrt))
            {
                mouse_down[10] = 1;
                if (page_number == 1) {
                    page1_mouse_down[10];
                    XPLMCommandOnce(Page1_Button11CommandOnceCmd);
                    if (Page1_Button11ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button11CommandContinueCmd);
                        Page1_Button11ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[10];
                    XPLMCommandOnce(Page2_Button11CommandOnceCmd);
                    if (Page2_Button11ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button11CommandContinueCmd);
                        Page2_Button11ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[10];
                    XPLMCommandOnce(Page3_Button11CommandOnceCmd);
                    if (Page3_Button11ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button11CommandContinueCmd);
                        Page3_Button11ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[10];
                    XPLMCommandOnce(Page4_Button11CommandOnceCmd);
                    if (Page4_Button11ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button11CommandContinueCmd);
                        Page4_Button11ContinueMode = 1;
                    }
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button12_lbrt))
            {
                mouse_down[11] = 1;
                if (page_number == 1) {
                    page1_mouse_down[11];
                    XPLMCommandOnce(Page1_Button12CommandOnceCmd);
                    if (Page1_Button12ContinueMode < 1) {
                        XPLMCommandBegin(Page1_Button12CommandContinueCmd);
                        Page1_Button12ContinueMode = 1;
                    }
                } else if (page_number == 2) {
                    page2_mouse_down[10];
                    XPLMCommandOnce(Page2_Button12CommandOnceCmd);
                    if (Page2_Button12ContinueMode < 1) {
                        XPLMCommandBegin(Page2_Button12CommandContinueCmd);
                        Page2_Button12ContinueMode = 1;
                    }
                } else if (page_number == 3) {
                    page3_mouse_down[11];
                    XPLMCommandOnce(Page3_Button12CommandOnceCmd);
                    if (Page3_Button12ContinueMode < 1) {
                        XPLMCommandBegin(Page3_Button12CommandContinueCmd);
                        Page3_Button12ContinueMode = 1;
                    }
                } else if (page_number == 4) {
                    page4_mouse_down[12];
                    XPLMCommandOnce(Page4_Button12CommandOnceCmd);
                    if (Page4_Button12ContinueMode < 1) {
                        XPLMCommandBegin(Page4_Button12CommandContinueCmd);
                        Page4_Button12ContinueMode = 1;
                    }
                }
            }
        }
    }

    if(xb2cvr_mouse_status == xplm_MouseUp)
    {
        mouse_down_hide = 0;
        mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
        mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
        mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
        mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;




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
                Page3_Button2ContinueMode = 0;
            }

            if (Page4_Button3ContinueMode == 1) {
                XPLMCommandEnd(Page4_Button3CommandContinueCmd);
                Page3_Button3ContinueMode = 0;
            }

            if (Page4_Button4ContinueMode == 1) {
                XPLMCommandEnd(Page4_Button4CommandContinueCmd);
                Page4_Button4ContinueMode = 0;
            }

            if (Page4_Button5ContinueMode == 1) {
                XPLMCommandEnd(Page4_Button5CommandContinueCmd);
                Page3_Button5ContinueMode = 0;
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
        }

    }

    return 1;
}
