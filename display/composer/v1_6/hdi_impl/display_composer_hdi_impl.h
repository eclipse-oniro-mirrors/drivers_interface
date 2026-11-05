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

#ifndef OHOS_HDI_DISPLAY_V1_6_DISPLAY_COMPOSER_HDI_IMPL_H
#define OHOS_HDI_DISPLAY_V1_6_DISPLAY_COMPOSER_HDI_IMPL_H

#include "common/include/display_config.h"
#include "v1_5/hdi_impl/display_composer_hdi_impl.h"
#include "v1_6/display_command/display_cmd_requester.h"
#include "v1_6/display_composer_type.h"
#include "v1_6/include/idisplay_composer_interface.h"
#include <cinttypes>

#undef LOG_TAG
#define LOG_TAG "DISP_HDI_COMP"
#undef LOG_DOMAIN
#define LOG_DOMAIN 0xD002515

namespace OHOS {
namespace HDI {
namespace Display {
namespace Composer {
namespace V1_6 {

using namespace OHOS::HDI::Display;

template <typename Interface, typename CompHdi, typename CmdReq>
class DisplayComposerHdiImpl : public V1_5::DisplayComposerHdiImpl<Interface, CompHdi, CmdReq> {
public:
    static IDisplayComposerInterface* Create(bool needSMQ)
    {
        sptr<CompHdi> hdi;
        std::shared_ptr<CmdReq> req = nullptr;
        HDF_LOGI("%{public}s: hdi v1_6 start", __func__);
        while ((hdi = CompHdi::Get()) == nullptr) {
            // Waiting for display composer service ready
            usleep(WAIT_TIME_INTERVAL);
        }
        HDF_LOGI("%{public}s: hdi v1_6 end", __func__);
        if (needSMQ) {
            req = CmdReq::Create(hdi);
            if (req == nullptr) {
                HDF_LOGE("%{public}s: Create DisplayCmdRequester failed %{public}d", __func__, __LINE__);
                return nullptr;
            }
        }
        return new DisplayComposerHdiImpl(hdi, req);
    }

    DisplayComposerHdiImpl(sptr<CompHdi> hdi, std::shared_ptr<CmdReq> req)
        : BaseType1_5(hdi, req) {}

    virtual ~DisplayComposerHdiImpl() {}

    virtual int32_t SetDisplayReadBackSmq(uint32_t devId, bool disableReadback) override
    {
        std::shared_ptr<CmdReq> reqCur = GetRequest(devId);
        COMPOSER_CHECK_NULLPTR_RETURN(reqCur);
        return ToDispErrCode(reqCur->SetDisplayReadBackSmq(devId, disableReadback));
    }

protected:
    using BaseType1_5 = V1_5::DisplayComposerHdiImpl<Interface, CompHdi, CmdReq>;
    using BaseType1_5::WAIT_TIME_INTERVAL;
    using BaseType1_5::ToDispErrCode;
    using BaseType1_5::GetRequest;
};
using HdiDisplayComposer =
    DisplayComposerHdiImpl<IDisplayComposerInterface, V1_5::IDisplayComposer, HdiDisplayCmdRequester>;
} // namespace V1_6
} // namespace Composer
} // namespace Display
} // namespace HDI
} // namespace OHOS
#endif // OHOS_HDI_DISPLAY_V1_6_DISPLAY_COMPOSER_HDI_IMPL_H
