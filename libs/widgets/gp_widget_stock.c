//SPDX-License-Identifier: LGPL-2.0-or-later

/*

   Copyright (c) 2014-2021 Cyril Hrubis <metan@ucw.cz>

 */

#include <string.h>
#include <json-c/json.h>

#include <gp_widgets.h>

static unsigned int stock_min_w(gp_widget *self, const gp_widget_render_ctx *ctx)
{
	(void)ctx;

	return self->stock->min_size;
}

static unsigned int stock_min_h(gp_widget *self, const gp_widget_render_ctx *ctx)
{
	(void)ctx;

	return self->stock->min_size;
}

static void render_stock_err_warn(const gp_widget_render_ctx *ctx,
                                  gp_coord x, gp_coord y,
                                  gp_size w, gp_size h, gp_pixel color)
{
	gp_pixmap *pix = ctx->buf;

	gp_coord cx = x + w/2;
	gp_coord cy = y + h/2;
	gp_size c = GP_MIN(w, h)/2 - 2;
	gp_size r = c/5;

	gp_fill_rrect_xywh(pix, x, y, w, h, ctx->bg_color, color, ctx->text_color);

	if (r > 1)
		gp_fill_circle(pix, cx, cy+h/4, r, ctx->text_color);
	else
		gp_fill_rect_xyxy(pix, cx-r, cy+h/4-r, cx+r, cy+h/4+r, ctx->text_color);

	gp_fill_rect_xyxy(pix, cx-r, cy-h/4-r, cx+r, cy+r, ctx->text_color);
}

static void render_stock_info(const gp_widget_render_ctx *ctx,
                              gp_coord x, gp_coord y,
                              gp_size w, gp_size h)
{
	gp_pixmap *pix = ctx->buf;

	gp_size c = GP_MIN(w, h)/2 - 2;
	gp_size r = c/5;
	gp_coord cx = x + w/2;
	gp_coord cy = y + h/2;

	gp_fill_rrect_xywh(pix, x, y, w, h, ctx->bg_color, ctx->sel_color, ctx->text_color);

	if (r > 1)
		gp_fill_circle(pix, cx, cy-h/4, r, ctx->text_color);
	else
		gp_fill_rect_xyxy(pix, cx-r, cy-h/4-r, cx+r, cy-h/4+r, ctx->text_color);

	gp_fill_rect_xyxy(pix, cx-r, cy+h/4, cx+r, cy-r, ctx->text_color);

	gp_fill_rect_xyxy(pix, cx-2*r, cy+h/4, cx+2*r, cy+h/4+r/2, ctx->text_color);

	gp_fill_rect_xyxy(pix, cx-2*r, cy-r, cx, cy-r+r/2, ctx->text_color);
}

static void render_stock_question(const gp_widget_render_ctx *ctx,
                                  gp_coord x, gp_coord y,
                                  gp_size w, gp_size h)
{
	gp_pixmap *pix = ctx->buf;

	gp_coord cx = x + w/2;
	gp_coord cy = y + h/2;
	gp_size c = GP_MIN(w, h)/2 - 2;
	gp_size r = c/5;

	gp_fill_rrect_xywh(pix, x, y, w, h, ctx->bg_color, ctx->sel_color, ctx->text_color);

	if (r > 1)
		gp_fill_circle(pix, cx, cy+h/4+r, r, ctx->text_color);
	else
		gp_fill_rect_xyxy(pix, cx-r, cy+h/4, cx+r, cy+h/4+2*r, ctx->text_color);

	gp_fill_rect_xyxy(pix, cx-r, cy-h/4+3*r, cx+r, cy+2*r, ctx->text_color);

	gp_fill_ring_seg(pix, cx, cy-h/4 + r, r, 3*r, GP_CIRCLE_SEG1 | GP_CIRCLE_SEG2 |GP_CIRCLE_SEG4, ctx->text_color);

	gp_fill_triangle(pix, cx-r, cy-h/4+3*r, cx, cy-h/4+2*r, cx, cy-h/4+3*r, ctx->text_color);
}

