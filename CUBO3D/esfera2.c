#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#define WIN_W 800
#define WIN_H 600

static float audio_amplitude = 0.0f;
static float audio_frequency = 0.0f;

void audioCallback(void *userdata, Uint8 *stream, int len) {
    Sint16 *samples = (Sint16*)stream;
    int count = len / 2;

    float sum = 0.0f;
    int zeroCross = 0;

    for (int i = 1; i < count; i++) {
        sum += fabs(samples[i]);

        if ((samples[i - 1] < 0 && samples[i] > 0) ||
            (samples[i - 1] > 0 && samples[i] < 0)) {
            zeroCross++;
        }
    }

    audio_amplitude = sum / count / 32768.0f;

    audio_frequency = (zeroCross * 44100.0f) / (2.0f * count);
}

int main() {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Window *win = SDL_CreateWindow(
        "Esfera Saltitando com Áudio",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIN_W, WIN_H, 0
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

    float y = WIN_H / 2;
    float vy = 0.0f;
    float radius = 40.0f;
    float gravity = 0.5f;

    int running = 1;
    SDL_Event e;

    while (running) {

        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)
                running = 0;

        vy += gravity;
        y += vy;

        if (vy > 10.0f) vy = 10.0f;
        if (vy < -10.0f) vy = -10.0f;

        float impulso = audio_amplitude * 20.0f;
        if (impulso > 5.0f) impulso = 5.0f;
        vy -= impulso;

        if (y + radius > WIN_H) {
            y = WIN_H - radius;
            vy = -vy * 0.7f;
        }

        if (y - radius < 0) {
            y = radius;
            vy = -vy * 0.5f;
        }

        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);

        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);

        for (int w = -radius; w <= radius; w++) {
            int h = sqrt(radius*radius - w*w);
            SDL_RenderDrawLine(r,
                WIN_W/2 + w, y - h,
                WIN_W/2 + w, y + h
            );
        }

        char texto[128];
        snprintf(texto, sizeof(texto),
                 "Amp: %.3f   Freq: %.1f Hz",
                 audio_amplitude, audio_frequency);

        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

        int x = WIN_W - 300;
        int ytxt = 20;

        for (int i = 0; texto[i]; i++) {
            SDL_RenderDrawLine(r, x + i*8, ytxt, x + i*8 + 6, ytxt);
        }

        SDL_RenderPresent(r);
    }

    SDL_CloseAudioDevice(mic);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
