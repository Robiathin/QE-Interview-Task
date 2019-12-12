
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "extract.h"
#include "extract_csv.h"
#include "extract_json.h"
#include "population_data.h"

START_TEST (test_json_parse)
{
	char *data = "[{ \"first_name\": \"LEONEL\", \"last_name\": \"FERREL\", \"siblings\": \"1\", \
\"favourite_food\": \"Meatballs\", \"birth_timezone\": \"-01:00\", \"birth_timestamp\": \"917172960000\" }]";
	population_data_t *pd;

	pd = population_data_from_json(data);
	ck_assert_str_eq(pd[0].first_name, "LEONEL");
	ck_assert_str_eq(pd[0].last_name, "FERREL");
	ck_assert_uint_eq(pd[0].siblings, 1);
	ck_assert_str_eq(pd[0].favourite_food, "Meatballs");
	ck_assert_str_eq(pd[0].birth_timezone, "-01:00");
	ck_assert_uint_eq(pd[0].birth_timestamp, 917172960000);

	ck_assert(pd[1].first_name == NULL);
	free(pd);
}
END_TEST

START_TEST (test_csv_parse)
{
	char *data = "first_name,last_name,siblings,favourite_food,birth_timezone,birth_timestamp\nDELIA,MCCRAE,5,chicken,-08:00,601605300000\n";
	population_data_t *pd;

	pd = population_data_from_csv(data);
	ck_assert_str_eq(pd[0].first_name, "DELIA");
	ck_assert_str_eq(pd[0].last_name, "MCCRAE");
	ck_assert_uint_eq(pd[0].siblings, 5);
	ck_assert_str_eq(pd[0].favourite_food, "chicken");
	ck_assert_str_eq(pd[0].birth_timezone, "-08:00");
	ck_assert_uint_eq(pd[0].birth_timestamp, 601605300000);

	ck_assert(pd[1].first_name == NULL);
	free(pd);
}
END_TEST

START_TEST (test_average_sibling)
{
	population_data_t testd[] = {
		{ "test1_first", "test1_last", 1, "Apples", "-05:00", 42000 },
		{ "test2_first", "test2_last", 2, "Apples", "-05:00", 42000 },
		{ "test3_first", "test3_last", 3, "Apples", "-05:00", 42000 },
		{ "test4_first", "test4_last", 4, "Apples", "-05:00", 42000 },
		{ "test5_first", "test5_last", 5, "Apples", "-05:00", 42000 },
		{ "test6_first", "test6_last", 1, "Apples", "-05:00", 42000 },
		{ "test7_first", "test7_last", 2, "Apples", "-05:00", 42000 },
		{ "test8_first", "test8_last", 3, "Apples", "-05:00", 42000 },
		{ "test9_first", "test9_last", 4, "Apples", "-05:00", 42000 },
		{ "test10_first", "test10_last", 5, "Apples", "-05:00", 42000 },
		{ NULL, NULL, 0, NULL, NULL, 0 },
	};	
	ck_assert_uint_eq(extract_average_siblings((population_data_t *)&testd), 3);
}
END_TEST

START_TEST (test_average_sibling_all2)
{
	population_data_t testd[] = {
		{ "test1_first", "test1_last", 2, "Apples", "-05:00", 42000 },
		{ "test2_first", "test2_last", 2, "Apples", "-05:00", 42000 },
		{ "test3_first", "test3_last", 2, "Apples", "-05:00", 42000 },
		{ "test4_first", "test4_last", 2, "Apples", "-05:00", 42000 },
		{ "test5_first", "test5_last", 2, "Apples", "-05:00", 42000 },
		{ "test6_first", "test6_last", 2, "Apples", "-05:00", 42000 },
		{ "test7_first", "test7_last", 2, "Apples", "-05:00", 42000 },
		{ "test8_first", "test8_last", 2, "Apples", "-05:00", 42000 },
		{ "test9_first", "test9_last", 2, "Apples", "-05:00", 42000 },
		{ "test10_first", "test10_last", 2, "Apples", "-05:00", 42000 },
		{ NULL, NULL, 0, NULL, NULL, 0 },
	};	
	ck_assert_uint_eq(extract_average_siblings((population_data_t *)&testd), 2);
}
END_TEST

