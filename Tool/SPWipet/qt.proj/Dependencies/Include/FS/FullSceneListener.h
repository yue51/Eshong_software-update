#ifndef FULLSCENELISTENER_H_
#define FULLSCENELISTENER_H_	1
#include <string>

namespace FS
{   
    class FullSceneListener
    {
    public:
        FullSceneListener(){}
        virtual ~FullSceneListener(){}
        
    public:
        static FullSceneListener*& GetSingleton(FullSceneListener* pFSListener=NULL);
        
    public:
        virtual void OnFSNext(const char* _id, const char* _tip){}
    };
    
}
#endif