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

#include <stdlib.h>

#include <check.h>

#include "chess.h"

START_TEST(test_chess_switch_side)
{
    int side;

    side = CHESS_WHITE;
    side = chess_switch_side(side);
    fail_unless(CHESS_BLACK == side, "switch_side() failed to change white to black");

    side = CHESS_BLACK;
    side = chess_switch_side(side);
    fail_unless(CHESS_WHITE == side, "switch_side() failed to change black to white");
}
END_TEST

START_TEST(test_chess_rank)
{
    int sq;

    for (sq = 0; sq < 8; sq++)
        fail_unless(0 == chess_rank(sq), "chess_rank() failed for square: %d", sq);
    for (sq = 8; sq < 16; sq++)
        fail_unless(1 == chess_rank(sq), "chess_rank() failed for square: %d", sq);
    for (sq = 16; sq < 24; sq++)
        fail_unless(2 == chess_rank(sq), "chess_rank() failed for square: %d", sq);
    for (sq = 24; sq < 32; sq++)
        fail_unless(3 == chess_rank(sq), "chess_rank() failed for square: %d", sq);
    for (sq = 32; sq < 40; sq++)
        fail_unless(4 == chess_rank(sq), "chess_rank() failed for square: %d", sq);
    for (sq = 40; sq < 48; sq++)
        fail_unless(5 == chess_rank(sq), "chess_rank() failed for square: %d", sq);
    for (sq = 48; sq < 56; sq++)
        fail_unless(6 == chess_rank(sq), "chess_rank() failed for square: %d", sq);
    for (sq = 56; sq < 64; sq++)
        fail_unless(7 == chess_rank(sq), "chess_rank() failed for square: %d", sq);
}
END_TEST

START_TEST(test_chess_file)
{
    int sq;

    for (sq = 0; sq < 57; sq += 8)
        fail_unless(0 == chess_file(sq), "chess_file() failed for square: %d", sq);
    for (sq = 1; sq < 58; sq += 8)
        fail_unless(1 == chess_file(sq), "chess_file() failed for square: %d", sq);
    for (sq = 2; sq < 59; sq += 8)
        fail_unless(2 == chess_file(sq), "chess_file() failed for square: %d", sq);
    for (sq = 3; sq < 60; sq += 8)
        fail_unless(3 == chess_file(sq), "chess_file() failed for square: %d", sq);
    for (sq = 4; sq < 61; sq += 8)
        fail_unless(4 == chess_file(sq), "chess_file() failed for square: %d", sq);
    for (sq = 5; sq < 62; sq += 8)
        fail_unless(5 == chess_file(sq), "chess_file() failed for square: %d", sq);
    for (sq = 6; sq < 63; sq += 8)
        fail_unless(6 == chess_file(sq), "chess_file() failed for square: %d", sq);
    for (sq = 7; sq < 64; sq += 8)
        fail_unless(7 == chess_file(sq), "chess_file() failed for square: %d", sq);
}
END_TEST

START_TEST(test_chess_square)
{
    int sq = 0;
    int rank, file;

    for (rank = 0; rank < 8; rank++) {
        for (file = 0; file < 8; file++) {
            fail_unless(sq == chess_square(rank, file), "chess_square() failed for square: %d (got: %d)",
                    sq, chess_square(rank, file));
            ++sq;
        }
    }
}
END_TEST

START_TEST(test_chess_square_left)
{
    int sq;

    for (sq = 0; sq < 64; sq++) {
        if (0 == sq % 8)
            fail_unless(-1 == chess_square_left(sq), "chess_square_left() failed for square: %d", sq);
        else
            fail_unless(sq - 1 == chess_square_left(sq), "chess_square_left() failed for square: %d", sq);
    }
}
END_TEST

START_TEST(test_chess_square_right)
{
    int sq;

    for (sq = 0; sq < 64; sq++) {
        if (7 == sq % 8)
            fail_unless(-1 == chess_square_right(sq), "chess_square_right() failed for square: %d", sq);
        else
            fail_unless(sq + 1 == chess_square_right(sq), "chess_square_right() failed for square: %d", sq);
    }
}
END_TEST

START_TEST(test_chess_square_up)
{
    int sq;

    for (sq = 0; sq < 64; sq++) {
        if (54 < sq)
            fail_unless(-1 == chess_square_up(sq), "chess_square_up() failed for square: %d", sq);
        else
            fail_unless(sq + 8 == chess_square_up(sq), "chess_square_up() failed for square: %d", sq);
    }
}
END_TEST

