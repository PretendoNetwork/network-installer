static const unsigned char arm_kernel_bin[] = {
  0xea, 0x00, 0x00, 0x06, 0xe3, 0xa0, 0x30, 0x00, 0xe1, 0x53, 0x00, 0x02,
  0x01, 0x2f, 0xff, 0x1e, 0xe7, 0xd1, 0xc0, 0x03, 0xe7, 0xc0, 0xc0, 0x03,
  0xe2, 0x83, 0x30, 0x01, 0xea, 0xff, 0xff, 0xf9, 0xe9, 0x2d, 0x40, 0x70,
  0xe5, 0x9f, 0x41, 0x34, 0xe5, 0x9f, 0x11, 0x34, 0xe2, 0x84, 0x3f, 0x92,
  0xe3, 0xa0, 0x2b, 0x01, 0xe3, 0xa0, 0x00, 0x00, 0xe1, 0x2f, 0xff, 0x33,
  0xeb, 0x00, 0x00, 0x57, 0xe1, 0xa0, 0x60, 0x00, 0xeb, 0x00, 0x00, 0x5e,
  0xe1, 0xa0, 0x50, 0x00, 0xeb, 0x00, 0x00, 0x57, 0xe3, 0x85, 0x00, 0xc0,
  0xeb, 0x00, 0x00, 0x5c, 0xe3, 0xc6, 0x0a, 0x01, 0xe3, 0xc0, 0x00, 0x05,
  0xeb, 0x00, 0x00, 0x50, 0xe5, 0x9f, 0x30, 0xfc, 0xe5, 0x9f, 0x20, 0xfc,
  0xe1, 0xa0, 0x00, 0x04, 0xe5, 0x83, 0x2a, 0x24, 0xe5, 0x9f, 0x10, 0xf4,
  0xe3, 0xa0, 0x20, 0x38, 0xeb, 0xff, 0xff, 0xe0, 0xe5, 0x9f, 0x30, 0xec,
  0xe5, 0x9f, 0x00, 0xec, 0xe5, 0x93, 0x2d, 0x18, 0xe5, 0x9f, 0x30, 0xe8,
  0xe2, 0x81, 0x10, 0x38, 0xe5, 0x83, 0x20, 0x00, 0xe3, 0xa0, 0x20, 0x68,
  0xeb, 0xff, 0xff, 0xd8, 0xe3, 0xa0, 0x39, 0x52, 0xe2, 0x80, 0x0a, 0x31,
  0xe5, 0x93, 0x20, 0x00, 0xe5, 0x9f, 0x10, 0xcc, 0xe2, 0x80, 0x0f, 0x57,
  0xeb, 0xff, 0xff, 0xd2, 0xe5, 0x9f, 0x20, 0xc4, 0xe5, 0x9f, 0x30, 0xc4,
  0xe1, 0xa0, 0x00, 0x06, 0xe5, 0x83, 0x2f, 0x78, 0xeb, 0x00, 0x00, 0x36,
  0xe2, 0x84, 0x4f, 0x59, 0xe5, 0x9f, 0x10, 0xb4, 0xe5, 0x9f, 0x00, 0xb4,
  0xe1, 0x2f, 0xff, 0x34, 0xe5, 0x9f, 0x30, 0xb0, 0xe1, 0x2f, 0xff, 0x33,
  0xe2, 0x84, 0x4c, 0x5f, 0xe1, 0xa0, 0x00, 0x05, 0xeb, 0x00, 0x00, 0x36,
  0xe2, 0x84, 0x40, 0x44, 0xe3, 0xe0, 0x30, 0x00, 0xe3, 0xe0, 0x20, 0x00,
  0xe3, 0xa0, 0x10, 0x0b, 0xe3, 0xa0, 0x00, 0x15, 0xe1, 0x2f, 0xff, 0x34,
  0xe3, 0xe0, 0x30, 0x00, 0xe3, 0xe0, 0x20, 0x00, 0xe3, 0xa0, 0x10, 0x0d,
  0xe3, 0xa0, 0x00, 0x15, 0xe1, 0x2f, 0xff, 0x34, 0xe3, 0xe0, 0x30, 0x00,
  0xe3, 0xe0, 0x20, 0x00, 0xe3, 0xa0, 0x10, 0x0f, 0xe3, 0xa0, 0x00, 0x15,
  0xe1, 0x2f, 0xff, 0x34, 0xe3, 0xe0, 0x30, 0x00, 0xe3, 0xe0, 0x20, 0x00,
  0xe3, 0xa0, 0x10, 0x10, 0xe3, 0xa0, 0x00, 0x15, 0xe1, 0x2f, 0xff, 0x34,
  0xe3, 0xe0, 0x30, 0x00, 0xe3, 0xe0, 0x20, 0x00, 0xe3, 0xa0, 0x10, 0x16,
  0xe3, 0xa0, 0x00, 0x15, 0xe1, 0x2f, 0xff, 0x34, 0xe3, 0xa0, 0x00, 0x00,
  0xe8, 0xbd, 0x80, 0x70, 0x08, 0x12, 0x00, 0x00, 0x01, 0xff, 0xf0, 0x00,
  0x08, 0x12, 0x90, 0x00, 0xe1, 0x2f, 0xff, 0x1e, 0x08, 0x13, 0x51, 0xd4,
  0x10, 0x16, 0xa0, 0x00, 0x10, 0x10, 0x01, 0x74, 0x00, 0x12, 0xf0, 0x00,
  0x00, 0x14, 0x80, 0x04, 0xe3, 0xa0, 0x00, 0x01, 0x12, 0xbd, 0x90, 0x00,
  0x00, 0x00, 0x40, 0x01, 0x08, 0x12, 0x98, 0xbc, 0x08, 0x12, 0xdc, 0xf0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x11, 0x0f, 0x10,
  0xe1, 0x2f, 0xff, 0x1e, 0xee, 0x01, 0x0f, 0x10, 0xe1, 0x2f, 0xff, 0x1e,
  0xee, 0x17, 0xff, 0x7a, 0x1a, 0xff, 0xff, 0xfd, 0xe3, 0xa0, 0x00, 0x00,
  0xee, 0x07, 0x0f, 0x9a, 0xe1, 0x2f, 0xff, 0x1e, 0xe1, 0x0f, 0x00, 0x00,
  0xe1, 0x2f, 0xff, 0x1e, 0xe1, 0x29, 0xf0, 0x00, 0xe1, 0x2f, 0xff, 0x1e,
  0xe9, 0x2d, 0x40, 0x30, 0xe1, 0xa0, 0x40, 0x00, 0xeb, 0x00, 0x39, 0xda,
  0xe5, 0x9f, 0x30, 0x1c, 0xe1, 0xa0, 0x50, 0x00, 0xe1, 0xa0, 0x00, 0x04,
  0xe1, 0x2f, 0xff, 0x33, 0xe1, 0xa0, 0x40, 0x00, 0xe1, 0xa0, 0x00, 0x05,
  0xeb, 0x00, 0x39, 0xd8, 0xe1, 0xa0, 0x00, 0x04, 0xe8, 0xbd, 0x80, 0x30,
  0xff, 0xff, 0xe3, 0xec, 0xe9, 0x2d, 0x40, 0x30, 0xe5, 0x8d, 0xe0, 0x04,
  0xe5, 0x8d, 0xc0, 0x08, 0xe5, 0x8d, 0x40, 0x0c, 0xe5, 0x8d, 0x60, 0x10,
  0xeb, 0x00, 0xb2, 0xfd, 0xea, 0xff, 0xff, 0xc9, 0x10, 0x14, 0x03, 0xf8,
  0x10, 0x62, 0x4d, 0xd3, 0x10, 0x14, 0x50, 0x00, 0x10, 0x14, 0x50, 0x20,
  0x10, 0x14, 0x00, 0x00, 0x10, 0x14, 0x00, 0x90, 0x10, 0x14, 0x00, 0x70,
  0x10, 0x14, 0x00, 0x98, 0x10, 0x14, 0x00, 0x84, 0x10, 0x14, 0x03, 0xe8,
  0x10, 0x14, 0x00, 0x3c, 0x00, 0x00, 0x01, 0x73, 0x00, 0x00, 0x01, 0x76,
  0xe9, 0x2d, 0x4f, 0xf0, 0xe2, 0x4d, 0xde, 0x17, 0xeb, 0x00, 0xb9, 0x92,
  0xe3, 0xa0, 0x10, 0x00, 0xe3, 0xa0, 0x20, 0x03, 0xe5, 0x9f, 0x0e, 0x68,
  0xeb, 0x00, 0xb3, 0x20
};
static const unsigned int arm_kernel_bin_len = 628;
