#ifndef VERTICES_H
#define VERTICES_H

#define GLFW_INCLUDE_NONE
//#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "colors.h"
#include "shaders.h"
#include "shader_utils.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include "stb_image.h"

void makeTexture();


bool symn_engaged = false;
bool symn_hover = false;
bool symn_click = false;

bool preset1_hover = false;
bool preset2_hover = false;
bool preset3_hover = false;
bool preset4_hover = false;
bool preset5_hover = false;
bool preset6_hover = false;
bool preset7_hover = false;
bool preset8_hover = false;
bool preset9_hover = false;
bool preset10_hover = false;
bool preset1_click = false;
bool preset2_click = false;
bool preset3_click = false;
bool preset4_click = false;
bool preset5_click = false;
bool preset6_click = false;
bool preset7_click = false;
bool preset8_click = false;
bool preset9_click = false;
bool preset10_click = false;

bool wfm1_hover = false;
bool wfm2_hover = false;
bool wfm3_hover = false;
bool wfm1_click = false;
bool wfm2_click = false;
bool wfm3_click = false;
bool wfm1_engaged = false;
bool wfm2_engaged = false;
bool wfm3_engaged = false;

bool wfm1preset1_hover = false;
bool wfm1preset2_hover = false;
bool wfm1preset3_hover = false;
bool wfm1preset4_hover = false;
bool wfm1preset5_hover = false;
bool wfm1preset6_hover = false;
bool wfm1preset7_hover = false;
bool wfm1preset1_click = false;
bool wfm1preset2_click = false;
bool wfm1preset3_click = false;
bool wfm1preset4_click = false;
bool wfm1preset5_click = false;
bool wfm1preset6_click = false;
bool wfm1preset7_click = false;

bool wfm2preset1_hover = false;
bool wfm2preset2_hover = false;
bool wfm2preset3_hover = false;
bool wfm2preset4_hover = false;
bool wfm2preset5_hover = false;
bool wfm2preset6_hover = false;
bool wfm2preset7_hover = false;
bool wfm2preset1_click = false;
bool wfm2preset2_click = false;
bool wfm2preset3_click = false;
bool wfm2preset4_click = false;
bool wfm2preset5_click = false;
bool wfm2preset6_click = false;
bool wfm2preset7_click = false;

bool wfm3preset1_hover = false;
bool wfm3preset2_hover = false;
bool wfm3preset3_hover = false;
bool wfm3preset4_hover = false;
bool wfm3preset5_hover = false;
bool wfm3preset6_hover = false;
bool wfm3preset7_hover = false;
bool wfm3preset1_click = false;
bool wfm3preset2_click = false;
bool wfm3preset3_click = false;
bool wfm3preset4_click = false;
bool wfm3preset5_click = false;
bool wfm3preset6_click = false;
bool wfm3preset7_click = false;

bool env1 = false;
bool env2 = false;
bool env3 = false;
bool x_click = false;
bool z_click = false;
bool x_hover = false;
bool z_hover = false;

bool atk1slider_hold = false;
bool dec1slider_hold = false;
bool rel1slider_hold = false;
bool atk2slider_hold = false;
bool dec2slider_hold = false;
bool rel2slider_hold = false;
bool atk3slider_hold = false;
bool dec3slider_hold = false;
bool rel3slider_hold = false;
bool debug = false;

bool atk1Top_click = false;
bool dec1Top_click = false;
bool sus1Top_click = false;
bool rel1Top_click = false;
bool atk1Btm_click = false;
bool dec1Btm_click = false;
bool sus1Btm_click = false;
bool rel1Btm_click = false;

bool atk2Top_click = false;
bool dec2Top_click = false;
bool sus2Top_click = false;
bool rel2Top_click = false;
bool atk2Btm_click = false;
bool dec2Btm_click = false;
bool sus2Btm_click = false;
bool rel2Btm_click = false;

bool atk3Top_click = false;
bool dec3Top_click = false;
bool sus3Top_click = false;
bool rel3Top_click = false;
bool atk3Btm_click = false;
bool dec3Btm_click = false;
bool sus3Btm_click = false;
bool rel3Btm_click = false;

bool osc1on_click = false;
bool osc2on_click = false;
bool osc3on_click = false;

//sliders
float atk1Mod = 0.0f;
float dec1Mod = 0.0f;
float sus1Mod = 0.0f;
float rel1Mod = 0.0f;
float atk2Mod = 0.0f;
float dec2Mod = 0.0f;
float sus2Mod = 0.0f;
float rel2Mod = 0.0f;
float atk3Mod = 0.0f;
float dec3Mod = 0.0f;
float sus3Mod = 0.0f;
float rel3Mod = 0.0f;

//screen
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 600;
unsigned int window_width = SCR_WIDTH;
unsigned int window_height = SCR_HEIGHT;
unsigned int ww = window_width / SCR_WIDTH;
unsigned int wh = window_height / SCR_HEIGHT;

// offset constants
float offset = 0.667f;
float q = 0.0025f;

// coordinates in TBLR
float wave[12] = { 0.870f, 0.770f, 0.100f + q - offset, 0.200f - q - offset,
                   0.870f, 0.770f, 0.100f + q,          0.200f - q,
                   0.870f, 0.770f, 0.100f + q + offset, 0.200f - q + offset };
float env[12] = { 0.870f, 0.770f,  0.200f + q - offset, 0.300f - q - offset,
                  0.870f, 0.770f,  0.200f + q, 0.300f - q,
                  0.870f, 0.770f,  0.200f + q + offset, 0.300f - q + offset };
float waveSelect[12] = { 0.220f - q, 0.125f + q, -0.260f + q - offset, -0.050f - q - offset,
                         0.220f - q, 0.125f + q, -0.260f + q, -0.050f - q,
                         0.220f - q, 0.125f + q, -0.260f + q + offset, -0.050f - q + offset };
float waveSelectDdn[12] = { 0.125f + q, -0.775f + q, -0.260f + q - offset, -0.050f - q - offset,
                            0.125f + q, -0.775f + q, -0.260f + q, -0.050f - q,
                            0.125f + q, -0.775f + q, -0.260f + q + offset, -0.050f - q + offset };
float synthMenu[4] = { 0.990f, 0.875f, -0.967f, -0.667f };
float synthMenuDdn[4] = { 0.875f, -0.8f, -0.967f, -0.555f };

float smq = (synthMenuDdn[0] - synthMenuDdn[1]) / 10;  //0.875 to -0.8
float wsmq = (waveSelectDdn[0] - waveSelectDdn[1]) / 7;


