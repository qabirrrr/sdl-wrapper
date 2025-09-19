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
    // Initialize SDL2
    sdl::init("SDL++ (Demo)", 1280, 720, 0); 

    // Create a rectangle
    sdl::rect_t rect((1280-80)/2, (720-80)/2, 80, 80);

    int state = 0; 

    // Loop if app is running
    while (sdl::running())
    {   
        // Handle events
        sdl::handle_events();

        // Change state when left clicked
        if (rect.left_clicked())
        {
            state = (state + 1) % 2;
        }

        if (state != 0)
        {
            // Change color to red
            rect.edit_color(sdl::colors::RED);

            // Size grows
            if (sdl::keys::held(SDL_SCANCODE_UP)) 
            {
                rect.w += 1;
                rect.h += 1;
            }

            // Size shrinks
            if (sdl::keys::held(SDL_SCANCODE_DOWN))
            {
                rect.w -= 1;
                rect.h -= 1;
            }

            // Place mouse cursor at the center of the rect
            rect.x = sdl::get_mousepos().x - (rect.w/2);
            rect.y = sdl::get_mousepos().y - (rect.h/2);
        }

        else 
        {
            // Change color to black again
            rect.edit_color(sdl::colors::BLACK);
        }

        // Clear renderer & set background to blue
        sdl::render::color(sdl::colors::BLUE); 
        sdl::render::clear();

        // Render rect
        rect.render_fill();

        // Display
        sdl::render::present();

        // Update
        sdl::update();
    }
    
    // Clean up everything
    sdl::cleanup();
    return 0;
}
</pre>

## Contact
If you encounter any bugs or issues with this library, feel free to email me at qabirrrr@gmail.com
