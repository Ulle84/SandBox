#include <QCoreApplication>
#include <iostream>

#define SET_BIT(val, bitIndex) val |= (1 << bitIndex)
#define CLEAR_BIT(val, bitIndex) val &= ~(1 << bitIndex)
#define TOGGLE_BIT(val, bitIndex) val ^= (1 << bitIndex)
#define BIT_IS_SET(val, bitIndex) (val & (1 << bitIndex))

class BitField {
public:
    bool bit0 : 1;
    bool bit1 : 1;
    bool bit2 : 1;
    bool bit3 : 1;
    bool bit4 : 1;
    bool bit5 : 1;
    bool bit6 : 1;
    bool bit7 : 1;

    friend std::ostream& operator<< (std::ostream& stream, const BitField& bitField);
};

std::ostream& operator<< (std::ostream& stream, const BitField& bitField)
{
  stream << bitField.bit0 ? 0 : 1;
  stream << bitField.bit1 ? 0 : 1;
  stream << bitField.bit2 ? 0 : 1;
  stream << bitField.bit3 ? 0 : 1;
  stream << " ";
  stream << bitField.bit4 ? 0 : 1;
  stream << bitField.bit5 ? 0 : 1;
  stream << bitField.bit6 ? 0 : 1;
  stream << bitField.bit7 ? 0 : 1;
  return stream;
}



int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  BitField bitField;
  bitField.bit0 = true;
  bitField.bit1 = false;
  bitField.bit2 = true;
  bitField.bit3 = false;
  bitField.bit4 = true;
  bitField.bit5 = false;
  bitField.bit6 = true;
  bitField.bit7 = false;

  std::cout << sizeof(bitField) << std::endl;
  std::cout << bitField << std::endl;

  return a.exec();
}
