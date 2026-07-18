void Object_SetByte48(void *object, unsigned char value)
{
    *(unsigned char *)((char *)object + 0x48) = value;
}
