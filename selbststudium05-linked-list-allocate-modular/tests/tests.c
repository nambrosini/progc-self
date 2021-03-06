#include "CUnit/Basic.h"
#include "test_utils.h"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

#define INFILE_TEST_END "input_end.input"
#define INFILE_TEST_INSERT_ONE "input_insert_one.input"
#define INFILE_TEST_INSERT_AND_SHOW "input_insert_and_show.input"
#define INFILE_TEST_INSERT_DUPLICATE "input_insert_duplicate.input"
#define INFILE_TEST_INSERT_IN_ORDER "input_insert_in_order.input"
#define INFILE_TEST_REMOVE "input_remove.input"
#define INFILE_TEST_REMOVE_NON_EXISTING "input_remove_non_existing.input"
#define INFILE_TEST_CLEAR "input_clear.input"

/// @brief The name of the STDOUT text file.
#define OUTFILE "stdout.txt"
/// @brief The name of the STDERR text file.
#define ERRFILE "stderr.txt"

static int setup(void)
{
    remove_file_if_exists(OUTFILE);
    remove_file_if_exists(ERRFILE);
    return 0; // success
}

static int teardown(void)
{
    // Do nothing.
    // Especially: do not remove result files - they are removed in int setup(void) *before* running a test.
    return 0; // success
}

static void testEnd() {
    const char *out_txt[] = {
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Exiting...\n"
    };

    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_TEST_END);

    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void testInsertOne() {
    const char *out_txt[] = {
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Exiting...\n"
    };

    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_TEST_INSERT_ONE);

    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void testInsertAndShow() {
    const char *out_txt[] = {
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "List of people:\n",
        "John Doe, 42\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Exiting...\n"
    };

    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_TEST_INSERT_AND_SHOW);

    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void testInsertDuplicate() {
    const char * out_txt[] = {
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Could not insert person. Person already exists.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Exiting...\n"
    };

    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_TEST_INSERT_DUPLICATE);

    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void testInsertInOrder() {

    const char *out_txt[] = {
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "List of people:\n",
        "John Doe, 42\n",
        "Zlatan Ibrahimovic, 38\n"
        "Pinco Pallino, 12\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Exiting...\n"
    };

    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_TEST_INSERT_IN_ORDER);

    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void testRemove() {
    const char *out_txt[] = {
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "List of people:\n",
        "John Doe, 42\n",
        "Zlatan Ibrahimovic, 38\n"
        "Pinco Pallino, 12\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to remove:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully removed.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "List of people:\n",
        "Zlatan Ibrahimovic, 38\n"
        "Pinco Pallino, 12\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Exiting...\n"
    };

    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_TEST_REMOVE);

    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void testRemoveNonExisting() {
    const char *out_txt[] = {
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to remove:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Could not delete person. Person doesn't exists.\n"
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Exiting...\n"
    };

    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_TEST_REMOVE_NON_EXISTING);

    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

static void testClear() {
    const char *out_txt[] = {
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Person to insert:\n",
        "Input first name: \n",
        "Input name: \n",
        "Input age: \n",
        "Person successfully inserted.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "List of people:\n",
        "John Doe, 42\n",
        "Zlatan Ibrahimovic, 38\n"
        "Pinco Pallino, 12\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "List successfully cleared.\n",
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "List is empty.\n"
        "\nWelcome to your personal stalking list:\n",
        "I(nsert)\n",
        "R(emove)\n",
        "S(how)\n",
        "C(lear)\n",
        "E(nd)\n",
        "Make your choice:\n",
        "Exiting...\n"
    };

    int exit_code = system(XSTR(TARGET) " 1>" OUTFILE " 2>" ERRFILE " <" INFILE_TEST_CLEAR);

    CU_ASSERT_EQUAL(exit_code, 0);
    assert_lines(OUTFILE, out_txt, sizeof(out_txt) / sizeof(*out_txt));
}

int main(void)
{
    // setup, run, teardown
    TestMainBasic(
        "person data management", 
        setup, teardown, 
        testEnd,
        testInsertOne,
        testInsertAndShow,
        testInsertDuplicate,
        testInsertInOrder,
        testRemove,
        testRemoveNonExisting,
        testClear
    );
}