static void render_stock_speaker(const gp_widget_render_ctx *ctx,
                                 gp_coord cx, gp_coord cy, gp_coord r,
                                 gp_widget *self)
{
	gp_pixmap *pix = ctx->buf;
	gp_pixel col = self->focused ? ctx->sel_color : ctx->text_color;

	gp_coord poly[] = {
		cx-2*(r/2), cy-2*r/3,
		cx-4*(r/2), cy-2*r/3,
		cx-4*(r/2), cy+2*r/3,
		cx-2*(r/2), cy+2*r/3,
		cx-r/4, cy+3*(r/2),
		cx, cy+3*(r/2),
		cx, cy-3*(r/2),
		cx-r/4, cy-3*(r/2),
	};

	gp_fill_polygon(pix, GP_ARRAY_SIZE(poly)/2, poly, col);

	gp_coord rd = r/3;
	gp_coord i;

	if (rd < 1)
		cx++;

	switch (self->stock->type) {
	case GP_WIDGET_STOCK_SPEAKER_MUTE:
		for (i = 0; i <= (rd+1)/2; i++) {
			gp_line(pix, cx+r/2+i, cy-r/2, cx+3*(r/2), cy+r/2-i, ctx->alert_color);
			gp_line(pix, cx+r/2, cy-r/2+i, cx+3*(r/2)-i, cy+r/2, ctx->alert_color);
			gp_line(pix, cx+r/2+i, cy+r/2, cx+3*(r/2), cy-r/2+i, ctx->alert_color);
			gp_line(pix, cx+r/2, cy+r/2-i, cx+3*(r/2)-i, cy-r/2, ctx->alert_color);
		}
	break;
	case GP_WIDGET_STOCK_SPEAKER_MIN:
	break;
	case GP_WIDGET_STOCK_SPEAKER_MAX:
		gp_fill_ring_seg(pix, cx+r/2, cy, 2*(r/2)+1, 2*(r/2)+1+rd, GP_CIRCLE_SEG1 | GP_CIRCLE_SEG4, col);
	/* fallthrough */
	case GP_WIDGET_STOCK_SPEAKER_MID:
		gp_fill_ring_seg(pix, cx+r/2, cy, r/3, r/3+rd, GP_CIRCLE_SEG1 | GP_CIRCLE_SEG4, col);
	break;
	default:
	break;
	}
}

static void render_stock_hardware(const gp_widget_render_ctx *ctx,
                                  gp_coord x, gp_coord y,
                                  gp_size w, gp_size h)
{
	gp_pixmap *pix = ctx->buf;
	gp_coord cx = x + w/2;
	gp_coord cy = y + h/2;
	gp_size c = GP_MIN(w, h)/3;
	gp_size dc = c/2;

	gp_coord l_end = GP_MIN(w, h)/2-c;
	gp_coord l_start = dc/10+2;
	gp_coord l_size = 1 + c/9;
	gp_coord sp_size = 1 + c/20;
	gp_coord c_sp_size = 1 + c/8;
	gp_coord legs = (2*c - 2*c_sp_size + sp_size)/(l_size + sp_size);
	gp_coord i;

	gp_fill_rect_xywh(pix, x, y, w, h, ctx->bg_color);

	gp_fill_rect_xyxy(pix, cx-c, cy-c, cx+c, cy+c, ctx->text_color);

	gp_fill_circle(pix, cx-c+c/2, cy-c+c/2, c/8, ctx->bg_color);

	c_sp_size = (2*c - legs*l_size - (legs-1) * sp_size+1)/2;


	for (i = 0; i < legs; i++) {
		gp_coord off = -c + c_sp_size + i * (l_size + sp_size);

		gp_fill_rect_xyxy(pix, cx+off, cy-c-l_start, cx+off+l_size-1, cy-c-l_end, ctx->text_color);
		gp_fill_rect_xyxy(pix, cx+off, cy+c+l_start, cx+off+l_size-1, cy+c+l_end, ctx->text_color);

		gp_fill_rect_xyxy(pix, cx-c-l_start, cy+off, cx-c-l_end, cy+off+l_size-1, ctx->text_color);
		gp_fill_rect_xyxy(pix, cx+c+l_start, cy+off, cx+c+l_end, cy+off+l_size-1, ctx->text_color);
	}
}

