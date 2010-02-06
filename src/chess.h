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

#include <stdbool.h>

/**
 * \file
 * Main include file
 **/

/**
 * This define represents the white side.
 **/
#define CHESS_WHITE 0
/**
 * This define represents the black side.
 **/
#define CHESS_BLACK 1

/**
 * This define is used to represents pawn.
 **/
#define CHESS_PAWN      1
/**
 * This define is used to represents knight.
 **/
#define CHESS_KNIGHT    2
/**
 * This define is used to represents a bishop.
 **/
#define CHESS_BISHOP    3
/**
 * This define is used to represents a rook.
 **/
#define CHESS_ROOK      4
/**
 * This define is used to represents a queen.
 **/
#define CHESS_QUEEN     5
/**
 * This define is used to represents a king.
 **/
#define CHESS_KING      6

/**
 * Switches the side from white to black or vice versa.
 **/
int chess_switch_side(int side);
/**
 * Returns the rank on which the given square is located.
 **/
int chess_rank(int square);
/**
 * Returns the file on which the given square is located.
 **/
int chess_file(int square);
/**
 * Returns the file on which the given square is located represented as a char
 * (a-h).
 **/
char chess_file_char(int square);
/**
 * Returns the square on given rank and file.
 **/
int chess_square(int rank, int file);
/**
 * Returns the square that is located on the left of the given square.
 * If the given square is on the left border this function returns -1.
 **/
int chess_square_left(int square);
/**
 * Returns the square that is located on the right of the given square.
 * If the given square is on the right border this function returns -1.
 **/
int chess_square_right(int square);
/**
 * Returns the square that is located above the given square.
 * If the given square is on top this function returns -1.
 **/
int chess_square_up(int square);
/**
 * Returns the square that is below the given square.
 * If the given square is on bottom this function returns -1.
 **/
int chess_square_down(int square);
/**
 * Returns true if the square is on the border.
 **/
bool chess_square_border(int square);
/**
 * Given the square notation (a1, b2, etc.) returns the index of the square.
 **/
int chess_square_index(const char *square);

/**
 * Returns the square notation of the given square index.
 * Returns NULL if the square index is invalid.
 **/
const char *chess_square_name(int square);

/**
 * Returns the character representation of the piece.
 **/
char chess_piece_char(int piece, int side);

/**
 * This structure represents a chess board.
 **/
struct chess_board {
    int side;                           /**< Side to move */
    int en_passant;                     /**< En passant square */
    int castling_flag;                  /**< Castling flags */
    int king_isq;                       /**< Initial square of the white king */
    int kingrook_isq;                   /**< Initial square of the white king rook */
    int queenrook_isq;                  /**< Initial square of the white queen rook */
    int rhmc;                           /**< Reversible half move counter */
    int fmc;                            /**< Full move counter */
    int cboard[64];                     /**< cboard[sq] gives the piece on square sq. */
    unsigned long long occupied[4];     /**< Occupied squares, (white, black, all, empty) */
    unsigned long long pieces[2][6];    /**< Pieces */
};

/**
 * Set piece to the given location on the board.
 **/
void chess_board_set_piece(struct chess_board *board_ptr, int square, int piece, int side);
/**
 * Get piece on the given square of the board.
 **/
int chess_board_get_piece(struct chess_board board, int square, int *piece_ptr, int *side_ptr);
/**
 * Clear the given piece on the given square of the board.
 **/
void chess_board_clear_piece(struct chess_board *board_ptr, int square, int piece, int side);
/**
 * Returns true if the given side has a piece on the given square.
 **/
bool chess_board_has_piece(struct chess_board board, int square, int side);

#endif // LIBCHESS_GUARD_CHESS_H

