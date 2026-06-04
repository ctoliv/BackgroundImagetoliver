# Lab 8 - Background Image and Rotating Bitmap

This repository contains my Lab 8 project for CPSC 440 Game Programming.

## Description

This lab uses Allegro to display a background image and a moving bitmap sprite. The program creates a 900 x 800 screen, loads a background image, loads a duck bitmap, and allows the duck to move around the screen using the arrow keys.

The duck can face different directions using bitmap flip flags. When the duck reaches the edge of the screen, it rotates about 3.14 radians before continuing.

## Features

- Creates a 900 x 800 display
- Loads and draws a background image
- Loads and draws a bitmap sprite
- Uses transparency for the duck image
- Uses `al_get_bitmap_width`
- Uses `al_get_bitmap_height`
- Uses `al_draw_bitmap`
- Uses `al_draw_rotated_bitmap`
- Uses `ALLEGRO_FLIP_HORIZONTAL`
- Uses `ALLEGRO_FLIP_VERTICAL`
- Arrow keys change the duck's direction
- Spacebar stops the duck
- Escape key closes the program
- Duck rotates when it reaches the edge of the screen

## Controls

- Up Arrow: Move duck up
- Down Arrow: Move duck down
- Left Arrow: Move duck left
- Right Arrow: Move duck right
- Spacebar: Stop the duck
- Escape: Close the program

## Project Files

- `Source.cpp` - Main program file with Allegro setup, image loading, keyboard input, movement, flipping, and rotation
- `cool.png` - Background image
- `duck.png` - Duck bitmap sprite

## How to Run

1. Open the project in Visual Studio.
2. Make sure Allegro is installed through NuGet.
3. Make sure the Addons is enabled.
4. Make sure `cool.png` and `duck.png` are in the project folder.
5. Build and run the project.
6. Use the arrow keys to move the duck and press Spacebar to stop it.

## Author

Christian Toliver
