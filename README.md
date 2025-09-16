# SDL++

A C++ wrapper around SDL2

## Features
- Built in preset of colors
- Custom objects (rect, ttf, asset)
- Easier input handling (clicks, keystate)
- Error handling & checks done automatically

## Build
- Install [MinGW](https://sourceforge.net/projects/mingw-w64/?utm_source=chatgpt.com) on your windows system
- Download latest from [Releases](https://github.com/qabirrrr/sdl-wrapper/releases)

Extract SDL++ and put it in your C: drive

### CMake
Set the base & add-on paths
<pre>
 set(BASE_PATH "C:/SDL2++/Base")
 set(ADD_ON_PATH "C:/SDL2++/Add-On")
</pre>

Add includes & lib
<pre>
 include_directories(
     ${BASE_PATH}/include ${ADD_ON_PATH}/include 
 )

 link_directories(
     ${BASE_PATH}/lib ${ADD_ON_PATH}/lib
 )
</pre>

Link everything together
<pre>
 target_link_libraries(ProjectName SDL2++ mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
</pre>

If you want to only use SDL2, you can just use the dependencies from the Base folder

If you're using SDL++, use everything in Base & Add-On folders

## Demo
 
- Render a rectangle
- Left click on it to equip it, left click again to unequip
- Press UP to increase its size, DOWN to decrease its size

<pre>
#include &lt;SDL++&gt;

int main(int argc, char* args[])
{
    sdl::init("SDL++ (Demo)", 1280, 720, 0);

    sdl::rect rect((1280-80)/2, (720-80)/2, 80, 80);
    int state = 0;

    while (sdl::running)
    {
        sdl::handle_events();

        // logic
        if (rect.mouse_clicked_left())
        {
            state = (state + 1) % 2;
        }

        if (state != 0)
        {
            if (sdl::keys::held(SDL_SCANCODE_UP))
            {
                rect.w += 1;
                rect.h += 1;
            }
            if (sdl::keys::held(SDL_SCANCODE_DOWN))
            {
                rect.w -= 1;
                rect.h -= 1;
            }
            rect.x = sdl::mouse_pos.x - (rect.w/2);
            rect.y = sdl::mouse_pos.y - (rect.h/2);
        }

        // render
        sdl::render::color(sdl::colors::BLUE); // blue background
        sdl::render::clear();

        rect.render_fill();

        sdl::render::present();
        sdl::update();
    }
    sdl::cleanup();
    return 0;
}
</pre>

## Contact
If you encounter any bugs or issues with this library, feel free to email me at qabirrrr@gmail.com
