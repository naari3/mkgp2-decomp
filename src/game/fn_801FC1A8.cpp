/* Deletes an owned object through its virtual destructor. */
class Ownedfn_801FC1A8 {
public:
    virtual ~Ownedfn_801FC1A8();
};

extern "C" void fn_801FC1A8(Ownedfn_801FC1A8 *obj) {
    delete obj;
}
