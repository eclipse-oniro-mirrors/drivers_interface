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

#ifndef CAMERA_DEVICE_ABILITY_ITEMS_H
#define CAMERA_DEVICE_ABILITY_ITEMS_H

typedef enum camera_ability_section {
    // Camera attribute information: position(facing), type, connection, description, sensor, lens description
    OHOS_CAMERA_PROPERTIES = 0,
    OHOS_CAMERA_LENS,
    OHOS_CAMERA_SENSOR,
    OHOS_CAMERA_SENSOR_INFO,
    OHOS_CAMERA_STATISTICS,

    // Camera device image acquisition
    OHOS_DEVICE_CONTROL = 0x1000, // Overall control, such as turning off automatic 3A, operating mode
    OHOS_DEVICE_EXPOSURE,
    OHOS_DEVICE_FOCUS,
    OHOS_DEVICE_WHITE_BLANCE,
    OHOS_DEVICE_FLASH,
    OHOS_DEVICE_ZOOM,

    // Camera effects & algorithms
    OHOS_CAMERA_EFFECT = 0x2000,

    // Camera flow control related
    OHOS_STREAM_ABILITY = 0x3000,
    OHOS_STREAM_CONTROL, // General control: frame rate, resolution, mirroring
    OHOS_STREAM_JPEG,
    OHOS_STREAM_VIDEO, // Video encoding related
    OHOS_STREAM_DEPTH,
    OHOS_STREAM_METADATA,
    OHOS_STREAM_METADATA_FACE,
    OHOS_STREAM_METADATA_BODY,

    // Secure camera control related
    OHOS_CAMERA_SECURE = 0x4000,
    // Xmage camera ability
    OHOS_XMAGE_COLOR_ABILITY = 0x5000,

    OHOS_ABILITY_SECTION_END = 0x6000,

    // Start vendor tag section
    OHOS_VENDOR_SECTION = 0X8000
} camera_ability_section_t;

typedef enum camera_device_metadata_section_start {
    OHOS_CAMERA_PROPERTIES_START = OHOS_CAMERA_PROPERTIES << 16,
    OHOS_CAMERA_LENS_START = OHOS_CAMERA_LENS << 16,
    OHOS_CAMERA_SENSOR_START = OHOS_CAMERA_SENSOR << 16,
    OHOS_CAMERA_SENSOR_INFO_START = OHOS_CAMERA_SENSOR_INFO << 16,
    OHOS_CAMERA_STATISTICS_START = OHOS_CAMERA_STATISTICS << 16,

    OHOS_DEVICE_CONTROL_START = OHOS_DEVICE_CONTROL << 16,
    OHOS_DEVICE_EXPOSURE_START = OHOS_DEVICE_EXPOSURE << 16,
    OHOS_DEVICE_FOCUS_START = OHOS_DEVICE_FOCUS << 16,
    OHOS_DEVICE_WHITE_BLANCE_START = OHOS_DEVICE_WHITE_BLANCE << 16,
    OHOS_DEVICE_FLASH_START = OHOS_DEVICE_FLASH << 16,
    OHOS_DEVICE_ZOOM_START = OHOS_DEVICE_ZOOM << 16,

    OHOS_CAMERA_EFFECT_START = OHOS_CAMERA_EFFECT << 16,

    OHOS_STREAM_ABILITY_START = OHOS_STREAM_ABILITY << 16,
    OHOS_STREAM_CONTROL_START = OHOS_STREAM_CONTROL << 16,
    OHOS_STREAM_JPEG_START = OHOS_STREAM_JPEG << 16,
    OHOS_STREAM_VIDEO_START = OHOS_STREAM_VIDEO << 16,
    OHOS_STREAM_DEPTH_START = OHOS_STREAM_DEPTH << 16,
    OHOS_STREAM_METADATA_START = OHOS_STREAM_METADATA << 16,
    OHOS_STREAM_METADATA_FACE_START = OHOS_STREAM_METADATA_FACE << 16,
    OHOS_STREAM_METADATA_BODY_START = OHOS_STREAM_METADATA_BODY << 16,

    OHOS_CAMERA_SECURE_START = OHOS_CAMERA_SECURE << 16,

    OHOS_XMAGE_COLOR_MODES_START = OHOS_XMAGE_COLOR_ABILITY << 16,
    OHOS_VENDOR_SECTION_START = OHOS_VENDOR_SECTION << 16,
} camera_device_info_section_start_t;

