#include <SDL2/SDL.h>
#include <math.h>

#define WIN_W 800
#define WIN_H 600

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erro ao inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Cubo 3D - Rotação XYZ",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_W, WIN_H,
        0
    );

    if (!window) {
        SDL_Log("Erro ao criar janela: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        SDL_Log("Erro ao criar renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Vértices do cubo
    double vertices[8][3] = {
        {-1, -1, -1},
        { 1, -1, -1},
        { 1,  1, -1},
        {-1,  1, -1},
        {-1, -1,  1},
        { 1, -1,  1},
        { 1,  1,  1},
        {-1,  1,  1}
    };

    // Arestas do cubo
    int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    int running = 1;
    SDL_Event event;

    double angleX = 0.0;
    double angleY = 0.0;
    double angleZ = 0.0;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        // Atualiza ângulos
        angleX += 0.015;
        angleY += 0.02;
        angleZ += 0.01;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        double camera_z = 4.0;
        double fov = 200.0;

        for (int i = 0; i < 12; i++) {

            int a = edges[i][0];
            int b = edges[i][1];

            double x0 = vertices[a][0];
            double y0 = vertices[a][1];
            double z0 = vertices[a][2];

            double x1 = vertices[b][0];
            double y1 = vertices[b][1];
            double z1 = vertices[b][2];

            // --- Rotação em X ---
            double y0x =  y0 * cos(angleX) - z0 * sin(angleX);
            double z0x =  y0 * sin(angleX) + z0 * cos(angleX);
            double x0x =  x0;

            double y1x =  y1 * cos(angleX) - z1 * sin(angleX);
            double z1x =  y1 * sin(angleX) + z1 * cos(angleX);
            double x1x =  x1;

            // --- Rotação em Y ---
            double x0y =  x0x * cos(angleY) - z0x * sin(angleY);
            double z0y =  x0x * sin(angleY) + z0x * cos(angleY);
            double y0y =  y0x;

            double x1y =  x1x * cos(angleY) - z1x * sin(angleY);
            double z1y =  x1x * sin(angleY) + z1x * cos(angleY);
            double y1y =  y1x;

            // --- Rotação em Z ---
            double x0z =  x0y * cos(angleZ) - y0y * sin(angleZ);
            double y0z =  x0y * sin(angleZ) + y0y * cos(angleZ);
            double z0z =  z0y;

            double x1z =  x1y * cos(angleZ) - y1y * sin(angleZ);
            double y1z =  x1y * sin(angleZ) + y1y * cos(angleZ);
            double z1z =  z1y;

            // --- Projeção perspectiva ---
            double f0 = camera_z / (camera_z + z0z);
            double f1 = camera_z / (camera_z + z1z);

            int sx0 = (int)(x0z * f0 * fov + WIN_W / 2);
            int sy0 = (int)(y0z * f0 * fov + WIN_H / 2);

            int sx1 = (int)(x1z * f1 * fov + WIN_W / 2);
            int sy1 = (int)(y1z * f1 * fov + WIN_H / 2);

            SDL_RenderDrawLine(renderer, sx0, sy0, sx1, sy1);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
