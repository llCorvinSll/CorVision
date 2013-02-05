#pragma once
#ifndef WORLD_H
#define WORLD_H

namespace core{
class World{
public:
    static  World& I(){
        return Instance;
    }
    bool runnig;
    void initWorld();
    //IO
    void pressKeyBoard(int character);
    void releaseKeyBoard(int character);
private:
    static World Instance;
    World(){}
    World(const World& root);
    World& operator=(const World&);
};
}
#endif // WORLD_H