typedef enum camera_device_metadata_tag {
    // Camera attribute related item
    /**
     * ohos.ability.cameraPositon [static, enum, public]
     *
     * camera property, report current camera position
     * (i.e. enum: FRONT/BACK/OTHER ...)
     */
    OHOS_ABILITY_CAMERA_POSITION = OHOS_CAMERA_PROPERTIES_START,
    /**
     * ohos.ability.cameraType [static, enum, public]
     *
     * camera property, report current camera type
     * (i.e. enum: WIDE_ANGLE/ULTRA_WIDE/TELTPHOTO/TRUE_DEAPTH/LOGICAL/UNSPECIFIED ...)
     */
    OHOS_ABILITY_CAMERA_TYPE,
    /**
     * ohos.ability.cameraConnectionType [static, enum, public]
     *
     * camera property, report current camera connection type
     * (i.e. enum: BUILTIN/USB_PLUGIN/REMOTE ...)
     */
    OHOS_ABILITY_CAMERA_CONNECTION_TYPE,
    /**
     * ohos.ability.memoryType [static, enum, public]
     *
     * camera property, report current camera memory type
     * (i.e. enum: mmap/userptr/overlay/dmabuf ...)
     */
    OHOS_ABILITY_MEMORY_TYPE,
    /**
     * ohos.ability.fpsRanges [static, int32[], public]
     *
     * camera property, report current camera support frame/second range
     * (i.e. int32[]: rangeMin1, rangeMax1, rangeMin2, rangeMax2, ...)
     */
    OHOS_ABILITY_FPS_RANGES,
    /**
     * ohos.ability.flashAvailable [static, enum, public]
     *
     * camera property, report current camera flash on/off available
     * (i.e. enum: false/true)
     */
    OHOS_ABILITY_FLASH_AVAILABLE,
    /**
     * ohos.camera.streamId [static, int32[], public]
     *
     * camera property, set current camera stream id
     * (i.e. int32[]: streamId, streamId, ...)
     */
    OHOS_CAMERA_STREAM_ID,
    /**
     * ohos.ability.prelaunchAvailable [static, enum, public]
     *
     * camera property, report current camera device prelaunch supported
     * (i.e. enum: enable/disable..)
     */
    OHOS_ABILITY_PRELAUNCH_AVAILABLE,
    /**
     * ohos.ability.customVideoFps [static, int32[], public]
     *
     * camera property, report current camera support custom opreationMode video fps range
     * (i.e. int32[] ... )
     */
    OHOS_ABILITY_CUSTOM_VIDEO_FPS,
    /**
     * ohos.ability.cameraModes [static, enum[], public]
     *
     * camera property, report current camera support camera mode
     * (i.e. enum[]: capture, video ...)
     */
    OHOS_ABILITY_CAMERA_MODES,
    /**
     * ohos.ability.sketchEnableRatio [static, float[], public]
     *
     * camera property, report current camera device sketch camera mode support ratio
     * (i.e. float[]: mode, ratio, mode, ratio, ...)
     */
    OHOS_ABILITY_SKETCH_ENABLE_RATIO,
    /**
     * ohos.ability.sketchReferenceFovRatio [static, float[], public]
     *
     * camera property, report current camera device sketch camera mode enable ratio
     * (i.e. float[]: mode, ratio, mode, ratio, ...)
     */
    OHOS_ABILITY_SKETCH_REFERENCE_FOV_RATIO,
    /**
     * ohos.ability.cameraFoldScreen [static, enum, public]
     *
     * camera property, report current camera device flod screen
     * (i.e. enum: other/inner/outer ...)
     */
    OHOS_ABILITY_CAMERA_FOLDSCREEN_TYPE,
    /**
     * ohos.ability.availableColorSpaces [static, int32[], public]
     *
     * camera property, report current camera device support color spaces
     * (i.e. int32[]: mode, colorSpaces[], -1, mode, colorSpaces[], -1, ...)
     */
    OHOS_ABILITY_AVAILABLE_COLOR_SPACES,
    /**
     * ohos.ability.nightModeSupportedExposureTime [static, int32[], public]
     *
     * camera property, report current camera device the shutter duration supported by the night mode
     * (i.e. int32[]: time (millisecond), time, ...)
     */
    OHOS_ABILITY_NIGHT_MODE_SUPPORTED_EXPOSURE_TIME,
    /**
     * ohos.camera.mesureExposureTime [static, uint32, public]
     *
     * camera property, report current camera device long exposure time by the night mode
     * (i.e. uint32: time(millisecond) ...)
     */
    OHOS_CAMERA_MESURE_EXPOSURE_TIME,
    /**
     * ohos.camera.exposureModePreviewState [static, uint32, public]
     *
     * camera property, report current camera device exposure mode perview state by the night mode
     * (i.e. uint32 ...)
     */
    OHOS_CAMERA_EXPOSURE_MODE_PREVIEW_STATE,
    /**
     * ohos.camera.userId [static, int32[], public]
     *
     * camera property, set userIds can be delivered during stream creation
     * to identify the user whose images are stored
     * (User IDs are bound when original images are flushed to disks.)
     * (i.e. int32[] ...)
     */
    OHOS_CAMERA_USER_ID,
    /**
     * ohos.ability.moonCaptureBoost [static, uint32[], public]
     *
     * camera property, report current camera device moon-gazing mode
     * (i.e. uint32[] ...)
     */
    OHOS_ABILITY_MOON_CAPTURE_BOOST,
    /**
     * ohos.control.moonCaptureBoost [static, enum, public]
     *
     * camera property, set current camera device moon-gazing mode
     * (i.e. enum: disable/enable ...)
     */
    OHOS_CONTROL_MOON_CAPTURE_BOOST,
    /**
     * ohos.status.moonCaptureDetection [static, uint32, public]
     *
     * camera property, query current camera device detection moon-gazing mode status
     * (i.e. uint32 ...)
     */
    OHOS_STATUS_MOON_CAPTURE_DETECTION,
    /**
     * ohos.ability.captureDurationSupported [static, enum, public]
     *
     * camera property, report current camera device
     * (i.e. enum: support/unsupport ...)
     */
    OHOS_ABILITY_CAPTURE_DURATION_SUPPORTED,
    /**
     * ohos.camera.customSnapshotDuration [static, uint32, public]
     *
     * camera property, query current camera device
     * (i.e. uint32 ...)
     */
    OHOS_CAMERA_CUSTOM_SNAPSHOT_DURATION,
    /**
     * ohos.ability.movingPhoto [static, int32[], public]
     *
     * camera property, report  current camera device different mode whether support living photo
     * (i.e. int32[]: mode, value, -1, ...)
     */
    OHOS_ABILITY_MOVING_PHOTO,
    /**
     * ohos.ability.flashSuggestionSupported [static, uint32[], public]
     *
     * camera property, report current camera whether support flash suggestion
     * (i.e. uint32[]: open/close ...)
     */
    OHOS_ABILITY_FLASH_SUGGESTION_SUPPORTED,
    /**
     * ohos.control.flashSuggestionSwitch [static, enum, public]
     *
     * camera property, set current camera whether support flash suggestion
     * (i.e. enum: support/notSupport ...)
     */
    OHOS_CONTROL_FLASH_SUGGESTION_SWITCH,
    /**
     * ohos.status.flashSuggestion [static, enum, public]
     *
     * camera property, query current camera whether support flash suggestion
     * (i.e. enum: support/notSupport ...)
     */
    OHOS_STATUS_FLASH_SUGGESTION,
    /**
     * ohos.ability.highQualitySupport [static, byte, public]
     *
     * camera property, report current camera whether support high quality
     * (i.e. byte: support/notSupport ...)
     */
    OHOS_ABILITY_HIGH_QUALITY_SUPPORT,
    /**
     * ohos.camera.propertiesEnd
     *
     * camera property end
     */
    OHOS_CAMERA_PROPERTIES_END,

    /**
     * ohos.sensor.exposureTime [static, int64, public]
     *
     * camera device property, query current camera exposure time
     * (i.e. int64 ...)
     */
    OHOS_SENSOR_EXPOSURE_TIME = OHOS_CAMERA_SENSOR_START,
    /**
     * ohos.sensor.colorCorrectionGains [static, float, public]
     *
     * camera device property, query current camera color correction gains
     * (i.e. float ...)
     */
    OHOS_SENSOR_COLOR_CORRECTION_GAINS,
    /**
     * ohos.sensor.orientation [static, int32, public]
     *
     * camera device property, query current camera orientation
     * (i.e. int32 ...)
     */
    OHOS_SENSOR_ORIENTATION,
    /**
     * ohos.ability.muteModes [static, enum[], public]
     *
     * camera device property, report current camera mute modes
     * (i.e. enum[]: OFF, solidColorBlack, ...)
     */
    OHOS_ABILITY_MUTE_MODES,
    /**
     * ohos.control.muteMode [static, enum, public]
     *
     * camera device property, set current camera mute mode
     * (i.e. enum: OFF/solidColorBlack ...)
     */
    OHOS_CONTROL_MUTE_MODE,
    /**
     * ohos.camera.sensorEnd
     *
     * camera sensor endChar
     */
    OHOS_CAMERA_SENSOR_END,

    OHOS_SENSOR_INFO_ACTIVE_ARRAY_SIZE = OHOS_CAMERA_SENSOR_INFO_START,
    OHOS_SENSOR_INFO_SENSITIVITY_RANGE,
    OHOS_SENSOR_INFO_MAX_FRAME_DURATION,
    OHOS_SENSOR_INFO_PHYSICAL_SIZE,
    OHOS_SENSOR_INFO_PIXEL_ARRAY_SIZE,
    OHOS_SENSOR_INFO_TIMESTAMP,
    OHOS_CAMERA_SENSOR_INFO_END,

    OHOS_STATISTICS_FACE_DETECT_MODE = OHOS_CAMERA_STATISTICS_START,
    OHOS_STATISTICS_FACE_DETECT_SWITCH,
    OHOS_STATISTICS_FACE_DETECT_MAX_NUM,
    OHOS_STATISTICS_HISTOGRAM_MODE,
    OHOS_STATISTICS_FACE_IDS,
    OHOS_STATISTICS_FACE_LANDMARKS,
    OHOS_STATISTICS_FACE_RECTANGLES,
    OHOS_STATISTICS_FACE_SCORES,
    OHOS_CAMERA_STATISTICS_END,

    OHOS_CONTROL_AE_ANTIBANDING_MODE = OHOS_DEVICE_CONTROL_START,
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
    OHOS_ABILITY_AE_COMPENSATION_RANGE,
    OHOS_ABILITY_AE_COMPENSATION_STEP,
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
    OHOS_CONTROL_FOCUSED_POINT,
    OHOS_CONTROL_NIGHT_MODE_TRY_AE,
    OHOS_CONTROL_MANUAL_EXPOSURE_TIME,
    OHOS_STATUS_CAMERA_CURRENT_FPS,
    OHOS_ABILITY_ISO_VALUES,
    OHOS_CONTROL_ISO_VALUE,
    OHOS_STATUS_ISO_VALUE,
    OHOS_ABILITY_SENSOR_EXPOSURE_TIME_RANGE,
    OHOS_CONTROL_SENSOR_EXPOSURE_TIME,
    OHOS_STATUS_SENSOR_EXPOSURE_TIME,
    OHOS_CONTROL_MOVING_PHOTO,
    OHOS_ABILITY_SENSOR_WB_VALUES,
    OHOS_CONTROL_SENSOR_WB_VALUE,
    OHOS_CONTROL_HIGH_QUALITY_MODE,
    OHOS_DEVICE_CONTROL_END,

    // Camera device image acquisition related
    OHOS_ABILITY_DEVICE_AVAILABLE_EXPOSUREMODES = OHOS_DEVICE_EXPOSURE_START,
    OHOS_CONTROL_EXPOSUREMODE,
    OHOS_ABILITY_EXPOSURE_MODES,
    OHOS_CONTROL_EXPOSURE_MODE,
    OHOS_ABILITY_METER_MODES,
    OHOS_ABILITY_SCENE_EXPOSURE_MODES,
    OHOS_ABILITY_EXPOSURE_TIME,
    OHOS_ABILITY_AE_LOCK,
    OHOS_DEVICE_EXPOSURE_END,

    OHOS_ABILITY_DEVICE_AVAILABLE_FOCUSMODES = OHOS_DEVICE_FOCUS_START,
    OHOS_CONTROL_FOCUSMODE,
    OHOS_ABILITY_FOCUS_MODES,
    OHOS_CONTROL_FOCUS_MODE,
    OHOS_ABILITY_FOCAL_LENGTH,
    OHOS_ABILITY_SCENE_FOCUS_MODES,
    OHOS_ABILITY_FOCUS_ASSIST_FLASH_SUPPORTED_MODES,
    OHOS_CONTROL_FOCUS_ASSIST_FLASH_SUPPORTED_MODE,
    OHOS_ABILITY_LENS_INFO_MINIMUM_FOCUS_DISTANCE,
    OHOS_CONTROL_LENS_FOCUS_DISTANCE,
    OHOS_ABILITY_EQUIVALENT_FOCUS,
    OHOS_CONTROL_FOCUS_DISTANCE,
    OHOS_DEVICE_FOCUS_END,

    OHOS_ABILITY_DEVICE_AVAILABLE_AWBMODES = OHOS_DEVICE_WHITE_BLANCE_START,
    OHOS_ABILITY_AWB_MODES,
    OHOS_ABILITY_AWB_LOCK,
    OHOS_DEVICE_WHITE_BLANCE_END,

    OHOS_ABILITY_DEVICE_AVAILABLE_FLASHMODES = OHOS_DEVICE_FLASH_START,
    OHOS_CONTROL_FLASHMODE,
    OHOS_ABILITY_FLASH_MODES,
    OHOS_CONTROL_FLASH_MODE,
    OHOS_CONTROL_FLASH_STATE,
    OHOS_ABILITY_SCENE_FLASH_MODES,
    OHOS_DEVICE_FLASH_END,

    OHOS_ABILITY_ZOOM_RATIO_RANGE = OHOS_DEVICE_ZOOM_START,
    OHOS_CONTROL_ZOOM_RATIO,
    OHOS_CONTROL_ZOOM_CROP_REGION,
    OHOS_ABILITY_ZOOM_CAP,
    OHOS_ABILITY_SCENE_ZOOM_CAP,
    OHOS_STATUS_CAMERA_CURRENT_ZOOM_RATIO,
    OHOS_CONTROL_SMOOTH_ZOOM_RATIOS,
    OHOS_CONTROL_PREPARE_ZOOM,
    OHOS_ABILITY_CAMERA_ZOOM_PERFORMANCE,
    OHOS_DEVICE_ZOOM_END,

    // Camera flow control related
    OHOS_ABILITY_STREAM_AVAILABLE_BASIC_CONFIGURATIONS = OHOS_STREAM_ABILITY_START,
    OHOS_STREAM_AVAILABLE_FORMATS,
    OHOS_ABILITY_STREAM_AVAILABLE_EXTEND_CONFIGURATIONS,
    OHOS_ABILITY_STREAM_QUICK_THUMBNAIL_AVAILABLE,
    OHOS_ABILITY_PORTRAIT_RESOLUSION,
    OHOS_ABILITY_SCENE_STREAM_QUICK_THUMBNAIL_AVAILABLE,
    OHOS_ABILITY_DEFERRED_IMAGE_DELIVERY,
    OHOS_CONTROL_DEFERRED_IMAGE_DELIVERY,
    OHOS_STREAM_ABILITY_END,

    OHOS_JPEG_GPS_COORDINATES = OHOS_STREAM_JPEG_START,
    OHOS_JPEG_GPS_PROCESSING_METHOD,
    OHOS_JPEG_GPS_TIMESTAMP,
    OHOS_JPEG_ORIENTATION,
    OHOS_JPEG_QUALITY,
    OHOS_JPEG_THUMBNAIL_QUALITY,
    OHOS_JPEG_THUMBNAIL_SIZE,
    OHOS_JPEG_AVAILABLE_THUMBNAIL_SIZES,
    OHOS_JPEG_MAX_SIZE,
    OHOS_JPEG_SIZE,
    OHOS_STREAM_JPEG_END,

    OHOS_ABILITY_VIDEO_STABILIZATION_MODES = OHOS_STREAM_VIDEO_START,
    OHOS_CONTROL_VIDEO_STABILIZATION_MODE,
    OHOS_CONTROL_VIDEO_DEBUG_SWITCH,
    OHOS_STREAM_VIDEO_END,

    // camera effects & algorithms
    OHOS_ABILITY_SCENE_FILTER_TYPES = OHOS_CAMERA_EFFECT_START,
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
    /**
     * ohos.ability.camera [static, enum, public]
     *
     * camera property, report current camera macro
     * (i.e. enum camera supported/nosupported)
     */
    OHOS_ABILITY_CAMERA_MACRO_SUPPORTED,
    /**
     * ohos.status.camera [static, enum, public]
     *
     * camera property, report current camera macro
     * (i.e. enum camera disbale/enable)
     */
    OHOS_CAMERA_MACRO_STATUS,
    /**
     * ohos.control.camera [static, enum, public]
     *
     * camera property, report current camera macro
     * (i.e. enum camera disbale/enable)
     */
    OHOS_CONTROL_CAMERA_MACRO,
    /**
     * ohos.ability.camera [static, float[], public]
     *
     * camera property, report current camera virtual aperture range
     * (i.e. float[] camera device supported frame)
     */
    OHOS_ABILITY_CAMERA_VIRTUAL_APERTURE_RANGE,
    /**
     * ohos.control.camera [static, float, public]
     *
     * camera property, report current camera virtual aperture value
     * (i.e. float camera device supported frame)
     */
    OHOS_CONTROL_CAMERA_VIRTUAL_APERTURE_VALUE,
    /**
     * ohos.control.camera [static, float[], public]
     *
     * camera property, report current camera physical aprtture range
     * (i.e. float[] camera device supported frame)
     */
    OHOS_ABILITY_CAMERA_PHYSICAL_APERTURE_RANGE,
    /**
     * ohos.control.camera [static, float, public]
     *
     * camera property, report current camera physical aprtture value
     * (i.e. float camera device supported frame)
     */
    OHOS_CONTROL_CAMERA_PHYSICAL_APERTURE_VALUE,
    /**
     * ohos.status.camera [static, float, public]
     *
     * camera property, report current camera physical aperture value
     * (i.e. float camera device supported frame)
     */
    OHOS_STATUS_CAMERA_APERTURE_VALUE,
    /**
     * ohos.status.exitcamera [static, byte, public]
     *
     * camera property, report current camera exitcamera event
     * (i.e. byte camera device exitcamera event)
     */
    OHOS_DEVICE_EXITCAMERA_EVENT,
    /**
     * ohos.control.motion [static, float, public]
     *
     * camera property, report current camera phone screen ratio
     * (i.e. float camera device phone screen ratio)
     */
    OHOS_CONTROL_MOTION_DETECTION_CHECK_AREA,
    /**
     * ohos.status.motion [static, enum, public]
     *
     * camera property, report current camera slow motion recording status
     * (i.e. enum camera disable/ready/start/recording/finish)
     */
    OHOS_STATUS_SLOW_MOTION_DETECTION,
    /**
     * ohos.ability.motion [static, enum, public]
     *
     * camera property, report current camera motion detection
     * (i.e. enum camera device support/nosupport)
     */
    OHOS_ABILITY_MOTION_DETECTION_SUPPORT,
    /**
     * ohos.control.motion [static, enum, public]
     *
     * camera property, report current camera Operation status detection switch
     * (i.e. enum camera device disable/enable)
     */
    OHOS_CONTROL_MOTION_DETECTION,
    /**
     * ohos.ability.exposure [static, byte, public]
     *
     * camera property, report current camera screen exposure
     * (i.e. byte camera device supported frame)
     */
    OHOS_ABILITY_EXPOSURE_HINT_SUPPORTED,
    /**
     * ohos.control.exposure [static, byte, public]
     *
     * camera property, report current camera screen exposure
     * (i.e. byte camera device supported frame)
     */
    OHOS_CONTROL_EXPOSURE_HINT_MODE,
    /**
     * ohos.status.exposure [static, uint32, public]
     *
     * camera property, report current camera screen exposure
     * (i.e. uint32 camera device supported frame)
     */
    OHOS_STATUS_ALGO_MEAN_Y,
    /**
     * ohos.status.preview [static, byte, public]
     *
     * camera property, report current camera preview shot id
     * (i.e. byte camera device supported frame)
     */
    OHOS_STATUS_PREVIEW_PHYSICAL_CAMERA_ID,
    /**
     * ohos.ability.capture [static, uint32[], public]
     *
     * camera property, report current camera expect time
     * (i.e. uint32[] camera device supported frame)
     */
    OHOS_ABILITY_CAPTURE_EXPECT_TIME,
    /**
     * ohos.camera.effectEnd
     *
     * camera effect end
     */
    OHOS_CAMERA_EFFECT_END,

    // camera secure related
    /**
     * ohos.control.secure [static, uint32, public]
     *
     * camera property, report current camera secure face mode
     * (i.e. uint32 camera device supported frame)
     */
    OHOS_CONTROL_SECURE_FACE_MODE = OHOS_CAMERA_SECURE_START,
    /**
     * ohos.control.secure [static, uint32[], public]
     *
     * camera property, report current camera secure facSe info
     * (i.e. uint32[] camera device supported frame)
     */
    OHOS_CONTROL_SECURE_FACE_INFO,
    /**
     * ohos.control.secure [static, uint32, public]
     *
     * camera property, report current camera face auth resuilt
     * (i.e. uint32 camera device supported frame)
     */
    OHOS_CONTROL_SECURE_FACE_AUTH_RESULT,
    /**
     * ohos.control.secure [static, uint32[], public]
     *
     * camera property, report current camera secure flash seq
     * (i.e. uint32[] camera device supported frame)
     */
    OHOS_CONTROL_SECURE_FLASH_SEQ,
    /**
     * ohos.control.secure [static, byte, public]
     *
     * camera property, report current camera IR lens
     * (i.e. byte camera device supported frame)
     */
    OHOS_CONTROL_SECURE_IR_LED_SWITCH,
    /**
     * ohos.control.secure [static, byte, public]
     *
     * camera property, report current camera IR lens lockae
     * (i.e. byte camera device supported frame)
     */
    OHOS_CONTROL_SECURE_IR_LOCKAE_SWITCH,
    /**
     * ohos.camera.secureEnd
     *
     * camera secure end
     */
    OHOS_CAMERA_SECURE_END,

    //XMAGE MODE
    /**
     * ohos.control.supported [static, byte, public]
     *
     * camera property, report current camera color modes
     * (i.e. byte camera device normal/bright/soft/mono)
     */
    OHOS_ABILITY_SUPPORTED_COLOR_MODES = OHOS_XMAGE_COLOR_MODES_START,
    /**
     * ohos.control.supported [static, byte, public]
     *
     * camera property, report current camera color modes
     * (i.e. byte camera device normal/bright/soft/mono)
     */
    OHOS_CONTROL_SUPPORTED_COLOR_MODES,
    /**
     * ohos.xmage.colorMoodesEnd
     *
     * camera xmage end
     */
    OHOS_XMAGE_COLOR_MODES_END,
} camera_device_metadata_tag_t;