static void render_stock_software(const gp_widget_render_ctx *ctx,
                                  gp_coord x, gp_coord y,
                                  gp_size w, gp_size h)
{
	gp_pixmap *pix = ctx->buf;
	gp_coord cx = x + w/2;
	gp_coord cy = y + h/2;
	gp_size c = GP_MIN(w, h)/3;
	gp_size dc = GP_ODD_UP(c/4)+2;
	gp_coord i;

	gp_fill_rect_xywh(pix, x, y, w, h, ctx->bg_color);

	gp_fill_rect_xyxy(pix, cx-c, cy-c, cx+c, cy+c, ctx->text_color);
	gp_hline_xxy(pix, cx-c, cx+c, cy-c+dc, ctx->fg_color);

	gp_size r = dc/2-1-dc/6;

	for (i = 0; i < 3; i++) {
		gp_size roff = r ? dc/2 : 1;
		gp_size off = r ? 3*r+1 : 2;

		gp_fill_circle(pix, cx+c-roff-i*off, cy-c+dc/2, r, ctx->bg_color);
	}
}

static void stock_render(gp_widget *self, const gp_offset *offset,
                         const gp_widget_render_ctx *ctx, int flags)
{
	gp_coord x = self->x + offset->x;
	gp_coord y = self->y + offset->y;
	gp_coord cx = x + self->w/2;
	gp_coord cy = y + self->h/2;
	gp_coord r = GP_MIN(self->w/2, self->h/2);

	(void)flags;

	switch (self->stock->type) {
	case GP_WIDGET_STOCK_SPEAKER_MIN:
	case GP_WIDGET_STOCK_SPEAKER_MAX:
	case GP_WIDGET_STOCK_SPEAKER_MID:
	case GP_WIDGET_STOCK_SPEAKER_MUTE:
		gp_fill_rect_xywh(ctx->buf, x, y, self->w, self->h, ctx->bg_color);
		render_stock_speaker(ctx, cx, cy, r/2, self);
	break;
	case GP_WIDGET_STOCK_INFO:
		render_stock_info(ctx, x, y, self->w, self->h);
	break;
	case GP_WIDGET_STOCK_WARN:
		render_stock_err_warn(ctx, x, y, self->w, self->h, ctx->warn_color);
	break;
	case GP_WIDGET_STOCK_ERR:
		render_stock_err_warn(ctx, x, y, self->w, self->h, ctx->alert_color);
	break;
	case GP_WIDGET_STOCK_QUESTION:
		render_stock_question(ctx, x, y, self->w, self->h);
	break;
	case GP_WIDGET_STOCK_HARDWARE:
		render_stock_hardware(ctx, x, y, self->w, self->h);
	break;
	case GP_WIDGET_STOCK_SOFTWARE:
		render_stock_software(ctx, x, y, self->w, self->h);
	break;
	}

	gp_widget_ops_blit(ctx, x, y, self->w, self->h);
}

