#include <stdio.h>
#include <string.h>

#include "argparser.h"

void assert(int pred, const char* msg) {
    if (!pred)
        fprintf(stderr, "ERROR: %s\n", msg);
}

/*
 * For arguments that take values (such as -d, --double), you can
 * use any of the following formats:
 *
 *      ./test -d 3
 *      ./test -d=3
 *      ./test --double 3
 *      ./test --double=3
 *
 * If you just want to check whether a flag is present (e.g. ./test -p),
 * use the ARGTYPE_BOOL option. These flags can be combined during
 * program execution (e.g. "./test -vp" is equivalent to "./test -v -p")
 */

int main(int argc, char* argv[]) {
    int v;
    int i = 0;
    double d = 0.0;
    char s[50] = "Zero";
    int p;
    int f;

    argparser ap = argparser_create(argc, argv, PARSEMODE_STRICT);

    argparser_add(&ap, "-v", NULL,        ARGTYPE_BOOL,   &v, "V arg");
    argparser_add(&ap, NULL, "--integer", ARGTYPE_INT,    &i, "I arg");
    argparser_add(&ap, "-d", "--double",  ARGTYPE_DOUBLE, &d, "D arg");
    argparser_add(&ap, "-s", "--string",  ARGTYPE_STRING, &s, "S arg");
    argparser_add(&ap, "-p", "--present", ARGTYPE_BOOL,   &p, "P arg");
    argparser_add(&ap, "-f", "--flag",    ARGTYPE_BOOL,   &f, "F arg");

    argparser_parse(&ap);

    /* Args */
    assert(v != 0,                 "v was not modified");
    assert(i != 0,                 "i was not modified");
    assert(d != 0.0,               "d was not modified");
    assert(strcmp(s, "Zero") != 0, "s was not modified");
    assert(p == 1,                 "p was not modified");
    assert(f == 1,                 "f was not modified");

    /* Print arg values */
    fprintf(stdout, "v: %d\n", v);
    fprintf(stdout, "i: %d\n", i);
    fprintf(stdout, "d: %f\n", d);
    fprintf(stdout, "s: %s\n", s);
    fprintf(stdout, "p: %d\n", p);
    fprintf(stdout, "f: %d\n", f);

    return 0;
}
