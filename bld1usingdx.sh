#!/usr/bin/env sh
#to be run as: sh bld1usingdx.sh
#where the android manifest exist.
#i.e. AndroidManifest.xml
# requires android.jar api 30
#or android 11 api
#use openssl to create keys and #certificates as your or use the included #key certificate.
# you need to change ecj's default option #to use java 8/9 (change the 7 to 9) which #is found at "/data/data/com.termux/files/usr/bin/ecj" or $PREFIX/bin/ecj
#nano can do it...nano `which ecj` write #the 7 to 9 and then ctrl-o then ctrl-x
#if android.jar is included there...delete #from the option -cp to the android.jar #there...
#search android 11 or api 30 android.jar #can be found on github.com
#now to editing this file:
#change on JARFILEHOME at the place in #this note marked "NOTE IMPORTANT" towards #the end of this (the start of the last #quarter approximately below.
#for java 8/9 to work with ecj you need #the lambda.jar included in this package or #separately (to be downloaded where you #downloaded this.)
#Best of luck with mobile android app #development. ~Bewketu Tadilo (~bts).
#The written and compiled app works on #android 8 and above.
#####################################################################


for CMD in aapt dx ecj
do
       	[ -z "$(command -v "$CMD")" ] && printf "%s\\n" " \"$CMD\" not found" && NOTFOUND=1
done
[ "$NOTFOUND" = "1" ] && exit
[ "$1" ] && [ -f "$1/AndroidManifest.xml" ] && cd "$1"
[ -f AndroidManifest.xml ] || exit

_CLEANUP_ () {
       	printf "\\n\\n%s\\n" "Completing tasks..."
       	[ "$CLEAN" = "1" ] 
      	rmdir --ignore-fail-on-non-empty assets
       	rmdir --ignore-fail-on-non-empty res
       	rm -rf output
       	rm -rf gen
       	rm -rf obj
	printf "\\n\\n%s\\n\\n" "Share https://wiki.termux.com/wiki/Development everwhere🌎🌍🌏🌐!"
}


_UNTP_() {
       	printf "\\n\\n%s\\n\\n\\n""Unable to process"
       	_CLEANUP_
       	exit
}

PKGNAME="$(grep -o "package=.*" AndroidManifest.xml | cut -d\" -f2)"


printf "%s\\n" "Beginning build"
[ -d assets ] || mkdir assets
[ -d res ] || mkdir res
mkdir -p output
mkdir -p gen
mkdir -p obj


printf "%s\\n" "aapt: started..."
aapt package -f -m \
    	-M "AndroidManifest.xml" \
       	-J "gen" \
       	-S "res" || _UNTP_
printf "%s\\n\\n" "aapt: done"
printf "%s\\n" "ecj: begun..."
for JAVAFILE in $(find . -type f -name "*.java")
do
       	JAVAFILES="$JAVAFILES $JAVAFILE"
done
##NOTE IMPORTANT
###here "/sdcard/JavaNIDE" to be changed to where you put the jar java library files###
JARFILEHOME=/sdcard/JavaNIDE/
###i.e the three java 8/9 jars###

ecj -d ./obj -sourcepath .  $JAVAFILES     -cp "$JARFILEHOME"/android.jar:"$JARFILEHOME"/androidx.jar:"$JARFILEHOME"/lambda.jar || _UNTP_

printf "%s\\n\\n" "ecj: done"

printf "%s\\n" "dx: started..."
dx --dex --min-sdk-version=26 --output=output/classes.dex obj || _UNTP_
printf "%s\\n\\n" "dx: done"

printf "%s\\n" "Making $PKGNAME.apk..."
aapt package -f \
       	--min-sdk-version 25 \
       	--target-sdk-version 30 \
       	-M AndroidManifest.xml \
       	-S res \
       	-A assets \
       	-F output/"$PKGNAME.apk" || _UNTP_


printf "\n%s\\n" "Adding classes.dex to $PKGNAME.apk..."
cd output || _UNTP_
aapt add -f "$PKGNAME.apk" classes.dex || { cd ..; _UNTP_; }

cp "$PKGNAME.apk" "$PKGNAME.0.apk"
printf  "Signing $PKGNAME.apk: "
sh ../signapk.sh sign --cert "../certificate.pem" --key "../key.pk8" --out "$PKGNAME.apk" "$PKGNAME.0.apk"
printf "%s\\n" "DONE"
mv "$PKGNAME.apk" ../"$PKGNAME.apk";

cd ..

CLEAN=1
_CLEANUP_
# buildusingdx.sh EOF
