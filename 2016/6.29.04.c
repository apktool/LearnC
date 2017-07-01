/**
 * @file 6.29.04.c
 * @brief getpwuid(),getpwnam(),getgrgid(),getgrnam()
 * @author LiWenGang
 * @date 2016-06-29
 */
#include<sys/types.h>
#include<pwd.h>
#include<grp.h>
#include<stdio.h>

char* userNameFromId(uid_t uid);		//通过UID获取用户名
uid_t userIdFromName(const char* name);	//通过用户名获取UID
char* groupFromId(gid_t gid);			//通过gid获取组名
gid_t groupIdFromName(const char* name);//通过组名获取GID

int main(int argc,char* argv[]){
	char* username;
	uid_t uid=1000;	

	username=userNameFromId(uid);
	printf("username=%s\n",username);
	uid=userIdFromName("li");
	printf("uid=%d\n",uid);
	
	char* groupname;
	gid_t gid=1000;
	
	groupname=groupFromId(gid);
	printf("groupname=%s\n",groupname);
	gid=groupIdFromName(groupname);
	printf("gid=%d\n",gid);
	
	return 0;
}

char* userNameFromId(uid_t uid){
	struct passwd *usr;
	usr=getpwuid(uid);
	if(usr==NULL){
		return NULL;
	}else{
		return usr->pw_name;
	}
}

uid_t userIdFromName(const char* name){
	struct passwd *usr;
	if(name==NULL||*name==0){
		return -1;
	}
	usr=getpwnam(name);
	if(usr==NULL){
		return -1;
	}
	return usr->pw_uid;
}

char* groupFromId(gid_t gid){
	struct group *grp;
	grp=getgrgid(gid);
	if(grp==NULL){
		return NULL;
	}else{
		return grp->gr_name;
	}
}

gid_t groupIdFromName(const char* name){
	struct group *grp;
	if(name==NULL||*name==0){
		return -1;
	}
	grp=getgrnam(name);
	if(grp==NULL){
		return -1;
	}else{
		return grp->gr_gid;
	}
}
