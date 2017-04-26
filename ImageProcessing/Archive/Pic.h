#ifndef PIC_H
#define PIC_H

class Pic {
public:
    Pic(); // Standard-Konstruktor
    Pic(unsigned int width, unsigned int height); // Werte-Konstruktor
    Pic(unsigned char* pixels, unsigned int width, unsigned int height);
    Pic(const Pic &p); // Kopier-Konstruktor
    ~Pic(); // Destruktor
    Pic& operator= (const Pic &p); // Zuweisungsoperator
    Pic& operator+ (const Pic &p);
    Pic& operator+= (const Pic& p);
    Pic& operator- (const Pic &p);
    Pic& operator-= (const Pic& p);
    //bool filterMedian(unsigned int filterWidth, unsigned int filterHeight);
    bool filterQuantil(unsigned int filterWidth, unsigned int filterHeight, double quantil);
    bool filterMedianHuang(unsigned int filterWidth, unsigned int filterHeight);
    bool filterVNormalMedianHuang(const unsigned char* filter, unsigned int filterWidth, unsigned int filterHeight);
    bool filterVNormalQuantil(const unsigned char* filter, unsigned int filterWidth, unsigned int filterHeight, double quantil);
    bool filterMedianHuang2(unsigned int filterWidth, unsigned int filterHeight);
    bool filterQuantilHuang(unsigned int filterWidth, unsigned int filterHeight, double quantil);
    bool filterMin(unsigned int filterWidth, unsigned int filterHeight);
    bool filterMax(unsigned int filterWidth, unsigned int filterHeight);
    bool initPic(unsigned int mode);
    bool writeRAW(char* name);
    bool readRAW(char* name);
    bool writePGM(char* name);
    //bool readPGM(char* name);
    unsigned int size(void) { return width * height; };
    unsigned char getPixelValue(unsigned int x, unsigned int y);
    bool setPixelValue(unsigned int x, unsigned int y, unsigned char value);
    unsigned int getWidth(void);
    unsigned int getHeight(void);
    const unsigned char* getPixels(void);
    unsigned char getMaximum();
    unsigned char getMinimum();
    bool spread();
    bool binarize(unsigned char thresh);
    unsigned int getTotal(void);
    bool isEqual(const Pic & p);
    //bool print(void);
    bool generarteStripes(unsigned int stripeWidth, unsigned int stripeType, unsigned int offset,  bool invert);
    bool markLine(unsigned int lineNumber, unsigned char value);
    bool markLine(unsigned int lineNumber, unsigned int xStart, unsigned int xEnd, unsigned char value);
    bool markColumn(unsigned int columnNumber, unsigned char value);
    bool markPoint(unsigned int x, unsigned int y, unsigned char color);
    bool drawRect(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, unsigned char color);
    bool fillRect(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, unsigned char color);
    bool drawLine(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, unsigned char color);
    bool checkPoint(unsigned int x, unsigned int y);
    int signum(int iNumber);

private:
    unsigned char* pixels;
    unsigned int width;
    unsigned int height;
};

#endif // PIC_H
