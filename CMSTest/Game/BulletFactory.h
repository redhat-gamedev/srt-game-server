#ifndef __CMSTest__Bullet_Factory__
#define __CMSTest__Bullet_Factory__

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

#include "Bullet.h"
#include "../Shared/FactoryT.h"


class BulletFactory :
    public FactoryT<Bullet, Bullet::_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    BulletFactory() {};
    
    // Destructor(s)
    ~BulletFactory() {};
    
public:
    // Singleton
    static BulletFactory& Instance()//unsigned int uiCapacity)
    {
        static BulletFactory  aBulletFactory;
        return aBulletFactory;
    }
    
    // Method(s)
    void Destroy(Bullet*& pBullet);
};

#endif /* defined(__CMSTest__Bullet_Factory__) */