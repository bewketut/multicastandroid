/********
*****last date:24 June,21 June,7 May,March 2022, February 2021
**** copyright owner(author): Bewketu Tadilo
**** license: BSD (put copyright ***holder name (i.e. Bewketu Tadilo and signature ~bts) on  this original code or derivative  and binaries to show the copyright embedded in it on further) *****/
#include <stdio.h> 
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
//#include<sys/stat.h>
//#include<sys/uio.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/mman.h>
//#define FILE_MODE (S_IRUSR |S_IWUSR |S_IRGRP |S_IROTH)
#define BUF_SIZ  8192    //4096
#define MCASTBUF_SIZ (BUF_SIZ+3) 
#define MCASTP 5010 
#define NMUTEXFILES  256
#define DATASNG 0
#define DATARPT 1
#define DATAPIPE 2

//extern char *base256(int num,char *str);
//extern int tobase10(char *str);
extern char *mycpy(char *str1, char *str2, int len);
extern char *mycpy3(char *str1, char *str2, char *str3,int len);
//extern int openmsock( struct sockaddr_in mcast);
//extern ssize_t writen(int fd,const void *ptr, size_t n);
extern off_t readnf(FILE *fd, void *ptr, off_t f, size_t n);
extern void *mmapf(int fd, void *ptr, off_t f, size_t n);
extern int fgetcn(FILE *f, char *buf,off_t off, int len);
extern int indexof0(char *str,int len);
//extern ssize_t wrtrdn(int fd, void *ptr, size_t n, ssize_t *fn(int,  void *, size_t));
extern ssize_t writen(FILE *fd, const void *ptr, size_t n);
extern ssize_t readn(FILE *fd, void *ptr, size_t n);
extern ssize_t wrtrdn(FILE *fd,const void *ptr, size_t n, size_t fn(const void *, size_t,size_t, FILE *));

/* bug: note for future coders (stdio printf library bug), printf can only be used with specifiers at the socket receiver. e.g as printf("%d%s",6,"string") and not as printf("%dstring",6).

struct srcmutexfiles {
		unsigned char *fhash;
		FILE *fname;
}; typedef struct srcmutexfiles mcastsrcfile;

This file exclusion struc is not removed...b/c I deal/mostly dealt with mutual exclusions in sockets of multicast. if one gets this main point  in multicast, then they can deal with multicast sockets further. so, here a buffer of BUF_SIZ (4096 or 8192- observe the granulity while supporting all unix systems with d/t  memory PAGE_SIZE..8192 being to add support to Solaris OS.) has added two more mutual exclusion bytes at the end of on every BUF_SIZed packet to be sent(technically one byte maybe suffice) and so the array is BUF_SIZ+2 (or as i call it and should be called MCASTBUF_SIZ) data[MCASTBUF_SIZ-2]=mutual exclusion byte 1
data[MCASTBUF_SIZ-1]=mutual exclusion byte 2
both to be checked by the receiver to do operations on the data until BUF_SIZ and repeat the process to the end of the full data.
This is a long note...just patterns...on days i use English...i suffer the consequence (it is like some spirit that thinks i am an English speaker doesn't want to stop extorting me.) but to Quraan project, on days i read and recite the Quraan and Arabic, I get to eat good meal at places or get to wedding and other cermonies where i get treated well. so to me English in a way has to end...this is (this note) supposed to be at my costs...everything one English word is added, I get to lose or even worse get jailed.
white ppl in the south hemi...saying they are of English origin...one has to believe they have be jinns...ppl saying there "they are going to Antartica for trip as if they know s.th"...d/t dimensional being trying to turn russia as south of the earth's hemisphere...in my sphere, ppl of the earth dying/or hiding from my existence space...and these English origin claiming jinns saying we exist...they trying to keep talking in English.paradox!they are really poor as the joke Oliver Twist..
**************************
**************************
--now able to send directories (folders) by the  using of the *tar* shell command....
**************************
*/
#define PROGLOCALE 0
#define PROGOPTSIZ 20
#define tointeger(x) (x>='0' && x <='9')? x-'0': (x>='A' && x< 'a' )? tolower(x)-7-'0': (x>'Z' && x <= 'z')? toupper(x)-7-'0':(x<'0')? x+'0':x
//0-en 1-amharic
const char *opti[PROGOPTSIZ]={"PROGOPTLocale:0",
"PROGOPTInput:0"};
char copr[300];
char *progopts[10][2]={{"%s : given address '%s'is not multicast\n",""},{ "Your channel is %d from ur username and a folder name channel%d or channel4all in this directory be with read/write permission 4file_sharing. You can be viewed at udp://127.0.0.1:%d with a media player.\n",""},
{"%s -c command or -f(v) files(-f write files on your channel%d folder -v streaming) -m[n] mcastaddr[or n-number] (Write mode)\n%s -m[n] mcastaddr[or n] (default using -227.226.225.224)(Receive mode)\n",""},{
"Connect first via wifi-direct or hotspot with the other devices. run ifconfig.\n",""},{"Connect first/others to this devicevia wifi-Direct or this(?) Wifi hotspot.The device's ip is:%s for this session. Restart this program if this error shows.\n",""},{"Waiting receiver to enter fresh.",""},{"Great!! multicasting receiver that sends is found.",""},{"Unable to send, do group exist\n",""},{"Unable to open file for reading (read permission). is the folder location correct?",""},{copr,""},{"Receive(R)/Send command(s)/Receivefor now(r/1-9/a-10p-28/)/Send file(x/v-stream)/quit(q)?\n(R/s/r[1-9a-p]/x[v]/q)",""},{"Write a filename/s(regex accepted):",""},{"Cannot join Multicast Group. Waiting in unicast. is this %sself is connection server host device-switch %s.(?)\n",""},{"opening file %s for writing %d\n",""},
{"The file %s is being streamed on udp://127.0.0.1:%d\n",""},{"File can't be opened- ro folder. The file %s is being streamed on udp://127.0.0.1:%d\n",""},{"Finished writing and just closed file ",""},{"Finished streaming %s%d on udp://127.0.0.1:%d\n",""},{"file can't be opened- ro folder/or is not being streamed\n",""}};

