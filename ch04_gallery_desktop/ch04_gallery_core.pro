TEMPLATE = subdirs

SUBDIRS += \
    gallery_core \
    gallery_desktop

gallery_desktop.depends = gallery_core
