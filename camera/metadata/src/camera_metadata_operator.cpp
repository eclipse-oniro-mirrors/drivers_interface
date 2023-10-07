/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "camera_metadata_operator.h"
#include <dlfcn.h>
#include <memory>
#include <securec.h>
#include <vector>
#include "camera_metadata_item_info.h"
#include "camera_vendor_tag.h"
#include "camera_example_vendor_tags.h"
#include "metadata_log.h"

namespace OHOS::Camera {
const int METADATA_HEADER_DATA_SIZE = 4;
const std::vector<int32_t> METADATATAGS = {
    OHOS_ABILITY_CAMERA_POSITION,
    OHOS_ABILITY_CAMERA_TYPE,
    OHOS_ABILITY_CAMERA_CONNECTION_TYPE,
    OHOS_ABILITY_MEMORY_TYPE,
    OHOS_ABILITY_FPS_RANGES,
    OHOS_ABILITY_FLASH_AVAILABLE,
    OHOS_CAMERA_STREAM_ID,
    OHOS_ABILITY_SKETCH_ENABLE_RATIO,
    OHOS_ABILITY_SKETCH_REFERENCE_FOV_RATIO,
    OHOS_ABILITY_AVAILABLE_COLOR_SPACES,

    OHOS_SENSOR_EXPOSURE_TIME,
    OHOS_SENSOR_COLOR_CORRECTION_GAINS,
    OHOS_SENSOR_ORIENTATION,
    OHOS_ABILITY_MUTE_MODES,
    OHOS_CONTROL_MUTE_MODE,

    OHOS_SENSOR_INFO_ACTIVE_ARRAY_SIZE,
    OHOS_SENSOR_INFO_SENSITIVITY_RANGE,
    OHOS_SENSOR_INFO_MAX_FRAME_DURATION,
    OHOS_SENSOR_INFO_PHYSICAL_SIZE,
    OHOS_SENSOR_INFO_PIXEL_ARRAY_SIZE,
    OHOS_SENSOR_INFO_TIMESTAMP,

    OHOS_STATISTICS_FACE_DETECT_MODE,
    OHOS_STATISTICS_FACE_DETECT_SWITCH,
    OHOS_STATISTICS_FACE_DETECT_MAX_NUM,
    OHOS_STATISTICS_HISTOGRAM_MODE,
    OHOS_STATISTICS_FACE_IDS,
    OHOS_STATISTICS_FACE_LANDMARKS,
    OHOS_STATISTICS_FACE_RECTANGLES,
    OHOS_STATISTICS_FACE_SCORES,

    OHOS_CONTROL_AE_ANTIBANDING_MODE,
    OHOS_CONTROL_AE_EXPOSURE_COMPENSATION,
    OHOS_CONTROL_AE_LOCK,
    OHOS_CONTROL_AE_MODE,
    OHOS_CONTROL_AE_REGIONS,
    OHOS_CONTROL_AE_TARGET_FPS_RANGE,
    OHOS_CONTROL_FPS_RANGES,
    OHOS_CONTROL_AF_MODE,
    OHOS_CONTROL_AF_REGIONS,
    OHOS_CONTROL_AF_TRIGGER,
    OHOS_CONTROL_AF_TRIGGER_ID,
    OHOS_CONTROL_AF_STATE,
    OHOS_CONTROL_AWB_LOCK,
    OHOS_CONTROL_AWB_MODE,
    OHOS_CONTROL_AWB_REGIONS,
    OHOS_CONTROL_AE_AVAILABLE_ANTIBANDING_MODES,
    OHOS_CONTROL_AE_AVAILABLE_MODES,
    OHOS_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES,
    OHOS_CONTROL_AE_COMPENSATION_RANGE,
    OHOS_CONTROL_AE_COMPENSATION_STEP,
    OHOS_CONTROL_AF_AVAILABLE_MODES,
    OHOS_CONTROL_AWB_AVAILABLE_MODES,
    OHOS_CONTROL_CAPTURE_MIRROR_SUPPORTED,
    OHOS_CONTROL_CAPTURE_MIRROR,
    OHOS_CONTROL_FOCUS_STATE,
    OHOS_CONTROL_METER_POINT,
    OHOS_CONTROL_METER_MODE,
    OHOS_CONTROL_EXPOSURE_STATE,

    // Camera device image acquisition related
    OHOS_ABILITY_DEVICE_AVAILABLE_EXPOSUREMODES,
    OHOS_CONTROL_EXPOSUREMODE,
    OHOS_ABILITY_EXPOSURE_MODES,
    OHOS_CONTROL_EXPOSURE_MODE,
    OHOS_ABILITY_METER_MODES,

    OHOS_ABILITY_DEVICE_AVAILABLE_FOCUSMODES,
    OHOS_CONTROL_FOCUSMODE,
    OHOS_ABILITY_FOCUS_MODES,
    OHOS_CONTROL_FOCUS_MODE,
    OHOS_ABILITY_FOCAL_LENGTH,

    OHOS_ABILITY_DEVICE_AVAILABLE_FLASHMODES,
    OHOS_CONTROL_FLASHMODE,
    OHOS_ABILITY_FLASH_MODES,
    OHOS_CONTROL_FLASH_MODE,
    OHOS_CONTROL_FLASH_STATE,

    OHOS_ABILITY_ZOOM_RATIO_RANGE,
    OHOS_CONTROL_ZOOM_RATIO,
    OHOS_CONTROL_ZOOM_CROP_REGION,
    OHOS_ABILITY_ZOOM_CAP,
    OHOS_ABILITY_SCENE_ZOOM_CAP,

    // Camera flow control related
    OHOS_ABILITY_STREAM_AVAILABLE_BASIC_CONFIGURATIONS,
    OHOS_STREAM_AVAILABLE_FORMATS,
    OHOS_ABILITY_STREAM_AVAILABLE_EXTEND_CONFIGURATIONS,

    OHOS_JPEG_GPS_COORDINATES,
    OHOS_JPEG_GPS_PROCESSING_METHOD,
    OHOS_JPEG_GPS_TIMESTAMP,
    OHOS_JPEG_ORIENTATION,
    OHOS_JPEG_QUALITY,
    OHOS_JPEG_THUMBNAIL_QUALITY,
    OHOS_JPEG_THUMBNAIL_SIZE,
    OHOS_JPEG_AVAILABLE_THUMBNAIL_SIZES,
    OHOS_JPEG_MAX_SIZE,
    OHOS_JPEG_SIZE,

    OHOS_ABILITY_VIDEO_STABILIZATION_MODES,
    OHOS_CONTROL_VIDEO_STABILIZATION_MODE,

    // camera effects & algorithms
    OHOS_ABILITY_SCENE_FILTER_TYPES,
    OHOS_CONTROL_FILTER_TYPE,
    OHOS_ABILITY_SCENE_PORTRAIT_EFFECT_TYPES,
    OHOS_CONTROL_PORTRAIT_EFFECT_TYPE,
    OHOS_ABILITY_SCENE_BEAUTY_TYPES,
    OHOS_CONTROL_BEAUTY_TYPE,
    OHOS_ABILITY_BEAUTY_AUTO_VALUES,
    OHOS_CONTROL_BEAUTY_AUTO_VALUE,
    OHOS_ABILITY_BEAUTY_FACE_SLENDER_VALUES,
    OHOS_CONTROL_BEAUTY_FACE_SLENDER_VALUE,
    OHOS_ABILITY_BEAUTY_SKIN_TONE_VALUES,
    OHOS_CONTROL_BEAUTY_SKIN_TONE_VALUE,
    OHOS_ABILITY_BEAUTY_SKIN_SMOOTH_VALUES,
    OHOS_CONTROL_BEAUTY_SKIN_SMOOTH_VALUE,

    // camera secure related
    OHOS_CONTROL_SECURE_FACE_MODE,
    OHOS_CONTROL_SECURE_FACE_INFO,
    OHOS_CONTROL_SECURE_FACE_AUTH_RESULT,
    OHOS_CONTROL_SECURE_FLASH_SEQ,
    OHOS_CONTROL_SECURE_IR_LED_SWITCH,
    OHOS_CONTROL_SECURE_IR_LOCKAE_SWITCH,

    //XMAGE MODES
    OHOS_ABILITY_SUPPORTED_COLOR_MODES,
    OHOS_CONTROL_SUPPORTED_COLOR_MODES,
};

uint32_t AlignTo(uint32_t val, uint32_t alignment)
{
    return static_cast<uint32_t>((static_cast<uintptr_t>(val) + ((alignment) - 1)) & ~((alignment) - 1));
}

uint32_t MaxAlignment(uint32_t dataAlignment, uint32_t metadataAlignment)
{
    return ((dataAlignment > metadataAlignment) ? dataAlignment : metadataAlignment);
}

uint8_t *GetMetadataData(const common_metadata_header_t *metadataHeader)
{
    if (!metadataHeader) {
        METADATA_ERR_LOG("GetMetadataData metadataHeader is null");
        return nullptr;
    }
    return (uint8_t *)metadataHeader + metadataHeader->data_start;
}

camera_metadata_item_entry_t *GetMetadataItems(const common_metadata_header_t *metadataHeader)
{
    return reinterpret_cast<camera_metadata_item_entry_t *>(
        (reinterpret_cast<uint8_t *>(const_cast<common_metadata_header_t *>(metadataHeader)) +
        metadataHeader->items_start));
}

common_metadata_header_t *FillCameraMetadata(common_metadata_header_t *buffer, size_t memoryRequired,
                                             uint32_t itemCapacity, uint32_t dataCapacity)
{
    METADATA_DEBUG_LOG("FillCameraMetadata start");
    if (buffer == nullptr) {
        METADATA_ERR_LOG("FillCameraMetadata buffer is null");
        return nullptr;
    }

    common_metadata_header_t *metadataHeader = static_cast<common_metadata_header_t *>(buffer);
    metadataHeader->version = CURRENT_CAMERA_METADATA_VERSION;
    metadataHeader->size = memoryRequired;
    metadataHeader->item_count = 0;
    metadataHeader->item_capacity = itemCapacity;
    metadataHeader->items_start = AlignTo(sizeof(common_metadata_header_t), ITEM_ALIGNMENT);
    metadataHeader->data_count = 0;
    metadataHeader->data_capacity = dataCapacity;
    size_t dataUnaligned = reinterpret_cast<uint8_t *>(GetMetadataItems(metadataHeader) +
                            metadataHeader->item_capacity) - reinterpret_cast<uint8_t *>(metadataHeader);
    metadataHeader->data_start = AlignTo(dataUnaligned, DATA_ALIGNMENT);

    METADATA_DEBUG_LOG("FillCameraMetadata end");
    return metadataHeader;
}

size_t CalculateCameraMetadataMemoryRequired(uint32_t itemCount, uint32_t dataCount)
{
    METADATA_DEBUG_LOG("CalculateCameraMetadataMemoryRequired start");
    size_t memoryRequired = sizeof(common_metadata_header_t);
    memoryRequired = AlignTo(memoryRequired, ITEM_ALIGNMENT);

    memoryRequired += sizeof(camera_metadata_item_entry_t[itemCount]);
    memoryRequired = AlignTo(memoryRequired, DATA_ALIGNMENT);

    memoryRequired += sizeof(uint8_t[dataCount]);
    memoryRequired = AlignTo(memoryRequired, METADATA_PACKET_ALIGNMENT);

    METADATA_DEBUG_LOG("CalculateCameraMetadataMemoryRequired memoryRequired: %{public}zu", memoryRequired);
    METADATA_DEBUG_LOG("CalculateCameraMetadataMemoryRequired end");
    return memoryRequired;
}

common_metadata_header_t *AllocateCameraMetadataBuffer(uint32_t item_capacity, uint32_t data_capacity)
{
    METADATA_DEBUG_LOG("AllocateCameraMetadataBuffer start");
    METADATA_DEBUG_LOG("AllocateCameraMetadataBuffer item_capacity: %{public}u, data_capacity: %{public}u",
                       item_capacity, data_capacity);
    size_t memoryRequired = CalculateCameraMetadataMemoryRequired(item_capacity, data_capacity);
    void *buffer = calloc(1, memoryRequired);
    if (buffer == nullptr) {
        METADATA_ERR_LOG("AllocateCameraMetadataBuffer memory allocation failed");
        return reinterpret_cast<common_metadata_header_t *>(buffer);
    }

    common_metadata_header_t *metadataHeader = FillCameraMetadata(reinterpret_cast<common_metadata_header_t *>(buffer),
                                                                  memoryRequired,
                                                                  item_capacity, data_capacity);
    if (metadataHeader == nullptr) {
        METADATA_ERR_LOG("AllocateCameraMetadataBuffer metadataHeader is null");
        free(buffer);
    }

    METADATA_DEBUG_LOG("AllocateCameraMetadataBuffer end");
    return metadataHeader;
}

int32_t GetMetadataSection(uint32_t itemSection, uint32_t *section)
{
    METADATA_DEBUG_LOG("GetMetadataSection start");
    if (itemSection < OHOS_CAMERA_PROPERTIES ||
        itemSection >= OHOS_ABILITY_SECTION_END) {
        METADATA_ERR_LOG("GetMetadataSection itemSection is not valid");
        return CAM_META_FAILURE;
    }

    int32_t ret = CAM_META_SUCCESS;
    switch (itemSection) {
        case OHOS_CAMERA_PROPERTIES:
            *section = OHOS_SECTION_CAMERA_PROPERTIES;
            break;
        case OHOS_CAMERA_SENSOR:
            *section = OHOS_SECTION_CAMERA_SENSOR;
            break;
        case OHOS_CAMERA_SENSOR_INFO:
            *section = OHOS_SECTION_CAMERA_SENSOR_INFO;
            break;
        case OHOS_CAMERA_STATISTICS:
            *section = OHOS_SECTION_CAMERA_STATISTICS;
            break;
        case OHOS_DEVICE_CONTROL:
            *section = OHOS_SECTION_CAMERA_CONTROL;
            break;
        case OHOS_DEVICE_EXPOSURE:
            *section = OHOS_SECTION_DEVICE_EXPOSURE;
            break;
        case OHOS_DEVICE_FOCUS:
            *section = OHOS_SECTION_DEVICE_FOCUS;
            break;
        case OHOS_DEVICE_FLASH:
            *section = OHOS_SECTION_DEVICE_FLASH;
            break;
        case OHOS_DEVICE_ZOOM:
            *section = OHOS_SECTION_DEVICE_ZOOM;
            break;
        case OHOS_STREAM_ABILITY:
            *section = OHOS_SECTION_STREAM_ABILITY;
            break;
        case OHOS_STREAM_JPEG:
            *section = OHOS_SECTION_STREAM_JPEG;
            break;
        case OHOS_STREAM_VIDEO:
            *section = OHOS_SECTION_STREAM_VIDEO;
            break;
        case OHOS_CAMERA_EFFECT:
            *section = OHOS_SECTION_CAMERA_EFFECT;
	    break;
        case OHOS_CAMERA_SECURE:
            *section = OHOS_SECTION_CAMERA_SECURE;
            break;
        case OHOS_XMAGE_COLOR_ABILITY:
            *section = OHOS_SECTION_CAMERA_XMAGE;
            break;
        default:
            METADATA_ERR_LOG("GetMetadataSection item section is not defined");
            ret = CAM_META_FAILURE;
            break;
    }

    METADATA_DEBUG_LOG("GetMetadataSection end");
    return ret;
}

int32_t GetCameraMetadataItemType(uint32_t item, uint32_t *dataType)
{
    METADATA_DEBUG_LOG("GetCameraMetadataItemType start");
    if (dataType == nullptr) {
        METADATA_ERR_LOG("GetCameraMetadataItemType dataType is null");
        return CAM_META_INVALID_PARAM;
    }
    uint32_t section;
    uint32_t itemTag = item >> BITWISE_SHIFT_16;
    if (itemTag >= OHOS_VENDOR_SECTION) {
#ifndef CAMERA_VENDOR_TAG
        std::shared_ptr<CameraVendorTagExample> vendorTag = std::make_shared<CameraVendorTagExample>();
        *dataType = vendorTag->GetVendorTagType(item);
#else
        void* libHandle_ = dlopen("libcamera_vendor_tag_impl.z.so", RTLD_LAZY);
        if (libHandle_ == nullptr) {
            METADATA_ERR_LOG("dlopen failed %{public}s", __func__);
            return CAM_META_FAILURE;
        }

        CreateCameraVendorTag* createVendorTag =
            reinterpret_cast<CreateCameraVendorTag*>(dlsym(libHandle_, "CreateVendorTagImpl"));
        if (createVendorTag == nullptr) {
            METADATA_ERR_LOG("CreateCameraVendorTag failed %{public}s", __func__);
            return CAM_META_FAILURE;
        }

        CameraVendorTag* vendorTagImpl = createVendorTag();
        *dataType = vendorTagImpl->GetVendorTagType(item);
#endif
        return CAM_META_SUCCESS;
    }
    int32_t ret = GetMetadataSection(itemTag, &section);
    if (ret != CAM_META_SUCCESS) {
        METADATA_ERR_LOG("GetCameraMetadataItemType section is not valid");
        return ret;
    }

    if (item >= g_ohosCameraSectionBounds[section][1]) {
        METADATA_ERR_LOG("GetCameraMetadataItemType item is not in section bound");
        return CAM_META_FAILURE;
    }

    uint32_t itemIndex = item & 0xFFFF;
    if (g_ohosItemInfo[section][itemIndex].item_type < META_TYPE_BYTE) {
        METADATA_ERR_LOG("GetCameraMetadataItemType item is not initialized");
        return CAM_META_FAILURE;
    }

    *dataType = g_ohosItemInfo[section][itemIndex].item_type;

    METADATA_DEBUG_LOG("GetCameraMetadataItemType end");
    return CAM_META_SUCCESS;
}

const char *GetCameraMetadataItemName(uint32_t item)
{
    METADATA_DEBUG_LOG("GetCameraMetadataItemName start");
    METADATA_DEBUG_LOG("GetCameraMetadataItemName item: %{public}u", item);
    uint32_t section;
    uint32_t itemTag = item >> BITWISE_SHIFT_16;
    if (itemTag >= OHOS_VENDOR_SECTION) {
#ifndef CAMERA_VENDOR_TAG
        std::shared_ptr<CameraVendorTagExample> vendorTag = std::make_shared<CameraVendorTagExample>();
        return vendorTag->GetVendorTagName(item);
#else
        void* libHandle_ = dlopen("libcamera_vendor_tag_impl.z.so", RTLD_LAZY);
        if (libHandle_ == nullptr) {
            METADATA_ERR_LOG("dlopen failed %{public}s", __func__);
            return nullptr;
        }

        CreateCameraVendorTag* createVendorTag =
            reinterpret_cast<CreateCameraVendorTag*>(dlsym(libHandle_, "CreateVendorTagImpl"));
        if (createVendorTag == nullptr) {
            METADATA_ERR_LOG("CreateCameraVendorTag failed %{public}s", __func__);
            return nullptr;
        }

        CameraVendorTag* vendorTagImpl = createVendorTag();
        return vendorTagImpl->GetVendorTagName(item);
#endif
    }
    int32_t ret = GetMetadataSection(itemTag, &section);
    if (ret != CAM_META_SUCCESS) {
        METADATA_ERR_LOG("GetCameraMetadataItemName section is not valid");
        return nullptr;
    }

    if (item >= g_ohosCameraSectionBounds[section][1]) {
        METADATA_ERR_LOG("GetCameraMetadataItemName item is not in section bound");
        return nullptr;
    }

    uint32_t itemIndex = item & 0xFFFF;
    METADATA_DEBUG_LOG("GetCameraMetadataItemName end");
    return g_ohosItemInfo[section][itemIndex].item_name;
}

size_t CalculateCameraMetadataItemDataSize(uint32_t type, size_t dataCount)
{
    METADATA_DEBUG_LOG("CalculateCameraMetadataItemDataSize start");
    if (type < META_TYPE_BYTE || type >= META_NUM_TYPES) {
        METADATA_ERR_LOG("CalculateCameraMetadataItemDataSize invalid type");
        return 0;
    }

    size_t dataBytes = dataCount * OHOS_CAMERA_METADATA_TYPE_SIZE[type];

    METADATA_DEBUG_LOG("CalculateCameraMetadataItemDataSize end");
    return (dataBytes <= METADATA_HEADER_DATA_SIZE) ? 0 : AlignTo(dataBytes, DATA_ALIGNMENT);
}

int AddCameraMetadataItem(common_metadata_header_t *dst, uint32_t item, const void *data, size_t dataCount)
{
    METADATA_DEBUG_LOG("AddCameraMetadataItem start");
    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        name = "<unknown>";
    }
    METADATA_DEBUG_LOG("AddCameraMetadataItem item id: %{public}u, name: %{public}s, "
                       "dataCount: %{public}zu", item, name, dataCount);

