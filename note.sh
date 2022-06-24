#mkasftp tested 100% on different #android mobiles and works perfect.
#with folder move mkasftp to the #Download folder. for terminone:-
#run this note on shell: sh note.sh

mkdir ~/bin;
printf "PATH=$PATH:~/bin; export PATH; cd /sdcard/Download;\n" > ~/.shrc;

cp /sdcard/Download/mkasftp ~/bin;
chmod a+x ~/bin/mkasftp;

printf "finished...now run mkasftp on the terminal.\n";
