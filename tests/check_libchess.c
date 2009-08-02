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

Suite *chess_suite(void)
{
    Suite *s = suite_create("Chess");

    TCase *tc_chess = tcase_create("chess");
    tcase_add_test(tc_chess, test_chess_switch_side);
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