    if (dst == nullptr) {
        METADATA_ERR_LOG("AddCameraMetadataItem common_metadata_header_t is null");
        return CAM_META_INVALID_PARAM;
    }

    if (!dataCount || data == nullptr) {
        METADATA_ERR_LOG("AddCameraMetadataItem data is not valid. item: %{public}u, "
                         "dataCount: %{public}zu", item, dataCount);
        return CAM_META_INVALID_PARAM;
    }

    if (dst->item_count == dst->item_capacity) {
        METADATA_ERR_LOG("AddCameraMetadataItem item_capacity limit reached. "
                         "item_count: %{public}d, item_capacity: %{public}d",
                         dst->item_count, dst->item_capacity);
        return CAM_META_ITEM_CAP_EXCEED;
    }

    uint32_t dataType;
    int32_t ret = GetCameraMetadataItemType(item, &dataType);
    if (ret != CAM_META_SUCCESS) {
        METADATA_ERR_LOG("AddCameraMetadataItem invalid item type");
        return CAM_META_INVALID_PARAM;
    }

    size_t dataBytes =
            CalculateCameraMetadataItemDataSize(dataType, dataCount);
    if (dataBytes + dst->data_count > dst->data_capacity) {
        METADATA_ERR_LOG("AddCameraMetadataItem data_capacity limit reached");
        return CAM_META_DATA_CAP_EXCEED;
    }

