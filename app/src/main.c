#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>
#include <zephyr/sys/__assert.h>

int main(void)
{
	int ret = 0;
	struct sensor_value light_val;

	const struct device *const dev = DEVICE_DT_GET_ONE(ams_tsl2591);

	if (!device_is_ready(dev)) {
		printk("sensor: device not ready.\n");
		return -1;
	}

	while (1) {
		ret = sensor_sample_fetch(dev);
		if (ret) {
			printf("sensor_sample_fetch failed ret %d\n", ret);
			return -1;
		}

		ret = sensor_channel_get(dev, SENSOR_CHAN_LIGHT, &light_val);
		if (ret) {
			printf("sensor_sample_fetch failed ret %d\n", ret);
			return -1;
		}

		printf("Light value int = %d, frac = %d\n", light_val.val1, light_val.val2);
		k_sleep(K_SECONDS(1));
	}

	return 0;
}