START_TEST (test_average_sibling_rounds_up)
{
	population_data_t testd[] = {
		{ "test1_first", "test1_last", 2, "Apples", "-05:00", 42000 },
		{ "test2_first", "test2_last", 2, "Apples", "-05:00", 42000 },
		{ "test3_first", "test3_last", 2, "Apples", "-05:00", 42000 },
		{ "test4_first", "test4_last", 2, "Apples", "-05:00", 42000 },
		{ "test5_first", "test5_last", 2, "Apples", "-05:00", 42000 },
		{ "test6_first", "test6_last", 2, "Apples", "-05:00", 42000 },
		{ "test7_first", "test7_last", 2, "Apples", "-05:00", 42000 },
		{ "test8_first", "test8_last", 2, "Apples", "-05:00", 42000 },
		{ "test9_first", "test9_last", 2, "Apples", "-05:00", 42000 },
		{ "test10_first", "test10_last", 3, "Apples", "-05:00", 42000 },
		{ NULL, NULL, 0, NULL, NULL, 0 },
	};
	ck_assert_uint_eq(extract_average_siblings((population_data_t *)&testd), 3);
}
END_TEST

START_TEST (test_birthday_data_all_jan)
{
	population_data_t testd[] = {
		{ "test1_first", "test1_last", 2, "Apples", "-00:00", 42000 },
		{ "test2_first", "test2_last", 2, "Apples", "-00:00", 42000 },
		{ "test3_first", "test3_last", 2, "Apples", "-00:00", 42000 },
		{ "test4_first", "test4_last", 2, "Apples", "-00:00", 42000 },
		{ "test5_first", "test5_last", 2, "Apples", "-00:00", 42000 },
		{ "test6_first", "test6_last", 2, "Apples", "-00:00", 42000 },
		{ "test7_first", "test7_last", 2, "Apples", "-00:00", 42000 },
		{ "test8_first", "test8_last", 2, "Apples", "-00:00", 42000 },
		{ "test9_first", "test9_last", 2, "Apples", "-00:00", 42000 },
		{ "test10_first", "test10_last", 3, "Apples", "-00:00", 42000 },
		{ NULL, NULL, 0, NULL, NULL, 0 },
	};
	birthday_data_t *bdd;

	bdd = extract_birthday_month_count((population_data_t *)&testd);
	ck_assert_uint_eq(bdd[0].count, 10);
	ck_assert_uint_eq(bdd[1].count, 0);
	ck_assert_uint_eq(bdd[2].count, 0);
	ck_assert_uint_eq(bdd[3].count, 0);
	ck_assert_uint_eq(bdd[4].count, 0);
	ck_assert_uint_eq(bdd[5].count, 0);
	ck_assert_uint_eq(bdd[6].count, 0);
	ck_assert_uint_eq(bdd[7].count, 0);
	ck_assert_uint_eq(bdd[8].count, 0);
	ck_assert_uint_eq(bdd[9].count, 0);
	ck_assert_uint_eq(bdd[10].count, 0);
	ck_assert_uint_eq(bdd[11].count, 0);
}
END_TEST

START_TEST (test_birthday_data_one_each)
{
	population_data_t testd[] = {
		{ "test1_first", "test1_last", 2, "Apples", "-00:00", 42000 },
		{ "test2_first", "test2_last", 2, "Apples", "-00:00", 2678442000 },
		{ "test3_first", "test3_last", 2, "Apples", "-00:00", 5097642000 },
		{ "test4_first", "test4_last", 2, "Apples", "-00:00", 7776042000 },
		{ "test5_first", "test5_last", 2, "Apples", "-00:00", 10368042000 },
		{ "test6_first", "test6_last", 2, "Apples", "-00:00", 13046442000 },
		{ "test7_first", "test7_last", 2, "Apples", "-00:00", 15638442000 },
		{ "test8_first", "test8_last", 2, "Apples", "-00:00", 18316842000 },
		{ "test9_first", "test9_last", 2, "Apples", "-00:00", 20995242000 },
		{ "test10_first", "test10_last", 3, "Apples", "-00:00", 23587242000 },
		{ "test11_first", "test11_last", 3, "Apples", "-00:00", 26265642000 },
		{ "test12_first", "test12_last", 3, "Apples", "-00:00", 28857642000 },
		{ NULL, NULL, 0, NULL, NULL, 0 },
	};
	birthday_data_t *bdd;

	bdd = extract_birthday_month_count((population_data_t *)&testd);
	ck_assert_uint_eq(bdd[0].count, 1);
	ck_assert_uint_eq(bdd[1].count, 1);
	ck_assert_uint_eq(bdd[2].count, 1);
	ck_assert_uint_eq(bdd[3].count, 1);
	ck_assert_uint_eq(bdd[4].count, 1);
	ck_assert_uint_eq(bdd[5].count, 1);
	ck_assert_uint_eq(bdd[6].count, 1);
	ck_assert_uint_eq(bdd[7].count, 1);
	ck_assert_uint_eq(bdd[8].count, 1);
	ck_assert_uint_eq(bdd[9].count, 1);
	ck_assert_uint_eq(bdd[10].count, 1);
	ck_assert_uint_eq(bdd[11].count, 1);
}
END_TEST

