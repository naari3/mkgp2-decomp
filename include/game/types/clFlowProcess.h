#ifndef GAME_TYPES_CLFLOWPROCESS_H
#define GAME_TYPES_CLFLOWPROCESS_H

class clFlowProcess {
public:
    clFlowProcess();
    virtual ~clFlowProcess();
    virtual int Update();
    virtual void Draw();
};

#endif /* GAME_TYPES_CLFLOWPROCESS_H */
