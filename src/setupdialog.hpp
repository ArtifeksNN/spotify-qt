#pragma once

#include "spotify/auth.hpp"

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QUrl>
#include <QLineEdit>
#include <QDesktopServices>
#include <QPushButton>
#include <QCoreApplication>
#include <QWebEngineView>
#include <QMessageBox>

class SetupDialog : public QDialog
{
public:
	explicit SetupDialog(QWidget *parent = nullptr);
	~SetupDialog() override;
private:
	spt::Auth *auth;
};