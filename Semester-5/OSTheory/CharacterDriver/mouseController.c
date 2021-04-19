
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#include <linux/input.h>
#include <linux/init.h>

#include <asm/irq.h>
#include <asm/io.h>
#include <linux/usb.h>

#define DEVICE_NAME "mouseController"
#define MAX 256

static char buffer[MAX+1] ="";

struct mouse_device {
    struct input_dev *idev;
    int x, y; 
};

static struct mouse_device *mouse;

int mouseController_open(struct inode *inode,struct file * filep)
{
    printk ("Device opened \n");
    return 0;
}

int mouseController_release(struct inode *inode,struct file *filep)
{
    printk("Device closed \n");
    return 0;
}

ssize_t mouseController_write(struct file *filep ,const char __user *buf,size_t length ,loff_t *f_pos)
{
    if (length > MAX)
        return -EINVAL;

    if (copy_from_user(buffer, buf, length) != 0)
        return -EFAULT;

    int i, command = -1;

    struct input_dev *dev = mouse->idev; 

    int val = 10 ;

    val *= buffer[1] - '0' + 1 ;

    switch (buffer[0])
    {
        case '8' :  input_report_rel(dev, REL_Y, -val);
                    break ;
        case '6' :  input_report_rel(dev, REL_X, val);
                    break ;
        case '2' :  input_report_rel(dev, REL_Y, val);
                    break ;
        case '4' :  input_report_rel(dev, REL_X, -val);
                    break ;
        case '7' :  input_report_rel(dev, REL_Y, -val);
                    input_report_rel(dev, REL_X, -val);
                    break ;
        case '9' :  input_report_rel(dev, REL_Y, -val);
                    input_report_rel(dev, REL_X, val);
                    break ;
        case '3' :  input_report_rel(dev, REL_Y, val);
                    input_report_rel(dev, REL_X, val);
                    break ;
        case '1' :  input_report_rel(dev, REL_X, -val);
                    input_report_rel(dev, REL_Y, val);
                    break ;
        case '5' :  input_report_key(dev, BTN_LEFT, 1);
			        input_sync(dev);
			        input_report_key(dev, BTN_LEFT, 0);
			        if(buffer[1]=='5')
			        {
			            input_sync(dev);
				        input_report_key(dev, BTN_LEFT, 1);
			            input_sync(dev);
				        input_report_key(dev, BTN_LEFT, 0);
			            input_sync(dev);
			        }
                    break ;
        case '0' :  input_report_key(dev, BTN_RIGHT, 1);
			        input_sync(dev);
			        input_report_key(dev, BTN_RIGHT, 0);
                    break ;
        default:
                break;
    }

    input_sync(dev);

    printk(KERN_INFO "Received %s characters from the user\n", buffer);

    return 0;
}

ssize_t mouseController_read(struct file *filep,char __user *buf,size_t length,loff_t *f_pos)
{
    if (length > MAX) 
        return -EINVAL ;

    if (copy_to_user(buf,buffer,length) != 0)
        return -EFAULT;

    int i;
    for(i=0;i<=MAX;i+=1) 
        buffer[i] = buffer[(i+length)>MAX ? MAX : i+length] ;
    printk ("Reading from the device ...\n");
    return 0;
}

struct file_operations mouseController_fops =
{
    .owner = THIS_MODULE ,
    .open = mouseController_open ,
    .read = mouseController_read ,
    .write = mouseController_write ,
    .release = mouseController_release ,
};

int mouseController_init(void)
{
    printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__) ;
    int result ;
    if ((result = register_chrdev(240 , "mouseController", &mouseController_fops)) < 0)
        goto fail ;
    
    struct input_dev *input_dev;

    mouse = kmalloc(sizeof(struct mouse_device), GFP_KERNEL);
    if (!mouse) 
        return -ENOMEM;
    memset(mouse, 0, sizeof(*mouse));

	input_dev = input_allocate_device();
	if (!input_dev) {
		printk(KERN_ERR "[mouseController] : Not enough memory\n");
	}

	mouse->idev = input_dev;

    input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	input_dev->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_LEFT) | BIT_MASK(BTN_RIGHT) | BIT_MASK(BTN_MIDDLE);
	input_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y) | BIT_MASK(REL_WHEEL);

	input_dev->name = DEVICE_NAME;	

	input_set_drvdata(input_dev, mouse);
	
	int retval = input_register_device(input_dev);
	if (retval) {
		printk(KERN_ERR "[mouseController] : Failed to register device\n");
		goto fail;
	}
    printk ("mouseController device driver loaded ...\n");
    return 0;
    fail :
        return -1;
}

void mouseController_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__) ;
    if(!mouse) return;

	input_unregister_device(mouse->idev);
	kfree(mouse);	
    unregister_chrdev (240 , "mouseController");

    printk ("mouseController driver unloaded ...\n");
}

module_init(mouseController_init) ;
module_exit(mouseController_exit) ;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vibans_V1");
<<<<<<< HEAD
MODULE_DESCRIPTION("mouseController Module");
=======
MODULE_DESCRIPTION("mouseController Module");
>>>>>>> 53fb8cad7642ad1e579eeb431a0fa6725267a1e6