    size_t dataPayloadBytes =
            dataCount * OHOS_CAMERA_METADATA_TYPE_SIZE[dataType];
    camera_metadata_item_entry_t *metadataItem = GetMetadataItems(dst) + dst->item_count;
    ret = memset_s(metadataItem, sizeof(camera_metadata_item_entry_t), 0, sizeof(camera_metadata_item_entry_t));
    if (ret != EOK) {
        METADATA_ERR_LOG("AddCameraMetadataItem: memset_s failed");
        return CAM_META_FAILURE;
    }
    metadataItem->item = item;
    metadataItem->data_type = dataType;
    metadataItem->count = dataCount;

    if (dataBytes == 0) {
        ret = memcpy_s(metadataItem->data.value, METADATA_HEADER_DATA_SIZE, data, dataPayloadBytes);
        if (ret != EOK) {
            METADATA_ERR_LOG("AddCameraMetadataItem memory copy failed");
            return CAM_META_FAILURE;
        }
    } else {
        metadataItem->data.offset = dst->data_count;
        ret = memcpy_s(GetMetadataData(dst) + metadataItem->data.offset, dst->data_capacity - dst->data_count, data,
            dataPayloadBytes);
        if (ret != EOK) {
            METADATA_ERR_LOG("AddCameraMetadataItem memory copy failed");
            return CAM_META_FAILURE;
        }
        dst->data_count += dataBytes;
    }
    dst->item_count++;

