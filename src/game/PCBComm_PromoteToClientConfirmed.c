extern void SetLocalPcbRole(int);

#pragma exceptions on
int PCBComm_PromoteToClientConfirmed(void) {
    SetLocalPcbRole(5);
    return 1;
}
#pragma exceptions reset
