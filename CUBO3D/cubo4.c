#include <SDL2/SDL.h>
#include <math.h>
#include <float.h>

#define WIN_W 800
#define WIN_H 600

typedef struct {
    double x, y, z;
} Vec3;

typedef struct {
    int v0, v1, v2, v3;
    SDL_Color color;
} Face;

double zbuffer[WIN_W][WIN_H];

void clearZBuffer() {
    for (int x = 0; x < WIN_W; x++)
        for (int y = 0; y < WIN_H; y++)
            zbuffer[x][y] = DBL_MAX;
}

void putPixel(SDL_Renderer *r, int x, int y, double z, SDL_Color c) {
    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
        return;

    if (z < zbuffer[x][y]) {
        zbuffer[x][y] = z;
        SDL_SetRenderDrawColor(r, c.r, c.g, c.b, 255);
        SDL_RenderDrawPoint(r, x, y);
    }
}

void drawTriangleZ(SDL_Renderer *r,
                   Vec3 a, Vec3 b, Vec3 c,
                   SDL_Color col)
{
    // Ordena por y
    if (b.y < a.y) { Vec3 t=a; a=b; b=t; }
    if (c.y < a.y) { Vec3 t=a; a=c; c=t; }
    if (c.y < b.y) { Vec3 t=b; b=c; c=t; }

    double dx1 = (b.y - a.y) ? (b.x - a.x) / (b.y - a.y) : 0;
    double dz1 = (b.y - a.y) ? (b.z - a.z) / (b.y - a.y) : 0;

    double dx2 = (c.y - a.y) ? (c.x - a.x) / (c.y - a.y) : 0;
    double dz2 = (c.y - a.y) ? (c.z - a.z) / (c.y - a.y) : 0;

    double dx3 = (c.y - b.y) ? (c.x - b.x) / (c.y - b.y) : 0;
    double dz3 = (c.y - b.y) ? (c.z - b.z) / (c.y - b.y) : 0;

    double sx = a.x, ex = a.x;
    double sz = a.z, ez = a.z;

    for (int y = (int)a.y; y <= (int)b.y; y++) {
        double x1 = sx, x2 = ex;
        double z1 = sz, z2 = ez;

        if (x2 < x1) {
            double t;
            t=x1; x1=x2; x2=t;
            t=z1; z1=z2; z2=t;
        }

        double dz = (x2 - x1) ? (z2 - z1) / (x2 - x1) : 0;

        double z = z1;
        for (int x = (int)x1; x <= (int)x2; x++) {
            putPixel(r, x, y, z, col);
            z += dz;
        }

        sx += dx1;
        sz += dz1;
        ex += dx2;
        ez += dz2;
    }

    sx = b.x; sz = b.z;
    ex = a.x + dx2 * (b.y - a.y);
    ez = a.z + dz2 * (b.y - a.y);

    for (int y = (int)b.y; y <= (int)c.y; y++) {
        double x1 = sx, x2 = ex;
        double z1 = sz, z2 = ez;

        if (x2 < x1) {
            double t;
            t=x1; x1=x2; x2=t;
            t=z1; z1=z2; z2=t;
        }

        double dz = (x2 - x1) ? (z2 - z1) / (x2 - x1) : 0;

        double z = z1;
        for (int x = (int)x1; x <= (int)x2; x++) {
            putPixel(r, x, y, z, col);
            z += dz;
        }

        sx += dx3;
        sz += dz3;
        ex += dx2;
        ez += dz2;
    }
}

int main() {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("Cubo 3D com Z-buffer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIN_W, WIN_H, 0);

    SDL_Renderer *r = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Vec3 vertices[8] = {
        {-1,-1,-1}, 
        {1,-1,-1}, 
        {1,1,-1}, 
        {-1,1,-1},
        {-1,-1, 1}, 
        {1,-1, 1}, 
        {1,1, 1}, 
        {-1,1, 1}
    };

    Face faces[6] = {
        {0,1,2,3, {255,0,0,255}},
        {4,5,6,7, {0,255,0,255}},
        {0,1,5,4, {0,0,255,255}},
        {2,3,7,6, {255,255,0,255}},
        {1,2,6,5, {255,0,255,255}},
        {0,3,7,4, {0,255,255,255}}
    };

    double ax=0, ay=0, az=0;
    int running = 1;
    SDL_Event e;

    while (running) {

        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) running = 0;

        // alterando os valores aqui eu altero a velocidade da rotação do cubo    
        ax += 0.01 * 10;
        ay += 0.02 * 10;
        az += 0.015 * 10;

        SDL_SetRenderDrawColor(r, 0,0,0,255);
        SDL_RenderClear(r);

        clearZBuffer();

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
            tv[i].z = z;
        }

        for (int i=0;i<6;i++) {
            Face f = faces[i];

            drawTriangleZ(r, tv[f.v0], tv[f.v1], tv[f.v2], f.color);
            drawTriangleZ(r, tv[f.v0], tv[f.v2], tv[f.v3], f.color);
        }

        SDL_RenderPresent(r);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