    METADATA_DEBUG_LOG("AddCameraMetadataItem end");
    return CAM_META_SUCCESS;
}

int GetCameraMetadataItem(const common_metadata_header_t *src, uint32_t index, camera_metadata_item_t *item)
{
    METADATA_DEBUG_LOG("GetCameraMetadataItem start");
    if (src == nullptr || item == nullptr) {
        METADATA_ERR_LOG("GetCameraMetadataItem src or item is null");
        return CAM_META_INVALID_PARAM;
    }

    int32_t ret = memset_s(item, sizeof(camera_metadata_item_t), 0, sizeof(camera_metadata_item_t));
    if (ret != EOK) {
        METADATA_ERR_LOG("GetCameraMetadataItem: memset_s failed");
        return CAM_META_FAILURE;
    }
    if (index >= src->item_count) {
        METADATA_ERR_LOG("GetCameraMetadataItem index is greater than item count");
        return CAM_META_INVALID_PARAM;
    }

    camera_metadata_item_entry_t *localItem = GetMetadataItems(src) + index;

    item->index = index;
    item->item = localItem->item;
    item->data_type = localItem->data_type;
    item->count = localItem->count;

    size_t dataBytes = CalculateCameraMetadataItemDataSize(localItem->data_type, localItem->count);
    if (dataBytes == 0) {
        item->data.u8 = localItem->data.value;
    } else {
        item->data.u8 = GetMetadataData(src) + localItem->data.offset;
    }

    METADATA_DEBUG_LOG("GetCameraMetadataItem end");
    return CAM_META_SUCCESS;
}

