#include <QApplication>
#include <QStyleFactory>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("MooDoo");
    app.setApplicationDisplayName("MooDoo - Your Mood-Aware Planner");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("MooDoo");
    
    // Set modern style
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // Create and show main window
    MainWindow window;
    window.show();
    
    return app.exec();
} 