#include <3ds.h>
#include <stdio.h>
#include <string.h>

#define TOP_W 400
#define BOT_W 320
#define SCREEN_H 240
#define TAG_GRID 8
#define TAG_SIZE 200
#define TOUCH_COUNT 5

typedef struct {
    int x;
    int y;
} TouchTarget;

static const u8 TAG0[TAG_GRID][TAG_GRID] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0},
    {0,0,1,1,0,1,0,0},
    {0,0,0,0,1,0,1,0},
    {0,0,0,0,1,1,0,0},
    {0,1,0,1,1,1,0,0},
    {0,1,0,1,0,1,1,0},
    {0,0,0,0,0,0,0,0},
};

static const u8 TAG1[TAG_GRID][TAG_GRID] = {
    {0,0,0,0,0,0,0,0},
    {0,1,0,0,1,0,0,0},
    {0,1,0,1,1,0,1,0},
    {0,0,0,0,1,1,0,0},
    {0,0,0,1,1,1,1,0},
    {0,1,1,1,0,1,0,0},
    {0,0,1,1,0,1,1,0},
    {0,0,0,0,0,0,0,0},
};

static const TouchTarget TOUCH_TARGETS[TOUCH_COUNT] = {
    {20, 20},
    {299, 20},
    {299, 219},
    {20, 219},
    {160, 120},
};

static void set_pixel(u8* fb, int width, int x, int y, u8 r, u8 g, u8 b)
{
    if (x < 0 || x >= width || y < 0 || y >= SCREEN_H) return;
    int index = (x * SCREEN_H + (SCREEN_H - 1 - y)) * 3;
    fb[index + 0] = b;
    fb[index + 1] = g;
    fb[index + 2] = r;
}

static void clear_screen(u8* fb, int width, u8 r, u8 g, u8 b)
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < SCREEN_H; y++) {
            set_pixel(fb, width, x, y, r, g, b);
        }
    }
}

static void draw_tag(u8* fb, int width, const u8 tag[TAG_GRID][TAG_GRID])
{
    int start_x = (width - TAG_SIZE) / 2;
    int start_y = (SCREEN_H - TAG_SIZE) / 2;
    int cell = TAG_SIZE / TAG_GRID;

    clear_screen(fb, width, 255, 255, 255);

    for (int row = 0; row < TAG_GRID; row++) {
        for (int col = 0; col < TAG_GRID; col++) {
            u8 value = tag[row][col] ? 255 : 0;
            for (int dy = 0; dy < cell; dy++) {
                for (int dx = 0; dx < cell; dx++) {
                    set_pixel(
                        fb,
                        width,
                        start_x + (col * cell) + dx,
                        start_y + (row * cell) + dy,
                        value,
                        value,
                        value
                    );
                }
            }
        }
    }
}

static void draw_touch_target(u8* fb, int width, const TouchTarget* target)
{
    clear_screen(fb, width, 0, 0, 0);

    for (int dy = -14; dy <= 14; dy++) {
        for (int dx = -14; dx <= 14; dx++) {
            int x = target->x + dx;
            int y = target->y + dy;
            int dist2 = dx * dx + dy * dy;
            if (dist2 <= 144) {
                set_pixel(fb, width, x, y, 255, 255, 255);
            }
            if (dist2 <= 49) {
                set_pixel(fb, width, x, y, 255, 0, 0);
            }
        }
    }

    for (int i = -20; i <= 20; i++) {
        set_pixel(fb, width, target->x + i, target->y, 255, 0, 0);
        set_pixel(fb, width, target->x, target->y + i, 255, 0, 0);
    }
}

int main(int argc, char **argv)
{
    gfxInitDefault();

    int state = 0; // 0: Top tag 0, 1: Bottom tag 1, 2..6: touch targets

    while (aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & (KEY_START | KEY_SELECT)) break; // Exit on Start or Select

        if (kDown & KEY_A) {
            state++;
            if (state > 1 + TOUCH_COUNT) state = 0; // Loop back
        }

        u8* fbTop = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
        u8* fbBot = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);

        if (state == 0) {
            draw_tag(fbTop, TOP_W, TAG0);
            clear_screen(fbBot, BOT_W, 0, 0, 0);
        }
        else if (state == 1) {
            clear_screen(fbTop, TOP_W, 0, 0, 0);
            draw_tag(fbBot, BOT_W, TAG1);
        }
        else {
            clear_screen(fbTop, TOP_W, 0, 0, 0);
            draw_touch_target(fbBot, BOT_W, &TOUCH_TARGETS[state - 2]);
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
