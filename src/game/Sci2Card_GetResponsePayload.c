extern void *memcpy(void *dst, const void *src, unsigned long size);

void Sci2Card_GetResponsePayload(void *self, void *payload)
{
    memcpy(payload, (unsigned char *)*(void **)((unsigned char *)self + 0x10) + 6, 0x45);
}
