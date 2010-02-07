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

#include <assert.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"
#include "magicmoves.h"

struct chess_board {
	int side;				/**< Side to move */
	int epsq;				/**< En passant square */
	int cflag;				/**< Castling flags */
	int isq[3];				/**< Initial squares of white king, king rook, and queen rook */
	unsigned rhmc;				/**< Reversible half move counter */
	unsigned fmc;				/**< Full move counter */
	int cboard[64];				/**< cboard[sq] gives the piece on square sq. */
	unsigned long long occupied[4];		/**< Occupied squares, (white, black, all, empty) */
	unsigned long long pieces[2][6];	/**< Pieces */
};

static const unsigned long long PAWN_ATTACKS[2][64] = {
	{0, 0, 0, 0, 0, 0, 0, 0,
	0x0000000000020000, 0x0000000000050000, 0x00000000000a0000, 0x0000000000140000,
	0x0000000000280000, 0x0000000000500000, 0x0000000000a00000, 0x0000000000400000,
	0x0000000002000000, 0x0000000005000000, 0x000000000a000000, 0x0000000014000000,
	0x0000000028000000, 0x0000000050000000, 0x00000000a0000000, 0x0000000040000000,
	0x0000000200000000, 0x0000000500000000, 0x0000000a00000000, 0x0000001400000000,
	0x0000002800000000, 0x0000005000000000, 0x000000a000000000, 0x0000004000000000,
	0x0000020000000000, 0x0000050000000000, 0x00000a0000000000, 0x0000140000000000,
	0x0000280000000000, 0x0000500000000000, 0x0000a00000000000, 0x0000400000000000,
	0x0002000000000000, 0x0005000000000000, 0x000a000000000000, 0x0014000000000000,
	0x0028000000000000, 0x0050000000000000, 0x00a0000000000000, 0x0040000000000000,
	0x0200000000000000, 0x0500000000000000, 0x0a00000000000000, 0x1400000000000000,
	0x2800000000000000, 0x5000000000000000, 0xa000000000000000, 0x4000000000000000,
	0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0,
	0x0000000000000002, 0x0000000000000005, 0x000000000000000a, 0x0000000000000014,
	0x0000000000000028, 0x0000000000000050, 0x00000000000000a0, 0x0000000000000040,
	0x0000000000000200, 0x0000000000000500, 0x0000000000000a00, 0x0000000000001400,
	0x0000000000002800, 0x0000000000005000, 0x000000000000a000, 0x0000000000004000,
	0x0000000000020000, 0x0000000000050000, 0x00000000000a0000, 0x0000000000140000,
	0x0000000000280000, 0x0000000000500000, 0x0000000000a00000, 0x0000000000400000,
	0x0000000002000000, 0x0000000005000000, 0x000000000a000000, 0x0000000014000000,
	0x0000000028000000, 0x0000000050000000, 0x00000000a0000000, 0x0000000040000000,
	0x0000000200000000, 0x0000000500000000, 0x0000000a00000000, 0x0000001400000000,
	0x0000002800000000, 0x0000005000000000, 0x000000a000000000, 0x0000004000000000,
	0x0000020000000000, 0x0000050000000000, 0x00000a0000000000, 0x0000140000000000,
	0x0000280000000000, 0x0000500000000000, 0x0000a00000000000, 0x0000400000000000,
	0, 0, 0, 0, 0, 0, 0, 0}
};
static const unsigned long long KNIGHT_ATTACKS[64] = {
	0x0000000000020400, 0x0000000000050800, 0x00000000000a1100, 0x0000000000142200,
	0x0000000000284400, 0x0000000000508800, 0x0000000000a01000, 0x0000000000402000,
	0x0000000002040004, 0x8000000005080008, 0x000000000a110011, 0x0000000014220022,
	0x0000000028440044, 0x0000000050880088, 0x00000000a0100010, 0x0000000040200020,
	0x0000000204000402, 0x0000000508000885, 0x0000000a1100110a, 0x0000001422002214,
	0x0000002844004428, 0x0000005088008850, 0x000000a0100010a0, 0x0000004020002040,
	0x0000020400040200, 0x0000050800088500, 0x00000a1100110a00, 0x0000142200221400,
	0x0000284400442800, 0x0000508800885000, 0x0000a0100010a000, 0x0000402000204000,
	0x0002040004020000, 0x0005080008850000, 0x000a1100110a0000, 0x0014220022140000,
	0x0028440044280000, 0x0050880088500000, 0x00a0100010a00000, 0x0040200020400000,
	0x0204000402000000, 0x0508000885000000, 0x0a1100110a000000, 0x1422002214000000,
	0x2844004428000000, 0x5088008850000000, 0xa0100010a0000000, 0x4020002040000000,
	0x0400040200000000, 0x0800088500000000, 0x1100110a00000000, 0x2200221400000000,
	0x4400442800000000, 0x8800885000000000, 0x100010a000000000, 0x2000204000000000,
	0x0004020000000000, 0x0008850000000000, 0x00110a0000000000, 0x0022140000000000,
	0x0044280000000000, 0x0088500000000000, 0x0010a00000000000, 0x0020400000000000
};
static const unsigned long long KING_ATTACKS[64] = {
	0x0000000000000302, 0x0000000000000705, 0x0000000000000e0a, 0x0000000000001c14,
	0x0000000000003828, 0x0000000000007050, 0x000000000000e0a0, 0x000000000000c040,
	0x0000000000030203, 0x0000000000070507, 0x00000000000e0a0e, 0x00000000001c141c,
	0x0000000000382838, 0x0000000000705070, 0x0000000000e0a0e0, 0x0000000000c040c0,
	0x0000000003020300, 0x0000000007050700, 0x000000000e0a0e00, 0x000000001c141c00,
	0x0000000038283800, 0x0000000070507000, 0x00000000e0a0e000, 0x00000000c040c000,
	0x0000000302030000, 0x0000000705070000, 0x0000000e0a0e0000, 0x0000001c141c0000,
	0x0000003828380000, 0x0000007050700000, 0x000000e0a0e00000, 0x000000c040c00000,
	0x0000030203000000, 0x0000070507000000, 0x00000e0a0e000000, 0x00001c141c000000,
	0x0000382838000000, 0x0000705070000000, 0x0000e0a0e0000000, 0x0000c040c0000000,
	0x0003020300000000, 0x0007050700000000, 0x000e0a0e00000000, 0x001c141c00000000,
	0x0038283800000000, 0x0070507000000000, 0x00e0a0e000000000, 0x00c040c000000000,
	0x0302030000000000, 0x0705070000000000, 0x0e0a0e0000000000, 0x1c141c0000000000,
	0x3828380000000000, 0x7050700000000000, 0xe0a0e00000000000, 0xc040c00000000000,
	0x0203000000000000, 0x0507000000000000, 0x0a0e000000000000, 0x141c000000000000,
	0x2838000000000000, 0x5070000000000000, 0xa0e0000000000000, 0x40c0000000000000
};

