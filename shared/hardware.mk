DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE := device/google/cuttlefish/shared/device_framework_matrix.xml

# aidl_interface
PRODUCT_PACKAGES += vendor.hardware.carsenze

# cc_binary
PRODUCT_PACKAGES += vendor.hardware.carsenze-service

# android_app
PRODUCT_PACKAGES += Carsenze

PRODUCT_ARTIFACT_PATH_REQUIREMENT_ALLOWED_LIST+= \
    system/app/Carsenze/%
	