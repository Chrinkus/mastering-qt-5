# Mastering Qt 5

## Chapter 3 - GalleryCore Library

This is a difficult chapter to comment on immediately, we built the underlying library for future projects but have not been able to 'test' the code we have written. There are a few to mention however.

### Object Oriented SQL Hierarchy

I've had a few questions about how to implement an SQLITE database in a single-responsibility, object-oriented way. The object hierarchy in the gallery\_core project seems to do a great job of doing just that:

* Album, Picture
    - basic data objects
        - map to table row data from specific tables
* DatabaseManager
    - attaches to a database file `gallery.db`
    - has Dao's as public const members for each table
* AlbumDao, PictureDao
    - used to access specific tables
    - only store pointers back to database manager
        - used to perform CRUD ops on own table
* AlbumModel, PictureModel
    - connects to 'some view'
    - store reference to database manager
        - is the client of the Dao's
    - stores an in memory buffer of data
        - AlbumModel stores all albums
        - PictureModel stores pictures from most recently queried album

Something I had to wrap my head around was that the pictures are not stored in the database. They are pictures that exist somewhere and the database just stores the url to them. This means that moving pictures can invalidate pictures and albums in this app. Would that throw an error?

Also, albums do not contain a list of contained pictures, they just represent an id that pictures within that album store. I guess this means that if the same picture is stored in multiple albums it's url will be added multiple times to the `pictures` database. This seems preferable to having each picture object store an array of album ids that may only really store a single id.

### Pointer to Vector of Pointers to Pictures

The text implementation of the in-memory buffer objects is questionable. There will only be one model at any given time so only keeping a pointer to a vector rather than the vector itself seems unnecessary. The use of smart pointers makes sense and is modern but the pointer to a 24byte vector is stingy considering the vector is STILL 24 bytes and we're storing another 8 for a pointer to it.

This may end up having a purpose later in the mobile application but for now and the desktop I'm sticking to `std::vector<std::unique_ptr<Picture>>`.

### The App

There is no end-app for this chapter so it feels a little Halo 2-ish but the next two chapters promise to be cool. The data management system is very interesting and I look forward to stealing it for my own applications.
