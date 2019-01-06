# Mastering Qt 5

## Chapter 4 - Desktop Gallery

This chapter puts the work in chapter 3 to use, crafting a desktop GUI for our gallery based on the gallery\_core library.

### Qt Classes to Familiarize With

At the end of last chapter we were introduced to the `QAbstractListModel` and the `QModelIndex` type. These are new to me and deserve some reading time. Knowing that they tie into the Qt Model/View architecture I saved this exploration for this chapter. Along with these there are still more new classes to look into, the first of which being the `QIdentityProxyModel`.

#### [QAbstractListModel](http://doc.qt.io/qt-5/qabstractlistmodel.html)

An abstract model that can be subclassed to create one-dimensional list models. More specialized than `QAbstractItemModel` so is not suitable for tree views, use `QAbstractTableModel` for two-dimensional data views.

Inherits from `QAbstractItemModel`. When subclassing `QAbstractListModel` we must implement overrides for `rowCount()` and `data()`. To syncronize any subscribing views, when inserting rows we need to book-end logic with `beginInsertRows()` and `endInsertRows()`. Its the same for removing rows.

There are a few terms that keep popping up that I need to better familiarize myself with, namely `Index` and `DisplayRole`. An index seems to be like an iterator since we need to define it for complex models. The display role is obviously tied to presentation but where and how these roles get defined and implemented is what I need to learn.

### A Document to Rule Them All

Digging into the above classes led me to the Qt Documentation for [Model/View Programming](http://doc.qt.io/qt-5/model-view-programming.html). I will spend some time reading this before continuing..

##### Sometime later...

Ok! Well that was.. a lot. Some necessary connections were made but before I continue with my work through the text I need to take what chapters 3 and 4 have presented and make my own project, attempting to follow the same pattern.

### The App

The photogallery app works as expected, I just don't have many pictures on my linux machine. I'll try again later on my Mac.
