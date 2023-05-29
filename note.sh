#mkasftp tested 100% on different #android mobiles and works perfect.
#with folder move mkasftp to the #Download folder. for terminone:-
#run this note on shell: sh note.sh

mkdir -p ~/bin && cp mkas* ~/bin/ && chmod a+x ~/bin/mkas* && mkdir -p /sdcard/m4power6 && mkdir -p /sdcard/m4power6/mkasftp &&  printf "alias m4='~/bin/mkasftcp'; alias m6='~/bin/mkasftcp6'; alias ..='cd ..'; alias mkf='~/bin/mkasudp'; alias mkf6='~/bin/mkasudp6';cd /sdcard/m4power6/mkasftp;\n" >> ~/.shrc && cp ~/.bashrc ~/.bashrc~ && cp ~/.shrc ~/.bashrc && printf "Now ready to use mkasftp6 and mkasftp6 android app using *two* different android mobiles or computer with terminals. old ~/.bashrc is ~/.bashrc~\n";
printf "finished...now run mkasftp on the terminal.\n";
