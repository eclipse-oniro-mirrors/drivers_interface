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

#ifndef CAMERA_METADATA_ITEM_INFO_H
#define CAMERA_METADATA_ITEM_INFO_H

#include "camera_metadata_operator.h"

namespace OHOS::Camera {
const static size_t OHOS_CAMERA_METADATA_TYPE_SIZE[META_NUM_TYPES] = {
    [META_TYPE_BYTE] = sizeof(uint8_t),
    [META_TYPE_INT32] = sizeof(int32_t),
    [META_TYPE_UINT32] = sizeof(uint32_t),
    [META_TYPE_FLOAT] = sizeof(float),
    [META_TYPE_INT64] = sizeof(int64_t),
    [META_TYPE_DOUBLE] = sizeof(double),
    [META_TYPE_RATIONAL] = sizeof(camera_rational_t)
};

static uint32_t g_ohosCameraSectionBounds[OHOS_SECTION_COUNT][2] = {
    [OHOS_SECTION_CAMERA_PROPERTIES] = {OHOS_CAMERA_PROPERTIES_START,  OHOS_CAMERA_PROPERTIES_END },
    [OHOS_SECTION_CAMERA_SENSOR] = {OHOS_CAMERA_SENSOR_START,      OHOS_CAMERA_SENSOR_END     },
    [OHOS_SECTION_CAMERA_SENSOR_INFO] = {OHOS_CAMERA_SENSOR_INFO_START, OHOS_CAMERA_SENSOR_INFO_END},
    [OHOS_SECTION_CAMERA_STATISTICS] = {OHOS_CAMERA_STATISTICS_START,  OHOS_CAMERA_STATISTICS_END },
    [OHOS_SECTION_CAMERA_CONTROL] = {OHOS_DEVICE_CONTROL_START,     OHOS_DEVICE_CONTROL_END    },
    [OHOS_SECTION_DEVICE_EXPOSURE] = {OHOS_DEVICE_EXPOSURE_START,    OHOS_DEVICE_EXPOSURE_END   },
    [OHOS_SECTION_DEVICE_FOCUS] = {OHOS_DEVICE_FOCUS_START,       OHOS_DEVICE_FOCUS_END      },
    [OHOS_SECTION_DEVICE_WHITE] = {OHOS_DEVICE_WHITE_BLANCE_START,    OHOS_DEVICE_WHITE_BLANCE_END      },
    [OHOS_SECTION_DEVICE_FLASH] = {OHOS_DEVICE_FLASH_START,       OHOS_DEVICE_FLASH_END      },
    [OHOS_SECTION_DEVICE_ZOOM] = {OHOS_DEVICE_ZOOM_START,        OHOS_DEVICE_ZOOM_END       },
    [OHOS_SECTION_STREAM_ABILITY] = {OHOS_STREAM_ABILITY_START,     OHOS_STREAM_ABILITY_END    },
    [OHOS_SECTION_STREAM_JPEG] = {OHOS_STREAM_JPEG_START,        OHOS_STREAM_JPEG_END       },
    [OHOS_SECTION_STREAM_VIDEO] = {OHOS_STREAM_VIDEO_START,       OHOS_STREAM_VIDEO_END      },
    [OHOS_SECTION_CAMERA_EFFECT] = {OHOS_CAMERA_EFFECT_START, OHOS_CAMERA_EFFECT_END },
    [OHOS_SECTION_CAMERA_SECURE] = {OHOS_CAMERA_SECURE_START, OHOS_CAMERA_SECURE_END },
    [OHOS_SECTION_CAMERA_XMAGE] = {OHOS_XMAGE_COLOR_MODES_START, OHOS_XMAGE_COLOR_MODES_END },
};

static item_info_t g_ohosCameraProperties[OHOS_CAMERA_PROPERTIES_END - OHOS_CAMERA_PROPERTIES_START] = {
    [OHOS_ABILITY_CAMERA_POSITION - OHOS_CAMERA_PROPERTIES_START] = {"cameraPosition",       META_TYPE_BYTE,  1 },
    [OHOS_ABILITY_CAMERA_TYPE - OHOS_CAMERA_PROPERTIES_START] = {"cameraType",           META_TYPE_BYTE,  1 },
    [OHOS_ABILITY_CAMERA_CONNECTION_TYPE -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraConnectionType", META_TYPE_BYTE,  1 },
    [OHOS_ABILITY_MEMORY_TYPE - OHOS_CAMERA_PROPERTIES_START] = {"cameraMemoryType", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_FPS_RANGES - OHOS_CAMERA_PROPERTIES_START] = {"fpsAvailableRanges",   META_TYPE_INT32, -1},
    [OHOS_ABILITY_FLASH_AVAILABLE - OHOS_CAMERA_PROPERTIES_START] = {"flashAvailable",       META_TYPE_BYTE,  1 },
    [OHOS_CAMERA_STREAM_ID - OHOS_CAMERA_PROPERTIES_START] = {"streamId",       META_TYPE_INT32,  1 },
    [OHOS_ABILITY_PRELAUNCH_AVAILABLE - OHOS_CAMERA_PROPERTIES_START] = {"prelaunchAvailable", META_TYPE_BYTE, 1 },
    [OHOS_ABILITY_CUSTOM_VIDEO_FPS - OHOS_CAMERA_PROPERTIES_START] = {"customVideoFps",   META_TYPE_INT32, -1},
    [OHOS_ABILITY_CAMERA_MODES - OHOS_CAMERA_PROPERTIES_START] = {"availableCameraModes", META_TYPE_BYTE, -1 },
    [OHOS_ABILITY_SKETCH_ENABLE_RATIO -
        OHOS_CAMERA_PROPERTIES_START] = {"sketchEnableRatio",       META_TYPE_FLOAT, -1},
    [OHOS_ABILITY_SKETCH_REFERENCE_FOV_RATIO -
        OHOS_CAMERA_PROPERTIES_START] = {"sketchReferenceFovRatio", META_TYPE_FLOAT, -1},
    [OHOS_ABILITY_CAMERA_FOLDSCREEN_TYPE -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraFoldscreenType", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_AVAILABLE_COLOR_SPACES -
        OHOS_CAMERA_PROPERTIES_START] = {"availableColorSpaces", META_TYPE_INT32, -1},
    [OHOS_CAMERA_USER_ID -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraUserId", META_TYPE_INT32, -1},
    [OHOS_ABILITY_NIGHT_MODE_SUPPORTED_EXPOSURE_TIME -
        OHOS_CAMERA_PROPERTIES_START] = {"nightModeSupportedExposureTime", META_TYPE_INT32, 1},
    [OHOS_CAMERA_MESURE_EXPOSURE_TIME -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraMesureExposureTime", META_TYPE_UINT32, 1},
    [OHOS_CAMERA_EXPOSURE_MODE_PREVIEW_STATE -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraExposureModePreviewState", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_MOON_CAPTURE_BOOST -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraAbilityMoonCaptureBoost", META_TYPE_UINT32, -1},
    [OHOS_CONTROL_MOON_CAPTURE_BOOST -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraControlMoonCaptureBoost", META_TYPE_BYTE, 1},
    [OHOS_STATUS_MOON_CAPTURE_DETECTION -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraStatusMoonCaptureDetection", META_TYPE_UINT32, 1},
    [OHOS_ABILITY_CAPTURE_DURATION_SUPPORTED -
        OHOS_CAMERA_PROPERTIES_START] = {"captureDurationSupported", META_TYPE_BYTE, 1},
    [OHOS_CAMERA_CUSTOM_SNAPSHOT_DURATION -
        OHOS_CAMERA_PROPERTIES_START] = {"customSnapshotDuration", META_TYPE_UINT32, 1},
    [OHOS_ABILITY_MOVING_PHOTO -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraAbilityMovingPhoto", META_TYPE_INT32, -1},
    [OHOS_ABILITY_FLASH_SUGGESTION_SUPPORTED -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraAbilityFlashSuggestionSupported", META_TYPE_UINT32, -1},
    [OHOS_CONTROL_FLASH_SUGGESTION_SWITCH -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraControlFlashSuggestionSwitch", META_TYPE_BYTE, 1},
    [OHOS_STATUS_FLASH_SUGGESTION -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraStatusFlashSuggestion", META_TYPE_UINT32, 1},
    [OHOS_ABILITY_HIGH_QUALITY_SUPPORT -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraAbilityHighQualitySupport", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAMERA_FOLD_STATUS -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraFoldStatus", META_TYPE_BYTE, 1},
    [OHOS_STATUS_CAMERA_OCCLUSION_DETECTION -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraStatusOcclusionDetection", META_TYPE_INT32, 1},
    [OHOS_ABILITY_STATISTICS_DETECT_TYPE -
        OHOS_CAMERA_PROPERTIES_START] = {"statisticsDetectType", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_STATISTICS_DETECT_SETTING -
        OHOS_CAMERA_PROPERTIES_START] = {"statisticsDetectSetting", META_TYPE_BYTE, -1},
    [OHOS_ABILITY_AVAILABLE_EXTENDED_STREAM_INFO_TYPES -
        OHOS_CAMERA_PROPERTIES_START] = {"availableExtendedStreamInfoTypes", META_TYPE_INT32, -1},
    [OHOS_ABILITY_AUTO_DEFERRED_VIDEO_ENHANCE -
        OHOS_CAMERA_PROPERTIES_START] = {"autoDeferredVideoEnhance", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_AUTO_DEFERRED_VIDEO_ENHANCE -
        OHOS_CAMERA_PROPERTIES_START] = {"controlAutoDeferredVideoEnhance", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_AUTO_CLOUD_IMAGE_ENHANCE -
        OHOS_CAMERA_PROPERTIES_START] = {"autoCloudImageEnhance", META_TYPE_INT32, -1},
    [OHOS_CONTROL_AUTO_CLOUD_IMAGE_ENHANCE -
        OHOS_CAMERA_PROPERTIES_START] = {"controlAutoCloudImageEnhance", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_TRIPOD_DETECTION -
        OHOS_CAMERA_PROPERTIES_START] = {"tripodDetection", META_TYPE_INT32, -1},
    [OHOS_CONTROL_TRIPOD_DETECTION -
        OHOS_CAMERA_PROPERTIES_START] = {"controlTripodDetection", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_TRIPOD_STABLITATION -
        OHOS_CAMERA_PROPERTIES_START] = {"tripodStablitation", META_TYPE_BYTE, 1},
    [OHOS_STATUS_TRIPOD_DETECTION_STATUS -
        OHOS_CAMERA_PROPERTIES_START] = {"tripodDetectionStatus", META_TYPE_BYTE, 1},
    [OHOS_STATUS_SKETCH_POINT -
        OHOS_CAMERA_PROPERTIES_START] = {"sketchPoint", META_TYPE_FLOAT, 1},
    [OHOS_ABILITY_LOW_LIGHT_BOOST -
        OHOS_CAMERA_PROPERTIES_START] = {"lowLightBoost", META_TYPE_INT32, -1},
    [OHOS_CONTROL_LOW_LIGHT_DETECT -
        OHOS_CAMERA_PROPERTIES_START] = {"controlLowLightBoost", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_LOW_LIGHT_BOOST -
        OHOS_CAMERA_PROPERTIES_START] = {"lowLightBoost", META_TYPE_BYTE, 1},
    [OHOS_STATUS_LOW_LIGHT_DETECTION -
        OHOS_CAMERA_PROPERTIES_START] = {"lowLightDetection", META_TYPE_BYTE, 1},
    [OHOS_STATUS_CAMERA_LENS_DIRTY_DETECTION -
        OHOS_CAMERA_PROPERTIES_START] = {"cameraLensDirtyDetection", META_TYPE_BYTE, 1},
    [OHOS_DEVICE_PROTECTION_STATE -
        OHOS_CAMERA_PROPERTIES_START] = {"protectionState", META_TYPE_BYTE, 1},
};

static item_info_t g_ohosCameraSensor[OHOS_CAMERA_SENSOR_END - OHOS_CAMERA_SENSOR_START] = {
    [OHOS_SENSOR_EXPOSURE_TIME - OHOS_CAMERA_SENSOR_START] = {"exposureTime",        META_TYPE_INT64, 1},
    [OHOS_SENSOR_COLOR_CORRECTION_GAINS - OHOS_CAMERA_SENSOR_START] = {"colorCorrectuonGain", META_TYPE_FLOAT, 1},
    [OHOS_SENSOR_ORIENTATION - OHOS_CAMERA_SENSOR_START] = {"sensorOrientation",         META_TYPE_INT32, 1},
    [OHOS_ABILITY_MUTE_MODES - OHOS_CAMERA_SENSOR_START] = {"muteAvailableModes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_MUTE_MODE - OHOS_CAMERA_SENSOR_START] = {"muteMode", META_TYPE_BYTE, 1},
};

static item_info_t g_ohosCameraSensorInfo[OHOS_CAMERA_SENSOR_INFO_END - OHOS_CAMERA_SENSOR_INFO_START] = {
    [OHOS_SENSOR_INFO_ACTIVE_ARRAY_SIZE -
        OHOS_CAMERA_SENSOR_INFO_START] = {"activeArraySize",       META_TYPE_INT32, -1},
    [OHOS_SENSOR_INFO_SENSITIVITY_RANGE -
        OHOS_CAMERA_SENSOR_INFO_START] = {"sensitivityRange",      META_TYPE_INT32, -1},
    [OHOS_SENSOR_INFO_MAX_FRAME_DURATION -
        OHOS_CAMERA_SENSOR_INFO_START] = {"maxFrameDuration",      META_TYPE_INT64, 1 },
    [OHOS_SENSOR_INFO_PHYSICAL_SIZE - OHOS_CAMERA_SENSOR_INFO_START] = {"physicalSize",          META_TYPE_FLOAT, 1 },
    [OHOS_SENSOR_INFO_PIXEL_ARRAY_SIZE -
        OHOS_CAMERA_SENSOR_INFO_START] = {"pixelArraySize",        META_TYPE_INT32, -1},
    [OHOS_SENSOR_INFO_TIMESTAMP - OHOS_CAMERA_SENSOR_INFO_START] = {"sensorOutputTimeStamp", META_TYPE_INT64, 1 },
};

static item_info_t g_ohosCameraStatistics[OHOS_CAMERA_STATISTICS_END - OHOS_CAMERA_STATISTICS_START] = {
    [OHOS_STATISTICS_FACE_DETECT_MODE - OHOS_CAMERA_STATISTICS_START] = {"faceDetectMode",   META_TYPE_BYTE,  1 },
    [OHOS_STATISTICS_FACE_DETECT_SWITCH - OHOS_CAMERA_STATISTICS_START] = {"faceDetectSwitch", META_TYPE_BYTE,  1 },
    [OHOS_STATISTICS_FACE_DETECT_MAX_NUM - OHOS_CAMERA_STATISTICS_START] = {"faceDetectMaxNum", META_TYPE_BYTE,  1 },
    [OHOS_STATISTICS_HISTOGRAM_MODE - OHOS_CAMERA_STATISTICS_START] = {"histogramMode",    META_TYPE_BYTE,  1 },
    [OHOS_STATISTICS_FACE_IDS - OHOS_CAMERA_STATISTICS_START] = {"faceIds",          META_TYPE_INT32, -1},
    [OHOS_STATISTICS_FACE_LANDMARKS - OHOS_CAMERA_STATISTICS_START] = {"faceLandmarks",    META_TYPE_INT32, -1},
    [OHOS_STATISTICS_FACE_RECTANGLES - OHOS_CAMERA_STATISTICS_START] = {"faceRectangles",   META_TYPE_FLOAT, -1},
    [OHOS_STATISTICS_FACE_SCORES - OHOS_CAMERA_STATISTICS_START] = {"faceScores",       META_TYPE_BYTE,  -1},
    [OHOS_STATISTICS_DETECT_HUMAN_FACE_INFOS -
        OHOS_CAMERA_STATISTICS_START] = {"detectHumanFaceInfos", META_TYPE_INT32,  -1},
    [OHOS_STATISTICS_DETECT_HUMAN_BODY_INFOS -
        OHOS_CAMERA_STATISTICS_START] = {"detectHumanBodyInfos", META_TYPE_INT32,  -1},
    [OHOS_STATISTICS_DETECT_CAT_FACE_INFOS -
        OHOS_CAMERA_STATISTICS_START] = {"detectCatFaceInfos", META_TYPE_INT32,  -1},
    [OHOS_STATISTICS_DETECT_CAT_BODY_INFOS -
        OHOS_CAMERA_STATISTICS_START] = {"detectCatBodyInfos", META_TYPE_INT32,  -1},
    [OHOS_STATISTICS_DETECT_DOG_FACE_INFOS -
        OHOS_CAMERA_STATISTICS_START] = {"detectDogFaceInfos", META_TYPE_INT32,  -1},
    [OHOS_STATISTICS_DETECT_DOG_BODY_INFOS -
        OHOS_CAMERA_STATISTICS_START] = {"detectDogBodyInfos", META_TYPE_INT32,  -1},
    [OHOS_STATISTICS_DETECT_SALIENT_INFOS -
        OHOS_CAMERA_STATISTICS_START] = {"detectSalientInfos", META_TYPE_INT32,  -1},
    [OHOS_STATISTICS_DETECT_BAR_CODE_INFOS -
        OHOS_CAMERA_STATISTICS_START] = {"detectBarCodeInfos", META_TYPE_INT32,  -1},
    [OHOS_STATISTICS_DETECT_BASE_FACE_INFO -
        OHOS_CAMERA_STATISTICS_START] = {"baseFaceInfo", META_TYPE_INT32,  -1},
};

static item_info_t g_ohosCameraControl[OHOS_DEVICE_CONTROL_END - OHOS_DEVICE_CONTROL_START] = {
    [OHOS_CONTROL_AE_ANTIBANDING_MODE -
        OHOS_DEVICE_CONTROL_START] = {"aeAntibandingMode",           META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_AE_EXPOSURE_COMPENSATION -
        OHOS_DEVICE_CONTROL_START] = {"aeExposureCompensation",      META_TYPE_INT32,    1 },
    [OHOS_CONTROL_AE_LOCK - OHOS_DEVICE_CONTROL_START] = {"aeLock",                      META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_AE_MODE - OHOS_DEVICE_CONTROL_START] = {"aeMode",                      META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_AE_REGIONS - OHOS_DEVICE_CONTROL_START] = {"aeRegions",                META_TYPE_FLOAT,    -1},
    [OHOS_CONTROL_AE_TARGET_FPS_RANGE -
        OHOS_DEVICE_CONTROL_START] = {"aeTargetFpsRange",            META_TYPE_INT32,    -1},
    [OHOS_CONTROL_FPS_RANGES - OHOS_DEVICE_CONTROL_START] = {"fpsRange",                    META_TYPE_INT32,    -1},
    [OHOS_CONTROL_AF_MODE - OHOS_DEVICE_CONTROL_START] = {"afMode",                         META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_AF_REGIONS - OHOS_DEVICE_CONTROL_START] = {"afRegions",                   META_TYPE_FLOAT,    -1},
    [OHOS_CONTROL_AF_TRIGGER - OHOS_DEVICE_CONTROL_START] = {"afTrigger",                   META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_AF_TRIGGER_ID - OHOS_DEVICE_CONTROL_START] = {"afTriggerId",              META_TYPE_INT32,    1 },
    [OHOS_CONTROL_AF_STATE - OHOS_DEVICE_CONTROL_START] = {"afState",                     META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_AWB_LOCK - OHOS_DEVICE_CONTROL_START] = {"awbLock",                     META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_AWB_MODE - OHOS_DEVICE_CONTROL_START] = {"awbMode",                     META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_AWB_REGIONS - OHOS_DEVICE_CONTROL_START] = {"awbRegions",                  META_TYPE_INT32,    -1},
    [OHOS_CONTROL_AE_AVAILABLE_ANTIBANDING_MODES -
        OHOS_DEVICE_CONTROL_START] = {"aeAvailableAntibandingModes", META_TYPE_BYTE,     -1},
    [OHOS_CONTROL_AE_AVAILABLE_MODES -
        OHOS_DEVICE_CONTROL_START] = {"aeAvailableModes",            META_TYPE_BYTE,     -1},
    [OHOS_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES -
        OHOS_DEVICE_CONTROL_START] = {"aeAvailableTargetFpsRanges",  META_TYPE_INT32,    -1},
    [OHOS_CONTROL_AE_COMPENSATION_RANGE -
        OHOS_DEVICE_CONTROL_START] = {"aeCompensationRange",         META_TYPE_INT32,    -1},
    [OHOS_CONTROL_AE_COMPENSATION_STEP -
        OHOS_DEVICE_CONTROL_START] = {"aeCompensationStep",          META_TYPE_RATIONAL, 1 },
    [OHOS_ABILITY_AE_COMPENSATION_RANGE -
        OHOS_DEVICE_CONTROL_START] = {"abilityAeCompensationRange",         META_TYPE_INT32,    -1},
    [OHOS_ABILITY_AE_COMPENSATION_STEP -
        OHOS_DEVICE_CONTROL_START] = {"abilityAeCompensationStep",          META_TYPE_RATIONAL, 1 },
    [OHOS_CONTROL_AF_AVAILABLE_MODES -
        OHOS_DEVICE_CONTROL_START] = {"afAvailableModes",            META_TYPE_BYTE,     -1},
    [OHOS_CONTROL_AWB_AVAILABLE_MODES -
        OHOS_DEVICE_CONTROL_START] = {"awbAvailableModes",           META_TYPE_BYTE,     -1},
    [OHOS_CONTROL_CAPTURE_MIRROR_SUPPORTED -
        OHOS_DEVICE_CONTROL_START] = {"mirrorSupported",             META_TYPE_BYTE,     -1 },
    [OHOS_CONTROL_CAPTURE_MIRROR - OHOS_DEVICE_CONTROL_START] = {"mirror",                      META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_FOCUS_STATE - OHOS_DEVICE_CONTROL_START] = {"focusState",                  META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_METER_POINT - OHOS_DEVICE_CONTROL_START] = {"meterPoint",                  META_TYPE_INT32,    -1},
    [OHOS_CONTROL_METER_MODE - OHOS_DEVICE_CONTROL_START] = {"meterMode",                   META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_EXPOSURE_STATE - OHOS_DEVICE_CONTROL_START] = {"exposureState",               META_TYPE_BYTE,     1 },
    [OHOS_CONTROL_FOCUSED_POINT - OHOS_DEVICE_CONTROL_START] = {"focusedPoint", META_TYPE_INT32, -1 },
    [OHOS_CONTROL_NIGHT_MODE_TRY_AE - OHOS_DEVICE_CONTROL_START] = {"nightModeTryAe", META_TYPE_BYTE, 1 },
    [OHOS_CONTROL_MANUAL_EXPOSURE_TIME - OHOS_DEVICE_CONTROL_START] = {"manualExposureTime", META_TYPE_UINT32, -1},
    [OHOS_STATUS_CAMERA_CURRENT_FPS - OHOS_DEVICE_CONTROL_START] = {"currentFps", META_TYPE_UINT32, 1},
    [OHOS_ABILITY_ISO_VALUES - OHOS_DEVICE_CONTROL_START] = {"supportedIsoValues", META_TYPE_INT32, -1},
    [OHOS_CONTROL_ISO_VALUE - OHOS_DEVICE_CONTROL_START] = {"isoValues", META_TYPE_INT32, 1},
    [OHOS_STATUS_ISO_VALUE - OHOS_DEVICE_CONTROL_START] = {"currentIsoValues", META_TYPE_INT32, 1},
    [OHOS_ABILITY_SENSOR_EXPOSURE_TIME_RANGE -
        OHOS_DEVICE_CONTROL_START] = {"sensorExposureTimeRange", META_TYPE_RATIONAL, -1},
    [OHOS_CONTROL_SENSOR_EXPOSURE_TIME - OHOS_DEVICE_CONTROL_START] = {"sensorExposureTime", META_TYPE_RATIONAL, 1},
    [OHOS_STATUS_SENSOR_EXPOSURE_TIME -
        OHOS_DEVICE_CONTROL_START] = {"currentSensorExposureTime", META_TYPE_RATIONAL, 1},
    [OHOS_CONTROL_MOVING_PHOTO - OHOS_DEVICE_CONTROL_START] = {"movingPhoto", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_SENSOR_WB_VALUES -
        OHOS_DEVICE_CONTROL_START] = {"supportedSensorWbValues", META_TYPE_INT32, -1},
    [OHOS_CONTROL_SENSOR_WB_VALUE - OHOS_DEVICE_CONTROL_START] = {"sensorWbValue", META_TYPE_INT32, 1},
    [OHOS_CONTROL_HIGH_QUALITY_MODE - OHOS_DEVICE_CONTROL_START] = {"highQualityMode", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_BURST_CAPTURE -
        OHOS_DEVICE_CONTROL_START] = {"cameraControlBurstCapture", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_CAMERA_USED_AS_POSITION -
        OHOS_DEVICE_CONTROL_START] = {"cameraUsedAsPosition", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_CAMERA_SESSION_USAGE -
        OHOS_DEVICE_CONTROL_START] = {"cameraSessionUsage", META_TYPE_INT32, 1},
    [OHOS_CONTROL_EJECT_RETRY -
        OHOS_DEVICE_CONTROL_START] = {"ejectRetry", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_FALL_PROTECTION -
        OHOS_DEVICE_CONTROL_START] = {"fallProtection", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_QUALITY_PRIORITIZATION -
        OHOS_DEVICE_CONTROL_START] = {"qualityPrioritization", META_TYPE_BYTE, 1},
};

static item_info_t g_ohosDeviceExposure[OHOS_DEVICE_EXPOSURE_END - OHOS_DEVICE_EXPOSURE_START] = {
    [OHOS_ABILITY_DEVICE_AVAILABLE_EXPOSUREMODES -
        OHOS_DEVICE_EXPOSURE_START] = {"exposureAvailableModes",  META_TYPE_BYTE,          -1},
    [OHOS_CONTROL_EXPOSUREMODE - OHOS_DEVICE_EXPOSURE_START] = {"exposureMode",            META_TYPE_BYTE, 1 },
    [OHOS_ABILITY_EXPOSURE_MODES - OHOS_DEVICE_EXPOSURE_START] = {"exposureSupportiveModes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_EXPOSURE_MODE - OHOS_DEVICE_EXPOSURE_START] = {"exMode",                  META_TYPE_BYTE, 1 },
    [OHOS_ABILITY_METER_MODES - OHOS_DEVICE_EXPOSURE_START] = {"meterAvailableModes",     META_TYPE_BYTE, -1},
    [OHOS_ABILITY_SCENE_EXPOSURE_MODES -
        OHOS_DEVICE_EXPOSURE_START] = {"sceneExposureSupportiveModes", META_TYPE_BYTE, -1},
    [OHOS_ABILITY_EXPOSURE_TIME - OHOS_DEVICE_EXPOSURE_START] = {"abilityExposureTime", META_TYPE_INT32, -1},
    [OHOS_ABILITY_AE_LOCK - OHOS_DEVICE_EXPOSURE_START] = {"abilityAELock", META_TYPE_BYTE, -1},
};

static item_info_t g_ohosDeviceFocus[OHOS_DEVICE_FOCUS_END - OHOS_DEVICE_FOCUS_START] = {
    [OHOS_ABILITY_DEVICE_AVAILABLE_FOCUSMODES -
        OHOS_DEVICE_FOCUS_START] = {"focusAvailablesModes", META_TYPE_BYTE,  -1},
    [OHOS_CONTROL_FOCUSMODE - OHOS_DEVICE_FOCUS_START] = {"focusMode",            META_TYPE_BYTE,  1 },
    [OHOS_ABILITY_FOCUS_MODES - OHOS_DEVICE_FOCUS_START] = {"focusSupportiveModes", META_TYPE_BYTE,  -1},
    [OHOS_CONTROL_FOCUS_MODE - OHOS_DEVICE_FOCUS_START] = {"fMode",                META_TYPE_BYTE,  1 },
    [OHOS_ABILITY_FOCAL_LENGTH - OHOS_DEVICE_FOCUS_START] = {"focalLength",          META_TYPE_FLOAT, 1 },
    [OHOS_ABILITY_SCENE_FOCUS_MODES - OHOS_DEVICE_FOCUS_START] = {"sceneFocusSupportiveModes", META_TYPE_BYTE, -1},
    [OHOS_ABILITY_FOCUS_ASSIST_FLASH_SUPPORTED_MODES -
        OHOS_DEVICE_FOCUS_START] = {"focusAssistFlashSupportedModes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_FOCUS_ASSIST_FLASH_SUPPORTED_MODE -
        OHOS_DEVICE_FOCUS_START] = {"sceneFocusSupportiveModes", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_LENS_INFO_MINIMUM_FOCUS_DISTANCE -
        OHOS_DEVICE_FOCUS_START] = {"lensInfoMinimumFocusDistance", META_TYPE_FLOAT, 1},
    [OHOS_CONTROL_LENS_FOCUS_DISTANCE - OHOS_DEVICE_FOCUS_START] = {"lensFocusDistance", META_TYPE_FLOAT, 1},
    [OHOS_ABILITY_EQUIVALENT_FOCUS - OHOS_DEVICE_FOCUS_START] = {"equivalentFocus", META_TYPE_INT32, -1},
    [OHOS_CONTROL_FOCUS_DISTANCE -
        OHOS_DEVICE_FOCUS_START] = {"controlFocusDistance", META_TYPE_FLOAT, 1},
    [OHOS_ABILITY_FOCUS_RANGE_TYPES - OHOS_DEVICE_FOCUS_START] = {"focusRangeTypes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_FOCUS_RANGE_TYPE - OHOS_DEVICE_FOCUS_START] = {"focusRangeType", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_FOCUS_TRACKING_MODE - OHOS_DEVICE_FOCUS_START] = {"focusTrackingMode", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_FOCUS_TRACKING_REGION - OHOS_DEVICE_FOCUS_START] = {"focusTrackingRegion", META_TYPE_INT32, -1},
    [OHOS_ABILITY_FOCUS_DRIVEN_TYPES - OHOS_DEVICE_FOCUS_START] = {"focusDrivenTypes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_FOCUS_DRIVEN_TYPE - OHOS_DEVICE_FOCUS_START] = {"focusDrivenType", META_TYPE_BYTE, 1},
};

static item_info_t g_ohosDeviceWhite[OHOS_DEVICE_WHITE_BLANCE_END - OHOS_DEVICE_WHITE_BLANCE_START] = {
    [OHOS_ABILITY_AWB_MODES - OHOS_DEVICE_WHITE_BLANCE_START] = {"whiteAvailablesModes", META_TYPE_BYTE,  -1},
    [OHOS_ABILITY_AWB_LOCK - OHOS_DEVICE_WHITE_BLANCE_START] = {"abilityAWBLock",            META_TYPE_BYTE,  1 },
};

static item_info_t g_ohosDeviceFlash[OHOS_DEVICE_FLASH_END - OHOS_DEVICE_FLASH_START] = {
    [OHOS_ABILITY_DEVICE_AVAILABLE_FLASHMODES - OHOS_DEVICE_FLASH_START] = {"flashAvailablesModes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_FLASHMODE - OHOS_DEVICE_FLASH_START] = {"flashMode",            META_TYPE_BYTE, 1 },
    [OHOS_ABILITY_FLASH_MODES - OHOS_DEVICE_FLASH_START] = {"flashSupportiveModes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_FLASH_MODE - OHOS_DEVICE_FLASH_START] = {"flaMode",              META_TYPE_BYTE, 1 },
    [OHOS_CONTROL_FLASH_STATE - OHOS_DEVICE_FLASH_START] = {"flashstate",           META_TYPE_BYTE, 1 },
    [OHOS_ABILITY_SCENE_FLASH_MODES - OHOS_DEVICE_FLASH_START] = {"sceneFlashSupportiveModes", META_TYPE_BYTE, -1},
};

static item_info_t g_ohosDeviceZoom[OHOS_DEVICE_ZOOM_END - OHOS_DEVICE_ZOOM_START] = {
    [OHOS_ABILITY_ZOOM_RATIO_RANGE - OHOS_DEVICE_ZOOM_START] = {"zoomRange",      META_TYPE_FLOAT, -1},
    [OHOS_CONTROL_ZOOM_RATIO - OHOS_DEVICE_ZOOM_START] = {"zoomRatio",      META_TYPE_FLOAT, 1 },
    [OHOS_CONTROL_ZOOM_CROP_REGION - OHOS_DEVICE_ZOOM_START] = {"zoomCropRegion", META_TYPE_INT32, -1},
    [OHOS_ABILITY_ZOOM_CAP - OHOS_DEVICE_ZOOM_START] = {"zoomCap",        META_TYPE_INT32, -1},
    [OHOS_ABILITY_SCENE_ZOOM_CAP - OHOS_DEVICE_ZOOM_START] = {"sceneZoomCap",   META_TYPE_INT32, -1},
    [OHOS_STATUS_CAMERA_CURRENT_ZOOM_RATIO -
        OHOS_DEVICE_ZOOM_START] = {"currentStatusZoomRatio", META_TYPE_UINT32, 1},
    [OHOS_CONTROL_SMOOTH_ZOOM_RATIOS - OHOS_DEVICE_ZOOM_START] = {"controlZoomRatios",   META_TYPE_UINT32, -1},
    [OHOS_CONTROL_PREPARE_ZOOM - OHOS_DEVICE_ZOOM_START] = {"controlPreZoom",   META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAMERA_ZOOM_PERFORMANCE - OHOS_DEVICE_ZOOM_START] = {"zoomPerformance",   META_TYPE_UINT32, -1},

};

static item_info_t g_ohosStreamAbility[OHOS_STREAM_ABILITY_END - OHOS_STREAM_ABILITY_START] = {
    [OHOS_ABILITY_STREAM_AVAILABLE_BASIC_CONFIGURATIONS -
        OHOS_STREAM_ABILITY_START] = {"streamAvailableConfigurations", META_TYPE_INT32, -1},
    [OHOS_STREAM_AVAILABLE_FORMATS -
        OHOS_STREAM_ABILITY_START] = {"streamAvailableFormats",        META_TYPE_INT32, -1},
    [OHOS_ABILITY_STREAM_AVAILABLE_EXTEND_CONFIGURATIONS -
        OHOS_STREAM_ABILITY_START] = {"streamExtendConfigurations",    META_TYPE_INT32, -1},
    [OHOS_ABILITY_STREAM_QUICK_THUMBNAIL_AVAILABLE -
        OHOS_STREAM_ABILITY_START] = {"streamQuickThumbnailAvailable", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_PORTRAIT_RESOLUSION -
        OHOS_STREAM_ABILITY_START] = {"streamPortraitResolusion", META_TYPE_INT32, -1},
    [OHOS_ABILITY_SCENE_STREAM_QUICK_THUMBNAIL_AVAILABLE -
        OHOS_STREAM_ABILITY_START] = {"sceneStreamQuickThumbnailAvailable", META_TYPE_BYTE, -1},
    [OHOS_ABILITY_DEFERRED_IMAGE_DELIVERY -
        OHOS_STREAM_ABILITY_START] = {"deferredImageDeliverySupportModes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_DEFERRED_IMAGE_DELIVERY -
        OHOS_STREAM_ABILITY_START] = {"deferredImageDeliveryMode", META_TYPE_BYTE, -1},
};

static item_info_t g_ohosStreamJpeg[OHOS_STREAM_JPEG_END - OHOS_STREAM_JPEG_START] = {
    [OHOS_JPEG_GPS_COORDINATES - OHOS_STREAM_JPEG_START] = {"gpsCoordinates",          META_TYPE_DOUBLE, -1},
    [OHOS_JPEG_GPS_PROCESSING_METHOD - OHOS_STREAM_JPEG_START] = {"gpsProcessingMethod",     META_TYPE_BYTE,   1 },
    [OHOS_JPEG_GPS_TIMESTAMP - OHOS_STREAM_JPEG_START] = {"gpsTimestamp",            META_TYPE_INT64,  1 },
    [OHOS_JPEG_ORIENTATION - OHOS_STREAM_JPEG_START] = {"jpegOrientation",             META_TYPE_INT32,  1 },
    [OHOS_JPEG_QUALITY - OHOS_STREAM_JPEG_START] = {"quality",                 META_TYPE_BYTE,   1 },
    [OHOS_JPEG_THUMBNAIL_QUALITY - OHOS_STREAM_JPEG_START] = {"thumbnailQuality",        META_TYPE_BYTE,   1 },
    [OHOS_JPEG_THUMBNAIL_SIZE - OHOS_STREAM_JPEG_START] = {"thumbnailSize",           META_TYPE_INT32,  -1},
    [OHOS_JPEG_AVAILABLE_THUMBNAIL_SIZES - OHOS_STREAM_JPEG_START] = {"availableThumbnailSizes", META_TYPE_INT32,  -1},
    [OHOS_JPEG_MAX_SIZE - OHOS_STREAM_JPEG_START] = {"maxSize",                 META_TYPE_INT32,  1 },
    [OHOS_JPEG_SIZE - OHOS_STREAM_JPEG_START] = {"size",                    META_TYPE_INT32,  1 },
};

static item_info_t g_ohosStreamVideo[OHOS_STREAM_VIDEO_END - OHOS_STREAM_VIDEO_START] = {
    [OHOS_ABILITY_VIDEO_STABILIZATION_MODES -
        OHOS_STREAM_VIDEO_START] = {"videoAvailableStabilizationModes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_VIDEO_STABILIZATION_MODE -
        OHOS_STREAM_VIDEO_START] = {"videoStabilizationMode",           META_TYPE_BYTE, 1 },
    [OHOS_CONTROL_VIDEO_DEBUG_SWITCH -
        OHOS_STREAM_VIDEO_START] = {"videoDebugSwitch",           META_TYPE_BYTE, 1 },
};

static item_info_t g_ohosPostProcess[OHOS_CAMERA_EFFECT_END - OHOS_CAMERA_EFFECT_START] {
    [OHOS_ABILITY_SCENE_FILTER_TYPES -
        OHOS_CAMERA_EFFECT_START] = {"sceneAvailableFilterTypes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_FILTER_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"filterType", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_SCENE_PORTRAIT_EFFECT_TYPES -
        OHOS_CAMERA_EFFECT_START] = {"sceneAvailablePotraitTypes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_PORTRAIT_EFFECT_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"portraitType", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_SCENE_BEAUTY_TYPES -
        OHOS_CAMERA_EFFECT_START] = {"sceneAvailableBeautyTypes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_BEAUTY_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"beautyType", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_BEAUTY_AUTO_VALUES -
        OHOS_CAMERA_EFFECT_START] = {"availableAutoBeautyValues", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_BEAUTY_AUTO_VALUE -
        OHOS_CAMERA_EFFECT_START] = {"autoBeautyValue", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_BEAUTY_FACE_SLENDER_VALUES -
        OHOS_CAMERA_EFFECT_START] = {"availableFaceSlenderValues", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_BEAUTY_FACE_SLENDER_VALUE -
        OHOS_CAMERA_EFFECT_START] = {"faceSlenderValue", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_BEAUTY_SKIN_SMOOTH_VALUES -
        OHOS_CAMERA_EFFECT_START] = {"availableSkinSmoothValues", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_BEAUTY_SKIN_SMOOTH_VALUE -
        OHOS_CAMERA_EFFECT_START] = {"skinSmoothValue", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_BEAUTY_SKIN_TONE_VALUES -
        OHOS_CAMERA_EFFECT_START] = {"availableSkinToneValues", META_TYPE_INT32, -1},
    [OHOS_CONTROL_BEAUTY_SKIN_TONE_VALUE -
        OHOS_CAMERA_EFFECT_START] = {"skinToneValue", META_TYPE_INT32, 1},
    [OHOS_ABILITY_CAMERA_MACRO_SUPPORTED -
        OHOS_CAMERA_EFFECT_START] = {"macroSupportedValue", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_SCENE_MACRO_CAP -
        OHOS_CAMERA_EFFECT_START] = {"sceneMacroCap", META_TYPE_INT32, -1},
    [OHOS_CAMERA_MACRO_STATUS -
        OHOS_CAMERA_EFFECT_START] = {"macroStatusValue", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_CAMERA_MACRO -
        OHOS_CAMERA_EFFECT_START] = {"macroStatusControlValue", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAMERA_VIRTUAL_APERTURE_RANGE -
        OHOS_CAMERA_EFFECT_START] = {"cameraVirtualApertureRange", META_TYPE_FLOAT, -1},
    [OHOS_CONTROL_CAMERA_VIRTUAL_APERTURE_VALUE -
        OHOS_CAMERA_EFFECT_START] = {"cameraVirtualApertureControlValue", META_TYPE_FLOAT, 1},
    [OHOS_ABILITY_CAMERA_PHYSICAL_APERTURE_RANGE -
        OHOS_CAMERA_EFFECT_START] = {"cameraPhysicalApertureRange", META_TYPE_FLOAT, -1},
    [OHOS_CONTROL_CAMERA_PHYSICAL_APERTURE_VALUE -
        OHOS_CAMERA_EFFECT_START] = {"cameraPhysicalApertureControlValue", META_TYPE_FLOAT, 1},
    [OHOS_STATUS_CAMERA_APERTURE_VALUE -
        OHOS_CAMERA_EFFECT_START] = {"currentCameraApertureValue", META_TYPE_FLOAT, 1},
    [OHOS_DEVICE_EXITCAMERA_EVENT - OHOS_CAMERA_EFFECT_START] = {"exitCameraEvent", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_MOTION_DETECTION_CHECK_AREA -
        OHOS_CAMERA_EFFECT_START] = {"superSlowMotionCheckArea", META_TYPE_FLOAT, -1},
    [OHOS_STATUS_SLOW_MOTION_DETECTION -
        OHOS_CAMERA_EFFECT_START] = {"superSlowMotionStatus", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_MOTION_DETECTION_SUPPORT -
        OHOS_CAMERA_EFFECT_START] = {"motionDetectionSupportValue", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_MOTION_DETECTION -
        OHOS_CAMERA_EFFECT_START] = {"motionDetectionControlValue", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_EXPOSURE_HINT_SUPPORTED - OHOS_CAMERA_EFFECT_START] = {"exposureHintSupported", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_EXPOSURE_HINT_MODE - OHOS_CAMERA_EFFECT_START] = {"exposureHintMode", META_TYPE_BYTE, 1},
    [OHOS_STATUS_ALGO_MEAN_Y - OHOS_CAMERA_EFFECT_START] = {"algoMeanY", META_TYPE_UINT32, 1},
    [OHOS_STATUS_PREVIEW_PHYSICAL_CAMERA_ID -
        OHOS_CAMERA_EFFECT_START] = {"previewPhysicalCameraId", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAPTURE_EXPECT_TIME -
        OHOS_CAMERA_EFFECT_START] = {"captureExpectTime", META_TYPE_UINT32, -1},
    [OHOS_ABILITY_EFFECT_SUGGESTION_SUPPORTED -
	    OHOS_CAMERA_EFFECT_START] = {"effectSuggestionSupported", META_TYPE_INT32, -1},
    [OHOS_CONTROL_EFFECT_SUGGESTION -
        OHOS_CAMERA_EFFECT_START] = {"effectSuggestion", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_EFFECT_SUGGESTION_DETECTION -
        OHOS_CAMERA_EFFECT_START] = {"effectSuggestionDetection", META_TYPE_BYTE, -1},
    [OHOS_CAMERA_EFFECT_SUGGESTION_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"effectSuggestionType", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_EFFECT_SUGGESTION_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"controlEffectSuggestionType", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_AVAILABLE_PROFILE_LEVEL -
        OHOS_CAMERA_EFFECT_START] = {"availableProfileLevel", META_TYPE_INT32, -1},
    [OHOS_ABILITY_AVAILABLE_PREVIEW_PROFILE -
        OHOS_CAMERA_EFFECT_START] = {"availablePreviewProfile", META_TYPE_INT32, -1},
    [OHOS_ABILITY_AVAILABLE_PHOTO_PROFILE -
        OHOS_CAMERA_EFFECT_START] = {"availablePhotoProfile", META_TYPE_INT32, -1},
    [OHOS_ABILITY_AVAILABLE_VIDEO_PROFILE -
        OHOS_CAMERA_EFFECT_START] = {"availableVideoProfile", META_TYPE_INT32, -1},
    [OHOS_ABILITY_AVAILABLE_METADATA_PROFILE -
        OHOS_CAMERA_EFFECT_START] = {"availableMetadataProfile", META_TYPE_INT32, -1},
    [OHOS_ABILITY_AVAILABLE_CONFIGURATIONS -
        OHOS_CAMERA_EFFECT_START] = {"availableConfigurations", META_TYPE_INT32, -1},
    [OHOS_ABILITY_CONFLICT_CONFIGURATIONS -
        OHOS_CAMERA_EFFECT_START] = {"conflictConfigurations", META_TYPE_INT32, -1},
    [OHOS_ABILITY_LIGHT_PAINTING_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"lightPaintingType", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_LIGHT_PAINTING_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"controlLightPaintingType", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_LIGHT_PAINTING_FLASH -
        OHOS_CAMERA_EFFECT_START] = {"controlLightPaintingFlash", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_TIME_LAPSE_INTERVAL -
        OHOS_CAMERA_EFFECT_START] = {"timeLapseInterval", META_TYPE_UINT32, 1},
    [OHOS_CONTROL_TIME_LAPSE_TRYAE_STATE -
        OHOS_CAMERA_EFFECT_START] = {"timeLapseTryaeState", META_TYPE_BYTE, 1},
    [OHOS_STATUS_TIME_LAPSE_PREVIEW_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"timeLapsePreviewType", META_TYPE_BYTE, 1},
    [OHOS_STATUS_TIME_LAPSE_TRYAE_HINT -
        OHOS_CAMERA_EFFECT_START] = {"timeLapseTryaeHint", META_TYPE_BYTE, 1},
    [OHOS_STATUS_TIME_LAPSE_CAPTURE_INTERVAL -
        OHOS_CAMERA_EFFECT_START] = {"timeLapseCaptureInterval", META_TYPE_UINT32, 1},
    [OHOS_STATUS_TIME_LAPSE_TRYAE_DONE -
        OHOS_CAMERA_EFFECT_START] = {"timeLapseTryaeDone", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_TIME_LAPSE_RECORD_STATE -
        OHOS_CAMERA_EFFECT_START] = {"timeLapseRecordState", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_TIME_LAPSE_PREVIEW_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"controlTimeLapsePreviewType", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_TIME_LAPSE_INTERVAL_RANGE -
        OHOS_CAMERA_EFFECT_START] = {"timeLapseIntervalRange", META_TYPE_UINT32, 1},
    [OHOS_ABILITY_LCD_FLASH -
        OHOS_CAMERA_EFFECT_START] = {"lcdFlash", META_TYPE_INT32, -1},
    [OHOS_CONTROL_LCD_FLASH_DETECTION -
        OHOS_CAMERA_EFFECT_START] = {"lcdFlashDetection", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_LCD_FLASH -
        OHOS_CAMERA_EFFECT_START] = {"controlLcdFlash", META_TYPE_BYTE, 1},
    [OHOS_STATUS_LCD_FLASH_STATUS -
        OHOS_CAMERA_EFFECT_START] = {"lcdFlashStatus", META_TYPE_INT32, 1},
    [OHOS_ABILITY_DEPTH_DATA_DELIVERY -
        OHOS_CAMERA_EFFECT_START] = {"depthDataDelivery", META_TYPE_INT32, -1},
    [OHOS_CONTROL_DEPTH_DATA_DELIVERY_SWITCH -
        OHOS_CAMERA_EFFECT_START] = {"depthDataDeliverySwitch", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_DEPTH_DATA_PROFILES -
        OHOS_CAMERA_EFFECT_START] = {"depthDataProfiles", META_TYPE_INT32, -1},
    [OHOS_CONTROL_DEPTH_DATA_ACCURACY -
        OHOS_CAMERA_EFFECT_START] = {"depthDataAccuracy", META_TYPE_INT32, -1},
    [OHOS_ABILITY_CAPTURE_MACRO_DEPTH_FUSION_SUPPORTED -
        OHOS_CAMERA_EFFECT_START] = {"captureMacroDepthFusionSupported", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAPTURE_MACRO_DEPTH_FUSION_ZOOM_RANGE -
        OHOS_CAMERA_EFFECT_START] = {"captureMacroDepthFussionZoomRange", META_TYPE_FLOAT, -1},
    [OHOS_CONTROL_CAPTURE_MACRO_DEPTH_FUSION -
        OHOS_CAMERA_EFFECT_START] = {"captureMacroDepthFusion", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAMERA_PORTRAIT_THEME_SUPPORTED -
        OHOS_CAMERA_EFFECT_START] = {"isPortraitThemeTypesSupported", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAMERA_PORTRAIT_THEME_TYPES -
        OHOS_CAMERA_EFFECT_START] = {"supportedPortraitThemeTypes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_CAMERA_PORTRAIT_THEME_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"portraitThemeType", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAMERA_VIDEO_ROTATION_SUPPORTED -
        OHOS_CAMERA_EFFECT_START] = {"isVideoRotationSupported", META_TYPE_BYTE, 1},
    [OHOS_ABILITY_CAMERA_VIDEO_ROTATION -
        OHOS_CAMERA_EFFECT_START] = {"supportedVideoRotation", META_TYPE_INT32, -1},
    [OHOS_CONTROL_CAMERA_VIDEO_ROTATION -
        OHOS_CAMERA_EFFECT_START] = {"videoRotation", META_TYPE_INT32, 1},
    [OHOS_MOVING_PHOTO_BUFFER_DURATION -
        OHOS_CAMERA_EFFECT_START] = {"movingPhotoBufferDuration", META_TYPE_UINT32, 1},
    [OHOS_MOVING_PHOTO_START -
        OHOS_CAMERA_EFFECT_START] = {"movingPhotoStart", META_TYPE_INT64, 1},
    [OHOS_MOVING_PHOTO_END -
        OHOS_CAMERA_EFFECT_START] = {"movingPhotoEnd", META_TYPE_INT64, 1},
    [OHOS_ABILITY_COLOR_RESERVATION_TYPES -
        OHOS_CAMERA_EFFECT_START] = {"colorReservationTypes", META_TYPE_BYTE, -1},
    [OHOS_CONTROL_COLOR_RESERVATION_TYPE -
        OHOS_CAMERA_EFFECT_START] = {"colorReservationType", META_TYPE_BYTE, 1},
};

static item_info_t g_ohosCameraSecure[OHOS_CAMERA_SECURE_END - OHOS_CAMERA_SECURE_START] = {
    [OHOS_CONTROL_SECURE_FACE_MODE -
        OHOS_CAMERA_SECURE_START] = {"secureFaceMode", META_TYPE_INT32, 1},
    [OHOS_CONTROL_SECURE_FACE_INFO -
        OHOS_CAMERA_SECURE_START] = {"secureFaceInfo", META_TYPE_INT32, -1},
    [OHOS_CONTROL_SECURE_FACE_AUTH_RESULT -
        OHOS_CAMERA_SECURE_START] = {"faceAuthResult", META_TYPE_INT32, 1},
    [OHOS_CONTROL_SECURE_FLASH_SEQ -
        OHOS_CAMERA_SECURE_START] = {"secureFlashSeq", META_TYPE_INT32, -1},
    [OHOS_CONTROL_SECURE_IR_LED_SWITCH -
        OHOS_CAMERA_SECURE_START] = {"irLedSwitch", META_TYPE_BYTE, 1},
    [OHOS_CONTROL_SECURE_IR_LOCKAE_SWITCH -
        OHOS_CAMERA_SECURE_START] = {"irLockaeSwitch", META_TYPE_BYTE, 1},
};

static item_info_t g_ohosCameraXmage[OHOS_XMAGE_COLOR_MODES_END - OHOS_XMAGE_COLOR_MODES_START] = {
    [OHOS_ABILITY_SUPPORTED_COLOR_MODES -
        OHOS_XMAGE_COLOR_MODES_START] = {"cameraXmageSupportMode",  META_TYPE_BYTE,  1},
    [OHOS_CONTROL_SUPPORTED_COLOR_MODES -
        OHOS_XMAGE_COLOR_MODES_START] = {"cameraXmageControlMode",  META_TYPE_BYTE,  1},
};


const static item_info_t *g_ohosItemInfo[OHOS_SECTION_COUNT] = {
    g_ohosCameraProperties,
    g_ohosCameraSensor,
    g_ohosCameraSensorInfo,
    g_ohosCameraStatistics,
    g_ohosCameraControl,
    g_ohosDeviceExposure,
    g_ohosDeviceFocus,
    g_ohosDeviceWhite,
    g_ohosDeviceFlash,
    g_ohosDeviceZoom,
    g_ohosStreamAbility,
    g_ohosStreamJpeg,
    g_ohosStreamVideo,
    g_ohosPostProcess,
    g_ohosCameraSecure,
    g_ohosCameraXmage,
};
} // namespace Camera
#endif /* CAMERA_METADATA_ITEM_INFO_H */
