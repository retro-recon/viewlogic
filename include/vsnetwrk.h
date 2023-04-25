/*
 * $Id: vsnetwrk.h,v 1.2.11.1 1995/10/17 20:41:05 cway Stab $
 *
 * System includes and defines for network access and process management
 *
 * Peter Colby- May 1991
 *
 * Copyright 1991 by Viewlogic Systems, Inc.
 */

#ifndef vsNETWORK_H
#define vsNETWORK_H

#if (vlOS_AIX || vlOS_SYSVR4)
#include <sys/utsname.h>
#include <sys/select.h>
#endif

#if (vlOS_SYSVR4)
#include <sys/systeminfo.h>
#include <sys/sockio.h>
#endif

#if (vlOS_UNIX)
#  include <sys/socket.h>
#  if HW_SAMSUNG
#    include <sys/in.h>
#  else
#    include <netinet/in.h>
#  endif
#  include <netdb.h>
#  include <arpa/inet.h>
#  include <sys/un.h>
#  include <net/if.h>
#endif

#endif /* vsNETWORK_H */
