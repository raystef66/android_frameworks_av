/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

// Proxy for media player implementations

//#define LOG_NDEBUG 0
#define LOG_TAG "MediaDrmService"

#include "MediaDrmService.h"
#include <binder/IServiceManager.h>
#include <utils/Log.h>

#ifdef ENABLE_TREBLE
#include <media/CryptoHal.h>
#include <media/DrmHal.h>
#else
#include <media/Crypto.h>
#include <media/Drm.h>
#endif

namespace android {

void MediaDrmService::instantiate() {
    defaultServiceManager()->addService(
            String16("media.drm"), new MediaDrmService());
}

sp<ICrypto> MediaDrmService::makeCrypto() {
#ifdef ENABLE_TREBLE
    return new CryptoHal;
#else
    return new Crypto;
#endif
}

sp<IDrm> MediaDrmService::makeDrm() {
#ifdef ENABLE_TREBLE
    return new DrmHal;
#else
    return new Drm;
#endif
}

} // namespace android
