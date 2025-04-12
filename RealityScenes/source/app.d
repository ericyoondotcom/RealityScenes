import std.stdio;
import bindbc.sdl;
import helpers.sdl_controller;

void main()
{
	SDLController controller = new SDLController();
	controller.createWindow();
	bool quitOnNextFrame = false;
	while(!quitOnNextFrame) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_EVENT_QUIT) {
				quitOnNextFrame = true;
			}
		}
		SDL_SetRenderDrawColor(controller.renderer, 0, 50, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(controller.renderer);
		SDL_RenderPresent(controller.renderer);
	}
}

