#include "vertices.h"
//#include "textures.h"
#include "csynth.h"

#include <list>
#include <iostream>
#include <algorithm>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void loadSynths();
void loadWave(int theChannel);
void loadEnvelope(int theChannel);
void get_resolution();
double MakeNoise(double dTime);


bool open = true;

vector<Note> vecNotes;
mutex muxNotes;
vector<Instrument> vecInstruments;

Instrument preset1;
Instrument preset2;
Instrument preset3;
Instrument preset4;
Instrument preset5;
Instrument preset6;
Instrument preset7;
Instrument preset8;
Instrument preset9;
Instrument preset10;
int octave = 3;
int channel = 0;

int main()
{
    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();
    olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

    sound.SetUserFunction(MakeNoise);

    char keyboard[129];
    memset(keyboard, ' ', 127);
    keyboard[128] = '\0';

    auto clock_old_time = chrono::high_resolution_clock::now();
    auto clock_real_time = chrono::high_resolution_clock::now();
    double dElapsedTime = 0.0;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triscillator", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // shaders
    Shader mainShader("Shaders/shader.vert", "Shaders/shader.frag");
    Shader volSliderShader("Shaders/volumeSlider.vert", "Shaders/shader.frag");
    Shader attackShader("Shaders/attackShader.vert", "Shaders/attackShader.geom", "Shaders/attackShader.frag");
    Shader decayShader("Shaders/decayShader.vert", "Shaders/decayShader.geom", "Shaders/decayShader.frag");
    Shader sustainShader("Shaders/sustainShader.vert", "Shaders/sustainShader.geom", "Shaders/sustainShader.frag");
    Shader releaseShader("Shaders/releaseShader.vert", "Shaders/releaseShader.geom", "Shaders/releaseShader.frag");
    Shader attackSlider("Shaders/button-atkShader.vert", "Shaders/button-atkShader.frag");
    Shader decaySlider("Shaders/button-decShader.vert", "Shaders/button-decShader.frag");
    Shader releaseSlider("Shaders/button-relShader.vert", "Shaders/button-relShader.frag");
    Shader textShader("Shaders/textShader.vert", "Shaders/textShader.frag");
    //Shader textShader("freeTypeShader.vert", "freeTypeShader.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    init();
    loadSynths();
    //loadEnvelope(channel);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (open)
    {
        //FIXME: something about the close button crashes the noise maker
        //if (glfwWindowShouldClose(window))
        //    open = false;
        // input
        // -----
        get_resolution();
        processInput(window);

        // play music notes
        for (int k = 0; k < 12; k++)
        {
            short nKeyState = GetAsyncKeyState((unsigned char)("AWSDRFTGHUJI"[k]));  //"ZSXCFVGBNJMK\xbcL\xbe\xbf"[k]) //AWSEDFTGYHUJKOLP

            double dTimeNow = sound.GetTime();

            muxNotes.lock();
            auto noteFound = find_if(vecNotes.begin(), vecNotes.end(), [&k](Note const& item) { return item.id % 12 == k; });
            if (noteFound == vecNotes.end())
            {

                if (nKeyState & 0x8000)
                {
                    Note n;
                    n.id = k + (12 * octave);
                    n.on = dTimeNow;
                    n.channel = channel;
                    n.active = true;

                    vecNotes.emplace_back(n);
                }
                else
                {

                }
            }
            else
            {
                if (nKeyState & 0x8000)
                {
                    if (noteFound->off > noteFound->on)
                    {
                        noteFound->on = dTimeNow;
                        noteFound->active = true;
                    }
                }
                else
                {
                    if (noteFound->off < noteFound->on)
                    {
                        noteFound->off = dTimeNow;
                    }
                }
            }
            muxNotes.unlock();
        }

        // render
        // ------
        glClearColor(pocketOrange[0], pocketOrange[1], pocketOrange[2], 1.0f);   //background color
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        mainShader.use();

        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, NUMBER_OF_SHAPES * 3, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAOs[103]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[104]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        unsigned int staticText;
        loadMyTexture(staticText, "Text/text-general.png");
        textShader.use();
        glBindTexture(GL_TEXTURE_2D, staticText);
        glBindVertexArray(VAOs[86]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        mainShader.use();

        if (wfm1_hover || wfm1_engaged) {
            glBindVertexArray(VAOs[2]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (wfm2_hover || wfm2_engaged) {
            glBindVertexArray(VAOs[3]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (wfm3_hover || wfm3_engaged) {
            glBindVertexArray(VAOs[4]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (env1) {
            glBindVertexArray(VAOs[70]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[71]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[72]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[73]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            attackShader.use();
            attackShader.setFloat("xMovement", atk1Mod);
            glBindVertexArray(VAOs[40]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            decayShader.use();
            decayShader.setFloat("xMovementAtk", atk1Mod);
            decayShader.setFloat("xMovementDec", dec1Mod);
            decayShader.setFloat("yMovementSus", sus1Mod);
            glBindVertexArray(VAOs[41]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            sustainShader.use();
            sustainShader.setFloat("xMovementAtk", atk1Mod);
            sustainShader.setFloat("yMovementSus", sus1Mod);
            sustainShader.setFloat("offset", -2 * offset);
            glBindVertexArray(VAOs[42]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            releaseShader.use();
            releaseShader.setFloat("xMovementRel", rel1Mod);
            releaseShader.setFloat("yMovementSus", sus1Mod);
            glBindVertexArray(VAOs[43]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            attackSlider.use();
            attackSlider.setFloat("xMovement", atk1Mod);
            glBindVertexArray(VAOs[51]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
            decaySlider.use();
            decaySlider.setFloat("xMovementAtk", atk1Mod);
            decaySlider.setFloat("xMovement", dec1Mod);
            decaySlider.setFloat("yMovement", sus1Mod);
            glBindVertexArray(VAOs[52]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
            releaseSlider.use();
            releaseSlider.setFloat("xMovement", rel1Mod);
            glBindVertexArray(VAOs[53]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);

            unsigned int adsr_text;
            loadMyTexture(adsr_text, "Text/text-select-adsr.png");
            textShader.use();
            glBindTexture(GL_TEXTURE_2D, adsr_text);
            glBindVertexArray(VAOs[91]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            mainShader.use();
        }
        else {
            glBindVertexArray(VAOs[57]);
            glDrawElements(GL_TRIANGLES, 4 * 3, GL_UNSIGNED_INT, 0);
            textShader.use();
            glBindTexture(GL_TEXTURE_2D, osc_left_ch);
            glBindVertexArray(VAOs[94]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            mainShader.use();
            if (wfm1_hover) {
                if (wfm1preset1_hover) {
                    glBindVertexArray(VAOs[15]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm1preset2_hover) {
                    glBindVertexArray(VAOs[16]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm1preset3_hover) {
                    glBindVertexArray(VAOs[17]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm1preset4_hover) {
                    glBindVertexArray(VAOs[18]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm1preset5_hover) {
                    glBindVertexArray(VAOs[19]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm1preset6_hover) {
                    glBindVertexArray(VAOs[20]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm1preset7_hover) {
                    glBindVertexArray(VAOs[21]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                unsigned int wfm1_menu_text;
                loadMyTexture(wfm1_menu_text, "Text/text-select-wvdrdn.png");
                textShader.use();
                glBindTexture(GL_TEXTURE_2D, wfm1_menu_text);
                glBindVertexArray(VAOs[88]);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                mainShader.use();
            }
        }
        if (env2) {
            glBindVertexArray(VAOs[62]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[63]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[64]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[65]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            attackShader.use();
            attackShader.setFloat("xMovement", atk2Mod);
            glBindVertexArray(VAOs[36]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            decayShader.use();
            decayShader.setFloat("xMovementAtk", atk2Mod);
            decayShader.setFloat("xMovementDec", dec2Mod);
            decayShader.setFloat("yMovementSus", sus2Mod);
            glBindVertexArray(VAOs[37]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            sustainShader.use();
            sustainShader.setFloat("xMovementAtk", atk2Mod);
            sustainShader.setFloat("yMovementSus", sus2Mod);
            sustainShader.setFloat("offset", 0.0f);
            glBindVertexArray(VAOs[38]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            releaseShader.use();
            releaseShader.setFloat("xMovementRel", rel2Mod);
            releaseShader.setFloat("yMovementSus", sus2Mod);
            glBindVertexArray(VAOs[39]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            attackSlider.use();
            attackSlider.setFloat("xMovement", atk2Mod);
            glBindVertexArray(VAOs[48]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
            decaySlider.use();
            decaySlider.setFloat("xMovementAtk", atk2Mod);
            decaySlider.setFloat("xMovement", dec2Mod);
            decaySlider.setFloat("yMovement", sus2Mod);
            glBindVertexArray(VAOs[49]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
            releaseSlider.use();
            releaseSlider.setFloat("xMovement", rel2Mod);
            glBindVertexArray(VAOs[50]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);

            unsigned int adsr_text;
            loadMyTexture(adsr_text, "Text/text-select-adsr.png");
            textShader.use();
            glBindTexture(GL_TEXTURE_2D, adsr_text);
            glBindVertexArray(VAOs[92]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            mainShader.use();
        }
        else {
            glBindVertexArray(VAOs[58]);
            glDrawElements(GL_TRIANGLES, 4 * 3, GL_UNSIGNED_INT, 0);
            textShader.use();
            glBindTexture(GL_TEXTURE_2D, osc_midl_ch);
            glBindVertexArray(VAOs[95]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            mainShader.use();
            if (wfm2_hover) {
                if (wfm2preset1_hover) { //wfm 2
                    glBindVertexArray(VAOs[22]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm2preset2_hover) {
                    glBindVertexArray(VAOs[23]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm2preset3_hover) {
                    glBindVertexArray(VAOs[24]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm2preset4_hover) {
                    glBindVertexArray(VAOs[25]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm2preset5_hover) {
                    glBindVertexArray(VAOs[26]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm2preset6_hover) {
                    glBindVertexArray(VAOs[27]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm2preset7_hover) {
                    glBindVertexArray(VAOs[28]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                unsigned int wfm2_menu_text;
                loadMyTexture(wfm2_menu_text, "Text/text-select-wvdrdn.png");
                textShader.use();
                glBindTexture(GL_TEXTURE_2D, wfm2_menu_text);
                glBindVertexArray(VAOs[89]);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                mainShader.use();
            }
        }
        if (env3) {
            glBindVertexArray(VAOs[78]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[79]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[80]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(VAOs[81]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            attackShader.use();
            attackShader.setFloat("xMovement", atk3Mod);
            glBindVertexArray(VAOs[44]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            decayShader.use();
            decayShader.setFloat("xMovementAtk", atk3Mod);
            decayShader.setFloat("xMovementDec", dec3Mod);
            decayShader.setFloat("yMovementSus", sus3Mod);
            glBindVertexArray(VAOs[45]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            sustainShader.use();
            sustainShader.setFloat("xMovementAtk", atk3Mod);
            sustainShader.setFloat("yMovementSus", sus3Mod);
            sustainShader.setFloat("offset", 2 * offset);
            glBindVertexArray(VAOs[46]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            releaseShader.use();
            releaseShader.setFloat("xMovementRel", rel3Mod);
            releaseShader.setFloat("yMovementSus", sus3Mod);
            glBindVertexArray(VAOs[47]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            attackSlider.use();
            attackSlider.setFloat("xMovement", atk3Mod);
            glBindVertexArray(VAOs[54]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
            decaySlider.use();
            decaySlider.setFloat("xMovementAtk", atk3Mod);
            decaySlider.setFloat("xMovement", dec3Mod);
            decaySlider.setFloat("yMovement", sus3Mod);
            glBindVertexArray(VAOs[55]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
            releaseSlider.use();
            releaseSlider.setFloat("xMovement", rel3Mod);
            glBindVertexArray(VAOs[56]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);

            unsigned int adsr_text;
            loadMyTexture(adsr_text, "Text/text-select-adsr.png");
            textShader.use();
            glBindTexture(GL_TEXTURE_2D, adsr_text);
            glBindVertexArray(VAOs[93]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            mainShader.use();
        }
        else {
            glBindVertexArray(VAOs[59]);
            glDrawElements(GL_TRIANGLES, 4 * 3, GL_UNSIGNED_INT, 0);
            textShader.use();
            glBindTexture(GL_TEXTURE_2D, osc_rght_ch);
            glBindVertexArray(VAOs[96]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            mainShader.use();
            if (wfm3_hover) {
                if (wfm3preset1_hover) { //wfm 2
                    glBindVertexArray(VAOs[29]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm3preset2_hover) {
                    glBindVertexArray(VAOs[30]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm3preset3_hover) {
                    glBindVertexArray(VAOs[31]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm3preset4_hover) {
                    glBindVertexArray(VAOs[32]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm3preset5_hover) {
                    glBindVertexArray(VAOs[33]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm3preset6_hover) {
                    glBindVertexArray(VAOs[34]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }
                if (wfm3preset7_hover) {
                    glBindVertexArray(VAOs[35]);
                    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
                }                
                unsigned int wfm3_menu_text;
                loadMyTexture(wfm3_menu_text, "Text/text-select-wvdrdn.png");
                textShader.use();
                glBindTexture(GL_TEXTURE_2D, wfm3_menu_text);
                glBindVertexArray(VAOs[90]);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                mainShader.use();
            }
        }

        //..SR and Volume / Local Octave Sliders
        glBindVertexArray(VAOs[74]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[75]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[76]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[77]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[66]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[67]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[68]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[69]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[82]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[83]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[84]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[85]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        if (vecInstruments[channel].getActive(0)) {
            glBindVertexArray(VAOs[97]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        if (vecInstruments[channel].getActive(1)) {
            glBindVertexArray(VAOs[98]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        if (vecInstruments[channel].getActive(2)) {
            glBindVertexArray(VAOs[99]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        unsigned int oscillatorOn_text;
        loadMyTexture(oscillatorOn_text, "Text/text-osc-on.png");
        textShader.use();
        glBindTexture(GL_TEXTURE_2D, oscillatorOn_text);
        glBindVertexArray(VAOs[100]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[101]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[102]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        mainShader.use();

        // preset select menu
        if (symn_hover || symn_engaged) {
            glBindVertexArray(VAOs[1]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset1_hover) {
            glBindVertexArray(VAOs[5]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset2_hover) {
            glBindVertexArray(VAOs[6]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset3_hover) {
            glBindVertexArray(VAOs[7]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset4_hover) {
            glBindVertexArray(VAOs[8]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset5_hover) {
            glBindVertexArray(VAOs[9]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset6_hover) {
            glBindVertexArray(VAOs[10]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset7_hover) {
            glBindVertexArray(VAOs[11]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset8_hover) {
            glBindVertexArray(VAOs[12]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset9_hover) {
            glBindVertexArray(VAOs[13]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }
        if (preset10_hover) {
            glBindVertexArray(VAOs[14]);
            glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
        }

        if (symn_hover || symn_engaged) {
            unsigned int synth_menu_text;
            loadMyTexture(synth_menu_text, "Text/text-select-presets.png");
            textShader.use();
            glBindTexture(GL_TEXTURE_2D, synth_menu_text);
            glBindVertexArray(VAOs[87]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            mainShader.use();
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(SURFACES, VAOs);
    glDeleteBuffers(SURFACES, VBOs);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

double convertx(float pos) {
    pos += 1;
    pos /= 2;
    return pos * SCR_WIDTH;
}
double converty(float pos) {
    pos *= -1;
    pos += 1;
    pos /= 2;
    return pos * SCR_HEIGHT;
}
double deconvertx(float pos) {
    pos /= SCR_WIDTH;
    pos *= 2;
    pos -= 1;
    return pos;
}
double deconverty(float pos) {
    pos /= SCR_HEIGHT;
    pos *= 2;
    pos -= 1;
    pos *= -1;
    return pos;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        debug = true;
    }
    else if (debug) {
        debug = false;
        std::cout << "Cursor Position at (" << xpos << ", " << ypos << ")" << std::endl;
    }

    //SYNTH MENU
    if (ypos > converty(synthMenu[0]) && ypos < converty(synthMenu[1]) && xpos > convertx(synthMenu[2]) && xpos < convertx(synthMenu[3])) {
        symn_hover = true;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            symn_click = true;
        }
        else if (symn_click) {
            if (symn_engaged)
                symn_engaged = false;
            else
                symn_engaged = true;
            symn_click = false;
        }
    }
    else if (ypos > converty(synthMenuDdn[0]) && ypos < converty(synthMenuDdn[1]) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3])) {
        if (symn_engaged)
            symn_hover = true;
        if (symn_hover) {
            if (ypos > converty(synthMenuDdn[0]) && ypos < converty(synthMenuDdn[0] - smq) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset1_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset1_click = true;
                else if (preset1_click) {
                    channel = 0;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset1_click = false;
                }
            }
            else
                preset1_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq) && ypos < converty(synthMenuDdn[0] - smq * 2) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset2_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset2_click = true;
                else if (preset2_click) {
                    channel = 1;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset2_click = false;
                }
            }
            else
                preset2_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq * 2) && ypos < converty(synthMenuDdn[0] - smq * 3) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset3_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset3_click = true;
                else if (preset3_click) {
                    channel = 2;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset3_click = false;
                }
            }
            else
                preset3_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq * 3) && ypos < converty(synthMenuDdn[0] - smq * 4) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset4_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset4_click = true;
                else if (preset4_click) {
                    channel = 3;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset4_click = false;
                }
            }
            else
                preset4_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq * 4) && ypos < converty(synthMenuDdn[0] - smq * 5) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset5_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset5_click = true;
                else if (preset5_click) {
                    channel = 4;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset5_click = false;
                }
            }
            else
                preset5_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq * 5) && ypos < converty(synthMenuDdn[0] - smq * 6) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset6_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset6_click = true;
                else if (preset6_click) {
                    channel = 5;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset6_click = false;
                }
            }
            else
                preset6_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq * 6) && ypos < converty(synthMenuDdn[0] - smq * 7) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset7_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset7_click = true;
                else if (preset7_click) {
                    channel = 6;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset7_click = false;
                }
            }
            else
                preset7_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq * 7) && ypos < converty(synthMenuDdn[0] - smq * 8) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset8_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset8_click = true;
                else if (preset8_click) {
                    channel = 7;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset8_click = false;
                }
            }
            else
                preset8_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq * 8) && ypos < converty(synthMenuDdn[0] - smq * 9) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset9_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset9_click = true;
                else if (preset9_click) {
                    channel = 8;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset9_click = false;
                }
            }
            else
                preset9_hover = false;
            if (ypos > converty(synthMenuDdn[0] - smq * 9) && ypos < converty(synthMenuDdn[0] - smq * 10) && xpos > convertx(synthMenuDdn[2]) && xpos < convertx(synthMenuDdn[3]))
            {
                preset10_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    preset10_click = true;
                else if (preset10_click) {
                    channel = 9;
                    loadWave(channel);
                    loadEnvelope(channel);
                    preset10_click = false;
                }
            }
            else
                preset10_hover = false;
        }
    }
    else {
        symn_hover = false;
        preset1_hover = false; preset2_hover = false; preset3_hover = false; preset4_hover = false; preset5_hover = false;
        preset6_hover = false; preset7_hover = false; preset8_hover = false; preset9_hover = false; preset10_hover = false;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            symn_engaged = false;
    }

    //ENV
    if (ypos > converty(env[0]) && ypos < converty(env[1]) && xpos > convertx(env[2]) && xpos < convertx(env[3])) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            env1 = true;
    }
    else if (env1)
        if (ypos > converty(wave[0]) && ypos < converty(wave[1]) && xpos > convertx(wave[2]) && xpos < convertx(wave[3]))
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                env1 = false;
    if (ypos > converty(env[4]) && ypos < converty(env[5]) && xpos > convertx(env[6]) && xpos < convertx(env[7])) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            env2 = true;
    }
    else if (env2)
        if (ypos > converty(wave[4]) && ypos < converty(wave[5]) && xpos > convertx(wave[6]) && xpos < convertx(wave[7]))
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                env2 = false;
    if (ypos > converty(env[8]) && ypos < converty(env[9]) && xpos > convertx(env[10]) && xpos < convertx(env[11])) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            env3 = true;
    }
    else if (env3)
        if (ypos > converty(wave[8]) && ypos < converty(wave[9]) && xpos > convertx(wave[10]) && xpos < convertx(wave[11]))
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                env3 = false;

    //WAVE DROPDOWNS
    if (env1) {
        vecInstruments[channel].env1.setAttackTime((atk1Mod + 0.15) * 5);
        vecInstruments[channel].env1.setDecayTime((dec1Mod + 0.15) * 5);
        vecInstruments[channel].env1.setSustainAmplitude(sus1Mod* (100 / 52));
        vecInstruments[channel].env1.setReleaseTime((rel1Mod + 0.15)* (100 / 15));
        if (ypos > converty(atk1TriTop[1]) && ypos < converty(atk1TriTop[7])
            && xpos > convertx(atk1TriTop[6]) && xpos < convertx(atk1TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                atk1Top_click = true;
            else if (atk1Top_click) {
                if(atk1Mod < 0.05)
                    atk1Mod += 0.025;
                atk1Top_click = false;
            }
        }
        if (ypos < converty(atk1TriBtm[1]) && ypos > converty(atk1TriBtm[7])
            && xpos > convertx(atk1TriBtm[6]) && xpos < convertx(atk1TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                atk1Btm_click = true;
            else if (atk1Btm_click) {
                if(atk1Mod > -0.125)
                    atk1Mod -= 0.025;
                atk1Btm_click = false;
            }
        }
        if (ypos > converty(dec1TriTop[1]) && ypos < converty(dec1TriTop[7])
            && xpos > convertx(dec1TriTop[6]) && xpos < convertx(dec1TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                dec1Top_click = true;
            else if (dec1Top_click) {
                if(dec1Mod < 0.05)
                    dec1Mod += 0.025;
                dec1Top_click = false;
            }
        }
        if (ypos < converty(dec1TriBtm[1]) && ypos > converty(dec1TriBtm[7])
            && xpos > convertx(dec1TriBtm[6]) && xpos < convertx(dec1TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                dec1Btm_click = true;
            else if (dec1Btm_click) {
                if(dec1Mod > -0.125)
                    dec1Mod -= 0.025;
                dec1Btm_click = false;
            }
        }
        if (ypos > converty(sus1TriTop[1]) && ypos < converty(sus1TriTop[7])
            && xpos < convertx(sus1TriTop[6]) && xpos > convertx(sus1TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus1Top_click = true;
            else if (sus1Top_click) {
                if(sus1Mod < 0.52)
                    sus1Mod += 0.025;
                sus1Top_click = false;
            }
        }
        if (ypos < converty(sus1TriBtm[1]) && ypos > converty(sus1TriBtm[7])
            && xpos < convertx(sus1TriBtm[6]) && xpos > convertx(sus1TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus1Btm_click = true;
            else if (sus1Btm_click) {
                if(sus1Mod > 0.025)
                    sus1Mod -= 0.025;
                sus1Btm_click = false;
            }
        }
        if (ypos > converty(rel1TriTop[1]) && ypos < converty(rel1TriTop[7])
            && xpos < convertx(rel1TriTop[6]) && xpos > convertx(rel1TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel1Top_click = true;
            else if (rel1Top_click) {
                if (rel1Mod < 0.0)
                    rel1Mod += 0.025;
                rel1Top_click = false;
            }
        }
        if (ypos < converty(rel1TriBtm[1]) && ypos > converty(rel1TriBtm[7])
            && xpos < convertx(rel1TriBtm[6]) && xpos > convertx(rel1TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel1Btm_click = true;
            else if (rel1Btm_click) {
                if (rel1Mod > -0.125)
                    rel1Mod -= 0.025;
                rel1Btm_click = false;
            }
        }

        if (ypos < converty(atk1box[7]) + atk1Mod && ypos > converty(atk1box[1]) + atk1Mod
            && xpos > convertx(atk1box[0]) + atk1Mod*(SCR_WIDTH/2) && xpos < convertx(atk1box[12]) + atk1Mod*(SCR_WIDTH/2) && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                atk1slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                atk1slider_hold = false;
            }
        }
        else if (atk1slider_hold) {
            float worldXPos = deconvertx(xpos);

            atk1Mod = worldXPos + 0.138889 + offset;
            atk1Mod = max(min(atk1Mod, 0.05), -0.15);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                atk1slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                atk1slider_hold = false; dec1slider_hold = false; rel1slider_hold = false;
            }
        }
        if (ypos < converty(dec1box[7])-sus1Mod*(SCR_HEIGHT/2) && ypos > converty(dec1box[1])-sus1Mod*(SCR_HEIGHT/2)
            && xpos > convertx(dec1box[0]) + dec1Mod*(SCR_WIDTH/2) + atk1Mod*(SCR_WIDTH/2) 
            && xpos < convertx(dec1box[12]) + dec1Mod*(SCR_WIDTH/2) + atk1Mod*(SCR_WIDTH/2) && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                dec1slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                dec1slider_hold = false;
            }
        }
        else if (dec1slider_hold) {
            float worldXPos = deconvertx(xpos);
            float worldYPos = deconverty(ypos);

            dec1Mod = worldXPos + offset - atk1Mod;
            sus1Mod = worldYPos - .25;
            dec1Mod = max(min(dec1Mod, 0.05), -0.15);
            sus1Mod = max(min(sus1Mod, 0.52), 0.0);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                dec1slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                dec1slider_hold = false;
            }
        }
        if (ypos < converty(rel1box[7]) && ypos > converty(rel1box[1])
            && xpos > convertx(rel1box[0]) + rel1Mod * (SCR_WIDTH / 2) && xpos < convertx(rel1box[12]) + rel1Mod * (SCR_WIDTH / 2) && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                rel1slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                rel1slider_hold = false;
            }
        }
        else if (rel1slider_hold) {
            float worldXPos = deconvertx(xpos);

            rel1Mod = worldXPos - 0.3 + offset;

            rel1Mod = max(min(rel1Mod, 0.00), -0.15);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                rel1slider_hold = true;
            }
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                rel1slider_hold = false;
            }
        }
    }
    else {
        //volume and octave sliders
        if (ypos > converty(sus1TriTop[1]) && ypos < converty(sus1TriTop[7])
            && xpos < convertx(sus1TriTop[6]) && xpos > convertx(sus1TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus1Top_click = true;
            else if (sus1Top_click) {
                if(vecInstruments[channel].getVolume(0) < 1.0)
                    vecInstruments[channel].setVolume(0, vecInstruments[channel].getVolume(0) + 0.1);
                sus1Top_click = false;
            }
        }
        if (ypos < converty(sus1TriBtm[1]) && ypos > converty(sus1TriBtm[7])
            && xpos < convertx(sus1TriBtm[6]) && xpos > convertx(sus1TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus1Btm_click = true;
            else if (sus1Btm_click) {
                if (vecInstruments[channel].getVolume(0) > 0.0)
                    vecInstruments[channel].setVolume(0, vecInstruments[channel].getVolume(0) - 0.1);
                sus1Btm_click = false;
            }
        }
        if (ypos > converty(rel1TriTop[1]) && ypos < converty(rel1TriTop[7])
            && xpos < convertx(rel1TriTop[6]) && xpos > convertx(rel1TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel1Top_click = true;
            else if (rel1Top_click) {
                vecInstruments[channel].setTranspose(0, vecInstruments[channel].getTranspose(0) + 1);
                rel1Top_click = false;
            }
        }
        if (ypos < converty(rel1TriBtm[1]) && ypos > converty(rel1TriBtm[7])
            && xpos < convertx(rel1TriBtm[6]) && xpos > convertx(rel1TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel1Btm_click = true;
            else if (rel1Btm_click) {
                vecInstruments[channel].setTranspose(0, vecInstruments[channel].getTranspose(0) - 1);
                rel1Btm_click = false;
            }
        }

        if (ypos > converty(waveSelect[0]) && ypos < converty(waveSelect[1]) && xpos > convertx(waveSelect[2]) && xpos < convertx(waveSelect[3]) && !(symn_engaged || symn_hover)) {
            wfm1_hover = true;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                wfm1_click = true;
            }
            else if (wfm1_click) {
                if (wfm1_engaged)
                    wfm1_engaged = false;
                else
                    wfm1_engaged = true;
                wfm1_click = false;
            }
        }
        else if (ypos > converty(waveSelectDdn[0]) && ypos < converty(waveSelectDdn[1]) && xpos > convertx(waveSelectDdn[2]) && xpos < convertx(waveSelectDdn[3])) {
            if (wfm1_engaged)
                wfm1_hover = true;
            if (wfm1_hover) {
                if (ypos > converty(waveSelectDdn[0]) && ypos < converty(waveSelectDdn[0] - wsmq) && xpos > convertx(waveSelectDdn[2]) && xpos < convertx(waveSelectDdn[3]))
                {
                    wfm1preset1_hover = true;
                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                        wfm1preset1_click = true;
                    else if (wfm1preset1_click) {
                        vecInstruments[channel].setOscillatorType(0, SINE);
                        loadMyTexture(osc_left_ch, "Text/text-select-sin.png");
                        wfm1preset1_click = false;
                    }
                }
                else
                    wfm1preset1_hover = false;
                if (ypos > converty(waveSelectDdn[0] - wsmq) && ypos < converty(waveSelectDdn[0] - wsmq * 2) && xpos > convertx(waveSelectDdn[2]) && xpos < convertx(waveSelectDdn[3]))
                {
                    wfm1preset2_hover = true;
                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                        wfm1preset2_click = true;
                    else if (wfm1preset2_click) {
                        vecInstruments[channel].setOscillatorType(0, TRIANGLE);
                        loadMyTexture(osc_left_ch, "Text/text-select-tri.png");
                        wfm1preset2_click = false;
                    }
                }
                else
                    wfm1preset2_hover = false;
                if (ypos > converty(waveSelectDdn[0] - wsmq * 2) && ypos < converty(waveSelectDdn[0] - wsmq * 3) && xpos > convertx(waveSelectDdn[2]) && xpos < convertx(waveSelectDdn[3]))
                {
                    wfm1preset3_hover = true;
                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                        wfm1preset3_click = true;
                    else if (wfm1preset3_click) {
                        vecInstruments[channel].setOscillatorType(0, SAW_ANALOG);
                        loadMyTexture(osc_left_ch, "Text/text-select-swa.png");
                        wfm1preset3_click = false;
                    }
                }
                else
                    wfm1preset3_hover = false;
                if (ypos > converty(waveSelectDdn[0] - wsmq * 3) && ypos < converty(waveSelectDdn[0] - wsmq * 4) && xpos > convertx(waveSelectDdn[2]) && xpos < convertx(waveSelectDdn[3]))
                {
                    wfm1preset4_hover = true;
                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                        wfm1preset4_click = true;
                    else if (wfm1preset4_click) {
                        vecInstruments[channel].setOscillatorType(0, SAW_DIGITAL);
                        loadMyTexture(osc_left_ch, "Text/text-select-swd.png");
                        wfm1preset4_click = false;
                    }
                }
                else
                    wfm1preset4_hover = false;
                if (ypos > converty(waveSelectDdn[0] - wsmq * 4) && ypos < converty(waveSelectDdn[0] - wsmq * 5) && xpos > convertx(waveSelectDdn[2]) && xpos < convertx(waveSelectDdn[3]))
                {
                    wfm1preset5_hover = true;
                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                        wfm1preset5_click = true;
                    else if (wfm1preset5_click) {
                        vecInstruments[channel].setOscillatorType(0, SQUARE);
                        loadMyTexture(osc_left_ch, "Text/text-select-sqa.png");
                        wfm1preset5_click = false;
                    }
                }
                else
                    wfm1preset5_hover = false;
                if (ypos > converty(waveSelectDdn[0] - wsmq * 5) && ypos < converty(waveSelectDdn[0] - wsmq * 6) && xpos > convertx(waveSelectDdn[2]) && xpos < convertx(waveSelectDdn[3]))
                {
                    wfm1preset6_hover = true;
                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                        wfm1preset6_click = true;
                    else if (wfm1preset6_click) {
                        vecInstruments[channel].setOscillatorType(0, PULSE);
                        loadMyTexture(osc_left_ch, "Text/text-select-pls.png");
                        wfm1preset6_click = false;
                    }
                }
                else
                    wfm1preset6_hover = false;
                if (ypos > converty(waveSelectDdn[0] - wsmq * 6) && ypos < converty(waveSelectDdn[0] - wsmq * 7) && xpos > convertx(waveSelectDdn[2]) && xpos < convertx(waveSelectDdn[3]))
                {
                    wfm1preset7_hover = true;
                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                        wfm1preset7_click = true;
                    else if (wfm1preset7_click) {
                        vecInstruments[channel].setOscillatorType(0, WHITE_NOISE);
                        loadMyTexture(osc_left_ch, "Text/text-select-wns.png");
                        wfm1preset7_click = false;
                    }
                }
                else
                    wfm1preset7_hover = false;
            }
        }
        else {
            wfm1_hover = false;
            wfm1preset1_hover = false; wfm1preset2_hover = false; wfm1preset3_hover = false; wfm1preset4_hover = false;
            wfm1preset5_hover = false; wfm1preset6_hover = false; wfm1preset7_hover = false;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                wfm1_engaged = false;
        }
    }
    if (env2) {
        vecInstruments[channel].env2.setAttackTime((atk2Mod + 0.15) * 5);
        vecInstruments[channel].env2.setDecayTime((dec2Mod + 0.15) * 5);
        vecInstruments[channel].env2.setSustainAmplitude(sus2Mod* (100 / 52));
        vecInstruments[channel].env2.setReleaseTime((rel2Mod + 0.15)* (100 / 15));
        if (ypos > converty(atk2TriTop[1]) && ypos < converty(atk2TriTop[7])
            && xpos > convertx(atk2TriTop[6]) && xpos < convertx(atk2TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                atk2Top_click = true;
            else if (atk2Top_click) {
                if (atk2Mod < 0.05)
                    atk2Mod += 0.025;
                atk2Top_click = false;
            }
        }
        if (ypos < converty(atk2TriBtm[1]) && ypos > converty(atk2TriBtm[7])
            && xpos > convertx(atk2TriBtm[6]) && xpos < convertx(atk2TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                atk2Btm_click = true;
            else if (atk2Btm_click) {
                if (atk2Mod > -0.125)
                    atk2Mod -= 0.025;
                atk2Btm_click = false;
            }
        }
        if (ypos > converty(dec2TriTop[1]) && ypos < converty(dec2TriTop[7])
            && xpos > convertx(dec2TriTop[6]) && xpos < convertx(dec2TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                dec2Top_click = true;
            else if (dec2Top_click) {
                if (dec2Mod < 0.05)
                    dec2Mod += 0.025;
                dec2Top_click = false;
            }
        }
        if (ypos < converty(dec2TriBtm[1]) && ypos > converty(dec2TriBtm[7])
            && xpos > convertx(dec2TriBtm[6]) && xpos < convertx(dec2TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                dec2Btm_click = true;
            else if (dec2Btm_click) {
                if (dec2Mod > -0.125)
                    dec2Mod -= 0.025;
                dec2Btm_click = false;
            }
        }
        if (ypos > converty(sus2TriTop[1]) && ypos < converty(sus2TriTop[7])
            && xpos < convertx(sus2TriTop[6]) && xpos > convertx(sus2TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus2Top_click = true;
            else if (sus2Top_click) {
                if (sus2Mod < 0.52)
                    sus2Mod += 0.025;
                sus2Top_click = false;
            }
        }
        if (ypos < converty(sus2TriBtm[1]) && ypos > converty(sus2TriBtm[7])
            && xpos < convertx(sus2TriBtm[6]) && xpos > convertx(sus2TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus2Btm_click = true;
            else if (sus2Btm_click) {
                if (sus2Mod > 0.025)
                    sus2Mod -= 0.025;
                sus2Btm_click = false;
            }
        }
        if (ypos > converty(rel2TriTop[1]) && ypos < converty(rel2TriTop[7])
            && xpos < convertx(rel2TriTop[6]) && xpos > convertx(rel2TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel2Top_click = true;
            else if (rel2Top_click) {
                if (rel2Mod < 0.0)
                    rel2Mod += 0.025;
                rel2Top_click = false;
            }
        }
        if (ypos < converty(rel2TriBtm[1]) && ypos > converty(rel2TriBtm[7])
            && xpos < convertx(rel2TriBtm[6]) && xpos > convertx(rel2TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel2Btm_click = true;
            else if (rel2Btm_click) {
                if (rel2Mod > -0.125)
                    rel2Mod -= 0.025;
                rel2Btm_click = false;
            }
        }

        if (ypos < converty(atk2box[7]) + atk2Mod && ypos > converty(atk2box[1]) + atk2Mod
            && xpos > convertx(atk2box[0]) + atk2Mod*(SCR_WIDTH/2) 
            && xpos < convertx(atk2box[12]) + atk2Mod*(SCR_WIDTH/2) && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                atk2slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                atk2slider_hold = false;
            }
        }
        else if (atk2slider_hold) {
            float worldXPos = deconvertx(xpos);

            atk2Mod = worldXPos + 0.138889;
            atk2Mod = max(min(atk2Mod, 0.05), -0.15);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                atk2slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                atk2slider_hold = false;
            }
        }
        if (ypos < converty(dec2box[7]) + dec2Mod- sus2Mod*(SCR_HEIGHT/2) && ypos > converty(dec2box[1]) + dec2Mod- sus2Mod*(SCR_HEIGHT/2)
            && xpos > convertx(dec2box[0]) + dec2Mod*(SCR_WIDTH/2) + atk2Mod*(SCR_WIDTH/2)  
            && xpos < convertx(dec2box[12]) + dec2Mod*(SCR_WIDTH/2) + atk2Mod*(SCR_WIDTH/2)  && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                dec2slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                dec2slider_hold = false;
            }
        }
        else if (dec2slider_hold) {
            float worldXPos = deconvertx(xpos);
            float worldYPos = deconverty(ypos);

            dec2Mod = worldXPos - atk2Mod;
            sus2Mod = worldYPos - .25;

            dec2Mod = max(min(dec2Mod, 0.05), -0.15);
            sus2Mod = max(min(sus2Mod, 0.52), 0.0);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                dec2slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                dec2slider_hold = false;
            }
        }
        if (ypos < converty(rel2box[7]) && ypos > converty(rel2box[1])
            && xpos > convertx(rel2box[0]) + rel2Mod * (SCR_WIDTH / 2) && xpos < convertx(rel2box[12]) + rel2Mod * (SCR_WIDTH / 2) && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                rel2slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                rel2slider_hold = false;
            }
        }
        else if (rel2slider_hold) {
            float worldXPos = deconvertx(xpos);

            rel2Mod = worldXPos - 0.3;

            rel2Mod = max(min(rel2Mod, 0.00), -0.15);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                rel2slider_hold = true;
            }
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                rel2slider_hold = false;
            }
        }
    }
    else {
        if (ypos > converty(sus2TriTop[1]) && ypos < converty(sus2TriTop[7])
            && xpos < convertx(sus2TriTop[6]) && xpos > convertx(sus2TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus2Top_click = true;
            else if (sus2Top_click) {
                if (vecInstruments[channel].getVolume(1) < 1.0)
                    vecInstruments[channel].setVolume(1, vecInstruments[channel].getVolume(1) + 0.1);
                sus2Top_click = false;
            }
        }
        if (ypos < converty(sus2TriBtm[1]) && ypos > converty(sus2TriBtm[7])
            && xpos < convertx(sus2TriBtm[6]) && xpos > convertx(sus2TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus2Btm_click = true;
            else if (sus2Btm_click) {
                if (vecInstruments[channel].getVolume(1) > 0.0)
                    vecInstruments[channel].setVolume(1, vecInstruments[channel].getVolume(1) - 0.1);
                sus2Btm_click = false;
            }
        }
        if (ypos > converty(rel2TriTop[1]) && ypos < converty(rel2TriTop[7])
            && xpos < convertx(rel2TriTop[6]) && xpos > convertx(rel2TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel2Top_click = true;
            else if (rel2Top_click) {
                vecInstruments[channel].setTranspose(1, vecInstruments[channel].getTranspose(1) + 1);
                rel2Top_click = false;
            }
        }
        if (ypos < converty(rel2TriBtm[1]) && ypos > converty(rel2TriBtm[7])
            && xpos < convertx(rel2TriBtm[6]) && xpos > convertx(rel2TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel2Btm_click = true;
            else if (rel2Btm_click) {
                vecInstruments[channel].setTranspose(1, vecInstruments[channel].getTranspose(1) - 1);
                rel2Btm_click = false;
            }
        }

        if (ypos > converty(waveSelect[4]) && ypos < converty(waveSelect[5]) && xpos > convertx(waveSelect[6]) && xpos < convertx(waveSelect[7]) && !symn_engaged) {
            wfm2_hover = true;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                wfm2_click = true;
            }
            else if (wfm2_click) {
                if (wfm2_engaged)
                    wfm2_engaged = false;
                else
                    wfm2_engaged = true;
                wfm2_click = false;
            }
        }
        else if (ypos > converty(waveSelectDdn[4]) && ypos < converty(waveSelectDdn[5]) && xpos > convertx(waveSelectDdn[6]) && xpos < convertx(waveSelectDdn[7])) {
            if (wfm2_engaged)
                wfm2_hover = true;

            if (ypos > converty(waveSelectDdn[4]) && ypos < converty(waveSelectDdn[4] - wsmq) && xpos > convertx(waveSelectDdn[6]) && xpos < convertx(waveSelectDdn[7]))
            {
                wfm2preset1_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm2preset1_click = true;
                else if (wfm2preset1_click) {
                    vecInstruments[channel].setOscillatorType(1, SINE);
                    loadMyTexture(osc_midl_ch, "Text/text-select-sin.png");
                    wfm2preset1_click = false;
                }
            }else
                wfm2preset1_hover = false;
            if (ypos > converty(waveSelectDdn[4] - wsmq) && ypos < converty(waveSelectDdn[4] - wsmq * 2) && xpos > convertx(waveSelectDdn[6]) && xpos < convertx(waveSelectDdn[7]))
            {
                wfm2preset2_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm2preset2_click = true;
                else if (wfm2preset2_click) {
                    vecInstruments[channel].setOscillatorType(1, TRIANGLE);
                    loadMyTexture(osc_midl_ch, "Text/text-select-tri.png");
                    wfm2preset2_click = false;
                }
            }else
                wfm2preset2_hover = false;
            if (ypos > converty(waveSelectDdn[4] - wsmq * 2) && ypos < converty(waveSelectDdn[4] - wsmq * 3) && xpos > convertx(waveSelectDdn[6]) && xpos < convertx(waveSelectDdn[7]))
            {
                wfm2preset3_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm2preset3_click = true;
                else if (wfm2preset3_click) {
                    vecInstruments[channel].setOscillatorType(1, SAW_ANALOG);
                    loadMyTexture(osc_midl_ch, "Text/text-select-swa.png");
                    wfm2preset3_click = false;
                }
            }else
                wfm2preset3_hover = false;
            if (ypos > converty(waveSelectDdn[4] - wsmq * 3) && ypos < converty(waveSelectDdn[4] - wsmq * 4) && xpos > convertx(waveSelectDdn[6]) && xpos < convertx(waveSelectDdn[7]))
            {
                wfm2preset4_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm2preset4_click = true;
                else if (wfm2preset4_click) {
                    vecInstruments[channel].setOscillatorType(1, SAW_DIGITAL);
                    loadMyTexture(osc_midl_ch, "Text/text-select-swd.png");
                    wfm2preset4_click = false;
                }
            }else
                wfm2preset4_hover = false;
            if (ypos > converty(waveSelectDdn[4] - wsmq * 4) && ypos < converty(waveSelectDdn[4] - wsmq * 5) && xpos > convertx(waveSelectDdn[6]) && xpos < convertx(waveSelectDdn[7]))
            {
                wfm2preset5_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm2preset5_click = true;
                else if (wfm2preset5_click) {
                    vecInstruments[channel].setOscillatorType(1, SQUARE);
                    loadMyTexture(osc_midl_ch, "Text/text-select-sqa.png");
                    wfm2preset5_click = false;
                }
            }else
                wfm2preset5_hover = false;
            if (ypos > converty(waveSelectDdn[4] - wsmq * 5) && ypos < converty(waveSelectDdn[4] - wsmq * 6) && xpos > convertx(waveSelectDdn[6]) && xpos < convertx(waveSelectDdn[7]))
            {
                wfm2preset6_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm2preset6_click = true;
                else if (wfm2preset6_click) {
                    vecInstruments[channel].setOscillatorType(1, PULSE);
                    loadMyTexture(osc_midl_ch, "Text/text-select-pls.png");
                    wfm2preset6_click = false;
                }
            }else
                wfm2preset6_hover = false;
            if (ypos > converty(waveSelectDdn[4] - wsmq * 6) && ypos < converty(waveSelectDdn[4] - wsmq * 7) && xpos > convertx(waveSelectDdn[6]) && xpos < convertx(waveSelectDdn[7]))
            {
                wfm2preset7_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm2preset7_click = true;
                else if (wfm2preset7_click) {
                    vecInstruments[channel].setOscillatorType(1, WHITE_NOISE);
                    loadMyTexture(osc_midl_ch, "Text/text-select-wns.png");
                    wfm2preset7_click = false;
                }
            }else
                wfm2preset7_hover = false;
        }
        else {
            wfm2_hover = false;
            wfm2preset1_hover = false; wfm2preset2_hover = false; wfm2preset3_hover = false; wfm2preset4_hover = false;
            wfm2preset5_hover = false; wfm2preset6_hover = false; wfm2preset7_hover = false;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                wfm2_engaged = false;
        }
    }
    if (env3) {
        vecInstruments[channel].env3.setAttackTime((atk3Mod + 0.15) * 5);
        vecInstruments[channel].env3.setDecayTime((dec3Mod + 0.15) * 5);
        vecInstruments[channel].env3.setSustainAmplitude(sus3Mod* (100 / 52));
        vecInstruments[channel].env3.setReleaseTime((rel3Mod + 0.15)* (100 / 15));
        if (ypos > converty(atk3TriTop[1]) && ypos < converty(atk3TriTop[7])
            && xpos > convertx(atk3TriTop[6]) && xpos < convertx(atk3TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                atk3Top_click = true;
            else if (atk3Top_click) {
                if (atk3Mod < 0.05)
                    atk3Mod += 0.025;
                atk3Top_click = false;
            }
        }
        if (ypos < converty(atk3TriBtm[1]) && ypos > converty(atk3TriBtm[7])
            && xpos > convertx(atk3TriBtm[6]) && xpos < convertx(atk3TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                atk3Btm_click = true;
            else if (atk3Btm_click) {
                if (atk3Mod > -0.125)
                    atk3Mod -= 0.025;
                atk3Btm_click = false;
            }
        }
        if (ypos > converty(dec3TriTop[1]) && ypos < converty(dec3TriTop[7])
            && xpos > convertx(dec3TriTop[6]) && xpos < convertx(dec3TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                dec3Top_click = true;
            else if (dec3Top_click) {
                if (dec3Mod < 0.05)
                    dec3Mod += 0.025;
                dec3Top_click = false;
            }
        }
        if (ypos < converty(dec3TriBtm[1]) && ypos > converty(dec3TriBtm[7])
            && xpos > convertx(dec3TriBtm[6]) && xpos < convertx(dec3TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                dec3Btm_click = true;
            else if (dec3Btm_click) {
                if (dec3Mod > -0.125)
                    dec3Mod -= 0.025;
                dec3Btm_click = false;
            }
        }
        if (ypos > converty(sus3TriTop[1]) && ypos < converty(sus3TriTop[7])
            && xpos < convertx(sus3TriTop[6]) && xpos > convertx(sus3TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus3Top_click = true;
            else if (sus3Top_click) {
                if (sus3Mod < 0.52)
                    sus3Mod += 0.025;
                sus3Top_click = false;
            }
        }
        if (ypos < converty(sus3TriBtm[1]) && ypos > converty(sus3TriBtm[7])
            && xpos < convertx(sus3TriBtm[6]) && xpos > convertx(sus3TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus3Btm_click = true;
            else if (sus3Btm_click) {
                if (sus3Mod > 0.025)
                    sus3Mod -= 0.025;
                sus3Btm_click = false;
            }
        }
        if (ypos > converty(rel3TriTop[1]) && ypos < converty(rel3TriTop[7])
            && xpos < convertx(rel3TriTop[6]) && xpos > convertx(rel3TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel3Top_click = true;
            else if (rel3Top_click) {
                if (rel3Mod < 0.0)
                    rel3Mod += 0.025;
                rel3Top_click = false;
            }
        }
        if (ypos < converty(rel3TriBtm[1]) && ypos > converty(rel3TriBtm[7])
            && xpos < convertx(rel3TriBtm[6]) && xpos > convertx(rel3TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel3Btm_click = true;
            else if (rel3Btm_click) {
                if (rel3Mod > -0.125)
                    rel3Mod -= 0.025;
                rel3Btm_click = false;
            }
        }
        if (ypos < converty(atk3box[7]) && ypos > converty(atk3box[1])
            && xpos > convertx(atk3box[0]) + atk3Mod*(SCR_WIDTH/2) && xpos < convertx(atk3box[12]) + atk3Mod*(SCR_WIDTH/2) && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                atk3slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                atk3slider_hold = false;
            }
        }
        else if (atk3slider_hold) {
            float worldXPos = deconvertx(xpos);
            atk3Mod = worldXPos + 0.138889 - offset;
            atk3Mod = max(min(atk3Mod, 0.05),-0.15);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                atk3slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                atk3slider_hold = false;
            }
        }
        if (ypos < converty(dec3box[7]) - sus3Mod*(SCR_HEIGHT/2) && ypos > converty(dec3box[1]) - sus3Mod*(SCR_HEIGHT/2)
            && xpos > convertx(dec3box[0]) + dec3Mod*(SCR_WIDTH/2) + atk3Mod*(SCR_WIDTH/2) 
            && xpos < convertx(dec3box[12]) + dec3Mod*(SCR_WIDTH/2) + atk3Mod*(SCR_WIDTH/2) && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                dec3slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                dec3slider_hold = false;
            }
        }
        else if (dec3slider_hold) {
            float worldXPos = deconvertx(xpos);
            float worldYPos = deconverty(ypos);

            dec3Mod = worldXPos - offset - atk3Mod;
            sus3Mod = worldYPos - .25;

            dec3Mod = max(min(dec3Mod, 0.05), -0.15);
            sus3Mod = max(min(sus3Mod, 0.52), 0.0);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                dec3slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                dec3slider_hold = false;
            }
        }
        if (ypos < converty(rel3box[7]) && ypos > converty(rel3box[1])
            && xpos > convertx(rel3box[0]) + rel3Mod*(SCR_WIDTH/2) && xpos < convertx(rel3box[12]) + rel3Mod*(SCR_WIDTH/2) && !symn_engaged) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                rel3slider_hold = true;
            }
            else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                rel3slider_hold = false;
            }
        }
        else if (rel3slider_hold) {
            float worldXPos = deconvertx(xpos);

            rel3Mod = worldXPos - 0.3 - offset;

            rel3Mod = max(min(rel3Mod, 0.00), -0.15);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                rel3slider_hold = true;
            }
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                rel3slider_hold = false;
            }
        }
    }
    else {
        if (ypos > converty(sus3TriTop[1]) && ypos < converty(sus3TriTop[7])
            && xpos < convertx(sus3TriTop[6]) && xpos > convertx(sus3TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus3Top_click = true;
            else if (sus3Top_click) {
                if (vecInstruments[channel].getVolume(2) < 1.0)
                    vecInstruments[channel].setVolume(2, vecInstruments[channel].getVolume(2) + 0.1);
                sus3Top_click = false;
            }
        }
        if (ypos < converty(sus3TriBtm[1]) && ypos > converty(sus3TriBtm[7])
            && xpos < convertx(sus3TriBtm[6]) && xpos > convertx(sus3TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                sus3Btm_click = true;
            else if (sus3Btm_click) {
                if (vecInstruments[channel].getVolume(2) > 0.0)
                    vecInstruments[channel].setVolume(2, vecInstruments[channel].getVolume(2) - 0.1);
                sus3Btm_click = false;
            }
        }
        if (ypos > converty(rel3TriTop[1]) && ypos < converty(rel3TriTop[7])
            && xpos < convertx(rel3TriTop[6]) && xpos > convertx(rel3TriTop[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel3Top_click = true;
            else if (rel3Top_click) {
                vecInstruments[channel].setTranspose(2, vecInstruments[channel].getTranspose(2) + 1);
                rel3Top_click = false;
            }
        }
        if (ypos < converty(rel3TriBtm[1]) && ypos > converty(rel3TriBtm[7])
            && xpos < convertx(rel3TriBtm[6]) && xpos > convertx(rel3TriBtm[12])) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                rel3Btm_click = true;
            else if (rel3Btm_click) {
                vecInstruments[channel].setTranspose(2, vecInstruments[channel].getTranspose(2) - 1);
                rel3Btm_click = false;
            }
        }

        if (ypos > converty(waveSelect[8]) && ypos < converty(waveSelect[9]) && xpos > convertx(waveSelect[10]) && xpos < convertx(waveSelect[11]) && !symn_engaged) {
            wfm3_hover = true;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                wfm3_click = true;
            }
            else if (wfm3_click) {
                if (wfm3_engaged)
                    wfm3_engaged = false;
                else
                    wfm3_engaged = true;
                wfm3_click = false;
            }
        }
        else if (ypos > converty(waveSelectDdn[8]) && ypos < converty(waveSelectDdn[9]) && xpos > convertx(waveSelectDdn[10]) && xpos < convertx(waveSelectDdn[11])) {
            if (wfm3_engaged)
                wfm3_hover = true;

            if (ypos > converty(waveSelectDdn[8]) && ypos < converty(waveSelectDdn[8] - wsmq) && xpos > convertx(waveSelectDdn[10]) && xpos < convertx(waveSelectDdn[11]))
            {
                wfm3preset1_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm3preset1_click = true;
                else if (wfm3preset1_click) {
                    vecInstruments[channel].setOscillatorType(2, SINE);
                    loadMyTexture(osc_rght_ch, "Text/text-select-sin.png");
                    wfm3preset1_click = false;
                }
            }else
                wfm3preset1_hover = false;
            if (ypos > converty(waveSelectDdn[8] - wsmq) && ypos < converty(waveSelectDdn[8] - wsmq * 2) && xpos > convertx(waveSelectDdn[10]) && xpos < convertx(waveSelectDdn[11]))
            {
                wfm3preset2_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm3preset2_click = true;
                else if (wfm3preset2_click) {
                    vecInstruments[channel].setOscillatorType(2, TRIANGLE);
                    loadMyTexture(osc_rght_ch, "Text/text-select-tri.png");
                    wfm3preset2_click = false;
                }
            }else
                wfm3preset2_hover = false;
            if (ypos > converty(waveSelectDdn[8] - wsmq * 2) && ypos < converty(waveSelectDdn[8] - wsmq * 3) && xpos > convertx(waveSelectDdn[10]) && xpos < convertx(waveSelectDdn[11]))
            {
                wfm3preset3_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm3preset3_click = true;
                else if (wfm3preset3_click) {
                    vecInstruments[channel].setOscillatorType(2, SAW_ANALOG);
                    loadMyTexture(osc_rght_ch, "Text/text-select-swa.png");
                    wfm3preset3_click = false;
                }
            }else
                wfm3preset3_hover = false;
            if (ypos > converty(waveSelectDdn[8] - wsmq * 3) && ypos < converty(waveSelectDdn[8] - wsmq * 4) && xpos > convertx(waveSelectDdn[10]) && xpos < convertx(waveSelectDdn[11]))
            {
                wfm3preset4_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm3preset4_click = true;
                else if (wfm3preset4_click) {
                    vecInstruments[channel].setOscillatorType(2, SAW_DIGITAL);
                    loadMyTexture(osc_rght_ch, "Text/text-select-swd.png");
                    wfm3preset4_click = false;
                }
            }else
                wfm3preset4_hover = false;
            if (ypos > converty(waveSelectDdn[8] - wsmq * 4) && ypos < converty(waveSelectDdn[8] - wsmq * 5) && xpos > convertx(waveSelectDdn[10]) && xpos < convertx(waveSelectDdn[11]))
            {
                wfm3preset5_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm3preset5_click = true;
                else if (wfm3preset5_click) {
                    vecInstruments[channel].setOscillatorType(2, SQUARE);
                    loadMyTexture(osc_rght_ch, "Text/text-select-sqa.png");
                    wfm3preset5_click = false;
                }
            }else
                wfm3preset5_hover = false;
            if (ypos > converty(waveSelectDdn[8] - wsmq * 5) && ypos < converty(waveSelectDdn[8] - wsmq * 6) && xpos > convertx(waveSelectDdn[10]) && xpos < convertx(waveSelectDdn[11]))
            {
                wfm3preset6_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm3preset6_click = true;
                else if (wfm3preset6_click) {
                    vecInstruments[channel].setOscillatorType(2, PULSE);
                    loadMyTexture(osc_rght_ch, "Text/text-select-pls.png");
                    wfm3preset6_click = false;
                }
            }else
                wfm3preset6_hover = false;
            if (ypos > converty(waveSelectDdn[8] - wsmq * 6) && ypos < converty(waveSelectDdn[8] - wsmq * 7) && xpos > convertx(waveSelectDdn[10]) && xpos < convertx(waveSelectDdn[11]))
            {
                wfm3preset7_hover = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                    wfm3preset7_click = true;
                else if (wfm3preset7_click) {
                    vecInstruments[channel].setOscillatorType(2, WHITE_NOISE);
                    loadMyTexture(osc_rght_ch, "Text/text-select-wns.png");
                    wfm3preset7_click = false;
                }
            }else
                wfm3preset7_hover = false;
        }
        else {
            wfm3_hover = false;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                wfm3_engaged = false;
        }
    }

    // OSC ON / OFF
    if (ypos > converty(osc_name_left[1]) && ypos < converty(osc_name_left[7])
        && xpos > convertx(osc_name_left[6]) && xpos < convertx(osc_name_left[12]) && !symn_hover && !atk1slider_hold) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            osc1on_click = true;
        else if (osc1on_click) {
            vecInstruments[channel].setActive(0, !vecInstruments[channel].getActive(0));
            osc1on_click = false;
        }
    }
    if (ypos > converty(osc_name_midl[1]) && ypos < converty(osc_name_midl[7])
        && xpos > convertx(osc_name_midl[6]) && xpos < convertx(osc_name_midl[12]) && !atk2slider_hold) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            osc2on_click = true;
        else if (osc2on_click) {
            vecInstruments[channel].setActive(1, !vecInstruments[channel].getActive(1));
            osc2on_click = false;
        }
    }
    if (ypos > converty(osc_name_rght[1]) && ypos < converty(osc_name_rght[7])
        && xpos > convertx(osc_name_rght[6]) && xpos < convertx(osc_name_rght[12]) && !atk3slider_hold) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            osc3on_click = true;
        else if (osc3on_click) {
            vecInstruments[channel].setActive(2, !vecInstruments[channel].getActive(2));
            osc3on_click = false;
        }
    }

    // XPRESSED / ZPRESSED
    if (!symn_engaged && !symn_hover && !wfm1_engaged && !wfm1_hover && !wfm1_click) {
        if (ypos < converty(z_left[13]) && ypos > converty(z_left[7]) && xpos > convertx(z_left[0]) && xpos < convertx(z_left[6])) {
            z_hover = true;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                z_click = true;
        }
        else if (z_click) {
            octave -= 1;
            z_click = false;
        }
        else {
            z_hover = false;
        }
        if (ypos < converty(z_right[13]) && ypos > converty(z_right[1]) && xpos > convertx(z_right[0]) && xpos < convertx(z_right[12])) {
            x_hover = true;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                x_click = true;
        }
        else if (x_click) {
            octave += 1;
            x_click = false;
        }
        else {
            x_hover = false;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void loadSynths() {
    for (int i = 0; i < 3; ++i) {
        preset1.setActive(i, true);
        preset1.setOscillatorType(i, SQUARE);
    }
    preset1.setVolume(0, 1.00);
    preset1.setVolume(1, 0.50);
    preset1.setVolume(2, 0.25);
    preset1.setTranspose(0, 0);
    preset1.setTranspose(1, 12);
    preset1.setTranspose(2, 24);
    preset1.setLFOHertz(0, 5.0);
    preset1.setLFOAmplitude(0, 0.001);
    preset1.setName("Harmonica");

    for (int i = 0; i < 3; ++i) {
        preset2.setActive(i, true);
    }
    preset2.setVolume(0, 1.00);
    preset2.setVolume(1, 0.50);
    preset2.setVolume(2, 0.25);
    preset2.setTranspose(0, 12);
    preset2.setTranspose(1, 24);
    preset2.setTranspose(2, 36);
    preset2.setName("Bell");

    preset2.env1.setAttackTime(0.01);
    preset2.env1.setDecayTime(1.0);
    preset2.env1.setSustainAmplitude(0.0);
    preset2.env1.setReleaseTime(1.0);
    preset2.env2.setAttackTime(0.01);
    preset2.env2.setDecayTime(1.0);
    preset2.env2.setSustainAmplitude(0.0);
    preset2.env2.setReleaseTime(1.0);
    preset2.env3.setAttackTime(0.01);
    preset2.env3.setDecayTime(1.0);
    preset2.env3.setSustainAmplitude(0.0);
    preset2.env3.setReleaseTime(1.0);

    for (int i = 0; i < 2; ++i) {
        preset3.setActive(i, true);
        preset3.setOscillatorType(i, TRIANGLE);
    }
    preset3.setOscillatorType(2, WHITE_NOISE);
    preset3.setName("Triangle Pluck");
    preset3.setVolume(0, 1.00);
    preset3.setVolume(1, 1.00);
    preset3.setVolume(2, 1.00);
    preset3.setTranspose(0, 0);
    preset3.setTranspose(1, 12);
    preset3.setTranspose(2, 12);
    preset3.setLFOHertz(0, 5.0);
    preset3.setLFOAmplitude(0, 0.001);
    preset3.env1.setAttackTime(0.05);
    preset3.env1.setDecayTime(0.4);
    preset3.env1.setSustainAmplitude(0.0);
    preset3.env1.setReleaseTime(0.4);
    preset3.env2.setAttackTime(0.05);
    preset3.env2.setDecayTime(0.2);
    preset3.env2.setSustainAmplitude(0.0);
    preset3.env2.setReleaseTime(0.2);
    preset3.env3.setAttackTime(0.05);
    preset3.env3.setDecayTime(0.1);
    preset3.env3.setSustainAmplitude(0.0);
    preset3.env3.setReleaseTime(0.2);
    
    for (int i = 0; i < 3; ++i) {
        preset4.setActive(i, true);
        preset4.setOscillatorType(i, SAW_ANALOG);
    }
    preset4.setName("SuperSaw");
    preset4.setVolume(0, 1.00);
    preset4.setVolume(1, 0.75);
    preset4.setVolume(2, 0.50);
    preset4.setTranspose(0, 0);
    preset4.setTranspose(1, 12);
    preset4.setTranspose(2, 24);
    preset4.setDetune(1, 0.05);
    preset4.setDetune(2, 0.05);


    vecInstruments.push_back(preset1);
    vecInstruments.push_back(preset2);
    vecInstruments.push_back(preset3);
    vecInstruments.push_back(preset4);
    vecInstruments.push_back(preset5);
    vecInstruments.push_back(preset6);
    vecInstruments.push_back(preset7);
    vecInstruments.push_back(preset8);
    vecInstruments.push_back(preset9);
    vecInstruments.push_back(preset10);

    for (int i = 4; i < 10; ++i) {
        vecInstruments[i].setActive(0, true);
        vecInstruments[i].setActive(1, false);
        vecInstruments[i].setActive(2, false);
        vecInstruments[i].setVolume(0, 1.00);
        vecInstruments[i].setVolume(1, 0.00);
        vecInstruments[i].setVolume(2, 0.00);
    }
    vecInstruments[5].setOscillatorType(0, SAW_DIGITAL);
    vecInstruments[5].setTranspose(0, -12);
    vecInstruments[6].setOscillatorType(0, WHITE_NOISE);
    vecInstruments[7].setOscillatorType(0, PULSE);
    vecInstruments[8].setOscillatorType(0, UNDERWATER);
    vecInstruments[9].setOscillatorType(0, DARK_HALLWAY);
    loadMyTexture(osc_left_ch, "Text/text-select-sqa.png");
    loadMyTexture(osc_midl_ch, "Text/text-select-sqa.png");
    loadMyTexture(osc_rght_ch, "Text/text-select-sqa.png");
    //add load instruments from file
}

void loadWave(int theChannel) {
    for (int i = 0; i < 3; ++i) {
        oscillatorType localOsc = vecInstruments[theChannel].getOscillatorType(i);
        if (!vecInstruments[theChannel].getActive(i))
            localOsc = WHITE_NOISE;
        switch (localOsc) {
        case SINE:
            if (i == 0)
                loadMyTexture(osc_left_ch, "Text/text-select-sin.png");
            else if (i == 1)
                loadMyTexture(osc_midl_ch, "Text/text-select-sin.png");
            else
                loadMyTexture(osc_rght_ch, "Text/text-select-sin.png");
            break;
        case TRIANGLE:
            if (i == 0)
                loadMyTexture(osc_left_ch, "Text/text-select-tri.png");
            else if (i == 1)                            
                loadMyTexture(osc_midl_ch, "Text/text-select-tri.png");
            else                                        
                loadMyTexture(osc_rght_ch, "Text/text-select-tri.png");
            break;
        case SAW_ANALOG:
            if (i == 0)
                loadMyTexture(osc_left_ch, "Text/text-select-swa.png");
            else if (i == 1)                            
                loadMyTexture(osc_midl_ch, "Text/text-select-swa.png");
            else                                        
                loadMyTexture(osc_rght_ch, "Text/text-select-swa.png");
            break;
        case SAW_DIGITAL:
            if (i == 0)
                loadMyTexture(osc_left_ch, "Text/text-select-swd.png");
            else if (i == 1)                            
                loadMyTexture(osc_midl_ch, "Text/text-select-swd.png");
            else                                        
                loadMyTexture(osc_rght_ch, "Text/text-select-swd.png");
            break;
        case SQUARE:
            if (i == 0)
                loadMyTexture(osc_left_ch, "Text/text-select-sqa.png");
            else if (i == 1)                            
                loadMyTexture(osc_midl_ch, "Text/text-select-sqa.png");
            else                                        
                loadMyTexture(osc_rght_ch, "Text/text-select-sqa.png");
            break;
        case PULSE:
            if (i == 0)
                loadMyTexture(osc_left_ch, "Text/text-select-pls.png");
            else if (i == 1)                            
                loadMyTexture(osc_midl_ch, "Text/text-select-pls.png");
            else                                        
                loadMyTexture(osc_rght_ch, "Text/text-select-pls.png");
            break;
        default:
            if (i == 0)
                loadMyTexture(osc_left_ch, "Text/text-select-wns.png");
            else if (i == 1)                            
                loadMyTexture(osc_midl_ch, "Text/text-select-wns.png");
            else                                        
                loadMyTexture(osc_rght_ch, "Text/text-select-wns.png");
            break;
        }
    }
}

void loadEnvelope(int theChannel) {
    atk1Mod = vecInstruments[theChannel].env1.getAttackTime() / 5 - 0.15;
    atk2Mod = vecInstruments[theChannel].env2.getAttackTime() / 5 - 0.15;
    atk3Mod = vecInstruments[theChannel].env3.getAttackTime() / 5 - 0.15;
    dec1Mod = vecInstruments[theChannel].env1.getDecayTime() / 5 - 0.15;
    dec2Mod = vecInstruments[theChannel].env2.getDecayTime() / 5 - 0.15;
    dec3Mod = vecInstruments[theChannel].env3.getDecayTime() / 5 - 0.15;
    sus1Mod = vecInstruments[theChannel].env1.getSustainAmplitude() * (52/100);
    sus2Mod = vecInstruments[theChannel].env2.getSustainAmplitude() * (52/100);
    sus3Mod = vecInstruments[theChannel].env3.getSustainAmplitude() * (52/100);/*
    rel1Mod = vecInstruments[theChannel].env1.getReleaseTime() * (15/100) - 0.15;
    rel2Mod = vecInstruments[theChannel].env2.getReleaseTime() * (15/100) - 0.15;
    rel3Mod = vecInstruments[theChannel].env3.getReleaseTime() * (15/100) - 0.15;*/

}

void get_resolution() {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    window_width = mode->width;
    window_height = mode->height;
}

typedef bool(*lambda)(Note const& item);
template<class T>
void safe_remove(T& v, lambda f)
{
    auto n = v.begin();
    while (n != v.end())
        if (!f(*n))
            n = v.erase(n);
        else
            ++n;
}

double MakeNoise(double dTime)
{
    unique_lock<mutex> lm(muxNotes);
    double dMixedOutput = 0.0;

    for (auto& n : vecNotes)
    {
        bool bNoteFinished = false;
        double dSound = 0;
        dSound = vecInstruments[n.channel].sound(dTime, n, bNoteFinished);
        dMixedOutput += dSound;

        if (bNoteFinished && n.off > n.on)
            n.active = false;
    }

    safe_remove<vector<Note>>(vecNotes, [](Note const& item) { return item.active; });


    return dMixedOutput * 0.2;
}