// switch type tag enumeration values
typedef enum camera_switch_enum {
    OHOS_CAMERA_SWTICH_OFF = 0,
    OHOS_CAMERA_SWTICH_ON,
} camera_switch_enum_t;

// OHOS_ABILITY_CAMERA_POSITION enumeration values
typedef enum camera_position_enum {
    OHOS_CAMERA_POSITION_FRONT = 0,
    OHOS_CAMERA_POSITION_BACK,
    OHOS_CAMERA_POSITION_OTHER
} camera_position_enum_t;

// OHOS_ABILITY_CAMERA_TYPE enumeration values
typedef enum camera_type_enum {
    OHOS_CAMERA_TYPE_WIDE_ANGLE = 0,
    OHOS_CAMERA_TYPE_ULTRA_WIDE,
    OHOS_CAMERA_TYPE_TELTPHOTO,
    OHOS_CAMERA_TYPE_TRUE_DEAPTH,
    OHOS_CAMERA_TYPE_LOGICAL,
    OHOS_CAMERA_TYPE_UNSPECIFIED,
} camera_type_enum_t;

// OHOS_ABILITY_CAMERA_CONNECTION_TYPE enumeration values
typedef enum camera_connection_type {
    OHOS_CAMERA_CONNECTION_TYPE_BUILTIN = 0,
    OHOS_CAMERA_CONNECTION_TYPE_USB_PLUGIN,
    OHOS_CAMERA_CONNECTION_TYPE_REMOTE,
} camera_connection_type_t;

