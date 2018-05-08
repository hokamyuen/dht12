#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "DHT12"

static int dht12_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int dht12_remove(struct i2c_client *client);

static ssize_t dht12_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);

static struct file_operations dht12_fops = {
	.owner = THIS_MODULE,
	.read = dht12_read,
};

static struct miscdevice dht12_miscdevice = {
	.name	= DEVICE_NAME,
	.fops	= &dht12_fops,
	.minor	= MISC_DYNAMIC_MINOR,
};

static struct i2c_client *g_client;
static int dht12_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int err = 0;
	printk("%s device is detected\n", DEVICE_NAME);
	g_client = client;
	err = misc_register(&dht12_miscdevice);
	if(err)
	{
		printk("%s: register miscdevice failed!\n", __FUNCTION__);
	}
	
	return 0;
}

static int dht12_remove(struct i2c_client *client)
{
	printk("%s\n", __FUNCTION__);
	misc_deregister(&dht12_miscdevice);
	return 0;
}

static ssize_t dht12_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	char data_addr = 0x00;
	char data_buf[5];
	
	i2c_master_send(g_client, &data_addr, 1);//write addr
	i2c_master_recv(g_client, &data_buf[0], 5);//read data
	copy_to_user(buf, data_buf, 5);
	return 5;
}

static const struct i2c_device_id dht12_id[] = {
	{ DEVICE_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, dht12_id);

static struct i2c_driver dht12_driver = {
	.driver		= {
		.name	= DEVICE_NAME,
		.owner	= THIS_MODULE,
	},
	.probe		= dht12_probe,
	.remove		= dht12_remove,
	.id_table	= dht12_id,
};

static int __init dht12_init(void)
{
	printk("%s\n", __FUNCTION__);
	return i2c_add_driver(&dht12_driver);
}

static void __exit dht12_exit(void)
{
	printk("%s\n", __FUNCTION__);
	i2c_del_driver(&dht12_driver);
}

module_init(dht12_init);
module_exit(dht12_exit);
MODULE_AUTHOR("hokamyuen");
MODULE_DESCRIPTION("dht12 drv");
MODULE_LICENSE("GPL");
MODULE_VERSION("V0.1");
