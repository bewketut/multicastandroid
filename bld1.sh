#!/usr/bin/env sh
# Copyright 2019-2021 (c) all rights reserved
# by BuildAPKs https://buildapks.github.io/buildAPKs/
# Contributeur : https://github.com/HemanthJabalpuri
# See LICENSE for details https://buildapks.github.io/docsBuildAPKs/
#####################################################################
set -e
[ -z "${RDR:-}" ] && RDR="$HOME/buildAPKs"
[ "$PWD" = "${PREFIX%/*}" ] || [ "$PWD" = "$PREFIX" ] || [ "$PWD" = "$HOME" ] || [ "$PWD" = "$RDR" ] && { printf "Signal 224 generated in %s;  Command '${0##*/}' cannot be run in directory %s; %s exiting...\\n" "$PWD" "$PWD" "${0##*/} build.one.bash" ; exit 224 ; }

for CMD in aapt apksigner d8 ecj
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
   	--min-sdk-version 25 \
       	--target-sdk-version 30 \
    	-M "AndroidManifest.xml" \
       	-J "gen" \
       	-S "res" || _UNTP_
printf "%s\\n\\n" "aapt: done"
printf "%s\\n" "ecj: begun..."
for JAVAFILE in $(find . -type f -name "*.java")
do
       	JAVAFILES="$JAVAFILES $JAVAFILE"
done
JARFILEHOME=/sdcard/m4power6/mkasftp/
ecj -d ./obj -sourcepath .  $JAVAFILES     -cp "$JARFILEHOME"/android.jar:"$JARFILEHOME"/androidx.jar:"$JARFILEHOME"/lambda.jar|| _UNTP_

printf "%s\\n\\n" "ecj: done"

printf "%s\\n" "d8: started..."
for CLASSFILE in $(find obj -type f -name "*.class")
do
       	CLASSFILES="$CLASSFILES $CLASSFILE"
done


d8  --lib "$JARFILEHOME"/android.jar   --release --output  output/ $CLASSFILES --min-api 25 || _UNTP_
printf "%s\\n\\n" "d8: done"


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
#"$RDR"/scripts/bash/shlibs/#buildAPKs/copy.apk.bash
#cp "$PKGNAME.apk" ../"$PKGNAME.0.apk"
printf  "Signing $PKGNAME.apk: "
apksigner sign --min-sdk-version 25 --ks-key-alias BewketuTadilo --ks ~/bewketut.keystore "$PKGNAME.apk" < ~/keykey.txt;
printf "DONE\n";
printf "%s" "Verifying $PKGNAME.apk: "
apksigner verify --min-sdk-version 25 --verbose "$PKGNAME.apk" || { cd ..; _UNTP_; }
printf "%s\\n" "DONE"
mv "$PKGNAME.apk" ../"$PKGNAME.apk";

cd ..

CLEAN=1
_CLEANUP_
# build.sh EOF
