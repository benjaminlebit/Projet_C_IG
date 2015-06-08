#include "ei_draw.h"
#include "ei_types.h"
#include "ei_widgetclass.h"
#include "ei_widget.h"
#include "widgetbutton.h"
#include "widgetframe.h"
#include "ei_placer.h"
#include <stdlib.h>
#include <assert.h>
#include "ei_application.h"
#include "global.h"
// void		ei_callback_t	(ei_widget_t*		widget,
// 				 struct ei_event_t*	event,
// 				 void*			user_param)
// {
// }


ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
							 ei_widget_t*		parent)
{
	ei_widgetclass_t *class = ei_widgetclass_from_name(class_name);
	if (class == NULL)
	{
		return NULL;
		exit(0);
	}
	/* void * memsize = class->allocfunc(); */
	/* ei_frame_t* new_widget = malloc(sizeof(*memsize)); */
	ei_widget_t *new_widget = class->allocfunc();

	new_widget->wclass = class;
	new_widget->parent = parent;
	new_widget->children_head = NULL;
	new_widget->children_tail = NULL;
	new_widget->next_sibling = NULL;
	new_widget->placer_params = NULL;
	if (parent != NULL)
	{
		//Le widget créé est le seul fils de parent :
		if (parent->children_head == NULL)
		{
			parent->children_head = (new_widget);
			parent->children_tail = (new_widget);
		}
		else
		{
			parent->children_tail->next_sibling = new_widget;
			parent->children_tail = new_widget;
		}
		/* ei_widget_t *tmp = parent->next_sibling; */
		/* while(tmp != NULL) */
		/* { */
		/* 	tmp = tmp->next_sibling; */
		/* } */
		
		/* tmp->next_sibling = (new_widget); */
	}

	class->setdefaultsfunc(new_widget);
	new_widget->pick_id = widget_id_pick;
	new_widget->pick_color = id_to_color(ei_app_root_surface(),widget_id_pick);
	widget_id_pick++;
	return new_widget;
}

void			ei_widget_destroy		(ei_widget_t*		widget)
{
	if (widget->children_head == NULL)
	{
		free(widget);
	}
	else
	{
		ei_widget_destroy (widget->children_head);
	}
}


ei_widget_t*		ei_widget_pick			(ei_point_t*		where)
{
	ei_widget_t* widget = malloc (sizeof(ei_widget_t));
	widget = ei_app_root_widget();
	uint32_t* pixel_ptr = (uint32_t*)(hw_surface_get_buffer(picking_surface) 
	+ where->y*hw_surface_get_size(picking_surface).width + where->x);
	while (widget!= NULL)
	{
		if (widget != ei_app_root_widget())
		{
			if (widget->pick_id == *pixel_ptr)
			{
				return widget;
			}
		}
		widget = widget->next_sibling;
	}
	return NULL;
}




void			ei_frame_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 const ei_color_t*	color,
							 int*			border_width,
							 ei_relief_t*		relief,
							 char**			text,
							 ei_font_t*		text_font,
							 ei_color_t*		text_color,
							 ei_anchor_t*		text_anchor,
							 ei_surface_t*		img,
							 ei_rect_t**		img_rect,
							 ei_anchor_t*		img_anchor)
{

	ei_frame_t* frame = (ei_frame_t*) widget;
	if (requested_size != NULL)
		frame->widget.requested_size = *requested_size;
	if (color != NULL)
		frame->color = *color;
	if (border_width != NULL)
		frame->border_size = *border_width;
	if (relief!=NULL)
		frame->relief = *relief;
	else 
		frame->relief = 0;
	if (text!=NULL)
		frame->texte = *text;
	if (text_font!=NULL)
		frame->font = *text_font;
	if (text_color!=NULL)
		frame->text_color = text_color;
	if (text_anchor!=NULL)
		frame->text_anchor = *text_anchor;
	if (img != NULL)
		frame->img = *img;
	if (img_rect != NULL)
		frame->img_rect = *img_rect;
	if (img_anchor!=NULL)
	 	frame->img_anchor = *img_anchor;
	if (frame->widget.parent == NULL){
		ei_size_t taille = {600,600};
		ei_point_t coin = {0,0};
		ei_rect_t loc = {coin, taille};
		frame->widget.screen_location = loc;
		frame->widget.content_rect = &loc;
	} else {
		/* ei_size_t taille = *requested_size; */
		/* ei_point_t coin = {150,200}; */
		/* ei_rect_t loc = {coin, taille}; */
		/* frame->widget.screen_location = loc; */
		/* frame->widget.content_rect = &loc; */
		frame->clipper = NULL;
	}
}


void			ei_button_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 const ei_color_t*	color,
							 int*			border_width,
							 int*			corner_radius,
							 ei_relief_t*		relief,
							 char**			text,
							 ei_font_t*		text_font,
							 ei_color_t*		text_color,
							 ei_anchor_t*		text_anchor,
							 ei_surface_t*		img,
							 ei_rect_t**		img_rect,
							 ei_anchor_t*		img_anchor,
							 ei_callback_t*		callback,
							 void**			user_param)
{
	ei_button_t* button = (ei_button_t*) widget;
	if (requested_size != NULL)
		button->widget.requested_size = *requested_size;
	if (color != NULL)
		button->color = *color;
	if (border_width != NULL)
		button->border_size = *border_width;
	if (relief!=NULL)
		button->relief = *relief;
	else 
		button->relief = 0;
	if (text!=NULL)
		button->texte = *text;
	if (text_font!=NULL)
		button->font = *text_font;
	if (text_color!=NULL)
		button->text_color = text_color;
	if (text_anchor!=NULL)
		button->text_anchor = *text_anchor;
	if (img != NULL)
		button->img = *img;
	if (img_rect != NULL)
		button->img_rect = *img_rect;
	if (img_anchor!=NULL)
	 	button->img_anchor = *img_anchor;
	if (corner_radius!=NULL)
		button->corner_radius = corner_radius;
	if (callback!=NULL)
		button->callback = *callback;
	if (user_param != NULL)
		button->user_param = *user_param;
}


void			ei_toplevel_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 ei_color_t*		color,
							 int*			border_width,
							 char**			title,
							 ei_bool_t*		closable,
							 ei_axis_set_t*		resizable,
						 	 ei_size_t**		min_size)
{
}
