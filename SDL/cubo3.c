#include <SDL2/SDL.h>
#include <math.h>

#define WIN_W 800
#define WIN_H 600

typedef struct {
    double x, y, z;
} Vec3;

typedef struct {
    int v0, v1, v2, v3;
    SDL_Color color;
} Face;

void drawTriangle(SDL_Renderer *r, int x0, int y0, int x1, int y1, int x2, int y2, SDL_Color c) {
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, 255);

    // Ordena por y (simples)
    if (y1 < y0) { int t; t=x0; x0=x1; x1=t; t=y0; y0=y1; y1=t; }
    if (y2 < y0) { int t; t=x0; x0=x2; x2=t; t=y0; y0=y2; y2=t; }
    if (y2 < y1) { int t; t=x1; x1=x2; x2=t; t=y1; y1=y2; y2=t; }

    double dx1 = (y1 - y0) ? (double)(x1 - x0) / (y1 - y0) : 0;
    double dx2 = (y2 - y0) ? (double)(x2 - x0) / (y2 - y0) : 0;
    double dx3 = (y2 - y1) ? (double)(x2 - x1) / (y2 - y1) : 0;

    double sx = x0;
    double ex = x0;

    for (int y = y0; y <= y1; y++) {
        SDL_RenderDrawLine(r, (int)sx, y, (int)ex, y);
        sx += dx1;
        ex += dx2;
    }

    sx = x1;
    ex = x0 + dx2 * (y1 - y0);

    for (int y = y1; y <= y2; y++) {
        SDL_RenderDrawLine(r, (int)sx, y, (int)ex, y);
        sx += dx3;
        ex += dx2;
    }
}

int main() {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("Cubo 3D Colorido",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIN_W, WIN_H, 0);

    SDL_Renderer *r = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Vec3 vertices[8] = {
        {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
        {-1,-1, 1}, {1,-1, 1}, {1,1, 1}, {-1,1, 1}
    };

    Face faces[6] = {
        {0,1,2,3, {255,0,0,255}},   // vermelho
        {4,5,6,7, {0,255,0,255}},   // verde
        {0,1,5,4, {0,0,255,255}},   // azul
        {2,3,7,6, {255,255,0,255}}, // amarelo
        {1,2,6,5, {255,0,255,255}}, // magenta
        {0,3,7,4, {0,255,255,255}}  // ciano
    };

    double ax=0, ay=0, az=0;
    int running = 1;
    SDL_Event e;

    while (running) {

        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) running = 0;

        ax += 0.01;
        ay += 0.02;
        az += 0.015;

        SDL_SetRenderDrawColor(r, 0,0,0,255);
        SDL_RenderClear(r);

        Vec3 tv[8];

        for (int i=0;i<8;i++) {
            double x=vertices[i].x, y=vertices[i].y, z=vertices[i].z;

            double y1 = y*cos(ax) - z*sin(ax);
            double z1 = y*sin(ax) + z*cos(ax);
            y = y1; z = z1;

            double x1 = x*cos(ay) - z*sin(ay);
            double z2 = x*sin(ay) + z*cos(ay);
            x = x1; z = z2;

            double x2 = x*cos(az) - y*sin(az);
            double y2 = x*sin(az) + y*cos(az);
            x = x2; y = y2;

            double f = 4.0 / (4.0 + z);
            tv[i].x = x * f * 200 + WIN_W/2;
            tv[i].y = y * f * 200 + WIN_H/2;
        }

        for (int i=0;i<6;i++) {
            Face f = faces[i];

            int v0=f.v0, v1=f.v1, v2=f.v2, v3=f.v3;

            drawTriangle(r, tv[v0].x, tv[v0].y, tv[v1].x, tv[v1].y, tv[v2].x, tv[v2].y, f.color);
            drawTriangle(r, tv[v0].x, tv[v0].y, tv[v2].x, tv[v2].y, tv[v3].x, tv[v3].y, f.color);
        }

        SDL_RenderPresent(r);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
