# mkasftp6 (ipv6 multicast file transfer protocol)
- accurate & errorfree udp multicast file transfer 
- (tested upto 512Mb file sizes)
- helps to know how good is the wifi receiver  of your phone (the RF module) (i.e. Your phone is not just the latest android but the quality. For e.g. an Android 6 tecno mobile in my hand sends and receives better than an Android 8 tecno mobile of my brother.) 
- works with or without terminal and for fine results making the receiver mobile a hotspot.
multicast android armv7-1a almost all android mobiles mkasftp binary
udp muticast file transfer protocol. multicast data filtering techniques on Android and Linux
prerequests
 --------
**for newer android versions(7 and above >7)
- update:install and use gui app mkasftp6.apk along with or without the shell binary mkasftp6. 

on Android 12 and above
-----------------------
one needs to give the installed app (mkasftp6.apk) all media permissions manually...until in the future ... make the program request the permssion.
- not to forget if it is android 12(or maybe above 9)...one should use "join mgroup" (the bottom most right button of the app) to connect to hostpot and follow what it says...it  requests for the user to "turn on wifi" but then one should follow the dialog that pops at the bottom of the app to connect...(as I think since Android 12(or 10 maybe)...wifi connection is only allowed if the app requests it...i.e. simply turning on wifi and trying to use it with the app cant work without getting the app to request it.  
you can use the app termux.
you can install clang and compile the code or just use the binaries...only .shrc changes to .bashrc

** for low version androids (like 5&6)...
the app terminone (terminal emulator) suffice-included on this release in case you want it all 2gether.
all one has to do is create a bin directory
on the home folder and put the binaries added on here on the code list
...add execution permission and done.
i.e (as in the Makefile)
 mkdir \~/bin
 echo "PATH=$PATH:\~/bin";export PATH" > ~/.shrc
 cp /sdcard/Download/mkasftp6 ~/bin
chmod a+x ~/bin/mkasftp6
 then start transfering files from/to phone to/from phone and PC.
**on linux the same story. I assume there you have clang or gcc as your option on the PC..
**So no need for ssh to run easy commands on remotely...mkasftp6 has the feature easily
to be done on all multicast receivers...

- (DONE) TODO:(worked on gui  although with not high priority): a gui featured android app.
Feedback on: bewketu@yandex.com
