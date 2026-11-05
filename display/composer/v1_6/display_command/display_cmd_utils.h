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

#ifndef OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_UTILS_H
#define OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_UTILS_H

#include "v1_5/display_command/display_cmd_utils.h"
#include "v1_6/display_composer_type.h"

#undef LOG_TAG
#define LOG_TAG "DISP_CMD"
#undef LOG_DOMAIN
#define LOG_DOMAIN 0xD002515

namespace OHOS {
namespace HDI {
namespace Display {
namespace Composer {
namespace V1_6 {

class DisplayCmdUtils : public V1_5::DisplayCmdUtils {
public:
    #define SWITCHCASE(x) case (x): {return #x;}
    static const char *CommandToString(int32_t cmdId)
    {
        switch (cmdId) {
            /* request cmd */
            SWITCHCASE(REQUEST_CMD_SET_DISPLAY_READ_BACK);
            default:
                return V1_5::DisplayCmdUtils::CommandToString(cmdId);
        }
    }
};
using CmdUtils = DisplayCmdUtils;
} // namespace V1_6
} // namespace Composer
} // namespace Display
} // namespace HDI
} // namespace OHOS
#endif // OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_UTILS_H
