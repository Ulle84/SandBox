#include "pic.h"

#include <cstdlib> // Zufallszahlen und sort()
#include <iostream> // Ein- und Ausgabe
#include <iomanip> // f�r setw(4) (manipulierte Ausgabe)
#include <fstream> // Dateien lesen und schreiben
#include <cmath> // Mathematische Funktionen, z.B. abs()

#include <vector>
#include <string.h>

using namespace std;



double getDistance(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, int mode)
{
    int xTemp = abs((int)(xEnd-xStart));
    int yTemp = abs((int)(yEnd-yStart));

    switch (mode)
    {
    case 1: // Euklidische Metrik
        return std::sqrt((double) xTemp*xTemp+yTemp*yTemp);
    case 2: // Monnem Metrik
        return xTemp+yTemp;
    case 3: // Maximums Metrik
        return xTemp>yTemp?xTemp:yTemp;
     default:
        return -1;
    }
}

bool Pic::markLine(unsigned int lineNumber, unsigned int xStart, unsigned int xEnd, unsigned char value) {
    // ist die Funktion vlt. schon ein bisschen oversized?

    if (xStart > xEnd) {
        return false;
    }
    for (unsigned int i = xStart; i <= xEnd; i++) {
        pixels[lineNumber*width + i] = value;
    }

    return true;
}

bool Pic::checkPoint(unsigned int x, unsigned int y) {
    // schaut, ob ein Punkt innerhalb eines Bildes liegt
    if (x <= width && y <= height) {
        return true;
    }
    else {
        return false;
    }
}

int Pic::signum(int iNumber) {
    // Signum-Funktion um das Vorzeichen der Zahl festzulegen
    if (iNumber == 0)
        return 0;
    if (iNumber < 0)
        return -1;
    else
        return 1;
}

bool Pic::drawLine(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, unsigned char color) {
    // Linie wird gezeichnet auf Basis des Start- und des Endpunktes.
    // Bedienung am Bresenham-Algorithmus
    // Optimierungsm�glichkeit:: F�r horizontale bzw. vertikale Linien -> Abfangen und direkt zeichnen ohne Schleifendurchlauf


    // sind die Punkte im Bild? Nein: false
    if (checkPoint(xStart, yStart) && checkPoint(xEnd, yEnd))
    {
        // Deklaration der funktionsinternen Variablen
        int dx, dy, adx, ady, es, el, sdx, sdy, pdx, pdy, ddx, ddy, error;
        unsigned int x, y;

        // Initialisierung der 1-dim. Abst�nde
        dx = xEnd - xStart;
        dy = yEnd - yStart;

        // Initialisierung Absolutbetr�ge und Signum-Distanzen
        adx = abs(dx);
        ady = abs(dy);
        sdx = signum(dx);
        sdy = signum(dy);

        // Schrittrichtung in Abh�ngigkeit der Lage von Start- und Endpunkt zueinander festlegen
        if (adx > ady)
        {
            // x ist die schnelle Achse = x steigt schneller als y
            pdx = sdx;  // Parallelschrit in x
            pdy = 0;    // Parallelschrit in y
            ddx = sdx;  // Diagonalschritt in x
            ddy = sdy;  // Diagonalschritt in y
            es = ady;   // Fehlerschritt schnelle Achse
            el = adx;   // Fehlerschritt langsame Achse
        }
        else
        {
            pdx = 0;
            pdy = sdy;
            ddx = sdx;
            ddy = sdy;
            es = adx;
            el = ady;
        }

        // Fehlerglied richtig initialsieren
        error = el/2;
        x = xStart;
        y = yStart;
        pixels[y * width + x] = color;

        // Pixelschleife: immer einen Schritt in Richtung schnelle Achse, ab und an auch einen
        // Schritt in die langsame Achse (wenn Fehlerglied < 0)
        for (int i = 0; i < el-1; ++i)
        {
            error -= es;
            if (error < 0)
            {
                // Schritt in die langsame Richtung (diagonal)
                error += el; // Fehlerglied positiv machen
                x += ddx;
                y += ddy;
            }
            else
            {
                // Schritt in die schnelle Richtung (parallel)
                x += pdx;
                y += pdy;
            }
            pixels[y * width + x] = color;
        }

        return true;
    }
    else {
        return false;
    }
}

bool Pic::fillRect(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, unsigned char color) {
    if (xStart > xEnd || yStart > yEnd) { // sind die zwei Punkte zueinander nicht plausibel?
        return false;
    }
    if (!checkPoint(xStart, yStart) || !checkPoint(xEnd, yEnd)) { // ist einer der Punkte ausserhalb des Bildes?
        return false;
    }
    for (unsigned int y = yStart; y <= yEnd; y++) {
        memset(&pixels[y * width + xStart], color, xEnd-xStart+1);
    }
    return true;
}

bool Pic::markPoint(unsigned int x, unsigned int y, unsigned char color) {
   if (!checkPoint(x, y)) {
    return false;
   }
    pixels[y * width + x] = color;
    return true;
}

bool Pic::drawRect(unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, unsigned char color) {
    if (xStart > xEnd) {
        return false;
    }
    if (yStart > yEnd) {
        return false;
    }
    if (xStart >= width || xEnd >= width) {
        return false;
    }
    if (yStart >= height || yEnd >= height) {
        return false;
    }

    // horizontale Kanten ohne Index direkt mit memeset()
    memset(&pixels[yStart*width + xStart], color, xEnd-xStart+1); // obere Kante
    memset(&pixels[yEnd*width + xStart], color, xEnd-xStart+1); // untere Kante

    // vertikale Kanten mit Index
    for (unsigned int i = yStart; i <= yEnd; i++) {
        pixels[i*width + xEnd] = color; // rechte Kante einzeichnen
        pixels[i*width + xStart] = color; // linke Kante einzeichnen
    }

    return true;
}

