#include <cairo/cairo.h>
#include <iostream>

int main()
{
    cairo_surface_t *canvas;
    cairo_t *cr;

    canvas=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,1280,690);
    cr=cairo_create(canvas);
    cairo_set_source_rgb(cr,130,120,0);
    cairo_set_line_width(cr,1);
    cairo_move_to(cr,50,50);
    cairo_line_to(cr,2,2);
    cairo_stroke(cr);
    cairo_destroy(cr);
    cairo_surface_write_to_png(canvas,"hello.png");
    cairo_surface_destroy(canvas);

    return 0;
}