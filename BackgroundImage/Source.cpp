/* you may get a warning
* Libpng-1.6 is more stringent about checking ICC profiles than previous versions. You can ignore the warning. To get rid of it, remove the iCCP chunk from the PNG image.

Some applications treat warnings as errors; if you are using such an application you do have to remove the chunk. You can do that with any of a variety of PNG editors such as ImageMagick's convert in.png out.png.

To remove the invalid iCCP chunk from all of the PNG files in a folder (directory), you can use ImageMagick's mogrify *.png, provided that your ImageMagick was built with libpng16 (run convert -list format | grep PNG to be sure of that).
*/


#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

int main(int argc, char **argv){

	const float FPS = 60;
	const int SCREEN_W = 900;
	const int SCREEN_H = 800;
	int duck_width = 0;
	int duck_height = 0;
	int drawFlip = 0;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	float duck_x = 100;
	float duck_y = 100;
	float duck_dx = -4.0, duck_dy = 4.0;
	float angle = 0;
	bool rotating = false;
	int direction = 1;
	bool moving = true;
	bool redraw = true;
	ALLEGRO_BITMAP *image=NULL;
	ALLEGRO_BITMAP *duck = NULL;

	if(!al_init()) {
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		al_destroy_timer(timer);
		return -1;
	}


	al_install_keyboard();
	al_init_image_addon();
	image = al_load_bitmap("cool.png");
	duck = al_load_bitmap("duck.png");
	duck_width = al_get_bitmap_width(duck);
	duck_height = al_get_bitmap_height(duck);
	al_convert_mask_to_alpha(duck, al_map_rgb(255, 0, 255));
	event_queue = al_create_event_queue();
	if(!event_queue) {
		al_destroy_bitmap(duck);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0,0,0));

	al_flip_display();

	al_start_timer(timer);

	while(1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (moving)
			{
				duck_x += duck_dx;
				duck_y += duck_dy;
			}

			// Start rotation when the image reaches the left or right edge.
			if (duck_x <= 0)
			{
				duck_x = 0;
				rotating = true;
				direction = 1;
				duck_dx = 4.0;
				duck_dy = 0;
			}
			else if (duck_x >= SCREEN_W - duck_width)
			{
				duck_x = SCREEN_W - duck_width;
				rotating = true;
				direction = 3;
				duck_dx = -4.0;
				duck_dy = 0;
			}

			// Start rotation when the image reaches the top or bottom edge.
			if (duck_y <= 0)
			{
				duck_y = 0;
				rotating = true;
				direction = 2;
				duck_dx = 0;
				duck_dy = 4.0;
			}
			else if (duck_y >= SCREEN_H - duck_height)
			{
				duck_y = SCREEN_H - duck_height;
				rotating = true;
				direction = 0;
				duck_dx = 0;
				duck_dy = -4.0;
			}
			// Rotate the image until it turns about 3.14 radians.
			if (rotating)
			{
				angle += 0.1;

				if (angle >= 3.14)
				{
					angle = 0;
					rotating = false;
				}
			}

			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		//Direction controls
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
			{
				// Spacebar stops the image.
				moving = false;
				duck_dx = 0;
				duck_dy = 0;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				direction = 1;
				moving = true;
				duck_dx = 4.0;
				duck_dy = 0;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				direction = 3;
				moving = true;
				duck_dx = -4.0;
				duck_dy = 0;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
			{
				direction = 0;
				moving = true;
				duck_dx = 0;
				duck_dy = -4.0;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
			{
				direction = 2;
				moving = true;
				duck_dx = 0;
				duck_dy = 4.0;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_bitmap(image,0,0,0);
			// Flip the bitmap so it faces the direction selected by the arrow key.
			drawFlip = 0;

			if (direction == 1)
			{
				//Right
				drawFlip = 0;
			}
			else if (direction == 3)
			{
				//Left
				drawFlip = ALLEGRO_FLIP_HORIZONTAL;
			}
			else if (direction == 0)
			{
				//Up
				drawFlip = ALLEGRO_FLIP_VERTICAL;
			}
			else if (direction == 2)
			{
				//Down
				drawFlip = 0;
			}
			if (rotating)
			{
				// Rotate around the center of the bitmap.
				al_draw_rotated_bitmap(
					duck,
					duck_width / 2,
					duck_height / 2,
					duck_x + duck_width / 2,
					duck_y + duck_height / 2,
					angle,
					drawFlip
				);
			}
			else
			{
				al_draw_bitmap(duck, duck_x, duck_y, drawFlip);
			}

			al_flip_display();
		}
	}

	al_destroy_bitmap(duck);
	al_destroy_bitmap(image);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	system("pause");
	return 0;
}