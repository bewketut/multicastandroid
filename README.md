# multicastandroid armv7-1a all android mobiles binary
udp muticast file transfer protocol; multicast data filtering techniques on Android and Linux
prerequests
------------
**for low version androids (like 5&6)...
the app terminone (terminal emulator) suffice.
all one has to do is create a bin directory
on the home folder and put the binaries added on here on the code list
...add execution permission and done.
i.e
 mkdir \~/bin
 echo "PATH=$PATH:\~/bin";export PATH" >> ~/.shrc
 cp /sdcard/Download/mkasftp ~/bin
chmod a+x ~/bin/mkasftp
 then start transfering files from/to phone to/from phone and PC.
**for newer android versions(7 and above >7) you can use the app termux.
you can install clang and compile the code or just use the binaries...only .shrc changes to .bashrc
**on linux the same story. I assume there you have clang or gcc as your option on the PC..
**So no need for ssh to run easy commands on remotely...mkasftp has the feature easily
to be done on all multicast receivers...

TODO(although with not high priority): a gui featured android app.
Feedback on: bewketu@yandex.com
