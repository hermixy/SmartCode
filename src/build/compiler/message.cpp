#include "message.h"
#include <QString>
#include <core_constants.h>



Message::Message(Message::MessageType _type, QString _info
                 , QString _file, int _line)
{
  type = _type;
  info=_info;
  file=_file;
  line=_line;
  icon = messageIcon(type);
}

QIcon Message::messageIcon(Message::MessageType type)
{
  switch(type)
    {
    case Message::Error:
      return QIcon(Core::Icon::COMPILE_ERROR);
    case  Message::Warning:
      return QIcon(Core::Icon::COMPILE_WARNING);
    }

  return QIcon();
}


