#include <iostream>
#include "plugin.h"

using namespace std;

void eject() {
  int fd;
  fd = open("/dev/cdrom", O_RDONLY | O_NONBLOCK);

  if (fd > 0) {
    ioctl(fd, CDROMEJECT, 0);

    close(fd);
  }
}

class HogeNPObject : public NPObject {
  public:
    static NPClass npClass;

    static bool HasMethod(NPObject *pObj, NPIdentifier name) {
      return validMethodName(name);
    }

    static bool Invoke(NPObject* pObj, NPIdentifier name, const NPVariant *args, uint32_t argc, NPVariant* result) {
      if (validMethodName(name)) {
        eject();

        BOOLEAN_TO_NPVARIANT(true, *result);
      }

      return true;
    }

  private:
    static bool validMethodName(NPIdentifier name) {
      NPUTF8 *methodName = ppFuncs->utf8fromidentifier(name);
      bool isMatchMethodName = strcmp(methodName, METHOD_NAME) == 0;

      ppFuncs->memfree(methodName);

      return isMatchMethodName;
    }
};

NPClass HogeNPObject::npClass = {
  NP_CLASS_STRUCT_VERSION,
  NULL, // Alloc
  NULL, // Dealloc
  NULL, // Invalidate
  HogeNPObject::HasMethod,  // hasMethod
  HogeNPObject::Invoke, // Invoke
  NULL, // InvokeDefault
  NULL, // hasProperty
  NULL, // getProperty
  NULL, // setProperty
  NULL, // RemoveProerty
  NULL, // enumerate
  NULL // construct
};

const char* NP_GetMIMEDescription() {
  return (const char*)"application/cdrom-eject-plugin::cdrom-eject-plugin";
}

NPError NP_GetValue(NPP instance, NPPVariable variable, void *value) {
  NPError rv = NPERR_NO_ERROR;

  switch (variable) {
    case NPPVpluginNameString:
      *static_cast<const char**>(value) = "cdrom-eject-plugin";

      break;

    case NPPVpluginDescriptionString:
      *static_cast<const char**>(value) = "cdrom-eject-plugin";

      break;

    case NPPVpluginNeedsXEmbed:
      *static_cast<bool*>(value) = true;

      break;

    case NPPVpluginScriptableNPObject: {
        *static_cast<NPObject**>(value) = ppFuncs->createobject(instance, &HogeNPObject::npClass);

        break;
    }

    default:
      rv = NPERR_INVALID_PARAM;

      break;
  }

  return rv;
}

NPError NP_Initialize(NPNetscapeFuncs* bFuncs, NPPluginFuncs* pFuncs) {
  ppFuncs = bFuncs;

  pFuncs->newp = NPP_New;
  pFuncs->getvalue = NP_GetValue;

  return NPERR_NO_ERROR;
}

NPError NP_Shutdown() {
  return NPERR_NO_ERROR;
}

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved) {
  return NPERR_NO_ERROR;
}
