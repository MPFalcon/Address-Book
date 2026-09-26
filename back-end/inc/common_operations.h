#ifndef COMMON_OPERATIONS_H
#    define COMMON_OPERATIONS_H

#    include "common.h"

#    define MAX_EMAIL_LEN 50
#    define MAX_NAME_LEN  50
#    define MAX_PN_LEN    10

// Define operation codes for the address book application
enum operation_codes
{
    OP_SHOW         = 0x01,
    OP_POST_ENTRY   = 0x2,
    OP_GET_ENTRY    = 0x3,
    OP_UPDATE_ENTRY = 0x4,
};

// Define update options for modifying entries in the address book
enum update_options
{
    OP_UPDATE_NAME  = 0x01,
    OP_UPDATE_PN    = 0x02,
    OP_UPDATE_EMAIL = 0x04,
};

#endif /* COMMON_OPERATIONS_H */

// EOF
