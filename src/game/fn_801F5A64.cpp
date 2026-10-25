/* Deletes an owned object through its virtual destructor. */
class Ownedfn_801F5A64 {
public:
    virtual ~Ownedfn_801F5A64();
};

extern "C" void fn_801F5A64(Ownedfn_801F5A64 *obj) {
    delete obj;
}
