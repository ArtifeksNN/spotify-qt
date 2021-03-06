#pragma once

#include "../mainwindow.hpp"
#include "../spotify/spotify.hpp"

#include <QMenu>
#include <QMessageBox>

class MainMenu: public QMenu
{
Q_OBJECT

public:
	MainMenu(spt::Spotify &spotify, Settings &settings, QWidget *parent = nullptr);

private:
	QWidget *parent;
	spt::Spotify &spotify;
	Settings &settings;
	QAction *about;
	QMenu *deviceMenu;
	void refreshDevices();
};
