/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef OHOS_HDI_DISPLAY_V1_6_IDISPLAY_COMPOSER_INTERFACE_H
#define OHOS_HDI_DISPLAY_V1_6_IDISPLAY_COMPOSER_INTERFACE_H

#include "v1_5/include/idisplay_composer_interface.h"
#include "v1_6/display_composer_type.h"

namespace OHOS {
namespace HDI {
namespace Display {
namespace Composer {
namespace V1_6 {

class IDisplayComposerInterface : public V1_5::IDisplayComposerInterface {
public:
    /**
     * @brief Obtains all interfaces of IDisplayComposerInterface.
     *
     * @return Returns <b>IDisplayComposerInterface*</b> if the operation is successful;
     * returns an null point otherwise.
     * @since 7.1
     * @version 1.0
     */
    static IDisplayComposerInterface* Get(bool needSMQ = true);
    
    /**
     * @brief Sets the display readback of status.
     *
     * @param devId Indicates the ID of the display device.
     * @param disableReadback Indicates whether to disable display readback.
     *        - true: Disable display readback (the display content cannot be read back)
     *        - false: Enable display readback (the display content can be read back normally)
     *
     * @return Returns <b>0</b> if the operation is successful; returns an error code defined
     * in {@link DispErrCode} otherwise.
     * @since 7.1
     * @version 1.0
     */
    virtual int32_t SetDisplayReadBackSmq(uint32_t devId, bool disableReadback) = 0;
};
} // V1_6
} // Composer
} // Display
} // HDI
} // OHOS
#endif // OHOS_HDI_DISPLAY_V1_6_IDISPLAY_COMPOSER_INTERFACE_H
