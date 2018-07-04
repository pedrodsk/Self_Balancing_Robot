deps_config := \
	/home/pedro/esp/esp-idf/components/app_trace/Kconfig \
	/home/pedro/esp/esp-idf/components/aws_iot/Kconfig \
	/home/pedro/esp/esp-idf/components/bt/Kconfig \
	/home/pedro/esp/esp-idf/components/driver/Kconfig \
	/home/pedro/esp/esp-idf/components/esp32/Kconfig \
	/home/pedro/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/pedro/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/pedro/esp/esp-idf/components/ethernet/Kconfig \
	/home/pedro/esp/esp-idf/components/fatfs/Kconfig \
	/home/pedro/esp/esp-idf/components/freertos/Kconfig \
	/home/pedro/esp/esp-idf/components/heap/Kconfig \
	/home/pedro/esp/esp-idf/components/libsodium/Kconfig \
	/home/pedro/esp/esp-idf/components/log/Kconfig \
	/home/pedro/esp/esp-idf/components/lwip/Kconfig \
	/home/pedro/esp/esp-idf/components/mbedtls/Kconfig \
	/home/pedro/esp/esp-idf/components/openssl/Kconfig \
	/home/pedro/esp/esp-idf/components/pthread/Kconfig \
	/home/pedro/esp/esp-idf/components/spi_flash/Kconfig \
	/home/pedro/esp/esp-idf/components/spiffs/Kconfig \
	/home/pedro/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/pedro/esp/esp-idf/components/vfs/Kconfig \
	/home/pedro/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/pedro/esp/esp-idf/Kconfig.compiler \
	/home/pedro/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/pedro/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/pedro/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/pedro/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
