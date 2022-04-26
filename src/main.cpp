#include <Arduino.h>

constexpr uint32_t led = LED_BUILTIN;

constexpr uint8_t pins[] = {PA0, PA1, PB9, PA2, PA3, PB15, PB13};

constexpr uint32_t max_segments = 37;

typedef struct
{
  uint8_t low;
  uint8_t high;
  bool turn_on;
} SEGMENT;

constexpr SEGMENT NON = {0, 0};
constexpr SEGMENT S1F = {1, 2};
constexpr SEGMENT S1G = {1, 3};
constexpr SEGMENT S1C = {1, 4};
constexpr SEGMENT S1D = {1, 5};
constexpr SEGMENT S3D = {1, 6};
constexpr SEGMENT S1B = {3, 1};
constexpr SEGMENT S2A = {3, 2};
constexpr SEGMENT S3F = {3, 4};
constexpr SEGMENT S3G = {3, 5};
constexpr SEGMENT S3E = {3, 6};
constexpr SEGMENT S5F = {3, 7};
constexpr SEGMENT S5D = {5, 1};
constexpr SEGMENT S2E = {5, 2};
constexpr SEGMENT S3B = {5, 3};
constexpr SEGMENT S3C = {5, 4};
constexpr SEGMENT S4F = {5, 6};
constexpr SEGMENT S5H = {5, 7};
constexpr SEGMENT S1A = {2, 1};
constexpr SEGMENT S2F = {2, 3};
constexpr SEGMENT S2G = {2, 4};
constexpr SEGMENT S2C = {2, 5};
constexpr SEGMENT S5C = {2, 6};
constexpr SEGMENT S1E = {4, 1};
constexpr SEGMENT S2B = {4, 2};
constexpr SEGMENT S5E = {4, 3};
constexpr SEGMENT S3A = {4, 5};
constexpr SEGMENT S4D = {4, 6};
constexpr SEGMENT S5A = {6, 1};
constexpr SEGMENT S2D = {6, 2};
constexpr SEGMENT S5B = {6, 3};
constexpr SEGMENT S4E = {6, 4};
constexpr SEGMENT S4C = {6, 5};
constexpr SEGMENT S4A = {6, 7};
constexpr SEGMENT S5G = {7, 3};
constexpr SEGMENT S4G = {7, 5};
constexpr SEGMENT S4B = {7, 6};

enum
{
  NNON = 0,
  NS1F = 1,
  NS1G = 2,
  NS1C = 3,
  NS1D = 4,
  NS3D = 5,
  NS1B = 6,
  NS2A = 7,
  NS3F = 8,
  NS3G = 9,
  NS3E = 10,
  NS5F = 11,
  NS5D = 12,
  NS2E = 13,
  NS3B = 14,
  NS3C = 15,
  NS4F = 16,
  NS5H = 17,
  NS1A = 18,
  NS2F = 19,
  NS2G = 20,
  NS2C = 21,
  NS5C = 22,
  NS1E = 23,
  NS2B = 24,
  NS5E = 25,
  NS3A = 26,
  NS4D = 27,
  NS5A = 28,
  NS2D = 29,
  NS5B = 30,
  NS4E = 31,
  NS4C = 32,
  NS4A = 33,
  NS5G = 34,
  NS4G = 35,
  NS4B = 36,
};

SEGMENT display_map[] = {
    NON,
    S1F,
    S1G,
    S1C,
    S1D,
    S3D,
    S1B,
    S2A,
    S3F,
    S3G,
    S3E,
    S5F,
    S5D,
    S2E,
    S3B,
    S3C,
    S4F,
    S5H,
    S1A,
    S2F,
    S2G,
    S2C,
    S5C,
    S1E,
    S2B,
    S5E,
    S3A,
    S4D,
    S5A,
    S2D,
    S5B,
    S4E,
    S4C,
    S4A,
    S5G,
    S4G,
    S4B,
};

