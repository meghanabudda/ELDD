#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/err.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/slab.h>
#include<linux/ioctl.h>


MODULE_AUTHOR("MEGHA");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IOCTL");

dev_t dev=0;
static struct class *dev_class;
static struct cdev my_cdev;
 

static struct file_operations fops=

{
    .owner          =THIS_MODULE,
    .read           = myread ,
    .write          = mywrite ,
    .unlocked_ioctl = chrioctl ,
    .open           = myopen ,
    .release        = myrelease ,
};

static long chrioctl(struct file *file ,unsigned  int cmd ,unsigned long arg)

{
    return 0;
}

/*open file function*/

static int myopen(struct inode *inode,struct file *file)
{
    pr_info("cannot open the file");
    return 0;
}

/*close file function*/
static int myrelease(struct inode *inode,struct file *file)
{
    pr_info("file is closed");
    return 0;
} 

/*read file */
static ssize_t myread(struct file *file,char __user *buf,size_t len,loff_t *off)
{
    return 0;
}


/* write file*/
static ssize_t mywrite(struct file *file,const char  *buf,size_t len,loff_t *off)
{
    return len;
}


static int __init chr_driver_init(void)
{
    if((alloc_chrdev_region(&dev,0,1,"char_dev"))<0)
    {
        pr_info("cannot allocate the major minor number");
        return -1;
    }
    pr_info("MAJOR =%d AND MINOR = %d",MAJOR(dev),MINOR(dev));
    /*creating cdev structure*/

    cdev_init(&my_cdev,&fops);
    /*adding char device to the system*/

    if((cdev_add(&my_cdev,dev,1))<0)
    {
        pr_info("cannot add character device in the system");
        goto r_class;
    }

    if(IS_ERR(dev_class=class_create(THIS_MODULE,"dri_class")))
    {
        pr_info("cannot create the device class");
        goto r_class;
    }

    if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"char_dev")))
    {
        pr_info("cannot create the device file ");
        goto r_device;
    }
    pr_info("Device Driver Insert...Done!!!\n");
    return 0;




r_class:
        unregister_chrdev_region(dev,1);
r_device:
        class_destroy(dev_class);
        return -1;
}
static void __exit chr_driver_exit(void)
{
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev,1);
    pr_info("its removed successfully");
}

module_init(chr_driver_init);
module_exit(chr_driver_exit);

