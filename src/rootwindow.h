#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QStackedLayout>
#include <QStackedWidget>
#include <QMainWindow>
#include <QStyleOption>
#include <QPainter>

#include "resource.h"
#include "capturewindow.h"
#include "settingswindow.h"
#include "displaymode.h"
#include "footer.h"

class RootWindow : public QMainWindow
{
    Q_OBJECT

  public:
    RootWindow(QWidget* parent = nullptr);
    void updateDisplayMode(DisplayMode display_mode);

  private:
    QString qss_light_mode;
    QString qss_dark_mode;
    QString qss_light_high_contrast_mode;
    QString qss_dark_high_contrast_mode;
};

#endif // ROOTWINDOW_H