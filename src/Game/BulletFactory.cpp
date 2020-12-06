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

#include "BulletFactory.h"
#include "Bullet.h"
#include "B2DBullet.h"
#include "B2DBulletFactory.h"
#include <assert.h>


// Method(s)
void BulletFactory::Destroy(Bullet*& pBullet)
{
    assert(pBullet);
    
    B2DBullet* pB2DBullet = (B2DBullet*)pBullet->m_pB2DEntity;
    FactoryT<Bullet, Bullet::_Dependencies>::Destroy(pBullet);    
    B2DBulletFactory::Instance().Destroy(pB2DBullet);
}
