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

Suite *chess_suite(void)
{
    Suite *s = suite_create("Chess");

    TCase *tc_chess = tcase_create("chess");

    tcase_add_test(tc_chess, test_chess_switch_side);
    tcase_add_test(tc_chess, test_chess_rank);
    tcase_add_test(tc_chess, test_chess_file);
    tcase_add_test(tc_chess, test_chess_filec);

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