float vertices[] = {
    //point             //color
    //TOP MENU:
    -0.995f, 0.99f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],     //0  top left
    -0.995f, 0.875f, 0.0f,  funeralGrey[0], funeralGrey[1], funeralGrey[2],     //1  bottom left
     0.995f, 0.99f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],     //2  top right
     0.995f, 0.875f, 0.0f,  funeralGrey[0], funeralGrey[1], funeralGrey[2],     //3  bottom right

     //OSCILLATOR LEFT:                                                              
    -0.995f, 0.870f, 0.0f,  funeralGrey[0], funeralGrey[1], funeralGrey[2],     //4  top left
    -0.995f, -0.02f, 0.0f,  glowGrey[0], glowGrey[1], glowGrey[2],              //5  bottom left
    -0.3355f, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],     //6  top right
    -0.3355f, -0.02f, 0.0f, glowGrey[0], glowGrey[1], glowGrey[2],              //7  bottom right
    //OSCILLATOR MIDDLE:                                                            
   -0.3305f, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],     //8  top left
   -0.3305f, -0.02f, 0.0f, glowGrey[0], glowGrey[1], glowGrey[2],              //9  bottom left
    0.3305f, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],     //10 top right
    0.3305f, -0.02f, 0.0f, glowGrey[0], glowGrey[1], glowGrey[2],              //11 bottom right
    //OSCILLATOR RIGHT:                                                            
    0.3355f, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],     //12 top left
    0.3355f, -0.02f, 0.0f, glowGrey[0], glowGrey[1], glowGrey[2],              //13 bottom left
    0.995f, 0.870f, 0.0f,  funeralGrey[0], funeralGrey[1], funeralGrey[2],     //14 top right
    0.995f, -0.02f, 0.0f,  glowGrey[0], glowGrey[1], glowGrey[2],              //15 bottom right

    //PIANO BACK:
   -0.995f, -0.025, 0.0f,  southGrey[0], southGrey[1], southGrey[2],           //16 top left
   -0.995f, -0.995f, 0.0f, glowOrange[0], glowOrange[1], glowOrange[2],        //17 bottom left
    0.995f, -0.025, 0.0f,  southGrey[0], southGrey[1], southGrey[2],           //18 top right
    0.995f, -0.995f, 0.0f, glowOrange[0], glowOrange[1], glowOrange[2],        //19 bottom right

    //OSCILLATOR 1 ORANGEBOX
   -0.3000f - offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 20 top left
   -0.3000f - offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 21 bottom left
    0.3000f - offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 22 top right
    0.3000f - offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 23 bottom right
    //OSCILLATOR 2 ORANGEBOX
   -0.3000f, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 24 top left
   -0.3000f, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 25 bottom left
    0.3000f, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 26 top right
    0.3000f, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 27 bottom right
    //OSCILLATOR 3 ORANGEBOX
   -0.3000f + offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 28 top left
   -0.3000f + offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 29 bottom left
    0.3000f + offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 30 top right
    0.3000f + offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 31 bottom right

    //OSCILLATOR 1 GREYBOX
   -0.3000f + q - offset, 0.770f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 32 top left
   -0.3000f + q - offset, 0.250f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 33 bottom left
    0.3000f - q - offset, 0.770f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 34 top right
    0.3000f - q - offset, 0.250f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 35 bottom right
    //OSCILLATOR 2 GREYBOX
    -0.3000f + q, 0.770f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 36 top left
    -0.3000f + q, 0.250f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 37 bottom left
     0.3000f - q, 0.770f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 38 top right
     0.3000f - q, 0.250f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 39 bottom right
     //OSCILLATOR 3 GREYBOX
     -0.3000f + q + offset, 0.770f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 40 top left
     -0.3000f + q + offset, 0.250f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 41 bottom left
      0.3000f - q + offset, 0.770f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 42 top right
      0.3000f - q + offset, 0.250f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],  // 43 bottom right

      //SYNTH SELECTOR MENU ORANGEBOX
     -0.967f, 0.990f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 44 top left
     -0.967f, 0.875f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 45 bottom left
     -0.667f, 0.990f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 46 top right
     -0.667f, 0.875f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],  // 47 bottom right
     //SYNTH SELECTOR MENU
    -0.967f + q, 0.990f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],  // 48 top left
    -0.967f + q, 0.875f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],  // 49 bottom left
    -0.667f - q, 0.990f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],  // 50 top right
    -0.667f - q, 0.875f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],  // 51 bottom right

    //UI ORANGEBOX 1
    -0.3000f - offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.3000f - offset, 0.0f, 0.0f,   pocketOrange[0], pocketOrange[1], pocketOrange[2],
     0.3000f - offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
     0.3000f - offset, 0.0f, 0.0f,   pocketOrange[0], pocketOrange[1], pocketOrange[2],
     //UI ORANGEBOX 2
    -0.3000f, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.3000f, 0.0f, 0.0f,   pocketOrange[0], pocketOrange[1], pocketOrange[2],
     0.3000f, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
     0.3000f, 0.0f, 0.0f,   pocketOrange[0], pocketOrange[1], pocketOrange[2],
     //UI ORANGEBOX 3
    -0.3000f + offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.3000f + offset, 0.0f, 0.0f,   pocketOrange[0], pocketOrange[1], pocketOrange[2],
     0.3000f + offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
     0.3000f + offset, 0.0f, 0.0f,   pocketOrange[0], pocketOrange[1], pocketOrange[2],

     //UI GREYBOX 1
    -0.3000f - offset + q, 0.250f - q, 0.0f, southGrey[0], southGrey[1], southGrey[2],
    -0.3000f - offset + q, 0.0f + q,   0.0f, southGrey[0], southGrey[1], southGrey[2],
     0.3000f - offset - q, 0.250f - q, 0.0f, southGrey[0], southGrey[1], southGrey[2],
     0.3000f - offset - q, 0.0f + q,   0.0f, southGrey[0], southGrey[1], southGrey[2],
     //UI GREYBOX 1
    -0.3000f + q, 0.250f - q, 0.0f, southGrey[0], southGrey[1], southGrey[2],
    -0.3000f + q, 0.0f + q,   0.0f, southGrey[0], southGrey[1], southGrey[2],
     0.3000f - q, 0.250f - q, 0.0f, southGrey[0], southGrey[1], southGrey[2],
     0.3000f - q, 0.0f + q,   0.0f, southGrey[0], southGrey[1], southGrey[2],
     //UI GREYBOX 1
    -0.3000f + offset + q, 0.250f - q, 0.0f, southGrey[0], southGrey[1], southGrey[2],
    -0.3000f + offset + q, 0.0f + q,   0.0f, southGrey[0], southGrey[1], southGrey[2],
     0.3000f + offset - q, 0.250f - q, 0.0f, southGrey[0], southGrey[1], southGrey[2],
     0.3000f + offset - q, 0.0f + q,   0.0f, southGrey[0], southGrey[1], southGrey[2],

     //OSC NAME GREYBOX1
     -0.3000f + q - offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2], //100
     -0.3000f + q - offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
     -0.075f - q - offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
     -0.075f - q - offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
     //OSC NAME GREYBOX2
    -0.3000f + q, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
    -0.3000f + q, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
    -0.075f - q, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
    -0.075f - q, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
    //OSC NAME GREYBOX3
   -0.3000f + q + offset, 0.870f - q, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   -0.3000f + q + offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   -0.075f - q + offset, 0.870f - q, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   -0.075f - q + offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],

   //OSC WAVE GREYBOX1
   0.100f + q - offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.100f + q - offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f - q - offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f - q - offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   //OSC WAVE GREYBOX2
   0.100f + q, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.100f + q, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f - q, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f - q, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   //OSC WAVE GREYBOX3
   0.100f + q + offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.100f + q + offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f - q + offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f - q + offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],

   //OSC ENV GREYBOX1
   0.200f + q - offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f + q - offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.300f - q - offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.300f - q - offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   //OSC ENV GREYBOX2
   0.200f + q, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f + q, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.300f - q, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.300f - q, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   //OSC ENV GREYBOX3
   0.200f + q + offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.200f + q + offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.300f - q + offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.300f - q + offset, 0.770f, 0.0f,   funeralGrey[0], funeralGrey[1], funeralGrey[2],

   //PIANO BLACKBOX
  -0.260f - offset, -0.175f,     0.0f, 0.0f, 0.0f, 0.0f,
  -0.260f - offset, -1.0f + q,     0.0f, 0.0f, 0.0f, 0.0f,
   0.260f + offset, -0.175f,     0.0f, 0.0f, 0.0f, 0.0f,
   0.260f + offset, -1.0f + q,     0.0f, 0.0f, 0.0f, 0.0f,

   //PIANO GREYBOX
  -0.260f - offset + q, -0.175f - q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],
  -0.260f - offset + q, -1.0f + q, 0.0f, iceGrey[0], iceGrey[1], iceGrey[2],
   0.260f + offset - q, -0.175f - q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],
   0.260f + offset - q, -1.0f + q, 0.0f, iceGrey[0], iceGrey[1], iceGrey[2],

   //WHITE KEYS...144
  -0.1236 * 7 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 7 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
  -0.1236 * 6 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 6 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

  -0.1236 * 6 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 6 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
  -0.1236 * 5 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 5 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

  -0.1236 * 5 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 5 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
  -0.1236 * 4 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 4 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

  -0.1236 * 4 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 4 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
  -0.1236 * 3 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 3 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

  -0.1236 * 3 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 3 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
  -0.1236 * 2 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 2 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

  -0.1236 * 2 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 * 2 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
  -0.1236 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

  -0.1236 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
  -0.1236 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
   0 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

   0 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
   0.1236 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

   0.1236 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
   0.1236 * 2 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 2 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

   0.1236 * 2 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 2 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
   0.1236 * 3 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 3 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

   0.1236 * 3 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 3 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
   0.1236 * 4 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 4 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

   0.1236 * 4 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 4 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
   0.1236 * 5 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 5 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

   0.1236 * 5 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 5 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
   0.1236 * 6 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 6 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

   0.1236 * 6 + q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 6 + q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],
   0.1236 * 7 - q, -0.225, 0.0f, pianoGrey[0], pianoGrey[1], pianoGrey[2],
   0.1236 * 7 - q, -1.0 + q, 0.0f, pianoWhite[0], pianoWhite[1], pianoWhite[2],

   //BLACK KEYS...204
  -0.1236 * 6 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 6 + 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],
  -0.1236 * 6 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 6 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

  -0.1236 * 5 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 5 + 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1] + .01, coolGrey[2] + .02,
  -0.1236 * 5 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 5 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

  -0.1236 * 4 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 4 + 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1] + .01, coolGrey[2] + .02,
  -0.1236 * 4 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 4 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

  -0.1236 * 2 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 2 + 0.04944, -0.645 + q, 0.0f, coolGrey[0] + .01, coolGrey[1] + .02, coolGrey[2] + .03,
  -0.1236 * 2 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 2 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

  -0.1236 * 1 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 1 + 0.04944, -0.645 + q, 0.0f, coolGrey[0] + .01, coolGrey[1] + .02, coolGrey[2] + .03,
  -0.1236 * 1 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
  -0.1236 * 1 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

   0.1236 * 1 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 1 + 0.04944, -0.645 + q, 0.0f, coolGrey[0] + .01, coolGrey[1] + .02, coolGrey[2] + .03,
   0.1236 * 1 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 1 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

   0.1236 * 2 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 2 + 0.04944, -0.645 + q, 0.0f, coolGrey[0] + .02, coolGrey[1] + .03, coolGrey[2] + .04,
   0.1236 * 2 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 2 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

   0.1236 * 3 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 3 + 0.04944, -0.645 + q, 0.0f, coolGrey[0] + .02, coolGrey[1] + .03, coolGrey[2] + .04,
   0.1236 * 3 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 3 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

   0.1236 * 5 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 5 + 0.04944, -0.645 + q, 0.0f, coolGrey[0] + .02, coolGrey[1] + .03, coolGrey[2] + .04,
   0.1236 * 5 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 5 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

   0.1236 * 6 + 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 6 + 0.04944, -0.645 + q, 0.0f, coolGrey[0] + .02, coolGrey[1] + .03, coolGrey[2] + .04,
   0.1236 * 6 - 0.04944, -0.225, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
   0.1236 * 6 - 0.04944, -0.645 + q, 0.0f, coolGrey[0], coolGrey[1], coolGrey[2],

};
const unsigned int indices[] = {
    0, 1, 2,    // TOP MENU
    1, 2, 3,
    4, 5, 6,    // OSC LEFT
    5, 6, 7,
    8, 9, 10,   // OSC MIDL
    9, 10, 11,
    12, 13, 14, // OSC RIGH
    13, 14, 15,
    16, 17, 18, // PIA BACK
    17, 18, 19,
    20, 21, 22, // OSC 1ORANG
    21, 22, 23,
    24, 25, 26, // OSC 2ORANG
    25, 26, 27,
    28, 29, 30, // OSC 3ORANG
    29, 30, 31,
    32, 33, 34, // OSC 1GREY
    33, 34, 35,
    36, 37, 38, // OSC 2GREY
    37, 38, 39,
    40, 41, 42, // OSC 3GREY
    41, 42, 43,
    44, 45, 46, // SELE ORAN
    45, 46, 47,
    48, 49, 50, // SELE GREY
    49, 50, 51,
    52, 53, 54, // UI ORANG1
    53, 54, 55,
    56, 57, 58, // UI ORANG2
    57, 58, 59,
    60, 61, 62, // UI ORANG3
    61, 62, 63,
    64, 65, 66, // UI GREY1
    65, 66, 67,
    68, 69, 70, // UI GREY2
    69, 70, 71,
    72, 73, 74, // UI GREY3
    73, 74, 75, 
    76, 77, 78, //(move em all up)
    77, 78, 79,
    80, 81, 82,
    81, 82, 83,
    84, 85, 86,
    85, 86, 87,
    88, 89, 90,
    89, 90, 91,
    92, 93, 94,
    93, 94, 95,
    96, 97, 98,
    97, 98, 99,
    100, 101, 102, //HEADG1
    101, 102, 103,
    104, 105, 106, //HEADG2
    105, 106, 107,
    108, 109, 110, //HEADG3
    109, 110, 111,
    112, 113, 114, //OSCGR1
    113, 114, 115,
    116, 117, 118, //OSCGR2
    117, 118, 119,
    120, 121, 122, //OSCGR3
    121, 122, 123,
    124, 125, 126, //ENVGR1
    125, 126, 127,
    128, 129, 130, //ENVGR2
    129, 130, 131,
    132, 133, 134, //ENVGR3
    133, 134, 135,
    136, 137, 138, //PIABB
    137, 138, 139,
    140, 141, 142, //PIAGB
    141, 142, 143,
    144, 145, 146, //WHITE KEYS
    145, 146, 147,
    148, 149, 150, //-6
    149, 150, 151,
    152, 153, 154, //-5
    153, 154, 155,
    156, 157, 158, //-4
    157, 158, 159,
    160, 161, 162, //-3
    161, 162, 163,
    164, 165, 166, //-2
    165, 166, 167,
    168, 169, 170, //-1
    169, 170, 171,
    172, 173, 174, //0
    173, 174, 175,
    176, 177, 178, //1
    177, 178, 179,
    180, 181, 182, //2
    181, 182, 183,
    184, 185, 186, //3
    185, 186, 187,
    188, 189, 190, //4
    189, 190, 191,
    192, 193, 194, //5
    193, 194, 195,
    196, 197, 198, //6
    197, 198, 199,
    200, 201, 202, //7
    201, 202, 203,
    204, 205, 206, //BLACK KEYS
    205, 206, 207,
    208, 209, 210, //-6
    209, 210, 211,
    212, 213, 214, //-5
    213, 214, 215,
    216, 217, 218, //-4
    217, 218, 219,
    220, 221, 222, //-2
    221, 222, 223,
};

