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

float white[] = {1.0, 1.0, 1.0, 1.0};

char * copilot_on = "+";
char * checkmark_off = "    ";
char * checkmark_on = " X ";

int checked [25];

int line_number = 2;

int left, top, right, bottom;

int label_width = 150;


size_t ii;

void				xb2cvr_draw(XPLMWindowID in_window_id, void * in_refcon);
int					xb2cvr_handle_mouse(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon);


// bounds_lbrt  0 left,  1 bottom,  2 right,  3 top
static int	coord_in_rect(float x, float y, float * bounds_lbrt)  { return (((x - 10) >= bounds_lbrt[0]) && ((x - 20) < bounds_lbrt[2]) && (y < bounds_lbrt[3]) && (y >= bounds_lbrt[1])); }


float current_FPS = 0.0;
float sum_FPS = 0.0;
float average_FPS = 0.0;
int FPS_loop = 0;

int mouse_down[12] = {};


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


        // Draw the main body of the checklist window.


        line_number = 1;


        // Display whether we're in front of our our layer
        {
            sprintf(scratch_buffer, "In front? %s", XPLMIsWindowInFront(xb2cvr_in_window_id) ? "Y" : "N");
            XPLMDrawString(col_white, l, t - line_number * char_height, scratch_buffer, NULL, xplmFont_Proportional);
        }

        // Display Average FPS if in VR
        {
            if (vr_is_enabled) {
                current_FPS = 1/(XPLMGetDataf(xb2cvr_g_FPS));
                sum_FPS = sum_FPS + current_FPS;
                FPS_loop = FPS_loop + 1;
                if (FPS_loop == 15) {
                    average_FPS = sum_FPS / 15;
                    FPS_loop = 0;
                    sum_FPS = 0;
                }
                sprintf(scratch_buffer, "FPS  %3.2f", average_FPS);
                XPLMDrawString(col_white, l + 70, t - line_number * char_height, scratch_buffer, NULL, xplmFont_Proportional);
            }
        }


        // Find out how big to make the buttons so they always fit on the window

        // Draw the Button1 button
        line_number = line_number + 2;
        const char * btn1_label = button1_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button1_lbrt[0] = l;
        g_button1_lbrt[3] = t - (line_number * char_height);
        g_button1_lbrt[2] = g_button1_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button1_lbrt[1] = g_button1_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button1_lbrt[0], g_button1_lbrt[1] + 12, (char *)btn1_label, NULL, xplmFont_Proportional);


        // Draw the Button2 button
        const char * btn2_label = button2_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button2_lbrt[0] = l + 180;
        g_button2_lbrt[3] = t - (line_number * char_height);
        g_button2_lbrt[2] = g_button2_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button2_lbrt[1] = g_button2_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button2_lbrt[0], g_button2_lbrt[1] + 12, (char *)btn2_label, NULL, xplmFont_Proportional);


        // Draw the Button3 button
        const char * btn3_label = button3_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button3_lbrt[0] = l + 360;
        g_button3_lbrt[3] = t - (line_number * char_height);
        g_button3_lbrt[2] = g_button3_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button3_lbrt[1] = g_button3_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button3_lbrt[0], g_button3_lbrt[1] + 12, (char *)btn3_label, NULL, xplmFont_Proportional);


        // Draw the Button4 button
        line_number = line_number + 6;
        const char * btn4_label = button4_label.c_str();


        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button4_lbrt[0] = l;
        g_button4_lbrt[3] = t - (line_number * char_height);
        g_button4_lbrt[2] = g_button4_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button4_lbrt[1] = g_button4_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button4_lbrt[0], g_button4_lbrt[1] + 12, (char *)btn4_label, NULL, xplmFont_Proportional);


        // Draw the Button5 button
        const char * btn5_label = button5_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button5_lbrt[0] = l + 180;
        g_button5_lbrt[3] = t - (line_number * char_height);
        g_button5_lbrt[2] = g_button5_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button5_lbrt[1] = g_button5_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button5_lbrt[0], g_button5_lbrt[1] + 12, (char *)btn5_label, NULL, xplmFont_Proportional);


        // Draw the Button6 button
        // const char * previous_btn_label = "Previous";
        const char * btn6_label = button6_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button6_lbrt[0] = l + 360;
        g_button6_lbrt[3] = t - (line_number * char_height);
        g_button6_lbrt[2] = g_button6_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button6_lbrt[1] = g_button6_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button6_lbrt[0], g_button6_lbrt[1] + 12, (char *)btn6_label, NULL, xplmFont_Proportional);


        // Draw the Button7 button
        line_number = line_number + 6;
        const char * btn7_label = button7_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button7_lbrt[0] = l;
        g_button7_lbrt[3] = t - (line_number * char_height);
        g_button7_lbrt[2] = g_button7_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button7_lbrt[1] = g_button7_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button7_lbrt[0], g_button7_lbrt[1] + 12, (char *)btn7_label, NULL, xplmFont_Proportional);


        // Draw the Button8 button
        const char * btn8_label = button8_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button8_lbrt[0] = l + 180;
        g_button8_lbrt[3] = t - (line_number * char_height);
        g_button8_lbrt[2] = g_button8_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button8_lbrt[1] = g_button8_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button8_lbrt[0], g_button8_lbrt[1] + 12, (char *)btn8_label, NULL, xplmFont_Proportional);


        // Draw the Button9 button
        const char * btn9_label = button9_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button9_lbrt[0] = l + 360;
        g_button9_lbrt[3] = t - (line_number * char_height);
        g_button9_lbrt[2] = g_button9_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button9_lbrt[1] = g_button9_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button9_lbrt[0], g_button9_lbrt[1] + 12, (char *)btn9_label, NULL, xplmFont_Proportional);


        // Draw the Button10 button
        line_number = line_number + 6;
        const char * btn10_label = button10_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button10_lbrt[0] = l;
        g_button10_lbrt[3] = t - (line_number * char_height);
        g_button10_lbrt[2] = g_button10_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button10_lbrt[1] = g_button10_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button10_lbrt[0], g_button10_lbrt[1] + 12, (char *)btn10_label, NULL, xplmFont_Proportional);


        // Draw the Button11 button
        const char * btn11_label = button11_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button11_lbrt[0] = l + 180;
        g_button11_lbrt[3] = t - (line_number * char_height);
        g_button11_lbrt[2] = g_button11_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button11_lbrt[1] = g_button11_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button11_lbrt[0], g_button11_lbrt[1] + 12, (char *)btn11_label, NULL, xplmFont_Proportional);


        // Draw the Button12 button
        const char * btn12_label = button12_label.c_str();

        // 0 left, 1 bottom, 2 right, 3 top
        // Position the button in the upper left of the window (sized to fit the button text)
        g_button12_lbrt[0] = l + 360;
        g_button12_lbrt[3] = t - (line_number * char_height);
        // g_previous_button_lbrt[2] = g_previous_button_lbrt[0] + XPLMMeasureString(xplmFont_Proportional, previous_btn_label, strlen(previous_btn_label) * 3.5); // *just* wide enough to fit the button text
        g_button12_lbrt[2] = g_button12_lbrt[0] + label_width; // *just* wide enough to fit the button text
        g_button12_lbrt[1] = g_button12_lbrt[3] - (3.00f * char_height); // a bit taller than the button text

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
        XPLMDrawString(col_black, g_button12_lbrt[0], g_button12_lbrt[1] + 12, (char *)btn12_label, NULL, xplmFont_Proportional);


        // Draw a bunch of informative text
            {


                // Set the y position for the first bunch of text we'll draw to a little below the buttons
                int y = g_button12_lbrt[1] - 2 * char_height;
                left = l;

                // Display the total global desktop bounds
                {
                    int global_desktop_lbrt[4];
                    XPLMGetScreenBoundsGlobal(&global_desktop_lbrt[0], &global_desktop_lbrt[3], &global_desktop_lbrt[2], &global_desktop_lbrt[1]);
                    sprintf(scratch_buffer, "Global desktop bounds: (%d, %d) to (%d, %d)", global_desktop_lbrt[0], global_desktop_lbrt[1], global_desktop_lbrt[2], global_desktop_lbrt[3]);
                    XPLMDrawString(col_white, left, y, scratch_buffer, NULL, xplmFont_Proportional);
                    y -= 1.5 * char_height;
                }

                // Display our bounds
                if(XPLMWindowIsPoppedOut(xb2cvr_in_window_id)) // we are in our own first-class window, rather than "floating" within X-Plane's own window
                {
                    int window_os_bounds[4];
                    XPLMGetWindowGeometryOS(xb2cvr_in_window_id, &window_os_bounds[0], &window_os_bounds[3], &window_os_bounds[2], &window_os_bounds[1]);
                    sprintf(scratch_buffer, "OS Bounds: (%d, %d) to (%d, %d)", window_os_bounds[0], window_os_bounds[1], window_os_bounds[2], window_os_bounds[3]);
                    XPLMDrawString(col_white, left, y, scratch_buffer, NULL, xplmFont_Proportional);
                    y -= 1.5 * char_height;
                }
                else
                {
                    int global_bounds[4];
                    XPLMGetWindowGeometry(xb2cvr_in_window_id, &global_bounds[0], &global_bounds[3], &global_bounds[2], &global_bounds[1]);
                    sprintf(scratch_buffer, "Window bounds: %d %d %d %d", global_bounds[0], global_bounds[1], global_bounds[2], global_bounds[3]);
                    XPLMDrawString(col_white, left, y, scratch_buffer, NULL, xplmFont_Proportional);
                    y -= 1.5 * char_height;
                }


                // Display the mouse's position info text
                {
                    int mouse_global_x, mouse_global_y;
                    XPLMGetMouseLocationGlobal(&mouse_global_x, &mouse_global_y);
                    sprintf(scratch_buffer, "Draw mouse (global): %d %d\n", mouse_global_x, mouse_global_y);
                    XPLMDrawString(col_white, left, y, scratch_buffer, NULL, xplmFont_Proportional);
                    y -= 1.5 * char_height;
                }

                // Display the mouse's window position info text
                {
                    // int mouse_window_x, mouse_window_y;
                    // dummy_cursor_status_handler(XPLMWindowID g_window, mouse_window_x, mouse_window_y, void * in_refcon);
                    // XPLMCursorStatus dummy_cursor_status_handler(XPLMWindowID in_window_id, mouse_window_x, mouse_window_y, void * in_refcon);
                    // sprintf(scratch_buffer, "Draw mouse (window): %d %d\n", mouse_window_x, mouse_window_y);
                    // XPLMDrawString(col_white, left, y, scratch_buffer, NULL, xplmFont_Proportional);
                    // y -= 1.5 * char_height;
                }


            }
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

            if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button1_lbrt)) {
                mouse_down[0] = 1;
                XPLMCommandOnce(Button1CommandOnceCmd);
                if (Button1ContinueMode < 1) {
                    XPLMCommandBegin(Button1CommandContinueCmd);
                    Button1ContinueMode = 1;
                }

            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button2_lbrt))
            {
                mouse_down[1] = 1;
                XPLMCommandOnce(Button2CommandOnceCmd);
                if (Button2ContinueMode < 1) {
                    XPLMCommandBegin(Button2CommandContinueCmd);
                    Button2ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button3_lbrt))
            {
                mouse_down[2] = 1;
                XPLMCommandOnce(Button3CommandOnceCmd);
                if (Button3ContinueMode < 1) {
                    XPLMCommandBegin(Button3CommandContinueCmd);
                    Button3ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button4_lbrt))
            {
                mouse_down[3] = 1;
                XPLMCommandOnce(Button4CommandOnceCmd);
                if (Button4ContinueMode < 1) {
                    XPLMCommandBegin(Button4CommandContinueCmd);
                    Button4ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button5_lbrt))
            {
                mouse_down[4] = 1;
                XPLMCommandOnce(Button5CommandOnceCmd);
                if (Button5ContinueMode < 1) {
                    XPLMCommandBegin(Button5CommandContinueCmd);
                    Button5ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button6_lbrt))
            {
                mouse_down[5] = 1;
                XPLMCommandOnce(Button6CommandOnceCmd);
                if (Button6ContinueMode < 1) {
                    XPLMCommandBegin(Button6CommandContinueCmd);
                    Button6ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button7_lbrt))
            {
                mouse_down[6] = 1;
                XPLMCommandOnce(Button7CommandOnceCmd);
                if (Button7ContinueMode < 1) {
                    XPLMCommandBegin(Button7CommandContinueCmd);
                    Button7ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button8_lbrt))
            {
                mouse_down[7] = 1;
                XPLMCommandOnce(Button8CommandOnceCmd);
                if (Button8ContinueMode < 1) {
                    XPLMCommandBegin(Button8CommandContinueCmd);
                    Button8ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button9_lbrt))
            {
                mouse_down[8] = 1;
                XPLMCommandOnce(Button9CommandOnceCmd);
                if (Button9ContinueMode < 1) {
                    XPLMCommandBegin(Button9CommandContinueCmd);
                    Button9ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button10_lbrt))
            {
                mouse_down[9] = 1;
                XPLMCommandOnce(Button10CommandOnceCmd);
                if (Button10ContinueMode < 1) {
                    XPLMCommandBegin(Button10CommandContinueCmd);
                    Button10ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button11_lbrt))
            {
                mouse_down[10] = 1;
                XPLMCommandOnce(Button11CommandOnceCmd);
                if (Button11ContinueMode < 1) {
                    XPLMCommandBegin(Button11CommandContinueCmd);
                    Button11ContinueMode = 1;
                }
            }


            else if (coord_in_rect(xb2cvr_x, xb2cvr_y, g_button12_lbrt))
            {
                mouse_down[11] = 1;
                XPLMCommandOnce(Button12CommandOnceCmd);
                if (Button12ContinueMode < 1) {
                    XPLMCommandBegin(Button12CommandContinueCmd);
                    Button12ContinueMode = 1;
                }
            }

        }

    }

    if(xb2cvr_mouse_status == xplm_MouseUp)
    {

        mouse_down[0] = 0, mouse_down[1] = 0, mouse_down[2] = 0;
        mouse_down[3] = 0, mouse_down[4] = 0, mouse_down[5] = 0;
        mouse_down[6] = 0, mouse_down[7] = 0, mouse_down[8] = 0;
        mouse_down[9] = 0, mouse_down[10] = 0, mouse_down[11] = 0;

        if (Button1ContinueMode == 1) {
            XPLMCommandEnd(Button1CommandContinueCmd);
            Button1ContinueMode = 0;
        }

        if (Button2ContinueMode == 1) {
            XPLMCommandEnd(Button2CommandContinueCmd);
            Button2ContinueMode = 0;
        }

        if (Button3ContinueMode == 1) {
            XPLMCommandEnd(Button3CommandContinueCmd);
            Button3ContinueMode = 0;
        }

        if (Button4ContinueMode == 1) {
            XPLMCommandEnd(Button4CommandContinueCmd);
            Button4ContinueMode = 0;
        }

        if (Button5ContinueMode == 1) {
            XPLMCommandEnd(Button5CommandContinueCmd);
            Button5ContinueMode = 0;
        }

        if (Button6ContinueMode == 1) {
            XPLMCommandEnd(Button6CommandContinueCmd);
            Button6ContinueMode = 0;
        }

        if (Button7ContinueMode == 1) {
            XPLMCommandEnd(Button7CommandContinueCmd);
            Button7ContinueMode = 0;
        }

        if (Button8ContinueMode == 1) {
            XPLMCommandEnd(Button8CommandContinueCmd);
            Button8ContinueMode = 0;
        }

        if (Button9ContinueMode == 1) {
            XPLMCommandEnd(Button9CommandContinueCmd);
            Button9ContinueMode = 0;
        }

        if (Button10ContinueMode == 1) {
            XPLMCommandEnd(Button10CommandContinueCmd);
            Button10ContinueMode = 0;
        }

        if (Button11ContinueMode == 1) {
            XPLMCommandEnd(Button11CommandContinueCmd);
            Button11ContinueMode = 0;
        }

        if (Button12ContinueMode == 1) {
            XPLMCommandEnd(Button12CommandContinueCmd);
            Button12ContinueMode = 0;
        }
    }

    return 1;
}