int main(int argc, char **argv){
int optindex=opti[0][14]-'0';
char *argstr= argv[0];

if(strrchr(argv[0],'/'))argstr=strrchr(argv[0],'/')+1;
if(strrchr(argv[0],'.'))argstr=strrchr(argv[0],'/');
strcat(strcat(strcat(strcat(strcpy(copr,"Copyright ©Bewketu Tadilo(bewketu@yandex.com)2021-22\nPrepared to receive commands and file transfers!\n Now run "),argstr)," -f filename/s or "),argstr)," -c shell command\t on another terminal or computer on the network.\n waiting...");

//printf("'0':%d,'a':%d,'A':%d\n",tointeger('0'),tointeger('a'),tointeger('A'));
struct sockaddr_in src,temp[NMUTEXFILES],mcast,mcast2,tmp2,src2;// *listadr;
struct in_addr mcastaddr;
off_t i;
int so[NMUTEXFILES][NMUTEXFILES],sc,sock,sock2=-1,n,sock3=-1;
unsigned int ttl=1, d, k, x1; socklen_t j, mlen;  
char message[MCASTBUF_SIZ];
unsigned char c=0,cmflag=0;
FILE *fp;struct ip_mreq imr;
// off_t filesizes[NMUTEXFILES],curroffs[NMUTEXFILES];
//char str[20],*str2; 
//str2=base256(65489,str);
//printf("%d\n,", tobase10(str2));

char *inetadr= (char *) malloc(sizeof(char )*INET_ADDRSTRLEN);
strcpy(inetadr,"227.226.225.");
int sendflag=0;

for(i=1; i<argc; i++) {
if(!strcmp(argv[i],"-m")){ inetadr= argv[i+1];cmflag=1; break;}
if(!strcmp(argv[i],"-n")|| !strcmp(argv[i],"-mn")){ 
  strcat(inetadr, argv[i+1]); 
  argv[i]="-m"; c=1; cmflag=1;
  break;}
  }
if(!c) strcat(inetadr,"224");

mcastaddr.s_addr=inet_addr(inetadr);
mcast2.sin_family=mcast.sin_family=AF_INET;
mcast2.sin_addr.s_addr=mcast.sin_addr.s_addr=inet_addr(inetadr);
mcast2.sin_port=mcast.sin_port=htons(MCASTP);
//struct hostent *mcastad=gethostbyname(argv[argc-1]);
//memcpy((char *) &mcastaddr.s_addr, mcastad->h_addr_list[0],mcastad->h_length); 
//char *co=strstr(argv[1],"-c");
//printf(co);

  if(!IN_MULTICAST(ntohl(mcastaddr.s_addr))) {
   printf("%s : given address '%s' is not multicast\n",argv[0],
	   inet_ntoa(mcastaddr));
    exit(1);
  }
  
char *fcomp= (char *)malloc(sizeof(char )*200);
int fcompflag=0; unsigned char srcflag=DATASNG;

uid_t user;
user=getuid();
struct passwd *user_p=getpwuid(user); 
char *host= (char *)malloc(sizeof(char)*245);
gethostname(host,255);

char *useraddr= strcat(strcat(user_p->pw_name,"@"),host);
unsigned char fileround_userchannel=useraddr[0] + useraddr[1]-useraddr[2]+ useraddr[(strlen(useraddr)/2)] - useraddr[(strlen(useraddr)/3)] +
useraddr[(strlen(useraddr)/4)] - useraddr[(strlen(useraddr)/5)]+ useraddr[3*(strlen(useraddr)/4)] - useraddr[4*(strlen(useraddr)/5)] ;
useraddr=strcat(useraddr,"~");
unsigned char userchannel= fileround_userchannel%NMUTEXFILES;
int channelname=0;channelname= ((userchannel-'0')> 0)? userchannel-'0': userchannel;
if(argc!=1 && argc < 3 ){
printf("Your channel is %d from ur username and a folder name channel%d or channel4all in this directory be with read/write permission 4file_sharing. You can be viewed at udp://127.0.0.1:%d with a media player.\n",channelname,channelname,MCASTP+channelname);
printf("%s -c command or -f(v) files(-f write files on your channel%d folder -v streaming) -m[n] mcastaddr[or n-number] (Write mode)\n%s -m[n] mcastaddr[or n] (default using -227.226.225.224)(Receive mode)\n",argv[0], channelname,argv[0]);

exit(0);
}
   char *addr2= (char *)malloc(sizeof(char )*(5+INET_ADDRSTRLEN)),*peern=(char *)malloc(sizeof(char )*(INET_ADDRSTRLEN +4)),*addr=NULL,*peern1=NULL;
FILE    *psfp= popen("ip route show | tail -n 1 | grep -o src.*","r"); 
//addr=strcpy(addr+4,"127.0.0.1");
if(psfp && fgets(addr2,INET_ADDRSTRLEN+5,psfp)!=NULL) pclose(psfp);
if (addr2[4]< '0' || addr2[4]>'9'){fprintf(stderr,"%s\n" ,"Atleast one of the file/s _receiver_/s shoud be _wifi hotspot_. Others can connect to _that receiver_ and can send and receive files. Connect first via wifi-direct or hotspot with the other devices. run ifconfig."); exit(0);}
/*
if(addr[4]!='1'){
psfp= popen("ip route show | grep -o src.*","r"); 
if(psfp && fgets(addr,INET_ADDRSTRLEN+5,psfp)!=NULL) pclose(psfp);
}
*/
addr=addr2+4;
strchr(addr,'\n')[0]='\0';
strchr(addr,' ')[0]='\0';

   /*psfp= popen("ip route show | grep -o 192.1.*","r");
if(psfp && fgets(peern,INET_ADDRSTRLEN+1,psfp)!=NULL) pclose(psfp);
if(!*peern || peern[0]!='1'){*/
psfp= popen("ip route show | tail -n 1","r");
if(psfp && fgets(peern,INET_ADDRSTRLEN+1,psfp)!=NULL) pclose(psfp);
if((peern1=strchr(peern,'/'))){
peern1[0]='\0';
strrchr(peern,'.')[1]='1';
}

char switchflag=0;
if(!strcmp(addr,peern) && !strcmp(strrchr(addr,'.')+1,"1")){
	switchflag=1;
	}
//char peerf=0; 

if(switchflag){
peern[0]=peern[1]=-1;
	char pscmd[57];  
	strcpy(pscmd,"ip neigh show | grep -o ");
	strncat(pscmd,addr,strlen(addr)/3); strcat(pscmd,"* | grep -v FAILED |tail -n 1");
//psfp= popen("ip neigh show | grep -o 192.* | grep -v FAILED | tail -1","r");
psfp= popen(pscmd,"r");
 fgets(peern,INET_ADDRSTRLEN,psfp);
if((peern1=strchr(peern,' ')))
 peern1[0]='\0';
 pclose(psfp);
if(peern[1]<'0' || peern[1]>'9' ){ fprintf(stderr,"Connect first/others to this devicevia wifi-Direct or this(?) Wifi hotspot.The device's ip is:%s for this session. Restart this program if this error shows.\n",addr); strncpy(peern,addr,INET_ADDRSTRLEN);}
}
src2.sin_family=tmp2.sin_family=src.sin_family=AF_INET;//
src2.sin_port=tmp2.sin_port=src.sin_port=htons(MCASTP);
char *tarext=(char *)malloc(sizeof(char )*6); strcpy(tarext,".tar0") ; 

src.sin_addr.s_addr=inet_addr(peern);

if(argc>2 && strncmp(argv[1],"-m",2)){
sendlabel:

 if((sock=socket(AF_INET, SOCK_DGRAM,0))<0) exit(0);
src2.sin_addr.s_addr=(switchflag)?inet_addr(addr):htonl(INADDR_ANY);

bind(sock, (struct sockaddr *) &src2, sizeof(src2));


setsockopt(sock,IPPROTO_IP,IP_MULTICAST_TTL, &ttl,sizeof(ttl));
message[MCASTBUF_SIZ-2]=userchannel;
message[MCASTBUF_SIZ-3]=DATARPT;
if(!switchflag){
// IP_DEFAULT_MULTICAST_TTL
setsockopt(sock,IPPROTO_IP,IP_MULTICAST_LOOP, &ttl,sizeof(ttl));}
//sc= sendto(sock,"test", 5, 0, (struct sockaddr *) &mcast, sizeof(mcast));
//printf("sc=%d\n",sc);
//if(sc==-1){ fprintf(stderr,"Close if the receiving is on...send or receive. Not both\n");
//exit(1);}
else if(strcmp(argv[1],"-c")){

strcpy(message,"XOFMCAST");
d=0,sc=0;
while((sc=sendto(sock,message+d,MCASTBUF_SIZ-d,0, (struct sockaddr *) &mcast, sizeof(mcast)))>0){
//if(sc<1) 
	d+=sc;
if(d>=8) break;
}
mlen=sizeof(src);
printf("%s\n","Waiting receiver to enter fresh.");

while(srcflag!=DATAPIPE){
recvfrom(sock, message,8, 0, (struct sockaddr *) &src, &mlen);
//if(i!=-1) break;
        if(!strncmp(message,"XOFREADY",8)){
     //   getpeername(sock, (struct sockaddr *)&src,&mlen);
printf("%s\n","Great!! multicasting receiver that sends is found.");

mcast=src; srcflag=DATAPIPE; 
}
}
//needed b/c router can't write data fast to mcast...at the receiver pipe to mcast.
message[MCASTBUF_SIZ-3]=DATAPIPE;
//src2.sin_addr.s_addr=htonl(INADDR_ANY);

//bind(sock, (struct sockaddr *) &src2,sizeof(src2));
d=0,sc=0;
while((sc=sendto(sock,message,MCASTBUF_SIZ,0, (struct sockaddr *) &src, sizeof(src)))>0){
//if(sc<1) 
	d+=sc;
if(d>=MCASTBUF_SIZ) break;
}
if(sc==-1) printf("Unable to send, to open pipe\n");message[MCASTBUF_SIZ-3]=DATARPT;
 
}
tarext[4]=channelname;
if(!strcmp(argv[1],"-c")){
char *command=message;
strcpy(command,argv[1]); 
strcpy(command+2,useraddr);
command= strcat(strcat(command,argv[2])," "); 
for(d=3;d<argc && strncmp(argv[d],"-m",2); d++) 
command= strcat(strcat(command,argv[d])," "); 
//if(srcflag)
//  sc= sendto(sock,command, 401, 0, (struct sockaddr *) &tmp2, sizeof(src));
//command[MCASTBUF_SIZ-3]=DATARPT; 
d=0,sc=0;
while((sc=sendto(sock,command,MCASTBUF_SIZ,0, (struct sockaddr *) &mcast, sizeof(mcast)))>0){
//if(sc<1) 
	d+=sc;
if(d>=MCASTBUF_SIZ) break;
}
if(sc==-1) printf("Unable to send, do group exist\n");
 }
if(!strcmp(argv[1],"-f")|| !strcmp(argv[1],"-v") || 
 !strcmp(argv[1],"-cf")){
int nf= (BUF_SIZ-10)/300;
//int nfiles=(argc-2)-cmflag*2; 
//decreasing the cmdline  '-m mcastaddr' from //the arguement list
int nfiles=(cmflag)?(argc-4) : (argc-2);size_t size=0,ntimes=0;
int rnfiles=nfiles, z=0, len1=0,rem=0,fdin;
 char *remn=message,*filename= message,*buffer =message, *strf2=NULL,rem1,rem2;
x1=2;

char filebuffer[BUF_SIZ];
char mmbuffer[BUF_SIZ];
FILE *fdin1;DIR *tempd=NULL;
unsigned char fileround,filehash,filehash3;
strcpy(message,"FOList");
for(j=2;j<argc && strncmp(argv[j],"-m",2); j++) {

 argv[2]=argv[j];
if(x1==j && nfiles>0){

if(nfiles<nf){
 message[7]=nfiles%256; 
message[8]=(nfiles)/256; nfiles=0;
}
else
{message[7]=nf%256;  
message[8]=nf/256;nfiles-=nf;}

 z=0;

while( z< nf && x1 < argc-cmflag*2)
{ 
len1=(!sendflag && strlen(argv[x1])< 300)?strlen(argv[x1]) : 300;
mycpy(message+10+z*300,argv[x1],len1);
if(len1< 300)
printf("file %d:%s size: unchecked  will be sent\n",x1-1,argv[x1]); 
else 
printf("file %d:%s size: %sKB will be sent\n",x1-1,argv[x1],argv[x1]+290);
x1++; z++;
}

n=0; d=0;
while((n=sendto(sock,message+d,MCASTBUF_SIZ-d, 0, (struct sockaddr *) &mcast, sizeof(mcast)))>0){
//if(n<1) continue;
 d+=n; if(d>=MCASTBUF_SIZ) break; }

}
 

tempd=opendir(argv[2]);
if(tempd) {
	closedir(tempd);
strf2=  strrchr(argv[2],'/');
strcpy(fcomp,"tar cvf "); //8 characters 6-readable(tarcvf)2-spaces.there4- fcomp+8 after strcat
if(strf2)
strcat(fcomp,strf2+1);
else
 strcat(fcomp,argv[2]); 
strcat(fcomp,tarext);
system(strcat(strcat(fcomp," "),argv[2])); 
usleep(1000);
strchr(fcomp+8,'.')[0]='\0';fcompflag=1;
strcat(fcomp,tarext);
fdin1=fopen(fcomp+8,"rb");//O_RDONLY); 
argv[2]=fcomp+8;
}
else fdin1=fopen(argv[2],"rb");//O_RDONLY);
//usleep(1000);
//printf("fcomp:%s",fcomp+8);

//create tar cvfz strcat(argv[2],".tgz") 

if(!fdin1) {printf("%s\n","Unable to open file for reading (read permission). is the folder location correct?");
            exit(1);}
if(!strcmp(argv[1],"-cf") && (fp=fopen(argv[2],"r"))){
     strcpy(message,"-cf"); strcpy(message+3,useraddr);
   int strx= strlen(useraddr)+3;
//message[MCASTBUF_SIZ-3]=DATARPT; 
   while(fgets(message+strx,400,fp))
       while((n=sendto(sock,message,MCASTBUF_SIZ, 0, (struct sockaddr *) &mcast, sizeof(mcast)))!=0) if(n!=-1)break;  
        fclose(fp);
}
else{
fileround=argv[2][0] + argv[2][strlen(argv[2])-(strlen(argv[2])/2)] - argv[2][strlen(argv[2])-(strlen(argv[2])/3)];
 filehash3= fileround%NMUTEXFILES;  
filehash= filehash3;


if(!strcmp(argv[1],"-f") || !strcmp(argv[1],"-v")) { filename[1]='S'; filename[2]='0'; message[3]='F';filename[4]='!';if(!strcmp(argv[1],"-v")) message[3]='f';}
filename[0]=filehash; message[5]=userchannel; filename[6]='\0';
//if(j==2) message[6]=argc-2;
//else message[6]='0';
if(strrchr(argv[2],'/')) strcat(filename,strrchr(argv[2],'/')+1);
else
strcat(filename,argv[2]);//initialization 

//struct stat statbuf;
//fstat(fdin,&statbuf);
//long size=statbuf.st_size; 
fdin =fileno(fdin1);
fseek(fdin1,0L,SEEK_END);
size=ftell(fdin1);
fseek(fdin1,0L,SEEK_SET);
 ntimes= (size/BUF_SIZ);

message[MCASTBUF_SIZ-1]=filehash3 ; 
n=0; d=0;
while((n=sendto(sock,filename+d,MCASTBUF_SIZ-d, 0, (struct sockaddr *) &mcast, sizeof(mcast)))>0){
//if(n<1) continue;
 d+=n; if(d>=MCASTBUF_SIZ) break; }
 rem = size%BUF_SIZ;
 rem1 =rem/256; 
rem2=rem%256;

//off_t pa_offset = 0 & ~(sysconf(_SC_PAGE_SIZE)-1);
//off_t offset;
buffer[MCASTBUF_SIZ-3]=DATARPT;
for(i=0,k=0;k< ntimes;k++,i+=BUF_SIZ){
/*note: offset has to be multi.of 2^12*/
  fgetcn(fdin1,filebuffer,i,BUF_SIZ);
mmapf(fdin,mmbuffer,i,BUF_SIZ);
 readnf(fdin1,buffer,i,BUF_SIZ);
mycpy3(buffer,mmbuffer,filebuffer,BUF_SIZ);

/*
buffer[MCASTBUF_SIZ-3]=srcflag;
n=0; d=0;
while((n=sendto(sock,buffer+d,MCASTBUF_SIZ-d, 0, (struct sockaddr *) &mcast, sizeof(mcast)))>-2){if(n<1) continue; d+=n; if(d>BUF_SIZ+2) break; }*/
 usleep(1);
n=0; d=0;
while((n=sendto(sock,buffer+d,MCASTBUF_SIZ-d, 0, (struct sockaddr *) &mcast, sizeof(mcast)))>0){
//if(n<1) continue;
 d+=n; if(d>=MCASTBUF_SIZ) break; }
usleep(1);
}

 message[4]= rem1; message[5]=rem2;
message[0]=filehash3; message[1]='E'; remn[2]='O'; message[3]='L'; message[6]=userchannel;
message[7]='\0'; 
//buffer[MCASTBUF_SIZ-3]=DATARPT;
n=0; d=0;
while((n=sendto(sock,message+d,MCASTBUF_SIZ-d, 0, (struct sockaddr *) &mcast, sizeof(mcast)))>0){
// if(n<1) continue;
 d+=n;  if(d>=MCASTBUF_SIZ) break; }

 //  pa_offset=20;
 //  printf("i፡%d po፡%d",i, 
//srs=mmap(0,rem,PROT_READ,MAP_SHARED,fdin,i);
fgetcn(fdin1,filebuffer,i,rem);		
mmapf(fdin,mmbuffer,i,rem);
readnf(fdin1,buffer,i,rem);
	mycpy3(buffer,mmbuffer,filebuffer,rem);

 /*
buffer[MCASTBUF_SIZ-3]=srcflag;
n=0; d=0;
while((n=sendto(sock,buffer+d,MCASTBUF_SIZ-d, 0, (struct sockaddr *) &mcast, sizeof(mcast)))>0){
// if(n<1) continue;
 d+=n;  if(d>=MCASTBUF_SIZ) break; }
//munmap(srs,size);
*/
buffer[MCASTBUF_SIZ-3]=(srcflag==DATAPIPE && j-1==rnfiles)?DATASNG:DATARPT;
n=0; d=0;
while((n=sendto(sock,buffer+d,MCASTBUF_SIZ-d, 0, (struct sockaddr *) &mcast, sizeof(mcast)))>0){
// if(n<1) continue;
 d+=n;  if(d>=MCASTBUF_SIZ) break; }
	 
//close(fdin);	 
fclose(fdin1);
 if(fcompflag){strncpy(fcomp,"rm -f ",6); system(fcomp);}
}
}

 }

if(sendflag)
	goto receivelabel;

  }
else {

//fprintf(stdout,"%s%s\n",copr);
fprintf(stdout,"%s\n",copr);
FILE *fn[NMUTEXFILES][NMUTEXFILES]; 
unsigned char findexmn=0,channel=0, prev=-1, fflag=0;//fflag1=0;fflag,k=0,*cm;
 char *chead, *filen,y='x',x,*cwdir= (char *) malloc(sizeof(char )*370);/*,*buff2=(char *)malloc(sizeof(char *)*6*BUF_SIZ)*/
char **filen1 = (char **)malloc(sizeof(char *)*500);
char *file_ats, *warning=(char *)malloc(sizeof(char )*285); strcpy(warning,"EEOf");
int sockp[2],recvonly='0';
char channelfolder[330]; strcpy(channelfolder,"channel"); c=0;
unsigned int nextlen[NMUTEXFILES][NMUTEXFILES],count=0, cnt=0, files2write=0,nlist=0; 
for(i=0;i<NMUTEXFILES;i++){
temp[i].sin_addr.s_addr=0; 
so[i][0]=0;
 for(d=0; d< NMUTEXFILES; d++){
nextlen[i][d]=BUF_SIZ; fn[i][d]=NULL;
 //so[i][j]=0;
}
}
filen= (char *)malloc(sizeof(char)*300);
strcpy(cwdir,"cd "); FILE *html=NULL,*html1=NULL; 
char archives[8][270]; for(d=0; d <8; d++) strcpy(archives[d],"tar xvf ");
html= fopen("index.htm","w");
if(html){
fprintf(html,"<!doctype html>\
<html>\
    <head>\
        <meta charset='utf-8'>\
        <meta http-equiv='x-ua-compatible' content='ie=edge'>\
        <title></title>\
        <meta name='description' content='www'>\
<meta name='viewport' content='width=device-width, initial-scale=1.0'><script>\
function vidcload(){window.location.reload(true);}</script></head>");
fclose(html);} char id[2]; id[0]='0'; id[1]='\0';
char localport[8];
int channelport;
char vid[540]; 
psfp=popen("cd ~/ && pwd","r");
fgets(cwdir+4,350,psfp);
pclose(psfp);
//strcpy(cwdir,getenv(HOME));
imr.imr_interface.s_addr=(switchflag)?inet_addr(addr):htonl(INADDR_ANY);
//if(switchflag){ //if _server x.x.x.1

 imr.imr_multiaddr.s_addr=mcastaddr.s_addr;                   
src.sin_addr.s_addr=inet_addr(peern);

receivelabel:

if(recvonly!=-1 && recvonly =='0' ){
if( y!='R'){
fprintf(stdout,"%s","Receive(R)/Send command(s)/Receivefor now(r/1-9/a-10p-28/)/Send file(x/v-stream)/quit(q)?\n(R/s/r[1-9a-p]/x[v]/q)");
while((x= getchar())!='\n')if(x!='r') y= toupper(x);else y=x; fprintf(stdout,"%s","\n");
if(y>='0' && y<='P'){if(y<='9') recvonly=y+1; else recvonly=  y-6;} 
  if(recvonly>'0' && recvonly<=('W')){ recvonly--;}
if(y=='R')recvonly=-1;
 if (y=='S' || y=='X' || y=='V'){
if(y=='X'|| y=='V'){
system("ls");
printf("%s","__(regex help note(using *): 1.files starting 'fil' enter: fil* result: all files like file1.txt filanything.pdf, filemusic.mp4 will be sent2. files ending with 'mp4' enter: *mp4 or *.mp4 result: vidclip.mp4,  filmanything.m4, anything.mp4 will be sent.3. filepart names in between them 'fil'. enter : *fil* and any and all files and folders containing the characters 'fil' in their name get send.)__\nWrite a filename/s(regex accepted):");
}
else if(y=='S') printf("$:~");
 fgets(filen,50,stdin);
strrchr(filen,'\n')[0]='\0'; 
if(y=='X'|| y=='V') {
if(y=='V') argv[1]="-v";
else argv[1]="-f"; strcpy(fcomp,"ls -ds "); i=0;
psfp=popen(strcat(fcomp,filen),"r");
//printf(fcomp);
if(!filen1[i])
filen1[i]=(char *)malloc(sizeof(char)*300);
while(fscanf(psfp,"%s%s",filen1[i]+290,filen1[i])!=EOF){
argv[i+2]=filen1[i];
//printf("%s\n",filen1[i]);
i++;
if(!filen1[i]) 
filen1[i]=(char *)malloc(sizeof(char)*300);
}
pclose(psfp);
argc=i+2;
}
else if(y=='S'){
 argv[1]="-c"; system(filen);  if(strstr(filen,"cd ") ){ 
if(strstr(filen,"cd ~")){ chdir(cwdir+4);if(strstr(filen,"cd ~/")) strcpy(fcomp,strstr(filen,"cd ~/")+5);  if(strchr(fcomp,' '))
strchr(fcomp,' ')[0]='\0'; if(fcomp) chdir(fcomp);
 }//fchdir(fd); }
else{
strcpy(fcomp,strstr(filen,"cd ")+3);  if(strchr(fcomp,' '))
strchr(fcomp,' ')[0]='\0'; chdir(fcomp);}
}  
argv[2]=filen; argc=3;
 }

sendflag=1;
goto sendlabel;
}}else y='l';
if(y=='Q'|| y=='T') return 0;

}
if(recvonly>'0' && recvonly!=-1)
recvonly--; 
if(count==1) count--;
if(!(cnt%25)){
               if(!cnt){
                  tmp2.sin_addr.s_addr=htonl(INADDR_ANY); //  
		if((sock2=socket(AF_INET, SOCK_DGRAM,0))<0) exit(0);

        //     imr.imr_multiaddr.s_addr=mcastaddr.s_addr;
		bind(sock2, (struct sockaddr *) &tmp2, sizeof(tmp2));
		  }
               
i=setsockopt(sock2, IPPROTO_IP, IP_ADD_MEMBERSHIP,  &imr, sizeof(struct ip_mreq));
if(i < 0) {printf("Cannot join Multicast Group. Waiting in unicast. is this %sself is connection server host device-switch %s.(?)\n",useraddr,addr);
}

else if(!switchflag) { //if _no_server x.x.x.1
n=0; d=0;
strcpy(message,"XOFREADY");
while((n=sendto(sock2,message+d,9-d, 0, (struct sockaddr *) &src, sizeof(src)))>0){
// if(n<1) continue;
 d+=n;  if(d>=9) break; }
 //if((sock3=socket(AF_INET, SOCK_DGRAM,0))<0) exit(0);

//bind(sock3, (struct sockaddr *) &mcast, sizeof(mcast));		
//sockp[0]=sock2; //sockp[1]=sock3;
//pipe(sockp);
//socketpair(AF_UNIX,SOCK_STREAM,0,sockp);
//qflag= 1;
}
  
}  cnt++;
mlen=sizeof(tmp2);
 while(1){
if(!files2write && count==1) goto receivelabel;
 i=0;d=0;
while((i=recvfrom(sock2, message+d, MCASTBUF_SIZ-d, 0, (struct sockaddr *) &tmp2 , &mlen))> 0){
if(d<30 && !switchflag  && !strncmp(message,"XOFMCAST",8))
{
	n=0; k=0;
strcpy(message,"XOFREADY");
while((n=sendto(sock2,message+k,9-k, 0, (struct sockaddr *) &tmp2, sizeof(tmp2)))>0){
// if(n<1) continue;
 k+=n;  if(k>=9) break; }

break; continue;
 }
 d=+i;
  if(switchflag && i==9  && !strncmp(message+d-i,"XOFREADY",8)) d-=9;

	  if(d>=MCASTBUF_SIZ) break;
}
 //if(i<1 && d< MCASTBUF_SIZ) goto interruptedstate;
//fflag1=fflag;
fflag=message[MCASTBUF_SIZ-3];
if(fflag!=DATARPT){
			if(fflag==DATAPIPE){
		if(!sock3 && !switchflag){
				if((sock3=socket(AF_INET, SOCK_DGRAM,0))<0) exit(0);

bind(sock3, (struct sockaddr *) &mcast, sizeof(mcast));	
			sockp[0]=sock2;
//sock3=openmsock(mcast);
sockp[1]=sock3;
pipe(sockp); 
		}
		
}
else if(sock3){
close(sock3); sock3=0;
}
 /*
		if(fflag1==DATARPT){
memcpy(filebuffer, message, MCASTBUF_SIZ);
continue;}
else
if ( filebuffer[MCASTBUF_SIZ-2]==message[MCASTBUF_SIZ-2]){
memcpy(mess3,message,MCASTBUF_SIZ);
memcpy(message,filebuffer,MCASTBUF_SIZ);
}*/
}//  printf("fnp:%d,groupid:%d,fnindex:%d\n",fn[channel][findexmn],channel,findexmn);
 if(!strncmp(message+1,"S0F!",4)||!strncmp(message+1,"S0f!",4)){ 
channel= ((unsigned char)message[5])%NMUTEXFILES;
findexmn=((unsigned char)message[0])%NMUTEXFILES;
channelport= ((channel-'0') > 0)?channel-'0': channel;
 snprintf(channelfolder+7,4,"%d",channelport);
strcat(channelfolder,"/");
strcat(channelfolder,message+6);
if(fn[channel][findexmn]==NULL){
if(fopen(channelfolder,"r")){ 
if((file_ats=strrchr(channelfolder,'.'))){ file_ats[0]='\0';strcpy(filen,"_1.");strcat(filen,file_ats+1);  strcat(channelfolder,filen);}
else strcat(channelfolder,"1");
}
if(!strncmp(message+1,"S0f!",4)){
if(!(so[channel][0]) && (so[channel][0]=socket(AF_INET, SOCK_DGRAM,0))<0) exit(0);

if(!temp[channel].sin_addr.s_addr){
temp[channel].sin_family=AF_INET;
temp[channel].sin_addr.s_addr=inet_addr("127.0.0.1");
temp[channel].sin_port=htons(MCASTP+channelport);
bind(so[channel][0], (struct sockaddr *) &temp[channel], sizeof(temp[channel]));
//while((n=sendto(so[channel][0],"HTTP/0.9 200 Ok\
//Server: Music serv\
//Content-Type: video/mp4",BUF_SIZ, 0, (struct sockaddr *) &temp[channel], sizeof(temp[channel])))!=0) if(n!=-1) break;
}
}
else if (opendir(strrchr(channelfolder,'/')) && (fn[channel][findexmn]=fopen(channelfolder,"w")));
else if (opendir("channel4all/")){
char channel4all[120]; strcpy(channel4all,"channel4all/"); strcat(channel4all,message+6);
if(fopen(channel4all,"r")){ 
if((file_ats=strrchr(channel4all,'.'))){ file_ats[0]='\0';strcpy(filen,"_1.");strcat(filen,file_ats+1);  strcat(channel4all,filen);}
else strcat(channel4all,"1");
} 
fn[channel][findexmn]=fopen(channel4all,"w"); //O_WRONLY | O_CREAT |O_TRUNC);
}
//fprintf(stderr,"Please make this progam root folder read only. Create a folder named channel4all (or the filesharer's channelfolder) under it for right operations of file sharing and multicast streaming.This option is left for network managers use!!:$\n");

else {
if(fopen(message+6,"r")){ 
if((file_ats=strrchr(message+6,'.'))){ file_ats[0]='\0';strcpy(filen,"_1.");strcat(filen,file_ats+1);  strcat(message+6,filen);}
else strcat(message+6,"1");
}
fn[channel][findexmn]=fopen(message+6,"w"); //O_WRONLY | O_CREAT |O_TRUNC);
strrchr(channelfolder,'/')[1]='\0'; 
strcat(channelfolder,message+6);
} 
tarext[4]=channelport;
if(strstr(message+6,tarext)){ strcpy(archives[findexmn%8]+8,message+6);
strcat(strcat(archives[findexmn%8],"; rm -f "),message+6);
}
} 
if(fn[channel][findexmn])
fprintf(stdout,"%s%s%s%d%s","opening file ",channelfolder, " for writing",findexmn,"\n");
else if(so[channel][0])
 fprintf(stdout,"The file %s is being streamed on udp://127.0.0.1:%d\n",channelfolder,MCASTP+channelport);
else {

	if(!(so[channel][0]) && 
(so[channel][0]=socket(AF_INET, SOCK_DGRAM,0))<0) exit(0);

if(!temp[channel].sin_addr.s_addr){
temp[channel].sin_family=AF_INET;
temp[channel].sin_addr.s_addr=inet_addr("127.0.0.1");
temp[channel].sin_port=htons(MCASTP+channelport);
bind(so[channel][0], (struct sockaddr *) &temp[channel], sizeof(temp[channel]));	
 fprintf(stderr,"File can't be opened- ro folder. The file %s is being streamed on udp://127.0.0.1:%d\n",channelfolder,MCASTP+channelport);}
}

if(prev!=channel){
//if(files2write==0) 
//snprintf(localport,8, "%d",30100);
 snprintf(localport,8, "%d",MCASTP+channelport);
html1=fopen("index.htm","a");
if(html1){
strcpy(vid,"<video  style='margin-left:3%;' width='100' height='330' autoplay='' controls='' id='thevid");strcat(vid,id); strcat(vid,"'><source src='");
strcat(vid,"udp://127.0.0.1:");strcat(vid,localport);  
 strcat(vid,"'></video><button onclick='document.querySelector(\"#thevid");
strcat(vid,id); strcat(vid,"\").src=\"");
strcat(vid,"udp://127.0.0.1:");strcat(vid,localport);  strcat(vid,"\"'>Update now</button>"); 
fprintf(html1,"%s",vid);
fclose(html1);
id[0]++;
} }
files2write+=(!nlist)?1:0;

}
else if(!strncmp(message+1,"EOL",3)){
findexmn=((unsigned char)message[0])%NMUTEXFILES;
channel=((unsigned char)message[6])%NMUTEXFILES;
 nextlen[channel][findexmn]=((unsigned char)message[4])*256 + ((unsigned char)message[5]) ;

}
else if(!strncmp(message,"FOList",6)){

nlist=message[8]*256+message[7];
//printf("message 9:%d\n",message[10]);
for(d=0;d< nlist; d++)
printf("%s%d%s%s%s%s%s","file",d+1, ":",message+10+d*300, " of_size:" ,message+10+d*300+290,"KB will be downloaded\n");
files2write+=nlist;
//nlist=0;
}
else if(files2write){
prev=channel;
channel=((unsigned char) message[MCASTBUF_SIZ-2])%NMUTEXFILES;
findexmn=((unsigned char) message[MCASTBUF_SIZ-1])%NMUTEXFILES;
channelport= ((channel-'0') > 0)?channel-'0': channel;
 snprintf(channelfolder+7,4,"%d",channelport);
strcat(channelfolder,"/");
message[MCASTBUF_SIZ-2]=0;
message[MCASTBUF_SIZ-1]=0;
//msync(message,BUF_SIZ,MS_SYNC);
if(findexmn>0){
if(fn[channel][findexmn]) {
//fwrite(message,1,nextlen[channel][findexmn],fn[channel][findexmn]);
//if(nextlen[channel][findexmn]==BUF_SIZ)
//writen(fn[channel][findexmn],message,i);//
if(d>=BUF_SIZ) 
writen(fn[channel][findexmn],message, nextlen[channel][findexmn]);
else
writen(fn[channel][findexmn],message, d);
}
else  {
//if(k>0)
//buff2= (char *) realloc(buff2,sizeof(char*)*k*BUF_SIZ);
//if(k<6)
//memcpy(buff2+k*BUF_SIZ,message,BUF_SIZ);
//else k=0;
//printf("%s val:%d\n",buff2+k*BUF_SIZ,k);
//sendto(sock2,buff2,k*BUF_SIZ, 0, (struct sockaddr *) &temp[channel], sizeof(temp[channel]));
while((n=sendto(so[channel][0],message/*buff2+k*BUF_SIZ*/,BUF_SIZ, 0, (struct sockaddr *) &temp[channel], sizeof(temp[channel])))!=0) if(n!=-1) break;
usleep(400);
}
if(nextlen[channel][findexmn]!=BUF_SIZ){
if(fn[channel][findexmn]){
	fclose(fn[channel][findexmn]);
fn[channel][findexmn]=NULL;
if(archives[findexmn%8][8]){ system(archives[findexmn%8]); archives[findexmn%8][8]=0;}
fprintf(stdout,"%s %d%s","Finished writing and just closed file ",findexmn,"\n");
 } 
else if (so[channel][0]){
	
//so[channel][0]=0;
 fprintf(stdout,"Finished streaming %s%d on udp://127.0.0.1:%d\n",channelfolder,findexmn,MCASTP+channelport);
 }
else 
fprintf(stdout,"file can't be opened- ro folder/or is not being streamed\n");
nlist+= (nlist>0)?-1:0;
files2write--;
if(message[0]=='E')printf("%s\n",message+4);
count=1;
nextlen[channel][findexmn]=BUF_SIZ;
}
}
else if(!strncmp(message,"-c",2)){
chead= strchr(message,'~');
if(chead) {
chead[0]='\0';
if(!strncmp(message,"-cf",3))
printf("%s:-%s", message+3,chead+1);
else printf("%s:-%s\n", message+2,chead+1);
if(strchr(chead+1,'/')&& !strstr(chead+1,"//")){
sendto(sock2,strcat(strcat(warning,"Warning error: Access is limited to the program folder ('//' forbidden)_no_command_executed!!~from~"),useraddr),125, 0, (struct sockaddr *) &mcast, sizeof(mcast)); count=1;}
else {
if(strstr(chead+1,"cd ~")) {system(chead+1); chdir(cwdir+4);}
else if(strstr(chead+1,"cd ")) {system(chead+1); chdir(strstr(chead+1,"cd ")+3);}
else
system(chead+1);}count=1;
}
else printf("%s\n","format: -c usern@hostn~ commands ...(needs the token '~' after -c before the command or -c~commands)");
}

}
else if(!files2write && !strncmp(message,"-c",2)){
chead= strchr(message,'~');
if(chead){
chead[0]='\0';
if(!strncmp(message,"-cf",3))
printf("%s:~%s", message+3,chead+1);
else 
printf("%s:~%s\n", message+2,chead+1);
if(strchr(chead+1,'/')&& !strstr(chead+1,"//")){
sendto(sock2,strcat(strcat(strcat(warning,"Warning error: Access is limited to the program folder ('//' forbidden)_no_command_executed!!~from~"),useraddr),cwdir+4),150, 0, (struct sockaddr *) &mcast, sizeof(mcast));
 count=1;
}
else {
if(strstr(chead+1,"cd ~")) {system(chead+1); chdir(cwdir+4);}
else if(strstr(chead+1,"cd ")) {system(chead+1); chdir(strstr(chead+1,"cd ")+3);}
else
system(chead+1);count=1; }
}
else printf("%s\n","format: -c usern@hostn~ commands ...(the token '~'  after -c before the command or -c~commands)");
}
/*if(mess3[1]){
	memcpy(message,mess3,MCASTBUF_SIZ);
	mess3[1]=0;
}*/
 }
//return setsockopt(so,IPPRTO_IP, IP_DROP_MEMBERSHIP, &imr, sizeof(struct ip_mreq));
}
 
return 0;
}
/*int openmsock( struct sockaddr_in mcast){
	int sock3; 
	
//setsockopt(sock3,IPPROTO_IP,IP_MULTICAST_TTL, &ttl,sizeof(ttl));// IP_DEFAULT_MULTICAST_TTL
//sockp[0]=sock1; sockp[1]=sock3;
//pipe(sockp);
return sock3;
//socketpair(AF_UNIX,SOCK_STREAM,0,sockp);
}*/
 int indexof0(char *str, int len){
 	int i=0;
 	for(i=1; i< len; i++)
 	if(!str[i]) return i;
 	return 0;
 }
 off_t readnf(FILE *fd, void *ptr, off_t f, size_t n){	
 int pos=0, k=0;
 memset(ptr,0,n);
 do {
 		fseek(fd,f+pos,SEEK_SET);	
	readn(fd,ptr+pos,n-pos);
	k=indexof0(ptr+pos,n-pos);
	pos+=k;
 } while(k);
	return f+n;
  }
  /*
off_t readnf(FILE *fd, void *ptr, off_t f, size_t n){	
	int i;
	//nread
		for(i=0; i < 11;i++){
	fseek(fd,f,SEEK_SET);
		//fgetcn(fd,ptr,f,n);
	fread(ptr,1,n,fd);
	} 
	for(i=0; i < 10;i++){
	fseek(fd,f,SEEK_SET);
		//fgetcn(fd,ptr,f,n);
	readn(fd,ptr,n);
	} 
	//2*n/3 read
		for(i=0; i <9;i++){		
	fseek(fd,f+n/3,SEEK_SET);
//		fgetcn(fd,ptr+n/3,f+n/3,n-n/3);
	fread(ptr+n/3,1,n-n/3,fd);	
	}
	//n/2 read
		for(i=0; i < 8;i++){
	fseek(fd,f+n/2,SEEK_SET);
	//	fgetcn(fd,ptr+n/2,f+n/2,n-n/2);
	fread(ptr+n/2,1,n-n/2,fd);	
	}
	
	for(i=0; i <7;i++){	
	fseek(fd,f+2*n/3,SEEK_SET);
//	fgetcn(fd,ptr+2*n/3,f+2*n/3,n-2*n/3);
	fread(ptr+2*n/3,1,n-2*n/3,fd);		
	}
		for(i=0; i < 6;i++){
	fseek(fd,f+3*n/4,SEEK_SET);
//	fgetcn(fd,ptr+3*n/4,f+3*n/4,n-3*n/4);
	fread(ptr+3*n/4,1,n-3*n/4,fd);	
	}
	return f+n;
//	printf("from:%ld,n:%ld,seekcur:%ld\n", f,f+n ,lseek(fd,0L,SEEK_CUR));
}*/
int fgetcn(FILE *fdin, char *buf, off_t offset, int len){
	int i; int val,k;
	
	memset(buf,0,len);
	for(k=0;k<2;k++){
	fseek(fdin,offset,SEEK_SET);
	for(i=0;i< len; i++){
	val=getc(fdin);
	if(val==EOF)  break;
	if(ferror(fdin)) { 
	clearerr(fdin);	
    i--;continue;
	}
	if(k==0 )
	buf[i]=val;
	else if (val) buf[i]=val;
	  
		}
	
		}
		return i;
}
void *mmapf(int fd,void *ptr, off_t f,size_t n){
//	size_t farray=(f>0)?f-1:f;
int i;
void	*srs;
memset(ptr,0,n);
	lseek(fd,0L,SEEK_SET);
	for(i=0; i <3; i++){
srs=mmap(0,n,PROT_READ,MAP_SHARED,fd,f);		
mycpy(ptr,srs,n);
munmap(srs,n);
	}
return srs;
}
char *mycpy(char *str1, char *str2, int len)
{
int i=0;
for(i=0; i < len; i++){
	if((str1[i]!= str2[i]) && str2[i])
str1[i]= str2[i];
}
return str1;
}
char *mycpy3(char *frd, char *mmp,char *fgtc,int len){
	int i=0;
	for(i=0; i<len; i++)
	{ 
	frd[i]=(fgtc[i] && (fgtc[i]==frd[i] || fgtc[i]==mmp[i]))? fgtc[i] :((frd[i])? frd[i] : ((mmp[i])?mmp[i] : fgtc[i]));
	}
return frd;
}
int configwr(char *argv,char opt)
{
	char cm[270]; char fname[300];
int fd; FILE *fp; off_t size;
strcpy(cm,"which "); 
FILE *mkfps=popen(strcat(cm,argv),"r");
 if(mkfps){fgets(fname,300,mkfps);
pclose(mkfps);}
else return 0;
fd=open(fname,O_RDONLY);
size=lseek(fd,0L,SEEK_END);
lseek(fd,0L,SEEK_SET);
char *buf1=(char *)malloc(sizeof(char )*size),*buf2=(char *)malloc(sizeof(char )*size);
fp=fdopen(fd,"r");
fgetcn(fp,buf1,0,size);
readnf(fp,buf2,0,size);
mycpy(buf1,buf2,size);
mmapf(fd,buf1,0,size);
off_t i=strlen(buf1); char *temp=buf1,*temp2=NULL;
while(i<size){

temp2=strstr(temp,"PROGOPTLocale:");
if(temp2){ temp2[14]=opt; break;}

temp=buf1+i+1;
i+=strlen(temp);
}
close(fd); fclose(fp);
if(temp2 && opt!=temp2[14]){
fp=fopen(fname,"w");
writen(fp,buf1,size);
fclose(fp); return 1;
}
return 0;
}