unsigned int NUMBER_OF_SHAPES = 2 * (37 + 14 + 10);

float SYNTH_MENU[] = {
    synthMenuDdn[2], synthMenuDdn[0], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    synthMenuDdn[2], synthMenuDdn[1], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    synthMenuDdn[3], synthMenuDdn[0], 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2],
    synthMenuDdn[3], synthMenuDdn[1], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float WFM1_MENU[] = {
    waveSelectDdn[2], waveSelectDdn[0], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[2], waveSelectDdn[1], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[3], waveSelectDdn[0], 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[3], waveSelectDdn[1], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float WFM2_MENU[] = {
    waveSelectDdn[6], waveSelectDdn[4], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[6], waveSelectDdn[5], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[7], waveSelectDdn[4], 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[7], waveSelectDdn[5], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float WFM3_MENU[] = {
    waveSelectDdn[10], waveSelectDdn[8], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[10], waveSelectDdn[9], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[11], waveSelectDdn[8], 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2],
    waveSelectDdn[11], waveSelectDdn[9], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};

float SELECTMENU1[] = {
    //WAVE NAME ORANGEBOX 1
    -0.260f - offset, 0.220f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.260f - offset, 0.1225f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.050f - offset, 0.220f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.050f - offset, 0.1225f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    //WAVE NAME GREYBOX 1
    -0.260f + q - offset, 0.220f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.260f + q - offset, 0.125f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.050f - q - offset, 0.220f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.050f - q - offset, 0.125f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
};
float SELECTMENU2[] = {
    //WAVE NAME ORANGEBOX 2
    -0.260f, 0.220f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.260f, 0.1225f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.050f, 0.220f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.050f, 0.1225f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],

    //WAVE NAME GREYBOX 2 
    -0.260f + q, 0.220f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.260f + q, 0.125f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.050f - q, 0.220f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.050f - q, 0.125f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
};
float SELECTMENU3[] = {
    //WAVE NAME ORANGEBOX 3
    -0.260f + offset, 0.220f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.260f + offset, 0.1225f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.050f + offset, 0.220f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.050f + offset, 0.1225f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],

    //WAVE NAME GREYBOX 3
    -0.260f + q + offset, 0.220f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.260f + q + offset, 0.125f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.050f - q + offset, 0.220f - q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
    -0.050f - q + offset, 0.125f + q, 0.0f, nimbusGrey[0], nimbusGrey[1], nimbusGrey[2],
};

