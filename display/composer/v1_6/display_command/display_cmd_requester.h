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

#ifndef OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_REQUESTER_H
#define OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_REQUESTER_H

#include "v1_5/display_command/display_cmd_requester.h"
#include "v1_5/idisplay_composer.h"
#include "v1_6/display_command/display_cmd_utils.h"
#include "v1_6/display_composer_type.h"


namespace OHOS {
namespace HDI {
namespace Display {
namespace Composer {
namespace V1_6 {
using namespace OHOS::HDI::Base;

template <typename Transfer, typename CompHdi>
class DisplayCmdRequester : public V1_5::DisplayCmdRequester<Transfer, CompHdi> {
public:
    DisplayCmdRequester(sptr<CompHdi> hdi) : BaseType1_5(hdi) {}

    // UINT32_MAX IS THE DEFAULT DEVID.
    static std::unique_ptr<DisplayCmdRequester> Create(sptr<CompHdi> hdi, uint32_t devId = UINT32_MAX)
    {
        DISPLAY_CHK_RETURN(hdi == nullptr, nullptr, HDF_LOGE("%{public}s: hdi is nullptr", __func__));
        auto requester = std::make_unique<DisplayCmdRequester>(hdi);
        DISPLAY_CHK_RETURN(requester == nullptr, nullptr,
            HDF_LOGE("%{public}s: CmdRequester is nullptr", __func__));
        auto ret = requester->Init(CmdUtils::INIT_ELEMENT_COUNT, devId);
        DISPLAY_CHK_RETURN(ret != HDF_SUCCESS, nullptr,
            HDF_LOGE("%{public}s: DisplayCmdRequester init failed", __func__));
        return requester;
    }

    int32_t SetDisplayReadBackSmq(uint32_t devId, bool disableReadback)
    {
        int32_t ret = 0;
        bool retBool = false;
        size_t writePos = requestPacker_.ValidSize();

        do {
            ret = CmdUtils::StartSection(REQUEST_CMD_SET_DISPLAY_READ_BACK, requestPacker_);
            DISPLAY_CHK_BREAK(ret != HDF_SUCCESS,
                HDF_LOGE("%{public}s: StartSection failed", __func__));

            retBool = requestPacker_.WriteUint32(devId);
            DISPLAY_CHK_BREAK(retBool == false,
                HDF_LOGE("%{public}s: write devId failed", __func__));

            retBool = requestPacker_.WriteBool(disableReadback);
            DISPLAY_CHK_BREAK(retBool == false,
                HDF_LOGE("%{public}s: write disableReadback failed", __func__));

            ret = CmdUtils::EndSection(requestPacker_);
            DISPLAY_CHK_BREAK(ret != HDF_SUCCESS,
                HDF_LOGE("%{public}s: EndSection failed", __func__));
        } while (0);

        if (retBool == false || ret != HDF_SUCCESS) {
            requestPacker_.RollBack(writePos);
            HDF_LOGE("%{public}s: writePos_ rollback", __func__);
            return HDF_FAILURE;
        }

        ReqStatistic(devId, REQUEST_CMD_SET_DISPLAY_READ_BACK, writePos);
        return HDF_SUCCESS;
    }

protected:
    using BaseType1_3 = V1_3::DisplayCmdRequester<Transfer, CompHdi>;
    using BaseType1_3::requestPacker_;
    using BaseType1_3::ReqStatistic;

private:
    using BaseType1_5 = V1_5::DisplayCmdRequester<Transfer, CompHdi>;
};
using HdiDisplayCmdRequester = V1_6::DisplayCmdRequester<SharedMemQueue<int32_t>, V1_5::IDisplayComposer>;
} // namespace V1_6
} // namespace Composer
} // namespace Display
} // namespace HDI
} // namespace OHOS
#endif // OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_REQUESTER_H
