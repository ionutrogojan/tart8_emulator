#include <stdio.h>
#include <raylib.h>

#define TILE 8
#define SCALE 4
#define WIDTH 24
#define HEIGHT 16

#define D_BLACK      0x000000ff
#define D_WHITE      0xa6a6a6ff
#define D_RED        0xb34712ff
#define D_YELLOW     0xf26624ff
#define D_GREEN      0x2db343ff
#define D_CYAN       0x2592a7ff
#define D_BLUE       0x2e4099ff
#define D_MAGENTA    0x992e99ff

#define L_BLACK      0x595959ff
#define L_WHITE      0xffffffff
#define L_RED        0xe62e2eff
#define L_YELLOW     0xffb319ff
#define L_GREEN      0x6dcc3dff
#define L_CYAN       0x2cc9beff
#define L_BLUE       0x457ae6ff
#define L_MAGENTA    0xd941b3ff

int main(void) {
	// Screen Buffer
	char buffer[WIDTH * HEIGHT];
	int cursorPosition = 0;
	int keyPressed = 0;
	int i = 0;
	int y = 0, x = 0;

	// SetTraceLogLevel(LOG_NONE);
	InitWindow((WIDTH * TILE * SCALE), (HEIGHT * TILE * SCALE), "Tart8");

	Image fontMap = LoadImage("./font.png");
	Texture2D fontAtlas = LoadTextureFromImage(fontMap);

	buffer[0] = 0;

	UnloadImage(fontMap);

	// Load custom shader
	Shader shader = LoadShader(0, "./shader/recolour.frag");
	SetShaderValue(shader, GetShaderLocation(shader, "textureSampler"), (int[1]){0}, SHADER_UNIFORM_INT);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GetColor(L_BLACK));

		if ((keyPressed = GetKeyPressed()) != 0) {
			switch (keyPressed) {
				case KEY_BACKSPACE:
					// printf("BackSpace\n");
					// fflush(stdout);
					if (cursorPosition > 0) {
						buffer[cursorPosition] = 0;
						cursorPosition--;
						buffer[cursorPosition] = 0;
					}
					// printf("c%d, %s\n", cursorPosition, buffer);
					// fflush(stdout);
				break;
				case KEY_ENTER:
					if (cursorPosition < (WIDTH * HEIGHT) - 1) {
						buffer[cursorPosition] = '\n';
						cursorPosition++;
						buffer[cursorPosition] = 0;
					}
					// printf("c%d, %s\n", cursorPosition, buffer);
					// fflush(stdout);
				break;
				default:

				break;
			}
		}

		if ((keyPressed = GetCharPressed()) != 0) {
			// printf("%d\n", keyPressed);
			// fflush(stdout);
			if (cursorPosition < (WIDTH * HEIGHT) - 1) {
				buffer[cursorPosition] = keyPressed;
				cursorPosition++;
				buffer[cursorPosition] = 0;    // terminate string
				// printf("c%d, %s\n", cursorPosition, buffer);
				// fflush(stdout);
			}
		}

		while (buffer[i] != '\0') {
			if (buffer[i] == '\n') {
				y++;
				x = 0;
			} else {
	
    BeginShaderMode(shader);
		SetShaderValue(shader, GetShaderLocation(shader, "replaceColor"), (float[4]){0.0f, 0.0f, 0.0f, 1.0f}, SHADER_UNIFORM_VEC4);
		SetShaderValue(shader, GetShaderLocation(shader, "newColor"), (float[4]){1.0f, 0.0f, 0.0f, 1.0f}, SHADER_UNIFORM_VEC4);
			// DrawTextureRec(fontAtlas, (Rectangle){ ((buffer[i] - 32) % 16) * TILE, (int)((buffer[i] - 32) / 16) * TILE, TILE, TILE }, (Vector2){ x * TILE, y * TILE }, WHITE);
			DrawTexturePro(fontAtlas, (Rectangle){((buffer[i] - 32) % 16) * TILE, (int)((buffer[i] - 32) / 16) * TILE, TILE, TILE}, (Rectangle){ x * TILE * SCALE, y * TILE * SCALE, TILE * SCALE, TILE * SCALE }, (Vector2){ 0, 0}, 0, WHITE);
	EndShaderMode();
				x++;
			}
			// printf("Drawing Char %c\n", buffer[i]);
			// fflush(stdout);
			i++;
		}
		i = 0;
		y = 0;
		x = 0;
		EndDrawing();
	}

	UnloadTexture(fontAtlas);
	UnloadShader(shader);

	CloseWindow();
	return 0;
}