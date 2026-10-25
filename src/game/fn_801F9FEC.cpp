/* Deletes an owned object through its virtual destructor. */
class Ownedfn_801F9FEC {
public:
    virtual ~Ownedfn_801F9FEC();
};

extern "C" void fn_801F9FEC(Ownedfn_801F9FEC *obj) {
    delete obj;
}
