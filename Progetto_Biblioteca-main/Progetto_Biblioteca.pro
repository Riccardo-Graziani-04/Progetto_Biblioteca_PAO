QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Set the folder for object files (.o)
OBJECTS_DIR = build

# Set the folder for generated moc files
MOC_DIR = build/moc

# Set the folder for generated UI files
UI_DIR = build/ui

# Set the folder for generated RCC files (resource files)
RCC_DIR = build/rcc

# Keep the executable in the main project directory
DESTDIR = $$PWD

SOURCES += \
    Model/Items/AbstractItem.cpp \
    Model/Items/Book.cpp \
    Model/Items/Movie.cpp \
    Model/Items/Music.cpp \
    Model/JSON/Json.cpp \
    Model/JSON/JsonFile.cpp \
    Model/JSON/JsonReader.cpp \
    Model/JSON/JsonRepository.cpp \
    Model/JSON/JsonVisitor.cpp \
    Model/Memory/ItemRepository.cpp \
    Model/Utility/EnumsConvertions.cpp \
    View/DetailWidgets/ItemDetailWidget.cpp \
    View/EditWidgets/AbstractItemEditWidget.cpp \
    View/EditWidgets/BookEditWidget.cpp \
    View/EditWidgets/ItemEditInjectior.cpp \
    View/EditWidgets/ItemEditWidget.cpp \
    View/EditWidgets/MovieEditWidget.cpp \
    View/EditWidgets/MusicEditWidget.cpp \
    View/EditWidgets/TypeSelector.cpp \
    View/ListWidgets/ItemCardWidget.cpp \
    View/ListWidgets/ItemListWidget.cpp \
    View/ListWidgets/SearchWidget.cpp \
    main.cpp \
    View/MainWindow.cpp

HEADERS += \
    Model/Items/Book.h \
    Model/Items/Movie.h \
    Model/Items/Music.h \
    Model/JSON/Json.h \
    Model/JSON/JsonFile.h \
    Model/JSON/JsonReader.h \
    Model/JSON/JsonRepository.h \
    Model/JSON/JsonVisitor.h \
    Model/Memory/ItemRepository.h \
    Model/Utility/ConstItemVisitor.h \
    Model/Utility/EnumsConvertions.h \
    Model/Utility/ItemVisitor.h \
    Model/Utility/ItemsEnums.h \
    View/DetailWidgets/ItemDetailWidget.h \
    View/EditWidgets/AbstractItemEditWidget.h \
    View/EditWidgets/BookEditWidget.h \
    View/EditWidgets/ItemEditInjectior.h \
    View/EditWidgets/ItemEditWidget.h \
    View/EditWidgets/MovieEditWidget.h \
    View/EditWidgets/MusicEditWidget.h \
    View/EditWidgets/TypeSelector.h \
    View/ListWidgets/ItemCardWidget.h \
    View/ListWidgets/ItemListWidget.h \
    View/ListWidgets/SearchWidget.h \
    View/MainWindow.h \
    Model/Items/AbstractItem.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  resources.qrc
