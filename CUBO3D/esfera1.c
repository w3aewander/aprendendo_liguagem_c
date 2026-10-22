#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

int win_w = 800;
int win_h = 600;

static float audio_amplitude = 0.0f;

void audioCallback(void *userdata, Uint8 *stream, int len) {
    Sint16 *samples = (Sint16*)stream;
    int count = len / 2;

    float sum = 0.0f;
    for (int i = 0; i < count; i++)
        sum += fabs(samples[i]);

    audio_amplitude = sum / count / 32768.0f;
}

int main() {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Window *win = SDL_CreateWindow(
        "Esfera Saltitando com Áudio",
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

    SDL_AudioDeviceID mic =
        SDL_OpenAudioDevice(NULL, 1, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

    if (!mic) {
        printf("Erro ao abrir microfone: %s\n", SDL_GetError());
        return 1;
    }

    SDL_PauseAudioDevice(mic, 0);

    float y = win_h / 2;
    float vy = 0.0f;
    float radius = 40.0f;
    float gravity = 0.5f;

    int running = 1;
    SDL_Event e;

    while (running) {

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT)
                running = 0;

            if (e.type == SDL_WINDOWEVENT &&
                e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

                int new_w = e.window.data1;
                int new_h = e.window.data2;

                float scaleX = (float)new_w / win_w;
                float scaleY = (float)new_h / win_h;

                y      *= scaleY;
                vy     *= scaleY;
                radius *= scaleY;
                gravity*= scaleY;

                win_w = new_w;
                win_h = new_h;
            }
        }

        vy += gravity;
        y += vy;

        if (audio_amplitude > 0.50f)
            vy -= audio_amplitude * 0.005f * win_h / 600.0f;

        if (vy > 10.0f * (win_h / 600.0f))
            vy = 10.0f * (win_h / 600.0f);

        if (vy < -10.0f * (win_h / 600.0f))
            vy = -10.0f * (win_h / 600.0f);

        float impulso = audio_amplitude * 20.0f * (win_h / 600.0f);
        if (impulso > 5.0f * (win_h / 600.0f))
            impulso = 5.0f * (win_h / 600.0f);

        vy -= impulso;

        if (y + radius > win_h) {
            y = win_h - radius;
            vy = -vy * 0.7f;
        }

        if (y - radius < 0) {
            y = radius;
            vy = -vy * 0.5f;
        }

        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);

        if(audio_amplitude > 0.15f) {
            SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        } else if (audio_amplitude > 0.07f) {
            SDL_SetRenderDrawColor(r, 255, 255, 0, 255);
        } else {
            SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
        }

        for (int w = -radius; w <= radius; w++) {
            int h = sqrt(radius*radius - w*w);
            SDL_RenderDrawLine(r, win_w/2 + w, y - h, win_w/2 + w, y + h);
        }

        SDL_RenderPresent(r);
    }

    SDL_CloseAudioDevice(mic);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