int FindCameraMetadataItemIndex(const common_metadata_header_t *src, uint32_t item, uint32_t *idx)
{
    METADATA_DEBUG_LOG("FindCameraMetadataItemIndex start");
    METADATA_DEBUG_LOG("FindCameraMetadataItemIndex item: %{public}u", item);
    if (src == nullptr || idx == nullptr) {
        METADATA_ERR_LOG("FindCameraMetadataItemIndex src or index is null");
        return CAM_META_INVALID_PARAM;
    }

    camera_metadata_item_entry_t *searchItem = GetMetadataItems(src);
    uint32_t index;
    for (index = 0; index < src->item_count; index++, searchItem++) {
        if (searchItem->item == item) {
            break;
        }
    }

    if (index == src->item_count) {
        METADATA_ERR_LOG("FindCameraMetadataItemIndex item: %{public}u not found", item);
        return CAM_META_ITEM_NOT_FOUND;
    }

    *idx = index;
    METADATA_DEBUG_LOG("FindCameraMetadataItemIndex index: %{public}u", index);
    METADATA_DEBUG_LOG("FindCameraMetadataItemIndex end");
    return CAM_META_SUCCESS;
}

int FindCameraMetadataItem(const common_metadata_header_t *src, uint32_t item, camera_metadata_item_t *metadataItem)
{
    uint32_t index = 0;
    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        name = "<unknown>";
    }
    METADATA_DEBUG_LOG("FindCameraMetadataItem item id: %{public}u, name: %{public}s", item, name);
    int ret = FindCameraMetadataItemIndex(src, item, &index);
    if (ret != CAM_META_SUCCESS) {
        return ret;
    }

    return GetCameraMetadataItem(src, index, metadataItem);
}

void SetOffset(camera_metadata_item_entry_t *metadataItems, camera_metadata_item_entry_t *item, size_t oldItemSize)
{
    if (CalculateCameraMetadataItemDataSize(metadataItems->data_type, metadataItems->count) > 0 &&
        metadataItems->data.offset > item->data.offset) {
        metadataItems->data.offset -= oldItemSize;
    }
}

int MetadataExpandItemMem(common_metadata_header_t *dst, camera_metadata_item_entry_t *item,
    size_t oldItemSize)
{
    if (item == nullptr || dst == nullptr) {
        METADATA_ERR_LOG("MetadataExpandItemMem item is null or dst is null");
        return CAM_META_INVALID_PARAM;
    }
    uint8_t *start = GetMetadataData(dst) + item->data.offset;
    uint8_t *end = start + oldItemSize;
    size_t length = dst->data_count - item->data.offset - oldItemSize;
    if (length != 0) {
        int32_t ret = memmove_s(start, length, end, length);
        if (ret != EOK) {
            METADATA_ERR_LOG("MetadataExpandItemMem memory move failed");
            return CAM_META_FAILURE;
        }
    }
    dst->data_count -= oldItemSize;

    camera_metadata_item_entry_t *metadataItems = GetMetadataItems(dst);
    for (uint32_t i = 0; i < dst->item_count; i++, ++metadataItems) {
        SetOffset(metadataItems, item, oldItemSize);
    }

    return CAM_META_SUCCESS;
}