START_TEST (test_birthday_data_timezone)
{
	population_data_t testd[] = {
		{ "test1_first", "test1_last", 2, "Apples", "-00:00", 2678400000 },
		{ "test7_first", "test7_last", 2, "Apples", "-01:00", 2678400000 },
		{ NULL, NULL, 0, NULL, NULL, 0 },
	};
	birthday_data_t *bdd;

	bdd = extract_birthday_month_count((population_data_t *)&testd);
	ck_assert_uint_eq(bdd[0].count, 1);
	ck_assert_uint_eq(bdd[1].count, 1);
}
END_TEST

START_TEST (test_food)
{
	population_data_t testd[] = {
		{ "test1_first", "test1_last", 2, "Apples", "-00:00", 42000 },
		{ "test2_first", "test2_last", 2, "Bananas", "-00:00", 42000 },
		{ NULL, NULL, 0, NULL, NULL, 0 },
	};
	food_data_t *food_data;

	food_data = extract_food_data((population_data_t *)&testd);
	ck_assert_uint_eq(food_data[0].count, 1);
	ck_assert_uint_eq(food_data[1].count, 1);
	ck_assert(food_data[2].food_name == NULL);
}
END_TEST


START_TEST (test_food_allone)
{
	population_data_t testd[] = {
		{ "test1_first", "test1_last", 2, "Apples", "-00:00", 42000 },
		{ "test2_first", "test2_last", 2, "Apples", "-00:00", 42000 },
		{ "test3_first", "test3_last", 2, "Apples", "-00:00", 42000 },
		{ "test4_first", "test4_last", 2, "Apples", "-00:00", 42000 },
		{ "test5_first", "test5_last", 2, "Apples", "-00:00", 42000 },
		{ "test6_first", "test6_last", 2, "Apples", "-00:00", 42000 },
		{ "test7_first", "test7_last", 2, "Apples", "-00:00", 42000 },
		{ "test8_first", "test8_last", 2, "Apples", "-00:00", 42000 },
		{ "test9_first", "test9_last", 2, "Apples", "-00:00", 42000 },
		{ "test10_first", "test10_last", 3, "Apples", "-00:00", 42000 },
		{ NULL, NULL, 0, NULL, NULL, 0 },
	};
	food_data_t *food_data;

	food_data = extract_food_data((population_data_t *)&testd);
	ck_assert_uint_eq(food_data[0].count, 10);
}
END_TEST

int
main(void)
{
	Suite *s;
	SRunner *sr;
	TCase *tc;
	int number_failed;

	s = suite_create("extractor");
	tc = tcase_create("extractor");

	tcase_add_test(tc, test_json_parse);
	tcase_add_test(tc, test_csv_parse);

	tcase_add_test(tc, test_average_sibling);
	tcase_add_test(tc, test_average_sibling_all2);
	tcase_add_test(tc, test_average_sibling_rounds_up);

	tcase_add_test(tc, test_food);
	tcase_add_test(tc, test_food_allone);

	tcase_add_test(tc, test_birthday_data_all_jan);
	tcase_add_test(tc, test_birthday_data_one_each);
	tcase_add_test(tc, test_birthday_data_timezone);

	suite_add_tcase(s, tc);
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
