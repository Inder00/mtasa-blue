
//
// SColor
//
// Encapsulates the most common usage of 4 byte color storage.
// Casts to and from a DWORD as 0xAARRGGBB
//
class SColor
{
    // No shifting allowed to access the color channel information
    void operator>>(int) const;
    void operator<<(int) const;
    void operator>>=(int);
    void operator<<=(int);

public:
    union
    {
        struct
        {
            unsigned char B, G, R, A;
        };
        unsigned long ulARGB;
    };

    SColor() {}
    SColor(unsigned long ulValue) { ulARGB = ulValue; }

    operator unsigned long() const { return ulARGB; }
};

//
// SColorARGB
//
// Make an SColor from A,R,G,B
//
class SColorRGBA : public SColor
{
public:
    SColorRGBA(unsigned char ucR, unsigned char ucG, unsigned char ucB, unsigned char ucA)
    {
        A = ucA;
        R = ucR;
        G = ucG;
        B = ucB;
    }
};
