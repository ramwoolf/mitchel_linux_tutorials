#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

char const * program_name;

void print_help(FILE* stream, int exit_code) {
    fprintf(stream, "Usage: %s options [ inputfile ... ]\n", program_name);
    fprintf(stream,
        "   -h --help               Display this help information.\n"
        "   -o --output filename    Write outout to file.\n"
        "   -v --verbose            Print Verbose messages.\n");
    exit(exit_code);
}

int main(int argc, char const *argv[])
{
    int next_option;
    char const * const short_options = "ho:v";
    const struct option long_options[] = {
        {"help", 0, NULL, 'h'},
        {"output", 1, NULL, 'o'},
        {"verbose", 0, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };

    char const * output_filename = NULL;
    int verbose = 0;
    program_name = argv[0];

    do
    {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);

        switch (next_option)
        {
        case 'h':
            print_help(stdout, 0);
        
        case 'o':
            output_filename = optarg;
            break;

        case 'v':
            verbose = 1;
            break;

        case '?':
            print_help(stderr, 1);

        case -1:
            break;
        
        default:
            abort();
        }
    } while (next_option != -1);

    if (verbose) {
        int i;
        for (i = optind; i < argc; ++i) {
            printf("Argument: %s\n", argv[i]);
        }
    }
    

    return 0;
}