inline int
chess_switch_side(int side)
{
	assert(side >= CHESS_SIDE_WHITE && side <= CHESS_SIDE_BLACK);

	return 1 ^ side;
}

inline int
chess_rank(int square)
{
	assert(square >= 0 && square <= 63);

	return square >> 3;
}

inline int
chess_file(int square)
{
	assert(square >= 0 && square <= 63);

	return square & 7;
}

inline char
chess_file_char(int square)
{
	assert(square >= 0 && square <= 63);

	return (char) chess_file(square) + 97;
}

inline int
chess_square(int rank, int file)
{
	assert(rank >= 0 && rank <= 7);
	assert(file >= 0 && file <= 7);

	return (rank << 3) + file;
}

inline int
chess_square_left(int square)
{
	assert(square >= 0 && square <= 63);

	if (square % 8 != 0)
		return square - 1;
	return -1;
}

inline int
chess_square_right(int square)
{
	assert(square >= 0 && square <= 63);

	if (square % 8 != 7)
		return square + 1;
	return -1;
}

inline int
chess_square_up(int square)
{
	assert(square >= 0 && square <= 63);

	if (square < 55)
		return square + 8;
	return -1;
}

inline int
chess_square_down(int square)
{
	assert(square >= 0 && square <= 63);

	if (square > 7)
		return square - 8;
	return -1;
}

