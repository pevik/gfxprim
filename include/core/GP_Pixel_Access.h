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
 * Copyright (C) 2011      Tomas Gavenciak <gavento@ucw.cz>                  *
 *                                                                           *
 *****************************************************************************/

#ifndef GP_PIXEL_ACCESS_H
#define GP_PIXEL_ACCESS_H

#include "GP_Context.h"
#include "GP_FnPerBpp.h"
#include "GP_Pixel.h"

/* 
 * Generated header
 */
#include "GP_Pixel_Access.gen.h"

/*
 * GetPixel with context transformations and clipping.
 * Returns 0 for clipped pixels or pixels outside bitmap.
 */
GP_Pixel GP_GetPixel_(GP_Context *context, int x, int y);

/*
 * Version of GetPixel without transformations nor border checking.
 */
static inline GP_Pixel GP_GetPixel_Raw(GP_Context *context, int x, int y)
{
	GP_FN_RET_PER_BPP(GP_GetPixel_Raw, context->bpp, context->bit_endian, 
		context, x, y);
}

/*
 * PutPixel with context transformations and clipping.
 * NOP for clipped pixels or pixels outside bitmap.
 */
void GP_PutPixel_(GP_Context *context, int x, int y, GP_Pixel p);

/*
 * Version of PutPixel without transformations nor border checking.
 */
static inline void GP_PutPixel_Raw(GP_Context *context, int x, int y, GP_Pixel p)
{
	GP_FN_PER_BPP(GP_PutPixel_Raw, context->bpp, context->bit_endian, 
		context, x, y, p);
}

#endif /* GP_PIXEL_ACCESS_H */