START_TEST(test_chess_square_down)
{
    int sq;

    for (sq = 0; sq < 64; sq++) {
        if (8 > sq)
            fail_unless(-1 == chess_square_down(sq), "chess_square_down() failed for square: %d", sq);
        else
            fail_unless(sq - 8 == chess_square_down(sq), "chess_square_down() failed for square: %d", sq);
    }
}
END_TEST

START_TEST(test_chess_square_border)
{
    int sq;
    int rank, file;

    for (sq = 0; sq < 64; sq++) {
        rank = chess_rank(sq);
        file = chess_file(sq);
        if (file == 0 || file == 7 || rank == 0 || rank == 7)
            fail_unless(chess_square_border(sq), "chess_square_border() failed for square: %d", sq);
        else
            fail_if(chess_square_border(sq), "chess_square_border() failed for square: %d", sq);
    }
}
END_TEST

START_TEST(test_chess_filec)
{
    int sq;

    for (sq = 0; sq < 57; sq += 8)
        fail_unless('a' == chess_filec(sq), "chess_filec() failed for square: %d", sq);
    for (sq = 1; sq < 58; sq += 8)
        fail_unless('b' == chess_filec(sq), "chess_filec() failed for square: %d", sq);
    for (sq = 2; sq < 59; sq += 8)
        fail_unless('c' == chess_filec(sq), "chess_filec() failed for square: %d", sq);
    for (sq = 3; sq < 60; sq += 8)
        fail_unless('d' == chess_filec(sq), "chess_filec() failed for square: %d", sq);
    for (sq = 4; sq < 61; sq += 8)
        fail_unless('e' == chess_filec(sq), "chess_filec() failed for square: %d", sq);
    for (sq = 5; sq < 62; sq += 8)
        fail_unless('f' == chess_filec(sq), "chess_filec() failed for square: %d", sq);
    for (sq = 6; sq < 63; sq += 8)
        fail_unless('g' == chess_filec(sq), "chess_filec() failed for square: %d", sq);
    for (sq = 7; sq < 64; sq += 8)
        fail_unless('h' == chess_filec(sq), "chess_filec() failed for square: %d", sq);
}
END_TEST