int UpdateCameraMetadataItemByIndex(common_metadata_header_t *dst, uint32_t index, const void *data, uint32_t dataCount,
                                    camera_metadata_item_t *updatedItem)
{
    METADATA_DEBUG_LOG("UpdateCameraMetadataItemByIndex start");
    if ((dst == nullptr) || (index >= dst->item_count)) {
        METADATA_ERR_LOG("UpdateCameraMetadataItemByIndex dst is null or invalid index");
        return CAM_META_INVALID_PARAM;
    }

    if (!dataCount || data == nullptr) {
        METADATA_ERR_LOG("UpdateCameraMetadataItemByIndex data is not valid. "
                         "dataCount: %{public}u", dataCount);
        return CAM_META_INVALID_PARAM;
    }

    int32_t ret = CAM_META_SUCCESS;
    camera_metadata_item_entry_t *item = GetMetadataItems(dst) + index;
    size_t dataSize = CalculateCameraMetadataItemDataSize(item->data_type, dataCount);
    size_t dataPayloadSize = dataCount * OHOS_CAMERA_METADATA_TYPE_SIZE[item->data_type];

    size_t oldItemSize = CalculateCameraMetadataItemDataSize(item->data_type, item->count);
    if (dataSize != oldItemSize) {
        if (dst->data_capacity < (dst->data_count + dataSize - oldItemSize)) {
            METADATA_ERR_LOG("UpdateCameraMetadataItemByIndex data_capacity limit reached");
            return CAM_META_DATA_CAP_EXCEED;
        }

        if (oldItemSize != 0) {
            ret = MetadataExpandItemMem(dst, item, oldItemSize);
            if (ret != CAM_META_SUCCESS) {
                return ret;
            }
        }

        if (dataSize != 0) {
            item->data.offset = dst->data_count;
            ret = memcpy_s(GetMetadataData(dst) + item->data.offset, dataPayloadSize, data, dataPayloadSize);
            if (ret != EOK) {
                METADATA_ERR_LOG("UpdateCameraMetadataItemByIndex memory copy failed");
                return CAM_META_FAILURE;
            }
            dst->data_count += dataSize;
        }
    } else if (dataSize != 0) {
        ret = memcpy_s(GetMetadataData(dst) + item->data.offset, dataPayloadSize, data, dataPayloadSize);
        if (ret != EOK) {
            METADATA_ERR_LOG("UpdateCameraMetadataItemByIndex memory copy failed");
            return CAM_META_FAILURE;
        }
    }

    if (dataSize == 0) {
        ret = memcpy_s(item->data.value, dataPayloadSize, data, dataPayloadSize);
        if (ret != EOK) {
            METADATA_ERR_LOG("UpdateCameraMetadataItemByIndex memory copy failed");
            return CAM_META_FAILURE;
        }
    }

    item->count = dataCount;
    if (updatedItem != nullptr) {
        ret = GetCameraMetadataItem(dst, index, updatedItem);
        if (ret != CAM_META_SUCCESS) {
            return ret;
        }
    }

    METADATA_DEBUG_LOG("UpdateCameraMetadataItemByIndex end");
    return ret;
}

int UpdateCameraMetadataItem(common_metadata_header_t *dst, uint32_t item, const void *data,
                             uint32_t dataCount, camera_metadata_item_t *updatedItem)
{
    METADATA_DEBUG_LOG("UpdateCameraMetadataItem item id: %{public}u, dataCount: %{public}u", item, dataCount);
    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        name = "<unknown>";
    }
    METADATA_DEBUG_LOG("UpdateCameraMetadataItem item id: %{public}u, name: %{public}s, "
                       "dataCount: %{public}u", item, name, dataCount);
    if (!dataCount || data == nullptr) {
        METADATA_ERR_LOG("UpdateCameraMetadataItem data is not valid. item: %{public}u, "
                         "dataCount: %{public}u", item, dataCount);
        return CAM_META_INVALID_PARAM;
    }

    uint32_t index = 0;
    int32_t ret = FindCameraMetadataItemIndex(dst, item, &index);
    if (ret != CAM_META_SUCCESS) {
        return ret;
    }

    return UpdateCameraMetadataItemByIndex(dst, index, data, dataCount, updatedItem);
}

int DeleteCameraMetadataItemByIndex(common_metadata_header_t *dst, uint32_t index)
{
    METADATA_DEBUG_LOG("DeleteCameraMetadataItemByIndex start");
    if (dst == nullptr) {
        METADATA_ERR_LOG("DeleteCameraMetadataItemByIndex dst is null");
        return CAM_META_INVALID_PARAM;
    }

    if (index >= dst->item_count) {
        METADATA_ERR_LOG("DeleteCameraMetadataItemByIndex item not valid");
        return CAM_META_INVALID_PARAM;
    }

    int32_t ret = CAM_META_SUCCESS;
    camera_metadata_item_entry_t *itemToDelete = GetMetadataItems(dst) + index;
    size_t dataBytes = CalculateCameraMetadataItemDataSize(itemToDelete->data_type, itemToDelete->count);
    if (dataBytes > 0) {
        uint8_t *start = GetMetadataData(dst) + itemToDelete->data.offset;
        uint8_t *end = start + dataBytes;
        size_t length = dst->data_count - itemToDelete->data.offset - dataBytes;
        if (length != 0) {
            ret = memmove_s(start, length, end, length);
            if (ret != EOK) {
                METADATA_ERR_LOG("DeleteCameraMetadataItemByIndex memory move failed");
                return CAM_META_FAILURE;
            }
        }
        dst->data_count -= dataBytes;

        camera_metadata_item_entry_t *metadataItems = GetMetadataItems(dst);
        for (uint32_t i = 0; i < dst->item_count; i++, ++metadataItems) {
            if (CalculateCameraMetadataItemDataSize(
                metadataItems->data_type, metadataItems->count) > 0 &&
                metadataItems->data.offset > itemToDelete->data.offset) {
                metadataItems->data.offset -= dataBytes;
            }
        }
    }

    uint64_t length = sizeof(camera_metadata_item_entry_t) * (dst->item_count - index - 1);
    if (length != 0) {
        ret = memmove_s(itemToDelete, length, itemToDelete + 1, length);
        if (ret != EOK) {
            METADATA_ERR_LOG("DeleteCameraMetadataItemByIndex memory move failed");
            return CAM_META_FAILURE;
        }
    }
    dst->item_count -= 1;
    METADATA_DEBUG_LOG("DeleteCameraMetadataItemByIndex end");
    return ret;
}