constexpr uint8_t digitals[10][4][7] = {
    // 0
    {
        {NS1F, NS1E, NS1D, NS1C, NS1B, NS1A},
        {NS2F, NS2E, NS2D, NS2C, NS2B, NS2A},
        {NS3F, NS3E, NS3D, NS3C, NS3B, NS3A},
        {NS4F, NS4E, NS4D, NS4C, NS4B, NS4A}},
    // 1
    {
        {NS1B, NS1C},
        {NS2B, NS2C},
        {NS3B, NS3C},
        {NS4B, NS4C}},
    // 2
    {
        {NS1A, NS1B, NS1G, NS1E, NS1D},
        {NS2A, NS2B, NS2G, NS2E, NS2D},
        {NS3A, NS3B, NS3G, NS3E, NS3D},
        {NS4A, NS4B, NS4G, NS4E, NS4D}},
    // 3
    {
        {NS1A, NS1B, NS1G, NS1C, NS1D},
        {NS2A, NS2B, NS2G, NS2C, NS2D},
        {NS3A, NS3B, NS3G, NS3C, NS3D},
        {NS4A, NS4B, NS4G, NS4C, NS4D}},
    // 4
    {
        {NS1F, NS1G, NS1B, NS1C},
        {NS2F, NS2G, NS2B, NS2C},
        {NS3F, NS3G, NS3B, NS3C},
        {NS4F, NS4G, NS4B, NS4C}},
    // 5
    {
        {NS1A, NS1F, NS1G, NS1C, NS1D},
        {NS2A, NS2F, NS2G, NS2C, NS2D},
        {NS3A, NS3F, NS3G, NS3C, NS3D},
        {NS4A, NS4F, NS4G, NS4C, NS4D}},
    // 6
    {
        {NS1A, NS1F, NS1E, NS1D, NS1C, NS1G},
        {NS2A, NS2F, NS2E, NS2D, NS2C, NS2G},
        {NS3A, NS3F, NS3E, NS3D, NS3C, NS3G},
        {NS4A, NS4F, NS4E, NS4D, NS4C, NS4G}},
    // 7
    {
        {NS1A, NS1B, NS1C},
        {NS2A, NS2B, NS2C},
        {NS3A, NS3B, NS3C},
        {NS4A, NS4B, NS4C}},
    // 8
    {
        {NS1A, NS1B, NS1C, NS1D, NS1E, NS1F, NS1G},
        {NS2A, NS2B, NS2C, NS2D, NS2E, NS2F, NS2G},
        {NS3A, NS3B, NS3C, NS3D, NS3E, NS3F, NS3G},
        {NS4A, NS4B, NS4C, NS4D, NS4E, NS4F, NS4G}},
    // 9
    {
        {NS1A, NS1B, NS1C, NS1D, NS1F, NS1G},
        {NS2A, NS2B, NS2C, NS2D, NS2F, NS2G},
        {NS3A, NS3B, NS3C, NS3D, NS3F, NS3G},
        {NS4A, NS4B, NS4C, NS4D, NS4F, NS4G}}

};

enum
{
  ICON_TF = 0,
  ICON_FM,
  ICON_USB,
  ICON_REC,
  ICON_COLON,
  ICON_BAT_FULL,
  ICON_BAT_EMPTY,
  ICON_DOT,
};

constexpr uint8_t icons[] = {
    NS5A,
    NS5B,
    NS5C,
    NS5D,
    NS5E,
    NS5F,
    NS5G,
    NS5H,
};

volatile uint8_t current_display_pos = 0;
HardwareTimer *display_timer = nullptr;

void refresh_next_segment()
{
  digitalToggle(led);
  uint8_t last_display_pos = 0;
  if (current_display_pos == 0)
  {
    last_display_pos = max_segments - 1;
  }
  else
  {
    last_display_pos = current_display_pos - 1;
  }
  // turn off last_display_pos
  {
    uint8_t p_low = display_map[last_display_pos].low;
    uint8_t p_high = display_map[last_display_pos].high;
    if ((p_low != 0) && (p_high != 0))
    {
      pinMode(pins[p_low - 1], INPUT);
      pinMode(pins[p_high - 1], INPUT);
    }
  }
  // turn on current_display_pos
  {
    uint8_t p_low = display_map[current_display_pos].low;
    uint8_t p_high = display_map[current_display_pos].high;
    bool turn_on = display_map[current_display_pos].turn_on;

    if ((p_low != 0) && (p_high != 0) && turn_on)
    {
      pinMode(pins[p_low - 1], OUTPUT);
      digitalWrite(pins[p_low - 1], LOW);
      pinMode(pins[p_high - 1], OUTPUT);
      digitalWrite(pins[p_high - 1], HIGH);
    }
  }
  current_display_pos++;
  if (current_display_pos >= max_segments)
  {
    current_display_pos = 0;
  }
}

void turn_off_all_segments()
{
  for (auto &s : display_map)
  {
    s.turn_on = false;
  }
}

void turn_on_segment(uint8_t s)
{
  if (s == NNON)
  {
    return;
  }
  display_map[s].turn_on = true;
}

void turn_off_display()
{
  for (auto p : pins)
  {
    pinMode(p, INPUT);
  }
}

void display_icon(const uint8_t icon)
{
  if (icon >= 8)
  {
    return;
  }
  turn_on_segment(icons[icon]);
}

void display_number(uint32_t n)
{
  if (n > 9999)
  {
    n = n % 10000;
  }

  uint32_t nd = 1;
  for (;;)
  {
    uint32_t d = n % 10;
    auto segs = digitals[d][4 - nd];
    for (int i = 0; i < 7; i++)
    {
      turn_on_segment(segs[i]);
    }
    nd++;
    n = n / 10;
    if (n == 0)
    {
      break;
    }
  }
}

uint8_t icon_n = 0;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(115200);

  turn_off_display();
  turn_off_all_segments();
  display_timer = new HardwareTimer(TIM1);
  display_timer->setOverflow(2000, HERTZ_FORMAT);
  display_timer->attachInterrupt(refresh_next_segment);
  display_timer->resume();
}

uint32_t last_change = millis();
uint32_t n = 0;

void loop()
{
  if (millis() - last_change > 100)
  {
    // display_timer->pause();
    // turn_off_display();
    turn_off_all_segments();
    last_change = millis();

    if (n >= 10000)
    {
      n = 0;
    }
    display_number(n);
    n++;

    if (icon_n >= 8)
    {
      icon_n = 0;
    }
    display_icon(icon_n);
    icon_n++;
    // display_timer->resume();
  }
}