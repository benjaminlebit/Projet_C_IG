#include "ei_types.h"
#include "ei_widget.h"
#include <stdlib.h>
#include <stdio.h>

ei_widget_t *root_widget_window = NULL;
ei_surface_t main_window_surface = NULL;

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
	//ei_widget_t * root_widget_window = ei_widget_create("frame",root_widget_window);
	//ei_surface_t picking_surface = hw_surface_create(main_window,main_window_size,EI_FALSE);

	hw_init();
	main_window_surface = hw_create_window(main_window_size, fullscreen);

	//registers all classes of widget and all geometry managers : TODO
	ei_frame_register_class();
	ei_button_register_class();
	ei_toplevel_register_class();
	
	//hw_surface_lock(main_window);
}

ei_widget_t *ei_app_root_widget()
{
	return root_widget_window;
}

ei_surface_t ei_app_root_surface()
{
	return main_window_surface;
}


void ei_app_free()
{
	/* ei_widget_t *root = ei_app_root_widget(); */
	/* ei_widget_destroy (root); */
	/* hw_quit(); */
}

void ei_app_quit_request()
{

}

static void affiche_widget_rec(ei_widget_t *widget, ei_rect_t* clipper)
{
	widget->wclass->drawfunc (widget, main_window_surface, main_window_surface, clipper);
	
	if (widget->next_sibling != NULL)
		affiche_widget_rec(widget->next_sibling, clipper);
	
	if (widget->children_head != NULL)
		affiche_widget_rec(widget->children_head, widget->content_rect);
		
}

void ei_app_run()
{
	/* ei_bool_t quit_app = EI_FALSE; */

	/* while (quit_app == EI_FALSE) */
	/* { */
	/* 	if (ei_app_quit_request()) */
	/* 	{ */
	/* 		quit_app = EI_TRUE; */
	/* 	} */
	/* 	//gestion de l'affichage : TODO */
	/* 	//hw_event_wait_next(); */
	/* 	//gestion des evenements : TODO */
	/* } */
	
	ei_rect_t*		clipper_ptr	= NULL;
	affiche_widget_rec(root_widget_window, clipper_ptr);
	getchar();
}

void ei_app_invalidate_rect(ei_rect_t* rect)
{
	
}
