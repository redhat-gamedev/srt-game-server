//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "PodFactory.h"
#include "Pod.h"
#include "B2DPod.h"
#include "B2DPodFactory.h"
#include <assert.h>


// Method(s)
void PodFactory::Destroy(Pod*& pPod)
{
    assert(pPod);
    
    B2DPod* pB2DPod = (B2DPod*)pPod->m_pB2DEntity;
    FactoryT<Pod, Pod::_Dependencies>::Destroy(pPod);
    B2DPodFactory::Instance().Destroy(pB2DPod);
}