bool Pic::filterVNormalQuantil(const unsigned char* filter, unsigned int filterWidth, unsigned int filterHeight, double quantil) {
    // quantil prüfen
    if (quantil < 0.0 || quantil > 1.0) {
        return false;
    }

    if (filterWidth > width || filterHeight > height) {
        return false; // Filtergröße zu groß
    }

    int leftFilterWidth = filterWidth / 2;
    int rightFilterWidth = filterWidth / 2;
    int topFilterHeight = filterHeight / 2;
    int bottomFilterHeight = filterHeight / 2;

    // Falls Filterbreite gerade
    if (filterWidth % 2 == 0) {
        rightFilterWidth--;
    }

    // Falls Filterhöhe gerade
    if (filterHeight % 2 == 0) {
        bottomFilterHeight--;
    }

    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    memset(resultPixels, 0, width * height);

    /* This algorithm ist doing median filtering of an image;
    This algorithm ignores border processing problem */

    int hist[256]; // histogram-array
    unsigned char mdn = 0; // Median-value
    int ltmdn = 0; // number of pixels having gray levels less than mdn in window
    unsigned char* leftcolumn = new unsigned char [filterHeight]; // left-most column of the previous window
    unsigned char* rightcolumn = new unsigned char [filterHeight]; // rightmost column of the current window

    int* leftFilterOffset = new int[filterHeight];
    int* rightFilterOffset = new int[filterHeight];

    for (unsigned int y = 0; y < filterHeight; y++) {
        for (unsigned int x = 0; x < filterWidth; x++) { // von links antasten
            if (filter[y * filterWidth + x] == 1) {
                leftFilterOffset[y] = x;
                x = filterWidth;
            }
        }
        for (unsigned int x = 0; x < filterWidth; x++) { // nochmal von rechts antasten
            if (filter[(y + 1) * filterWidth - 1 - x] == 1) {
                rightFilterOffset[y] = x;
                x = filterWidth;
            }
        }
    }


    int countFilterIndices = 0;
    for (unsigned int i = 0; i < filterWidth * filterHeight; i++) {
        if (filter[i] > 0) {
            countFilterIndices++;
        }
    }
    if (countFilterIndices < 1) {
        // alle Indizes der Filtermaske sind <= 0
        return false;
    }
    int th = 0;
    if (quantil < 1.0) {
        th = (int) countFilterIndices * quantil; // global parameter to help decide median
    }
    else {
        th = countFilterIndices - 1;
    }

    for (unsigned int y = topFilterHeight; y < height - bottomFilterHeight; y++) { // über alle Zeilen
        // Histogramm auf 0 setzen
        for (int x = 0; x < 256; x++) {
            hist[x] = 0;
        }

        // Set up arry hist for the first window (in every line)
        for (int l = -leftFilterWidth; l <= rightFilterWidth; l++) {
            for (int k = -topFilterHeight; k <= bottomFilterHeight; k++) {
                // only if index > 0 in filterMask
                if (filter[(k + topFilterHeight) * filterWidth + l + leftFilterWidth] != 0) {
                    hist[pixels[(y + k) * width + (leftFilterWidth + l)]]++;
                }
            }
        }



        // find mdn by moving through the histogram bins
        int sum = 0;
        for (int i = 0; i < 256; i++) {
            sum += hist[i];
            if (sum > th) {
                mdn = i;
                ltmdn = sum - hist[i]; // updating count ltmdn
                i = 256; // aus der Schleife aussteigen!
            }
        }
        resultPixels[y * width + leftFilterWidth] = mdn;
        for (unsigned int x = leftFilterWidth + 1; x < width - rightFilterWidth; x++) { // über alle Spalten


            // update histogram
            // ToDo das hier in die oberen Schleifen packen?
            for (unsigned int i = 0; i < filterHeight; i++) {
                int g = pixels[(y - topFilterHeight + i) * width + x - leftFilterWidth - 1 + leftFilterOffset[i]]; // leftcolumn[i]
                //cout << "geht raus: " << g << endl;
                hist[g]--;
                if (g < mdn) { // check to update the counter ltmdn
                    ltmdn--;
                }
                /* widht + x + leftFilterWidht? */
                g = pixels[(y - topFilterHeight + i) * width + x + rightFilterWidth - rightFilterOffset[i]]; // rightcolumn[i]
                //cout << "geht rein: " << g << endl;
                hist[g]++;
                if (g < mdn) {
                    ltmdn++;
                }
            }

            // find median
            if (ltmdn > th) {
                // the median in the current window is smaller than
                // the one in the prvious window
                while (ltmdn > th) {
                    mdn--;
                    ltmdn = ltmdn - hist[mdn]; // update counter ltmdn
                }
            }
            else {
                while(ltmdn + hist[mdn] <= th) {
                    ltmdn = ltmdn + hist[mdn]; // update counter ltmdn
                    mdn++; // move up one histogram bin
                }
            }
            resultPixels[y * width + x] = mdn;
        }
    }


    // Ergebnis ins Originalbild kopieren
    //ToDo Effizienter durch Pointer "umhängen"
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = resultPixels[i];
    }

    delete[] resultPixels; // Speicher wieder freigeben
    delete[] leftFilterOffset;
    delete[] rightFilterOffset;
    delete[] leftcolumn;
    delete[] rightcolumn;

    return true;
}

