# RoverRun
 
To install and run the project :

- Clone the main branch
- Execute `git submodule init`
- Execute `git submodule update`
- Reload CMake Project
- Build the app
- Then you can run it !

**WARNING ON WINDOWS ! (or if you get the 0xC0000135 error)**

You'll find on the folders `cmake-build-debug/vendors/SDL` and `cmake-build-debug/vendors/SDL_image` files names respectively `SDL3.dll` and `SDL3_image.dll`.

**IT IS VERY IMPORTANT TO COPY THEM INTO THE FOLDER** `cmake-build-debug/`.

If it still doesn't work, you may have to install the .net framework.

Then you can re-build the app and run it safely!

Have fun!
