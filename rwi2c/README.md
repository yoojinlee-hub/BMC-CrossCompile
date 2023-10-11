# TMP75's Protocol
```
struct i2c_msg {
  __u16 addr;
  __u16 flags;
#define I2C_M_TEN		0x0010
#define I2C_M_RD		0x0001
#define I2C_M_NOSTART		0x4000
#define I2C_M_REV_DIR_ADDR	0x2000
#define I2C_M_IGNORE_NAK	0x1000
#define I2C_M_NO_RD_ACK		0x0800
#define I2C_M_RECV_LEN		0x0400
  __u16 len;
  __u8 * buf;
}; 
``` 
![site](https://docs.huihoo.com/linux/kernel/2.6.26/kernel-api/re1210.html)

<br>
![image](https://github.com/yoojinlee-hub/BMC-CrossCompile/assets/80568037/de5bf308-1fd8-4dff-aaf8-582798aae6ac)
![image](https://github.com/yoojinlee-hub/BMC-CrossCompile/assets/80568037/03dcd1f4-6efa-473f-bfc3-8875725bf409)
![image](https://github.com/yoojinlee-hub/BMC-CrossCompile/assets/80568037/b4a4eee3-ea8a-4fc3-8452-027908b9c2a4)
![image](https://github.com/yoojinlee-hub/BMC-CrossCompile/assets/80568037/7f81131a-95f5-44b1-8334-663eb8ac1ff3)
