# Mastering Qt 5

## Chapter 1 - Todo app

For an introduction chapter I didn't expect there to be much that was 'new' to me, I've already done a bunch of Qt tutorials and experimented with some features on my own. I was wrong, of course.

### Custom QWidget

In all of the tutorials I had done, not once was I ever tasked to create a custom widget. Creating a custom `Task` widget, a composite of Qt's built in widgets, very much reminded me of React and Angular's approaches to components. The text admits to cutting a corner in implementing model logic into the Task class but the power and expressiveness of this pattern is exciting.

### Signals and Slots

I had obviously been exposed to the Signals and Slots pattern in previous Qt experiments but had not seen them implemented on the fly ala the `MainWindow::addTask()` function. Every task that gets added is wired up to the GUI upon creation. Previous to this all `connect()` calls took place in constructors which made the system seem more rigid than it apparently is.

### A Clash of Styles

One difficulty I have is accepting the authors' style of C++. Coming from 'Programming Principles and Practice Using C++' I have a difficult time not following conventions set forth by Bjarne Stroustrup himself. Small things like using braces for object creation instead of parenthesis and prefixing member variables with lowercase 'm' are minor annoyances but the use of C-style casts is downright distasteful. I'll have to potentially come up with a 'style-interpretation guide' of my own for this repo.

There is also the use of a ranged for-loop that is suspect. The loop is used to count the number of completed tasks and takes six lines to achieve what `std::count_if` accomplishes in two. The suggestion of using algorithms to express common functionality is old and should probably be the lesson to be taught in this instance.

### The Application

In the end I can't argue with the output of the chapter, the todo list functions well on Mac and Windows. Perhaps this isn't an earth shaking revelation but when a cross platform project actually works without too much fiddling its a big deal to me.

All in all the first chapter does the job of exciting the reader to continue on through the text and that's exactly what you need. I look forward to continuing my journey to Master Qt 5.