bool Pic::isEqual(const Pic & p) {
    if (&p == this) {
        return true;
    }

    unsigned char* pixels2 = p.pixels;
    unsigned int width2 = p.width;
    unsigned int height2 = p.height;

    if (width != width2) {
        return false;
    }

    if (height != height2) {
        return false;
    }

    if (memcmp(pixels, pixels2, sizeof(pixels)) != 0) {
        return false;
    }
    return true;
}

bool Pic::filterMin(unsigned int filterWidth, unsigned int filterHeight) {
    // Minimumsfilter

    // Falls Filtergröße gerade
    if (filterWidth % 2 != 1) {
        filterWidth++; // auf die nächstgrößten ungeraden Filtergröße erhöhen
    }

    if (filterHeight % 2 != 1) {
        filterHeight++; // auf die nächstgrößten ungeraden Filtergröße erhöhen
    }

    if (filterWidth > width || filterHeight > height) {
        return false; // Filtergröße zu groß
    }

    //cout << "Filtergroesse: " << filterWidth << " x " << filterHeight << endl;
    //cout << endl;

    int halfFilterWidth = filterWidth / 2;
    int halfFilterHeight = filterHeight / 2;

    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    for (unsigned int i = 0; i < width * height; i++) {
        resultPixels[i] = 0;
    }

    // Minimum berechnen
    for (unsigned int x = halfFilterWidth; x < width - halfFilterWidth; x++) {
        for (unsigned int y = halfFilterHeight; y < height - halfFilterHeight; y++) {
            int min = 256;
            for (int l = -halfFilterWidth; l <= halfFilterWidth; l++) {
                for (int k = -halfFilterHeight; k <= halfFilterHeight; k++) {
                    if (pixels[(y + k) * width + (x + l)] < min) {
                        min = pixels[(y + k) * width + (x + l)];
                    }
                }
            }
            resultPixels[y * width + x] = min;
        }
    }


    // Ergebnis ins Originalbild kopieren
    memcpy(resultPixels, pixels, sizeof(pixels)); // destination, source, number of bytes to copy

    delete[] resultPixels; // Speicher wieder freigeben

    return true;
}

bool Pic::filterMax(unsigned int filterWidth, unsigned int filterHeight) {
    // Minimumsfilter


    // Falls Filtergröße gerade
    if (filterWidth % 2 != 1) {
        filterWidth++; // auf die nächstgrößten ungeraden Filtergröße erhöhen
    }

    if (filterHeight % 2 != 1) {
        filterHeight++; // auf die nächstgrößten ungeraden Filtergröße erhöhen
    }

    if (filterWidth > width || filterHeight > height) {
        return false; // Filtergröße zu groß
    }

    //cout << "Filtergroesse: " << filterWidth << " x " << filterHeight << endl;
    //cout << endl;

    int halfFilterWidth = filterWidth / 2;
    int halfFilterHeight = filterHeight / 2;

    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    for (unsigned int i = 0; i < width * height; i++) {
        resultPixels[i] = 0;
    }

    // Minimum berechnen
    for (unsigned int x = halfFilterWidth; x < width - halfFilterWidth; x++) {
        for (unsigned int y = halfFilterHeight; y < height - halfFilterHeight; y++) {
            int max = -1;
            for (int l = -halfFilterWidth; l <= halfFilterWidth; l++) {
                for (int k = -halfFilterHeight; k <= halfFilterHeight; k++) {
                    if (pixels[(y + k) * width + (x + l)] > max) {
                        max = pixels[(y + k) * width + (x + l)];
                    }
                }
            }
            resultPixels[y * width + x] = max;
        }
    }


    // Ergebnis ins Originalbild kopieren
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = resultPixels[i];
    }

    delete[] resultPixels; // Speicher wieder freigeben

    return true;
}

unsigned int Pic::getTotal(void) {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < size(); i++) {
        sum += pixels[i];
    }
    return sum;
}

const unsigned char* Pic::getPixels(void) {
    //ToDo Verifizieren, dass const in jeder Situation vor überschreiben schützt
    return pixels;
}

Pic::Pic() : width(800), height(600) {// Standardkonstruktor
    pixels = new unsigned char [width * height];
}

Pic::Pic(unsigned char* pixels, unsigned int width, unsigned int height) : pixels(pixels), width(width), height(height) {
    // Frage:
    // was passiert, wenn der Destruktor aufgerufen wird?
    // werden dann die pixel gelöscht?
    // Anwort:
    // Wenn die Pic Klasse aus einem Image erstellt wird
    // z. B. Pic test(image->bits(), image->width(), image->height());
    // dann werden auch nach der Zerstörung des test-Objeketes die Pixel des images erhalten
}

Pic::Pic(unsigned int width, unsigned int height) : width(width), height(height) {// Wertekonstruktor
    pixels = new unsigned char [width * height];
}

Pic::Pic(const Pic &p) {
    width = p.width;
    height = p.height;

    pixels = new unsigned char [width * height];

    unsigned char* z1 = pixels;
    unsigned char* z2 = p.pixels;

    for (unsigned int i = 0; i < width * height; i++) {
        *z1++ = *z2++;
    }
}

unsigned int Pic::getWidth () {
    return width;
}

unsigned int Pic::getHeight() {
    return height;
}

bool Pic::binarize(unsigned char thresh) {
    for (unsigned int i = 0; i < size(); i++) {
        if (pixels[i] < thresh) {
            pixels[i] = 0;
        }
        else {
            pixels[i] = 255;
        }
    }
    return true;
}

