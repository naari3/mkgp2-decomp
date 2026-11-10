#ifndef SPECIAL_FACE_MESH_PRIVATE_H
#define SPECIAL_FACE_MESH_PRIVATE_H
#include "game/types/size_t.h"
#include "game/SpecialFacePrivate.h"
void *operator new(size_t);
void operator delete(void *) throw();
extern "C" {
extern unsigned int SpecialFaceMesh_data_803FE0AC[], SpecialFaceMesh_vtable_803FE0B8[];
void PtrVec_Reserve(void *, unsigned int);
void PtrVec_InsertFill(void *, SpecialFaceNative **, unsigned int, SpecialFaceNative **);
}
struct SpecialFaceMeshNative;
extern "C" SpecialFaceMeshNative *lbl_806D1138;
struct FacePtrStorage {
    unsigned int capacity, count;
    SpecialFaceNative **data;
    FacePtrStorage() : capacity(0), count(0), data(0) {}
    ~FacePtrStorage() { if (data) operator delete(data); }
};
struct FacePtrMid : FacePtrStorage { ~FacePtrMid() {} };
struct FacePtrVec : FacePtrMid { ~FacePtrVec() {} };
struct FaceMeshBase {
    unsigned int *vptr;
    FaceMeshBase() { vptr = SpecialFaceMesh_vtable_803FE0B8; lbl_806D1138 = (SpecialFaceMeshNative *)this; vptr = SpecialFaceMesh_data_803FE0AC; }
    ~FaceMeshBase() { vptr = SpecialFaceMesh_vtable_803FE0B8; }
};
struct SpecialFaceMeshNative : FaceMeshBase {
    FacePtrVec faces;
    SpecialFaceMeshNative(struct FaceSourceGroup *, int);
    ~SpecialFaceMeshNative();
};
struct FaceSourceGroup { SpecialFaceSource *data; int count; };
extern "C" SpecialFaceMeshNative *lbl_806D1138;
#endif