static struct stock_types {
	const char *str_type;
	enum gp_widget_stock_type type;
} stock_types[] = {
	{"err", GP_WIDGET_STOCK_ERR},
	{"warn", GP_WIDGET_STOCK_WARN},
	{"info", GP_WIDGET_STOCK_INFO},
	{"question", GP_WIDGET_STOCK_QUESTION},

	{"speaker_min", GP_WIDGET_STOCK_SPEAKER_MIN},
	{"speaker_mid", GP_WIDGET_STOCK_SPEAKER_MID},
	{"speaker_max", GP_WIDGET_STOCK_SPEAKER_MAX},
	{"speaker_mute", GP_WIDGET_STOCK_SPEAKER_MUTE},

	{"hardware", GP_WIDGET_STOCK_HARDWARE},
	{"software", GP_WIDGET_STOCK_SOFTWARE},
};

static int gp_widget_stock_type_from_str(const char *type)
{
	unsigned int i;

	for (i = 0; i < GP_ARRAY_SIZE(stock_types); i++) {
		if (!strcmp(type, stock_types[i].str_type))
			return stock_types[i].type;
	}

	return -1;
}

static const char *gp_widget_stock_type_name(enum gp_widget_stock_type type)
{
	unsigned int i;

	for (i = 0; i < GP_ARRAY_SIZE(stock_types); i++) {
		if (stock_types[i].type == type)
			return stock_types[i].str_type;
	}

	return NULL;
}

static gp_widget *stock_from_json(json_object *json, gp_htable **uids)
{
	const char *stock = NULL;
	int type, min_size = -1;

	(void)uids;

	json_object_object_foreach(json, key, val) {
		if (!strcmp(key, "stock"))
			stock = json_object_get_string(val);
		else if (!strcmp(key, "min_size"))
			min_size = json_object_get_int(val);
		else
			GP_WARN("Invalid stock key '%s'", key);
	}

	if (!stock) {
		GP_WARN("Missing stock type");
		return NULL;
	}

	type = gp_widget_stock_type_from_str(stock);
	if (type < 0) {
		GP_WARN("Unknown stock '%s'", stock);
		return NULL;
	}

	return gp_widget_stock_new(type, min_size);
}

static int stock_event(gp_widget *self, const gp_widget_render_ctx *ctx, gp_event *ev)
{
	(void) ctx;

	if (ev->type != GP_EV_KEY)
		return 0;

	if (ev->code == GP_EV_KEY_UP)
		return 0;

	switch (ev->val) {
	case GP_BTN_LEFT:
	case GP_BTN_PEN:
	case GP_KEY_ENTER:
	        gp_widget_send_widget_event(self, 0);
		return 1;
	}

	return 0;
}

struct gp_widget_ops gp_widget_stock_ops = {
	.min_w = stock_min_w,
	.min_h = stock_min_h,
	.render = stock_render,
	.event = stock_event,
	.from_json = stock_from_json,
	.id = "stock",
};

gp_widget *gp_widget_stock_new(enum gp_widget_stock_type type, int min_size)
{
	const gp_widget_render_ctx *ctx = gp_widgets_render_ctx();
	gp_widget *ret;

	if (!gp_widget_stock_type_name(type)) {
		GP_WARN("Invalid stock type %u", type);
		return NULL;
	}

	ret = gp_widget_new(GP_WIDGET_STOCK, GP_WIDGET_CLASS_NONE, sizeof(struct gp_widget_stock));
	if (!ret)
		return NULL;

	if (min_size < 0)
		ret->stock->min_size = GP_ODD_UP(gp_text_ascent(ctx->font) + 2 * ctx->padd);
	else
		ret->stock->min_size = GP_ODD_UP((gp_text_ascent(ctx->font) + 4) * min_size);

	ret->stock->type = type;
	ret->no_events = 1;

	return ret;
}

void gp_widget_stock_type_set(gp_widget *self, enum gp_widget_stock_type type)
{
	GP_WIDGET_ASSERT(self, GP_WIDGET_STOCK, );

	if (self->stock->type == type)
		return;

	if (!gp_widget_stock_type_name(type)) {
		GP_WARN("Invalid stock type %u", type);
		return;
	}

	self->stock->type = type;
	gp_widget_redraw(self);
}
