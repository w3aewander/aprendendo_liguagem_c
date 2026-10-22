#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#define NUM_BALLS 100

static float audio_amplitude = 0.0f;
static float sensitivity = 0.5f;

typedef struct {
    float x, y;
    float vx, vy;
    float radius;
    SDL_Color color;
} Ball;

void audioCallback(void *userdata, Uint8 *stream, int len) {
    Sint16 *samples = (Sint16*)stream;
    int count = len / 2;

    float sum = 0.0f;
    for (int i = 0; i < count; i++)
        sum += fabs(samples[i]);

    audio_amplitude = sum / count / 32768.0f;
}

void drawCircle(SDL_Renderer *r, int cx, int cy, int radius, SDL_Color c) {
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, 255);

    for (int w = -radius; w <= radius; w++) {
        int h = sqrt(radius*radius - w*w);
        SDL_RenderDrawLine(r, cx + w, cy - h, cx + w, cy + h);
    }
}

void handleBallCollision(Ball *a, Ball *b) {
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dist = sqrt(dx*dx + dy*dy);
    float minDist = a->radius + b->radius;

    if (dist < minDist && dist > 0.0f) {

        float nx = dx / dist;
        float ny = dy / dist;

        float overlap = minDist - dist;

        a->x -= nx * overlap * 0.5f;
        a->y -= ny * overlap * 0.5f;
        b->x += nx * overlap * 0.5f;
        b->y += ny * overlap * 0.5f;

        float va = a->vx * nx + a->vy * ny;
        float vb = b->vx * nx + b->vy * ny;

        float swap = vb - va;

        a->vx += swap * nx;
        a->vy += swap * ny;
        b->vx -= swap * nx;
        b->vy -= swap * ny;
    }
}

int main() {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    int win_w = 800;
    int win_h = 600;

    SDL_Window *win = SDL_CreateWindow(
        "Bolinhas Reagindo ao Som",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        win_w, win_h,
        SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer *r = SDL_CreateRenderer(
        win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_AudioSpec want, have;
    SDL_zero(want);

    want.freq = 44100;
    want.format = AUDIO_S16;
    want.channels = 1;
    want.samples = 4096;
    want.callback = audioCallback;

    SDL_AudioDeviceID mic = SDL_OpenAudioDevice(
        NULL, 1, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE
    );

    if (!mic) {
        printf("Erro ao abrir microfone: %s\n", SDL_GetError());
        return 1;
    }

    SDL_PauseAudioDevice(mic, 0);

    Ball balls[NUM_BALLS];

    for (int i = 0; i < NUM_BALLS; i++) {
        balls[i].x = rand() % win_w;
        balls[i].y = rand() % win_h;
        balls[i].vx = ((rand() % 200) - 100) / 50.0f;
        balls[i].vy = ((rand() % 200) - 100) / 50.0f;
        balls[i].radius = 1.5 + rand() % 2;
        balls[i].color = (SDL_Color){ rand()%255, rand()%255, rand()%255, 255 };
    }

    int running = 1;
    SDL_Event e;

    while (running) {

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT)
                running = 0;

            if (e.type == SDL_WINDOWEVENT &&
                e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

                win_w = e.window.data1;
                win_h = e.window.data2;
            }
        }

        float force = audio_amplitude * sensitivity * 70.0f;

        for (int i = 0; i < NUM_BALLS; i++) {
            balls[i].vx += ((rand() % 200) - 100) / 500.0f * force;
            balls[i].vy += ((rand() % 200) - 100) / 500.0f * force;

            balls[i].x += balls[i].vx;
            balls[i].y += balls[i].vy;

            if (balls[i].x < balls[i].radius) {
                balls[i].x = balls[i].radius;
                balls[i].vx *= -0.7f;
            }
            if (balls[i].x > win_w - balls[i].radius) {
                balls[i].x = win_w - balls[i].radius;
                balls[i].vx *= -0.7f;
            }
            if (balls[i].y < balls[i].radius) {
                balls[i].y = balls[i].radius;
                balls[i].vy *= -0.7f;
            }
            if (balls[i].y > win_h - balls[i].radius) {
                balls[i].y = win_h - balls[i].radius;
                balls[i].vy *= -0.7f;
            }
        }

        for (int i = 0; i < NUM_BALLS; i++)
            for (int j = i + 1; j < NUM_BALLS; j++)
                handleBallCollision(&balls[i], &balls[j]);

        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);

        for (int i = 0; i < NUM_BALLS; i++)
            drawCircle(r, balls[i].x, balls[i].y, balls[i].radius, balls[i].color);

        SDL_RenderPresent(r);
    }

    SDL_CloseAudioDevice(mic);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);

    SDL_Quit();
    return 0;
}
