#include "main.h"

int main(void)
{
    int exit_code = EXIT_FAILURE;

    DEBUGPRINTF("%s", "Starting address book...");

    // Start the server
    if (SUCCESS != start_server())
    {
        ERRORPRINTF(start_server());
        goto EXIT;
    }

    exit_code = EXIT_SUCCESS;

EXIT:
    return exit_code;
}

// EOF