bool Pic::filterMedianHuang(unsigned int filterWidth, unsigned int filterHeight) {

    int leftFilterWidth = filterWidth / 2;
    int rightFilterWidth = filterWidth / 2;
    int topFilterHeight = filterHeight / 2;
    int bottomFilterHeight = filterHeight / 2;

    // Falls Filterbreite gerade
    if (filterWidth % 2 == 0) {
        rightFilterWidth--;
    }

    // Falls Filterhöhe gerade
    if (filterHeight % 2 != 1) {
        bottomFilterHeight--;
    }

    if (filterWidth > width || filterHeight > height) {
        return false; // Filtergröße zu groß
    }

    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    memset(resultPixels, 0, width * height);

    /* This algorithm ist doing median filtering of an image;
    This algorithm ignores border processing problem */

    int hist[256]; // histogram-array
    unsigned char mdn = 0; // Median-value
    int ltmdn = 0; // number of pixels having gray levels less than mdn in window
    //unsigned char leftcolumn[filterHeight]; // left-most column of the previous window
    //unsigned char rightcolumn[filterHeight]; // rightmost column of the current window

    int th = filterWidth * filterHeight / 2; // global parameter to help decide median

    for (unsigned int y = topFilterHeight; y < height - bottomFilterHeight; y++) { // über alle Zeilen
        // Histogramm auf 0 setzen
        for (int x = 0; x < 256; x++) {
            hist[x] = 0;
        }

        // Set up arry hist for the first window (in every line)
        for (int l = -leftFilterWidth; l <= rightFilterWidth; l++) {
            for (int k = -topFilterHeight; k <= bottomFilterHeight; k++) {
                hist[pixels[(y + k) * width + (leftFilterWidth + l)]]++;
            }
        }

        // find mdn by moving through the histogram bins
        int sum = 0;
        for (int i = 0; i < 256; i++) {
            sum += hist[i];
            if (sum > th) {
                mdn = i;
                ltmdn = sum - hist[i]; // updating count ltmdn
                i = 256; // aus der Schleife aussteigen!
            }
        }
        resultPixels[y * width + leftFilterWidth] = mdn;
        for (unsigned int x = leftFilterWidth + 1; x < width - rightFilterWidth; x++) { // über alle Spalten

            // update histogram
            // ToDo das hier in die oberen Schleifen packen?
            for (unsigned int i = 0; i < filterHeight; i++) {
                int g = pixels[(y - topFilterHeight + i) * width + x - leftFilterWidth - 1]; // leftcolumn[i]
                hist[g]--;
                if (g < mdn) { // check to update the counter ltmdn
                    ltmdn--;
                }
                /* widht + x + leftFilterWidht? */
                g = pixels[(y - topFilterHeight + i) * width + x + rightFilterWidth]; // rightcolumn[i]
                hist[g]++;
                if (g < mdn) {
                    ltmdn++;
                }
            }

            // find median
            if (ltmdn > th) {
                // the median in the current window is smaller than
                // the one in the prvious window
                while (ltmdn > th) {
                    mdn--;
                    ltmdn = ltmdn - hist[mdn]; // update counter ltmdn
                }
            }
            else {
                while(ltmdn + hist[mdn] <= th) {
                    ltmdn = ltmdn + hist[mdn]; // update counter ltmdn
                    mdn++; // move up one histogram bin
                }
            }
            resultPixels[y * width + x] = mdn;
        }
    }



    // Ergebnis ins Originalbild kopieren
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = resultPixels[i];
    }

    delete[] resultPixels; // Speicher wieder freigeben

    return true;
}

bool Pic::filterVNormalMedianHuang(const unsigned char* filter, unsigned int filterWidth, unsigned int filterHeight) {
    //ToDo V-Normalität der Filtermaske checken



    if (filterWidth > width || filterHeight > height) {
        return false; // Filtergröße zu groß
    }

    int leftFilterWidth = filterWidth / 2;
    int rightFilterWidth = filterWidth / 2;
    int topFilterHeight = filterHeight / 2;
    int bottomFilterHeight = filterHeight / 2;

    // Falls Filterbreite gerade
    if (filterWidth % 2 == 0) {
        rightFilterWidth--;
    }

    // Falls Filterhöhe gerade
    if (filterHeight % 2 == 0) {
        bottomFilterHeight--;
    }

    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    memset(resultPixels, 0, width * height);

    /* This algorithm ist doing median filtering of an image;
    This algorithm ignores border processing problem */

    int hist[256]; // histogram-array
    unsigned char mdn = 0; // Median-value
    int ltmdn = 0; // number of pixels having gray levels less than mdn in window
    unsigned char* leftcolumn = new unsigned char [filterHeight]; // left-most column of the previous window
    unsigned char* rightcolumn = new unsigned char [filterHeight]; // rightmost column of the current window

    int* leftFilterOffset = new int[filterHeight];
    int* rightFilterOffset = new int[filterHeight];

    for (unsigned int y = 0; y < filterHeight; y++) {
        for (unsigned int x = 0; x < filterWidth; x++) { // von links antasten
            if (filter[y * filterWidth + x] == 1) {
                leftFilterOffset[y] = x;
                x = filterWidth;
            }
        }
        for (unsigned int x = 0; x < filterWidth; x++) { // nochmal von rechts antasten
            if (filter[(y + 1) * filterWidth - 1 - x] == 1) {
                rightFilterOffset[y] = x;
                x = filterWidth;
            }
        }
    }



    int countFilterIndices = 0;
    for (unsigned int i = 0; i < filterWidth * filterHeight; i++) {
        if (filter[i] > 0) {
            countFilterIndices++;
        }
    }
    if (countFilterIndices < 1) {
        // alle Indizes der Filtermaske sind <= 0
        return false;
    }
    //cout << "countFilterIndices: " << countFilterIndices << endl;
    int th = countFilterIndices / 2;

    for (unsigned int y = topFilterHeight; y < height - bottomFilterHeight; y++) { // über alle Zeilen
        // Histogramm auf 0 setzen
        for (int x = 0; x < 256; x++) {
            hist[x] = 0;
        }

        // Set up arry hist for the first window (in every line)
        for (int l = -leftFilterWidth; l <= rightFilterWidth; l++) {
            for (int k = -topFilterHeight; k <= bottomFilterHeight; k++) {
                // only if index > 0 in filterMask
                if (filter[(k + topFilterHeight) * filterWidth + l + leftFilterWidth] != 0) {
                    hist[pixels[(y + k) * width + (leftFilterWidth + l)]]++;
                }
            }
        }



        // find mdn by moving through the histogram bins
        int sum = 0;
        for (int i = 0; i < 256; i++) {
            sum += hist[i];
            if (sum > th) {
                mdn = i;
                ltmdn = sum - hist[i]; // updating count ltmdn
                i = 256; // aus der Schleife aussteigen!
            }
        }
        resultPixels[y * width + leftFilterWidth] = mdn;
        for (unsigned int x = leftFilterWidth + 1; x < width - rightFilterWidth; x++) { // über alle Spalten


            // update histogram
            // ToDo das hier in die oberen Schleifen packen?
            for (unsigned int i = 0; i < filterHeight; i++) {
                int g = pixels[(y - topFilterHeight + i) * width + x - leftFilterWidth - 1 + leftFilterOffset[i]]; // leftcolumn[i]
                //cout << "geht raus: " << g << endl;
                hist[g]--;
                if (g < mdn) { // check to update the counter ltmdn
                    ltmdn--;
                }
                /* widht + x + leftFilterWidht? */
                g = pixels[(y - topFilterHeight + i) * width + x + rightFilterWidth - rightFilterOffset[i]]; // rightcolumn[i]
                //cout << "geht rein: " << g << endl;
                hist[g]++;
                if (g < mdn) {
                    ltmdn++;
                }
            }

            // find median
            if (ltmdn > th) {
                // the median in the current window is smaller than
                // the one in the prvious window
                while (ltmdn > th) {
                    mdn--;
                    ltmdn = ltmdn - hist[mdn]; // update counter ltmdn
                }
            }
            else {
                while(ltmdn + hist[mdn] <= th) {
                    ltmdn = ltmdn + hist[mdn]; // update counter ltmdn
                    mdn++; // move up one histogram bin
                }
            }
            resultPixels[y * width + x] = mdn;
        }
    }



    // Ergebnis ins Originalbild kopieren
    //ToDo Effizienter durch Pointer "umhängen"
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = resultPixels[i];
    }

    delete[] resultPixels; // Speicher wieder freigeben
    delete[] leftFilterOffset;
    delete[] rightFilterOffset;
    delete[] leftcolumn;
    delete[] rightcolumn;

    return true;
}

bool Pic::filterMedianHuang2(unsigned int filterWidth, unsigned int filterHeight) {

    // Falls Filterbreite gerade
    if (filterWidth % 2 != 1) {
        filterWidth++; // auf die nächstgrößten ungeraden Filterbreiteöße erhöhen
    }

    // Falls Filterhöhe gerade
    if (filterHeight % 2 != 1) {
        filterHeight++; // auf die nächstgrößten ungeraden Filterhöße erhöhen
    }

    if (filterWidth > width || filterHeight > height) {
        return false; // Filtergröße zu groß
    }

    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    memset(resultPixels, 0, width * height);

    /* This algorithm ist doing median filtering of an image;
    This algorithm ignores border processing problem */

    int hist[256]; // histogram-array
    unsigned char mdn = 0; // Median-value
    int ltmdn = 0; // number of pixels having gray levels less than mdn in window
    //unsigned char leftcolumn[filterHeight]; // left-most column of the previous window
    //unsigned char rightcolumn[filterHeight]; // rightmost column of the current window

    int th = filterWidth * filterHeight / 2; // global parameter to help decide median

    int halfFilterWidth = filterWidth / 2;
    int halfFilterHeight = filterHeight / 2;

    for (unsigned int y = halfFilterHeight; y < height - halfFilterHeight; y++) { // über alle Zeilen
        // Histogramm auf 0 setzen
        for (int x = 0; x < 256; x++) {
            hist[x] = 0;
        }

        // Set up arry hist for the first window (in every line)
        for (int l = -halfFilterWidth; l <= halfFilterWidth; l++) {
            for (int k = -halfFilterHeight; k <= halfFilterHeight; k++) {
                hist[pixels[(y + k) * width + (halfFilterWidth + l)]]++;
            }
        }

        // find mdn by moving through the histogram bins
        int sum = 0;
        for (int i = 0; i < 256; i++) {
            sum += hist[i];
            if (sum > th) {
                mdn = i;
                ltmdn = sum - hist[i]; // updating count ltmdn
                i = 256; // aus der Schleife aussteigen!
            }
        }
        resultPixels[y * width + halfFilterWidth] = mdn;
        for (unsigned int x = halfFilterWidth + 1; x < width - halfFilterWidth; x++) { // über alle Spalten


            // update histogram
            // ToDo das hier in die oberen Schleifen packen?
            for (unsigned int i = 0; i < filterHeight; i++) {
                int g = pixels[(y - halfFilterHeight + i) * width + x - halfFilterWidth - 1]; // leftcolumn[i]
                hist[g]--;
                if (g < mdn) { // check to update the counter ltmdn
                    ltmdn--;
                }
                g = pixels[(y - halfFilterHeight + i) * width + x + halfFilterWidth]; // rightcolumn[i]
                hist[g]++;
                if (g < mdn) {
                    ltmdn++;
                }
            }

            // find median
            if (ltmdn > th) {
                // the median in the current window is smaller than
                // the one in the prvious window
                while (ltmdn > th) {
                    mdn--;
                    ltmdn = ltmdn - hist[mdn]; // update counter ltmdn
                }
            }
            else {
                while(ltmdn + hist[mdn] <= th) {
                    ltmdn = ltmdn + hist[mdn]; // update counter ltmdn
                    mdn++; // move up one histogram bin
                }
            }
            resultPixels[y * width + x] = mdn;
        }
    }



    // Ergebnis ins Originalbild kopieren
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = resultPixels[i];
    }

    delete[] resultPixels; // Speicher wieder freigeben
    //delete[] leftcolumn;
    //delete[] rightcolumn;

    return true;
}

