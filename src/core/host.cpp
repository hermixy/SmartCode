#include "host.h"

Host::Host()
{

}

Host::OS Host::os()
{
#if defined(Q_OS_WIN)
  return  Windows;
#elif defined (Q_OS_LINUX)
  return Linux;
#elif defined (Q_OS_MAC)
  return Mac;
#elif defined (Q_OS_UNIX)
  return Unix;
#else
  return Unknown;
#endif

}