inline bool
chess_square_border(int square)
{
	int file, rank;

	assert(square >= 0 && square <= 63);

	file = chess_file(square);
	rank = chess_rank(square);

	return ((file == 0) || (file == 7) || (rank == 0) || (rank == 7));
}

int
chess_square_index(const char *square)
{
	int rank, file;

	file = square[0] - 97;
	rank = atoi(++square) - 1;

	return chess_square(rank, file);
}

const char *
chess_square_name(int square)
{
	assert(square >= 0 && square <= 63);

	switch (square) {
	case 0: return "a1";
	case 1: return "b1";
	case 2: return "c1";
	case 3: return "d1";
	case 4: return "e1";
	case 5: return "f1";
	case 6: return "g1";
	case 7: return "h1";

	case 8:  return "a2";
	case 9:  return "b2";
	case 10: return "c2";
	case 11: return "d2";
	case 12: return "e2";
	case 13: return "f2";
	case 14: return "g2";
	case 15: return "h2";

	case 16: return "a3";
	case 17: return "b3";
	case 18: return "c3";
	case 19: return "d3";
	case 20: return "e3";
	case 21: return "f3";
	case 22: return "g3";
	case 23: return "h3";

	case 24: return "a4";
	case 25: return "b4";
	case 26: return "c4";
	case 27: return "d4";
	case 28: return "e4";
	case 29: return "f4";
	case 30: return "g4";
	case 31: return "h4";

	case 32: return "a5";
	case 33: return "b5";
	case 34: return "c5";
	case 35: return "d5";
	case 36: return "e5";
	case 37: return "f5";
	case 38: return "g5";
	case 39: return "h5";

	case 40: return "a6";
	case 41: return "b6";
	case 42: return "c6";
	case 43: return "d6";
	case 44: return "e6";
	case 45: return "f6";
	case 46: return "g6";
	case 47: return "h6";

	case 48: return "a7";
	case 49: return "b7";
	case 50: return "c7";
	case 51: return "d7";
	case 52: return "e7";
	case 53: return "f7";
	case 54: return "g7";
	case 55: return "h7";

	case 56: return "a8";
	case 57: return "b8";
	case 58: return "c8";
	case 59: return "d8";
	case 60: return "e8";
	case 61: return "f8";
	case 62: return "g8";
	case 63: return "h8";

	default: return NULL;
	}
}

char
chess_piece_char(int piece, int side)
{
	bool iswhite;
	char cpiece;

	assert(piece >= CHESS_PIECE_PAWN && piece <= CHESS_PIECE_KING);
	assert(side == CHESS_SIDE_WHITE || side == CHESS_SIDE_BLACK);

	iswhite = (side == CHESS_SIDE_WHITE);
	cpiece = 0;

	switch (piece) {
	case CHESS_PIECE_PAWN:
		cpiece = iswhite ? 'P' : 'p';
		break;
	case CHESS_PIECE_KNIGHT:
		cpiece = iswhite ? 'N' : 'n';
		break;
	case CHESS_PIECE_BISHOP:
		cpiece = iswhite ? 'B' : 'b';
		break;
	case CHESS_PIECE_ROOK:
		cpiece = iswhite ? 'R' : 'r';
		break;
	case CHESS_PIECE_QUEEN:
		cpiece = iswhite ? 'Q' : 'q';
		break;
	case CHESS_PIECE_KING:
		cpiece = iswhite ? 'K' : 'k';
		break;
	default:
		break;
	}

	return cpiece;
}

