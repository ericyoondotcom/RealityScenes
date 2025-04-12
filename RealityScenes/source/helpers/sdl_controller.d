module helpers.sdl_controller;
import std.stdio;
import std.string;
import std.conv;
import core.runtime;
import std.path;
import bindbc.sdl;
import bindbc.loader;

class SDLController {
    public SDL_Window* window = null;
    public SDL_Renderer* renderer = null;

    public this() {
        loadSDL();

        if(!SDL_Init(SDL_INIT_VIDEO)) { // in SDL3, this returns a bool (success) and not an int (0 = success)
            throw new Exception("Failed to initialize SDL: " ~ SDL_GetError().to!string);
            return;
        }
        writeln("SDL initialized");
    }

    public void createWindow() {
        window = SDL_CreateWindow("Rhythm Game Studio", 960, 540, 0);
        if(window is null) throw new Exception("Failed to create SDL window: " ~ SDL_GetError().to!string);

        renderer = SDL_CreateRenderer(window, null);
        if(renderer is null) throw new Exception("Failed to create SDL renderer: " ~ SDL_GetError().to!string);
    }

    public ~this() {
        if(renderer !is null) SDL_DestroyRenderer(renderer);
        if(window !is null) SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
