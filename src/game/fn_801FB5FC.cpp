/* Deletes an owned object through its virtual destructor. */
class Ownedfn_801FB5FC {
public:
    virtual ~Ownedfn_801FB5FC();
};

extern "C" void fn_801FB5FC(Ownedfn_801FB5FC *obj) {
    delete obj;
}
