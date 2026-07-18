extern const char *PcbConnStateIdToName(int state_id);

const char *PcbConn_GetStateName(void *self)
{
    return PcbConnStateIdToName(((int *)self)[3]);
}
