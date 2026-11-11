extern "C" const char lbl_803F1CBC[9];

namespace std {
class exception {
public:
    exception() { }
    virtual ~exception() { }
    virtual const char* what() const;
};

class bad_cast : public exception {
public:
    bad_cast() { }
    virtual ~bad_cast();
    virtual const char* what() const;
};

const char* bad_cast::what() const { return lbl_803F1CBC; }
bad_cast::~bad_cast() { }
} // namespace std