// OHOS_CONTROL_EXPOSUREMODE
// and OHOS_ABILITY_EXPOSURE_MODES enumeration values
typedef enum camera_exposure_mode_enum {
    OHOS_CAMERA_EXPOSURE_MODE_MANUAL = 0,
    OHOS_CAMERA_EXPOSURE_MODE_CONTINUOUS_AUTO,
    OHOS_CAMERA_EXPOSURE_MODE_LOCKED,
    OHOS_CAMERA_EXPOSURE_MODE_AUTO
} camera_exposure_mode_enum_t;

// OHOS_CONTROL_FOCUS_MODE and OHOS_ABILITY_FOCUS_MODES enumeration values
typedef enum camera_focus_mode_enum {
    OHOS_CAMERA_FOCUS_MODE_MANUAL = 0,
    OHOS_CAMERA_FOCUS_MODE_CONTINUOUS_AUTO,
    OHOS_CAMERA_FOCUS_MODE_AUTO,
    OHOS_CAMERA_FOCUS_MODE_LOCKED
} camera_focus_mode_enum_t;

// OHOS_ABILITY_FOCUS_ASSIST_FLASH_SUPPORTED_MODES enumeration values
typedef enum camera_focus_assist_flash_mode_enum {
    OHOS_CAMERA_FOCUS_ASSIST_FLASH_MODE_DEFAULT = 0,
    OHOS_CAMERA_FOCUS_ASSIST_FLASH_MODE_AUTO,
    OHOS_CAMERA_FOCUS_ASSIST_FLASH_MODE_ON,
    OHOS_CAMERA_FOCUS_ASSIST_FLASH_MODE_OFF
} camera_focus_assist_flash_mode_enum_t;

