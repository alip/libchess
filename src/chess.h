/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2009 Ali Polatel <polatel@gmail.com>
 *
 * This file is part of the libchess library. libchess is free software; you
 * can redistribute it and/or modify it under the terms of the GNU Lesser
 * General Public License version 2.1, as published by the Free Software
 * Foundation.
 *
 * libchess is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef LIBCHESS_GUARD_CHESS_H
#define LIBCHESS_GUARD_CHESS_H 1

/* Colours */
#define CHESS_WHITE                 0
#define CHESS_BLACK                 1

/* Pieces */
#define CHESS_PAWN      1
#define CHESS_KNIGHT    2
#define CHESS_BISHOP    3
#define CHESS_ROOK      4
#define CHESS_QUEEN     5
#define CHESS_KING      6

int chess_switch_side(int side);
int chess_rank(int square);
int chess_file(int square);
char chess_filec(int square);

#endif // LIBCHESS_GUARD_CHESS_H

