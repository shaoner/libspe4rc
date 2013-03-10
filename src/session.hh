/*!
 * \file session.hh
 * \author shaoner
 * \brief IRC client session
 */

#ifndef COM_SESSION_HH
# define COM_SESSION_HH

# include <QObject>
# include <QString>
# include <QByteArray>

# include <common.hh>
# include <protocol.hh>
# include <parser.hh>
# include <event-processor.hh>

namespace com
{

  /*!
   * \class Session
   * \brief This class is a single IRC connection
            It represents a client
   */
  class Session : public QObject
  {
    Q_OBJECT
  public:
    /// Ctor
    Session();
    /// Dtor
    ~Session();
  public:
    /// Client command
    Error               start() const;
    void                stop() const;
    void                send_raw(const QString& raw);
    /// Command shortcuts
    void                join(const QString& channel);
    void                part(const QString& channel);
    void                notice(const QString& who, const QString& message);
    void                mode(const QString& who, const QString& mode);
    /// IRC event listener notifier
    void                add_notifier(EventName type, Event* notifier);
    void                remove_notifier(EventName type, Event* notifier);
    void                set_default_notifier(EventName type, Event* notifier);
    void                reset_default_notifier(EventName type);
  private slots:
    /// Socket event listeners
    void                on_connect();
    void                on_disconnect();
    void                on_socket_error(QAbstractSocket::SocketError error);
    void                on_receive_data();
  public:
    /// Server paramaters
    const QString&      hostname() const;
    quint16             port() const;
    void                hostname(const QString& hostname);
    void                port(quint16 port);
    void                password(const QString& password);
    /// Client parameters
    const QString&      nickname() const;
    const QString&      altnickname() const;
    const QString&      username() const;
    const QString&      realname() const;
    void                nickname(const QString& nickname);
    void                altnickname(const QString& nickname);
    void                username(const QString& username);
    void                realname(const QString& realname);
  private:
    QString             _hostname;
    int                 _port;
    QString             _password;
    QString             _prefix;
    QString             _nickname;
    QString             _altnickname;
    QString             _username;
    QString             _realname;
    QByteArray          _readData;
    Parser              _parserDriver;
    EventProcessor*     _eventDriver;
    Protocol*           _proto;
  };

} // namespace com

#endif /* !COM_SESSION_HH */
