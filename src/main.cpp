#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <iostream>
#include <format>
#include "IK2.h"

#define SPIN_MIN -100
#define SPIN_MAX 100

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1145, 745, "Discrete Laplacian");
    SetTargetFPS(60);

    // window:
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Vector2 picStart = {170.f, 125.f};
    int spinner001Value = -1;
    int spinner002Value = -1;
    int spinner003Value = -1;
    int spinner004Value = -1;
    int spinner005Value = 8;
    int spinner006Value = -1;
    int spinner007Value = -1;
    int spinner008Value = -1;
    int spinner009Value = -1;
    bool spinnerEditMode1 = false;
    bool spinnerEditMode2 = false;
    bool spinnerEditMode3 = false;
    bool spinnerEditMode4 = false;
    bool spinnerEditMode5 = false;
    bool spinnerEditMode6 = false;
    bool spinnerEditMode7 = false;
    bool spinnerEditMode8 = false;
    bool spinnerEditMode9 = false;
    float kern[] = { -1.f, -1.f,  1.f,
                    -1.f, 8.f, -1.f,
                    -1.f, -1.f,  -1.f
                };
    
    Image imOrigin = LoadImage("resources/01.png");
    ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); 
    Image imCopy = ImageCopy(imOrigin);
    Texture2D texture = LoadTextureFromImage(imCopy);
    bool textureReload = false;

    SetTraceLogLevel(LOG_ALL);
    
    while (!WindowShouldClose()){
        
        if (IsFileDropped()) {
            FilePathList droppedFiles = LoadDroppedFiles();
            TraceLog(LOG_WARNING, "got file: %s\n", droppedFiles.paths[0]);
            if (IsFileExtension(droppedFiles.paths[0], ".png") ||
                IsFileExtension(droppedFiles.paths[0], ".jpg") ||
                IsFileExtension(droppedFiles.paths[0], ".jpeg")) {
                    imOrigin = LoadImage(droppedFiles.paths[0]);
                    if (imOrigin.width > width - picStart.x) { 
                        float aspectRatio = float(imOrigin.width) / float(imOrigin.height);
                        ImageResize(&imOrigin, width - picStart.x - 5, (width - picStart.x - 5) / aspectRatio);
                    }
                    if (imOrigin.height > height - picStart.y) { 
                        float aspectRatio = float(imOrigin.width) / float(imOrigin.height);
                        ImageResize(&imOrigin, (height - picStart.y - 5) * aspectRatio, height - picStart.y - 5);
                    }
                    ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
                    imCopy = ImageCopy(imOrigin);
                    //UnloadTexture(texture);
                    texture = LoadTextureFromImage(imCopy);
                    Color *pixels = LoadImageColors(imCopy);
                    UpdateTexture(texture, pixels);
                    UnloadImageColors(pixels);
                }
            UnloadDroppedFiles(droppedFiles);
        }

        if (IsKeyReleased(KEY_ONE)) {
            imOrigin = LoadImage("resources/01.png");
            if (imOrigin.width > width - picStart.x) { 
                float aspectRatio = float(imOrigin.width) / float(imOrigin.height);
                ImageResize(&imOrigin, width - picStart.x - 5, (width - picStart.x - 5) / aspectRatio);
            }
            if (imOrigin.height > height - picStart.y) { 
                float aspectRatio = float(imOrigin.width) / float(imOrigin.height);
                ImageResize(&imOrigin, (height - picStart.y - 5) * aspectRatio, height - picStart.y - 5);
            }
            ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            imCopy = ImageCopy(imOrigin);
            texture = LoadTextureFromImage(imCopy);
            Color *pixels = LoadImageColors(imCopy);
            UpdateTexture(texture, pixels);
            UnloadImageColors(pixels);
        }

        if (IsKeyReleased(KEY_TWO)) {
            imOrigin = LoadImage("resources/02.jpg");
            if (imOrigin.width > width - picStart.x) { 
                float aspectRatio = float(imOrigin.width) / float(imOrigin.height);
                ImageResize(&imOrigin, width - picStart.x - 5, (width - picStart.x - 5) / aspectRatio);
            }
            if (imOrigin.height > height - picStart.y) { 
                float aspectRatio = float(imOrigin.width) / float(imOrigin.height);
                ImageResize(&imOrigin, (height - picStart.y - 5) * aspectRatio, height - picStart.y - 5);
            }
            ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            imCopy = ImageCopy(imOrigin);
            texture = LoadTextureFromImage(imCopy);
            Color *pixels = LoadImageColors(imCopy);
            UpdateTexture(texture, pixels);
            UnloadImageColors(pixels);
        }

        if (IsKeyReleased(KEY_THREE)) {
            imOrigin = LoadImage("resources/03.jpg");
            if (imOrigin.width > width - picStart.x) { 
                float aspectRatio = float(imOrigin.width) / float(imOrigin.height);
                ImageResize(&imOrigin, width - picStart.x - 5, (width - picStart.x - 5) / aspectRatio);
            }
            if (imOrigin.height > height - picStart.y) { 
                float aspectRatio = float(imOrigin.width) / float(imOrigin.height);
                ImageResize(&imOrigin, (height - picStart.y - 5) * aspectRatio, height - picStart.y - 5);
            }
            ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            imCopy = ImageCopy(imOrigin);
            texture = LoadTextureFromImage(imCopy);
            Color *pixels = LoadImageColors(imCopy);
            UpdateTexture(texture, pixels);
            UnloadImageColors(pixels);
        }


        // check for resize
        int newheight = GetScreenHeight();
        int newwidth = GetScreenWidth();
        if (newheight != height || newwidth != width) {
            width = newwidth;
            height = newheight;
        }
        
        // drawing:
        BeginDrawing();
        ClearBackground(BLACK);

        if (GuiSpinner((Rectangle){ 25, 25, 75, 25 }, NULL, &spinner001Value,  SPIN_MIN, SPIN_MAX, spinnerEditMode1))  {
            spinnerEditMode1 = !spinnerEditMode1;
        }
        if (GuiSpinner((Rectangle){ 100, 25, 75, 25 }, NULL, &spinner002Value, SPIN_MIN, SPIN_MAX, spinnerEditMode2))  {
            spinnerEditMode2 = !spinnerEditMode2;
        }
        if (GuiSpinner((Rectangle){ 175, 25, 75, 25 }, NULL, &spinner003Value, SPIN_MIN, SPIN_MAX, spinnerEditMode3))  {
            spinnerEditMode3 = !spinnerEditMode3;
        }
        if (GuiSpinner((Rectangle){ 25, 50, 75, 25 }, NULL, &spinner004Value,  SPIN_MIN, SPIN_MAX, spinnerEditMode4))  {
            spinnerEditMode4 = !spinnerEditMode4;
        }
        if (GuiSpinner((Rectangle){ 100, 50, 75, 25 }, NULL, &spinner005Value, SPIN_MIN, SPIN_MAX, spinnerEditMode5))  {
            spinnerEditMode5 = !spinnerEditMode5;
        }
        if (GuiSpinner((Rectangle){ 175, 50, 75, 25 }, NULL, &spinner006Value, SPIN_MIN, SPIN_MAX, spinnerEditMode6))  {
            spinnerEditMode6 = !spinnerEditMode6;
        }
        if (GuiSpinner((Rectangle){ 25, 75, 75, 25 }, NULL, &spinner007Value, SPIN_MIN, SPIN_MAX, spinnerEditMode7))  {
            spinnerEditMode7 = !spinnerEditMode7;
        }
        if (GuiSpinner((Rectangle){ 100, 75, 75, 25 }, NULL, &spinner008Value, SPIN_MIN, SPIN_MAX, spinnerEditMode8))  {
            spinnerEditMode8 = !spinnerEditMode8;
        }
        if (GuiSpinner((Rectangle){ 175, 75, 75, 25 }, NULL, &spinner009Value, SPIN_MIN, SPIN_MAX, spinnerEditMode9))  {
            spinnerEditMode9 = !spinnerEditMode9;
        }

        if (GuiButton((Rectangle){62, 125, 100, 25}, "Apply") || IsKeyReleased(KEY_A)) {
            kern[0] = spinner001Value;
            kern[1] = spinner002Value;
            kern[2] = spinner003Value;
            kern[3] = spinner004Value;
            kern[4] = spinner005Value;
            kern[5] = spinner006Value;
            kern[6] = spinner007Value;
            kern[7] = spinner008Value;
            kern[8] = spinner009Value;
            float total = 0.f;
            for (int i = 0; i < 9; i++) {
                total += kern[i];
            }
            if (fabs(total) > 0.001f) { // "normalize"
                for (int i = 0; i < 9; i++) {
                    kern[i] /= total;
                }
            }
            ImageKernelNoAlpha(&imCopy, kern, 9); 
            ImageFormat(&imCopy, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); 
            Color *pixels = LoadImageColors(imCopy);
            UpdateTexture(texture, pixels);
            UnloadImageColors(pixels);
        }

        if (GuiButton((Rectangle){62, 175, 100, 25}, "Original") || IsKeyReleased(KEY_O)) {
            imCopy = ImageCopy(imOrigin);
            texture = LoadTextureFromImage(imCopy);
            Color *pixels = LoadImageColors(imCopy);
            UpdateTexture(texture, pixels);
            UnloadImageColors(pixels);
        }

        DrawTextureV(texture, picStart, WHITE);
        EndDrawing();
    }

    UnloadTexture(texture);       // Unload texture from VRAM
    UnloadImage(imOrigin);        // Unload image-origin from RAM
    UnloadImage(imCopy);          // Unload image-copy from RAM

    CloseWindow();
    return 0;
}

// wasm compilation:

// em++ -std=c++20 -o game.html src/main.cpp -Os -Wall \
// -I ~/dev/emsdk/upstream/emscripten/cache/sysroot/include -I./src  -I/usr/local/include \
// -L ~/dev/emsdk/upstream/emscripten/cache/sysroot/lib/libraylib.a -s USE_GLFW=3 \
// -s ASYNCIFY -s ALLOW_MEMORY_GROWTH=1 --preload-file resources \
// --shell-file minshell.html -DPLATFORM_WEB ~/dev/emsdk/upstream/emscripten/cache/sysroot/lib/libraylib.a
//

// app compilation for local use:

// g++ -std=c++20 -o game src/main.cpp -Os -Wall -I./src -I/opt/homebrew/Cellar/raylib/5.5/include -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib