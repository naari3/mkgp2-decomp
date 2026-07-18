void PcbConn_MarkDisabled(void *conn) {
    ((unsigned char *)conn)[0x3E] = 0;
    *(int *)((unsigned char *)conn + 0x0C) = 11;
}
