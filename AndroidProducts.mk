#
# Copyright 2017 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

PRODUCT_MAKEFILES := \
	aosp_cf_arm_minidroid:$(LOCAL_DIR)/vsoc_arm_minidroid/aosp_cf.mk \
	aosp_cf_arm64_auto:$(LOCAL_DIR)/vsoc_arm64_only/auto/aosp_cf.mk \
	aosp_cf_arm64_phone:$(LOCAL_DIR)/vsoc_arm64/phone/aosp_cf.mk \
	aosp_cf_arm64_phone_pgagnostic:$(LOCAL_DIR)/vsoc_arm64_pgagnostic/phone/aosp_cf.mk \
	aosp_cf_arm64_phone_fullmte:$(LOCAL_DIR)/vsoc_arm64_only/phone/aosp_cf_fullmte.mk \
	aosp_cf_arm64_phone_hwasan:$(LOCAL_DIR)/vsoc_arm64/phone/aosp_cf_hwasan.mk \
	aosp_cf_arm64_only_phone:$(LOCAL_DIR)/vsoc_arm64_only/phone/aosp_cf.mk \
	aosp_cf_arm64_only_phone_hwasan:$(LOCAL_DIR)/vsoc_arm64_only/phone/aosp_cf_hwasan.mk \
	aosp_cf_arm64_minidroid:$(LOCAL_DIR)/vsoc_arm64_minidroid/aosp_cf.mk \
	aosp_cf_arm64_slim:$(LOCAL_DIR)/vsoc_arm64_only/slim/aosp_cf.mk \
	aosp_cf_riscv64_minidroid:$(LOCAL_DIR)/vsoc_riscv64_minidroid/aosp_cf.mk \
	aosp_cf_riscv64_slim:$(LOCAL_DIR)/vsoc_riscv64/slim/aosp_cf.mk \
	aosp_cf_riscv64_wear:$(LOCAL_DIR)/vsoc_riscv64/wear/aosp_cf.mk \
	aosp_cf_riscv64_phone:$(LOCAL_DIR)/vsoc_riscv64/phone/aosp_cf.mk \
	aosp_cf_x86_64_auto:$(LOCAL_DIR)/vsoc_x86_64_only/auto/aosp_cf.mk \
	aosp_cf_x86_64_auto_md:$(LOCAL_DIR)/vsoc_x86_64_only/auto_md/aosp_cf.mk \
	aosp_cf_x86_64_auto_mdnd:$(LOCAL_DIR)/vsoc_x86_64_only/auto_mdnd/aosp_cf.mk \
	aosp_cf_x86_64_auto_portrait:$(LOCAL_DIR)/vsoc_x86_64_only/auto_portrait/aosp_cf.mk \
	aosp_cf_x86_64_pc:$(LOCAL_DIR)/vsoc_x86_64_only/pc/aosp_cf.mk \
	aosp_cf_x86_64_phone:$(LOCAL_DIR)/vsoc_x86_64/phone/aosp_cf.mk \
	aosp_cf_x86_64_phone_vendor:$(LOCAL_DIR)/vsoc_x86_64/phone/aosp_cf_vendor.mk \
	aosp_cf_x86_64_ssi:$(LOCAL_DIR)/vsoc_x86_64/phone/aosp_cf_ssi.mk \
	aosp_cf_x86_64_tv:$(LOCAL_DIR)/vsoc_x86_64/tv/aosp_cf.mk \
	aosp_cf_x86_64_foldable:$(LOCAL_DIR)/vsoc_x86_64/phone/aosp_cf_foldable.mk \
	aosp_cf_x86_64_host:$(LOCAL_DIR)/vsoc_x86_64_host/aosp_cf.mk \
	aosp_cf_x86_64_minidroid:$(LOCAL_DIR)/vsoc_x86_64_minidroid/aosp_cf.mk \
	aosp_cf_x86_64_only_phone:$(LOCAL_DIR)/vsoc_x86_64_only/phone/aosp_cf.mk \
	aosp_cf_x86_64_phone_pgagnostic:$(LOCAL_DIR)/vsoc_x86_64_pgagnostic/phone/aosp_cf.mk \
	aosp_cf_x86_64_only_phone_hsum:$(LOCAL_DIR)/vsoc_x86_64_only/phone/aosp_cf_hsum.mk \
	aosp_cf_x86_64_slim:$(LOCAL_DIR)/vsoc_x86_64_only/slim/aosp_cf.mk \
	aosp_cf_x86_64_wear:$(LOCAL_DIR)/vsoc_x86_64_only/wear/aosp_cf.mk \
	aosp_cf_x86_pasan:$(LOCAL_DIR)/vsoc_x86/pasan/aosp_cf.mk \
	aosp_cf_x86_phone:$(LOCAL_DIR)/vsoc_x86/phone/aosp_cf.mk \
	aosp_cf_x86_only_phone:$(LOCAL_DIR)/vsoc_x86_only/phone/aosp_cf.mk \
	aosp_cf_x86_go_phone:$(LOCAL_DIR)/vsoc_x86/go/aosp_cf.mk \
	aosp_cf_x86_tv:$(LOCAL_DIR)/vsoc_x86/tv/aosp_cf.mk \
	aosp_cf_x86_wear:$(LOCAL_DIR)/vsoc_x86/wear/aosp_cf.mk \

COMMON_LUNCH_CHOICES := \
	aosp_cf_arm64_auto-trunk_staging-userdebug \
	aosp_cf_arm64_phone-trunk_staging-userdebug \
	aosp_cf_riscv64_phone-trunk_staging-userdebug \
	aosp_cf_x86_64_only_phone_hsum-trunk_staging-userdebug \
	aosp_cf_x86_64_pc-trunk_staging-userdebug \
	aosp_cf_x86_64_phone-trunk_staging-userdebug \
	aosp_cf_x86_64_foldable-trunk_staging-userdebug \
	aosp_cf_x86_64_auto-trunk_staging-userdebug \
	aosp_cf_x86_64_auto_mdnd-trunk_staging-userdebug \
	aosp_cf_x86_phone-trunk_staging-userdebug \
	aosp_cf_x86_tv-trunk_staging-userdebug \
	aosp_cf_x86_64_tv-trunk_staging-userdebug
