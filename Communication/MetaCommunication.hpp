# pragma once

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QTimer>
#include <QMetaType>

namespace zzs
{
	class META_COMMUNICATION : public QObject
	{
		Q_OBJECT

	public:
		enum class CONNECTION_STATUS
		{
			DISCONNECT,
			CONNECTING,
			CONNECTED,
			ERROR
		};
	public:
		META_COMMUNICATION(QObject* parent = nullptr)
			:ConnectionState__(CONNECTION_STATUS::CONNECTED),
			RefreshTimer__(nullptr)
		{
			qRegisterMetaType<CONNECTION_STATUS>("META_CONN_STATUS");
			this->RefreshTimer__ = new QTimer(this);
		}
		

		virtual bool Connect(QString Host, uint16_t port, uint timeout = 0) = 0;
		virtual bool Disconnect() = 0;
		virtual bool SendUserCommand(const QVariantMap& CommandPair) = 0;


	signals:
		void ConnectionStateChanged(META_COMMUNICATION::CONNECTION_STATUS);
		void ReceivedPDO(QVariantList);

	protected:
		virtual bool RequestPDO()
		{
			if (this->ConnectionState__ == CONNECTION_STATUS::CONNECTED)
				return true;
			else
				return false;
		}

		QTimer* RefreshTimer__;
		CONNECTION_STATUS ConnectionState__;
	};
};