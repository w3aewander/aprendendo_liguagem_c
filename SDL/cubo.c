#include <SDL2/SDL.h>
#include <math.h>

#define WIN_W 800
#define WIN_H 600

int main(int argc, char *argv[]) {

    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erro ao inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    // Cria janela
    SDL_Window *window = SDL_CreateWindow(
        "Cubo 3D - SDL2",
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

    // Cria renderer
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

    double angle = 0.0; // ângulo de rotação

    while (running) {

        // Eventos
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        // Atualiza ângulo
        angle += 0.02;

        // Limpa tela
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Cor das linhas
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Parâmetros da câmera
        double camera_z = 4.0;
        double fov = 200.0;

        // Desenha cada aresta
        for (int i = 0; i < 12; i++) {

            int a = edges[i][0];
            int b = edges[i][1];

            // Vértice A
            double x0 = vertices[a][0];
            double y0 = vertices[a][1];
            double z0 = vertices[a][2];

            // Vértice B
            double x1 = vertices[b][0];
            double y1 = vertices[b][1];
            double z1 = vertices[b][2];

            // ---------------------------
            // ROTACAO EM Y
            // ---------------------------
            double x0r =  x0 * cos(angle) - z0 * sin(angle);
            double z0r =  x0 * sin(angle) + z0 * cos(angle);
            double y0r =  y0;

            double x1r =  x1 * cos(angle) - z1 * sin(angle);
            double z1r =  x1 * sin(angle) + z1 * cos(angle);
            double y1r =  y1;

            // ---------------------------
            // ROTACAO EM X
            // ---------------------------
            double y0r2 =  y0r * cos(angle) - z0r * sin(angle);
            double z0r2 =  y0r * sin(angle) + z0r * cos(angle);
            double x0r2 =  x0r;

            double y1r2 =  y1r * cos(angle) - z1r * sin(angle);
            double z1r2 =  y1r * sin(angle) + z1r * cos(angle);
            double x1r2 =  x1r;

            // ---------------------------
            // PROJEÇÃO PERSPECTIVA
            // ---------------------------
            double f0 = camera_z / (camera_z + z0r2);
            double f1 = camera_z / (camera_z + z1r2);

            int sx0 = (int)(x0r2 * f0 * fov + WIN_W / 2);
            int sy0 = (int)(y0r2 * f0 * fov + WIN_H / 2);

            int sx1 = (int)(x1r2 * f1 * fov + WIN_W / 2);
            int sy1 = (int)(y1r2 * f1 * fov + WIN_H / 2);

            // Desenha linha
            SDL_RenderDrawLine(renderer, sx0, sy0, sx1, sy1);
        }

        // Mostra frame
        SDL_RenderPresent(renderer);
    }

    // Finaliza
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
