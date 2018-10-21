#ifndef MESSAGE_H
#define MESSAGE_H

class QString;
class QIcon;

class Message
{
public:

    enum MessageType
    {
      Unknown,
      Error,
      Warning
    };

    Message(MessageType _type,QString _info,QString _file = QString(),int _line = -1);

    MessageType type;
    QString info;
    QString file;
    int line;
    QIcon icon;

    QIcon messageIcon(MessageType type);
};

#endif // MESSAGE_H
