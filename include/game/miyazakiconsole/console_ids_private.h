#ifndef MIYAZAKI17E_CONSOLE_IDS_PRIVATE_H
#define MIYAZAKI17E_CONSOLE_IDS_PRIVATE_H
struct Table { unsigned int ids[13]; unsigned int At(int n) const { return ids[n]; } };
#endif
