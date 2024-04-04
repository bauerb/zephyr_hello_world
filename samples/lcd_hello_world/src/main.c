#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/auxdisplay.h>


int main()
{
  const struct device *lcd = DEVICE_DT_GET(DT_NODELABEL(auxdisplay_0));
  uint8_t data[64];
  int rc = 0;

  printk("Set up LCD display\n");

  if(!device_is_ready(lcd))
  {
    printk("Auxdisplay device is not ready.");
    return 1;
  }

  rc = auxdisplay_backlight_set(lcd, 1);
  if (rc != 0)
  {
    printk("Failed to enable backlight: %d", rc);
    return 1;
  }

  rc = auxdisplay_cursor_set_enabled(lcd, true);
  if (rc != 0)
  {
    printk("Failed to enable cursor: %d", rc);
    return 1;
  }

  snprintk(data, sizeof(data), "Hello world from %s", CONFIG_BOARD);
  rc = auxdisplay_write(lcd, data, strlen(data));
  if(rc != 0) {
    printk("Failed to write data: %d", rc);
    return 1;
  }

  printk("Main-Loop\n");

  while(1)
  {
  }

  return 0;
}
