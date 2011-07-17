/*****************************************************************************
 * This file is part of gfxprim library.                                     *
 *                                                                           *
 * Gfxprim is free software; you can redistribute it and/or                  *
 * modify it under the terms of the GNU Lesser General Public                *
 * License as published by the Free Software Foundation; either              *
 * version 2.1 of the License, or (at your option) any later version.        *
 *                                                                           *
 * Gfxprim is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Lesser General Public License for more details.                           *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public          *
 * License along with gfxprim; if not, write to the Free Software            *
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,                        *
 * Boston, MA  02110-1301  USA                                               *
 *                                                                           *
 * Copyright (C) 2009-2010 Jiri "BlueBear" Dluhos                            *
 *                         <jiri.bluebear.dluhos@gmail.com>                  *
 *                                                                           *
 * Copyright (C) 2009-2010 Cyril Hrubis <metan@ucw.cz>                       *
 *                                                                           *
 *****************************************************************************/

#include "GP_Gfx.h"
#include "core/GP_FnPerBpp.h"
#include "core/GP_DefFnPerBpp.h"

#include "algo/Circle.algo.h"

/* Generate drawing functions for various bit depths. */
GP_DEF_DRAW_FN_PER_BPP(GP_Circle, DEF_CIRCLE_FN)

void GP_Circle(GP_Context *context, GP_Coord xcenter, GP_Coord ycenter,
               GP_Size r, GP_Pixel pixel)
{
	GP_CHECK_CONTEXT(context);

	GP_FN_PER_BPP_CONTEXT(GP_Circle, context, context,
	                      xcenter, ycenter, r, pixel);
}

void GP_TCircle(GP_Context *context, GP_Coord xcenter, GP_Coord ycenter,
                GP_Size r, GP_Pixel pixel)
{
	GP_CHECK_CONTEXT(context);

	GP_TRANSFORM_POINT(context, xcenter, ycenter);
	
	GP_Circle(context, xcenter, ycenter, r, pixel);
}

#include "algo/FillCircle.algo.h"

/* Generate drawing functions for various bit depths. */
GP_DEF_FILL_FN_PER_BPP(GP_FillCircle, DEF_FILLCIRCLE_FN)

void GP_FillCircle(GP_Context *context, GP_Coord xcenter, GP_Coord ycenter,
                   GP_Size r, GP_Pixel pixel)
{
	GP_CHECK_CONTEXT(context);

	GP_FN_PER_BPP_CONTEXT(GP_FillCircle, context, context,
	                      xcenter, ycenter, r, pixel);
}

void GP_TFillCircle(GP_Context *context, GP_Coord xcenter, GP_Coord ycenter,
                    GP_Size r, GP_Pixel pixel)
{
	GP_CHECK_CONTEXT(context);
	
	GP_TRANSFORM_POINT(context, xcenter, ycenter);
	
	GP_FillCircle(context, xcenter, ycenter, r, pixel);
}

#include "algo/FillRing.algo.h"

/* Generate drawing functions for various bit depths. */
GP_DEF_FILL_FN_PER_BPP(GP_FillRing, DEF_FILLRING_FN)

void GP_FillRing(GP_Context *context, GP_Coord xcenter, GP_Coord ycenter,
                   GP_Size r1, GP_Size r2, GP_Pixel pixel)
{
	GP_CHECK_CONTEXT(context);

	GP_FN_PER_BPP_CONTEXT(GP_FillRing, context, context,
	                      xcenter, ycenter, r1, r2, pixel);
}

void GP_TFillRing(GP_Context *context, GP_Coord xcenter, GP_Coord ycenter,
                    GP_Size r1, GP_Size r2, GP_Pixel pixel)
{
	GP_CHECK_CONTEXT(context);
	
	GP_TRANSFORM_POINT(context, xcenter, ycenter);
	
	GP_FillRing(context, xcenter, ycenter, r1, r2, pixel);
}
