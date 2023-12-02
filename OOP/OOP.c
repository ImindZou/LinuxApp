#include <stdio.h>

struct file_operation{
	void (*read)(void);
	void (*write)(void);
};

struct file_system{
	char name[20];
	struct file_operation fops;	
};

struct file_CD{
	char name[20];
	void (*chouxiang_write)(void);
	struct file_system fops2;
};

void chouxiang_write(void){
	printf("chouxiang_write...\n");
}

void ext_read(void){
	printf("ext read ...\n");
}

void ext_write(void){
	printf("ext write...\n");
}

void fat_read(void){
	printf("fat read...\n");
}

void fat_write(void){
	printf("fat write...\n");
}

/*void chouxian_write(void){			//这是缺陷
	printf("chouxian write...\n");
}

void chouxian_read(void){
	printf("chouxian read...\n");
}*/

int main(void){
	struct file_system ext = {"ext3",{ext_read,ext_write}};
	struct file_system fat = {"fat32",{fat_read,fat_write}};
	struct file_CD fops2 = {"chouxiang",chouxiang_write,{"fat32",{ext_read,ext_write}}};

	struct file_system *fp;
	fp = &ext;
	fp->fops.read();
	fp = &fat;
	fp->fops.read();
	ext.fops.read();
	struct file_CD *chouxiang;
	chouxiang = &fops2;
	printf("file_CD's name: %s\n",chouxiang->name);
	printf("chouxiang **name :%s\n",chouxiang->fops2.name);
	chouxiang->fops2.fops.write();
	//chouxiang->fops2->(struct file_operation *).ext_write();
	chouxiang->fops2.fops.read();
	//printf("fops2 name :%s\n",fops2.name);
	//fops2.fops.ext_read();
	chouxiang->chouxiang_write();

	return 0;
}
