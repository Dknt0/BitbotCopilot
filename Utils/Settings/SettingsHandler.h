#pragma once

#include <QObject>
#include <tuple>
#include <QSettings>
#include <QList>
#include "../GamepadDriver/ZQGamepad.h"

#define ZSet SettingsHandler::getInstance()

struct AutoRunCommand_t
{
	QString KeyName;
	QString WaitUntil;
	size_t WaitTime;
};

using AutoRunCmdList = QList<AutoRunCommand_t>;

class SettingsHandler  : public QObject
{
	Q_OBJECT

public:
	static SettingsHandler* getInstance();
public:
	SettingsHandler(QObject *parent=nullptr);
	~SettingsHandler();
	std::tuple<QString, uint16_t> getIPAndPort();
	std::tuple<QString, QString> getBackendPathAndName();
	bool isVIP();
	bool isBackendRemote();
	std::tuple<QString, QString> getRemoteBackendUserNameAndIP();

	AutoRunCmdList  getAutoRunCommandList();

private:
	QVariant WRSettings(QString key, QVariant default_value);
	QSettings* settings__;
};