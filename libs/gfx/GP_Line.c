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
#include "algo/Line.algo.h"
#include "core/GP_FnPerBpp.h"

/* Generate drawing functions for various bit depths. */
DEF_LINE_FN(GP_Line1bpp_LE,  GP_Context *, GP_Pixel, GP_PutPixel1bpp_LE)
DEF_LINE_FN(GP_Line2bpp_LE,  GP_Context *, GP_Pixel, GP_PutPixel2bpp_LE)
DEF_LINE_FN(GP_Line4bpp_LE,  GP_Context *, GP_Pixel, GP_PutPixel4bpp_LE)
DEF_LINE_FN(GP_Line1bpp_BE,  GP_Context *, GP_Pixel, GP_PutPixel1bpp_BE)
DEF_LINE_FN(GP_Line2bpp_BE,  GP_Context *, GP_Pixel, GP_PutPixel2bpp_BE)
DEF_LINE_FN(GP_Line4bpp_BE,  GP_Context *, GP_Pixel, GP_PutPixel4bpp_BE)
DEF_LINE_FN(GP_Line8bpp,  GP_Context *, GP_Pixel, GP_PutPixel8bpp)
DEF_LINE_FN(GP_Line16bpp, GP_Context *, GP_Pixel, GP_PutPixel16bpp)
DEF_LINE_FN(GP_Line24bpp, GP_Context *, GP_Pixel, GP_PutPixel24bpp)
DEF_LINE_FN(GP_Line32bpp, GP_Context *, GP_Pixel, GP_PutPixel32bpp)

void GP_Line(GP_Context *context, int x0, int y0, int x1, int y1,
             GP_Pixel pixel)
{
	GP_CHECK_CONTEXT(context);

	GP_FN_PER_BPP(GP_Line, context->bpp, context, x0, y0, x1, y1, pixel);
}

void GP_TLine(GP_Context *context, int x0, int y0, int x1, int y1,
              GP_Pixel pixel)
{
	GP_CHECK_CONTEXT(context);
	
	GP_TRANSFORM_POINT(context, x0, y0);
	GP_TRANSFORM_POINT(context, x1, y1);
	
	GP_Line(context, x0, y0, x1, y1, pixel);
}