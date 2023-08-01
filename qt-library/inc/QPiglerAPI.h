#include <QObject>
#include <QString>
#include <QImage>

#include "PiglerAPI.h"
#include "PiglerTapServer.h"

class QPiglerAPI;

class QPiglerTapHandler : public IPiglerTapHandler
{
private:
	QPiglerAPI *api;
	
public:
	QPiglerTapHandler(QPiglerAPI *api);
	virtual void handleTap(TInt uid, TBuf<64> appName, TBuf<256> text, TBool remove);
};

class QPiglerAPI : public QObject
{
	Q_OBJECT
	
private:
	PiglerAPI* api;
	QPiglerTapHandler *handler;
	
public:
	explicit QPiglerAPI(QObject* parent);
	~QPiglerAPI();
	
public slots:
	qint32 init(QString name);
	qint32 init();
	
	QString appName();
	QString hexAppName();
	
	qint32 setNotification(qint32 notificationId, QString title, QString message);
	qint32 updateNotification(qint32 notificationId, QString title, QString message);
	qint32 createNotification(QString title, QString message);
	
	qint32 removeNotification(qint32 notificationId);
	qint32 removeAllNotifications();
	
	qint32 getLastTappedNotification();
	
	qint32 setRemoveNotificationOnTap(qint32 notificationId, bool remove);
	
	qint32 setNotificationIcon(qint32 notificationId, QImage icon);
	
	void close();
	
	void doHandleTap(qint32 notificationId, QString appName, QString appNameHex, QString text, bool remove);
	
signals:
	void handleTap(qint32 notificationId, QString appName, QString appNameHex, QString text, bool remove);
};
