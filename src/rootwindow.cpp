#include "rootwindow.h"

RootWindow::RootWindow(QWidget* parent)
  : QMainWindow(parent)
{
    // Load in the font resource file
    Resource::import(QString("PlusJakartaSans Variable"));

    // Load in the different display mode style sheets
    this->qss_light_mode = Resource::load(QString(":/ui/style/light"));
    this->qss_dark_mode = Resource::load(QString(":/ui/style/dark"));
    this->qss_light_high_contrast_mode =
      Resource::load(QString(":/ui/style/light-high-contrast"));
    this->qss_dark_high_contrast_mode =
      Resource::load(QString(":/ui/style/dark-high-contrast"));

    // Create the central layout for the main window
    QBoxLayout* central_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    central_layout->setMargin(0);
    central_layout->setSpacing(0);

    // Create the central widget to store the layout and main window content
    QWidget* central_widget = new QWidget(this);
    central_widget->setLayout(central_layout);

    // Create the stacked widget which will store the different windows
    QStackedWidget* stacked_widget = new QStackedWidget(this);

    // Create the capture window widget
    CaptureWindow* capture_window = new CaptureWindow;
    stacked_widget->addWidget(capture_window);

    // Create the settings window widget
    SettingsWindow* settings_window = new SettingsWindow(this);
    stacked_widget->addWidget(settings_window);

    // Create the debug footer which allows for updating the stacked widget
    Footer* footer = new Footer(this);

    // Add the base items to the central layout
    central_layout->addWidget(stacked_widget);
    central_layout->addWidget(footer);

    // Set the main windows central widget and object name
    this->setCentralWidget(central_widget);
    this->setObjectName(QString("MainWindow"));

    // Set the current display mode based off of the user settings
    this->updateDisplayMode(
      (DisplayMode)SettingsHandler::getValue("display_mode", DisplayMode::Dark)
        .toInt());

    // Connect the window updated listener
    connect(footer,
            &Footer::selectedWindowUpdated,
            [=](int index)
            {
                stacked_widget->setCurrentIndex(index);
            });

    // Connect the display mode updated listener
    connect(settings_window,
            &SettingsWindow::displayModeUpdated,
            [=](DisplayMode display_mode)
            {
                this->updateDisplayMode(display_mode);
            });
};

void
RootWindow::updateDisplayMode(DisplayMode display_mode)
{
    // Set the new display mode value in the user settings
    SettingsHandler::setValue("display_mode", display_mode);

    // Update the root style sheet
    switch (display_mode)
    {
        case Light:
            this->setStyleSheet(this->qss_light_mode);
            break;
        case Dark:
            this->setStyleSheet(this->qss_dark_mode);
            break;
        case LightHighContrast:
            this->setStyleSheet(this->qss_light_high_contrast_mode);
            break;
        case DarkHighContrast:
            this->setStyleSheet(this->qss_dark_high_contrast_mode);
            break;
    };
};