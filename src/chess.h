/* vim: set cino= fo=croql sw=8 ts=8 sts=0 noet cin fdm=syntax : */

/*
 * Copyright (c) 2009, 2010 Ali Polatel <alip@exherbo.org>
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
#include <sys/types.h>

/**
 * \file
 * Main include file
 **/

/**
 * This define represents the white side.
 **/
#define CHESS_SIDE_WHITE 0
/**
 * This define represents the black side.
 **/
#define CHESS_SIDE_BLACK 1

/**
 * This define is used to represent pawn.
 **/
#define CHESS_PIECE_PAWN 1
/**
 * This define is used to represent knight.
 **/
#define CHESS_PIECE_KNIGHT 2
/**
 * This define is used to represent bishop.
 **/
#define CHESS_PIECE_BISHOP 3
/**
 * This define is used to represent rook.
 **/
#define CHESS_PIECE_ROOK 4
/**
 * This define is used to represent queen.
 **/
#define CHESS_PIECE_QUEEN 5
/**
 * This define is used to represent king.
 **/
#define CHESS_PIECE_KING 6

/**
 * This castling flag is used to represent white king side castle.
 **/
#define CHESS_CASTLE_KINGSIDE_WHITE 0x0001

/**
 * This castling flag is used to represent white queen side castle.
 **/
#define CHESS_CASTLE_QUEENSIDE_WHITE 0x0002

/**
 * This castling flag is used to represent black king side castle.
 **/
#define CHESS_CASTLE_KINGSIDE_BLACK 0x0004

/**
 * This castling flag is used to represent black queen side castle.
 **/
#define CHESS_CASTLE_QUEENSIDE_BLACK 0x0008

/**
 * This castling flag is used to represent white castle.
 **/
#define CHESS_CASTLE_WHITE (CHESS_CASTLE_KINGSIDE_WHITE | CHESS_CASTLE_QUEENSIDE_WHITE)

/**
 * This castling flag is used to represent black castle.
 **/
#define CHESS_CASTLE_BLACK (CHESS_CASTLE_KINGSIDE_BLACK | CHESS_CASTLE_QUEENSIDE_BLACK)

/**
 * Switches the side from white to black or vice versa.
 * \param side Side, either CHESS_WHITE or CHESS_BLACK
 **/
int
chess_switch_side(int side);

/**
 * Returns the rank on which the given square is located.
 **/
int
chess_rank(int square);

/**
 * Returns the file on which the given square is located.
 **/
int
chess_file(int square);

/**
 * Returns the file on which the given square is located represented as a char
 * (a-h).
 **/
char
chess_file_char(int square);

/**
 * Returns the square on given rank and file.
 **/
int
chess_square(int rank, int file);

/**
 * Returns the square that is located on the left of the given square.
 * If the given square is on the left border this function returns -1.
 **/
int
chess_square_left(int square);

/**
 * Returns the square that is located on the right of the given square.
 * If the given square is on the right border this function returns -1.
 **/
int
chess_square_right(int square);

/**
 * Returns the square that is located above the given square.
 * If the given square is on top this function returns -1.
 **/
int
chess_square_up(int square);

/**
 * Returns the square that is below the given square.
 * If the given square is on bottom this function returns -1.
 **/
int
chess_square_down(int square);

/**
 * Returns true if the square is on the border.
 **/
bool
chess_square_border(int square);

/**
 * Given the square notation (a1, b2, etc.) returns the index of the square.
 **/
int
chess_square_index(const char *square);

/**
 * Returns the square notation of the given square index.
 * Returns NULL if the square index is invalid.
 **/
const char *
chess_square_name(int square);

/**
 * Returns the character representation of the piece.
 **/
char
chess_piece_char(int piece, int side);

/**
 * This opaque structure represents a chess board.
 **/
struct chess_board;

/**
 * Initializes and returns a chess board structure.
 * Returns NULL if memory allocation fails and sets errno accordingly.
 **/
struct chess_board *
chess_board_init(void);

/**
 * Returns the side to move.
 **/
int
chess_board_get_side(const struct chess_board *board);

/**
 * Sets the side to move.
 * \param side Side to move, either CHESS_WHITE or CHESS_BLACK.
 **/
void
chess_board_set_side(struct chess_board *board, int side);

/**
 * Returns the en passant square.
 **/
int
chess_board_get_enpassant_square(const struct chess_board *board);

/**
 * Sets the en passant square.
 **/
void
chess_board_set_enpassant_square(struct chess_board *board, int square);

/**
 * Returns the castling flags.
 **/
int
chess_board_get_castling_flags(const struct chess_board *board);

/**
 * Sets the castling flags.
 **/
void
chess_board_set_castling_flags(struct chess_board *board, int flags);

/**
 * Returns the initial square of white king.
 * Used to determine castling rights.
 **/
int
chess_board_get_initial_king_square(const struct chess_board *board);

/**
 * Sets the initial square of white king.
 * Used to determine castling rights.
 **/
void
chess_board_set_initial_king_square(struct chess_board *board, int square);

/**
 * Returns the initial square of white king rook.
 * Used to determine castling rights.
 **/
int
chess_board_get_initial_krook_square(const struct chess_board *board);

/**
 * Sets the initial square of white king rook.
 * Used to determine castling rights.
 **/
void
chess_board_set_initial_krook_square(struct chess_board *board, int square);

/**
 * Returns the initial square of white queen rook.
 * Used to determine castling rights.
 **/
int
chess_board_get_initial_qrook_square(const struct chess_board *board);

/**
 * Sets the initial square of white queen rook.
 * Used to determine castling rights.
 **/
void
chess_board_set_initial_qrook_square(struct chess_board *board, int square);

/**
 * Returns the reversible half move counter.
 * Used to determine if a draw can be claimed under the fifty-move rule.
 **/
unsigned
chess_board_get_rhmc(const struct chess_board *board);

/**
 * Sets the reversible half move counter.
 * Used to determine if a draw can be claimed under the fifty-move rule.
 **/
void
chess_board_set_rhmc(struct chess_board *board, unsigned count);

/**
 * Returns the full move counter.
 **/
unsigned
chess_board_get_fmc(const struct chess_board *board);

/**
 * Sets the full move counter.
 **/
void
chess_board_set_fmc(struct chess_board *board, unsigned count);

/**
 * Set piece to the given location on the board.
 **/
void
chess_board_set_piece(struct chess_board *board, int square, int piece, int side);

/**
 * Get piece on the given square of the board.
 * Returns true if a piece is found on the given square, false otherwise.
 * \param piece_r Pointer to save the piece information, may be NULL.
 * \param side_r Pointer to save the side information, may be NULL.
 **/
bool
chess_board_get_piece(const struct chess_board *board, int square, int *piece_r, int *side_r);

/**
 * Clear the given piece on the given square of the board.
 **/
void
chess_board_clear_piece(struct chess_board *board, int square, int piece, int side);

/**
 * Returns true if the given side has a piece on the given square.
 **/
bool
chess_board_has_piece(const struct chess_board *board, int square, int side);

/**
 * Returns the Forsyth–Edwards Notation of the current position.
 * Returns NULL if there wasn't enough room to hold the notation.
 * \param fen String to hold the FEN notation
 * \param len Length of the string
 **/
char *
chess_board_get_fen(struct chess_board *board, char *fen, size_t len);

#endif /* !LIBCHESS_GUARD_CHESS_H */
