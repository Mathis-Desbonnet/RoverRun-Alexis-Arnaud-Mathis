# RoverRun Set-Up
 
To install and run the project :

- Clone the main branch
- Execute `git submodule init`
- Execute `git submodule update`
- Reload CMake Project
- Build the app
- Then you can run it!
-------------------------------------------------------
**WARNING ON WINDOWS ! (or if you get the 0xC0000135 error)**

You'll find on the folders `cmake-build-debug/vendors/SDL` and `cmake-build-debug/vendors/SDL_image` files names respectively `SDL3.dll` and `SDL3_image.dll`.

**IT IS VERY IMPORTANT TO COPY THEM INTO THE FOLDER** `cmake-build-debug/`.

If it still doesn't work, you may have to install the .net framework.

Then you can re-build the app and run it safely!

--------------------------------------------------------

Also, sometimes SDL (and mostly SDL_images) have some problem in memory allocation.

If you get the error 0xC0000005, just re-start the program.

If there is another problem, please tell us ASAP!

--------------------------------------------------------

Have fun!