// OHOS_CONTROL_FLASHMODE and OHOS_ABILITY_FLASH_MODES enumeration values
typedef enum camera_flash_mode_enum {
    OHOS_CAMERA_FLASH_MODE_CLOSE = 0,
    OHOS_CAMERA_FLASH_MODE_OPEN,
    OHOS_CAMERA_FLASH_MODE_AUTO,
    OHOS_CAMERA_FLASH_MODE_ALWAYS_OPEN
} camera_flash_mode_enum_t;

// OHOS_CONTROL_FLASH_STATE enumeration values
typedef enum camera_flash_state_enum {
    OHOS_CAMERA_FLASH_STATE_UNAVAILABLE = 0,
    OHOS_CAMERA_FLASH_STATE_CHARGING,
    OHOS_CAMERA_FLASH_STATE_READY,
    OHOS_CAMERA_FLASH_STATE_FLASHING,
    OHOS_CAMERA_FLASH_STATE_UNKNOWN
} camera_flash_state_enum_t;

// OHOS_CONTROL_AE_ANTIBANDING_MODE enumeration values
typedef enum camera_ae_antibanding_mode {
    OHOS_CAMERA_AE_ANTIBANDING_MODE_OFF,
    OHOS_CAMERA_AE_ANTIBANDING_MODE_50HZ,
    OHOS_CAMERA_AE_ANTIBANDING_MODE_60HZ,
    OHOS_CAMERA_AE_ANTIBANDING_MODE_AUTO,
} camera_ae_antibanding_mode_t;

