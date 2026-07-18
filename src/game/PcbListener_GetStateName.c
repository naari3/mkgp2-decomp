extern const char *PcbConnStateIdToName(int state_id);

const char *PcbListener_GetStateName(void *self)
{
    return PcbConnStateIdToName(((int *)self)[1]);
}