int DeleteCameraMetadataItem(common_metadata_header_t *dst, uint32_t item)
{
    METADATA_DEBUG_LOG("DeleteCameraMetadataItem item: %{public}u", item);
    uint32_t index = 0;
    int32_t ret = FindCameraMetadataItemIndex(dst, item, &index);
    if (ret != CAM_META_SUCCESS) {
        return ret;
    }

    return DeleteCameraMetadataItemByIndex(dst, index);
}

void FreeCameraMetadataBuffer(common_metadata_header_t *dst)
{
    if (dst != nullptr) {
        free(dst);
    }
}

uint32_t GetCameraMetadataItemCount(const common_metadata_header_t *metadataHeader)
{
    if (!metadataHeader) {
        METADATA_ERR_LOG("GetCameraMetadataItemCount::metadataHeader is null");
        return 0;
    }
    return metadataHeader->item_count;
}

uint32_t GetCameraMetadataItemCapacity(const common_metadata_header_t *metadataHeader)
{
    if (!metadataHeader) {
        METADATA_ERR_LOG("GetCameraMetadataItemCapacity::metadataHeader is null");
        return 0;
    }
    return metadataHeader->item_capacity;
}

uint32_t GetCameraMetadataDataSize(const common_metadata_header_t *metadataHeader)
{
    if (metadataHeader == nullptr) {
        METADATA_ERR_LOG("GetCameraMetadataDataSize::metadataHeader is null");
        return 0;
    }
    return metadataHeader->data_capacity;
}

int32_t CopyCameraMetadataItems(common_metadata_header_t *newMetadata, const common_metadata_header_t *oldMetadata)
{
    if (newMetadata == nullptr || oldMetadata == nullptr) {
        return CAM_META_INVALID_PARAM;
    }

    int32_t ret;
    if (oldMetadata->item_count != 0) {
        ret = memcpy_s(GetMetadataItems(newMetadata), sizeof(camera_metadata_item_entry_t[oldMetadata->item_count]),
            GetMetadataItems(oldMetadata), sizeof(camera_metadata_item_entry_t[oldMetadata->item_count]));
        if (ret != EOK) {
            METADATA_ERR_LOG("CopyCameraMetadataItems memory copy failed");
            return CAM_META_FAILURE;
        }
    }

    if (oldMetadata->data_count != 0) {
        ret = memcpy_s(GetMetadataData(newMetadata), sizeof(uint8_t[oldMetadata->data_count]),
            GetMetadataData(oldMetadata), sizeof(uint8_t[oldMetadata->data_count]));
        if (ret != EOK) {
            METADATA_ERR_LOG("CopyCameraMetadataItems memory copy failed");
            return CAM_META_FAILURE;
        }
    }

    newMetadata->item_count = oldMetadata->item_count;
    newMetadata->data_count = oldMetadata->data_count;

    return CAM_META_SUCCESS;
}

std::string U8ItemToString(int32_t item, const camera_metadata_item_t entry)
{
    std::string st = {};
    uint32_t count = entry.count;
    std::string dataStr = std::to_string(*(entry.data.u8));
    for (uint32_t i = 1; i < count; i++) {
        if ((i % WRAP_LENGTH) == 0) {
            dataStr += "]\n\t[" + std::to_string(*(entry.data.u8 + i));
        } else {
            dataStr += " " + std::to_string(*(entry.data.u8 + i));
        }
    }

    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        METADATA_ERR_LOG("U8ItemToString: get u8 item name fail!");
        return st;
    }
    std::string nameStr(name);

    st = nameStr + " (" + std::to_string(entry.index) + "): " +
        OHOS_CAMERA_METADATA_TYPE[entry.data_type] + "[" + std::to_string(count) + "]" + "\n\t[" + dataStr + "]";

    return st;
}

std::string I32ItemToString(int32_t item, const camera_metadata_item_t entry)
{
    std::string st = {};
    uint32_t count = entry.count;
    std::string dataStr = std::to_string(*(entry.data.i32));
    for (uint32_t i = 1; i < count; i++) {
        if ((i % WRAP_LENGTH) == 0) {
            dataStr += "]\n\t[" + std::to_string(*(entry.data.i32 + i));
        } else {
            dataStr += " " + std::to_string(*(entry.data.i32 + i));
        }
    }

    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        METADATA_ERR_LOG("I32ItemToString: get i32 item name fail!");
        return st;
    }
    std::string nameStr(name);

    st = nameStr + " (" + std::to_string(entry.index) + "): " +
        OHOS_CAMERA_METADATA_TYPE[entry.data_type] + "[" + std::to_string(count) + "]" + "\n\t[" + dataStr + "]";

    return st;
}

std::string U32ItemToString(int32_t item, const camera_metadata_item_t entry)
{
    std::string st = {};
    uint32_t count = entry.count;
    std::string dataStr = std::to_string(*(entry.data.ui32));
    for (uint32_t i = 1; i < count; i++) {
        if ((i % WRAP_LENGTH) == 0) {
            dataStr += "]\n\t[" + std::to_string(*(entry.data.ui32 + i));
        } else {
            dataStr += " " + std::to_string(*(entry.data.ui32 + i));
        }
    }

    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        METADATA_ERR_LOG("U32ItemToString: get u32 item name fail!");
        return st;
    }
    std::string nameStr(name);

    st = nameStr + " (" + std::to_string(entry.index) + "): " +
        OHOS_CAMERA_METADATA_TYPE[entry.data_type] + "[" + std::to_string(count) + "]" + "\n\t[" + dataStr + "]";

    return st;
}

