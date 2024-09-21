#ifndef __IR_CODES__
#define __IR_CODES__

class irTvCodes {
public:
  typedef enum {
    NONE,
    SONY,
    PANASONIC,
    LG,
    JVC,
    SHARP,
    SAMSUNG,
    NEC,
    END,
    TECHNIKA
  }type_e;

  static unsigned long getPowerCode(type_e type) {
    switch(type) {
      case SONY:
        return 0xa90;
      case PANASONIC:
        return 0x0100BCBD;
      case LG:
        return 0x20DF10EF;
      case JVC:
        return 0xC5E8;
      case SHARP:
        return 0x41A2;
      case SAMSUNG:
        return 0xE0E040BF;
      case NEC:
        return 0x12345678;
      case TECHNIKA:
        return 0xFE50AF;
      default:
        return 0xF0F;
    }
  }
  static unsigned long getChanDownCode(type_e type) {
    switch(type) {
      case SONY:
        return 0x890;
      case PANASONIC:
        return 0x0100ACAD;
      case LG:
        return 0x20DF807F;
      case JVC:
        return 0xCD06;
      case SHARP:
        return 0x4122;
      case SAMSUNG:
        return 0xE0E008F7;
      case NEC:
        return 0x12345678;
      case TECHNIKA:
        return 0xFE3AC5;
      default:
        return 0xF0F;
    }
  }
  static unsigned long getChanUpCode(type_e type) {
    switch(type) {
      case SONY:
        return 0x090;
      case PANASONIC:
        return 0x01002C2D;
      case LG:
        return 0x20DF00FF;
      case JVC:
        return 0xCDF6;
      case SHARP:
        return 0x4222;
      case SAMSUNG:
        return 0xE0E048B7;
      case NEC:
        return 0x12345678;
      case TECHNIKA:
        return 0xFEF807;
      default:
        return 0xF0F;
    }
  }
  static unsigned long getVolDownCode(type_e type) {
    switch(type) {
      case SONY:
        return 0xC90;
      case PANASONIC:
        return 0x01008485;
      case LG:
        return 0x20DFC03F;
      case JVC:
        return 0xC5F8;
      case SHARP:
        return 0x42A2;
      case SAMSUNG:
        return 0xE0E0D02F;
      case NEC:
        return 0x12345678;
      case TECHNIKA:
        return 0xFEFA05;
      default:
        return 0xF0F;
    }
  }
  static unsigned long getVolUpCode(type_e type) {
    switch(type) {
      case SONY:
        return 0x490;
      case PANASONIC:
        return 0x01000405;
      case LG:
        return 0x20DF40BF;
      case JVC:
        return 0xC578;
      case SHARP:
        return 0x40A2;
      case SAMSUNG:
        return 0xE0E0E01F;
      case NEC:
        return 0x12345678;
      case TECHNIKA:
        return 0xFE7887;
      default:
        return 0xF0F;
    }
  }
  static unsigned long getSourceCode(type_e type) {
    return 0xF0F;
      switch(type) {
      case SONY:
        return 0xA50;
      case PANASONIC:
        return 0x0100A0A1;
      case LG:
        return 0x20DF40BF;
      case JVC:
        return 0xC1C0;
      case SHARP:
        return 0x4322;
      case SAMSUNG:
        return 0xE0E0807F;
      case NEC:
        return 0x12345678;
      case TECHNIKA:
        return 0xFE50AF;
      default:
        return 0xF0F;
    }
  }
  static unsigned long getGuideCode(type_e type) {
    switch(type) {
      case SONY:
        return 0x070;
      case PANASONIC:
        return 0x01000405;
      case LG:
        return 0x20DF40BF;
      case JVC:
        return 0xC53C;
      case SHARP:
        return 0x458E;
      case SAMSUNG:
        return 0xE0E0F20D;
      case NEC:
        return 0x12345678;
      case TECHNIKA:
        return 0xFE50AF;
      default:
        return 0xF0F;
    }
  }

  static unsigned long getMediaCode(type_e type) {
    switch(type) {
      case SONY:
        return 0x5D0;
      case PANASONIC:
        return 0x01006061;
      case LG:
        return 0x20DF40BF;
      case JVC:
        return 0xC5D0;
      case SHARP:
        return 0x40A2;
      case SAMSUNG:
        return 0xE0E0E21D;
      case NEC:
        return 0x12345678;
      case TECHNIKA:
        return 0xFE50AF;
      default:
        return 0xF0F;
    }
  }

  static unsigned long getCustomCode(char* type) {

  }
};

#endif