// OHOS_ABILITY_AE_LOCK
// OHOS_CONTROL_AE_LOCK enumeration values
typedef enum camera_ae_lock {
    OHOS_CAMERA_AE_LOCK_OFF,
    OHOS_CAMERA_AE_LOCK_ON,
} camera_ae_lock_t;

// OHOS_CONTROL_AE_MODE enumeration values
typedef enum camera_ae_mode {
    OHOS_CAMERA_AE_MODE_OFF,
    OHOS_CAMERA_AE_MODE_ON,
    OHOS_CAMERA_AE_MODE_ON_AUTO_FLASH,
    OHOS_CAMERA_AE_MODE_ON_ALWAYS_FLASH,
    OHOS_CAMERA_AE_MODE_ON_AUTO_FLASH_REDEYE,
    OHOS_CAMERA_AE_MODE_ON_EXTERNAL_FLASH,
} camera_ae_mode_t;

// OHOS_CONTROL_AF_MODE
// and OHOS_CONTROL_AF_AVAILABLE_MODES enumeration values
typedef enum camera_af_mode {
    OHOS_CAMERA_AF_MODE_OFF,
    OHOS_CAMERA_AF_MODE_AUTO,
    OHOS_CAMERA_AF_MODE_MACRO,
    OHOS_CAMERA_AF_MODE_CONTINUOUS_VIDEO,
    OHOS_CAMERA_AF_MODE_CONTINUOUS_PICTURE,
    OHOS_CAMERA_AF_MODE_EDOF,
} camera_af_mode_t;

// OHOS_CONTROL_AF_TRIGGER enumeration values
typedef enum camera_af_trigger {
    OHOS_CAMERA_AF_TRIGGER_IDLE,
    OHOS_CAMERA_AF_TRIGGER_START,
    OHOS_CAMERA_AF_TRIGGER_CANCEL,
} camera_af_trigger_t;

// OHOS_CONTROL_AF_STATE enumeration values
typedef enum camera_af_state {
    OHOS_CAMERA_AF_STATE_INACTIVE,
    OHOS_CAMERA_AF_STATE_PASSIVE_SCAN,
    OHOS_CAMERA_AF_STATE_PASSIVE_FOCUSED,
    OHOS_CAMERA_AF_STATE_ACTIVE_SCAN,
    OHOS_CAMERA_AF_STATE_FOCUSED_LOCKED,
    OHOS_CAMERA_AF_STATE_NOT_FOCUSED_LOCKED,
    OHOS_CAMERA_AF_STATE_PASSIVE_UNFOCUSED,
} camera_af_state_t;

// OHOS_CONTROL_AWB_LOCK enumeration values
typedef enum camera_awb_lock {
    OHOS_CAMERA_AWB_LOCK_OFF,
    OHOS_CAMERA_AWB_LOCK_ON,
} camera_awb_lock_t;

// OHOS_ABILITY_AWB_MODES and OHOS_CONTROL_AWB_MODE enumeration values
typedef enum camera_awb_mode {
    OHOS_CAMERA_AWB_MODE_OFF,
    OHOS_CAMERA_AWB_MODE_AUTO,
    OHOS_CAMERA_AWB_MODE_INCANDESCENT,
    OHOS_CAMERA_AWB_MODE_FLUORESCENT,
    OHOS_CAMERA_AWB_MODE_WARM_FLUORESCENT,
    OHOS_CAMERA_AWB_MODE_DAYLIGHT,
    OHOS_CAMERA_AWB_MODE_CLOUDY_DAYLIGHT,
    OHOS_CAMERA_AWB_MODE_TWILIGHT,
    OHOS_CAMERA_AWB_MODE_SHADE,
} camera_awb_mode_t;

// OHOS_STATISTICS_FACE_DETECT_MODE
// and OHOS_STATISTICS_FACE_DETECT_SWITCH enumeration values
typedef enum camera_face_detect_mode {
    OHOS_CAMERA_FACE_DETECT_MODE_OFF,
    OHOS_CAMERA_FACE_DETECT_MODE_SIMPLE
} camera_face_detect_mode_t;

// OHOS_STATISTICS_HISTOGRAM_MODE enumeration values
typedef enum camera_histogram_mode {
    OHOS_CAMERA_HISTOGRAM_MODE_OFF,
    OHOS_CAMERA_HISTOGRAM_MODE_ON,
} camera_histogram_mode_t;