bool Pic::filterQuantilHuang(unsigned int filterWidth, unsigned int filterHeight, double quantil) {
    // quantil prüfen
    if (quantil < 0.0 || quantil > 1.0) {
        return false;
    }


    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    memset(resultPixels, 0, width * height);

    /* This algorithm ist doing median filtering of an image;
    This algorithm ignores border processing problem */

    int hist[256]; // histogram-array
    unsigned char mdn = 0; // Median-value
    int ltmdn = 0; // number of pixels having gray levels less than mdn in window
    //unsigned char leftcolumn[filterHeight]; // left-most column of the previous window
    //unsigned char rightcolumn[filterHeight]; // rightmost column of the current window

    int th = 0;
    if (quantil < 1.0) {
        th = (int) filterWidth * filterHeight * quantil; // global parameter to help decide median
    }
    else {
        th = filterWidth * filterHeight - 1;
    }

    int halfFilterWidth = filterWidth / 2;
    int halfFilterHeight = filterHeight / 2;

    for (unsigned int y = halfFilterHeight; y < height - halfFilterHeight; y++) { // über alle Zeilen
        // Histogramm auf 0 setzen
        memset(hist, 0, sizeof(hist));

        // Set up arry hist for the first window (in every line)
        for (int l = -halfFilterWidth; l <= halfFilterWidth; l++) {
            for (int k = -halfFilterHeight; k <= halfFilterHeight; k++) {
                hist[pixels[(y + k) * width + (halfFilterWidth + l)]]++;
            }
        }

        // find mdn by moving through the histogram bins
        int sum = 0;
        for (int i = 0; i < 256; i++) {
            sum += hist[i];
            if (sum > th) {
                mdn = i;
                ltmdn = sum - hist[i]; // updating count ltmdn
                i = 256; // aus der Schleife aussteigen!
            }
        }
        resultPixels[y * width + halfFilterWidth] = mdn;
        for (unsigned int x = halfFilterWidth + 1; x < width - halfFilterWidth; x++) { // über alle Spalten

            //cout << endl;

            // update histogram
            // ToDo das hier in die oberen Schleifen packen?
            for (unsigned int i = 0; i < filterHeight; i++) {
                int g = pixels[(y - halfFilterHeight + i) * width + x - halfFilterWidth - 1]; // leftcolumn[i]
                hist[g]--;
                if (g < mdn) { // check to update the counter ltmdn
                    ltmdn--;
                }
                g = pixels[(y - halfFilterHeight + i) * width + x + halfFilterWidth]; // rightcolumn[i]
                hist[g]++;
                if (g < mdn) {
                    ltmdn++;
                }
            }

            // find median
            if (ltmdn > th) {
                // the median in the current window is smaller than
                // the one in the prvious window
                while (ltmdn > th) {
                    mdn--;
                    ltmdn = ltmdn - hist[mdn]; // update counter ltmdn
                }
            }
            else {
                while(ltmdn + hist[mdn] <= th) {
                    ltmdn = ltmdn + hist[mdn]; // update counter ltmdn
                    mdn++; // move up one histogram bin
                }
            }
            resultPixels[y * width + x] = mdn;
        }
    }



    // Ergebnis ins Originalbild kopieren
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = resultPixels[i];
    }

    delete[] resultPixels; // Speicher wieder freigeben

    return true;
}

// deprecated
/*bool Pic::filterMedian (unsigned int filterWidth, unsigned int filterHeight) {


    // Falls Filtergröße gerade
    if (filterWidth % 2 != 1) {
        filterWidth++; // auf die nächstgrößten ungeraden Filtergröße erhöhen
    }

    if (filterHeight % 2 != 1) {
        filterHeight++; // auf die nächstgrößten ungeraden Filtergröße erhöhen
    }

    if (filterWidth > width || filterHeight > height) {
        return false; // Filtergröße zu groß
    }

    //cout << "Filtergroesse: " << filterWidth << " x " << filterHeight << endl;
    //cout << endl;

    int halfFilterWidth = filterWidth / 2;
    int halfFilterHeight = filterHeight / 2;

    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    for (unsigned int i = 0; i < width * height; i++) {
        resultPixels[i] = 0;
    }

    // Median berechnen
    for (unsigned int x = halfFilterWidth; x < width - halfFilterWidth; x++) {
        for (unsigned int y = halfFilterHeight; y < height - halfFilterHeight; y++) {
            //ToDo Variante ohne Vektor programmieren

            vector<unsigned char> vec;
            // Median Vektor füllen
            for (int l = -halfFilterWidth; l <= halfFilterWidth; l++) {
                for (int k = -halfFilterHeight; k <= halfFilterHeight; k++) {
                    vec.push_back(pixels[(y + k) * width + (x + l)]);
                }
            }

            // Vektorisieren
            //sort(vec.begin(), vec.end());

            resultPixels[y * width + x] = vec[vec.size() / 2];



        }
    }


    // Ergebnis ins Originalbild kopieren
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = resultPixels[i];
    }

    delete[] resultPixels; // Speicher wieder freigeben

    return true;
}
*/

