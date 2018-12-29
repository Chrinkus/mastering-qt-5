# Mastering Qt 5

## Chapter 2 - SystemInfo App

If chapter 1 was impressive in its clarity and direction, chapter 2 represents the commitment of the authors to actually teach something along the way. Diving into `qmake` so early in the text helps to reveal a lot of the mysteries that Youtube tutorials are contentedly ignorant of.

### A Real Cross-Platform Project

I referred to the previous chapter's application as cross platform but it was the same code on Windows and Mac, just handed to different compilers. This chapter's project demands platform specific code and teaches the learner how to selectively compile different sources depending on environment.

I was able to confirm that the final project worked on Mac and Windows. I'm currently working on dual booting my Windows machine to have a Linux environment available. The WSL seems too limited for dev work.

### Design Patterns Ahoy!

It's been a while since I read Design Patterns by the G4 and when I did read it I had a tough time differentiating between some of the concepts. It's nice that this text is deliberate when incorporating them.

There are enough singleton nay-sayers out there to have made me question whether the pattern is of any use in modern programming. I like the implementation in chapter 2 and I'm sure this won't be the last time the pattern gets used in the text. It will be interesting to see whether the testing chapter tackles the pattern.

### It's an OO World

Despite the news I've read object oriented programming is alive and well. I can't imagine how GUI programming would be accomplished without it. This chapter makes great use of inheritance and composition to achieve the final project. There are a few decisions I would question but no one questions a working application, do they?

Specifically, the Mac and Linux implementations of the `cpuLoadAverage()` member function are identical, couldn't they be implemented in the base class as virtual and overridden only in the Windows implementation? My guess is that no, since they are both Unix based their similarity is convenient but not indicitive of how the function would be implemented in 'normal' cases. Still worth the discussion.

Also, for the `cpuLoadAverage()` calculation, the previous data is stored in a `QVector` and referenced awkwardly using indexes. I would think that it would be more semantically appropriate to store the info in a struct and calculate using clearer names:
```
struct Sample {
    qulonglong user, nice, system, idle;
};

double SysInfoMacImpl::cpuLoadAverage()
{
    Sample old_sample = mCpuLoadLastValues;
    Sample new_sample = cpu_raw_data();
    mCpuLoadLastValues = new_sample;

    double overall = (new_sample.user - old_sample.user) +
    		     (new_sample.nice - old_sample.nice) +
		     (new_sample.system - old_sample.system);
    // ...
}
```
Again, the objection I would see to this would be that the info used by Windows is different than the info used by Mac and Linux. This solution, however, greatly contributes to the readability of the code so I would think that platform-specific embedded structs wouldn be a decent solution.

### Building w/qmake

I appreciated the deep dive into the build process so early in the text. Having spent some time working with CMake I have an appreciation for build processes. Still I was disappointed to find zero mentions of CMake in the text's index and wonder if the authors actually use qmake in their production work.

I have not yet implemented a Qt project using CMake myself however so perhaps getting the MOC system to play nice by hand is not an attractive teaching point for the text.

### Bookmark the Errata

An unfortunate thing happened when building and running the app for the first time, it crashed immediately. Something was wrong. I double and triple checked my code but could not find the error. Then I searched on stack overflow and found the same problem answered by one of the authors. They had missed setting a centralWidget layout in the source code and that caused a segfault when attempting to reference a null value.

The actual solution offered by Guillaume Lazar was to edit the XML code by hand, something that Qt discourages you from doing anytime you accidentally look at the form code. 

### The Application

As mentioned above, the application works well on Windows and Mac. The default window sizing could have been increased and I may just bake that into the `MainWindow` class anyways. The cpuAverage widget jumps around from ~5% to 50% on my MacBookPro but since 500ms for a processor is an eternity it's probably not a big deal.