std::string I64ItemToString(int32_t item, const camera_metadata_item_t entry)
{
    std::string st = {};
    uint32_t count = entry.count;
    std::string dataStr = std::to_string(*(entry.data.i64));
    for (uint32_t i = 1; i < count; i++) {
        if ((i % WRAP_LENGTH) == 0) {
            dataStr += "]\n\t[" + std::to_string(*(entry.data.i64 + i));
        } else {
            dataStr += " " + std::to_string(*(entry.data.i64 + i));
        }
    }

    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        METADATA_ERR_LOG("I64ItemToString: get i64 item name fail!");
        return st;
    }
    std::string nameStr(name);

    st = nameStr + " (" + std::to_string(entry.index) + "): " +
        OHOS_CAMERA_METADATA_TYPE[entry.data_type] + "[" + std::to_string(count) + "]" + "\n\t[" + dataStr + "]";

    return st;
}

std::string FloatItemToString(int32_t item, const camera_metadata_item_t entry)
{
    std::string st = {};
    uint32_t count = entry.count;
    std::string dataStr = std::to_string(*(entry.data.f));
    for (uint32_t i = 1; i < count; i++) {
        if ((i % WRAP_LENGTH) == 0) {
            dataStr += "]\n\t[" + std::to_string(*(entry.data.f + i));
        } else {
            dataStr += " " + std::to_string(*(entry.data.f + i));
        }
    }

    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        METADATA_ERR_LOG("FloatItemToString: get float item name fail!");
        return st;
    }
    std::string nameStr(name);

    st = nameStr + " (" + std::to_string(entry.index) + "): " +
        OHOS_CAMERA_METADATA_TYPE[entry.data_type] + "[" + std::to_string(count) + "]" + "\n\t[" + dataStr + "]";

    return st;
}

std::string DoubleItemToString(int32_t item, const camera_metadata_item_t entry)
{
    std::string st = {};
    uint32_t count = entry.count;
    std::string dataStr = std::to_string(*(entry.data.d));
    for (uint32_t i = 1; i < count; i++) {
        if ((i % WRAP_LENGTH) == 0) {
            dataStr += "]\n\t[" + std::to_string(*(entry.data.d + i));
        } else {
            dataStr += " " + std::to_string(*(entry.data.d + i));
        }
    }

    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        METADATA_ERR_LOG("DoubleItemToString: get double item name fail!");
        return st;
    }
    std::string nameStr(name);

    st = nameStr + " (" + std::to_string(entry.index) + "): " +
        OHOS_CAMERA_METADATA_TYPE[entry.data_type] + "[" + std::to_string(count) + "]" + "\n\t[" + dataStr + "]";

    return st;
}

std::string RationalItemToString(int32_t item, const camera_metadata_item_t entry)
{
    std::string st = {};
    uint32_t count = entry.count;
    std::string dataStr = std::to_string((*(entry.data.r)).numerator) + "/" +
        std::to_string((*(entry.data.r)).denominator);
    for (uint32_t i = 1; i < count; i++) {
        if ((i % WRAP_LENGTH) == 0) {
            dataStr += "]\n\t[" + std::to_string((*(entry.data.r + i)).numerator) + "/" +
                std::to_string((*(entry.data.r + i)).denominator);
        } else {
            dataStr += " " + std::to_string((*(entry.data.r + i)).numerator) + "/" +
                std::to_string((*(entry.data.r + i)).denominator);
        }
    }

    const char *name = GetCameraMetadataItemName(item);
    if (name == nullptr) {
        METADATA_ERR_LOG("RationalItemToString: get rational item name fail!");
        return st;
    }
    std::string nameStr(name);

    st = nameStr + " (" + std::to_string(entry.index) + "): " +
        OHOS_CAMERA_METADATA_TYPE[entry.data_type] + "[" + std::to_string(count) + "]" + "\n\t[" + dataStr + "]";

    return st;
}

std::string MetadataItemDump(const common_metadata_header_t *metadataHeader, uint32_t item)
{
    camera_metadata_item_t entry;
    std::string st = {};

    int ret = FindCameraMetadataItem(metadataHeader, item, &entry);
    if (ret != 0) {
        METADATA_ERR_LOG("get item error and item = %{public}d", item);
        return st;
    }

    switch (entry.data_type) {
        case META_TYPE_BYTE:
            st = U8ItemToString(item, entry);
            break;
        case META_TYPE_INT32:
            st = I32ItemToString(item, entry);
            break;
        case META_TYPE_UINT32:
            st = U32ItemToString(item, entry);
            break;
        case META_TYPE_FLOAT:
            st = FloatItemToString(item, entry);
            break;
        case META_TYPE_INT64:
            st = I64ItemToString(item, entry);
            break;
        case META_TYPE_DOUBLE:
            st = DoubleItemToString(item, entry);
            break;
        case META_TYPE_RATIONAL:
            st = RationalItemToString(item, entry);
            break;
        default:
            METADATA_ERR_LOG("invalid param and item = %{public}d", item);
            break;
    }

    if (!st.empty()) {
        st += "\n";
    }
    return st;
}

std::string FormatCameraMetadataToString(const common_metadata_header_t *metadataHeader)
{
    std::string metaStr;
    if (metadataHeader == nullptr) {
        METADATA_ERR_LOG("metadataHeader is nullptr");
        return metaStr;
    }

    for (auto it = METADATATAGS.begin(); it != METADATATAGS.end(); it++) {
        metaStr += MetadataItemDump(metadataHeader, *it);
    }
    METADATA_INFO_LOG("metadataHeader item = %{public}s", metaStr.c_str());
    return metaStr;
}
} // Camera