bool Pic::filterQuantil (unsigned int filterWidth, unsigned int filterHeight, double quantil) {
    // quantil prüfen
    if (quantil < 0.0 || quantil > 1.0) {
        return false;
    }

    // Falls Filtergröße gerade
    if (filterWidth % 2 != 1) {
        filterWidth++; // auf die nächstgrößten ungeraden Filtergröße erhöhen
    }

    if (filterHeight % 2 != 1) {
        filterHeight++; // auf die nächstgrößten ungeraden Filtergröße erhöhen
    }

    if (filterWidth > width || filterHeight > height) {
        return false; // Filtergröße zu groß
    }

    //cout << "Filtergroesse: " << filterWidth << " x " << filterHeight << endl;
    //cout << endl;

    int halfFilterWidth = filterWidth / 2;
    int halfFilterHeight = filterHeight / 2;

    // Speicher für Resultatbild anlegen und mit 0 initalisieren
    unsigned char* resultPixels = new unsigned char [width * height];
    for (unsigned int i = 0; i < width * height; i++) {
        resultPixels[i] = 0;
    }

    // Median berechnen
    for (unsigned int x = halfFilterWidth; x < width - halfFilterWidth; x++) {
        for (unsigned int y = halfFilterHeight; y < height - halfFilterHeight; y++) {
            //ToDo Variante ohne Vektor programmieren

            vector<unsigned char> vec;
            // Median Vektor füllen
            for (int l = -halfFilterWidth; l <= halfFilterWidth; l++) {
                for (int k = -halfFilterHeight; k <= halfFilterHeight; k++) {
                    vec.push_back(pixels[(y + k) * width + (x + l)]);
                }
            }

            // Vektor sortieren
            //sort(vec.begin(), vec.end());

            if (quantil < 1.0) {
                resultPixels[y * width + x] = vec[(int) vec.size() * quantil];
            }
            else {
                resultPixels[y * width + x] = vec[vec.size() - 1];
            }

        }
    }


    // Ergebnis ins Originalbild kopieren
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = resultPixels[i];
    }

    delete[] resultPixels; // Speicher wieder freigeben

    return true;
}


Pic& Pic::operator= (const Pic &p)
                    {
    if (&p != this)
    {
        delete[] pixels;

        width = p.width;
        height = p.height;

        pixels = new unsigned char [width * height];

        unsigned char* z1 = pixels;
        unsigned char* z2 = p.pixels;

        for (unsigned int i = 0; i < width * height; i++)
            *z1++ = *z2++;

    }
    return *this;
}


Pic& Pic::operator +=(const Pic& p) {
    if (&p != this) {
        unsigned char* z1 = pixels;
        unsigned char* z2 = p.pixels;

        if ((p.width == width) && (p.height == height)) {
            for (unsigned int i = 0; i < size(); i++) {
                *z1 = ((*z1) + (*z2)) / 2;
                *z1++;
                *z2++;
            }
        }
    }
    return *this;
}

Pic& Pic::operator+ (const Pic &p)
{
    static Pic temp(width, height);

    if ((p.width == width) && (p.height == height)) {
        unsigned char* z1 = pixels;
        unsigned char* z2 = p.pixels;
        unsigned char* z3 = temp.pixels;

        for (unsigned int i = 0; i < width * height; i++)
            z3[i] = ((z1[i] + z2[i]) / 2);
    }
    return temp;
}

Pic& Pic::operator -=(const Pic& p)
                     {
    if (&p != this) {
        unsigned char* z1 = pixels;
        unsigned char* z2 = p.pixels;

        if ((p.width == width) && (p.height == height)) {
            for (unsigned int i = 0; i < width * height; i++) {
                if (z1[i] - z2[i] > 0)
                    z1[i] = (z1[i] - z2[i]);
                else
                    z1[i] = 0;
            }
        }
    }
    return *this;
}

Pic& Pic::operator- (const Pic &p)
{
    static Pic temp(width, height);

    if ((p.width == width) && (p.height == height)) {
        unsigned char* z1 = pixels;
        unsigned char* z2 = p.pixels;
        unsigned char* z3 = temp.pixels;

        for (unsigned int i = 0; i < width * height; i++) {
            if (z1[i] - z2[i] > 0)
                z3[i] = (z1[i] - z2[i]);
            else
                z3[i] = 0;
        }

    }
    return temp;
}

unsigned char Pic::getPixelValue(unsigned int x, unsigned int y) {
    if (x >= width || y >= height) {
        return 0; // ToDo 0 ist nicht aussagekräftig
    }
    return pixels[y * width + x];
}

