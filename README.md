# Triscillator

Triscillator is an additive synthesizer with three oscillators that can choose between 7 waveforms. 

It consists of an interface for creating and manipulating waveforms, contained in csynth.h and csynth.cpp,
and a graphical interface that extends this interface into a desktop app, in main.cpp, vertices.h, and colors.h.

## Installation

1. Obtain the GLAD and GLFW libraries:
[Generate GLAD](https://glad.dav1d.de/)
[Download pre-compiled GLFW binaries](https://www.glfw.org/download)

2. Ensure that project is in 32-bit (x86) Mode
   
3. Link libraries to project:
   
	VC++ Directories:

		Include Directories:

			LocalPath\cui\glad\include
   
			LocalPath\cui\glfw-3.4-x86\glfw-3.4.bin.WIN32\include
   
		Library Directores:

			LocalPath\cui\glfw-3.4-x86\glfw-3.4.bin.WIN32\lib-vc2022\glfw3.lib
   
			(for lib-vc2022 use your local version)
   
	C/C++

		Code Generation

			Runtime Library
   
				If Debug Mode: Multi-Threaded Debug DLL
   
				If Release Mode: Multi-Threaded DLL
   
			Security Check
   
				Disable Security Check
   
	Linker

		Input

			Additional Dependencies
   
				LocalPath\cui\glfw-3.4-x86\glfw-3.4.bin.WIN32\lib-vc2022\glfw3.lib
				(for lib-vc2022 use your local version)
   
				opengl32.lib
   
5. Build app

## Usage

1. Play notes: Press a key on your computer keyboard that corresponds with the key in the interface. You can press multiple at once.
2. Change oscillators: Hover or press the drop-down labelled square. Select an oscillator type from the dropdown.
3. Change volume: Press the up and down arrows on the screen to increase or decrease the volume of each individual oscillator.
4. Change note: Press the up and down arrows on the screen to increment or decrement the pitch of each individual oscillator by one tone.
5. Toggle oscillator on/off: Press the on/off switch on top of each oscillator to turn it on or off.
6. Change playback octave: Press the left and right arrows around the octave control to move the keyboard up and down an octave.
7. Change preset: Hover or press the drop-down labelled preset. Select a preset from the dropdown.
8. Change envelope: Click the Env button to change to the envelope tab. This allows you to change attack, decay, sustain, and release (ADSR).
	a. Drag and drop a vertex to change ADSR fluidly.
	b. Press the up and down arrows that correspond to each control to change ADSR incrementally.

## Todo
- [] Fix intense lag when manipulating ADSR
- [] Multiple keybinds: press screen to play note and press computer keyboard to play note
- [] Fullscreen support
- [] Text generation and numerical feedback
- [] Implement detune and LFO controls in interface
- [] Save and load custom presets
- [] Unlimited presets
- [] MIDI compatibility

## Credits

[Synth](https://github.com/OneLoneCoder/synth/tree/master) by One Lone Coder. Used olcNoiseMaker.h and encapsulated the synthesizer functionality into an interface.
[]()

## License

[MIT](https://choosealicense.com/licenses/mit/)
