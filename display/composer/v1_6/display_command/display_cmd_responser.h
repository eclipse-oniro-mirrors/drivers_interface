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

#ifndef OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_RESPONSER_H
#define OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_RESPONSER_H

#include "v1_5/display_command/display_cmd_responser.h"
#include "v1_6/display_composer_type.h"
#include "v1_6/display_command/display_cmd_utils.h"

#define DISPLAY_TRACE HdfTrace trace(__func__, "HDI:DISP:")

namespace OHOS {
namespace HDI {
namespace Display {
namespace Composer {
namespace V1_6 {
using namespace OHOS::HDI::Base;

template <typename Transfer, typename VdiImpl>
class DisplayCmdResponser : public V1_5::DisplayCmdResponser<Transfer, VdiImpl> {
public:
    static std::unique_ptr<DisplayCmdResponser> Create(VdiImpl* impl, std::shared_ptr<DeviceCacheManager> cacheMgr)
    {
        DISPLAY_CHK_RETURN(impl == nullptr, nullptr,
            HDF_LOGE("%{public}s: error, VdiImpl is nullptr", __func__));
        DISPLAY_CHK_RETURN(cacheMgr == nullptr, nullptr,
            HDF_LOGE("%{public}s: error, cacheMgr is nullptr", __func__));
        return std::make_unique<DisplayCmdResponser>(impl, cacheMgr);
    }

    DisplayCmdResponser(VdiImpl* impl, std::shared_ptr<DeviceCacheManager> cacheMgr) : BaseType1_5(impl, cacheMgr) {}

    virtual ~DisplayCmdResponser() {}

    int32_t ProcessRequestCmd(CommandDataUnpacker& unpacker, int32_t cmd,
        const std::vector<HdifdInfo>& inFds, std::vector<HdifdInfo>& outFds)
    {
        HDF_LOGD("%{public}s: HDI 1.6 PackSection, cmd-[%{public}d] = %{public}s",
            __func__, cmd, CmdUtils::CommandToString(cmd));
        if (cmd == REQUEST_CMD_SET_DISPLAY_READ_BACK) {
            OnSetDisplayReadBack(unpacker);
        } else {
            return V1_2::DisplayCmdResponser<Transfer, VdiImpl>::ProcessRequestCmd(unpacker, cmd, inFds, outFds);
        }
        return HDF_SUCCESS;
    }

    void OnSetDisplayReadBack(CommandDataUnpacker& unpacker)
    {
        DISPLAY_TRACE;
        uint32_t devId = 0;
        bool disableReadback = 0;
        bool retBool = true;

        int32_t ret = unpacker.ReadUint32(devId) ? HDF_SUCCESS : HDF_FAILURE;
        DISPLAY_CHECK(ret != HDF_SUCCESS, goto UNPACKER_EXIT);

        retBool = unpacker.ReadBool(disableReadback);
        DISPLAY_CHECK(retBool == false, goto UNPACKER_EXIT);

        if (impl_ != nullptr && impl_->SetDisplayReadBack != nullptr) {
            HdfTrace traceVdi("SetDisplayReadBack", "HDI:DISP:HARDWARE");
            ret = impl_->SetDisplayReadBack(devId, disableReadback);
        }
        DISPLAY_CHECK(ret != HDF_SUCCESS, goto UNPACKER_EXIT);

UNPACKER_EXIT:
        if (ret != HDF_SUCCESS || retBool == false) {
            errMaps_.emplace(REQUEST_CMD_SET_DISPLAY_READ_BACK, ret);
        }
        return;
    }

    int32_t CmdRequest(uint32_t inEleCnt, const std::vector<HdifdInfo>& inFds,
        uint32_t& outEleCnt, std::vector<HdifdInfo>& outFds)
    {
        std::shared_ptr<char> requestData(new char[inEleCnt * CmdUtils::ELEMENT_SIZE], std::default_delete<char[]>());
        int32_t ret = CmdRequestDataRead(requestData, inEleCnt);
        CommandDataUnpacker unpacker;
        unpacker.Init(requestData.get(), inEleCnt << CmdUtils::MOVE_SIZE);
#ifdef DEBUG_DISPLAY_CMD_RAW_DATA
        unpacker.Dump();
#endif // DEBUG_DISPLAY_CMD_RAW_DATA

        int32_t unpackCmd = -1;
        bool retBool = unpacker.PackBegin(unpackCmd);
        DISPLAY_CHK_RETURN(retBool == false, HDF_FAILURE,
            HDF_LOGE("%{public}s: error: Check RequestBegin failed", __func__));
        DISPLAY_CHK_RETURN(unpackCmd != CONTROL_CMD_REQUEST_BEGIN, HDF_FAILURE,
                           HDF_LOGI("error: unpacker PackBegin cmd not match, cmd(%{public}d)=%{public}s.", unpackCmd,
                                    CmdUtils::CommandToString(unpackCmd)));

        DISPLAY_CHK_RETURN(PeriodDataReset() == HDF_FAILURE, HDF_FAILURE,
                           HDF_LOGE("%{public}s: error: PeriodDataReset failed", __func__));
        while (ret == HDF_SUCCESS && unpacker.NextSection()) {
            DISPLAY_CHK_RETURN(unpacker.BeginSection(unpackCmd) == false, HDF_FAILURE,
                HDF_LOGE("error: PackSection failed, unpackCmd=%{public}s.",
                CmdUtils::CommandToString(unpackCmd)));
            ret = ProcessRequestCmd(unpacker, unpackCmd, inFds, outFds);
        }

        DISPLAY_CHK_RETURN(ret != HDF_SUCCESS, ret,
                           HDF_LOGE("%{public}s: ProcessRequestCmd failed", __func__));
        /* pack request end commands */
        replyPacker_.PackEnd(CONTROL_CMD_REPLY_END);

#ifdef DEBUG_DISPLAY_CMD_RAW_DATA
        /* just for debug */
        replyPacker_.Dump();
        HDF_LOGI("CmdReply command cnt=%{public}d", replyCommandCnt_);
#endif // DEBUG_DISPLAY_CMD_RAW_DATA

        /*  Write reply pack */
        outEleCnt = replyPacker_.ValidSize() >> CmdUtils::MOVE_SIZE;
        ret = CmdRequestDataWrite(outEleCnt);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("Reply write failure, ret=%{public}d", ret);
            outEleCnt = 0;
        }
        return ret;
    }

protected:
    using BaseType1_5 = V1_5::DisplayCmdResponser<Transfer, VdiImpl>;
    using BaseType1_0 = V1_0::DisplayCmdResponser<Transfer, VdiImpl>;
    using BaseType1_0::impl_;
    using BaseType1_0::errMaps_;
    using BaseType1_0::replyPacker_;
    using BaseType1_0::CmdRequestDataWrite;
    using BaseType1_0::CmdRequestDataRead;
    using BaseType1_0::PeriodDataReset;
};

using HdiDisplayCmdResponser = DisplayCmdResponser<SharedMemQueue<int32_t>, DisplayComposerVdiAdapter>;
} // namespace V1_6
} // namespace Composer
} // namespace Display
} // namespace HDI
} // namespace OHOS
#endif // OHOS_HDI_DISPLAY_V1_6_DISPLAY_CMD_RESPONSER_H
