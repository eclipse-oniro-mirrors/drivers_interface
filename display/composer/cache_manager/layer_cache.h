/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef OHOS_HDI_DISPLAY_V1_0_LAYER_CACHE_H
#define OHOS_HDI_DISPLAY_V1_0_LAYER_CACHE_H

#include <functional>
#include <memory>
#include <unordered_map>
#include "base/native_buffer.h"
#include "cache_manager.h"
#include "nocopyable.h"
#include <mutex>

namespace OHOS {
namespace HDI {
namespace Display {
namespace Composer {
using namespace OHOS::HDI::Base;
class LayerCache : public NoCopyable {
public:
    ~LayerCache();
    static LayerCache* Create(uint32_t id);
    int32_t SetLayerBuffer(const BufferHandle* buffer, uint32_t seqNo, bool &needFreeBuffer,
        const std::vector<uint32_t>& deletingList, std::function<int32_t (const BufferHandle&)> realFunc);
    int32_t SetBufferCacheMaxCount(uint32_t cacheCount);
    void Dump() const;
private:
    explicit LayerCache(uint32_t id);
    int32_t Init();

    uint32_t layerId_;
    std::shared_ptr<CacheManager<uint32_t, NativeBuffer>> bufferCaches_;
    std::mutex mutex_;
};
} // namespace Composer
} // namespace Display
} // namespace HDI
} // namespace OHOS
#endif // OHOS_HDI_DISPLAY_V1_0_LAYER_CACHE_H
