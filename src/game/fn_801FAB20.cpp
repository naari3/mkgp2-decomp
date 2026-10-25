/* Deletes an owned object through its virtual destructor. */
class Ownedfn_801FAB20 {
public:
    virtual ~Ownedfn_801FAB20();
};

extern "C" void fn_801FAB20(Ownedfn_801FAB20 *obj) {
    delete obj;
}
