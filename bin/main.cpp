#include "../lib/raylib.h"

#include "board.hpp"

#include <thread>
#include <algorithm>
#include <chrono>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(0, 0, "sonway");

    SetExitKey(NULL);
    SetTargetFPS(60);

    ToggleFullscreen();

    board::clear();

    int width = GetScreenWidth();
    int height = GetScreenHeight();

    RenderTexture2D texture = LoadRenderTexture(1920, 1080);

    bool helpOpened = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE))
            helpOpened = !helpOpened;

        BeginDrawing();

        BeginTextureMode(texture);
        ClearBackground(WHITE);

        board::draw();

        if (IsKeyPressed(KEY_SPACE))
            board::density++;

        if (IsKeyPressed(KEY_LEFT_ALT))
            board::density--;

        board::density = std::clamp(board::density, 1, 10);

        if (helpOpened) {
            DrawRectangle(0, 0, 1920, 1080, ColorAlpha(BLACK, 0.5f));
            DrawText("sonway", 1920 / 2 - MeasureText("sonway", 180) / 2 + 4, 1080 / 2 - 396, 180, BLACK);
            DrawText("sonway", 1920 / 2 - MeasureText("sonway", 180) / 2, 1080 / 2 - 400, 180, RED);

            DrawText("ESCAPE - toggle menu", 1920 / 2 - MeasureText("ESCAPE - toggle menu", 50) / 2, 1080 / 2 - 200, 50, WHITE);
            DrawText("ENTER - new generation", 1920 / 2 - MeasureText("ENTER - new generation", 50) / 2, 1080 / 2 - 150, 50, WHITE);
            DrawText("SPACE - increase density", 1920 / 2 - MeasureText("SPACE - increase density", 50) / 2, 1080 / 2 - 100, 50, WHITE);
            DrawText("LALT - decrease density", 1920 / 2 - MeasureText("LALT - decrease density", 50) / 2, 1080 / 2 - 50, 50, WHITE);
            DrawText("LCTRL - reset cells", 1920 / 2 - MeasureText("SPACE - reset cells", 50) / 2, 1080 / 2, 50, WHITE);

            DrawText(TextFormat("density: %d", board::density), 1920 / 2 - MeasureText(TextFormat("density: %d", board::density), 50) / 2, 1080 / 2 + 100, 50, WHITE);
        } else {
            if (IsKeyDown(KEY_ENTER)) {
                board::generate();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

            if (IsKeyPressed(KEY_LEFT_CONTROL)) {
                board::clear();
                board::generate();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }

        EndTextureMode();

        DrawTexturePro(texture.texture, Rectangle{0, 0, 1920.f, -1080.f}, Rectangle{0.f, 0.f, (float)width, (float)height}, Vector2{0.f, 0.f}, 0.0f, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}