float SELECT1[] = { synthMenuDdn[2], synthMenuDdn[0], 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0], 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT2[] = { synthMenuDdn[2], synthMenuDdn[0] - smq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT3[] = { synthMenuDdn[2], synthMenuDdn[0] - smq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT4[] = { synthMenuDdn[2], synthMenuDdn[0] - smq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT5[] = { synthMenuDdn[2], synthMenuDdn[0] - smq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT6[] = { synthMenuDdn[2], synthMenuDdn[0] - smq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT7[] = { synthMenuDdn[2], synthMenuDdn[0] - smq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT8[] = { synthMenuDdn[2], synthMenuDdn[0] - smq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 8, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 8, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT9[] = { synthMenuDdn[2], synthMenuDdn[0] - smq * 8, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 9, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 8, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 9, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float SELECT10[] = { synthMenuDdn[2], synthMenuDdn[0] - smq * 9, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[2], synthMenuDdn[0] - smq * 10, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 9, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                    synthMenuDdn[3], synthMenuDdn[0] - smq * 10, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};

float wSELECT1L[] = { waveSelectDdn[2], waveSelectDdn[0], 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[2], waveSelectDdn[0] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0], 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT2L[] = { waveSelectDdn[2], waveSelectDdn[0] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[2], waveSelectDdn[0] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT3L[] = { waveSelectDdn[2], waveSelectDdn[0] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[2], waveSelectDdn[0] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT4L[] = { waveSelectDdn[2], waveSelectDdn[0] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[2], waveSelectDdn[0] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT5L[] = { waveSelectDdn[2], waveSelectDdn[0] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[2], waveSelectDdn[0] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT6L[] = { waveSelectDdn[2], waveSelectDdn[0] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[2], waveSelectDdn[0] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT7L[] = { waveSelectDdn[2], waveSelectDdn[0] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[2], waveSelectDdn[0] - wsmq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[3], waveSelectDdn[0] - wsmq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};

float wSELECT1M[] = { waveSelectDdn[6], waveSelectDdn[4], 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[6], waveSelectDdn[4] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4], 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT2M[] = { waveSelectDdn[6], waveSelectDdn[4] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[6], waveSelectDdn[4] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT3M[] = { waveSelectDdn[6], waveSelectDdn[4] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[6], waveSelectDdn[4] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT4M[] = { waveSelectDdn[6], waveSelectDdn[4] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[6], waveSelectDdn[4] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT5M[] = { waveSelectDdn[6], waveSelectDdn[4] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[6], waveSelectDdn[4] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT6M[] = { waveSelectDdn[6], waveSelectDdn[4] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[6], waveSelectDdn[4] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT7M[] = { waveSelectDdn[6], waveSelectDdn[4] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[6], waveSelectDdn[4] - wsmq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[7], waveSelectDdn[4] - wsmq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};

float wSELECT1R[] = { waveSelectDdn[10], waveSelectDdn[8], 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                 waveSelectDdn[10], waveSelectDdn[8] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                 waveSelectDdn[11], waveSelectDdn[8], 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                 waveSelectDdn[11], waveSelectDdn[8] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT2R[] = { waveSelectDdn[10], waveSelectDdn[8] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[10], waveSelectDdn[8] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT3R[] = { waveSelectDdn[10], waveSelectDdn[8] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[10], waveSelectDdn[8] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 2, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT4R[] = { waveSelectDdn[10], waveSelectDdn[8] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[10], waveSelectDdn[8] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 3, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT5R[] = { waveSelectDdn[10], waveSelectDdn[8] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[10], waveSelectDdn[8] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 4, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT6R[] = { waveSelectDdn[10], waveSelectDdn[8] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[10], waveSelectDdn[8] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 5, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};
float wSELECT7R[] = { waveSelectDdn[10], waveSelectDdn[8] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[10], waveSelectDdn[8] - wsmq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 6, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
                     waveSelectDdn[11], waveSelectDdn[8] - wsmq * 7, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
};

float attack1[] = { -0.3f  - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f - offset, 0.770f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };
float decay1[] = {  -0.15f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f - offset, 0.770f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.00f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };
float sustain1[] = {-0.15f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //BL
                    -0.15f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //BR
                     0.15f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //TL
                     0.15f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] }; //TR
float release1[] = { 0.15f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.15f - offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.3f - offset,  0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };


float attack2[] = { -0.3f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f, 0.770f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };
float decay2[] = {  -0.15f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f, 0.770f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.00f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };
float sustain2[] = {-0.15f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //BL
                    -0.15f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //BR
                     0.15f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //TL
                     0.15f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] }; //TR
float release2[] = { 0.15f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.15f, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.3f,  0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };

float attack3[] = { -0.3f + offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f +offset, 0.770f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };
float decay3[] = {  -0.15f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                    -0.15f +offset, 0.770f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.00f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };
float sustain3[] = {-0.15f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //BL
                    -0.15f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //BR
                     0.15f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],   //TL
                     0.15f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] }; //TR
float release3[] = { 0.15f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.15f +offset, 0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2],
                     0.3f + offset,  0.250f, 0.f, fadedOrange[0], fadedOrange[1], fadedOrange[2] };

float bq = 0.01f;
//TL BL TR BR
float atk1box[] = { -0.15f - bq-offset, 0.770f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f - bq-offset, 0.770f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f + bq-offset, 0.770f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f + bq-offset, 0.770f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };
float dec1box[] = {  0.00f - bq-offset, 0.250f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f - bq-offset, 0.250f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f + bq-offset, 0.250f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f + bq-offset, 0.250f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };
float rel1box[] = {  0.30f - bq-offset, 0.250f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f - bq-offset, 0.250f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f + bq-offset, 0.250f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f + bq-offset, 0.250f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };

float atk2box[] = { -0.15f-bq, 0.770f+2*bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f-bq, 0.770f-  bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f+bq, 0.770f+2*bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f+bq, 0.770f-  bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };
float dec2box[] = {  0.00f-bq, 0.250f+2*bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f-bq, 0.250f-  bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f+bq, 0.250f+2*bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f+bq, 0.250f-  bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };
float rel2box[] = {  0.30f-bq, 0.250f+2*bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f-bq, 0.250f-  bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f+bq, 0.250f+2*bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f+bq, 0.250f-  bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };

float atk3box[] = { -0.15f - bq+offset, 0.770f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f - bq+offset, 0.770f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f + bq+offset, 0.770f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                    -0.15f + bq+offset, 0.770f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };
float dec3box[] = {  0.00f - bq+offset, 0.250f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f - bq+offset, 0.250f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f + bq+offset, 0.250f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.00f + bq+offset, 0.250f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };
float rel3box[] = {  0.30f - bq+offset, 0.250f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f - bq+offset, 0.250f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f + bq+offset, 0.250f + 2 * bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
                     0.30f + bq+offset, 0.250f - bq, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], };

float xClick[] = {
    -0.885f + q, -0.05f, 0.0f, hoverOrange[0] - q, hoverOrange[1] - q, hoverOrange[2] - q,
    -0.885f + q, -0.125f, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
    -0.8f + q, -0.05f, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
    -0.8f + q, -0.125f, 0.0f, hoverOrange[0] + .2, hoverOrange[1] + .15, hoverOrange[2] + .1,
};
float zClick[] = {
    -0.97f + q, -0.05f, 0.0f, hoverOrange[0] - q, hoverOrange[1] - q, hoverOrange[2] - q,
    -0.97f + q, -0.125f, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
    -0.885f + q, -0.05f, 0.0f, hoverOrange[0], hoverOrange[1], hoverOrange[2],
    -0.885f + q, -0.125f, 0.0f, hoverOrange[0] + .2, hoverOrange[1] + .15, hoverOrange[2] + .1,
};

//TriTop: TOP LEFT RIGHT
//TriBtm: BTM LEFT RIGHT
//Triangle margins go: 1.75, 5, 1.75, 8, 1.75, 5, 1.75
float atk1TriTop[] = {
        -0.215f-offset,  0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.2375f-offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.1975f-offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float atk1TriBtm[] = {
        -0.215f-offset, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.2375f-offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.1975f-offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float dec1TriTop[] = {
        -0.075f-offset, 0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0975f-offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0575f-offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float dec1TriBtm[] = {
        -0.075f-offset, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0975f-offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0575f-offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float sus1TriTop[] = {
         0.075f-offset, 0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0975f-offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0575f-offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float sus1TriBtm[] = {
         0.075f-offset, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0975f-offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0575f-offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float rel1TriTop[] = {
         0.215f-offset,  0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.2375f-offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.1975f-offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float rel1TriBtm[] = {
         0.215f-offset, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.2375f-offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.1975f-offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};

float atk2TriTop[] = {
        -0.215f,  0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.2375f, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.1975f, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float atk2TriBtm[] = {
        -0.215f, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.2375f, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.1975f, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float dec2TriTop[] = {
        -0.075f, 0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0975f, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0575f, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float dec2TriBtm[] = {
        -0.075f, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0975f, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0575f, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float sus2TriTop[] = {
         0.075f, 0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0975f, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0575f, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float sus2TriBtm[] = {
         0.075f, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0975f, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0575f, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float rel2TriTop[] = {
         0.215f,  0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.2375f, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.1975f, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float rel2TriBtm[] = {
         0.215f, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.2375f, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.1975f, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};

float atk3TriTop[] = {
        -0.215f + offset,  0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.2375f + offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.1975f + offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float atk3TriBtm[] = {
        -0.215f + offset, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.2375f + offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.1975f + offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float dec3TriTop[] = {
        -0.075f + offset, 0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0975f + offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0575f + offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float dec3TriBtm[] = {
        -0.075f + offset, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0975f + offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
        -0.0575f + offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float sus3TriTop[] = {
         0.075f + offset, 0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0975f + offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0575f + offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float sus3TriBtm[] = {
         0.075f + offset, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0975f + offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.0575f + offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float rel3TriTop[] = {
         0.215f + offset,  0.2325f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.2375f + offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.1975f + offset, 0.1825f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
float rel3TriBtm[] = {
         0.215f + offset, 0.0175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.2375f + offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
         0.1975f + offset, 0.05175f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};


//text
float staticText[] = {
    // positions                            // colors                                    // texture coords
    -1.f + q, 1.f - q, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f, // top left
    -1.f + q,-1.f + q, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f, // bottom left
     1.f - q, 1.f - q, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f, // top right
     1.f - q,-1.f + q, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f  // bottom right 
};
float synth_menu_text[] = {
    synthMenuDdn[2], synthMenuDdn[0], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    synthMenuDdn[2], synthMenuDdn[1], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
    synthMenuDdn[3], synthMenuDdn[0], 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2],1.0f, 1.0f,
    synthMenuDdn[3], synthMenuDdn[1], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float wfm1_menu_text[] = {
    waveSelectDdn[2], waveSelectDdn[0], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    waveSelectDdn[2], waveSelectDdn[1], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
    waveSelectDdn[3], waveSelectDdn[0], 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2],1.0f, 1.0f,
    waveSelectDdn[3], waveSelectDdn[1], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float wfm2_menu_text[] = {
    waveSelectDdn[6], waveSelectDdn[4], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    waveSelectDdn[6], waveSelectDdn[5], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
    waveSelectDdn[7], waveSelectDdn[4], 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2],1.0f, 1.0f,
    waveSelectDdn[7], waveSelectDdn[5], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float wfm3_menu_text[] = {
    waveSelectDdn[10], waveSelectDdn[8], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    waveSelectDdn[10], waveSelectDdn[9], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
    waveSelectDdn[11], waveSelectDdn[8], 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2],1.0f, 1.0f,
    waveSelectDdn[11], waveSelectDdn[9], 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float adsr1_text[] = {
    -0.3000f - offset, 0.250f, 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.3000f - offset, 0.0f,   0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.3000f - offset, 0.250f, 0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.3000f - offset, 0.0f,   0.0f,  pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float adsr2_text[] = {
    -0.3000f, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.3000f, 0.0f,   0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.3000f, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.3000f, 0.0f,   0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float adsr3_text[] = {
    -0.3000f + offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.3000f + offset, 0.0f,   0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.3000f + offset, 0.250f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.3000f + offset, 0.0f,   0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};


unsigned int osc_left_ch;
unsigned int osc_midl_ch;
unsigned int osc_rght_ch;

float osc_left[] = {
    -0.3000f-offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.3000f-offset, 0.f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.3000f-offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.3000f-offset, 0.f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float osc_midl[] = {
    -0.3000f, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.3000f, 0.f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.3000f, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.3000f, 0.f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float osc_rght[] = {
    -0.3000f+offset,  0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.3000f+offset,  0.f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.3000f+offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.3000f+offset, 0.f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};

float osc_name_left[] = {
    -0.075f + q - offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
    -0.075f + q - offset, 0.770f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
     0.100f - q - offset, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
     0.100f - q - offset, 0.770f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
};
float osc_name_midl[] = {
    -0.075f + q, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
    -0.075f + q, 0.770f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
     0.100f - q, 0.870f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
     0.100f - q, 0.770f, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
};
float osc_name_rght[] = {
    -0.075f + q + offset, 0.870f - q, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
    -0.075f + q + offset, 0.770f, 0.0f,     funeralGrey[0], funeralGrey[1], funeralGrey[2],
     0.100f - q + offset, 0.870f - q, 0.0f, funeralGrey[0], funeralGrey[1], funeralGrey[2],
     0.100f - q + offset, 0.770f, 0.0f,     funeralGrey[0], funeralGrey[1], funeralGrey[2],

};
float osc_on_left[] = {
    -0.075f + q - offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.075f + q - offset, 0.770f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.100f - q - offset, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.100f - q - offset, 0.770f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float osc_on_midl[] = {
    -0.075f + q, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.075f + q, 0.770f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.100f - q, 0.870f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.100f - q, 0.770f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f
};
float osc_on_rght[] = {
    -0.075f + q + offset, 0.870f - q, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 1.0f,
    -0.075f + q + offset, 0.770f, 0.0f,     pocketOrange[0], pocketOrange[1], pocketOrange[2], 0.0f, 0.0f,
     0.100f - q + offset, 0.870f - q, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 1.0f,
     0.100f - q + offset, 0.770f, 0.0f,     pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f, 0.0f

};

/*
  -0.97f + q, -0.05f, 0.0f, pocketOrange[0] - q, pocketOrange[1] - q, pocketOrange[2] - q,
  -0.97f + q, -0.125f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
  -0.8f + q, -0.05f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
  -0.8f + q, -0.125f, 0.0f, pocketOrange[0] + .2, pocketOrange[1] + .15, pocketOrange[2] + .1,
*/

//left top bottom
float z_left[] = {
    -0.970f, -0.0875f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.930f, -0.05f,   0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.930f, -0.125f,  0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};
//top bottom right
float z_right[] = {
    -0.850f, -0.05f ,  0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.850f, -0.125f,  0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
    -0.800f, -0.0875f, 0.0f, pocketOrange[0], pocketOrange[1], pocketOrange[2],
};

const unsigned int triangle_idx[] = { 0, 1, 2 };

const unsigned int square_idx[] = {
    0,1,2,  1,2,3
};
const unsigned int select_idx[] = {
    0,1,2,  1,2,3,
    4,5,6,  5,6,7
};


const unsigned int SURFACES = 105; //60 and 61 are free
unsigned int VBOs[SURFACES], VAOs[SURFACES], EBOs[SURFACES];

//Index in VAO array, vertex array and size, index array and size, and specify if it has a texture
void loadArray(int index, const float* vertices, GLsizei verticesSize, const unsigned int* indices, GLsizei indicesSize, bool texture) {
    glBindVertexArray(VAOs[index]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[index]);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[index]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    if (texture) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    else {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
}


void init() {
    glGenVertexArrays(SURFACES, VAOs);
    glGenBuffers(SURFACES, VBOs);
    glGenBuffers(SURFACES, EBOs);

    loadArray(0, vertices, sizeof(vertices), indices, sizeof(indices), false);

    loadArray(1, SYNTH_MENU, sizeof(SYNTH_MENU), square_idx, sizeof(square_idx), false);
    loadArray(2, WFM1_MENU, sizeof(WFM1_MENU), square_idx, sizeof(square_idx), false);
    loadArray(3, WFM2_MENU, sizeof(WFM2_MENU), square_idx, sizeof(square_idx), false);
    loadArray(4, WFM3_MENU, sizeof(WFM3_MENU), square_idx, sizeof(square_idx), false);

    loadArray(5, SELECT1, sizeof(SELECT1), square_idx, sizeof(square_idx), false);
    loadArray(6, SELECT2, sizeof(SELECT2), square_idx, sizeof(square_idx), false);
    loadArray(7, SELECT3, sizeof(SELECT3), square_idx, sizeof(square_idx), false);
    loadArray(8, SELECT4, sizeof(SELECT4), square_idx, sizeof(square_idx), false);
    loadArray(9, SELECT5, sizeof(SELECT5), square_idx, sizeof(square_idx), false);
    loadArray(10, SELECT6, sizeof(SELECT6), square_idx, sizeof(square_idx), false);
    loadArray(11, SELECT7, sizeof(SELECT7), square_idx, sizeof(square_idx), false);
    loadArray(12, SELECT8, sizeof(SELECT8), square_idx, sizeof(square_idx), false);
    loadArray(13, SELECT9, sizeof(SELECT9), square_idx, sizeof(square_idx), false);
    loadArray(14, SELECT10, sizeof(SELECT10), square_idx, sizeof(square_idx), false);

    loadArray(15, wSELECT1L, sizeof(wSELECT1L), square_idx, sizeof(square_idx), false);
    loadArray(16, wSELECT2L, sizeof(wSELECT2L), square_idx, sizeof(square_idx), false);
    loadArray(17, wSELECT3L, sizeof(wSELECT3L), square_idx, sizeof(square_idx), false);
    loadArray(18, wSELECT4L, sizeof(wSELECT4L), square_idx, sizeof(square_idx), false);
    loadArray(19, wSELECT5L, sizeof(wSELECT5L), square_idx, sizeof(square_idx), false);
    loadArray(20, wSELECT6L, sizeof(wSELECT6L), square_idx, sizeof(square_idx), false);
    loadArray(21, wSELECT7L, sizeof(wSELECT7L), square_idx, sizeof(square_idx), false);
    loadArray(22, wSELECT1M, sizeof(wSELECT1M), square_idx, sizeof(square_idx), false);
    loadArray(23, wSELECT2M, sizeof(wSELECT2M), square_idx, sizeof(square_idx), false);
    loadArray(24, wSELECT3M, sizeof(wSELECT3M), square_idx, sizeof(square_idx), false);
    loadArray(25, wSELECT4M, sizeof(wSELECT4M), square_idx, sizeof(square_idx), false);
    loadArray(26, wSELECT5M, sizeof(wSELECT5M), square_idx, sizeof(square_idx), false);
    loadArray(27, wSELECT6M, sizeof(wSELECT6M), square_idx, sizeof(square_idx), false);
    loadArray(28, wSELECT7M, sizeof(wSELECT7M), square_idx, sizeof(square_idx), false);
    loadArray(29, wSELECT1R, sizeof(wSELECT1R), square_idx, sizeof(square_idx), false);
    loadArray(30, wSELECT2R, sizeof(wSELECT2R), square_idx, sizeof(square_idx), false);
    loadArray(31, wSELECT3R, sizeof(wSELECT3R), square_idx, sizeof(square_idx), false);
    loadArray(32, wSELECT4R, sizeof(wSELECT4R), square_idx, sizeof(square_idx), false);
    loadArray(33, wSELECT5R, sizeof(wSELECT5R), square_idx, sizeof(square_idx), false);
    loadArray(34, wSELECT6R, sizeof(wSELECT6R), square_idx, sizeof(square_idx), false);
    loadArray(35, wSELECT7R, sizeof(wSELECT7R), square_idx, sizeof(square_idx), false);

    loadArray(36, attack2, sizeof(attack2), triangle_idx, sizeof(triangle_idx), false);
    loadArray(37, decay2, sizeof(decay2), triangle_idx, sizeof(triangle_idx), false);
    loadArray(38, sustain2, sizeof(sustain2), triangle_idx, sizeof(triangle_idx), false);
    loadArray(39, release2, sizeof(release2), triangle_idx, sizeof(triangle_idx), false);
    loadArray(40, attack1, sizeof(attack1), triangle_idx, sizeof(triangle_idx), false);
    loadArray(41, decay1, sizeof(decay1), triangle_idx, sizeof(triangle_idx), false);
    loadArray(42, sustain1, sizeof(sustain1), triangle_idx, sizeof(triangle_idx), false);
    loadArray(43, release1, sizeof(release1), triangle_idx, sizeof(triangle_idx), false);
    loadArray(44, attack3, sizeof(attack3), triangle_idx, sizeof(triangle_idx), false);
    loadArray(45, decay3, sizeof(decay3), triangle_idx, sizeof(triangle_idx), false);
    loadArray(46, sustain3, sizeof(sustain3), triangle_idx, sizeof(triangle_idx), false);
    loadArray(47, release3, sizeof(release3), triangle_idx, sizeof(triangle_idx), false);

    loadArray(48, atk2box, sizeof(atk2box), square_idx, sizeof(square_idx), false);
    loadArray(49, dec2box, sizeof(dec2box), square_idx, sizeof(square_idx), false);
    loadArray(50, rel2box, sizeof(rel2box), square_idx, sizeof(square_idx), false);
    loadArray(51, atk1box, sizeof(atk1box), square_idx, sizeof(square_idx), false);
    loadArray(52, dec1box, sizeof(dec1box), square_idx, sizeof(square_idx), false);
    loadArray(53, rel1box, sizeof(rel1box), square_idx, sizeof(square_idx), false);
    loadArray(54, atk3box, sizeof(atk3box), square_idx, sizeof(square_idx), false);
    loadArray(55, dec3box, sizeof(dec3box), square_idx, sizeof(square_idx), false);
    loadArray(56, rel3box, sizeof(rel3box), square_idx, sizeof(square_idx), false);

    loadArray(57, SELECTMENU1, sizeof(SELECTMENU1), select_idx, sizeof(select_idx), false);
    loadArray(58, SELECTMENU2, sizeof(SELECTMENU2), select_idx, sizeof(select_idx), false);
    loadArray(59, SELECTMENU3, sizeof(SELECTMENU3), select_idx, sizeof(select_idx), false);

    loadArray(62, atk2TriTop, sizeof(atk2TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(63, atk2TriBtm, sizeof(atk2TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(64, dec2TriTop, sizeof(dec2TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(65, dec2TriBtm, sizeof(dec2TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(66, sus2TriTop, sizeof(sus2TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(67, sus2TriBtm, sizeof(sus2TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(68, rel2TriTop, sizeof(rel2TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(69, rel2TriBtm, sizeof(rel2TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(70, atk1TriTop, sizeof(atk1TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(71, atk1TriBtm, sizeof(atk1TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(72, dec1TriTop, sizeof(dec1TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(73, dec1TriBtm, sizeof(dec1TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(74, sus1TriTop, sizeof(sus1TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(75, sus1TriBtm, sizeof(sus1TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(76, rel1TriTop, sizeof(rel1TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(77, rel1TriBtm, sizeof(rel1TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(78, atk3TriTop, sizeof(atk3TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(79, atk3TriBtm, sizeof(atk3TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(80, dec3TriTop, sizeof(dec3TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(81, dec3TriBtm, sizeof(dec3TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(82, sus3TriTop, sizeof(sus3TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(83, sus3TriBtm, sizeof(sus3TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(84, rel3TriTop, sizeof(rel3TriTop), triangle_idx, sizeof(triangle_idx), false);
    loadArray(85, rel3TriBtm, sizeof(rel3TriBtm), triangle_idx, sizeof(triangle_idx), false);
    loadArray(86, staticText, sizeof(staticText), square_idx, sizeof(square_idx), true);
    loadArray(87, synth_menu_text, sizeof(synth_menu_text), square_idx, sizeof(square_idx), true);
    loadArray(88, wfm1_menu_text, sizeof(wfm1_menu_text), square_idx, sizeof(square_idx), true);
    loadArray(89, wfm2_menu_text, sizeof(wfm2_menu_text), square_idx, sizeof(square_idx), true);
    loadArray(90, wfm3_menu_text, sizeof(wfm3_menu_text), square_idx, sizeof(square_idx), true);
    loadArray(91, adsr1_text, sizeof(adsr1_text), square_idx, sizeof(square_idx), true);
    loadArray(92, adsr2_text, sizeof(adsr2_text), square_idx, sizeof(square_idx), true);
    loadArray(93, adsr3_text, sizeof(adsr3_text), square_idx, sizeof(square_idx), true);
    loadArray(94, osc_left, sizeof(osc_left), square_idx, sizeof(square_idx), true);
    loadArray(95, osc_midl, sizeof(osc_midl), square_idx, sizeof(square_idx), true);
    loadArray(96, osc_rght, sizeof(osc_rght), square_idx, sizeof(square_idx), true);
    loadArray(97, osc_name_left, sizeof(osc_name_left), square_idx, sizeof(square_idx), false);
    loadArray(98, osc_name_midl, sizeof(osc_name_midl), square_idx, sizeof(square_idx), false);
    loadArray(99, osc_name_rght, sizeof(osc_name_rght), square_idx, sizeof(square_idx), false);
    loadArray(100, osc_on_left, sizeof(osc_on_left), square_idx, sizeof(square_idx), true);
    loadArray(101, osc_on_midl, sizeof(osc_on_midl), square_idx, sizeof(square_idx), true);
    loadArray(102, osc_on_rght, sizeof(osc_on_rght), square_idx, sizeof(square_idx), true);
    loadArray(103, z_left, sizeof(z_left), triangle_idx, sizeof(triangle_idx), false);
    loadArray(104, z_right, sizeof(z_right), triangle_idx, sizeof(triangle_idx), false);
}


void loadMyTexture(unsigned int& texture, std::string path) {

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}
#endif
