Wayne State Computer Setup:

1. Open Engineering VLAB 
2. Extract all
3. Open cui.sln
4. Set to Debug x86 OR Release x86
5. Project -> General -> Platform Toolset -> set to your local toolset (Wayne State computers use v142)
6. Map the directories to your local directories:
	VC++ Directories
		Include Directories:
			LocalPath\cui\glad\include
			LocalPath\cui\glfw-3.4-x86\glfw-3.4.bin.WIN32\include
		Library Directores:
			LocalPath\cui\glfw-3.4-x86\glfw-3.4.bin.WIN32\lib-vc2022\glfw3.lib
			(for lib-vc2022 use your local version)
	C/C++
		Code Generation
			Runtime Library
				Multi-Threaded Debug DLL OR Multi-Threaded DLL
			Security Check
				Disable Security Check
	Linker
		Input
			Additional Dependencies
				LocalPath\cui\glfw-3.4-x86\glfw-3.4.bin.WIN32\lib-vc2022\glfw3.lib
				(for lib-vc2022 use your local version)
				opengl32.lib
7. Build
