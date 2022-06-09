#with folder move mkasftp to #Download folder. for terminone.
#run: sh note.sh
mkdir ~/bin;
print "PATH=$PATH:~/bin; export PATH; cd /sdcard/Download;" > ~/.shrc;

cp /sdcard/Download/mkasftp ~/bin;
chmod a+x ~/bin/mkasftp

print "finished...now run mkasftp on the terminal.";
