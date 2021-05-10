typedef struct Color
{
  const byte red;
  const byte green;
  const byte blue;

  Color(const byte red, const byte green, const byte blue)
      : red(red),
        green(green),
        blue(blue){};

  Color(const int hexColor)
      : red((hexColor >> 0x10) & 0xFF),
        green((hexColor >> 010) & 0xFF),
        blue(hexColor & 0xFF){};

  const Color operator+(const Color other) const
  {
    return {
        average(this->red, other.red),
        average(this->green, other.green),
        average(this->blue, other.blue),
    };
  }

  const int getHex() const
  {
    return (this->red << 0x10) + (this->green << 010) + this->blue;
  };

} Color;

const int average(const int x, const int y)
{
  return int(x + y / 2);
};

#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define PURPLE 0xFF00FF
#define YELLOW 0xFFFF00
#define CYAN 0x00FFFF