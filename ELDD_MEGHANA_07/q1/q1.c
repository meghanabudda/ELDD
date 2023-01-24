#include<linux/kernel.h>
#include<linux/module.h>
#include <linux/init.h>
#include<linux/semaphore.h>
#include<linux/wait.h>
#include <linux/fcntl.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>              
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MEGHA");
MODULE_DESCRIPTION("MULTIPLE DEVICES");

static struct class *myclass=NULL;
static struct device *mydevice=NULL;
static dev_t mycdevt; 
static struct semaphore *sem;
static struct cdev *mycdev;

wait_queue_head_fp;
init_wait_queue_(&fp);
static int myopen(struct inode *inod, struct file *fp)/*This function will be called when we open the Device file*/

{
	down(&sem);
	pr_info("Critical Section\n");
	return 0;
}

static int myclose(struct inode *inod, struct file *fp)/*This function will be called when we close the Device file*/

{
	up(&sem);
	pr_info("Critical Section Freed\n");
	return 0;
}

static ssize_t myread(struct file *file, char *buf, size_t len,loff_t *off)/*This function will be called when we read the Device file*/

{
	return 0;
}

static ssize_t mywrite(struct file *file, const char *buf, size_t len, loff_t *off)/*This function will be called when we write the Device file*/

{
	return len;
}

/*File Operations structure*/

static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = myread,
        .write          = mywrite,
        .open           = myopen,
        .release        = myclose,
};

/*Module Init function*/

static int __init myinit(void)
{
int ret;

    ret=alloc_chrdev_region(&mycdevt, MINOR_NUM, MINOR_CNT, "mycdevt");
    if(ret<0)
    {
        pr_info("Cannot allocate chardev\n");
        return -1;
    }

/*Creating cdev structure*/

    mycdev=cdev_alloc();
        if(mycdev==NULL)
        {
        	pr_info("cdev_alloc failed\n");
        }
        
        mycdev -> ops =&fops;
/*Adding character device to the system*/
        ret=cdev_add(mycdev,mycdevt,1);
        if(ret<0)
        {
            pr_info("Cannot add the device to the system\n");
        }
 
/*Creating struct class*/
        myclass=class_create(THIS_MODULE,"class_name");
        if(myclass==NULL)
        {
            pr_info("Cannot create the struct class\n");
            
        }
 
/*Creating device*/
        mydevice=device_create(myclass,NULL,mycdevt,NULL,"mydevice");
        if(mydevice==NULL)
        {
            pr_info("Cannot create the Device 1\n");
            
        }
/*Semaphore initialisation*/
        void sema_init(&sem,1);
        pr_info("myinit done");
        return 0;
        }
 

/*Module exit function*/

static void __exit myexit(void)
{
	device_destroy(myclass,mycdevt);
    class_unregister(myclass);
    class_destroy(myclass);
    cdev_del(mycdev);
    unregister_chrdev(MAJOR(mycdevt),"mycdevt");
    pr_info("exit...Done!!!\n");
}
module_init(myinit);
module_exit(myexit);