struct chess_board *
chess_board_init(void)
{
	struct chess_board *board;

	board = calloc(1, sizeof(struct chess_board));
	if (board == NULL)
		return NULL;

	board->side = CHESS_SIDE_WHITE;
	board->epsq = -1;
	board->cflag = 0;
	board->isq[0] = chess_square_index("e1");
	board->isq[1] = chess_square_index("h1");
	board->isq[2] = chess_square_index("a1");
	board->rhmc = 0;
	board->fmc = 1;

	return board;
}

int
chess_board_get_side(const struct chess_board *board)
{
	return board->side;
}

void
chess_board_set_side(struct chess_board *board, int side)
{
	assert(side == CHESS_SIDE_WHITE || side == CHESS_SIDE_BLACK);

	board->side = side;
}

int
chess_board_get_enpassant_square(const struct chess_board *board)
{
	return board->epsq;
}

void
chess_board_set_enpassant_square(struct chess_board *board, int square)
{
	assert(square >= 0 && square <= 63);

	board->epsq = square;
}

int
chess_board_get_castling_flags(const struct chess_board *board)
{
	return board->cflag;
}

void
chess_board_set_castling_flags(struct chess_board *board, int flags)
{
	board->cflag = flags;
}

int
chess_board_get_initial_king_square(const struct chess_board *board)
{
	return board->isq[0];
}

void
chess_board_set_initial_king_square(struct chess_board *board, int square)
{
	assert(square >= 0 && square <= 63);

	board->isq[0] = square;
}

int
chess_board_get_initial_krook_square(const struct chess_board *board)
{
	return board->isq[1];
}

void
chess_board_set_initial_krook_square(struct chess_board *board, int square)
{
	assert(square >= 0 && square <= 63);

	board->isq[1] = square;
}

int
chess_board_get_initial_qrook_square(const struct chess_board *board)
{
	return board->isq[2];
}

void
chess_board_set_initial_qrook_square(struct chess_board *board, int square)
{
	assert(square >= 0 && square <= 63);

	board->isq[2] = square;
}

unsigned
chess_board_get_rhmc(const struct chess_board *board)
{
	return board->rhmc;
}

void
chess_board_set_rhmc(struct chess_board *board, unsigned count)
{
	board->rhmc = count;
}

unsigned
chess_board_get_fmc(const struct chess_board *board)
{
	return board->fmc;
}

void
chess_board_set_fmc(struct chess_board *board, unsigned count)
{
	board->fmc = count;
}

void
chess_board_set_piece(struct chess_board *board, int square, int piece, int side)
{
	unsigned long long sqbit;

	assert(square >= 0 && square <= 63);
	assert(piece >= CHESS_PIECE_PAWN && piece <= CHESS_PIECE_KING);

	sqbit = (1ULL << square);
	board->pieces[side][piece] |= sqbit;
	board->occupied[side] |= sqbit;
	board->occupied[2] |= sqbit;
	board->occupied[3] &= ~sqbit;
	board->cboard[square] = piece;
}

bool
chess_board_get_piece(const struct chess_board *board, int square, int *piece_r, int *side_r)
{
	int piece;

	assert(square >= 0 && square <= 63);

	piece = board->cboard[square];
	if (!piece) {
		if (piece_r != NULL)
			*piece_r = 0;
		if (side_r != NULL)
			*side_r = 0;
		return false;
	}

	if (piece_r != NULL)
		*piece_r = piece;

	if (side_r != NULL) {
		if ((board->pieces[CHESS_SIDE_WHITE][piece] & (1ULL << square)) != 0)
			*side_r = CHESS_SIDE_WHITE;
		else
			*side_r = CHESS_SIDE_BLACK;
	}

	return true;
}