// OHOS_STREAM_AVAILABLE_FORMATS
// and OHOS_ABILITY_STREAM_AVAILABLE_BASIC_CONFIGURATIONS enumeration values
typedef enum camera_format {
    OHOS_CAMERA_FORMAT_RGBA_8888 = 1,
    OHOS_CAMERA_FORMAT_YCBCR_420_888,
    OHOS_CAMERA_FORMAT_YCRCB_420_SP,
    OHOS_CAMERA_FORMAT_YCBCR_420_SP,
    OHOS_CAMERA_FORMAT_JPEG,
    OHOS_CAMERA_FORMAT_YCBCR_P010,
    OHOS_CAMERA_FORMAT_YCRCB_P010,
    OHOS_CAMERA_FORMAT_DNG,
    OHOS_CAMERA_FORMAT_422_YUYV,
    OHOS_CAMERA_FORMAT_IMPLEMENTATION_DEFINED = 0x1000,
} camera_format_t;

// OHOS_ABILITY_STREAM_QUICK_THUMBNAIL_AVAILABLE enumeration values
typedef enum camera_quick_thumbnail_available {
    OHOS_CAMERA_QUICK_THUMBNAIL_FALSE = 0,
    OHOS_CAMERA_QUICK_THUMBNAIL_TRUE,
} camera_quick_thumbnail_available_t;

// OHOS_CONTROL_FOCUS_STATE enumeration values
typedef enum camera_focus_state {
    OHOS_CAMERA_FOCUS_STATE_SCAN,
    OHOS_CAMERA_FOCUS_STATE_FOCUSED,
    OHOS_CAMERA_FOCUS_STATE_UNFOCUSED,
} camera_focus_state_t;

// OHOS_CONTROL_METER_MODE and OHOS_ABILITY_METER_MODES enumeration values
typedef enum camera_meter_mode {
    OHOS_CAMERA_SPOT_METERING = 0,
    OHOS_CAMERA_REGION_METERING,
    OHOS_CAMERA_OVERALL_METERING,
    OHOS_CAMERA_CENTER_WEIGHTED_METERING,
} camera_meter_mode_t;

typedef enum camera_exposure_state {
    OHOS_CAMERA_EXPOSURE_STATE_SCAN,
    OHOS_CAMERA_EXPOSURE_STATE_CONVERGED,
} camera_exposure_state_t;

// OHOS_CONTROL_CAPTURE_MIRROR
// and OHOS_CONTROL_CAPTURE_MIRROR_SUPPORTED enumeration values
typedef enum camera_mirror {
    OHOS_CAMERA_MIRROR_OFF = 0,
    OHOS_CAMERA_MIRROR_ON,
} camera_mirror_t;

// OHOS_JPEG_ORIENTATION enumeration values
typedef enum camera_jpeg_orientation {
    OHOS_CAMERA_JPEG_ROTATION_0 = 0,
    OHOS_CAMERA_JPEG_ROTATION_90 = 90,
    OHOS_CAMERA_JPEG_ROTATION_180 = 180,
    OHOS_CAMERA_JPEG_ROTATION_270 = 270,
} camera_jpeg_orientation_t;

// OHOS_JPEG_QUALITY enumeration values
typedef enum camera_jpeg_quality {
    OHOS_CAMERA_JPEG_LEVEL_LOW = 0,
    OHOS_CAMERA_JPEG_LEVEL_MIDDLE,
    OHOS_CAMERA_JPEG_LEVEL_HIGH,
} camera_jpeg_quality_t;

// OHOS_ABILITY_VIDEO_STABILIZATION_MODES
// and OHOS_CONTROL_VIDEO_STABILIZATION_MODE enumeration values
typedef enum camera_video_stabilization_mode {
    OHOS_CAMERA_VIDEO_STABILIZATION_OFF = 0,
    OHOS_CAMERA_VIDEO_STABILIZATION_LOW,
    OHOS_CAMERA_VIDEO_STABILIZATION_MIDDLE,
    OHOS_CAMERA_VIDEO_STABILIZATION_HIGH,
    OHOS_CAMERA_VIDEO_STABILIZATION_AUTO,
} CameraVideoStabilizationMode;

// OHOS_ABILITY_FLASH_AVAILABLE enumeration values
typedef enum camera_flash_available {
    OHOS_CAMERA_FLASH_FALSE = 0,
    OHOS_CAMERA_FLASH_TRUE,
} CameraFlashAvailable;

// OHOS_ABILITY_MEMORY_TYPE enumeration values
typedef enum camera_memory_type_enum {
    OHOS_CAMERA_MEMORY_MMAP = 1,
    OHOS_CAMERA_MEMORY_USERPTR,
    OHOS_CAMERA_MEMORY_OVERLAY,
    OHOS_CAMERA_MEMORY_DMABUF,
} camera_memory_type_enum_t;

// OHOS_ABILITY_MUTE_MODES and OHOS_CONTROL_MUTE_MODE enumeration values
typedef enum camera_mute_mode {
    OHOS_CAMERA_MUTE_MODE_OFF,
    OHOS_CAMERA_MUTE_MODE_SOLID_COLOR_BLACK,
} camera_mute_mode_t;

// OHOS_ABILITY_SCENE_FILTER_TYPES enumeration values
typedef enum camera_filter_type {
    OHOS_CAMERA_FILTER_TYPE_OFF = 0,
    OHOS_CAMERA_FILTER_TYPE_NONE,
    OHOS_CAMERA_FILTER_TYPE_CLASSIC,
    OHOS_CAMERA_FILTER_TYPE_DAWN,
    OHOS_CAMERA_FILTER_TYPE_PURE,
    OHOS_CAMERA_FILTER_TYPE_GREY,
    OHOS_CAMERA_FILTER_TYPE_NATURAL,
    OHOS_CAMERA_FILTER_TYPE_MORI,
    OHOS_CAMERA_FILTER_TYPE_FAIR,
    OHOS_CAMERA_FILTER_TYPE_PINK,
} camera_filter_type_t;

