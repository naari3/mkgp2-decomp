int PcbConn_RecycleIfOver(int *conn)
{
    if (conn[3] != 10) {
        return 0;
    }

    conn[3] = 2;
    conn[14] = 0;
    return 1;
}
