# GameFramework
**GameFramework** is only for *learning*, and for now it only supports **Windows** operating systems.

## This FrameWork Requires Some Dependencies
Don't worry because the requirements already exist.
 - SDL2
 - SDL2 Image
 - SDL2 Mixer
 - SDL2 TTF
 - OneTTB
 - ENTT
 - nlohmann/json
 - Box2D
 
## First Time
- You only need to open the project with the `*.sln` format file.
- You can set everything in the `GameFramework` project because that is the point that will become the `*.exe` file. Starting from the name of the executable.
- For the first time you can code in `Main/src/root.cpp`.

## For x86 Architecture Users
- Because I usually run the program and compile it using x64 so I don't include the x86 compile result.
- So for you x86 users, you only need to copy the required `*.dll` library into the compiled folder.
- I have prepared all the settings for x86 so I only need to copy the library.

What Must Be Moved:
 - SDL2
 - SDL2 Image
 - SDL2 Mixer
 - Box2D
 - **OneTBB**

## Support
| Suport             | Operating System | Architecture Build  |
| ------------------ |:----------------:| -------------------:|
| :heavy_check_mark: | Windows          |         x86         |
| :heavy_check_mark: | Windows          |         x64         |