START_TEST(test_chess_squarei)
{
    fail_unless(0 == chess_squarei("a1"), "chess_squarei() failed for a1 (got: %d)", chess_squarei("a1"));
    fail_unless(1 == chess_squarei("b1"), "chess_squarei() failed for b1");
    fail_unless(2 == chess_squarei("c1"), "chess_squarei() failed for c1");
    fail_unless(3 == chess_squarei("d1"), "chess_squarei() failed for d1");
    fail_unless(4 == chess_squarei("e1"), "chess_squarei() failed for e1");
    fail_unless(5 == chess_squarei("f1"), "chess_squarei() failed for f1");
    fail_unless(6 == chess_squarei("g1"), "chess_squarei() failed for g1");
    fail_unless(7 == chess_squarei("h1"), "chess_squarei() failed for h1");
    fail_unless(8 == chess_squarei("a2"), "chess_squarei() failed for a2");
    fail_unless(9 == chess_squarei("b2"), "chess_squarei() failed for b2");
    fail_unless(10 == chess_squarei("c2"), "chess_squarei() failed for c2");
    fail_unless(11 == chess_squarei("d2"), "chess_squarei() failed for d2");
    fail_unless(12 == chess_squarei("e2"), "chess_squarei() failed for e2");
    fail_unless(13 == chess_squarei("f2"), "chess_squarei() failed for f2");
    fail_unless(14 == chess_squarei("g2"), "chess_squarei() failed for g2");
    fail_unless(15 == chess_squarei("h2"), "chess_squarei() failed for h2");
    fail_unless(16 == chess_squarei("a3"), "chess_squarei() failed for a3");
    fail_unless(17 == chess_squarei("b3"), "chess_squarei() failed for b3");
    fail_unless(18 == chess_squarei("c3"), "chess_squarei() failed for c3");
    fail_unless(19 == chess_squarei("d3"), "chess_squarei() failed for d3");
    fail_unless(20 == chess_squarei("e3"), "chess_squarei() failed for e3");
    fail_unless(21 == chess_squarei("f3"), "chess_squarei() failed for f3");
    fail_unless(22 == chess_squarei("g3"), "chess_squarei() failed for g3");
    fail_unless(23 == chess_squarei("h3"), "chess_squarei() failed for h3");
    fail_unless(24 == chess_squarei("a4"), "chess_squarei() failed for a4");
    fail_unless(25 == chess_squarei("b4"), "chess_squarei() failed for b4");
    fail_unless(26 == chess_squarei("c4"), "chess_squarei() failed for c4");
    fail_unless(27 == chess_squarei("d4"), "chess_squarei() failed for d4");
    fail_unless(28 == chess_squarei("e4"), "chess_squarei() failed for e4");
    fail_unless(29 == chess_squarei("f4"), "chess_squarei() failed for f4");
    fail_unless(30 == chess_squarei("g4"), "chess_squarei() failed for g4");
    fail_unless(31 == chess_squarei("h4"), "chess_squarei() failed for h4");
    fail_unless(32 == chess_squarei("a5"), "chess_squarei() failed for a5");
    fail_unless(33 == chess_squarei("b5"), "chess_squarei() failed for b5");
    fail_unless(34 == chess_squarei("c5"), "chess_squarei() failed for c5");
    fail_unless(35 == chess_squarei("d5"), "chess_squarei() failed for d5");
    fail_unless(36 == chess_squarei("e5"), "chess_squarei() failed for e5");
    fail_unless(37 == chess_squarei("f5"), "chess_squarei() failed for f5");
    fail_unless(38 == chess_squarei("g5"), "chess_squarei() failed for g5");
    fail_unless(39 == chess_squarei("h5"), "chess_squarei() failed for h5");
    fail_unless(40 == chess_squarei("a6"), "chess_squarei() failed for a6");
    fail_unless(41 == chess_squarei("b6"), "chess_squarei() failed for b6");
    fail_unless(42 == chess_squarei("c6"), "chess_squarei() failed for c6");
    fail_unless(43 == chess_squarei("d6"), "chess_squarei() failed for d6");
    fail_unless(44 == chess_squarei("e6"), "chess_squarei() failed for e6");
    fail_unless(45 == chess_squarei("f6"), "chess_squarei() failed for f6");
    fail_unless(46 == chess_squarei("g6"), "chess_squarei() failed for g6");
    fail_unless(47 == chess_squarei("h6"), "chess_squarei() failed for h6");
    fail_unless(48 == chess_squarei("a7"), "chess_squarei() failed for a7");
    fail_unless(49 == chess_squarei("b7"), "chess_squarei() failed for b7");
    fail_unless(50 == chess_squarei("c7"), "chess_squarei() failed for c7");
    fail_unless(51 == chess_squarei("d7"), "chess_squarei() failed for d7");
    fail_unless(52 == chess_squarei("e7"), "chess_squarei() failed for e7");
    fail_unless(53 == chess_squarei("f7"), "chess_squarei() failed for f7");
    fail_unless(54 == chess_squarei("g7"), "chess_squarei() failed for g7");
    fail_unless(55 == chess_squarei("h7"), "chess_squarei() failed for h7");
    fail_unless(56 == chess_squarei("a8"), "chess_squarei() failed for a8");
    fail_unless(57 == chess_squarei("b8"), "chess_squarei() failed for b8");
    fail_unless(58 == chess_squarei("c8"), "chess_squarei() failed for c8");
    fail_unless(59 == chess_squarei("d8"), "chess_squarei() failed for d8");
    fail_unless(60 == chess_squarei("e8"), "chess_squarei() failed for e8");
    fail_unless(61 == chess_squarei("f8"), "chess_squarei() failed for f8");
    fail_unless(62 == chess_squarei("g8"), "chess_squarei() failed for g8");
    fail_unless(63 == chess_squarei("h8"), "chess_squarei() failed for h8");
}
END_TEST

static Suite *chess_suite(void)
{
    Suite *s = suite_create("Chess");

    TCase *tc_chess = tcase_create("chess");

    tcase_add_test(tc_chess, test_chess_switch_side);
    tcase_add_test(tc_chess, test_chess_rank);
    tcase_add_test(tc_chess, test_chess_file);
    tcase_add_test(tc_chess, test_chess_square);
    tcase_add_test(tc_chess, test_chess_square_left);
    tcase_add_test(tc_chess, test_chess_square_right);
    tcase_add_test(tc_chess, test_chess_square_up);
    tcase_add_test(tc_chess, test_chess_square_down);
    tcase_add_test(tc_chess, test_chess_square_border);
    tcase_add_test(tc_chess, test_chess_filec);
    tcase_add_test(tc_chess, test_chess_squarei);

    suite_add_tcase(s, tc_chess);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = chess_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