/*ssize_t readn(FILE *fd, void *ptr, size_t n){
		size_t nleft; ssize_t nread;
	nleft=n; 
	while(nleft>0){
		if((nread=fread(ptr,1,nleft,fd))<0){ if(nleft==n) return -1;
		else break;}
		else if(nread==0) break;
	nleft-=nread;
	ptr+=nread;
	} return (n-nleft);
	}
*/
ssize_t readn(FILE *fd,void *ptr, size_t n){
 return  wrtrdn(fd,ptr,n,fread);
}
ssize_t writen(FILE *fd,const void *ptr, size_t n){
 return  wrtrdn(fd,ptr,n,fwrite);
}
ssize_t wrtrdn(FILE *fd, const void *ptr, size_t n, size_t fn( const void *,size_t, size_t, FILE *
)){
	size_t nleft; ssize_t nread;
	nleft=n; 
	while(nleft>0){
		if((nread=fn(ptr,1,nleft,fd))<0){ if(nleft==n) return -1;
		else break;}
		else if(nread==0) break;
	nleft-=nread;
	ptr+=nread;
	} return (n-nleft);
}
/*
char *base256(int num,char *str){
unsigned char rem;
int divn;
int len=strlen(str);printf("%d\n",strlen(str)); str[len--]='\0';
for(divn= num/256,rem=num%256,str[len--]=rem; divn > 256; divn=divn/256,rem=divn%256)
str[len--]=rem;
str[len--]=divn;
return str+len;
}
int tobase10(char *str){
int len= strlen(str);
int tot,i,j;
tot=(unsigned char) str[len-1];
printf("%s\n",str);
int base=100;
int mult=256;
for(i=0, j=len-2; j>-1 && i <len-2; i++,j--){
tot+=((unsigned char) str[j])*mult;
mult=mult*base;
base=base*100;
printf("total:%d\n",tot);
}

return tot;
}


char *int2str(int k)
{ int i;
  char str[10];
      for(i=1; i<k; i*=10);

       k%i 
}


static struct option long_opt[] = {
    {"cmd", 1, 0, 'c'},
    {"file", 1, 0, 'f'},
    {"maddr", 1, 0, 'm'},
    {NULL, 0, NULL, 0}
};
static char *short_opt = "c:f:m:";
char *myargs(int argc, char **argv){
    while (1) {
	c = getopt_long(argc, argv, short_opt, long_opt, NULL);
	if (c == -1)
	    break;
         
         else return optarg;
}
*/