// OHOS_ABILITY_SCENE_PORTRAIT_EFFECT_TYPES enumeration values
typedef enum camera_portrait_effect_type {
    OHOS_CAMERA_PORTRAIT_EFFECT_OFF = 0,
    OHOS_CAMERA_PORTRAIT_CIRCLES,
    OHOS_CAMERA_PORTRAIT_HEART,
    OHOS_CAMERA_PORTRAIT_ROTATED,
    OHOS_CAMERA_PORTRAIT_STUDIO,
    OHOS_CAMERA_PORTRAIT_THEATER,
} camera_portrait_effect_type_t;

// OHOS_ABILITY_SCENE_BEAUTY_TYPES enumeration values
typedef enum camera_beauty_type {
    OHOS_CAMERA_BEAUTY_TYPE_OFF = 0,
    OHOS_CAMERA_BEAUTY_TYPE_AUTO,
    OHOS_CAMERA_BEAUTY_TYPE_SKIN_SMOOTH,
    OHOS_CAMERA_BEAUTY_TYPE_FACE_SLENDER,
    OHOS_CAMERA_BEAUTY_TYPE_SKIN_TONE,
} camera_beauty_type_t;

//OHOS_ABILITY_SUPPORTED_COLOR_MODES and OHOS_CONTROL_SUPPORTED_COLOR_MODES enumeration
typedef enum camera_xmage_color_type {
    CAMERA_CUSTOM_COLOR_NORMAL = 0,
    CAMERA_CUSTOM_COLOR_BRIGHT,
    CAMERA_CUSTOM_COLOR_SOFT,
    CAMERA_CUSTOM_COLOR_MONO,
} camera_xmage_color_type_t;

// OHOS_ABILITY_CAMERA_FOLDSCREEN_TYPE enumeration values
typedef enum camera_fold_screen_enum {
    OHOS_CAMERA_FOLDSCREEN_OTHER = 0,
    OHOS_CAMERA_FOLDSCREEN_INNER,
    OHOS_CAMERA_FOLDSCREEN_OUTER,
} camera_foldscreen_enum_t;

// OHOS_ABILITY_CAMERA_MACRO_SUPPORTED enumeration values
typedef enum camera_macro_supported_type {
    OHOS_CAMERA_MACRO_NOT_SUPPORTED = 0,
    OHOS_CAMERA_MACRO_SUPPORTED,
} camera_macro_supported_type_t;

// OHOS_CAMERA_MACRO_STATUS and OHOS_CONTROL_CAMERA_MACRO enumeration values
typedef enum camera_macro_status_control_type {
    OHOS_CAMERA_MACRO_DISABLE = 0,
    OHOS_CAMERA_MACRO_ENABLE,
} camera_macro_status_control_type_t;

// OHOS_CONTROL_MOON_CAPTURE_BOOST enumeration values
typedef enum camera_moon_capture_boost_control_type {
    OHOS_CAMERA_MOON_CAPTURE_BOOST_DISABLE = 0,
    OHOS_CAMERA_MOON_CAPTURE_BOOST_ENABLE,
} camera_moon_capture_boost_control_type_t;

// OHOS_CONTROL_PREPARE_ZOOM enumeration values
typedef enum camera_zoomsmooth_control_type {
    OHOS_CAMERA_ZOOMSMOOTH_PREPARE_DISABLE = 0,
    OHOS_CAMERA_ZOOMSMOOTH_PREPARE_ENABLE,
} camera_zoomsmooth_control_type_t;

// OHOS_STATUS_SUPER_SLOW_MOTION enumeration values
typedef enum camera_slow_motion_status_type {
    OHOS_CONTROL_SLOW_MOTION_STATUS_DISABLE = 0,
    OHOS_CONTROL_SLOW_MOTION_STATUS_READY,
    OHOS_CONTROL_SLOW_MOTION_STATUS_START,
    OHOS_CONTROL_SLOW_MOTION_STATUS_RECORDING,
    OHOS_CONTROL_SLOW_MOTION_STATUS_FINISH,
} camera_slow_motion_status_type_t;

// OHOS_ABILITY_MOTION_DETECTION_SUPPORT enumeration values
typedef enum camera_motion_detection_supported_type {
    OHOS_CAMERA_MOTION_DETECTION_NOT_SUPPORTED = 0,
    OHOS_CAMERA_MOTION_DETECTION_SUPPORTED,
} camera_motion_detection_supported_type_t;

//  OHOS_CONTROL_MOTION_DETECTION enumeration values
typedef enum camera_motion_detection_control_type {
    OHOS_CAMERA_MOTION_DETECTION_DISABLE = 0,
    OHOS_CAMERA_MOTION_DETECTION_ENABLE,
} camera_motion_detection_control_type_t;

// OHOS_ABILITY_MOVING_PHOTO
typedef enum moving_photo_enum {
    OHOS_CAMERA_MOVING_PHOTO_UNSUPPORT = 0,
    OHOS_CAMERA_MOVING_PHOTO_SUPPORT,
} moving_photo_enum_t;
 
// OHOS_CONTROL_MOVING_PHOTO
typedef enum control_moving_photo_enum {
    OHOS_CAMERA_MOVING_PHOTO_OFF = 0,
    OHOS_CAMERA_MOVING_PHOTO_ON,
} control_moving_photo_enum_t;

// OHOS_STATUS_FLASH_SUGGESTION enumeration values
typedef enum camera_flash_suggestion_supported_enum {
    OHOS_CAMERA_FLASH_SUGGESTION_SUPPORTED_CLOSE = 0,
    OHOS_CAMERA_FLASH_SUGGESTION_SUPPORTED_OPEN,
} camera_flash_suggestion_supported_enum_t;

// ABILITY_SUPPORTED_TAGS enumeration values
typedef enum camera_supported_enum {
    OHOS_CAMERA_NOT_SUPPORTED = 0,
    OHOS_CAMERA_SUPPORTED,
} camera_supported_enum_t;

// OHOS_CONTROL_HIGH_QUALITY_MODE
typedef enum ControlHighQualityModeEnum {
    OHOS_CONTROL_HIGH_QUALITY_MODE_OFF = 0,
    OHOS_CONTROL_HIGH_QUALITY_MODE_ON,
} ControlHighQualityModeEnumT;

#endif
