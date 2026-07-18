extern void DisplayStruct_Init(void *self);

void *KartDriver_New_Empty(void *self)
{
    DisplayStruct_Init(self);
    return self;
}
