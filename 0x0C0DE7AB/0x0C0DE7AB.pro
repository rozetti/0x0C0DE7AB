TEMPLATE = subdirs
SUBDIRS += \
    editor \
    6it \
    RTQt
message($$CONFIG)
winrt {
} else {
SUBDIRS += \
    RZQtIDELeftGutterWidgetTests \
    RZQtIDELeftGutterWidgetLineTests \
    RZQtIDELeftGutterWidgetLinesTests
}
