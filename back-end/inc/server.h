#ifndef SERVER_H
#    define SERVER_H

#    include <sys/ioctl.h>
#    include <net/if.h>
#    include <linux/if_packet.h>
#    include <linux/if_ether.h>
#    include <arpa/inet.h>
#    include <sys/select.h>
#    include <sys/wait.h>
#    include <sys/types.h>
#    include <sys/socket.h>
#    include <netdb.h>

#    include "common.h"

/**
 * @brief Start the server.
 *
 * @return 0 on success, -1 on failure.
 */
int start_server(void);

#endif /* SERVER_H */

// EOF
