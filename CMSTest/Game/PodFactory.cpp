//
//  PodFactory.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-03.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

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