bool Pic::initPic(unsigned int mode) {
    // mode
    // 1 - black
    // 2 - white
    // 3 - random
    // 4 - serial
    // ToDo
    // 5 - horizontaler Grauwertkeil
    // - horizontaler periodischer Grauwertkeil
    // 6 - vertikaler Grauwertkeil
    // - vertikal periodischer Grauwertkeil
    // 7 - schräger Grauwertkeil
    // 8 - schräger periodischer Grauwertkeil
    // 9 - Kreismuster (image_jaehne aus ipp)

    //ToDo: switch-case Anweisung wäre wohl eleganter
    if (mode == 1) { // black pic
        memset(pixels, 0, width * height);
        return true;
    }
    if (mode == 2) { // white pic
        memset(pixels, 255, width * height);
        return true;
    }
    if (mode == 3) { // random pic
        srand(23); //ToDo: richtiger seed mit Datum und Zeit
        for (unsigned int i = 0; i < width * height; i++) {
            pixels[i] = 128 + rand() % 10;
            //pixels[i] = rand() % 256;
        }
        return true;
    }
    if (mode == 4) { // 0, 1, 2 ... 255, 0, 1, ...
        for (unsigned int i = 0; i < width * height; i++) {
            pixels[i] = i % 256;
        }
        return true;
    }
    return true;
}

//bool generarteStripes(unsigned int stripeWidth, unsigned int offset, bool bothDirections, bool rotate, bool invert);
bool Pic::generarteStripes(unsigned int stripeWidth, unsigned int stripeType, unsigned int offset,  bool invert) {
    for (unsigned x = 0; x < width; x++) {
        for(unsigned y = 0; y < height; y++) {
            if ((stripeType % 2) == 1) {
                // 0 Grad
                pixels[y*width + x] += ((y + offset) % (2 * stripeWidth)) / stripeWidth;
                //pixels[y*width + x] += ((x + offset) % (2 * stripeWidth)) / stripeWidth;
            }

            /*
            if (rotate) {
                pixels[y*width + x] += (int(getDistance(0, 0, x + offset, y + offset, 2)) % (2 * stripeWidth)) / stripeWidth;
                if (bothDirections) {
                    pixels[y*width + x] += (int(getDistance(0, width-1, x + offset, y + offset, 2)) % (2 * stripeWidth)) / stripeWidth;
                    pixels[y*width + x] = pixels[y*width + x] % 2;
                }
            }
            else {
                pixels[y*width + x] += ((x + offset) % (2 * stripeWidth)) / stripeWidth;
                if (bothDirections) {
                    pixels[y*width + x] += ((y + offset) % (2 * stripeWidth)) / stripeWidth;
                    pixels[y*width + x] = pixels[y*width + x] % 2;
                }
            }
            if (invert) {
                if (pixels[y*width + x] == 1) {
                    pixels[y*width + x] = 0;
                }
                else {
                    pixels[y*width + x] = 1;
                }
            }
            // 1 -> 255
            if (pixels[y*width + x] == 1) {
                pixels[y*width + x] = 255;
            }
            */
        }
    }
    return true;
}

bool Pic::spread() {
    unsigned char maximum = getMaximum();
    unsigned char minimum = getMinimum();
    if ((maximum - minimum) == 0) {
        return true;
    }
    // auf 0 runterziehen
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] -= minimum;
    }
    // spreizen
    for (unsigned int i = 0; i < width * height; i++) {
        pixels[i] = pixels[i] * 255 / (maximum - minimum);
    }
    return true;
}

unsigned char Pic::getMaximum() {
    unsigned char maximum = 0;
    for (unsigned int i = 0; i < width * height; i++) {
        if (pixels[i] > maximum) {
            maximum = pixels[i];
        }
    }
    return maximum;
}

unsigned char Pic::getMinimum() {
    unsigned char minimum = 255;
    for (unsigned int i = 0; i < width * height; i++) {
        if (pixels[i] < minimum) {
            minimum = pixels[i];
        }
    }
    return minimum;
}

bool Pic::writeRAW(char* name) {
    ofstream ofs(name, ios_base::binary);
    if (!ofs) {
        return false;
    }
    if (ofs.write((char*) pixels, width * height)) {
        return true;
    }
    else {
        return false;
    }
}

bool Pic::readRAW(char* name) {
    ifstream ifs(name, ios_base::binary);
    if (!ifs) {
        return false;
    }
    if (ifs.read((char*) pixels, width * height)) {
        return true;
    }
    else {
        return false;
    }
}

bool Pic::writePGM(char* name) {
    int error = 0;
    FILE *fp;
    fp = fopen(name, "wb");// <- Use binary format !!!!
    if (0 == fp) //->_ptr
    {
        return false;
    }

    error = fprintf(fp, "P5\n%d %d\n255\n", width, height);
    if (0 > error)
    {
        return false;
    }
    fwrite(pixels, 1, width * height, fp);
    fclose(fp);
    return true;
}

bool Pic::setPixelValue(unsigned int x, unsigned int y, unsigned char value) {
    pixels[y * width + x] = value;
    return true;
}

bool Pic::markLine(unsigned int lineNumber, unsigned char value) {
    if (lineNumber >= height) { // befinden wir uns ausserhalb des Bildes?
        return false;
    }
    memset(&pixels[lineNumber * width], value, width);
    return true;
}

bool Pic::markColumn(unsigned int columnNumber, unsigned char value) {
    if (columnNumber >= width) { // befinden wir uns ausserhalb des Bildes?
        return false;
    }
    for (unsigned int i = 0; i < height; i++) {
        pixels[i * width + columnNumber] = value;
    }
    return true;
}

Pic::~Pic() { // Destruktor
    delete[] pixels;
}