void
chess_board_clear_piece(struct chess_board *board, int square, int piece, int side)
{
	unsigned long long sqbit;

	assert(square >= 0 && square <= 63);
	assert(piece >= CHESS_PIECE_PAWN && piece <= CHESS_PIECE_KING);
	assert(side == CHESS_SIDE_WHITE || side == CHESS_SIDE_BLACK);

	sqbit = (1ULL << square);
	board->pieces[side][piece] &= ~sqbit;
	board->occupied[side] &= ~sqbit;
	board->occupied[2] &= ~sqbit;
	board->occupied[3] |= sqbit;
	board->cboard[square] = 0;
}

bool
chess_board_has_piece(const struct chess_board *board, int square, int side)
{
	assert(square >= 0 && square <= 63);
	assert(side == CHESS_SIDE_WHITE || side == CHESS_SIDE_BLACK);

	return ((board->occupied[side] & (1ULL << square)) != 0);
}

char *
chess_board_get_fen(struct chess_board *board, char *fen, size_t len)
{
	int empty, square, piece, side, ret;
	size_t ind;
	const char *epsq;

	ind = 0;

#define PUSHCHAR(ch)				\
	do {					\
		fen[ind++] = (char)(ch);	\
		if (ind >= len)			\
			return NULL;		\
	} while (0)

	/* Step 1: Fill in the board position */
	for (int rank = 7; rank >= 0; rank--) {
		empty = 0;

		for (int file = 0; file < 8; file++) {
			square = chess_square(rank, file);
			if (!chess_board_get_piece(board, square, &piece, &side))
				++empty;
			else {
				if (empty > 0) {
					assert(empty <= 8);
					PUSHCHAR(empty + 48);
					empty = 0;
				}
				PUSHCHAR(chess_piece_char(piece, side));
			}
		}

		if (empty > 0) {
			assert(empty <= 8);
			PUSHCHAR(empty + 48);
		}

		if (rank > 0)
			PUSHCHAR('/');
	}

	/* Field separator */
	PUSHCHAR(' ');

	/* Step 2: Fill in the side to move */
	PUSHCHAR((board->side == CHESS_SIDE_WHITE) ? 'w' : 'b');

	/* Field separator */
	PUSHCHAR(' ');

	/* Step 3: Fill in the castling rights */
	if (!(board->cflag & (CHESS_CASTLE_WHITE | CHESS_CASTLE_BLACK))) {
		/* No castling rights, add '-' */
		PUSHCHAR('-');
	}
	else {
		if (board->cflag & (CHESS_CASTLE_KINGSIDE_WHITE)) {
			/* White can castle king side */
			PUSHCHAR('K');
		}
		if (board->cflag & (CHESS_CASTLE_QUEENSIDE_WHITE)) {
			/* White can castle king side */
			PUSHCHAR('Q');
		}
		if (board->cflag & (CHESS_CASTLE_KINGSIDE_BLACK)) {
			/* Black can castle king side */
			PUSHCHAR('k');
		}
		if (board->cflag & (CHESS_CASTLE_QUEENSIDE_BLACK)) {
			/* Black can castle king side */
			PUSHCHAR('q');
		}
	}

	/* Field separator */
	PUSHCHAR(' ');

	/* Step 4: Fill in the en passant square */
	if (board->epsq < 0) {
		/* No en passant square, add '-' */
		PUSHCHAR('-');
	}
	else {
		epsq = chess_square_name(board->epsq);
		assert(epsq != NULL);
		PUSHCHAR(epsq[0]);
		PUSHCHAR(epsq[1]);
	}

	PUSHCHAR('\0');
#undef PUSHCHAR

	ret = snprintf(fen + strlen(fen), len - strlen(fen), " %d %d", board->rhmc, board->fmc);
	if (ret < 0 || (unsigned)ret > (len - strlen(fen)))
		return NULL;
	return fen;
}
