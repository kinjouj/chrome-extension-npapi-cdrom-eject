#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/cdrom.h>

#include "npapi.h"
#include "npfunctions.h"
#include "nptypes.h"

#define METHOD_NAME "eject"

NPNetscapeFuncs* ppFuncs;
